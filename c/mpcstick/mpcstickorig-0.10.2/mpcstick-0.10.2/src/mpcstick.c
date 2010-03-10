/***************************************************************************
 *            mpcstick.c
 *
 *  Simple MPD client to control an MPD server using a Linux Joystick Device 
 *  (/dev/input/jsX). Uses libmpdclient (http://www.musicpd.org/) and GLib.
 *
 *  Mon Apr 12 19:51:13 2004
 *  Copyright  2004  Aaron Bockover
 *  aaron@aaronbock.net
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/* Todo:

		1) Output redirection for daemon mode?
		2) Fix sensitivity issues with analog joypads
		3) Better axis support?
		4) Use g_timeout_add((mpd_server_timeout / 2) * 1000, mpc_ping, NULL)
		   instead of separate thread for calling mpd ping 
*/
 
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <glib.h>
#include <getopt.h>
#include <signal.h>
#include <errno.h>

#define PACKAGE "mpcstick"
#define VERSION "0.10.2"

#include "libmpdclient.h"

#define PING_WAIT while(pinging);
#define ASSERT_CONNECTION if(!conn) return FALSE;
#define CPE "Parse error on line %d of config file "

gboolean mpc_previous();
gboolean mpc_next();
gboolean mpc_volume_up();
gboolean mpc_volume_down();
gboolean mpc_playpause();
gboolean mpc_stop();
gboolean mpc_seek_left();
gboolean mpc_seek_right();
gboolean mpc_close();

enum {
	JS_BUTTON_NONE = 0,
	JS_AXIS_UP = 2,
	JS_AXIS_DOWN = 4,
	JS_AXIS_LEFT = 8,
	JS_AXIS_RIGHT = 16,
	JS_BUTTON_1 = 32,
	JS_BUTTON_2 = 64,
	JS_BUTTON_3 = 128,
	JS_BUTTON_4 = 256,
	JS_BUTTON_5 = 512,
	JS_BUTTON_6 = 1024,
	JS_BUTTON_7 = 2048,
	JS_BUTTON_8 = 4096,
	JS_BUTTON_9 = 8192,
	JS_BUTTON_10 = 16384
};

enum {
	CONFIG_SECTION_INVALID = 0,
	CONFIG_SECTION_GENERAL,
	CONFIG_SECTION_KEYBINDINGS
};

typedef struct {
	gchar *id;
	gboolean (*function)();
} js_function_table;

js_function_table function_table[] = {
	"previous", mpc_previous,
	"next", mpc_next,
	"volume_up", mpc_volume_up,
	"volume_down", mpc_volume_down,
	"playpause", mpc_playpause,
	"stop", mpc_stop,
	"seek_left", mpc_seek_left,
	"seek_right", mpc_seek_right,
	"close", mpc_close,
	NULL, NULL
};

typedef struct {
	gchar *id;
	gint code;
} js_button_table;

js_button_table button_table[] = {
	"JS_AXIS_UP", JS_AXIS_UP,
	"JS_AXIS_DOWN", JS_AXIS_DOWN,
	"JS_AXIS_LEFT", JS_AXIS_LEFT,
	"JS_AXIS_RIGHT", JS_AXIS_RIGHT,
	"JS_BUTTON_1", JS_BUTTON_1,
	"JS_BUTTON_2", JS_BUTTON_2,
	"JS_BUTTON_3", JS_BUTTON_3,
	"JS_BUTTON_4", JS_BUTTON_4,
	"JS_BUTTON_5", JS_BUTTON_5,
	"JS_BUTTON_6", JS_BUTTON_6,
	"JS_BUTTON_7", JS_BUTTON_7,
	"JS_BUTTON_8", JS_BUTTON_8,
	"JS_BUTTON_9", JS_BUTTON_9,
	"JS_BUTTON_10", JS_BUTTON_10,
	NULL, JS_BUTTON_NONE
};

typedef struct {
	gint button;
	gint function_index;
} keybinding;

typedef struct {
	gchar *js_dev_path;
	gchar *server_address;
	gint server_port;
	gint server_timeout;
	gint volume_change;
	gint seek_change;
	gboolean loaded_ok, js_debug;
	GList *keybindings;
} mpcstick_config;

mpcstick_config *config;
mpd_Connection *conn;
mpd_Status *status;
gboolean pinging;
GRand *rng;

gboolean run_callback(gint buttons)
{
	gint i, n_bindings;
	keybinding *key;
	gboolean called = FALSE, result = TRUE;
	
	n_bindings = g_list_length(config->keybindings);

	for(i = 0; i < n_bindings; i++) {
		key = g_list_nth_data(config->keybindings, i);
		
		if(key->button == buttons) {
			result = (*(function_table[key->function_index].function))();
			called = TRUE;
			break;
		}
	}
		
	if(!called && !config->js_debug)
		g_printerr("No action assigned to key combination (%d)\n", buttons);
	
	return result;
}

gint lookup_function(gchar *function_id)
{
	gint i;
	
	for(i = 0; function_table[i].function != NULL; i++) {
		if(g_strcasecmp(function_table[i].id, function_id) == 0) {
			return i;
		}
	}
	
	return -1;
}

gint lookup_button_code(gchar *button_id)
{
	gint i;
	
	for(i = 0; button_table[i].code != JS_BUTTON_NONE; i++) {
		if(g_strcasecmp(button_table[i].id, button_id) == 0) {
			return button_table[i].code;
		}
	}
	
	return JS_BUTTON_NONE;
}	

const gchar *lookup_button_name(gint code)
{
	gint i;
	
	for(i = 0; button_table[i].code != JS_BUTTON_NONE; i++) {
		if(code == button_table[i].code) {
			return button_table[i].id;
		}
	}
	
	return "JS_BUTTON_NONE";
}

gchar *joystick_available(const gchar *dev_path)
{
	int joyfd = 1;
	struct JS_DATA_TYPE jsd;
	gboolean ok;
	gchar ioctl_buffer[255];

	joyfd = open(dev_path, 0);                                 
	if(joyfd == 0)
		return FALSE;
	
	ok = read(joyfd, &jsd, JS_RETURN) == JS_RETURN;
	
	if(ok)
		ioctl(joyfd, JSIOCGNAME(255), &ioctl_buffer);
	
	close(joyfd);
	
	if(ok)
		return g_strdup(ioctl_buffer);
	
	return NULL;
}

void joystick_listen(gchar *joy_dev_path)
{
	gint jfd;
	struct js_event jse;
	gint pressed_button, pressed_axis, last_pressed_button, last_pressed_axis;
	gboolean call_callback;

	jfd = open(joy_dev_path, 0);                                 
	if(jfd == 0)
		return;      
	
	if(config->js_debug) {
		g_printf("\n** Entering Joystick Debug Mode. This mode will print\n"
		         "   a button's ID that should be used in the mcpstick\n"
		         "   configuration file when it is pressed. Useful for\n"
		         "   exploring the button map of your joystick device.\n\n");
	}
	
	pressed_button = JS_BUTTON_NONE;
	pressed_axis = JS_BUTTON_NONE;
	last_pressed_button = JS_BUTTON_NONE;
	last_pressed_button = JS_BUTTON_NONE;
	call_callback = TRUE;
	
	while(read(jfd, &jse, sizeof(struct js_event)) == sizeof(struct js_event)) {
		switch(jse.type) {
			case JS_EVENT_BUTTON:
				if(jse.value == 1) {
					switch(jse.number) {
						case 0: pressed_button = JS_BUTTON_1; break;
						case 1: pressed_button = JS_BUTTON_2; break;
						case 2: pressed_button = JS_BUTTON_3; break;
						case 3: pressed_button = JS_BUTTON_4; break;
						case 4: pressed_button = JS_BUTTON_5; break;
						case 5: pressed_button = JS_BUTTON_6; break;
						case 6: pressed_button = JS_BUTTON_7; break;
						case 7: pressed_button = JS_BUTTON_8; break;
						case 8: pressed_button = JS_BUTTON_9; break;
						case 9: pressed_button = JS_BUTTON_10; break;
						default: pressed_button = JS_BUTTON_NONE; break;
					}
					
					if(config->js_debug)
						g_printf("You pressed: %s\n", 
							lookup_button_name(pressed_button));
				} else {
					pressed_button = JS_BUTTON_NONE;
				}
				
				break;
			case JS_EVENT_AXIS:
				if(jse.value != 0) {
					if(jse.number == 0 && jse.value > 0) 
						pressed_axis = JS_AXIS_RIGHT;
					else if(jse.number == 0 && jse.value < 0) 
						pressed_axis = JS_AXIS_LEFT;
					else if(jse.number == 1 && jse.value > 0) 
						pressed_axis = JS_AXIS_DOWN;
					else if(jse.number == 1 && jse.value < 0) 
						pressed_axis = JS_AXIS_UP;
					else
						pressed_axis = JS_BUTTON_NONE;
					
					if(config->js_debug)
						g_printf("You pressed: %s\n", 
							lookup_button_name(pressed_axis));
				} else {
					pressed_axis = JS_BUTTON_NONE;
				}
				
				break;
			default:
				pressed_button = JS_BUTTON_NONE;
				pressed_axis = JS_BUTTON_NONE;
				break;
		}
			
		call_callback = 
			(!((last_pressed_axis != JS_BUTTON_NONE 
				&& pressed_axis == JS_BUTTON_NONE)
			|| (last_pressed_button != JS_BUTTON_NONE 
				&& pressed_button == JS_BUTTON_NONE))) &&
			(pressed_button | pressed_axis != JS_BUTTON_NONE
			&& (jse.value > 30000 || jse.value < 30000));
		
		last_pressed_axis = pressed_axis;
		last_pressed_button = pressed_button;
		
		if(call_callback)
			if(!run_callback(pressed_button | pressed_axis))
				break;
	
		call_callback = TRUE;
	}
	
	close(jfd);
}

gboolean mpc_get_status()
{
	ASSERT_CONNECTION;
	PING_WAIT;
	
	if((status = mpd_getStatus(conn)) == NULL) {
		g_printerr("Error: %s\n", conn->errorStr);
		mpd_closeConnection(conn);
		return FALSE;
	}
	
	mpd_finishCommand(conn);
	return TRUE;
}

gboolean mpc_previous()
{
	ASSERT_CONNECTION;
	PING_WAIT;
	
	mpd_sendPrevCommand(conn);
	mpd_finishCommand(conn);
	
	return TRUE;
}

gboolean mpc_next()
{
	ASSERT_CONNECTION;
	PING_WAIT;

	mpd_sendNextCommand(conn);
	mpd_finishCommand(conn);
	
	return TRUE;
}

gboolean mpc_volume_up()
{
	ASSERT_CONNECTION;
	PING_WAIT;
	
	mpc_get_status();
	mpd_sendSetvolCommand(conn, status->volume + config->volume_change);
	mpd_finishCommand(conn);
	
	return TRUE;
}

gboolean mpc_volume_down()
{
	ASSERT_CONNECTION;
	PING_WAIT;
	
	mpc_get_status();
	mpd_sendSetvolCommand(conn, status->volume - config->volume_change);
	mpd_finishCommand(conn);
	
	return TRUE;
}

gboolean mpc_playpause()
{
	gint index = 0;
	
	ASSERT_CONNECTION;
	PING_WAIT;
	
	mpc_get_status();
	
	if(status->state == MPD_STATUS_STATE_PAUSE 
		|| status->state == MPD_STATUS_STATE_PLAY) {
		mpd_sendPauseCommand(conn);
	} else {
		if(status->random)
			index = g_rand_int_range(rng, 0, status->playlist);
		mpd_sendPlayCommand(conn, index);
	}
	
	mpd_finishCommand(conn);
	
	return TRUE;
}

gboolean mpc_close()
{
	static gint second_last_call = 0;
	static gint last_call = 0;
	
	/* If pressed 3 times in t->2 seconds, quit the program... */
	
	if(second_last_call != 0) {
		if(time(NULL) - last_call <= 1)
			return FALSE;
		
		last_call = 0;
		second_last_call = 0;
	} else {
		if(last_call == 0) 
			last_call = time(NULL);
		else
			second_last_call = time(NULL);
	}

	return TRUE;
}

gboolean mpc_stop()
{
	ASSERT_CONNECTION;
	PING_WAIT;
	
	mpd_sendStopCommand(conn);
	mpd_finishCommand(conn);
	
	return TRUE;
}

gboolean mpc_seek_left()
{
	ASSERT_CONNECTION;
	PING_WAIT;
	
	mpc_get_status();
	mpd_sendSeekCommand(conn, status->song, 
		status->elapsedTime - config->seek_change);
	mpd_finishCommand(conn);
	
	return TRUE;
}

gboolean mpc_seek_right()
{
	ASSERT_CONNECTION;
	PING_WAIT;	
	
	mpc_get_status();
	mpd_sendSeekCommand(conn, status->song, 
		status->elapsedTime + config->seek_change);
	mpd_finishCommand(conn);
	
	return TRUE;
}

gboolean mpc_ping()
{
	ASSERT_CONNECTION;
	
	mpd_sendPingCommand(conn);
	mpd_finishCommand(conn);
	return TRUE;
}

void mpc_thread_ping(gint sleep_s)
{
	while(1) {
		pinging = TRUE;
		mpc_ping();
		pinging = FALSE;
		sleep(sleep_s);
	}
}

void config_dump(mpcstick_config *_config)
{
	gint i, n_keys;
	keybinding *key;
	
	g_printf("mpcstick configuration dump:\n");
	g_printf("\tserver_addr    = %s\n", _config->server_address);
	g_printf("\tserver_port    = %d\n", _config->server_port);
	g_printf("\tserver_timeout = %d\n", _config->server_timeout);
	g_printf("\tjs_device      = %s\n", _config->js_dev_path);
	g_printf("\tvolume_change  = %d\n", _config->volume_change);
	g_printf("\tseek_change    = %d\n", _config->seek_change);
	
	g_printf("\n\tkeybindings:\n");
	
	n_keys = g_list_length(_config->keybindings);
	for(i = 0; i < n_keys; i++) {
		key = g_list_nth_data(_config->keybindings, i);
		g_printf("\t%d = %d (%s)\n", key->button, key->function_index, 
			function_table[key->function_index].id);
	}
}

void config_add_keybinding(mpcstick_config *_config, 
	gint button, gint function_index)
{
	keybinding *key = (keybinding *)g_malloc(sizeof(keybinding));	
	if(!key)
		return;
	
	key->button = button;
	key->function_index = function_index;
	
	_config->keybindings = g_list_append(_config->keybindings, key);
}

mpcstick_config *config_new()
{
	mpcstick_config *_config 
		= (mpcstick_config*)g_malloc(sizeof(mpcstick_config));
	
	if(!_config)
		return NULL;
	
	_config->js_dev_path = g_strdup("/dev/input/js0");
	_config->server_address = g_strdup("localhost");
	_config->keybindings = NULL;
	
	_config->server_port = 2100;
	_config->server_timeout = 60;
	_config->volume_change = 5;
	_config->seek_change = 5;
	
	return _config;
}
	
void config_free(mpcstick_config *_config)
{
	gint i, n_items;
	
	if(_config == NULL)
		return;
	
	if(_config->js_dev_path != NULL)
		g_free(_config->js_dev_path);
	
	if(_config->server_address != NULL)
		g_free(_config->server_address);
	
	n_items = g_list_length(_config->keybindings);
	for(i = 0; i < n_items; i++) {
		g_free(g_list_nth_data(_config->keybindings, i));
	}
	
	g_list_free(_config->keybindings);
	g_free(_config);
	_config = NULL;
}

void config_parse_line(mpcstick_config *_config, gint section, 
	gchar *line, gint line_number)
{
	gchar **parts, **buttons;
	gchar *key, *value;
	gint button_1 = 0, button_2 = 0;
	gint button_code, function_index;
	
	parts = g_strsplit(line, "=", -1);
	
	if(parts[0] == NULL || parts[1] == NULL) {
		g_printerr(CPE "(invalid key/value pair formation)\n", line_number);
		return;
	}
	
	key = parts[0];
	value = parts[1];
	g_strstrip(key);
	g_strstrip(value);
	
	if(key == NULL || value == NULL) {
		g_printerr(CPE "(empty key or value)\n", line_number);
		return;
	}
	
	if(section == CONFIG_SECTION_GENERAL) {
		if(g_strcasecmp(key, "server_addr") == 0) {
			if(_config->server_address != NULL)
				g_free(_config->server_address);
			_config->server_address = g_strdup(value);
		} else if(g_strcasecmp(key, "js_device") == 0) {
			if(_config->js_dev_path != NULL)
				g_free(_config->js_dev_path);
			_config->js_dev_path = g_strdup(value);
		} else if(g_strcasecmp(key, "server_port") == 0) {
			_config->server_port = atoi(value);
		} else if(g_strcasecmp(key, "server_timeout") == 0) {
			_config->server_timeout = atoi(value);
		} else if(g_strcasecmp(key, "volume_change") == 0) {
			_config->volume_change = atoi(value);
		} else if(g_strcasecmp(key, "seek_change") == 0) {
			_config->seek_change = atoi(value);
		} else {
			g_printerr(CPE "(unkown key '%s')\n", line_number, key);
		}
	} else if(section == CONFIG_SECTION_KEYBINDINGS) {
		buttons = g_strsplit(key, "|", 2);
		g_strstrip(buttons[0]);
		
		button_1 = lookup_button_code(buttons[0]);
		if(buttons[1] != NULL) {
			g_strstrip(buttons[1]);
			button_2 = lookup_button_code(buttons[1]);
			
		}
		
		button_code = button_1 | button_2;
		function_index = lookup_function(value);
		
		g_strfreev(buttons);
		
		if(button_code <= 0) {
			g_printerr(CPE "(invalid button setup: %s)\n", line_number, key);
			return;
		}
		
		if(function_index < 0) {
			g_printerr(CPE "(unkown button map function '%s')\n", 
				line_number, value);
			return;
		}
		
		config_add_keybinding(_config, button_code, function_index);
	} else {
		g_printerr(CPE "(data not in valid section)\n", line_number);
	}
}

mpcstick_config *config_load(gchar *config_path)
{
	const gint buffer_size = 255;
	gchar *buffer = NULL;
	gchar t_buf[buffer_size];
	gchar **lines;
	FILE *fd;
	gint config_section = CONFIG_SECTION_INVALID, i;
	mpcstick_config *_config;
	
	_config = config_new();
	
	fd = fopen(config_path, "r");
	if(!fd) {
		_config->loaded_ok = FALSE;	
		return _config;
	}
		
	buffer = (gchar *)g_malloc(buffer_size + 1);
	buffer[0] = '\0';
	
	while(fgets((gchar *)&t_buf, buffer_size, fd)) {
		strcat(buffer, t_buf);
		buffer = (gchar *)g_realloc(buffer, strlen(buffer) + buffer_size + 1);		
	}
	
	fclose(fd);
	
	lines = g_strsplit(buffer, "\n", -1);
	g_free(buffer);
	
	for(i = 0; lines[i] != NULL; i++) {
		g_strstrip(lines[i]);
		
		if(g_strncasecmp(lines[i], "[general]", 9) == 0) 
			config_section = CONFIG_SECTION_GENERAL;
		else if(g_strncasecmp(lines[i], "[keybindings]", 13) == 0) 	
			config_section = CONFIG_SECTION_KEYBINDINGS;
		else if(lines[i] != NULL && strlen(lines[i]) > 0)
			config_parse_line(_config, config_section, lines[i], i + 1);
	}
	
	g_strfreev(lines);
	
	_config->loaded_ok = TRUE;
	return _config;
}

void mpc_quit()
{
	g_printf("Closing connection and exiting...\n");
	mpd_closeConnection(conn);
	conn = NULL;
	config_free(config);
}

void signal_callback(int signal_caught)
{
	static int t = 0;
	switch(signal_caught) {
		case SIGINT: 
			if(t++ == 0) {
				mpc_quit(); 
				exit(0); 
			}
			
			break;
	}
}	

void print_version()
{
	g_printf("%s (MPD Client Daemon) %s\n\n", PACKAGE, VERSION);
	g_printf("Copyright (C) 2004 Aaron Bockover <aaron@aaronbock.net>\n");
	g_printf("This is free software; see the source for copying conditions.  There is NO\n");
	g_printf("warranty; not even MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
}

void print_usage(gchar *name)
{
	g_printf("usage:\n");
	g_printf("   %s [options]\n\n", name);
	
	g_printf("   --help                     prints this help\n");
	g_printf("   --version                  shows version information\n");
	g_printf("   --config-file <file>       specify alternate config file the default\n");
	g_printf("                              is ~/.mpcstick\n");
	g_printf("   --config-dump              print debug output of loaded configuration\n");
	g_printf("   --js-device <device path>  path to joystick device - overrides the\n");
	g_printf("                              default joystick device and the device\n");
	g_printf("                              provided in mpcstick configuration\n");
	g_printf("   --js-debug                 print joystick button IDs to screen to\n");
	g_printf("                              make it easier to discover the button\n");
	g_printf("                              mapping of a device. Only available\n");
	g_printf("                              in standalone mode.\n");
	g_printf("   --standalone               run mpcstick in terminal (do not fork to daemon)\n");
	g_printf("\n");
}

int main(int argc, char **argv)
{
	GThread *thread;
	GError *error = NULL;
	gchar *config_file = NULL, *js_device = NULL, c;
	gboolean dump_config = FALSE, standalone = FALSE, js_debug = FALSE;
	gchar *js_device_name;
	
	/* Parse command line options */
  	while(1) {
		static struct option long_options[] = {
			{"config-file", required_argument, 0, 'f'},
			{"standalone",  no_argument,       0, 's'},
			{"config-dump", no_argument,       0, 'd'},
			{"js-device",   required_argument, 0, 'j'},
			{"js-debug",    no_argument,       0, 'g'},
			{"help",        no_argument,       0, 'h'},
			{"version",     no_argument,       0, 'v'},
			{0, 0, 0, 0}
		};
		
		int option_index = 0;
      	c = getopt_long(argc, argv, "fdsjg", long_options, &option_index);
		
      	if(c == -1)
        	break;

		switch(c) {
			case 'f': config_file = g_strdup(optarg); break;
			case 'j': js_device = g_strdup(optarg); break;
			case 's': standalone = TRUE; break;
			case 'd': dump_config = TRUE; break;
			case 'g': js_debug = TRUE; break;
			case 'h': print_usage(argv[0]); exit(1); break;
			case 'v': print_version(); exit(1); break;
		}
	}
	
	/* For choosing a random play index when stopped */
	rng = g_rand_new();
	
	/* Load configuration file */
	if(config_file == NULL) 
		config_file = g_strconcat(g_get_home_dir(), "/.mpcstick", NULL);
	
	config = config_load(config_file);
	if(dump_config)
		config_dump(config);

	if(js_device != NULL) {
		g_free(config->js_dev_path);
		config->js_dev_path = g_strdup(js_device);
		g_free(js_device);
	}

	config->js_debug = js_debug;
	
	if(!config->loaded_ok) {
		g_printerr("Could not load configuration from %s\n", config_file);
	} else {
		g_printf("Using configuration file %s\n", config_file);
	}
	
	g_free(config_file);
	
	/* See if there really is a joystick */
	js_device_name = joystick_available(config->js_dev_path);
	if(!js_device_name) {
		g_printerr("Joystick device not found: %s\n", config->js_dev_path);
		exit(1);
	}
	
	/* Connect to MPD server */
	conn = mpd_newConnection(config->server_address, config->server_port,
		config->server_timeout);
	if(conn->error) {
		g_printf("mpd connection error: %s\n", conn->errorStr);
		mpd_closeConnection(conn);
		exit(1);
	}

	g_printf("Connected to mpd server (%s:%d) Version %d.%d.%d\n",
		config->server_address, config->server_port, 
		conn->version[0], conn->version[1], conn->version[2]);
	
	g_printf("Listening to joystick on %s: %s\n", 
		config->js_dev_path, js_device_name);
	g_free(js_device_name);
	
	if(standalone) {
		/* Set up a signal catcher to exit nicely on CTRL+C at the console */
		signal(SIGINT, signal_callback);
	} else {
		/* Fork into a daemon: code basically taken directly from mpd itself */
		int pid;
		
		if(js_debug) {
			g_printf("\n** JS Debug mode is only available when mpcstick is\n"
			         "   running in standalone mode. To run mpcstick in\n"
			         "   standalone mode, use the --standalone option.\n\n");
		}
		
		g_printf("Forking mpcstick into daemon mode...\n");
		
		pid = fork();
		
		if(pid > 0) 
			_exit(0);
		else if(pid < 0) {
			g_printerr("Could not fork mpcstick to daemon\n");
			exit(1);
		}
		
		if(chdir("/") < 0) {
			g_printerr("Could not change to root directory\n");
			exit(1);
		}
		
		if(setsid() < 0) {
			g_printerr("Could not setsid\n");
			exit(1);
		}
		
		if(close(STDOUT_FILENO)) {
			fprintf(stderr,"Could not close stdout : %s\n", strerror(errno));
			exit(1);
		}
		
		if(close(STDERR_FILENO)) {
			g_printerr("Could not close stderr : %s\n", strerror(errno));
			exit(1);
		}
	}
	
	/* Initialize thread for calling ping to MPD server */
	g_thread_init(NULL);
	thread = g_thread_create((GThreadFunc)mpc_thread_ping, 
		GINT_TO_POINTER(config->server_timeout / 2), FALSE, &error);
	if(!thread) {
		g_printerr("Failed to create thread: %s\n", error->message);
		exit(1);
    }
	
	/* Listen on the joystick ('main loop') */
	joystick_listen(config->js_dev_path);
	
	/* Clean up and leave */
	mpc_quit();
	
	exit(0);
}

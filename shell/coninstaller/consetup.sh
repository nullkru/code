#!/bin/bash
#by kru<@chao.ch> [http://chao.ch] 
#for acaridev.ch yeah weeeeeee pwnz
#date: 25.06.2006

#VARS
PRNAME=$@
MYSQLDUMP="$HOME/skeletons/contenido/condb_20060625.sql"
HOME=/home/mmesser
[[ ! $1 ]] && echo "usage: $0 <projectname>" && exit 1

main() {

echo "Welcome to acaridev contenido installer!"
echo -e "========================================\n\n"


echo -e "Projectname == mmesser_<prname>: $PRNAME is this correct?[N/y] \c "
read ANSWER
	if [[ "$ANSWER" == "y" ]]; then
		setup
	else
		echo "Stop!#@?!"
		return 1
	fi

}

endout() {
	echo "Setup finished..."
	echo -e "=================\n"

	echo "The following stuff you had todo manually"
	echo "+ in contenido > administration > mandanten : pfäde anpassen"
}

mysqladd() {
	
	printf "Creating mysql structure." ; sleep 0.5 ; printf "." ; sleep 0.5 ; printf "." ; sleep 0.5 ; printf ".\n\n"
	
	mysql -ummesser -pmilbe-spiderdev! -D mmesser_con$PRNAME < $MYSQLDUMP
	endout
	}


setup() {

printf "Creating directory,file structure and mysql DB." ; sleep 0.5 ; printf "." ; sleep 0.5 ; printf "." ; sleep 0.5 ; printf ".\n\n"

echo "Creating DB!"
if [[ -d "$HOME/www/$PRNAME" ]]; then 
	echo "Sorry $HOME/www/$PRNAME exists. Stop"
	return 1;
else
	mkdir -p $HOME/www/$PRNAME
fi


cp -r $HOME/skeletons/contenido/* $HOME/www/$PRNAME/

	#create config.php for contenido
rm -rf $HOME/www/$PRNAME/con/contenido/includes/config.php
touch  $HOME/www/$PRNAME/con/contenido/includes/config.php
cat << EOF > $HOME/www/$PRNAME/con/contenido/includes/config.php
<?php

/******************************************
* File      :   config.php
* Project   :   $PRNAME
* Descr     :   Defines all general
*               variables of Contenido.
*
* © four for business AG
******************************************/

global \$cfg;

/* Section 1: Path settings
 * ------------------------
 *
 * Path settings which will vary along different
 * Contenido settings.
 *
 * A little note about web and server path settings:
 * - A Web Path can be imagined as web addresses. Example:
 *   http://192.168.1.1/test/
 * - A Server Path is the path on the server's hard disk. Example:
 *   /var/www/html/contenido    for Unix systems OR
 *   c:/htdocs/contenido        for Windows systems
 *
 * Note: If you want to modify the locations of subdirectories for
 *       some reason (e.g. the includes directory), see Section 8.
 */

/* The root server path to the contenido backend */
\$cfg['path']['contenido']               = '/home/mmesser/public_html/$PRNAME/con/contenido/';

/* The web server path to the contenido backend */
\$cfg['path']['contenido_fullhtml']      = 'http://$PRNAME.acaridev.ch/con/contenido/';

/* The root server path where all frontends reside */
\$cfg['path']['frontend']                = '/home/mmesser/public_html/$PRNAME/con';

/* The root server path to the conlib directory */
\$cfg['path']['phplib']                  = '/home/mmesser/public_html/$PRNAME/con/conlib/';

/* The root server path to the pear directory */
\$cfg['path']['pear']                    = '/home/mmesser/public_html/$PRNAME/con/pear/';

/* The server path to the desired WYSIWYG-Editor */
\$cfg['path']['wysiwyg']                 = '/home/mmesser/public_html/$PRNAME/con/contenido/external/wysiwyg/tinymce2/';

/* The web path to the desired WYSIWYG-Editor */
\$cfg['path']['wysiwyg_html']            = 'http://$PRNAME.acaridev.ch/con/contenido/external/wysiwyg/tinymce2/';

/* The server path to all WYSIWYG-Editors */
\$cfg['path']['all_wysiwyg']                 = '/home/mmesser/public_html/$PRNAME/con/contenido/external/wysiwyg/';

/* The web path to all WYSIWYG-Editors */
\$cfg['path']['all_wysiwyg_html']            = 'http://$PRNAME.acaridev.ch/con/contenido/external/wysiwyg/';





/* Section 2: Database settings
 * ----------------------------
 *
 * Database settings for MySQL. Note that we don't support
 * other databases in this release.
 */

/* The prefix for all contenido system tables, usually "con" */
\$cfg['sql']['sqlprefix'] = 'con';

/* The host where your database runs on */
\$contenido_host = 'localhost';

/* The database name which you use */
\$contenido_database = 'mmesser_con$PRNAME';

/* The username to access the database */
\$contenido_user = 'mmesser';

/* The password to access the database */
\$contenido_password = 'milbe-spiderdev!';

\$cfg["database_extension"] = 'mysql';

\$cfg["nolock"] = false;

\$cfg["is_start_compatible"] = false;
?>
EOF

mysqladd

}

#start
main


#EOF

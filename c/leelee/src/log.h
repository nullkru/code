#ifndef LOG_H
#define LOG_H


#define LOG_MUTE   -1

#define LOG_FATAL  0
#define LOG_STATUS 1 
#define LOG_WARN   2 
#define LOG_INFO   3 
#define LOG_DEBUG1 4 
#define LOG_DEBUG2 5 // show all traffic


extern void log_printf(int llevel, int errstr, const char *fmt, ...);


#define log_print(llevel,fmt...) (log_printf(llevel, 0, fmt))
#define log_perror(llevel,fmt...) (log_printf(llevel, 1, fmt))

#define debug(a,b...) log_print(LOG_DEBUG ## a, b);


#endif /* #ifndef LOG_H */

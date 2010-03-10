#ifndef CLIENT_H
#define CLIENT_H

extern int       client_fd; 

extern void client_connect (void);
extern void client_close   (void);
extern void client_write   (const char *buffer, size_t buflen);
extern void client_read    (void);
extern void init_ssl(void);

#endif /* #ifdef CLIENT_H */

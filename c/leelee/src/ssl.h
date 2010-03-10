#ifndef SSL_H
#define SSL_H

extern void init_ssl(void);
extern void ssl_handshake(int fd);

extern SSL *ssl;

#endif

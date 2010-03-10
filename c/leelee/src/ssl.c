#include <openssl/ssl.h>

#include "log.h"

static SSL_CTX *ctx;
static SSL_METHOD *meth;
SSL *ssl;

void init_ssl(void)
{
   log_print(LOG_STATUS, "initializing ssl");
   SSL_load_error_strings();
   SSLeay_add_ssl_algorithms();
   meth = SSLv23_client_method();
   ctx = SSL_CTX_new(meth);
   if(SSL_CTX_use_certificate_file(ctx, "ssl.crt", SSL_FILETYPE_PEM) <= 0)
     {
	log_perror(LOG_FATAL, "couldn't open certificate");
	exit(1);
     }
   
   if(SSL_CTX_use_PrivateKey_file(ctx, "ssl.key", SSL_FILETYPE_PEM) <= 0)
     {
	log_perror(LOG_FATAL, "couldn't open private key");
	exit(1);
     }
   
   if(!SSL_CTX_check_private_key(ctx))
     {
	log_perror(LOG_FATAL, "bad private key");
	exit(1);
     }   
}

void ssl_handshake(int fd)
{
   ssl = SSL_new(ctx);
   if(!ssl)
     {
	log_perror(LOG_FATAL, "couldn't create ssl object");
	exit(1);
     }
   
   SSL_set_connect_state(ssl);
   SSL_set_fd(ssl, fd);
   
   if(SSL_connect(ssl) < 0)
     {
	log_perror(LOG_FATAL, "ssl handshake failed");
	exit(1);
     }   
}

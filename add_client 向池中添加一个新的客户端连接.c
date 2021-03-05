#include "csapp.h"

void add_client(int connfd, pool *p)
{
    int i;
    p->nready--;
    for (i = 0; i < FD_SETSIZE; i++) 
        if (p->clientfd[i] < 0) {
           
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);

           
            FD_SET(connfd, &p->read_set);

           
            if (connfd > p->maxfd)
                p->maxfd = connfd;
            if (i > p->maxi)
                p->maxi = i;
            break;
        }
    if (i == FD_SETSIZE) 
        app_error("add_client error: Too many clients");
}
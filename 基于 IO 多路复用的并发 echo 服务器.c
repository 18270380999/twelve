#include "csapp.h"

typedef struct { 
    int maxfd;        
    fd_set read_set;  
    fd_set ready_set; 
    int nready;       
    int maxi;        
    int clientfd[FD_SETSIZE];    
    rio_t clientrio[FD_SETSIZE]; 
} pool;

int byte_cnt = 0; 

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    listenfd = Open_listenfd(argv[1]);
    init_pool(listenfd, &pool);

    while (1) {
        
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);
        
      
        if (FD_ISSET(listenfd, &pool.ready_set)) {
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            add_client(connfd, &pool);
        }
        
       
        check_clients(&pool);
    }
}
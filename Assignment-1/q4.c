#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *host_lookup(char *ip_addr) {
    
    struct sockaddr_in temp;
    socklen_t l;
    char buf[NI_MAXHOST], *ret_buf;

    temp.sin_family = AF_INET;
    temp.sin_addr.s_addr = inet_addr(ip_addr);
    l = sizeof(struct sockaddr_in);
    if (getnameinfo((struct sockaddr *) &temp, l, buf, sizeof(buf), NULL, 0, NI_NAMEREQD)) {
        printf("Could not resolve lookup of the hostname\n");
        return NULL;
    }
    ret_buf = (char *)malloc((strlen(buf) + 1) * sizeof(char));
    strcpy(ret_buf, buf);
    return ret_buf;
}

int main(int argc, char *argv[]) {
    char *ip_addr = argv[1];
    char *reverse_hostname = host_lookup(ip_addr);
    printf("Host domain: %s\n", reverse_hostname);
}
/**
* @file q2_server.c
* @brief server program for UDP file transfer demonstration
*
* @author Bhavye Jain
* @date August 2019
*/

#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
#define IP_PROTOCOL 0 
#define PORT_NO 15050 
#define NET_BUF_SIZE 32 
#define cipherKey 'S' 
#define sendrecvflag 0 
#define nofile "File Not Found!" 
  
/** 
* function to clear buffer 
* @param b The buffer
*/
void clearBuffer(char* b) { 
    int i; 
    for (i = 0; i < NET_BUF_SIZE; i++) 
        b[i] = '\0'; 
} 
  
/** 
* function to encrypt using xor
* @param ch The character to be encrypted
*/
char encrypt(char ch) { 
    return ch ^ cipherKey; 
} 
  
/**
* function to send file 
* @param fp FILE pointer
* @param buf The buffer
* @param s The buffer size
*/
int sendFile(FILE* fp, char* buf, int s) { 
    int i, len; 
    if (fp == NULL) { 
        strcpy(buf, nofile); 
        len = strlen(nofile); 
        buf[len] = EOF; 
        for (i = 0; i <= len; i++) 
            buf[i] = encrypt(buf[i]); 
        return 1; 
    } 
  
    char ch, ch2; 
    for (i = 0; i < s; i++) { 
        ch = fgetc(fp); 
        ch2 = encrypt(ch); 
        buf[i] = ch2; 
        if (ch == EOF) 
            return 1; 
    } 
    return 0; 
} 

int main() 
{ 
    int sockfd, nBytes; 
    struct sockaddr_in addr_con; 
    int addrlen = sizeof(addr_con); 
    addr_con.sin_family = AF_INET; 
    addr_con.sin_port = htons(PORT_NO); 
    addr_con.sin_addr.s_addr = INADDR_ANY; 
    char net_buf[NET_BUF_SIZE]; 
    FILE* fp; 
  
    /// create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL); 
  
    if (sockfd < 0) 
        printf("\nfile descriptor not received!!\n"); 
    else
        printf("\nfile descriptor %d received\n", sockfd); 
  
    if (bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con)) == 0) 
        printf("\nBinding successfull!\n"); 
    else
        printf("\nBinding Failed!\n"); 
  
    while (1) { 
        printf("\nListening for file request...\n"); 
  
        /// receive file name 
        clearBuffer(net_buf); 
  
        nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*) &addr_con, (socklen_t*) &addrlen); 
  
        printf("\nRequest Received For File: %s\n", net_buf); 

        fp = fopen(net_buf, "r"); 
        
        if (fp == NULL) 
            printf("\nFile open failed!\n"); 
        else
            printf("\nFile Opened Successfully!\n"); 
  
        while (1) { 
            if (sendFile(fp, net_buf, NET_BUF_SIZE)) { 
                sendto(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, addrlen); 
                break; 
            } 
  
            sendto(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, addrlen); 
            clearBuffer(net_buf); 
        } 

        printf("\nData Sent!\n");

        if (fp != NULL) 
            fclose(fp); 
    } 
    return 0; 
}
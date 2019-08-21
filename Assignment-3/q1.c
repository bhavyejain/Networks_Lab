/**
* @file q2_client.c
* @brief program to find out the class, network id and host id of a given IP address.
*
* @author Bhavye Jain
* @date August 2019
*/

#include <stdio.h> 
#include <string.h> 
  
/** 
* Function to find out the Class of the IP address
* @param ip_addr IP address string
*/
char getClass(char ip_addr[]) { 
    char octet[4];    // variable to store the first octet
    int i = 0; 
    while (ip_addr[i] != '.') { 
        octet[i] = ip_addr[i]; 
        ++i; 
    } 
    --i; 
  
    // convert octet to number
    int ip = 0, j = 1; 
    while (i >= 0) { 
        ip = ip + (octet[i] - '0') * j; 
        j = j * 10; 
        i--; 
    } 
  
    if (ip >=1 && ip <= 126) 
        return 'A'; 

    else if (ip >= 128 && ip <= 191) 
        return 'B'; 
  
    else if (ip >= 192 && ip <= 223) 
        return 'C'; 

    else if (ip >= 224 && ip <= 239) 
        return 'D'; 

    else
        return 'E'; 
} 
  
/** 
* Function to get Network ID as well as Host ID 
* @param ip_addr IP address string
* @param ip_class IP address class
*/
void getNetworkAndHostID(char ip_addr[], char ip_class) { 

    // Initializing network and host array to NULL 
    char network[12], host[12]; 
    for (int k = 0; k < 12; k++) 
        network[k] = host[k] = '\0'; 
  
    /// Class A
    if (ip_class == 'A') { 

        int i = 0, j = 0; 
        while (ip_addr[j] != '.') 
            network[i++] = ip_addr[j++]; 
        i = 0; 
        j++; 
        while (ip_addr[j] != '\0') 
            host[i++] = ip_addr[j++]; 
        printf("Network ID is %s\n", network); 
        printf("Host ID is %s\n", host); 
    } 
  
    /// Class B
    else if (ip_class == 'B') {

        int i = 0, j = 0, dotCount = 0; 
        while (dotCount < 2) 
        { 
            network[i++] = ip_addr[j++]; 
            if (ip_addr[j] == '.') 
                dotCount++; 
        } 
        i = 0; 
        j++; 
  
        while (ip_addr[j] != '\0') 
            host[i++] = ip_addr[j++]; 
  
        printf("Network ID is %s\n", network); 
        printf("Host ID is %s\n", host); 
    } 
  
    /// Class C
    else if (ip_class == 'C') { 

        int i = 0, j = 0, dotCount = 0; 
        while (dotCount < 3) 
        { 
            network[i++] = ip_addr[j++]; 
            if (ip_addr[j] == '.') 
                dotCount++; 
        } 
  
        i = 0; 
        j++; 
  
        while (ip_addr[j] != '\0') 
            host[i++] = ip_addr[j++]; 
  
        printf("Network ID is %s\n", network); 
        printf("Host ID is %s\n", host); 
    } 

    else
        printf("IP address is not divided into Network and Host ID in this class\n"); 
} 

int main() { 
    char ip_addr[14];
    printf("Enter IP address\n");
    scanf("%s", ip_addr);
    char ip_class = getClass(ip_addr); 
    printf("Given IP address belongs to Class %c\n", ip_class); 
    getNetworkAndHostID(ip_addr, ip_class); 
    return 0; 
} 
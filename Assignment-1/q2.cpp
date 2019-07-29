#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    struct ifreq ifr;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    string ans;
    char buff[3];
    strcpy(ifr.ifr_name, "enp3s0");

    if (ioctl(fd, SIOCGIFHWADDR, &ifr) == 0) {
        for (int i = 0; i <= 5; i++){
            snprintf(buff, sizeof(buff), "%.2x", (unsigned char)ifr.ifr_addr.sa_data[i]);
            ans = ans + buff + ":";
        }
        cout << "MAC address: " << ans << endl;
        return 0;
    }

    return 1;
}
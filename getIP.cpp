#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <iostream>
#include <cstdlib>
#include <cstring>

int getIP(char*);

int main(){
    char b[100];
    getIP(b);
    printf("%s\n",b);
    return 0;
}

int getIP(char* box)
{
    struct ifaddrs *addresses;

    if(getifaddrs(&addresses) == -1){
            printf("getifaddrs call failed\n");
            return 0;
    }

    struct ifaddrs *address = addresses;
    while(address)
    {
        int family = address->ifa_addr->sa_family;
        if(family == AF_INET || family == AF_INET6)
        {
            if (strcmp(address->ifa_name , "lo"))
            {
                char ap[100];
                const int family_size = family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
                getnameinfo(address->ifa_addr, family_size, box, sizeof(ap), 0, 0, NI_NUMERICHOST);
                //printf("%s\n", box);
                break;
            }
        }
        address = address->ifa_next;
    }
    freeifaddrs(addresses);
    return 0;
    
}

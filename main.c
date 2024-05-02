#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include "memory.h"

typedef struct {
    uint8_t dest_addr[6]; // 宛先アドレス
    uint8_t src_addr[6];  // 送信元アドレス
    uint16_t type;        // イーサタイプ
}EtherHdr;


int main(void){
    uint8_t buff[20];
    uint16_t type = 0x0800;
    EtherHdr *hdr;
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

    strcpy(s.ifr_name, "eth0");
    if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
        int i;
        for (i = 0; i < 6; ++i){
            memcpy(&buff[i],&(s.ifr_addr.sa_data[i]),1);
        }
        for (i = 0; i < 6; ++i){
            memcpy(&buff[i + 6],&(s.ifr_addr.sa_data[i]),1);
        }
    buff[12] = (uint8_t)(type & 0xFF); // 下位8ビットを12バイト目にセット
    buff[13] = (uint8_t)((type>> 8) & 0xFF); // 上位8ビットを13バイト目にセット
    }
    int a;
    for(a=0;a<14;a++){
        printf(" %02x", buff[a]);
    }
    return 0;
}
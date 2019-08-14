#include"sarp.h"

void makeArp(uint8_t* mIp,u_char* sMac, struct eth_header* eth,struct arp_header* arp){
    u_char broad[6] ={255,255,255,255,255,255};
    u_char zr[6] ={0};

    memcpy(eth->dstMac,broad,6);
    memcpy(eth->srcMac,sMac,6);
    arp->opCode[0] = {0x00};
    arp->opCode[1] = {0x01};
    memcpy(arp->sMac,sMac,6);
    memcpy(arp->sIp,mIp,4);
    memcpy(arp->dMac,zr,6);
    //memcpy(arp->dIp,senIp,4);
}
void sendArp(struct eth_header* eth, struct arp_header* arp,char* dev){
    u_char packet[42];
    makePacket(packet,eth,arp);
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *handle = pcap_open_live(dev
                , BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return ;
    }

    pcap_sendpacket(handle,packet,42);
}

void broadcasting(uint8_t* mIp,u_char* mMac,char* dev){
    struct eth_header eth;
    struct arp_header arp;
    makeArp(mIp,mMac,&eth, &arp);
    sendArp(&eth,&arp,dev);
}

#include "sarp.h"

int main(int argc,char* argv[]){

    if(argc!=2){
        printf("Need more argument");
        return -1;
    }

    u_char mMac[6];
    uint8_t mIp[4];
    
    myInfo(argv[1], mMac, mIp);
    
    while(1){
        int flag = 0;
        flag = table_check();
        if(flag!=0){
            system("sudo arp -d wlan0");//, argv[1]);
            broadcasting();
        }
    }

    return 0;
}

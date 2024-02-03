#include "base64.h"
#include <stdint.h>

const char map[64]= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int base64Encode(const uint8_t *src, size_t srclen, char *dst, size_t dstlen){

    if(!src || !dst){
        return 1;
    }

    if(dstlen/4 * 3 < srclen + 1){
        return 2;
    }

    while(srclen >= 3){ 
        srclen -= 3;
        uint32_t tmp = src[0] << 16
                     | src[1] << 8
                     | src[2];
        src += 3;
        dst[0] = map[(tmp >> 18) & 0x3F];
        dst[1] = map[(tmp >> 12) & 0x3F];
        dst[2] = map[(tmp >>  6) & 0x3F];
        dst[3] = map[(tmp      ) & 0x3F];
        dst += 4;
    }


    uint32_t tmp;
    switch(srclen){
        case 0:
            break;

        case 1:
            tmp = src[0] << 16; 
            dst[0] = map[(tmp >> 18) & 0x3F];
            dst[1] = map[(tmp >> 12) & 0x3F];
            dst[2] = '=';
            dst[3] = '=';
            dst += 4;
            break;

        case 2:
            tmp = src[0] << 16
                | src[1] << 8; 
            dst[0] = map[(tmp >> 18) & 0x3F];
            dst[1] = map[(tmp >> 12) & 0x3F];
            dst[2] = map[(tmp >>  6) & 0x3F];
            dst[3] = '=';
            dst += 4;
            break;

        default:
            break;
    }

    dst[0] = '\0';

    return 0;

}
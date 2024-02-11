#include "base64.h"
#include <stdint.h>

const char map[64]= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int indexOf(int c){
    for(int i = 0; i < 64; i++){
        if(map[i] == c){
            return i;
        }
    }

    if(c == '='){
        return 0;
    }

    return -1;
}

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

int base64Decode(const char *src, size_t srclen, uint8_t *dst, size_t dstlen){

    if(!src || !dst){
        return 1;
    }

    if(srclen & 3 == 1){
        return 3;
    }

    if(srclen/4 * 3 > dstlen){
        return 2;
    }

    while(srclen >= 4){
        srclen -= 4;
        uint32_t tmp = indexOf(src[0]) << 18
                     | indexOf(src[1]) << 12
                     | indexOf(src[2]) << 6
                     | indexOf(src[3]);
        src += 4;
        dst[0] = (tmp >> 16) & 0xFF;
        dst[1] = (tmp >>  8) & 0xFF;
        dst[2] = (tmp      ) & 0xFF;
        dst += 3;
    }

    uint32_t tmp;
    if(srclen == 2){
        tmp = indexOf(src[0]) << 18
            | indexOf(src[1]) << 12;
        dst[0] = (tmp >> 16) & 0xFF;
    }else if(srclen == 3){
        tmp = indexOf(src[0]) << 18
            | indexOf(src[1]) << 12
            | indexOf(src[2]) << 6;
        dst[0] = (tmp >> 16) & 0xFF;
        dst[1] = (tmp >>  8) & 0xFF;
    }

    return 0;
}
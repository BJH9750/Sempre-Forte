#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <map>
#include <unistd.h>
#include <vector>
#include <openssl/evp.h>
#include <LIEF/LIEF.hpp>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <random>

using namespace std;

static unordered_map<uint8_t, uint8_t> cvt, rcvt;

uint32_t* init_table()
{
    uint32_t* op_table = (uint32_t *)malloc(sizeof(uint32_t) * 256);
    
    op_table[0x00] = 2, op_table[0x0e] = 2, op_table[0x80] = 2, op_table[0x01] = 2, op_table[0x81] = 2, op_table[0x82] = 2, op_table[0x04] = 2, op_table[0x83] = 2, 
    op_table[0x84] = 2, op_table[0x07] = 2, op_table[0x85] = 2, op_table[0x86] = 2, op_table[0x87] = 2, op_table[0x88] = 2, op_table[0x89] = 2, op_table[0x8a] = 2, 
    op_table[0x8b] = 2, op_table[0x8c] = 2, op_table[0x8d] = 2, op_table[0x8e] = 2, op_table[0x12] = 2, op_table[0x8f] = 2, op_table[0x21] = 2, op_table[0xb0] = 2, 
    op_table[0xb1] = 2, op_table[0xb2] = 2, op_table[0xb3] = 2, op_table[0xb4] = 2, op_table[0xb5] = 2, op_table[0xb6] = 2, op_table[0xb7] = 2, op_table[0xb8] = 2, 
    op_table[0xb9] = 2, op_table[0xba] = 2, op_table[0xbb] = 2, op_table[0xbc] = 2, op_table[0xbd] = 2, op_table[0xbe] = 2, op_table[0xbf] = 2, op_table[0xc0] = 2, 
    op_table[0xc1] = 2, op_table[0xc2] = 2, op_table[0xc3] = 2, op_table[0xc4] = 2, op_table[0xc5] = 2, op_table[0xc6] = 2, op_table[0xc7] = 2, op_table[0xc8] = 2, 
    op_table[0xc9] = 2, op_table[0xca] = 2, op_table[0xcb] = 2, op_table[0xcc] = 2, op_table[0xcd] = 2, op_table[0xce] = 2, op_table[0xcf] = 2, op_table[0x7b] = 2, 
    op_table[0x7c] = 2, op_table[0x7d] = 2, op_table[0x7e] = 2, op_table[0x7f] = 2, op_table[0x27] = 2, op_table[0x0a] = 2, op_table[0x0b] = 2, op_table[0x0c] = 2, 
    op_table[0x0d] = 2, op_table[0x0f] = 2, op_table[0x10] = 2, op_table[0x11] = 2, op_table[0x1d] = 2, op_table[0x1e] = 2, op_table[0x28] = 2, op_table[0x29] = 4, 
    op_table[0x08] = 4, op_table[0x02] = 4, op_table[0x05] = 4, op_table[0x38] = 4, op_table[0x39] = 4, op_table[0x3a] = 4, op_table[0x3b] = 4, op_table[0x3c] = 4, 
    op_table[0x3d] = 4, op_table[0x19] = 4, op_table[0x13] = 4, op_table[0x15] = 4, op_table[0x16] = 4, op_table[0x60] = 4, op_table[0x61] = 4, op_table[0x22] = 4, 
    op_table[0xff] = 4, op_table[0x62] = 4, op_table[0x63] = 4, op_table[0x64] = 4, op_table[0x65] = 4, op_table[0x66] = 4, op_table[0x67] = 4, op_table[0x68] = 4, 
    op_table[0x69] = 4, op_table[0x6a] = 4, op_table[0x6b] = 4, op_table[0x6c] = 4, op_table[0x6d] = 4, op_table[0x1a] = 4, op_table[0x1c] = 4, op_table[0xfe] = 4, 
    op_table[0x1f] = 4, op_table[0x90] = 4, op_table[0x91] = 4, op_table[0x92] = 4, op_table[0x93] = 4, op_table[0x94] = 4, op_table[0x95] = 4, op_table[0x96] = 4, 
    op_table[0x97] = 4, op_table[0x98] = 4, op_table[0x99] = 4, op_table[0x9a] = 4, op_table[0x9b] = 4, op_table[0x9c] = 4, op_table[0x9d] = 4, op_table[0x9e] = 4, 
    op_table[0x9f] = 4, op_table[0xa0] = 4, op_table[0xa1] = 4, op_table[0xa2] = 4, op_table[0xa3] = 4, op_table[0xa4] = 4, op_table[0xa5] = 4, op_table[0xa6] = 4, 
    op_table[0xa7] = 4, op_table[0xa8] = 4, op_table[0xa9] = 4, op_table[0xaa] = 4, op_table[0xab] = 4, op_table[0xac] = 4, op_table[0x2d] = 4, op_table[0x2e] = 4, 
    op_table[0x2f] = 4, op_table[0x30] = 4, op_table[0x31] = 4, op_table[0xad] = 4, op_table[0xae] = 4, op_table[0xaf] = 4, op_table[0x44] = 4, op_table[0x45] = 4, 
    op_table[0x46] = 4, op_table[0x47] = 4, op_table[0x48] = 4, op_table[0x49] = 4, op_table[0x4a] = 4, op_table[0x4b] = 4, op_table[0x4c] = 4, op_table[0x4d] = 4, 
    op_table[0x4e] = 4, op_table[0x4f] = 4, op_table[0x50] = 4, op_table[0x51] = 4, op_table[0xd8] = 4, op_table[0xd9] = 4, op_table[0xda] = 4, op_table[0xdb] = 4, 
    op_table[0xdc] = 4, op_table[0xdd] = 4, op_table[0xde] = 4, op_table[0xdf] = 4, op_table[0xe0] = 4, op_table[0xe1] = 4, op_table[0xe2] = 4, op_table[0x32] = 4, 
    op_table[0x33] = 4, op_table[0x34] = 4, op_table[0x35] = 4, op_table[0x36] = 4, op_table[0x37] = 4, op_table[0xd0] = 4, op_table[0xd1] = 4, op_table[0xd2] = 4, 
    op_table[0xd3] = 4, op_table[0xd4] = 4, op_table[0xd5] = 4, op_table[0xd6] = 4, op_table[0xd7] = 4, op_table[0x20] = 4, op_table[0x23] = 4, op_table[0x52] = 4, 
    op_table[0x53] = 4, op_table[0x54] = 4, op_table[0x55] = 4, op_table[0x56] = 4, op_table[0x57] = 4, op_table[0x58] = 4, op_table[0x59] = 4, op_table[0x5a] = 4, 
    op_table[0x5b] = 4, op_table[0x5c] = 4, op_table[0x5d] = 4, op_table[0x5e] = 4, op_table[0x5f] = 4, op_table[0x2a] = 6, op_table[0x09] = 6, op_table[0x03] = 6, 
    op_table[0x06] = 6, op_table[0x14] = 6, op_table[0x17] = 6, op_table[0x2b] = 6, op_table[0x2c] = 6, op_table[0x26] = 6, op_table[0x1b] = 6, op_table[0x24] = 6, 
    op_table[0x6e] = 6, op_table[0x6f] = 6, op_table[0x70] = 6, op_table[0x71] = 6, op_table[0x72] = 6, op_table[0xfc] = 6, op_table[0x25] = 6, op_table[0x74] = 6, 
    op_table[0x75] = 6, op_table[0x76] = 6, op_table[0x77] = 6, op_table[0x78] = 6, op_table[0xfd] = 6, op_table[0xfa] = 8, op_table[0xfb] = 8, op_table[0x18] = 10; 

    rcvt[0xE3] = 0x52, rcvt[0xE4] = 0x53, rcvt[0xE5] = 0x54, rcvt[0xE6] = 0x59, rcvt[0xE7] = 0x5A, rcvt[0xE8] = 0x5B, rcvt[0xE9] = 0x6E, rcvt[0xEA] = 0x74, rcvt[0xEB] = 0x5C,
    rcvt[0xEC] = 0x5D, rcvt[0xED] = 0x5E, rcvt[0xEE] = 0x5F, rcvt[0xEF] = 0x55, rcvt[0xF0] = 0x56, rcvt[0xF1] = 0x57, rcvt[0xF2] = 0x58, rcvt[0x73] = 0x0e;
    cvt[0x52] = 0xE3, cvt[0x53] = 0xE4, cvt[0x54] = 0xE5, cvt[0x59] = 0xE6, cvt[0x5A] = 0xE7, cvt[0x5B] = 0xE8, cvt[0x6E] = 0xE9, cvt[0x74] = 0xEA, cvt[0x5C] = 0xEB,
    cvt[0x5D] = 0xEC, cvt[0x5E] = 0xED, cvt[0x5F] = 0xEE, cvt[0x55] = 0xEF, cvt[0x56] = 0xF0, cvt[0x57] = 0xF1, cvt[0x58] = 0xF2, cvt[0x0e] = 0x73;
    
    return op_table;
}

void make_hash(vector<uint8_t> msg_vec, uint32_t msg_len, uint8_t* res, uint32_t* res_len)
{
    EVP_MD_CTX* ctx;
    //printf("hash -1\n");
    uint8_t* hmsg = (uint8_t*)malloc(sizeof(uint8_t)*msg_len);
    //printf("hash 0\n");
    for(int i=0; i<msg_len; i++){
        hmsg[i] = msg_vec[i];
    }
    //printf("hash 1\n");
    ctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, hmsg, msg_len);
    EVP_DigestFinal_ex(ctx, res, res_len);
    //printf("hash 2\n");
    EVP_MD_CTX_free(ctx);
    //printf("hash 3\n");
    free(hmsg);
}

void hash_print(uint8_t* msg, uint32_t msg_len, string name)
{
    printf("%02X", msg[0]);
    for(int i = 1; i < msg_len; ++i){
        printf(":%02X", msg[i]);
    }
    printf("\n");

    FILE* result = fopen(name.c_str(), "wb");
    for(int i = 0; i < msg_len; ++i){
        fwrite(msg+i, 1, 1, result);
    }
}
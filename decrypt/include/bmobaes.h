/**
* Encryption Standard Cipher
* create by zhou.2016-01-19
*/
#ifndef BMOBSDK_AES_H_
#define BMOBSDK_AES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>


using namespace std;

namespace bmobaes{

    typedef uint8_t state_t[4][4];
    // typedef uint8_t state_t[4][4];

    #ifndef MULTIPLY_AS_A_FUNCTION
    #define MULTIPLY_AS_A_FUNCTION 0
    #endif

    #if MULTIPLY_AS_A_FUNCTION
    static uint8_t Multiply(uint8_t x, uint8_t y)
    {
    return (((y & 1) * x) ^
       ((y>>1 & 1) * xtime(x)) ^
       ((y>>2 & 1) * xtime(xtime(x))) ^
       ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^
       ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))));
    }
    #else
    #define Multiply(x, y)                                \
        (  ((y & 1) * x) ^                              \
        ((y>>1 & 1) * xtime(x)) ^                       \
        ((y>>2 & 1) * xtime(xtime(x))) ^                \
        ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^         \
        ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))   \

    #endif

    class BmobAES{
    public:

        /**
        * 解密数据
        * @param in const unsigned char* 要解密的数据
        * @param key const unsigned char* 解密密钥
        * @param out char* 解密后数据存储
        */
        static void deaes(const unsigned char* in,int len,const unsigned char key[],char out[]);
        /**
        * 加密数据
        * @param in const unsigned char* 要加密的数据
        * @param key const unsigned char* 加密密钥
        * @param our char* 加密后的数据存储
        */
        static void enaes(const unsigned char* in,int len,const unsigned char key[],char out[]);



    private:
        static void AES128_CBC_encrypt_buffer(uint8_t* output, uint8_t* input, \
                              uint32_t length, const uint8_t* key, const uint8_t* iv);
        static void AES128_CBC_decrypt_buffer(uint8_t* output, uint8_t* input, \
                              uint32_t length, const uint8_t* key, const uint8_t* iv);

        /**
        * This function produces Nb(Nr+1) round keys.
        * The round keys are used in each round to decrypt the states.
        */
        static void KeyExpansion(void);

        /*
        * The ShiftRows() function shifts the rows in the state to the left.
        * Each row is shifted with different offset.
        * Offset = Row number. So the first row is not shifted.
        */
        static void ShiftRows(void);

        /**
        * MixColumns function mixes the columns of the state matrix
        */
        static void MixColumns(void);

        /**
        * Cipher is the main function that encrypts the PlainText.
        */
        static void Cipher(void);

        static void InvCipher(void);


        /**
        * MixColumns function mixes the columns of the state matrix.
        * The method used to multiply may be difficult to understand for the inexperienced.
        * Please use the references to gain more information.
        */
        static void InvMixColumns(void);

        static void InvShiftRows(void);

        inline static uint8_t getSBoxValue(uint8_t num){
            return sbox[num];
        }

        inline static uint8_t getSBoxInvert(uint8_t num){
            return rsbox[num];
        }


        /**
        * This function adds the round key to state.
        * The round key is added to the state by an XOR function.
        */
        static void AddRoundKey(uint8_t round){
            uint8_t i,j;
            for(i=0;i<4;++i)
            {
                for(j = 0; j < 4; ++j)
                {
                    (*state)[i][j] ^= RoundKey[round * Nb * 4 + i * Nb + j];
                }
            }
        }

        /**
        * The SubBytes Function Substitutes the values in the
        * state matrix with values in an S-box.
        */
        static void SubBytes(void){
            uint8_t i, j;
            for(i = 0; i < 4; ++i)
            {
                for(j = 0; j < 4; ++j)
                {
                    (*state)[j][i] = getSBoxValue((*state)[j][i]);
                }
            }
        }

        static uint8_t xtime(uint8_t x){
            return ((x<<1) ^ (((x>>7) & 1) * 0x1b));
        }

        /**
        * The SubBytes Function Substitutes the values in the
        * state matrix with values in an S-box.
        */
        static void InvSubBytes(void){
            uint8_t i,j;
            for(i=0;i<4;++i)
            {
                for(j=0;j<4;++j)
                {
                    (*state)[j][i] = getSBoxInvert((*state)[j][i]);
                }
            }
        }

        static void BlockCopy(uint8_t* output, uint8_t* input){
            uint8_t i;
            for (i=0;i<KEYLEN;++i)
            {
                output[i] = input[i];
            }
        }

        static void XorWithIv(uint8_t* buf){
            uint8_t i;
            for(i = 0; i < KEYLEN; ++i)
            {
                buf[i] ^= Iv[i];
            }
        }


    private:
        /*
        * Number of columns (32-bit words) comprising the State. For this
        * standard, Nb = 4.
        */
        static const int Nb = 4;

        /*
        * Number of 32-bit words comprising the Cipher Key. For this
        * standard, Nk = 4, 6, or 8.
        */
        static int Nk;

        /*
        * Number of rounds, which is a function of  Nk  and  Nb (which is
        * fixed). For this standard, Nr = 10, 12, or 14.
        */
        static int Nr;

        static int KEYLEN;

        /*
        * Inverse S-box transformation table
        */
        static  uint8_t rsbox[256];

        /*
        * S-box transformation table
        */
        static  uint8_t sbox[256];

        static  uint8_t Rcon[255];
        // static  uint8_t Rcon[10];


        static state_t* state;

        // The array that stores the round keys.
        static uint8_t RoundKey[176];

        // The Key input to the AES Program
        static  uint8_t* Key;

        static uint8_t* Iv;

    public:
        /**
        *
        */
        static string secretKey;
        /**
        *
        */
        static string key1;
        /**
        *
        */
        static string key2;
        /**
        *
        */
        static string key3;
    };

}

#endif

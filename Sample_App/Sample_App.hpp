
#include "../Globals.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdint>
#include <random>
#include <fstream>
#include <string.h>
#include "ZT.hpp"
#include "RandomRequestSource.hpp"
#include <openssl/ec.h>
#include <openssl/ecdh.h>
#include <openssl/ecdsa.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/obj_mac.h>

#define PRIME256V1_KEY_SIZE 32

static unsigned char hardcoded_verification_key_x[PRIME256V1_KEY_SIZE] = 
	{0x45, 0xb2, 0x00, 0x83, 0x53, 0x11, 0x4b, 0xbb,
	 0x78, 0xeb, 0x67, 0x17, 0xf2, 0xc9, 0x51, 0xe4,
	 0xcc, 0x1d, 0x93, 0x89, 0x0c, 0x70, 0xe1, 0x93,
	 0xcc, 0xd2, 0x83, 0x01, 0x68, 0x61, 0xe6, 0xec};

static unsigned char hardcoded_verification_key_y[PRIME256V1_KEY_SIZE] =
	{0xde, 0x24, 0xec, 0x0b, 0xf9, 0x0c, 0x03, 0x27,
	 0xb8, 0x1b, 0x89, 0x40, 0x80, 0x28, 0x54, 0xd8,
	 0xfb, 0xa5, 0xc8, 0x07, 0x57, 0x4c, 0x38, 0xab,
	 0xc3, 0x3e, 0xfb, 0x68, 0x42, 0xd1, 0xa5, 0xcf};

EC_KEY *ENCLAVE_PUBLIC_KEY = NULL;

unsigned char shared_aes_key[16];

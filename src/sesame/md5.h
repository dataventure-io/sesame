#ifndef _MD5
#define _MD5

#include <stdint.h>

typedef struct MD5_HASH_STRUCT
{
	// These vars will contain the hash
	uint32_t h0, h1, h2, h3;

} MD5_HASH;

void md5(MD5_HASH* msg_hash, uint8_t* initial_msg, size_t initial_len);

#endif
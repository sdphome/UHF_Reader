#ifndef __SM3_H
#define __SM3_H

#define  SM3_LBLOCK         16
#define  SM3_CBLOCK         64
#define  SM3_DIGEST_LENGTH  32
#define  SM3_LAST_BLOCK     56

typedef struct SM3state_st {
	unsigned long h[8];
	unsigned long Nl, Nh;
	unsigned long data[SM3_LBLOCK];
	unsigned int num;
} SM3_CTX;

void SM3_Init(SM3_CTX * ctx);
void SM3_Update(SM3_CTX * ctx, const void *data, unsigned int len);
void SM3_Final(unsigned char *md, SM3_CTX * ctx);

unsigned char *sm3(const unsigned char *d, unsigned int n, unsigned char *md);

#endif

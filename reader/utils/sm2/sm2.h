#ifndef __ALGSM2_H
#define __ALGSM2_H

#include "types.h"
#include "miracl.h"
#include "sm3.h"

int sm3_e(u_char *userid, int userid_len, u_char *xa, int xa_len, u_char *ya, int ya_len, u_char *msg, int msg_len, u_char *e);
/*
���ܣ������û�ID����Կ��������ǩ������ǩ����ϢHASHֵ
[����] userid�� �û�ID
[����] userid_len�� userid���ֽ���
[����] xa�� ��Կ��X����
[����] xa_len: xa���ֽ���
[����] ya�� ��Կ��Y����
[����] ya_len: ya���ֽ���
[����] msg��Ҫǩ������Ϣ
[����] msg_len�� msg���ֽ���
[���] e��32�ֽڣ�����ǩ������ǩ

����ֵ��
		��1���ڴ治��
		  0���ɹ�
*/

void sm2_keygen(unsigned char *wx,int *wxlen, unsigned char *wy,int *wylen,unsigned char *privkey, int *privkeylen);
/*
���ܣ�����SM2��˽Կ��
[���] wx��   ��Կ��X���꣬����32�ֽ���ǰ���0x00
[���] wxlen: wx���ֽ�����32
[���] wy��   ��Կ��Y���꣬����32�ֽ���ǰ���0x00
[���] wylen: wy���ֽ�����32
[���] privkey��˽Կ������32�ֽ���ǰ���0x00
[���] privkeylen�� privkey���ֽ�����32
*/

void sm2_sign(unsigned char *hash,int hashlen,unsigned char *privkey,int privkeylen,unsigned char *cr,int *rlen,unsigned char *cs,int *slen);
/*
���ܣ�SM2ǩ��
[����] hash��    sm3_e()�Ľ��
[����] hashlen�� hash���ֽ�����ӦΪ32
[����] privkey�� ˽Կ
[����] privkeylen�� privkeylen���ֽ���
 
[���] cr��  ǩ������ĵ�һ���֣�����32�ֽ���ǰ���0x00��
[���] rlen��cr���ֽ�����32
[���] cs��  ǩ������ĵڶ����֣�����32�ֽ���ǰ���0x00��
[���] slen��cs���ֽ�����32
*/

int  sm2_verify(unsigned char *hash,int hashlen,unsigned char  *cr,int rlen,unsigned char *cs,int slen, unsigned char *wx,int wxlen, unsigned char *wy,int wylen);
/*
���ܣ���֤SM2ǩ��
[����] hash��    sm3_e()�Ľ��
[����] hashlen�� hash���ֽ�����ӦΪ32
[����] cr��  ǩ������ĵ�һ����
[����] rlen��cr���ֽ���
[����] cs��  ǩ������ĵڶ����֡�
[����] slen��cs���ֽ���
[����] wx��   ��Կ��X����
[����] wxlen: wx���ֽ�����������32�ֽ�
[����] wy��   ��Կ��Y����
[����] wylen: wy���ֽ�����������32�ֽ�

����ֵ��
		0����֤ʧ��
		1����֤ͨ��
*/

int  sm2_encrypt(unsigned char *msg,int msglen, unsigned char *wx,int wxlen, unsigned char *wy,int wylen, unsigned char *outmsg);
/*
���ܣ���SM2��Կ�������ݡ����ܽ�����������ݶ�96�ֽڣ�
[����] msg     Ҫ���ܵ�����
[����] msglen��msg���ֽ���
[����] wx��    ��Կ��X����
[����] wxlen:  wx���ֽ�����������32�ֽ�
[����] wy��    ��Կ��Y����
[����] wylen:  wy���ֽ�����������32�ֽ�

[���] outmsg: ���ܽ�������������ݶ�96�ֽڣ���C1��64�ֽڣ���C3��32�ֽڣ�����ǰ��0x00

����ֵ��
		-1��        ����ʧ��
		msglen+96�� ���ܳɹ�
*/

int  sm2_decrypt(unsigned char *msg,int msglen, unsigned char *privkey, int privkeylen, unsigned char *outmsg);
/*
���ܣ���SM2˽Կ�������ݡ����ܽ��������������96�ֽڣ�
[����] msg     Ҫ���ܵ����ݣ���sm2_encrypt()���ܵĽ����������96�ֽڡ�
[����] msglen��msg���ֽ���
[����] privkey�� ˽Կ
[����] privkeylen�� privkeylen���ֽ���

[���] outmsg: ���ܽ����������������96�ֽڣ�

����ֵ��
		-1��        ����ʧ��
		msglen-96�� ���ܳɹ�
*/

void sm2_keyagreement_a1_3(unsigned char *kx1, int *kx1len, 
						   unsigned char *ky1, int *ky1len,
						   unsigned char *ra,  int *ralen
						   );

/*
���ܣ���ԿЭ�̵ķ��𷽵��ô˺�������һ����ʱ��Կ(kx1, ky1)����Ӧ�����������Կ���͸��Է��������ra�Լ����档
[���] kx1��   ��Կ��X���꣬����32�ֽ���ǰ���0x00
[���] kx1len��kx1���ֽ�����32
[���] ky1��   ��Կ��Y���꣬����32�ֽ���ǰ���0x00
[���] ky1len��ky1���ֽ�����32
[���] ra:     �����������32�ֽ���ǰ���0x00
[���] ralen�� ra���ֽ�����32

����ֵ����
	
*/

int sm2_keyagreement_b1_9( 
						  unsigned char *kx1, int kx1len,
						  unsigned char *ky1, int ky1len,
						  unsigned char *pax, int paxlen,
						  unsigned char *pay, int paylen,
						  unsigned char *private_b,   int private_b_len,
						  unsigned char *pbx, int pbxlen,
						  unsigned char *pby, int pbylen,
						  unsigned char *ida, int idalen,
						  unsigned char *idb, int idblen,
						  unsigned int  kblen,
						  unsigned char *kbbuf,
						  unsigned char *kx2, int *kx2len,
						  unsigned char *ky2, int *ky2len,
						  unsigned char *xv,  int *xvlen,
						  unsigned char *yv,  int *yvlen,
						  unsigned char *sb
						  );

/*

���ܣ���ԿЭ�̵Ľ��շ����ô˺���Э�̳���Կkbbuf��ͬʱ����һ����ʱ��Կ(kx2, ky2)�Լ�(xv, yv)��sb��(kx2, ky2)��sb���͸��Է���kbbuf��(xv, yv)�Լ����档
˵����
[����] (kx1, ky1)�Ƿ��𷽲�������ʱ��Կ
[����] (pax, pay)�Ƿ��𷽵Ĺ�Կ
[����] private_b�ǽ��շ���˽Կ
[����] (pbx, pby)�ǽ��շ��Ĺ�Կ
[����] ida�Ƿ��𷽵��û���ʶ
[����] idb�ǽ��շ����û���ʶ
[����] kblen��ҪԼ������Կ�ֽ���

[���] kbbuf��Э����Կ���������
[���] (kx2, ky2)�ǽ��շ���������ʱ��Կ������32�ֽ���ǰ���0x00
[���] (xv, yv)�ǽ��շ��������м������Լ����棬������֤Э�̵���ȷ�ԡ�������32�ֽ���ǰ���0x00�����(xv, yv)=NULL���������
[���] sb�ǽ��շ�������32�ֽڵ�HASHֵ��Ҫ���͸����𷽣�������֤Э�̵���ȷ�ԡ����Ϊsb=NULL���������


����ֵ��0��ʧ��  1���ɹ�
	
*/

int sm2_keyagreement_a4_10( 
						  unsigned char *kx1, int kx1len,
						  unsigned char *ky1, int ky1len,
						  unsigned char *pax, int paxlen,
						  unsigned char *pay, int paylen,
						  unsigned char *private_a,   int private_a_len,
						  unsigned char *pbx, int pbxlen,
						  unsigned char *pby, int pbylen,
						  unsigned char *ida, int idalen,
						  unsigned char *idb, int idblen,
						  unsigned char *kx2, int kx2len,
						  unsigned char *ky2, int ky2len,
						  unsigned char *ra,  int ralen,
						  unsigned int  kalen,
						  unsigned char *kabuf,
						  unsigned char *s1,
						  unsigned char *sa
						  );

/*

���ܣ���ԿЭ�̵ķ��𷽵��ô˺���Э�̳���Կkabuf��ͬʱ����s1��sa��s1��kabuf�Լ����棬sa���͸����շ�������ȷ��Э�̹��̵���ȷ�ԡ�
˵����
[����] (kx1, ky1)�Ƿ��𷽲�������ʱ��Կ
[����] (pax, pay)�Ƿ��𷽵Ĺ�Կ
[����] private_a�Ƿ��𷽵�˽Կ
[����] (pbx, pby)�ǽ��շ��Ĺ�Կ
[����] ida�Ƿ��𷽵��û���ʶ
[����] idb�ǽ��շ����û���ʶ
[����] (kx2, ky2)�ǽ��շ���������ʱ��Կ
[����] ra�Ƿ��𷽵���sm2_keyagreement_a1_3�����������
[����] kalen��ҪԼ������Կ�ֽ���

[���] kabuf��Э����Կ���������
[���] s1��sa�Ƿ��𷽲�����32�ֽڵ�HASHֵ��s1�Լ����棨Ӧ����sb����saҪ���͸����շ���������֤Э�̵���ȷ�ԡ����s1��saΪNULL���������


����ֵ��0��ʧ��  1���ɹ�
	
*/

void sm2_keyagreement_b10( 
						  unsigned char *pax, int paxlen,
						  unsigned char *pay, int paylen,
						  unsigned char *pbx, int pbxlen,
						  unsigned char *pby, int pbylen,
						  unsigned char *kx1, int kx1len,
						  unsigned char *ky1, int ky1len,
						  unsigned char *kx2, int kx2len,
						  unsigned char *ky2, int ky2len,
						  unsigned char *xv, int xvlen,
						  unsigned char *yv, int yvlen,
						  unsigned char *ida, int idalen,
						  unsigned char *idb, int idblen,
						  unsigned char *s2
						 );
/*

���ܣ���ԿЭ�̵Ľ��շ����ô˺�������s2��������֤Э�̹��̵���ȷ�ԡ�
˵����
[����] (pax, pay)�Ƿ��𷽵Ĺ�Կ
[����] (pbx, pby)�ǽ��շ��Ĺ�Կ
[����] (kx1, ky1)�Ƿ��𷽲�������ʱ��Կ
[����] (kx2, ky2)�ǽ��շ���������ʱ��Կ
[����] (xv, yv)�ǽ��շ��������м���
[����] ida�Ƿ��𷽵��û���ʶ
[����] idb�ǽ��շ����û���ʶ

[���] s2�ǽ��շ�������32�ֽڵ�HASHֵ��Ӧ����sa��


����ֵ����
*/
#endif

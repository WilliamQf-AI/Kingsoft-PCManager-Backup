#ifndef MAX_CRYPT_MES_LEN_16
#define MAX_CRYPT_MES_LEN_16 128
#endif

//Return length of M
int RSADecrypt(
			   char C[], //ʮ����
			   int nC, 
			   char E[],
			   char N[],
			   char *M //�ַ���
			   );
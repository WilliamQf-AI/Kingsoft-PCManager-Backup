#ifndef MAX_CRYPT_MES_LEN_16
#define MAX_CRYPT_MES_LEN_16 128
#endif

//Return length of C
int RSAEncrypt(
			   char M[], //�ַ��� 
			   size_t uM, 
			   char D[],
			   char N[],
			   char *C //ʮ����
				);

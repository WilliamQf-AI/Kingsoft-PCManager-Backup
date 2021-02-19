//#include "StdAfx.h"
#include "stdlib.h"
#include <string.h>
#include "RSAEncrypt.h"
extern "C"  
{
	#include "lip.h"
}

//Return length of C
int RSAEncrypt(
			   char M[],	//�ַ��� 
			   size_t uM, 
			   char D[],	//16�����ַ���
			   char N[],	//16�����ַ���
			   char *C		//16�����ַ���
)
{
	int nRet = 0;
	size_t i = 0;
	int nCLen = 0;
	char *pM16 = NULL;
	verylong vN = 0, vD = 0, vM = 0, vC = 0; //Freelip�еĴ�������Ϊverylong�� 

	if (uM > (MAX_CRYPT_MES_LEN_16/2))
		goto Exit0;

	pM16 = (char *)malloc((uM+1)<<1);
	if (pM16)
		memset(pM16, 0, (uM+1)<<1);
	
	for (i = 0; i<uM; i++)
	{
		itoa(M[i], &pM16[i<<1], 16);
	}
	
	zhsread(pM16, &vM); //��ʼ������M��M�����û�����ʮ�����Ʊ�ʾ
	zhsread(N, &vN); //��ʼ��ģ��N 
	zhsread(D, &vD); //��ʼ��˽ԿD 
	zexpmod(vM, vD, vN, &vC); //��������C = (M ^ D) mod N 
	nCLen = zhswrite(C, vC); //��C��16���ƴ���ʾд��C��
	nRet = 1;

Exit0:
	if (pM16)
	{
		free(pM16);
		pM16 = NULL;
	}

	return nRet>0?nCLen:-1;
}

#include "stdlib.h"
#include "RSAEncrypt.h"
extern "C"  
{
	#include "lip.h"
}

//Return length of M
int RSADecrypt(
			   char C[],	//16�����ַ���
			   int nC, 
			   char E[],	//16�����ַ���	
			   char N[],	//16�����ַ���
			   char *M		//�ַ���
			   )
{
	
	int nRet = 0;
	int i = 0;
	int nMLen = 0;
	char *pM16 = NULL;
	verylong vN = 0, vE = 0, vM = 0, vC = 0; //Freelip�еĴ�������Ϊverylong�� 
	char tmp[4] = {0};
	
	if (nC > MAX_CRYPT_MES_LEN_16)
		goto Exit0;

	pM16 = (char *)malloc(MAX_CRYPT_MES_LEN_16); //���RSA���ݿ�
	
	zhsread(C, &vC); 
	zhsread(N, &vN); //��ʼ��ģ��N 
	zhsread(E, &vE); //��ʼ��˽ԿD 
	zexpmod(vC, vE, vN, &vM); //��������C = (M ^ D) mod N 
	nMLen = zhswrite(pM16, vM); //��M��16���ƴ���ʾд��pm16��

	nRet = 1;
	for (i = 0; (i<(nMLen>>1))&&(nRet==1); i++)
	{
		tmp[0] = pM16[i<<1];
		tmp[1] = pM16[(i<<1) + 1];
		nRet = sscanf(tmp, "%2x", &M[i]);
	}

	M[i] = '\x0';
	
Exit0:
	if (pM16)
	{
		free(pM16);
		pM16 = NULL;
	}
	

	return nRet>0?nMLen>>1:-1;
}
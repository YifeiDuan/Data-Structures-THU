#include<stdio.h>
#include<string.h>
#define L 17000000

long long int result; //��� 
char read[L] , str[2*L + 1]; //read���ڶ��룬str���ڼ�¼manacher�㷨���봦���Ľ�� 
int p[2*L + 1]; //��¼strÿ��Ԫ�ص������İ뾶 

int main()
{	
	scanf("%s" , read);
	
	str[0] = '$'; //str�����Ԫ�� 
	int i;
	for(i = 0 ; i < strlen(read) ; i ++) //���빹��manacher������ 
	{
		str[2*i + 1] = '#';
		str[2*i + 2] = read[i];
	}
	str[2*strlen(read) + 1] = '#';
	str[2*strlen(read) + 2] = '\0'; //���βԪ�� 
	
	int pos = 1, mx = 1; //mx���ڼ�¼��ǰ���ҵ��Ļ����������쵽����ĩ��posΪ��������� 
    result = 0;
    int len = strlen(str);
    for(i = 1 ; i <= len ; i ++) //����manacher�㷨������str��ÿ��Ԫ�أ�str[0]���⣩ȷ���������İ뾶 
	{
        if (i <= mx) //�����ǰ��iû�г�����ǰ��mx�����ǵķ�Χ���������֪�ĶԳ���ȡmin��p[2*pos - i] �� mx - i�� Ϊp[i]����ֵ 
		{
			if(p[2*pos - i] < mx - i) p[i] = p[2*pos - i];
            else p[i] = mx - i;
        }
        else p[i] = 0; //���������Ϊ0��iλ�õ�Ԫ������������İ뾶�� 
        while (str[i + p[i] + 1] == str[i - p[i] - 1]) p[i] ++; //��mx����չѰ�ң�������β�������ǣ�������ÿ���Խ�� 
        if (p[i] + i > mx) //����µ������İ뾶ĩ�˳���mx�������mx��pos 
		{
            mx = p[i] + i;
            pos = i;
        }
        
    }
    for(i = 2 ; i < len ; i ++)
	{
		int numi = (p[i]/2) + (p[i]%2) ; //�������İ뾶�۰�����ȡ���õ��Ը�λ��Ϊ���ĵĻ����� 
        result += (long long int)numi;
	} 
    
    printf("%lld" , result);

	
	return 0;
}

#include<stdio.h>
#include<string.h>
#define L 17000000

using namespace std;
int main()
{
	char *read = new char[L];
	char *str = new char[2*L+1];
	int *p = new int[2*L + 1];
	
	scanf("%s" , read);
	
	str[0] = '$';
	int i;
	for(i = 0 ; i < strlen(read) ; i ++)
	{
		str[2*i + 1] = '#';
		str[2*i + 2] = read[i];
	}
	str[2*strlen(read) + 1] = '#';
	str[2*strlen(read) + 2] = '\0';
	
	int pos = 1, mx = 1;
    int len = strlen(str);
    long long int result = 0;
    for(i = 1 ; i <= len ; i ++)
	{
        if (i < mx)
		{
			if(p[2*pos - i] < mx - i) p[i] = p[2*pos - i];
            else p[i] = mx - i;
        }
        else p[i] = 1;
        //while ((i + p[i] + 1 < len) && (i - p[i] - 1 > 0) && (str[i + p[i] + 1] == str[i - p[i] - 1])) p[i] ++;
        while (str[i + p[i]] == str[i - p[i]]) p[i] ++;
        if (p[i] + i > mx)
		{
            mx = p[i] + i;
            pos = i;
        }
        
        int numi;
        if(p[i] % 2 == 1) numi = (p[i] - 1)/2 ;
        else numi = p[i]/2 ;
        result += (long long int)numi;
    }
    
    printf("%lld" , result);

	
	return 0;
}

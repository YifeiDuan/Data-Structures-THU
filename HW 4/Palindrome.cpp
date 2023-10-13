#include<stdio.h>
#include<string.h>
#define L 17000000

long long int result; //结果 
char read[L] , str[2*L + 1]; //read用于读入，str用于记录manacher算法插入处理后的结果 
int p[2*L + 1]; //记录str每个元素的最大回文半径 

int main()
{	
	scanf("%s" , read);
	
	str[0] = '$'; //str标记首元素 
	int i;
	for(i = 0 ; i < strlen(read) ; i ++) //插入构成manacher的序列 
	{
		str[2*i + 1] = '#';
		str[2*i + 2] = read[i];
	}
	str[2*strlen(read) + 1] = '#';
	str[2*strlen(read) + 2] = '\0'; //标记尾元素 
	
	int pos = 1, mx = 1; //mx用于记录此前所找到的回文序列延伸到的最末，pos为其回文中心 
    result = 0;
    int len = strlen(str);
    for(i = 1 ; i <= len ; i ++) //利用manacher算法，对于str中每个元素（str[0]除外）确定其最大回文半径 
	{
        if (i <= mx) //如果当前的i没有超出此前的mx所覆盖的范围，则根据已知的对称性取min（p[2*pos - i] ， mx - i） 为p[i]起算值 
		{
			if(p[2*pos - i] < mx - i) p[i] = p[2*pos - i];
            else p[i] = mx - i;
        }
        else p[i] = 0; //否则起算点为0（i位置的元素自身不算入回文半径） 
        while (str[i + p[i] + 1] == str[i - p[i] - 1]) p[i] ++; //向mx后拓展寻找，由于首尾有特殊标记，因而不用考虑越界 
        if (p[i] + i > mx) //如果新的最大回文半径末端超出mx，则更新mx和pos 
		{
            mx = p[i] + i;
            pos = i;
        }
        
    }
    for(i = 2 ; i < len ; i ++)
	{
		int numi = (p[i]/2) + (p[i]%2) ; //对最大回文半径折半向上取整得到以该位置为中心的回文数 
        result += (long long int)numi;
	} 
    
    printf("%lld" , result);

	
	return 0;
}

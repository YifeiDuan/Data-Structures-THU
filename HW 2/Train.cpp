#include<stdio.h>
#include<string.h>
int numB , numS , numOps; //分别记录b、s栈以及ops数组当中的元素个数 
void operateA(int ai , int m , int *s , int *b , char *ops , int *obs); //在a上进行操作，参数包括操作对象在a中的角标ai、S容量m、栈s、b，操作记录ops、操作对象记录obs 
void operateS(int *s , int *b , char *ops , int *obs); //在s上进行操作，参数包括s、b、ops、obs 
int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	int *a = new int[n + 1] ;
	int *b = new int[n + 1] ;
	int *s = new int[n + 1] ;
	char *ops = new char[2*n + 1]; //每个车厢要么直接P，要么一次I一次O，要么I后无法O，操作总数最多2n+1 
	int *obs = new int[2*n + 1];
	int i , j;
	for(i = 1 ; i <= n ; i ++) scanf("%d" , &a[i]); //录入a上的排序 
	for(i = 0 ; i <= 2*n ; i ++) ops[i] = ' '; //char数组赋初值 
	
	numB = 0;
	numS = 0;
	numOps = 0; //三个记录数量的变量赋初值0 
	b[0] = 0; //车厢进b的一个必要条件是b中此前的最后一节编号小于新车厢编号，故b[0]赋为0 
	s[0] = 100001; //车厢进s的必要条件反之，故给s[0]赋一个比n上限更大的数 
	
	int tempS , tempB;
	for(i = 1 ; i <= n ; i ++) //以a中初始车厢总量为限模拟操作过程，每次对a顶车厢操作之前先对s操作使s中可以出栈入b的都被执行操作 
	{
		tempS = numS;
		tempB = numB;
		for(j = 1 ; (j <= tempS) && (tempB > 0)  ; j ++) //若b中不为空，遍历s中每一节车厢 
		{
			if(b[numB] < s[numS] - 1) break; //若位于s顶的车厢不能与b顶的车厢接上，则跳出循环遍历 
			else operateS(s , b , ops , obs); //否则操作s队列，使s顶车厢进入b 
		}
		
		operateA(a[i] , m , s , b , ops , obs); //处理完s后，操作a顶车厢 
		
		if(ops[1] == 'N') break; //每次操作a后判断ops[1]是否因驶入序列不可行而被标记 
		else continue;
	}
	tempS = numS;
	tempB = numB;
	for(j = 1 ; (j <= tempS) && (tempB > 0)  ; j ++) //在a中最后一节车厢出a后，仍要再遍历操作一次s 
	{
		if(b[numB] < s[numS] - 1) break;
		else operateS(s , b , ops , obs);
	}
	
	if(ops[1] == 'N') printf("No"); //ops[1]被标记则输出No 
	else
	{
		for(i = 1 ; i <= numOps - 1 ; i ++) //否则遍历操作对象和操作类型记录并输出 
	    {
		    printf("%d %c\n" , obs[i] , ops[i]);
	    }
	    printf("%d %c" , obs[numOps] , ops[numOps]);
	}
	
}
void operateS(int *s , int *b , char *ops , int *obs)
{
	numB ++;
	b[numB] = s[numS]; //s顶车厢进入b 
	numS --;
	numOps ++;
	ops[numOps] = 'O'; //记录操作类型O 
	obs[numOps] = b[numB]; //记录操作对象 
}
void operateA(int ai , int m , int *s , int *b , char *ops , int *obs)
{
	if (b[numB] == ai - 1) //如果b顶车厢编号恰好比a顶车厢小1，则可直接通过，进入b 
	{
		numB ++;
		b[numB] = ai;
		numOps ++;
		ops[numOps] = 'P';
		obs[numOps] = ai;
	}
	else //否则就考虑是否能进s 
	{
		if(numS == m) ops[1] = 'N'; //如果s已满，则说明输入的驶入序列不可行 
		else
		{
			if(s[numS] < ai) ops[1] = 'N'; //如果s顶车厢编号更小则a顶无法入s，也说明输入的驶入序列不可行 
			else //否则a顶车厢进入s 
			{
				numS ++;
				s[numS] = ai;
				numOps ++;
				ops[numOps] = 'I';
				obs[numOps] = ai;
			}
		}
	}
}


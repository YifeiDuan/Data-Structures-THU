#include<stdio.h>
#include<string.h>
int numB , numS , numOps; //�ֱ��¼b��sջ�Լ�ops���鵱�е�Ԫ�ظ��� 
void operateA(int ai , int m , int *s , int *b , char *ops , int *obs); //��a�Ͻ��в�����������������������a�еĽǱ�ai��S����m��ջs��b��������¼ops�����������¼obs 
void operateS(int *s , int *b , char *ops , int *obs); //��s�Ͻ��в�������������s��b��ops��obs 
int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	int *a = new int[n + 1] ;
	int *b = new int[n + 1] ;
	int *s = new int[n + 1] ;
	char *ops = new char[2*n + 1]; //ÿ������Ҫôֱ��P��Ҫôһ��Iһ��O��ҪôI���޷�O�������������2n+1 
	int *obs = new int[2*n + 1];
	int i , j;
	for(i = 1 ; i <= n ; i ++) scanf("%d" , &a[i]); //¼��a�ϵ����� 
	for(i = 0 ; i <= 2*n ; i ++) ops[i] = ' '; //char���鸳��ֵ 
	
	numB = 0;
	numS = 0;
	numOps = 0; //������¼�����ı�������ֵ0 
	b[0] = 0; //�����b��һ����Ҫ������b�д�ǰ�����һ�ڱ��С���³����ţ���b[0]��Ϊ0 
	s[0] = 100001; //�����s�ı�Ҫ������֮���ʸ�s[0]��һ����n���޸������ 
	
	int tempS , tempB;
	for(i = 1 ; i <= n ; i ++) //��a�г�ʼ��������Ϊ��ģ��������̣�ÿ�ζ�a���������֮ǰ�ȶ�s����ʹs�п��Գ�ջ��b�Ķ���ִ�в��� 
	{
		tempS = numS;
		tempB = numB;
		for(j = 1 ; (j <= tempS) && (tempB > 0)  ; j ++) //��b�в�Ϊ�գ�����s��ÿһ�ڳ��� 
		{
			if(b[numB] < s[numS] - 1) break; //��λ��s���ĳ��᲻����b���ĳ�����ϣ�������ѭ������ 
			else operateS(s , b , ops , obs); //�������s���У�ʹs���������b 
		}
		
		operateA(a[i] , m , s , b , ops , obs); //������s�󣬲���a������ 
		
		if(ops[1] == 'N') break; //ÿ�β���a���ж�ops[1]�Ƿ���ʻ�����в����ж������ 
		else continue;
	}
	tempS = numS;
	tempB = numB;
	for(j = 1 ; (j <= tempS) && (tempB > 0)  ; j ++) //��a�����һ�ڳ����a����Ҫ�ٱ�������һ��s 
	{
		if(b[numB] < s[numS] - 1) break;
		else operateS(s , b , ops , obs);
	}
	
	if(ops[1] == 'N') printf("No"); //ops[1]����������No 
	else
	{
		for(i = 1 ; i <= numOps - 1 ; i ++) //���������������Ͳ������ͼ�¼����� 
	    {
		    printf("%d %c\n" , obs[i] , ops[i]);
	    }
	    printf("%d %c" , obs[numOps] , ops[numOps]);
	}
	
}
void operateS(int *s , int *b , char *ops , int *obs)
{
	numB ++;
	b[numB] = s[numS]; //s���������b 
	numS --;
	numOps ++;
	ops[numOps] = 'O'; //��¼��������O 
	obs[numOps] = b[numB]; //��¼�������� 
}
void operateA(int ai , int m , int *s , int *b , char *ops , int *obs)
{
	if (b[numB] == ai - 1) //���b��������ǡ�ñ�a������С1�����ֱ��ͨ��������b 
	{
		numB ++;
		b[numB] = ai;
		numOps ++;
		ops[numOps] = 'P';
		obs[numOps] = ai;
	}
	else //����Ϳ����Ƿ��ܽ�s 
	{
		if(numS == m) ops[1] = 'N'; //���s��������˵�������ʻ�����в����� 
		else
		{
			if(s[numS] < ai) ops[1] = 'N'; //���s�������Ÿ�С��a���޷���s��Ҳ˵�������ʻ�����в����� 
			else //����a���������s 
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


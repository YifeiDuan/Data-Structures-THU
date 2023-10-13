#include<stdio.h>
#include<string.h>
int staff[10000002] , line[10000002];
int num , linetag , ctag;
long long int result;
void LogIn(int id , int code);
void LogOut(int id);
void Close();
void Number();
void Query(int id);
int main()
{
	num = 0;
	linetag = 0;
	ctag = 0;
	result = 0;
	memset(staff , -1 , 10000002);
	memset(line , 0 , 10000002)	;
	
	int n , m , i;
	scanf("%d %d\r\n" , &n , &m);
	
	char op;
	int id , code;
	for(i = 1 ; i <= m - 1; i++)
	{
		scanf("%c" , &op);
		switch(op)
		{
			case'I':
				scanf("%d %d\r\n" , &id , &code);
				LogIn(id , code);
				break;
			case'O':
				scanf("%d\r\n" , &id);
				LogOut(id);
				break;
			case'C':
				scanf("\r\n");
				Close();
				break;
			case'N':
				scanf("\r\n");
				Number();
				break;
			case'Q':
				scanf("%d\r\n" , &id);
				Query(id);
				break;
		}
	}
	scanf("%c" , &op);
	switch(op)
	{
		case'I':
				scanf("%d %d" , &id , &code);
				LogIn(id , code);
				break;
		case'O':
				scanf("%d" , &id);
				LogOut(id);
				break;
		case'C':
				Close();
				break;
		case'N':
				Number();
				break;
		case'Q':
				scanf("%d" , &id);
				Query(id);
				break;
	}
		
	printf("%lld" , result);
}
void LogIn(int id , int code)
{
	linetag ++;
	
	if((line[id] < ctag)||(line[id] == 0))
	{
		line[id] = linetag;
		staff[id] = code;
	    num ++;
	}
	else
	{
		line[id] = linetag;
		staff[id] = code;
	 } 
}
void LogOut(int id)
{
	linetag ++;
	int i , tag;
	if(line[id] > ctag)
	{
		staff[id] = -1;
		line[id] = 0;
	    num --;
	}
	else line[id] = 0;
}
void Close()
{
	linetag ++;
	ctag = linetag;
	num = 0;
}
void Number()
{
	linetag ++;
	result += (long long int) num;
}
void Query(int id)
{
	linetag ++;
	if(line[id] < ctag) result -= 1;
	else result += (long long int) staff[id];
}

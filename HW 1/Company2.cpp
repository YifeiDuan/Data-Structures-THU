#include<stdio.h>
#include<string.h>
long long int staff[10000001];
int mark[1000001];
int rank[10000001];
long long int num ;
long long int result;
void LogIn(int id , long long int code);
void LogOut(int id);
void Close();
void Number();
void Query(int id);
int main()
{
	num = 0;
	result = 0;
	memset(staff , -1 , 10000001);
	memset(mark , 0 , 1000001);
	memset(rank , 0 , 10000001);
	
	int n , m , i;
	scanf("%d %d\n" , &n , &m);
	
	char op;
	int id ;
	long long int code;
	for(i = 1 ; i <= m - 1; i++)
	{
		scanf("%c" , &op);
		switch(op)
		{
			case'I':
				scanf("%d %lld\n" , &id , &code);
				LogIn(id , code);
				break;
			case'O':
				scanf("%d\n" , &id);
				LogOut(id);
				break;
			case'C':
				scanf("\n");
				Close();
				break;
			case'N':
				scanf("\n");
				Number();
				break;
			case'Q':
				scanf("%d\n" , &id);
				Query(id);
				break;
		}
	}
	scanf("%c" , &op);
	switch(op)
	{
		case'I':
				scanf("%d %lld" , &id , &code);
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
void LogIn(int id , long long int code)
{
	if(staff[id] == -1)
	{
		staff[id] = code;
	    num ++;
	    mark[num] = id;
	    rank[id] = num;
	    
	}
	else staff[id] = code;
}
void LogOut(int id)
{
	int i;
	if(staff[id] != -1)
	{
		staff[id] = -1;
		for(i = rank[id] ; i <= num - 1 ; i ++)
		{
			rank[mark[i]] --;
			mark[i] = mark[i + 1];
		}
		rank[id] = 0;
		mark[num] = 0;
	    num --;
	}
	else num += 0;
}
void Close()
{
	int i;
	for(i = 1 ; i <= num ; i ++)
	{
		staff[mark[i]] = -1;
		mark[i] = 0;
	}
	num = 0;
}
void Number()
{
	result +=  num;
}
void Query(int id)
{
	result +=  staff[id];
}

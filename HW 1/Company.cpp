#include<stdio.h>
#include<string.h>
int staff[10000005] , mark[1000005];//staff数组用于记录每个员工的code，mark数组用于标记哪些员工处于登陆状态（元素个数小于等于m最大可能值） 
int num ;//用于记录登陆人数 
long long int result;//随时更新Q,N计算结果之和 
void LogIn(int id , int code);
void LogOut(int id);
void Close();
void Number();
void Query(int id);
//每个操作类型设计一个void函数实现相应操作 
int main()
{
	num = 0;
	result = 0;
	memset(staff , -1 , 10000005);
	memset(mark , 0 , 1000005)	;
	
	int n , m , i;
	scanf("%d %d\r\n" , &n , &m);
	
	char op;
	int id , code;
	for(i = 1 ; i <= m - 1; i++)//用循环语句来输入前m-1次操作的信息 
	{
		scanf("%c" , &op);
		switch(op)//识别每行输入的第一个字符后用switch语句进入后续不同操作 
		{
			case'I':
				scanf("%d %d\r\n" , &id , &code);//对I、O、Q操作要先输入参数后再换行 
				LogIn(id , code);
				break;
			case'O':
				scanf("%d\r\n" , &id);
				LogOut(id);
				break;
			case'C':
				scanf("\r\n");//对C、N操作直接换行 
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
	scanf("%c" , &op);//最后一次输入 
	switch(op)//与上面不同的是switch读取后不再换行
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
		
	printf("%lld" , result);//输出结果 
}
void LogIn(int id , int code)//I操作，传员工编号和code 
{
	if(staff[id] == -1) 
	{
		staff[id] = code;
	    num ++;
	    mark[num] = id;
	}//如果不是登陆状态，则登入code，同时mark该员工 
	else staff[id] = code;//如果已经登陆则更新code 
}
void LogOut(int id)//O操作，传员工编号 
{
	int i , tag;
	if(staff[id] != -1)//如果该员工处于登陆状态 
	{
		staff[id] = -1;//则登出 
		for(i = 1 ; i <= num ; i ++)
		{
			if(mark[i] == id) 
			{
				tag = i;
				break;
			}
			else num += 0;
		}//并在mark中找到该员工 
		for(i = tag ; i <= num - 1 ; i ++)
		{
			mark[i] = mark[i + 1];
		}//将mark中排在该员工后面的员工顺次前移一位 
		mark[num] = 0; //mark的人数减少一名 
	    num --;//登陆人数减少一名 
	}
	else num += 0;//如果不该员工处于登陆状态则无改变 
}
void Close()//C操作无参数 
{
	int i;
	for(i = 1 ; i <= num ; i ++)
	{
		staff[mark[i]] = -1;
		mark[i] = 0;
	}//用num次循环通过mark找到登入状态的员工并将之逐一登出，mark清零 
	num = 0;//登入总人数清零 
}
void Number()//N操作无参数 
{
	result += (long long int) num;//结果加上此刻登陆态人数 
}
void Query(int id)//Q操作,传员工编号 
{
	result += (long long int) staff[id];//结果加上该员工此时的code 
}

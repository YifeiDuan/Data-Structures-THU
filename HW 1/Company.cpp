#include<stdio.h>
#include<string.h>
int staff[10000005] , mark[1000005];//staff�������ڼ�¼ÿ��Ա����code��mark�������ڱ����ЩԱ�����ڵ�½״̬��Ԫ�ظ���С�ڵ���m������ֵ�� 
int num ;//���ڼ�¼��½���� 
long long int result;//��ʱ����Q,N������֮�� 
void LogIn(int id , int code);
void LogOut(int id);
void Close();
void Number();
void Query(int id);
//ÿ�������������һ��void����ʵ����Ӧ���� 
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
	for(i = 1 ; i <= m - 1; i++)//��ѭ�����������ǰm-1�β�������Ϣ 
	{
		scanf("%c" , &op);
		switch(op)//ʶ��ÿ������ĵ�һ���ַ�����switch�����������ͬ���� 
		{
			case'I':
				scanf("%d %d\r\n" , &id , &code);//��I��O��Q����Ҫ������������ٻ��� 
				LogIn(id , code);
				break;
			case'O':
				scanf("%d\r\n" , &id);
				LogOut(id);
				break;
			case'C':
				scanf("\r\n");//��C��N����ֱ�ӻ��� 
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
	scanf("%c" , &op);//���һ������ 
	switch(op)//�����治ͬ����switch��ȡ���ٻ���
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
		
	printf("%lld" , result);//������ 
}
void LogIn(int id , int code)//I��������Ա����ź�code 
{
	if(staff[id] == -1) 
	{
		staff[id] = code;
	    num ++;
	    mark[num] = id;
	}//������ǵ�½״̬�������code��ͬʱmark��Ա�� 
	else staff[id] = code;//����Ѿ���½�����code 
}
void LogOut(int id)//O��������Ա����� 
{
	int i , tag;
	if(staff[id] != -1)//�����Ա�����ڵ�½״̬ 
	{
		staff[id] = -1;//��ǳ� 
		for(i = 1 ; i <= num ; i ++)
		{
			if(mark[i] == id) 
			{
				tag = i;
				break;
			}
			else num += 0;
		}//����mark���ҵ���Ա�� 
		for(i = tag ; i <= num - 1 ; i ++)
		{
			mark[i] = mark[i + 1];
		}//��mark�����ڸ�Ա�������Ա��˳��ǰ��һλ 
		mark[num] = 0; //mark����������һ�� 
	    num --;//��½��������һ�� 
	}
	else num += 0;//�������Ա�����ڵ�½״̬���޸ı� 
}
void Close()//C�����޲��� 
{
	int i;
	for(i = 1 ; i <= num ; i ++)
	{
		staff[mark[i]] = -1;
		mark[i] = 0;
	}//��num��ѭ��ͨ��mark�ҵ�����״̬��Ա������֮��һ�ǳ���mark���� 
	num = 0;//�������������� 
}
void Number()//N�����޲��� 
{
	result += (long long int) num;//������ϴ˿̵�½̬���� 
}
void Query(int id)//Q����,��Ա����� 
{
	result += (long long int) staff[id];//������ϸ�Ա����ʱ��code 
}

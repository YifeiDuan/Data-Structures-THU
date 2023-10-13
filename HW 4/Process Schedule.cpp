#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct pro //�ṹ��洢����������Ϣ 
{
	int ID; //���̺� 
	int P; //���ȼ� 
	int CT; //����ʱ�� 
	int ET; //ִ��ʱ�� 
	int RET; //��ִ��ʱ��	
} ;
struct pro list[1000001]; //���н��̵��б� 
struct pro PQ[1000001]; //��ǰ�Ѿ���������δ������ϵĽ��̣�Ҫ�ų���ȫ����� 

void Add(int q); //�������� 
void delMax(int q); //ɾ������� 
int comp(int a , int b , int c); //�����бȽϸ��������� 

int main()
{
	int N;
	scanf("%d\n" , &N);
	
	int i;
	for(i = 1 ; i <= N ; i ++) //¼��ȫ��������Ϣ 
	{
		if(i == N) scanf("%d %d %d %d" , &list[i].ID , &list[i].P , &list[i].CT , &list[i].ET);
		else scanf("%d %d %d %d\n" , &list[i].ID , &list[i].P , &list[i].CT , &list[i].ET);
		list[i].RET = 0;
		PQ[0].RET = 0;
	}
	
	int t = 0, num = 0; //t��������ʱ�� ��num���Ѿ������Ľ����� 
	int p = 1 , q = 0; //p��list����δ�����ĵ�һ��������list�е��ȣ�q���Ѿ���������δ��ɵĽ������� 
	while(1) //ģ�����й��̣�ÿ����1���ӡ�ѭ��һ�� 
	{
		t ++; //����1���� 
		
		if(num > 0)
		{
			PQ[0].RET ++; //����ִ�еĽ��̣�����ִ��ʱ��+1 		
		    if(PQ[0].RET == PQ[0].ET) //����ý���ִ����� 
		    {
			    i = PQ[0].ID;
			    delMax(q);
			    q --;
			    printf("%d %d\n" , i , t);
		    }
		} 
		
		for(p = num + 1 ; list[p].CT == t ; p ++) 
		{
			PQ[q] = list[p];
		    q ++;		
		} //���ڴ���ʱ��Ϊ��ʱ�̵Ľ��̣����δ��� 
		
		if(p-1 > num) //���p�к��� 
		{
			num = p-1; //����num
			Add(q); //���Ѵ����Ľ����ų���ȫ����� 
			
			printf("%d\n" , PQ[0].ID);
		}
		
		if((q < 0)&&(num == N)) break;
	}
	
	return 0;
}

int comp(int a , int b , int c)
{
	int m;
	m = b;
	if(PQ[b].P < PQ[c].P) m = c;
	if(PQ[b].P == PQ[c].P)
	{
		if(PQ[b].CT > PQ[c].CT) m = c;
		if(PQ[b].CT == PQ[c].CT)
		{
			if(PQ[b].ID > PQ[c].ID) m = c;
		}
	}
	
	if(PQ[a].P < PQ[m].P) return m -(2*a);
	else if(PQ[a].P == PQ[m].P)
	{
		if(PQ[a].CT > PQ[m].CT) return m -(2*a);
		if(PQ[a].CT == PQ[m].CT)
		{
			if(PQ[a].ID > PQ[m].ID) return m -(2*a);
		}
	}
	
	return 0;
}

void Add(int q)
{
	int inner = (q-1)/2 - 1;
	int i;
	struct pro temp;
	if(q == 1) return;
	if(q == 2)
	{
		int pd = 0;
		if(PQ[0].P < PQ[1].P) pd = 1;
	    if(PQ[0].P == PQ[1].P)
	    {
		    if(PQ[0].CT > PQ[1].CT) pd = 1;
		    if(PQ[0].CT == PQ[1].CT)
		    {
			    if(PQ[0].ID > PQ[1].ID) pd = 1;
		    }
	    }
	    
	    if(pd == 1)
	    {
	    	temp = PQ[0];
		    PQ[0] = PQ[1];
		    PQ[1] = temp;
		}
		return;
	}
	for(i = inner ; i >= 0 ; i --)
	{
		switch(comp(i , 2*i+1 , 2*(i+1)))
		{
			case 0:
				break;
				
			case 1:
				temp = PQ[i];
				PQ[i] = PQ[2*i+1];
				PQ[2*i+1] = temp;
				break;
			
			case 2:
				temp = PQ[i];
				PQ[i] = PQ[2*(i+1)];
				PQ[2*(i+1)] = temp;
				break;			   			    	
		}
	}
}

void delMax(int q)
{
	PQ[0] = PQ[q-1];
	if(q < 3) return;
	
	int pd = 0;
	struct pro temp;
	if(q == 3)
	{
		if(PQ[0].P < PQ[1].P) pd = 1;
	    if(PQ[0].P == PQ[1].P)
	    {
		    if(PQ[0].CT > PQ[1].CT) pd = 1;
		    if(PQ[0].CT == PQ[1].CT)
		    {
			    if(PQ[0].ID > PQ[1].ID) pd = 1;
		    }
	    }
	    
	    if(pd == 1)
	    {
	    	temp = PQ[0];
		    PQ[0] = PQ[1];
		    PQ[1] = temp;
		}
		return;
	}
		
	int i = 0;
	while(i <= (q-1)/2 - 1)
	{
		switch(comp(i , 2*i+1 , 2*(i+1)))
		{
			case 0:
				pd = 1;
				break;
				
			case 1:
				temp = PQ[i];
				PQ[i] = PQ[2*i+1];
				PQ[2*i+1] = temp;
				i = 2*i+1;
				break;
			
			case 2:
				temp = PQ[i];
				PQ[i] = PQ[2*(i+1)];
				PQ[2*(i+1)] = temp;
				i = 2*(i+1);
				break;			   			    	
		}
		if(pd == 1) break;
	}
	return;
}


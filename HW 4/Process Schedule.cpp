#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct pro //结构体存储单个进程信息 
{
	int ID; //进程号 
	int P; //优先级 
	int CT; //创建时间 
	int ET; //执行时间 
	int RET; //已执行时间	
} ;
struct pro list[1000001]; //所有进程的列表 
struct pro PQ[1000001]; //当前已经创建且尚未运行完毕的进程，要排成完全二叉堆 

void Add(int q); //批量建立 
void delMax(int q); //删除最大者 
int comp(int a , int b , int c); //下滤中比较父亲与两子 

int main()
{
	int N;
	scanf("%d\n" , &N);
	
	int i;
	for(i = 1 ; i <= N ; i ++) //录入全部进程信息 
	{
		if(i == N) scanf("%d %d %d %d" , &list[i].ID , &list[i].P , &list[i].CT , &list[i].ET);
		else scanf("%d %d %d %d\n" , &list[i].ID , &list[i].P , &list[i].CT , &list[i].ET);
		list[i].RET = 0;
		PQ[0].RET = 0;
	}
	
	int t = 0, num = 0; //t是运行总时间 ，num是已经创建的进程数 
	int p = 1 , q = 0; //p是list中尚未创建的第一个进程在list中的秩，q是已经创建而尚未完成的进程数量 
	while(1) //模拟运行过程，每“过1分钟”循环一次 
	{
		t ++; //过了1分钟 
		
		if(num > 0)
		{
			PQ[0].RET ++; //正在执行的进程，其已执行时间+1 		
		    if(PQ[0].RET == PQ[0].ET) //如果该进程执行完毕 
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
		} //对于创建时间为该时刻的进程，依次创建 
		
		if(p-1 > num) //如果p有后移 
		{
			num = p-1; //更新num
			Add(q); //将已创建的进程排成完全二叉堆 
			
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


#include<stdio.h>
#include<string.h>
struct vertex
{
	int indegree; //入度 
	int outdegree; //出度 
	int *next; //出度集（所有后继） 
	int *edge; //记录从当前城市指向各后继的差价
	int max; //记录从该城市走到零出度点的各路径带来的最大收益
	int imax; //记录上述最大收益对应的后继节点 
}; 

int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	struct vertex *graph = new struct vertex[n + 1]; //创建图
	
	int i , j;
	for(i = 0 ; i <= n ; i ++)
	{
		graph[i].indegree = 0;
		graph[i].outdegree = 0;
		graph[i].next = new int[101];
		graph[i].edge = new int[101];
		graph[i].max = 0;
		graph[i].imax = -1; 
	}  //图中各城市的各种信息初始化 
	
	int start , end , price; //每次输入边的起点、终点、差价 
	for(i = 1 ; i <= m ; i ++)
	{
		if(i == m) scanf("%d %d %d" , &start , &end , &price);
		else scanf("%d %d %d\n" , &start , &end , &price);
		
		graph[start].outdegree += 1; //起点出度+1
		if(graph[start].outdegree + 1 > 101) //如果出度大小超出初始设定的容量，则要更新容量 
		{
			int *p = new int[graph[start].outdegree];
			int *q = new int[graph[start].outdegree];
			for(j = 0 ; j <= graph[start].outdegree - 1 ; j ++)
			{
				p[j] = graph[start].next[j];
				q[j] = graph[start].edge[j];
			}
			delete[] graph[start].next;
			delete[] graph[start].edge;
			
			graph[start].next = new int[graph[start].outdegree + 1];
			graph[start].edge = new int[graph[start].outdegree + 1];
			for(j = 0 ; j <= graph[start].outdegree - 1 ; j ++)
			{
				graph[start].next[j] = p[j];
				graph[start].edge[j] = q[j];
			}
			delete[] p;
			delete[] q;
		}
		else n += 0;
		
		graph[start].next[graph[start].outdegree] = end; //终点是起点的第出度个后继 
		graph[start].edge[graph[start].outdegree] = price; //记录相应边的差价 
		graph[end].indegree += 1; //终点入度+1
	}
	
	//以下为拓扑排序 
	int *stack = new int[n + 1]; //作为栈使用的数组
	int top = 0; //栈顶 
	int *queue = new int[n + 1]; //作为队列使用、输出拓扑排序结果的数组
	int tail = 0; //队尾 
	for(i = 1 ; i <= n ; i ++)
	{
		if(graph[i].indegree == 0)
		{
			top ++;
			stack[top] = i;
		} 
		else continue;
	} //初始的零入度点入栈 
	while(top > 0) //当栈不为空时 
	{
		tail ++;
		queue[tail] = stack[top]; //栈顶转入队尾 
		int current = stack[top]; //记录该节点编号
		stack[top] = 0;
		top --; //栈顶前移 
		for(i = 1 ; i <= graph[current].outdegree ; i ++)
		{
			int successor = graph[current].next[i]; //successor为当前查看的后继节点 
			if(graph[successor].indegree == 1)
			{
				top ++;
				stack[top] = successor;
			}
			else top += 0;
			
			graph[successor].indegree -= 1; 
		}
	}
	
	
	//以下为动态规划获取各点的最大收益信息 
	int earning; //用于计算后续收益 
	for(i = n ; i > 0 ; i --) //从拓扑序末尾开始向前递推记录各点最大后续收益 
	{
		int index = queue[i]; 
		if(graph[index].outdegree == 0) continue; //零出度点的信息与初始赋值相同，不必更新，直接继续循环 
		else
		{
			for(j = 1 ; j <= graph[index].outdegree ; j ++)
			{
				earning = graph[index].edge[j] + graph[graph[index].next[j]].max; //与此时后继相对应的收益=关联边权重+后继的最大收益 
				if(earning > graph[index].max) //如果这个收益比此前记录的最大收益更大，则更新 
				{
					graph[index].max = earning;
					graph[index].imax = graph[index].next[j];
				}
				else if(earning == graph[index].max)//如果相等，记录字典序更小的后继 
				{
					if(graph[index].next[j] < graph[index].imax) graph[index].imax = graph[index].next[j];
					else graph[index].imax += 0;
				}
				else continue;
			} 
		}
	}  
	
	//以下为找到并输出最大收益路径上的各节点 
	int Max = 0; //所有收益中最大的那个
	int MaxStart = 0; //记录最大收益路径的起点 
	for(i = 1 ; i <= n ; i ++) //在所有点里寻找起点 
	{
		if(graph[queue[i]].max > Max)
		{
			Max = graph[queue[i]].max;
			MaxStart = queue[i];
		} 
		else if(graph[queue[i]].max == Max)
		{
			if(graph[queue[i]].imax < MaxStart) MaxStart = queue[i];
			else MaxStart += 0;
		}
		else continue;
	} 
	j = MaxStart;
	while(graph[j].outdegree > 0)
	{
		printf("%d " , j);
		j = graph[j].imax;
	} 
	printf("%d" , j);
	
} 



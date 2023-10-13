#include<stdio.h>
#include<string.h>
struct vertex
{
	int indegree; //入度 
	int outdegree; //出度 
	int *next; //记录所有当前城市关联的有向边的终点（后继） 
	int *edge; //记录从当前城市指向各城市的有向边对应的差价 
}; 

int *bestpath; //记录最佳路线 
int *path; //记录任意搜索到的路线 
int max; //记录目前最优路线的收益 

void FindPath(struct vertex *graph , int city , int *path , int length , int earning); 
int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	struct vertex *graph = new struct vertex[n + 1]; //创建图
	bestpath = new int[n];
	path = new int[n];
	
	int i , j;
	for(i = 0 ; i <= n ; i ++)
	{
		graph[i].indegree = 0;
		graph[i].outdegree = 0;
		graph[i].next = new int[101];
		graph[i].edge = new int[101];
		/*for(j = 0 ; j <= 100000 ; j ++)
		{
			graph[i].next[j] = 0;
			graph[i].edge[j] = 0;
		}*/
	}  //图中各城市的各种信息赋初值0
	
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
	
	for(i = 0 ; i < n ; i ++)
	{
		bestpath[i] = 0;
		path[i] = 0;
	}
	max = 0;
	for(i = 1 ; i <= n ; i ++)
	{
		if(graph[i].indegree == 0) FindPath(graph , i , path , 0 , 0);
	} 
	
	for(i = 0 ; bestpath[i] != 0 ; i ++) printf("%d " , bestpath[i]); 
} 

void FindPath(struct vertex *graph , int city , int *path , int length , int earning)
{
	path[length] = city; //把当前城市加入路线 
	
	int k;
	if(graph[city].outdegree == 0) //如果当前城市没有后继，则表明又完整地找到一条路线，开始与之前的最佳路线作比较处理 
	{
		if(earning > max) //若新路线赚钱更多 
		{
			max = earning; //则更新最大收益 
			for(k = 0 ; bestpath[k] != 0 ; k ++) bestpath[k] = 0; //原最佳路线清零 
			for(k = 0 ; path[k] != 0 ; k ++) bestpath[k] = path[k]; //赋为现在的路线 
		}
		else if(earning == max) //若赚钱与之前的最佳路线一样多，则要根据字典序判断 
		{
			int criterion = 0; //判据。初始为0 
			for(k = 0 ; path[k] != 0 ; k ++) //顺序查看新路线中的各个城市 
			{
				if(path[k] < bestpath[k]) //当中第一次出现比原最佳路线同级城市编号更小的时候 
				{
					criterion = 1; //判据改为1 
					break; //跳出循环 
				}
				else continue; //否则继续 
			}
			if(criterion == 1) //如果判据为1，说明新路线字典序更小，更新最佳路线 
			{
				for(k = 0 ; bestpath[k] != 0 ; k ++) bestpath[k] = 0;
			    for(k = 0 ; path[k] != 0 ; k ++) bestpath[k] = path[k];
			}
			else max += 0;
		}
		else max += 0;
		
		path[length] = 0; //把路线上最后一点清零，然后返回上一层 
		return; 
	}
	else //如果当前城市有后继
	{
		for(k = 1 ; k <= graph[city].outdegree ; k ++) //依次将所有后继作为路线中下一点进行递归 
		{
			int nextcity = graph[city].next[k];
			int newearning = earning + graph[city].edge[k];
			FindPath(graph , nextcity , path , length + 1 , newearning);
		}
		
		path[length] = 0; //把路线上最后一点清零，然后返回上一层
		return; 
	} 
}

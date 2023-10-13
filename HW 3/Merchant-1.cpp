#include<stdio.h>
#include<string.h>
struct vertex
{
	int indegree; //入度 
	int outdegree; //出度 
	int next[100001]; //记录所有当前城市关联的有向边的终点（后继） 
	int edge[100001]; //记录从当前城市指向各城市的有向边对应的差价 
}; 

int path[100000]; //记录任意搜索到的路线 
int max; //记录目前最优路线的收益 

void FindPath(struct vertex *graph , int city , int *path , int length , int earning); 
int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	struct vertex *graph = new struct vertex[n + 1];
	
	int i , j;
	for(i = 0 ; i <= n ; i ++)
	{
		graph[i].indegree = 0;
		graph[i].outdegree = 0;
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
		graph[start].next[graph[start].outdegree] = end; //终点是起点的第出度个后继 
		graph[start].edge[end] = price; //记录相应边的差价 
		graph[end].indegree += 1; //终点入度+1 
	}
	
	for(i = 0 ; i < 100000 ; i ++)
	{
		path[i] = 0;
	}
	max = 0;
	for(i = 1 ; i <= n ; i ++)
	{
		if(graph[i].indegree == 0) FindPath(graph , i , path , 0 , 0);
	} 
	
	printf("%d" , max); 
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
			FindPath(graph , nextcity , path , length + 1 , earning + graph[city].edge[nextcity]);
		}
		
		path[length] = 0; //把路线上最后一点清零，然后返回上一层
		return; 
	} 
}

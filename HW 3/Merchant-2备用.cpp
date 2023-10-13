#include<stdio.h>
#include<string.h>
struct vertex
{
	int indegree; //��� 
	int outdegree; //���� 
	int *next; //��¼���е�ǰ���й���������ߵ��յ㣨��̣� 
	int *edge; //��¼�ӵ�ǰ����ָ������е�����߶�Ӧ�Ĳ�� 
}; 

int *bestpath; //��¼���·�� 
int *path; //��¼������������·�� 
int max; //��¼Ŀǰ����·�ߵ����� 

void FindPath(struct vertex *graph , int city , int *path , int length , int earning); 
int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	struct vertex *graph = new struct vertex[n + 1]; //����ͼ
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
	}  //ͼ�и����еĸ�����Ϣ����ֵ0
	
	int start , end , price; //ÿ������ߵ���㡢�յ㡢��� 
	for(i = 1 ; i <= m ; i ++)
	{
		if(i == m) scanf("%d %d %d" , &start , &end , &price);
		else scanf("%d %d %d\n" , &start , &end , &price);
		
		graph[start].outdegree += 1; //������+1 
		if(graph[start].outdegree + 1 > 101) //������ȴ�С������ʼ�趨����������Ҫ�������� 
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
		
		graph[start].next[graph[start].outdegree] = end; //�յ������ĵڳ��ȸ���� 
		graph[start].edge[graph[start].outdegree] = price; //��¼��Ӧ�ߵĲ�� 
		graph[end].indegree += 1; //�յ����+1
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
	path[length] = city; //�ѵ�ǰ���м���·�� 
	
	int k;
	if(graph[city].outdegree == 0) //�����ǰ����û�к�̣���������������ҵ�һ��·�ߣ���ʼ��֮ǰ�����·�����Ƚϴ��� 
	{
		if(earning > max) //����·��׬Ǯ���� 
		{
			max = earning; //������������ 
			for(k = 0 ; bestpath[k] != 0 ; k ++) bestpath[k] = 0; //ԭ���·������ 
			for(k = 0 ; path[k] != 0 ; k ++) bestpath[k] = path[k]; //��Ϊ���ڵ�·�� 
		}
		else if(earning == max) //��׬Ǯ��֮ǰ�����·��һ���࣬��Ҫ�����ֵ����ж� 
		{
			int criterion = 0; //�оݡ���ʼΪ0 
			for(k = 0 ; path[k] != 0 ; k ++) //˳��鿴��·���еĸ������� 
			{
				if(path[k] < bestpath[k]) //���е�һ�γ��ֱ�ԭ���·��ͬ�����б�Ÿ�С��ʱ�� 
				{
					criterion = 1; //�оݸ�Ϊ1 
					break; //����ѭ�� 
				}
				else continue; //������� 
			}
			if(criterion == 1) //����о�Ϊ1��˵����·���ֵ����С���������·�� 
			{
				for(k = 0 ; bestpath[k] != 0 ; k ++) bestpath[k] = 0;
			    for(k = 0 ; path[k] != 0 ; k ++) bestpath[k] = path[k];
			}
			else max += 0;
		}
		else max += 0;
		
		path[length] = 0; //��·�������һ�����㣬Ȼ�󷵻���һ�� 
		return; 
	}
	else //�����ǰ�����к��
	{
		for(k = 1 ; k <= graph[city].outdegree ; k ++) //���ν����к����Ϊ·������һ����еݹ� 
		{
			int nextcity = graph[city].next[k];
			int newearning = earning + graph[city].edge[k];
			FindPath(graph , nextcity , path , length + 1 , newearning);
		}
		
		path[length] = 0; //��·�������һ�����㣬Ȼ�󷵻���һ��
		return; 
	} 
}

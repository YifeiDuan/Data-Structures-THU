#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct lz //��¼��/ʯ�ĵĽṹ�� 
{
	int x;
	int y;
};

long long int totalCost; //�ܻ��� 

int cmpfunc (const void * a, const void * b); //����qsort 

int get(int x); //�ж�x�ڵ����丸�����ӻ������� 
void rotate(int x); //����x��ת 
void splay(int x); //����splay���� 
void insert(int &x , int f , int v); //��x������Ϊf�������ҵ�����������Ҫ���λ�ò���ֵΪv���½ڵ� 
int findM(int v); //��splay����������С��v�ĵ�һ��ֵ�ı�� 
void remove(int x); //��splay����ɾ���ڵ�x 
//���Ϲ���splay�ĸ��ֺ��������ο���https://www.cnblogs.com/lazy-people/p/9326556.html�Ľ��� 

int son[500001][2]; //son[i][0]��¼���i�ڵ�����ӽڵ��ţ�son[i][1]��Ϊ���� 
int father[500001]; //��¼���i�ڵ�ĸ��� 
int key[500001]; //��¼���i�ڵ��ֵ
int root; //���ڵ��� 
int p; //��¼splay�����һ������ĵ�ı��

int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	struct lz *bridge = new struct lz[n]; //�������¼�ŵ���Ϣ 
	struct lz *material = new struct lz[m]; //�������¼ʯ����Ϣ 
	
	int i , j;
	for(i = 0 ; i < n ; i ++) scanf("%d %d\n" , &bridge[i].x , &bridge[i].y);
	for(i = 0 ; i < m ; i ++)
	{
		if(i == m - 1) scanf("%d %d" , &material[i].x , &material[i].y);
		else  scanf("%d %d\n" , &material[i].x , &material[i].y);
	}
	
	qsort(bridge , n , sizeof(bridge[0]) , cmpfunc); //��������������������� 
	qsort(material , m , sizeof(material[0]) , cmpfunc); //��������������ʯ������ 

	int index; //��¼�ҵ���ʯ����splay���еı�� 
	for(i = n - 1 , j = m - 1 ; i >= 0 ; i --) //����������������ſ�ʼ��һ��ǰƥ�����Ҫ���ʯ�� 
	{
		while((j >= 0)&&(material[j].y >= bridge[i].y)) //����δ�������е�������������ʯ�Ŀ�ʼ��һ��ǰ�Ѵ��ڵ�ǰ�ŵ����������ʯ�Ķ��������� 
		{
			insert(root , 0 , material[j].x); //���� 
			splay(p); //splay���� 
			j --;  
		}
		index = findM(bridge[i].x); //Ϊ��ǰ�����ҵ�����ʵ�ʯ�������еı�� 
		totalCost += (long long int) key[index]; //�����仨�� 
		remove(index); //������ɾ�����ʯ�ĵ���Ϣ 
	}
	
	printf("%lld" , totalCost);
	
	return 0;
}

int cmpfunc (const void * a, const void * b)
{
   return (*(lz *)a).y > (*(lz *)b).y ? 1 : -1;
}

int get(int x)
{
	return son[father[x]][1] == x;
}
void rotate(int x)
{
	int f = father[x] , ff = father[f] , w = get(x); //���ڵ���f���游ff���ж�x��������ݵ�w 
	son[f][w] = son[x][w^1]; //x�ڵ����һ�����ŵ�x��λ�� 
	father[son[f][w]] = f; //����x��һ�����ĸ���Ϊf 
	son[x][w^1] = f; //��f�ӵ�x����һ����λ�� 
	father[f] = x; //����f�ĸ���Ϊx
	father[x] = ff; //����x�ĸ��ڵ�Ϊff 
	if(ff != 0) son[ff][son[ff][1] == f] = x; //���fԭ�����Ǹ��ڵ㣨���ڵ�ĸ��ױ��Ϊ0������ff��Ϊ0����x�ӵ�ff֮��fԭ����λ��
	return; 
}
void splay(int x)
{
	for(int f ; f = father[x] ; rotate(x))
	{
		if(father[f]) //�����游ʱ��������һ�� 
		{
			if(get(f) == get(x)) rotate(f); //������һ��������ת���ף�Ȼ��ͨ��ѭ����ṹ��תx 
			else rotate(x); //��������һ��������תһ��x��Ȼ��ͨ��ѭ����ṹ����תһ��x 
		}
		if(f == 0) break;
	}
	root = x; //x�������ڵ㴦 
	return;
} 
void insert(int &x , int f , int v) //��x����ַ����֤���ղ���ʱ�丸f����Ӧ�ӽڵ���Ϣ������ 
{
	if(x == 0) //��xΪ0ʱ˵����λ��δ����ֵ 
	{
		p ++; //����ģ���� 
		x = p; //������ֵ���Ϊp 
		key[x] = v; //��¼ֵ 
		father[x] = f; //��¼�丸���
	}
	else insert(son[x][key[x] <= v] , x , v); //x��Ϊ0ʱ������һ�㣬��key[x]<=v��ֻ����x���ӣ�����ֻ�������� 
	
	return; 
}
int findM(int v)
{
	int x = root; //�Ӹ��ڵ㿪ʼѰ�� 
    while(true)
    {
        if(key[x] < v) //���ֵ��vС��x����Ϊ���ӣ�����Ѱ�� 
        {
            x = son[x][1];
            continue;
        }
        else
		{
			if(son[x][0] != 0) //��key[x]���ڵ���v��ǰ���£�������Ӵ��� 
            {
                int y = son[x][0]; //���¼���� 
                while((key[y] < v) && (son[y][1] != 0)) y = son[y][1]; //��y��ֵС��v��y���Ӵ���ʱ�����ϸ���yΪ������ 
                if(key[y] >= v) //ֱ��ֵ���ڵ���v 
                {
                    x = y;
                    continue;
                }
            }
		} 
        
        return x;
    }
}

void remove(int x)
{
	splay(x); //�Ѵ�ɾ���ڵ�ת������ 
	if((son[x][0] == 0)&&(son[x][1] == 0)) //��������Ӷ�û�У�ֱ������ڵ���Ϣ 
	{
		key[x] = 0;
		return;
	}
	if(son[x][0] == 0) //���ֻ������ 
	{
		root = son[x][1]; //�����ӳ�Ϊ�¸� 
		father[root] = 0; //����������ϸ���Ϣ 
		key[x] = 0;
		son[x][1] = 0;
		return;
	}
	if(son[x][1] == 0) //���ֻ�����ӣ�����ֻ�����ӵ�������� 
	{
		root = son[x][0];
		father[root] = 0;
		key[x] = 0;
		son[x][0] = 0;
		return;
	} 
	if((son[x][0] != 0)&&(son[x][1] != 0)) //�����Ӷ����� 
	{
		int now = son[x][0]; //��λ������
        while(son[now][1] != 0)  //ѭ�����������������ұߵĵ㣬����ѭ��ʱnowΪ����ֵС��key[root]������� 
        {
        	int temp = son[now][1];
        	now = temp;
		}
		splay(now); //��nowת����������Ϊ�¸�����Ȼû������ 
        father[son[x][1]] = now; //�¸��̳��ϸ����� 
		son[now][1] = son[x][1]; 
		key[x] = 0; //��������ϸ���Ϣ 
		son[x][0] = 0;
		son[x][1] = 0;
		father[x] = 0;
		return;
	}
} 

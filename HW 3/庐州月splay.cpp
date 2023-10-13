#include<stdio.h>
#include<string.h>
struct lz //��¼��/ʯ�ĵĽṹ�� 
{
	int x;
	int y;
};
struct lz bridge[500000];
struct lz material[500000];
long long int totalCost;

void mergeSortB(int lo , int hi); //���Ű�����������鲢������С���� 
void mergeB(int lo , int mi , int hi); //������Ķ��ֹ鲢 
void mergeSortM(int lo , int hi); //��ʯ�İ����������鲢������С���� 
void mergeM(int lo , int mi , int hi); //ʯ������Ķ��ֹ鲢 

int get(int x); //�ж�x�ڵ����丸�����ӻ������� 
void rotate(int x); //����x��ת 
void splay(int x); //����splay���� 
void insert(int x , int f , int v); //��x������Ϊf�������ҵ�����������Ҫ���λ�ò���ֵΪv���½ڵ� 
int findM(int v); //��splay����������С��v�ĵ�һ��ֵ�ı�� 
void remove(int x); //��splay����ɾ���ڵ�x 

int son[500001][2]; //son[i][0]��¼���i�ڵ�����ӽڵ��ţ�son[i][1]��Ϊ���� 
int father[500001]; //��¼���i�ڵ�ĸ��� 
int key[500001]; //��¼���i�ڵ��ֵ
int root; //���ڵ��� 
int p; //��¼splay�����һ������ĵ�ı�� 

int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	int i , j;
	for(i = 0 ; i < n ; i ++) scanf("%d %d\n" , &bridge[i].x , &bridge[i].y);
	for(i = 0 ; i < m ; i ++)
	{
		if(i == m - 1) scanf("%d %d" , &material[i].x , &material[i].y);
		else  scanf("%d %d\n" , &material[i].x , &material[i].y);
	}
	
	mergeSortB(0 , n);
	mergeSortM(0 , m);
	
	totalCost = 0;
	
	int index;
	root = 0;
	p = 0;
	for(i = 0 ; i <= m ; i ++)
	{
		son[i][0] = 0;
		son[i][1] = 0;
		father[i] = 0;
		key[i] = 0;
	} 
	for(i = n - 1 , j = m - 1 ; i >= 0 ; i --)
	{
		while((j >= 0)&&(material[j].y >= bridge[i].y))
		{
			insert(root , 0 , material[j].x);
			splay(p);
			j --;
		}
		index = findM(bridge[i].x);
		totalCost += (long long int) key[index];
		remove(index);
	}
	
	printf("%lld" , totalCost);
}

void mergeSortB(int lo , int hi)
{
	if(hi - lo < 2) return;
	int mi = (lo + hi) >> 1;
	mergeSortB(lo , mi);
	mergeSortB(mi , hi);
	mergeB(lo , mi , hi);
}
void mergeB(int lo , int mi , int hi)
{
	int i , j , k;
	int lb = mi - lo;
	struct lz *B = new struct lz[lb];
	for(i = 0 ; i < lb ; i ++) B[i] = bridge[lo + i];
	int lc = hi = mi;
	for(i = lo , j = 0 , k = mi ; (j < lb) || (k - mi < lc) ; )
	{
		if((j < lb) && ((lc <= k - mi)||(B[j].y < bridge[k].y))) bridge[i ++] = B[j ++];
		if((k - mi < lc) && ((lb <= j)||(B[j].y > bridge[k].y))) bridge[i ++] = bridge[k ++];
	}
	delete[] B;
}

void mergeSortM(int lo , int hi)
{
	if(hi - lo < 2) return;
	int mi = (lo + hi) >> 1;
	mergeSortM(lo , mi);
	mergeSortM(mi , hi);
	mergeM(lo , mi , hi);
}
void mergeM(int lo , int mi , int hi)
{
	int i , j , k;
	int lb = mi - lo;
	struct lz *B = new struct lz[lb];
	for(i = 0 ; i < lb ; i ++) B[i] = material[lo + i];
	int lc = hi = mi;
	for(i = lo , j = 0 , k = mi ; (j < lb) || (k - mi < lc) ; )
	{
		if((j < lb) && ((lc <= k - mi)||(B[j].y < material[k].y))) material[i ++] = B[j ++];
		if((k - mi < lc) && ((lb <= j)||(B[j].y > material[k].y))) material[i ++] = material[k ++];
	}
	delete[] B;
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
void insert(int x , int f , int v)
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
        return x;
    }
} 
void remove(int x)
{
	splay(x);
	if((son[root][0] == 0)&&(son[root][1] == 0)) key[root] = 0;
	else if(son[root][0] == 0)
	{
		int old = root;
		root = son[old][1];
		father[root] = 0;
		key[old] = 0;
		son[old][1] = 0;
	}
	else if(son[root][1] == 0)
	{
		int old = root;
		root = son[old][0];
		father[root] = 0;
		key[old] = 0;
		son[old][0] = 0;
	} 
	else //�����Ӷ����� 
	{
		int old = root;
		int now = son[root][0]; //��λ������
        while(son[now][1] != 0) now = son[now][1]; //ѭ�����������������ұߵĵ㣬����ѭ��ʱnowΪ����ֵС��key[root]������� 
        splay(now);
        father[son[old][1]] = now;
		son[now][1] = son[old][1]; 
		key[old] = 0;
		son[old][0] = 0;
		son[old][1] = 0;
		father[old] = 0;
	}
	
	return;
} 

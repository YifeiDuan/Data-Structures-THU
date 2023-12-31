#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct lz //记录桥/石材的结构体 
{
	int x;
	int y;
};

long long int totalCost; //总花费 

int cmpfunc (const void * a, const void * b); //用于qsort 

int get(int x); //判断x节点是其父的左子还是右子 
void rotate(int x); //树绕x旋转 
void splay(int x); //对树splay操作 
void insert(int &x , int f , int v); //从x（父亲为f）出发找到符合搜索树要求的位置插入值为v的新节点 
int findM(int v); //在splay树中搜索不小于v的第一个值的编号 
void remove(int x); //在splay树中删除节点x 
//以上关于splay的各种函数，都参考了https://www.cnblogs.com/lazy-people/p/9326556.html的讲解 

int son[500001][2]; //son[i][0]记录编号i节点的左子节点编号，son[i][1]则为右子 
int father[500001]; //记录编号i节点的父亲 
int key[500001]; //记录编号i节点的值
int root; //根节点编号 
int p; //记录splay树最后一个插入的点的编号

int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	struct lz *bridge = new struct lz[n]; //开数组记录桥的信息 
	struct lz *material = new struct lz[m]; //开数组记录石材信息 
	
	int i , j;
	for(i = 0 ; i < n ; i ++) scanf("%d %d\n" , &bridge[i].x , &bridge[i].y);
	for(i = 0 ; i < m ; i ++)
	{
		if(i == m - 1) scanf("%d %d" , &material[i].x , &material[i].y);
		else  scanf("%d %d\n" , &material[i].x , &material[i].y);
	}
	
	qsort(bridge , n , sizeof(bridge[0]) , cmpfunc); //依据美化度需求对桥排序 
	qsort(material , m , sizeof(material[0]) , cmpfunc); //依据美化能力对石材排序 

	int index; //记录找到的石材在splay树中的编号 
	for(i = n - 1 , j = m - 1 ; i >= 0 ; i --) //从美化需求度最大的桥开始逐一向前匹配符合要求的石材 
	{
		while((j >= 0)&&(material[j].y >= bridge[i].y)) //从尚未插入树中的美化能力最大的石材开始逐一向前把大于当前桥的美化需求的石材都插入树中 
		{
			insert(root , 0 , material[j].x); //插入 
			splay(p); //splay操作 
			j --;  
		}
		index = findM(bridge[i].x); //为当前的桥找到最合适的石材在树中的编号 
		totalCost += (long long int) key[index]; //加上其花费 
		remove(index); //从树中删除这个石材的信息 
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
	int f = father[x] , ff = father[f] , w = get(x); //父节点编号f，祖父ff，判断x左右子身份的w 
	son[f][w] = son[x][w^1]; //x节点的另一子树放到x的位置 
	father[son[f][w]] = f; //更新x另一子树的父亲为f 
	son[x][w^1] = f; //将f接到x的另一子树位置 
	father[f] = x; //更新f的父亲为x
	father[x] = ff; //更新x的父节点为ff 
	if(ff != 0) son[ff][son[ff][1] == f] = x; //如果f原来不是根节点（根节点的父亲编号为0），即ff不为0，则将x接到ff之下f原本的位置
	return; 
}
void splay(int x)
{
	for(int f ; f = father[x] ; rotate(x))
	{
		if(father[f]) //存在祖父时可能三点一线 
		{
			if(get(f) == get(x)) rotate(f); //若三点一线则先旋转父亲，然后通过循环体结构旋转x 
			else rotate(x); //若无三点一线则先旋转一次x，然后通过循环体结构再旋转一次x 
		}
		if(f == 0) break;
	}
	root = x; //x来到根节点处 
	return;
} 
void insert(int &x , int f , int v) //对x传地址，保证最终插入时其父f的相应子节点信息被更新 
{
	if(x == 0) //当x为0时说明该位置未插入值 
	{
		p ++; //树规模扩大 
		x = p; //待插入值编号为p 
		key[x] = v; //记录值 
		father[x] = f; //记录其父编号
	}
	else insert(son[x][key[x] <= v] , x , v); //x不为0时深入下一层，若key[x]<=v则只考虑x右子，否则只考虑左子 
	
	return; 
}
int findM(int v)
{
	int x = root; //从根节点开始寻找 
    while(true)
    {
        if(key[x] < v) //如果值比v小则x更新为右子，继续寻找 
        {
            x = son[x][1];
            continue;
        }
        else
		{
			if(son[x][0] != 0) //（key[x]大于等于v的前提下）如果左子存在 
            {
                int y = son[x][0]; //则记录左子 
                while((key[y] < v) && (son[y][1] != 0)) y = son[y][1]; //在y的值小于v且y右子存在时，不断更新y为其右子 
                if(key[y] >= v) //直到值大于等于v 
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
	splay(x); //把待删除节点转到根部 
	if((son[x][0] == 0)&&(son[x][1] == 0)) //如果左右子都没有，直接清除节点信息 
	{
		key[x] = 0;
		return;
	}
	if(son[x][0] == 0) //如果只有右子 
	{
		root = son[x][1]; //则左子成为新根 
		father[root] = 0; //再如下清空老根信息 
		key[x] = 0;
		son[x][1] = 0;
		return;
	}
	if(son[x][1] == 0) //如果只有左子，类似只有右子的情况操作 
	{
		root = son[x][0];
		father[root] = 0;
		key[x] = 0;
		son[x][0] = 0;
		return;
	} 
	if((son[x][0] != 0)&&(son[x][1] != 0)) //左右子都存在 
	{
		int now = son[x][0]; //定位左子树
        while(son[now][1] != 0)  //循环查找左子树中最右边的点，结束循环时now为树中值小于key[root]的最大者 
        {
        	int temp = son[now][1];
        	now = temp;
		}
		splay(now); //将now转到根部，成为新根，必然没有右子 
        father[son[x][1]] = now; //新根继承老根右子 
		son[now][1] = son[x][1]; 
		key[x] = 0; //如下清空老根信息 
		son[x][0] = 0;
		son[x][1] = 0;
		father[x] = 0;
		return;
	}
} 

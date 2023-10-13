#include<stdio.h>
#include<string.h>
int n;
struct node
{
	int ID;
	struct node *lChild;
	struct node *rChild;
}; //结构体记录节点的编号、左子节点（树）、右子节点（树）

struct node *Build0(int *a , int *b , int alo , int ahi , int blo , int bhi , int *fa , int *fb); //建立二叉树 
void Output0(struct node *tree); //中序输出 

int main()
{
	scanf("%d\n" , &n);
	
	int *a = new int[n + 1]; //记录先序 
	int *b = new int[n + 1]; //记录后序 
	int *fa = new int[n + 1];  //记录各编号节点在先序的位置 
	int *fb = new int[n + 1];  //记录各编号节点在后序的位置 
	
	a[0] = 0;
	b[0] = 0;
	fa[0] = 0;
	fb[0] = 0;
	
	//下为输入，a与fa，b与fb各自构成校验环关系 
	int i;
	for(i = 1 ; i <= n - 1 ; i ++)
	{
		scanf("%d" , &a[i]);
		fa[a[i]] = i;
	}
	scanf("%d\n" , &a[n]);
	fa[a[n]] = n;
	
	for(i = 1 ; i <= n ; i ++)
	{
		scanf("%d" , &b[i]);
		fb[b[i]] = i;
	}
	
	node *tree = Build0(a , b , 1 , n , 1 , n , fa , fb); //构建二叉树 
	Output0(tree); //中序输出二叉树信息 
	
	return 0;
}
struct node *Build0(int *a , int *b , int alo , int ahi , int blo , int bhi , int *fa , int *fb) //参数反映待建子树在先序、后序中的所处位置区间，alo，bhi分别为新树根在先序、后序的位置 
{
	node *root=new struct node; //新建根节点 
    root->ID = a[alo];
    root->lChild = NULL;
    root->rChild = NULL;
    
    if(alo == ahi)    return root; //如果待建子树规模为1即只含根这一个节点，则直接返回即可 
    
    int pos , lctree;
    pos = fb[a[alo + 1]]; //寻找左子树根在后序中的位置
    lctree = pos - blo + 1;//左子树规模
	 
    root->lChild = Build0(a , b , alo + 1 , alo + lctree , blo , pos , fa , fb); //创建此时root的左子树，左子树在先序、后序中都处在全子树区间的前半段 
    root->rChild = Build0(a , b , alo + lctree + 1 , ahi , pos + 1 , bhi - 1 , fa , fb); //创建此时root的右子树，右子树在先序、后序中都处在全子树区间的后半段
    return root; //左右子树分别构建完成后，加上共同的根，则该全子树已构建完全，返回这个全子树的根 
}

void Output0(struct node *tree)
{
	if(tree == NULL) return; //对叶节点的子，返回上一层继续输出 
	Output0(tree->lChild); //输出左子树 
	printf("%d " , tree->ID); //输出此时的根 
	Output0(tree->rChild);  //输出右子树 
} 

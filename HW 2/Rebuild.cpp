#include<stdio.h>
#include<string.h>
int n;
struct node
{
	int ID;
	struct node *lChild;
	struct node *rChild;
}; //结构体记录节点的编号、左子节点（树）、右子节点（树） 

struct node *Build0(int *a , int *b , int alo , int ahi , int blo , int bhi); //0号情况，建立二叉树，下同 
void Output0(struct node *tree); //0号情况，进行输出，下同 

struct node *Build1(int *a , int *b , int alo , int ahi , int blo , int bhi);
void Output1(struct node *tree);

struct node *Build2(int *a , int *b , int alo , int ahi , int blo , int bhi);
void Output2(struct node *tree);

struct node *Build3(int *a , int *b , int alo , int ahi , int blo , int bhi);
void Output3(struct node *tree);
struct node *list[1100001]; //对于层次遍历需要一个结构体指针数组实现进出队列 

int main()
{
	int k;
	scanf("%d %d\n" , &n , &k);
	
	int *a = new int[n + 1];
	int *b = new int[n + 1]; 
	
	a[0] = 0;
	b[0] = 0;
	
	int i;
	for(i = 1 ; i <= n - 1 ; i ++) scanf("%d" , &a[i]);
	scanf("%d\n" , &a[n]);
	
	for(i = 1 ; i <= n ; i ++) scanf("%d" , &b[i]);
	
	node *tree = NULL;
	switch(k) //对于不同的k，分别进入不同case来建立二叉树和按要求遍历输出 
	{
		case 0:
			tree = Build0(a , b , 1 , n , 1 , n);
	        Output0(tree);
	        break;
	    case 1:
			tree = Build1(a , b , 1 , n , 1 , n);
	        Output1(tree);
	        break;
	    case 2:
			tree = Build2(a , b , 1 , n , 1 , n);
	        Output2(tree);
	        break;
	    case 3:
			tree = Build3(a , b , 1 , n , 1 , n);
	        Output3(tree);
	        break;
	}
	
	return 0;
}

struct node *Build0(int *a , int *b , int alo , int ahi , int blo , int bhi) //参数反映待建子树在先序、后序中的所处位置区间，alo，bhi分别为新树根在先序、后序的位置 
{
	node *root=new struct node; //新建根节点 
    root->ID = a[alo];
    root->lChild = NULL;
    root->rChild = NULL;
    
    if(alo == ahi)    return root; //如果待建子树规模为1即只含根这一个节点，则直接返回即可 
    
    int pos , lctree;
    int i;
    for(i = blo ; i <= bhi ; i++)
	{
        if(a[alo + 1] == b[i]) //寻找左子树根在后序中的位置 
		{
            pos=i;
            break;
        }
        else continue; 
    }
    lctree = pos - blo + 1;//左子树规模 
    root->lChild = Build0(a , b , alo + 1 , alo + lctree , blo , pos); //创建此时root的左子树，左子树在先序、后序中都处在全子树区间的前半段 
    root->rChild = Build0(a , b , alo + lctree + 1 , ahi , pos + 1 , bhi - 1); //创建此时root的右子树，右子树在先序、后序中都处在全子树区间的后半段
    return root; //左右子树分别构建完成后，加上共同的根，则该全子树已构建完全，返回这个全子树的根 
}

void Output0(struct node *tree) //中序遍历 
{
	if(tree == NULL) return; //对叶节点的子，返回上一层继续输出 
	Output0(tree->lChild); //输出左子树 
	printf("%d " , tree->ID); //输出此时的根 
	Output0(tree->rChild);  //输出右子树 
} 

struct node *Build1(int *a , int *b , int alo , int ahi , int blo , int bhi) //参数反映待建子树在先序、中序中的所处位置区间，alo为新树根在先序的位置 
{
	node *root=new struct node; //新建根节点 
    root->ID = a[alo];
    root->lChild = NULL;
    root->rChild = NULL;
    
    if(alo == ahi)    return root; //如果待建子树规模为1即只含根这一个节点，则直接返回即可 
    
    int pos , lctree , rctree;
    int i;
    for(i = blo ; i <= bhi ; i++)
	{
        if(a[alo] == b[i]) //寻找此时树根在中序中的位置 
		{
            pos=i;
            break;
        }
        else continue; 
    }
    lctree = pos - blo; //左子树规模 
    rctree = bhi - pos; //右子树规模 
    
    if(lctree != 0) root->lChild = Build1(a , b , alo + 1 , alo + lctree , blo , pos - 1); //创建此时root的左子树，左子树在先序、中序中都处在全子树区间的前半段 

    if(rctree != 0) root->rChild = Build1(a , b , alo + lctree + 1 , ahi , pos + 1 , bhi); //创建此时root的右子树，右子树在先序、中序中都处在全子树区间的后半段

	return root; //左右子树分别构建完成后，加上共同的根，则该全子树已构建完全，返回这个全子树的根 
}

void Output1(struct node *tree) //后序遍历 
{
	if(tree == NULL) return; //对叶节点的子，返回上一层输出 
	Output1(tree->lChild); //输出左子树 
	Output1(tree->rChild);  //输出右子树 
	printf("%d " , tree->ID); //输出此时的根 
} 

struct node *Build2(int *a , int *b , int alo , int ahi , int blo , int bhi) //参数反映待建子树在中序、后序中的所处位置区间，bhi为新树根在后序的位置 
{
	node *root=new struct node; //新建根节点 
    root->ID = b[bhi];
    root->lChild = NULL;
    root->rChild = NULL;
    
    if(blo == bhi)    return root; //如果待建子树规模为1即只含根这一个节点，则直接返回即可 
    
    int pos , lctree , rctree;
    int i;
    for(i = alo ; i <= ahi ; i++)
	{
        if(b[bhi] == a[i]) //寻找此时树根在中序中的位置 
		{
            pos=i;
            break;
        }
        else continue; 
    }
    lctree = pos - alo; //左子树规模
	rctree = ahi - pos; //右子树规模
	 
    if(lctree != 0) root->lChild = Build2(a , b , alo , pos - 1 , blo , blo + lctree - 1); //创建此时root的左子树，左子树在中序、后序中都处在全子树区间的前半段 
    if(rctree != 0) root->rChild = Build2(a , b , pos + 1 , ahi , blo + lctree , bhi - 1); //创建此时root的右子树，右子树在中序、后序中都处在全子树区间的后半段
    return root; //左右子树分别构建完成后，加上共同的根，则该全子树已构建完全，返回这个全子树的根 
}

void Output2(struct node *tree) //先序遍历 
{
	if(tree == NULL) return; //对叶节点的子，返回上一层输出 
	printf("%d " , tree->ID); //输出此时的根
	Output2(tree->lChild); //输出左子树 
	Output2(tree->rChild);  //输出右子树  
} 

struct node *Build3(int *a , int *b , int alo , int ahi , int blo , int bhi) //参数反映待建子树在先序、后序中的所处位置区间，alo，bhi分别为新树根在先序、后序的位置 
{
	node *root=new struct node; //新建根节点 
    root->ID = a[alo];
    root->lChild = NULL;
    root->rChild = NULL;
    
    list[a[alo]] = root; //为了后序层次遍历将新建的根节点信息同步存入list数组 
    
    if(alo == ahi)    return root; //如果待建子树规模为1即只含根这一个节点，则直接返回即可 
    
    int pos , lctree , rctree;
    int i;
    for(i = blo ; i <= bhi ; i++)
	{
        if(a[alo + 1] == b[i]) //寻找子树根在后序中的位置 
		{
            pos=i;
            break;
        }
        else continue; 
    }
    
    if(pos == bhi - 1) //说明只有左或右一个子树 , 不妨设为左 
	{
		root->lChild = Build3(a , b , alo + 1 , ahi , blo , pos);
	} 
	else
	{
		lctree = pos - blo + 1;//左子树规模 
        root->lChild = Build3(a , b , alo + 1 , alo + lctree , blo , pos); //创建此时root的左子树，左子树在先序、后序中都处在全子树区间的前半段 
        root->rChild = Build3(a , b , alo + lctree + 1 , ahi , pos + 1 , bhi - 1); //创建此时root的右子树，右子树在先序、后序中都处在全子树区间的后半段
	}
    
    return root; //左右子树分别构建完成后，加上共同的根，则该全子树已构建完全，返回这个全子树的根 
}

void Output3(struct node *tree) //层次遍历 
{
	int i;
	int *output = new int[n + 1]; //int数组用于当作队列 
	struct node *curnode = NULL; //现节点 
	struct node *leftnode = NULL; //现节点的左子 
	struct node *rightnode = NULL; //现节点的右子 
	output[1] = tree->ID; //首节点入队 
	int head , tail; //标记队列首尾 
	head = 1;
	tail = 2;
	for(i = 1 ; i <= n - 1 ; i ++)
	{
		printf("%d " , output[head]); //队首输出 
		curnode = list[output[head]]; //访问队首节点的信息 
		if(curnode->lChild != NULL) //若有左子节点，则从队尾入队 
		{
			leftnode = curnode->lChild;
			output[tail] = leftnode->ID;
			tail ++;
		}
		
		if(curnode->rChild != NULL) //若有右子节点，则从队尾入队 
		{
			rightnode = curnode->rChild;
			output[tail] = rightnode->ID;
			tail ++;
		}
		
		head ++; //队首后移 
	}
	printf("%d" , output[n]);
}

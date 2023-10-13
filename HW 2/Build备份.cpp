#include<stdio.h>
#include<string.h>
int N; 
struct node
{
	int ID;
	int numChilds;
	struct node *lChild;
	struct node *rChild;
}; //结构体用于记录节点信息，包括编号、子树数量、左右子树（长子和弟弟） 
int main()
{
	
	scanf("%d\n" , &N);
	struct node *tree = new struct node[N + 1]; //以结构体数组表示树，分配空间 
	
	//下为实际不存在的0号节点（为便于其它节点按编号访问）的赋值 
	tree[0].ID = 0;
	tree[0].numChilds = 0;
	tree[0].lChild = NULL;
	tree[0].rChild = NULL;
	
    //下为录入邻接表信息创建初始的树 
    tree[1].rChild = NULL; //根节点无兄弟 
	int i , j , code , newcode;
	for(i = 1 ; i <= N ; i ++) //按行输入节点 
	{
		tree[i].ID = i; //编号 
		scanf("%d" , &tree[i].numChilds); //孩子数量 
		if(tree[i].numChilds == 0) //0个孩子则左子为空 
		{
			tree[i].lChild = NULL;
			continue;
		}
		else //孩子数大于0 
		{
			scanf("%d" , &code);
			tree[i].lChild = &tree[code]; //录入长子节点编号 
			if(tree[i].numChilds == 1) //若孩子数为0 
			{
				tree[code].rChild = NULL;
				continue; //则长子无兄弟，继续外层循环输入下一个节点的信息 
			}
			else //若孩子数大于1 
			{
				for(j = 2 ; j <= tree[i].numChilds - 1 ; j ++) //则从长子开始顺次赋值兄弟（右子） 
			    {
				    scanf("%d" , &newcode);
				    tree[code].rChild = &tree[newcode];
				    code = newcode;
			    }
			    scanf("%d\n" , &newcode);
				tree[code].rChild = &tree[newcode];
				tree[newcode].rChild = NULL;
			}
		}
	}
	
	
	//下为层次遍历输出结果
	int *output = new int[N + 1]; //int数组用于当作队列 
	for(i = 0 ; i <= N ; i ++) output[i] = i; //赋初值，根节点编号1，入队为队首 
	int head , tail; //分别标记队首、队尾 
	struct node *curnode; //指针指向现节点 
	head = 1;
	tail = 2;
	for(i = 1 ; i <= N - 1 ; i ++)
	{
		printf("%d\n" , tree[output[head]].ID); //输出队首编号 
		curnode = &tree[output[head]]; //队首编号的节点作为现节点 
		if(curnode->lChild != NULL) //如果有孩子 
		{
			curnode = curnode->lChild; //新的现节点为原先节点的长子 
			output[tail] = curnode->ID; //则长子由队尾入队 
			tail ++; //队尾后移 
			while(curnode->rChild != NULL) //当现节点有弟弟时 
			{
				curnode = curnode->rChild; //不断右移指针 
				output[tail] = curnode->ID; //次子及以后的孩子顺次从队尾入队 
				tail ++;
			}
		}
		else if(curnode->lChild == NULL) tail += 0; //如果没有孩子则队尾不变 
		
		head ++; //队首后移 
	}
	printf("%d" , tree[output[head]].ID);  
}

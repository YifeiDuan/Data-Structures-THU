#include<stdio.h>
#include<string.h>
int N , M;
struct node
{
	int ID;
	int numChilds;
	struct node *lChild;
	struct node *rChild;
};
struct node *move(struct node *tree , int k);
int main()
{
	
	scanf("%d %d\n" , &N , &M);
	struct node *tree = new struct node[N + 1];
	
	tree[0].ID = 0;
	tree[0].numChilds = 0;
	tree[0].lChild = NULL;
	tree[0].rChild = NULL;
	
    //��Ϊ¼���ڽӱ���Ϣ������ʼ���� 
    tree[1].rChild = NULL;
	int i , j , code , newcode;
	for(i = 1 ; i <= N ; i ++)
	{
		tree[i].ID = i;
		scanf("%d" , &tree[i].numChilds);
		if(tree[i].numChilds == 0)
		{
			tree[i].lChild = NULL;
			continue;
		}
		else
		{
			scanf("%d" , &code);
			tree[i].lChild = &tree[code];
			if(tree[i].numChilds == 1)
			{
				tree[code].rChild = NULL;
				continue;
			}
			else
			{
				for(j = 2 ; j <= tree[i].numChilds - 1 ; j ++)
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
	
	//��Ϊ����M�������ƶ�
	int k;
	for(k = 1 ; k <= M ; k ++) tree = move(tree , k);
	
	//��Ϊ��α���������
	int *output = new int[N + 1];
	for(i = 0 ; i <= N ; i ++) output[i] = i;
	int head , tail;
	struct node *curnode;
	head = 1;
	tail = 2;
	for(i = 1 ; i <= N - 1 ; i ++)
	{
		printf("%d\n" , tree[output[head]].ID);
		curnode = &tree[output[head]];
		if(curnode->lChild != NULL)
		{
			curnode = curnode->lChild;
			output[tail] = curnode->ID;
			tail ++;
			while(curnode->rChild != NULL)
			{
				curnode = curnode->rChild;
				output[tail] = curnode->ID;
				tail ++;
			}
		}
		else if(curnode->lChild == NULL) tail += 0;
		
		head ++;
	}
	printf("%d" , tree[output[head]].ID);  
}

struct node *move(struct node *tree , int k)
{
	int steps , t , rank , r;
	struct node *p , *q , *parent;
	
	//��Ϊ��Ѱ��Դ�����������ԭλ�ò��� 
	p = &tree[1]; //p��Դ����
	q = NULL;
	parent = NULL;
	scanf("%d" , &steps);
	for(t = 1 ; t <= steps ; t ++)
	{
		if(t == steps) scanf("%d\n" , &rank);
		else scanf("%d" , &rank);
		
		if((p->lChild == NULL)||(p->numChilds < rank + 1)) continue;
		else
		{
			q = p;
			parent = p;
			p = p->lChild;
			if(rank == 0) continue;
			else
			{
				for(r = 1 ; r <= rank ; r ++)
				{
					q = p;
					p = p->rChild;
				}
			}
		}	
	} 
	if(p == q->lChild)
	{
		q->lChild = p->rChild;
		q->numChilds -= 1;
		p->rChild = NULL;
	}
	else if(p == q->rChild)
	{
		q->rChild = p->rChild;
		parent->numChilds -= 1;
		p->rChild = NULL;
	}
	
	//��ΪѰ��Ŀ�길�ڵ�
	q = &tree[1]; //��q��Ŀ�길�ڵ㣬p����Ϊ֮ǰ�ҵ���Դ�������� 
	scanf("%d" , &steps);
	for(t = 1 ; t <= steps ; t ++)
	{
		if(t == steps) scanf("%d\n" , &rank);
		else scanf("%d" , &rank);
		
		if((q->lChild == NULL)||(q->numChilds < rank + 1)) continue;
		else
		{
			parent = q;
			q = q->lChild;
			if(rank == 0) continue;
			else
			{
				for(r = 1 ; r <= rank ; r ++) q = q->rChild;
			}
		}
	}
	
	//��Ϊ����rank������������λ��
	parent = q;
	parent->numChilds += 1;
	if(k == M) scanf("%d" , &rank);
	else scanf("%d\n" , &rank);
	if(rank == 0)
	{
		p->rChild = q->lChild;
		q->lChild = p;
	}
	else if(parent->numChilds > rank)
	{
		q = q->lChild;
		for(r = 2 ; r <= rank ; r ++) q = q->rChild;
		p->rChild = q->rChild;
		q->rChild = p; 
	}
	else if(parent->numChilds <= rank)
	{
		q = q->lChild;
		while(q->rChild != NULL) q = q->rChild;
		p->rChild = q->rChild;
		q->rChild = p;
	}
	
	return tree;  
} 

#include<stdio.h>
#include<string.h>
int n;
struct node
{
	int ID;
	struct node *lChild;
	struct node *rChild;
}; //�ṹ���¼�ڵ�ı�š����ӽڵ㣨���������ӽڵ㣨���� 

struct node *Build0(int *a , int *b , int alo , int ahi , int blo , int bhi); //0���������������������ͬ 
void Output0(struct node *tree); //0������������������ͬ 

struct node *Build1(int *a , int *b , int alo , int ahi , int blo , int bhi);
void Output1(struct node *tree);

struct node *Build2(int *a , int *b , int alo , int ahi , int blo , int bhi);
void Output2(struct node *tree);

struct node *Build3(int *a , int *b , int alo , int ahi , int blo , int bhi);
void Output3(struct node *tree);
struct node *list[1100001]; //���ڲ�α�����Ҫһ���ṹ��ָ������ʵ�ֽ������� 

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
	switch(k) //���ڲ�ͬ��k���ֱ���벻ͬcase�������������Ͱ�Ҫ�������� 
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

struct node *Build0(int *a , int *b , int alo , int ahi , int blo , int bhi) //������ӳ�������������򡢺����е�����λ�����䣬alo��bhi�ֱ�Ϊ�����������򡢺����λ�� 
{
	node *root=new struct node; //�½����ڵ� 
    root->ID = a[alo];
    root->lChild = NULL;
    root->rChild = NULL;
    
    if(alo == ahi)    return root; //�������������ģΪ1��ֻ������һ���ڵ㣬��ֱ�ӷ��ؼ��� 
    
    int pos , lctree;
    int i;
    for(i = blo ; i <= bhi ; i++)
	{
        if(a[alo + 1] == b[i]) //Ѱ�����������ں����е�λ�� 
		{
            pos=i;
            break;
        }
        else continue; 
    }
    lctree = pos - blo + 1;//��������ģ 
    root->lChild = Build0(a , b , alo + 1 , alo + lctree , blo , pos); //������ʱroot���������������������򡢺����ж�����ȫ���������ǰ��� 
    root->rChild = Build0(a , b , alo + lctree + 1 , ahi , pos + 1 , bhi - 1); //������ʱroot���������������������򡢺����ж�����ȫ��������ĺ���
    return root; //���������ֱ𹹽���ɺ󣬼��Ϲ�ͬ�ĸ������ȫ�����ѹ�����ȫ���������ȫ�����ĸ� 
}

void Output0(struct node *tree) //������� 
{
	if(tree == NULL) return; //��Ҷ�ڵ���ӣ�������һ�������� 
	Output0(tree->lChild); //��������� 
	printf("%d " , tree->ID); //�����ʱ�ĸ� 
	Output0(tree->rChild);  //��������� 
} 

struct node *Build1(int *a , int *b , int alo , int ahi , int blo , int bhi) //������ӳ�������������������е�����λ�����䣬aloΪ�������������λ�� 
{
	node *root=new struct node; //�½����ڵ� 
    root->ID = a[alo];
    root->lChild = NULL;
    root->rChild = NULL;
    
    if(alo == ahi)    return root; //�������������ģΪ1��ֻ������һ���ڵ㣬��ֱ�ӷ��ؼ��� 
    
    int pos , lctree , rctree;
    int i;
    for(i = blo ; i <= bhi ; i++)
	{
        if(a[alo] == b[i]) //Ѱ�Ҵ�ʱ�����������е�λ�� 
		{
            pos=i;
            break;
        }
        else continue; 
    }
    lctree = pos - blo; //��������ģ 
    rctree = bhi - pos; //��������ģ 
    
    if(lctree != 0) root->lChild = Build1(a , b , alo + 1 , alo + lctree , blo , pos - 1); //������ʱroot���������������������������ж�����ȫ���������ǰ��� 

    if(rctree != 0) root->rChild = Build1(a , b , alo + lctree + 1 , ahi , pos + 1 , bhi); //������ʱroot���������������������������ж�����ȫ��������ĺ���

	return root; //���������ֱ𹹽���ɺ󣬼��Ϲ�ͬ�ĸ������ȫ�����ѹ�����ȫ���������ȫ�����ĸ� 
}

void Output1(struct node *tree) //������� 
{
	if(tree == NULL) return; //��Ҷ�ڵ���ӣ�������һ����� 
	Output1(tree->lChild); //��������� 
	Output1(tree->rChild);  //��������� 
	printf("%d " , tree->ID); //�����ʱ�ĸ� 
} 

struct node *Build2(int *a , int *b , int alo , int ahi , int blo , int bhi) //������ӳ�������������򡢺����е�����λ�����䣬bhiΪ�������ں����λ�� 
{
	node *root=new struct node; //�½����ڵ� 
    root->ID = b[bhi];
    root->lChild = NULL;
    root->rChild = NULL;
    
    if(blo == bhi)    return root; //�������������ģΪ1��ֻ������һ���ڵ㣬��ֱ�ӷ��ؼ��� 
    
    int pos , lctree , rctree;
    int i;
    for(i = alo ; i <= ahi ; i++)
	{
        if(b[bhi] == a[i]) //Ѱ�Ҵ�ʱ�����������е�λ�� 
		{
            pos=i;
            break;
        }
        else continue; 
    }
    lctree = pos - alo; //��������ģ
	rctree = ahi - pos; //��������ģ
	 
    if(lctree != 0) root->lChild = Build2(a , b , alo , pos - 1 , blo , blo + lctree - 1); //������ʱroot���������������������򡢺����ж�����ȫ���������ǰ��� 
    if(rctree != 0) root->rChild = Build2(a , b , pos + 1 , ahi , blo + lctree , bhi - 1); //������ʱroot���������������������򡢺����ж�����ȫ��������ĺ���
    return root; //���������ֱ𹹽���ɺ󣬼��Ϲ�ͬ�ĸ������ȫ�����ѹ�����ȫ���������ȫ�����ĸ� 
}

void Output2(struct node *tree) //������� 
{
	if(tree == NULL) return; //��Ҷ�ڵ���ӣ�������һ����� 
	printf("%d " , tree->ID); //�����ʱ�ĸ�
	Output2(tree->lChild); //��������� 
	Output2(tree->rChild);  //���������  
} 

struct node *Build3(int *a , int *b , int alo , int ahi , int blo , int bhi) //������ӳ�������������򡢺����е�����λ�����䣬alo��bhi�ֱ�Ϊ�����������򡢺����λ�� 
{
	node *root=new struct node; //�½����ڵ� 
    root->ID = a[alo];
    root->lChild = NULL;
    root->rChild = NULL;
    
    list[a[alo]] = root; //Ϊ�˺����α������½��ĸ��ڵ���Ϣͬ������list���� 
    
    if(alo == ahi)    return root; //�������������ģΪ1��ֻ������һ���ڵ㣬��ֱ�ӷ��ؼ��� 
    
    int pos , lctree , rctree;
    int i;
    for(i = blo ; i <= bhi ; i++)
	{
        if(a[alo + 1] == b[i]) //Ѱ���������ں����е�λ�� 
		{
            pos=i;
            break;
        }
        else continue; 
    }
    
    if(pos == bhi - 1) //˵��ֻ�������һ������ , ������Ϊ�� 
	{
		root->lChild = Build3(a , b , alo + 1 , ahi , blo , pos);
	} 
	else
	{
		lctree = pos - blo + 1;//��������ģ 
        root->lChild = Build3(a , b , alo + 1 , alo + lctree , blo , pos); //������ʱroot���������������������򡢺����ж�����ȫ���������ǰ��� 
        root->rChild = Build3(a , b , alo + lctree + 1 , ahi , pos + 1 , bhi - 1); //������ʱroot���������������������򡢺����ж�����ȫ��������ĺ���
	}
    
    return root; //���������ֱ𹹽���ɺ󣬼��Ϲ�ͬ�ĸ������ȫ�����ѹ�����ȫ���������ȫ�����ĸ� 
}

void Output3(struct node *tree) //��α��� 
{
	int i;
	int *output = new int[n + 1]; //int�������ڵ������� 
	struct node *curnode = NULL; //�ֽڵ� 
	struct node *leftnode = NULL; //�ֽڵ������ 
	struct node *rightnode = NULL; //�ֽڵ������ 
	output[1] = tree->ID; //�׽ڵ���� 
	int head , tail; //��Ƕ�����β 
	head = 1;
	tail = 2;
	for(i = 1 ; i <= n - 1 ; i ++)
	{
		printf("%d " , output[head]); //������� 
		curnode = list[output[head]]; //���ʶ��׽ڵ����Ϣ 
		if(curnode->lChild != NULL) //�������ӽڵ㣬��Ӷ�β��� 
		{
			leftnode = curnode->lChild;
			output[tail] = leftnode->ID;
			tail ++;
		}
		
		if(curnode->rChild != NULL) //�������ӽڵ㣬��Ӷ�β��� 
		{
			rightnode = curnode->rChild;
			output[tail] = rightnode->ID;
			tail ++;
		}
		
		head ++; //���׺��� 
	}
	printf("%d" , output[n]);
}

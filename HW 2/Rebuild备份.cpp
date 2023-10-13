#include<stdio.h>
#include<string.h>
int n;
struct node
{
	int ID;
	struct node *lChild;
	struct node *rChild;
}; //�ṹ���¼�ڵ�ı�š����ӽڵ㣨���������ӽڵ㣨����

struct node *Build0(int *a , int *b , int alo , int ahi , int blo , int bhi , int *fa , int *fb); //���������� 
void Output0(struct node *tree); //������� 

int main()
{
	scanf("%d\n" , &n);
	
	int *a = new int[n + 1]; //��¼���� 
	int *b = new int[n + 1]; //��¼���� 
	int *fa = new int[n + 1];  //��¼����Žڵ��������λ�� 
	int *fb = new int[n + 1];  //��¼����Žڵ��ں����λ�� 
	
	a[0] = 0;
	b[0] = 0;
	fa[0] = 0;
	fb[0] = 0;
	
	//��Ϊ���룬a��fa��b��fb���Թ���У�黷��ϵ 
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
	
	node *tree = Build0(a , b , 1 , n , 1 , n , fa , fb); //���������� 
	Output0(tree); //���������������Ϣ 
	
	return 0;
}
struct node *Build0(int *a , int *b , int alo , int ahi , int blo , int bhi , int *fa , int *fb) //������ӳ�������������򡢺����е�����λ�����䣬alo��bhi�ֱ�Ϊ�����������򡢺����λ�� 
{
	node *root=new struct node; //�½����ڵ� 
    root->ID = a[alo];
    root->lChild = NULL;
    root->rChild = NULL;
    
    if(alo == ahi)    return root; //�������������ģΪ1��ֻ������һ���ڵ㣬��ֱ�ӷ��ؼ��� 
    
    int pos , lctree;
    pos = fb[a[alo + 1]]; //Ѱ�����������ں����е�λ��
    lctree = pos - blo + 1;//��������ģ
	 
    root->lChild = Build0(a , b , alo + 1 , alo + lctree , blo , pos , fa , fb); //������ʱroot���������������������򡢺����ж�����ȫ���������ǰ��� 
    root->rChild = Build0(a , b , alo + lctree + 1 , ahi , pos + 1 , bhi - 1 , fa , fb); //������ʱroot���������������������򡢺����ж�����ȫ��������ĺ���
    return root; //���������ֱ𹹽���ɺ󣬼��Ϲ�ͬ�ĸ������ȫ�����ѹ�����ȫ���������ȫ�����ĸ� 
}

void Output0(struct node *tree)
{
	if(tree == NULL) return; //��Ҷ�ڵ���ӣ�������һ�������� 
	Output0(tree->lChild); //��������� 
	printf("%d " , tree->ID); //�����ʱ�ĸ� 
	Output0(tree->rChild);  //��������� 
} 

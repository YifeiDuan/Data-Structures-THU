#include<stdio.h>
#include<string.h>
int N; 
struct node
{
	int ID;
	int numChilds;
	struct node *lChild;
	struct node *rChild;
}; //�ṹ�����ڼ�¼�ڵ���Ϣ��������š������������������������Ӻ͵ܵܣ� 
int main()
{
	
	scanf("%d\n" , &N);
	struct node *tree = new struct node[N + 1]; //�Խṹ�������ʾ��������ռ� 
	
	//��Ϊʵ�ʲ����ڵ�0�Žڵ㣨Ϊ���������ڵ㰴��ŷ��ʣ��ĸ�ֵ 
	tree[0].ID = 0;
	tree[0].numChilds = 0;
	tree[0].lChild = NULL;
	tree[0].rChild = NULL;
	
    //��Ϊ¼���ڽӱ���Ϣ������ʼ���� 
    tree[1].rChild = NULL; //���ڵ����ֵ� 
	int i , j , code , newcode;
	for(i = 1 ; i <= N ; i ++) //��������ڵ� 
	{
		tree[i].ID = i; //��� 
		scanf("%d" , &tree[i].numChilds); //�������� 
		if(tree[i].numChilds == 0) //0������������Ϊ�� 
		{
			tree[i].lChild = NULL;
			continue;
		}
		else //����������0 
		{
			scanf("%d" , &code);
			tree[i].lChild = &tree[code]; //¼�볤�ӽڵ��� 
			if(tree[i].numChilds == 1) //��������Ϊ0 
			{
				tree[code].rChild = NULL;
				continue; //�������ֵܣ��������ѭ��������һ���ڵ����Ϣ 
			}
			else //������������1 
			{
				for(j = 2 ; j <= tree[i].numChilds - 1 ; j ++) //��ӳ��ӿ�ʼ˳�θ�ֵ�ֵܣ����ӣ� 
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
	
	
	//��Ϊ��α���������
	int *output = new int[N + 1]; //int�������ڵ������� 
	for(i = 0 ; i <= N ; i ++) output[i] = i; //����ֵ�����ڵ���1�����Ϊ���� 
	int head , tail; //�ֱ��Ƕ��ס���β 
	struct node *curnode; //ָ��ָ���ֽڵ� 
	head = 1;
	tail = 2;
	for(i = 1 ; i <= N - 1 ; i ++)
	{
		printf("%d\n" , tree[output[head]].ID); //������ױ�� 
		curnode = &tree[output[head]]; //���ױ�ŵĽڵ���Ϊ�ֽڵ� 
		if(curnode->lChild != NULL) //����к��� 
		{
			curnode = curnode->lChild; //�µ��ֽڵ�Ϊԭ�Ƚڵ�ĳ��� 
			output[tail] = curnode->ID; //�����ɶ�β��� 
			tail ++; //��β���� 
			while(curnode->rChild != NULL) //���ֽڵ��еܵ�ʱ 
			{
				curnode = curnode->rChild; //��������ָ�� 
				output[tail] = curnode->ID; //���Ӽ��Ժ�ĺ���˳�δӶ�β��� 
				tail ++;
			}
		}
		else if(curnode->lChild == NULL) tail += 0; //���û�к������β���� 
		
		head ++; //���׺��� 
	}
	printf("%d" , tree[output[head]].ID);  
}

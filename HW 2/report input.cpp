#include<stdio.h>
int main()
{
    int x;
    int n = 250000;
    int k = 1;
    FILE *fp=fopen("D:\\�γ�\\�����\\���ݽṹ\\��ҵ2\\text.txt","w");
    fprintf(fp,"%d %d\n" , n , k);
    for(x = 250000 ; x >= 1 ; x --) fprintf(fp,"%d ",x);
    fprintf(fp , "\n");
    for(x = 1 ; x <= 250000 ; x ++) fprintf(fp,"%d ",x);
    
    fclose(fp);

}

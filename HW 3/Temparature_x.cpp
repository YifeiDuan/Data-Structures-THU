#pragma warning(disable:4996)
#include <stdio.h>
#include "temperature.h"
#define maxn 50000
using namespace std;
struct range_node;//��Χ��ѯ�Ľڵ㹹�ɷ�Χ��ѯ��
//station_type��ÿһ���۲�վ�ľ������ݣ�������x,y���꣬�¶�temp��
//�۲�վ�ڲ�����һ��ָ��c��������ָ��Ҷ�ӽڵ㣬Ȼ����������·����
//һ��ָ��road������ָ��ǰһ���ڵ�
typedef struct _station_type
{
	int x, y;
	int temp;
	_station_type&operator=(const _station_type&data)
	{
		temp = data.temp;
		x = data.x;
		y = data.y;
		return *this;
	}
	range_node*c,*road=NULL;
} station_type;
station_type stations[maxn];
//fctree����������yֵ���飬ÿ��fctree�ж�����station_type���͵�data
//yֵ�Ƚϴ�С����yֵ��ͬʱ����xֵ�����ﲻ���ܳ���x��yֵ��ͬ
struct fctree {
	station_type data;
	bool operator>(const fctree&a)
	{
		if (data.y > a.data.y)return true;
		else if (data.y == a.data.y) {
			if (data.x > a.data.x)return true;
			else return false;
		}
		else return false;
	}
	bool operator<(const fctree&a)
	{
		if (data.y < a.data.y)return true;
		else if (data.y == a.data.y) {
			if (data.x < a.data.x)return true;
			else return false;
		}
		else return false;
	}
};
//ÿ���ڵ㶼������ָ��Ͷ�Ӧ��yֵ
//����Ҫ����AVL��
struct range_node {
	range_node*rc, *lc, *parent;
	fctree*fc;//���ָ������ָ��y��ֵ�����飬�ǵó�ʼ��ʱҪ��new fc��ȷ�����������С
	int fc_size = 0;
	station_type data;//ÿ���ڵ��ж�ֻ��һ�����ݵ�
	int height = 0;
	range_node() { rc = lc = NULL; fc = NULL; parent = NULL; }
	range_node(const station_type&e, range_node*p, fctree*fc1 = NULL, range_node*lc1 = NULL, range_node*rc1 = NULL) :data(e), parent(p), fc(fc1), lc(lc1), rc(rc1) {}
};
 
//����AVL��---------------------------------------------------------
struct rangetree {
	//�����������ݳ�Ա;
	rangetree() { range_node(); }
	range_node*_hot;//�������ĸ��׽ڵ�
	range_node*_root;//���ڵ�
	range_node*&search(const int&e);
	void insertAsRoot(const station_type&e);
	range_node*insert(const station_type&data);
	range_node*&fromparento(range_node*g);
	range_node*connect34(range_node*a, range_node*b, range_node*c, range_node*t0, range_node*t1, range_node*t2, range_node*t3);
	range_node*rotateAt(range_node*g);
	void search_leaf(range_node*&v, int&i, range_node*hot);
	int size = 0;
};
//_station_type�������Ҫ��x��y�����
bool operator==(const _station_type&data1, const _station_type&data2)
{
	return ((data1.x == data2.x) && (data1.y == data2.y));
}
int stature(range_node*a) { return a ? a->height : -1; }//����a����Ϊ�գ������Ҫ��������һ������
void rangetree::insertAsRoot(const station_type&e)
{
	_root = new range_node(e, NULL); size++;
}
range_node*&searchin(range_node*&v, const int&e, range_node*&hot)
{
	if (!v)return v;
	hot = v;
	return searchin((e <= v->data.x) ? v->lc : v->rc, e, hot);
}
range_node*&rangetree::search(const int&e)
{
	//����_hot=NULL�󣬾Ͳ���ÿ�β�ѯ����_hot���¸�����
	return searchin(_root, e, _hot = NULL);
}
bool Balance(range_node a) { return (stature(a.lc) - stature(a.rc)) > -2 && stature(a.lc) - stature(a.rc) < 2; }
bool islchild(range_node*g) { return g->parent && (g->parent->lc == g); }
bool isrchild(range_node*g) { return g->parent && (g->parent->rc == g); }
void updateheight(range_node*g)
{
	if (stature(g->lc)>stature(g->rc)) { g->height = stature(g->lc) + 1; }
	else { g->height = stature(g->rc) + 1; }
}
range_node*tallerchild(range_node*g)
{
	return (stature(g->lc) > stature(g->rc)) ? g->lc : (((stature(g->lc) <stature(g->rc)) ? g->rc : (islchild(g) ? g->lc : g->rc)));
}
range_node*&rangetree::fromparento(range_node*g)
{
	if (g->parent) { return islchild(g) ? g->parent->lc : g->parent->rc; }
	else { return _root; }
}
range_node*rangetree::insert(const station_type&data)
{
	range_node*&x = search(data.x);
	//x���ܸı䣬��Ϊx�����ã�x�ı䣬���丸�ڵ�ĺ���ָ��Ҳ���Ÿı䣬��Ϊ�˰�ȫ��������ܸı䣻
	range_node*xx = x = new range_node(data, _hot);
	for (range_node*g = _hot; g; g = g->parent)
	{
		if (!Balance(*g)) {
			auto&temp = fromparento(g);//=rotateAt(tallerchild(tallerchild(g)));
									   //auto p = tallerchild(g);
									   //auto v = tallerchild(p);
			temp = rotateAt(tallerchild(tallerchild(g)));
			break;
		}
		else updateheight(g);
	}
	size++;
	return xx;
}
range_node*rangetree::connect34(range_node*a, range_node*b, range_node*c, range_node*t0, range_node*t1, range_node*t2, range_node*t3)
{
	a->lc = t0; if (t0) { t0->parent = a; }// printf("a->lc= %d\n", a->lc->data.x);
	a->rc = t1; if (t1) { t1->parent = a; }//printf("a->rc= %d\n", a->rc->data.x);
	updateheight(a);
	c->lc = t2; if (t2) { t2->parent = c; } //printf("c->lc= %d\n", c->lc->data.x);
	c->rc = t3; if (t3) { t3->parent = c; }// printf("c->rc= %d\n", c->rc->data.x);
	updateheight(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b; updateheight(b);
	return b;
}
range_node*rangetree::rotateAt(range_node*v)
{
	range_node*p = v->parent;
	range_node*g = p->parent;
	if (islchild(p)) {
		if (islchild(v)) {
			p->parent = g->parent;//������parentָ��ҲҪ�ǵø��£�
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else
		{
			v->parent = g->parent;
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	}
	else {
		if (islchild(v)) {
			v->parent = g->parent;
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
		else {
			p->parent = g->parent;
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
	}
}
//AVL���������---------------------------------------------------------
 
bool isleaf(range_node*root) {
	return root && (!root->lc && !root->rc);
}
int n;
long long int  record = 0;
int count;
station_type stack_x1[100], stack_x2[100];
int road_x1, road_x2;
void merge_y(fctree*&a1, fctree data_lc[], fctree data_rc[], int n_lc, int n_rc)
{
	a1 = new fctree[n_lc + n_rc];
	int i = 0, j = 0, k = 0;
	while (i < n_lc&&j < n_rc)
	{
		if (data_lc[i] < data_rc[j])a1[k++].data = data_lc[i++].data;
		else a1[k++].data = data_rc[j++].data;
	}
	if (i == n_lc)
		while (k<n_lc + n_rc)
		{
			a1[k++].data = data_rc[j++].data;
		}
	else
		while (k<n_lc + n_rc)
		{
			a1[k++].data = data_lc[i++].data;
		}
}
//����Ҷ�ӽڵ㲢�Ҳ����Ӧ��xֵ�ڵ㣬ע�⣬ÿ����һ�Σ�ÿ���ڵ��yֵҲ�����һ��
//�ڵ���fctreeװyֵ
void rangetree::search_leaf(range_node*&v, int&i, range_node*hot)
{
	if (!v) {
		if (i < n)
		{
			stations[i].c = v = new range_node(stations[i], hot);
			v->fc = new fctree[1]; 
			v->fc->data = stations[i++];
			(v->fc_size)++;
		}
	}
	else {
		hot = v;
		search_leaf(v->lc, i, hot);
		search_leaf(v->rc, i, hot);
		if (v->lc && v->rc)
		{
			merge_y(v->fc, v->lc->fc, v->rc->fc, v->lc->fc_size, v->rc->fc_size);
			v->fc_size = v->lc->fc_size + v->rc->fc_size;
		}
		else
		{
			v->fc = new fctree[v->lc->fc_size];
			for (auto i = 0; i < v->lc->fc_size; i++)v->fc[i].data = v->lc->fc[i].data;
			v->fc_size = v->lc->fc_size;
		}
	}
}
//���ڶ�x����2�ֲ���
void merge_x(station_type data[], int lo, int mi, int hi)
{
	station_type*a1 = new station_type[mi - lo];
	int k = lo, i = 0, t = mi - lo;
	for (auto i = 0; i < mi - lo; i++)a1[i] = data[k++];
	while ((mi< hi) && (i<t))
	{
		if (a1[i].x < data[mi].x)data[lo++] = a1[i++];
		else if (a1[i].x == data[mi].x&&a1[i].y < data[mi].y)data[lo++] = a1[i++];
		else data[lo++] = data[mi++];
	}
	if (i == t);
	else while (lo < hi)data[lo++] = a1[i++];
	delete[]a1;
}
void mergesort_x(station_type data[], int lo, int hi)
{
	int mi;
	if (hi - lo > 1) {
		mi = (hi + lo) >> 1;
		mergesort_x(data, lo, mi);
		mergesort_x(data, mi, hi);
		merge_x(data, lo, mi, hi);
	}
	else return;
}
//Ѱ��x1��x2
void search_x1(range_node*root, int x1, int x2, station_type stack[], int&road, int lo, int hi)
{
	int lenght = hi;
	while (hi > lo)
	{
		int mi = (hi + lo) >> 1;
		(stations[mi].x<x1) ? lo = mi + 1 : hi = mi;
	}
	if (lo<lenght&& stations[lo].x <= x2) {
		auto root = stations[lo].c;
		while (root)
		{
			stack[road] = root->data;
			stack[road].c = root;
			if (!isleaf(stack[road].c))stack[road].road = stack[road - 1].c;
			road++;
			root = root->parent;
			
		}
	}
	else;
}
void search_x2(range_node*root, int x1, int x2, station_type stack[], int&road, int lo, int hi)
{
	int lenght = hi;
	while (hi > lo)
	{
		int mi = (hi + lo) >> 1;
		(stations[mi].x > x2) ? hi = mi : lo = mi + 1;
	}
	--lo;
	if (lo > -1 && stations[lo].x >= x1) {
		auto root = stations[lo].c;
		while (root)
		{
			stack[road] = root->data;
			stack[road].c = root;
			if (!isleaf(stack[road].c))stack[road].road = stack[road - 1].c;
			road++;
			root = root->parent;
		}
	}
	else;
}
//Ѱ��ÿ��·���Ĺ����ڵ㣬�Ӹýڵ㿪ʼ����
range_node*common_root()
{
	while (0 < road_x1 && 0 < road_x2&&stack_x1[--road_x1] == stack_x2[--road_x2]);
	return (stack_x1[road_x1] == stack_x2[road_x2]) ? stack_x1[road_x1].c : stack_x1[++road_x1].c;
}
//��ÿ���ڵ��yֵ����2�ֲ��ң�
void search_y(range_node*root, int lo, int hi, int y1, int y2)
{
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		(y1 <= root->fc[mi].data.y) ? hi = mi : lo = mi + 1;
	}
	while (lo < root->fc_size&&root->fc[lo].data.y <= y2  )
	{
		record += root->fc[lo].data.temp;
		count++;
		lo++;
	}
}
void travelReport(int x1,int x2,int y1, int y2)
{
	while (road_x1 >= 0)
	{
		auto rc = stack_x1[road_x1].c->rc;
		auto lc = stack_x1[road_x1].c->lc;
		auto road = stack_x1[road_x1].road;
		if (rc&&rc!=road)search_y(rc, 0, rc->fc_size, y1, y2);
		road_x1--;
	}
	auto now = stack_x1[road_x1 + 1].c;
	if (now->data.x >= x1 &&now->data.x <= x2 && now->data.y >= y1 && now->data.y <= y2)
	{
		count++;
		record += now->data.temp;
	}
	while (road_x2 >= 0)
	{
		auto rc = stack_x2[road_x2].c->rc;
		auto lc = stack_x2[road_x2].c->lc;
		auto road = stack_x2[road_x2].road;
		if (lc&&lc != road)search_y(lc, 0, lc->fc_size, y1, y2);
		road_x2--;
	}
	auto now2 = stack_x2[road_x2 + 1].c;
	if (now2->data.x >= x1 && now2->data.x <= x2 && now2->data.y >= y1 && now2->data.y <= y2)
	{
		count++;
		record += now2->data.temp;
	}
}
//������������������֤AVL������ȷ����-----------------------------------------------------------------
void xianxutravel(range_node*r)
{
	printf("%d(%d)\n", r->data.x, r->data.y);
	if (r->lc)xianxutravel(r->lc);
	if (r->rc)xianxutravel(r->rc);
}
void midtravel(range_node*r)
{
	if (r->lc)midtravel(r->lc);
	printf("%d(%d)\n", r->data.x, r->data.y);
	if (r->rc)midtravel(r->rc);
}
int main()
{
	n = GetNumOfStation();
	if (n == 0) {
		int x1, x2, y1, y2;
		while (GetQuery(&x1, &y1, &x2, &y2)) {
			Response(0); printf("0\n");
		}
		return 0;
	}
	rangetree a;
	for (auto i = 0; i < n; i++)GetStationInfo(i, &(stations[i].x), &(stations[i].y), &(stations[i].temp));
	a.insertAsRoot(stations[0]);
	for (auto i = 1; i < n; i++)a.insert(stations[i]);
	//Ϊ�˷�ֹ�����ȴ�Ĳ��뵼�º���С��û��λ�ã����Ե�������;
 
	mergesort_x(stations, 0, n);
	int i = 0;
	a._hot = NULL;
	a.search_leaf(a._root, i, a._hot);
	//������������
	//midtravel(a._root);
	//printf("--------------\n");
	//xianxutravel(a._root);
	
	int x1, x2, y1, y2, num = 1;
	while (GetQuery(&x1, &y1, &x2, &y2))
	{
		search_x1(a._root, x1, x2, stack_x1, road_x1, 0, n);
		//ȡ��ע�Ϳ��Կ���·��
		//printf("road%d:= ", num);
		//for (auto i = 0; i < road_x1; i++) { printf("%d(%d) ", stack_x1[i].x, stack_x1[i].y); }
		//printf("\n");
		search_x2(a._root, x1, x2, stack_x2, road_x2, 0, n);
		//printf("road%d:= ", num++);
		//printf("%d,%d\n", road_x1, road_x2);
		//for (auto i = 0; i < road_x2; i++) { printf("%d(%d) ", stack_x2[i].x, stack_x2[i].y); }
		//printf("\n");
		int t1 = road_x1, t2 = road_x2;
		if (road_x1&&road_x2)
		{
			range_node*v = common_root();
			//ȡ��ע�Ϳ��Կ��������ڵ�
			//printf("%d,%d\n", road_x1, road_x2);
			//printf("v= %d(%d)\n", v->data.x, v->data.y
				road_x1--;
				travelReport(x1,x2,y1, y2);
			//printf("count = %d\n", count);
			if (count != 0) {
				Response(record / count);
				//ȡ��ע�Ϳ���ֱ�ӿ������
				//printf("%d\n", record / count);
				//printf("count= %d\n", count);
			}
			else {
				Response(0);
				//printf("0\n");
			}
		}
		else {
			Response(0);
			//printf("0\n");
		}
		for (auto i = 0; i < t1; i++) { stack_x1[i].c = NULL; stack_x1[i].road = NULL; stack_x1[i].x = 0; stack_x1[i].y = 0; stack_x1[i].temp = 0; }
		for (auto i = 0; i <t2; i++) { stack_x2[i].c = NULL; stack_x1[i].road = NULL; stack_x2[i].x = 0; stack_x2[i].y = 0; stack_x2[i].temp = 0; }
		t1 = t2 = road_x1 = road_x2 = record = count = 0;
	}
}

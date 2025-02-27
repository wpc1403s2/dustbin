#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<string.h>
#include<cmath>
using namespace std;

// ================= 代码实现开始 =================

typedef double lf;
typedef long long ll;

const int N = 300005;

// 用于存储一个二维平面上的点
struct ip {
	int x, y;

	// 构造函数
	ip(int x = 0, int y = 0) : x(x), y(y) { }

	// 先比较x轴，再比较y轴
	bool operator < (const ip &a) const {
		return x == a.x ? y < a.y : x < a.x;
	}
} a[N], b[N];

// 计算x的平方
ll sqr(const ll &x) {
	return x * x;
}

// 计算点a和点b的距离
lf dis(const ip &a, const ip &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

/* 请在这里定义你需要的全局变量 */
lf ans;
void solve(int l, int r)
{
	if (r - l <= 0) {
		//ans = min(ans, dis(a[l], a[r]));
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1,r);
	int md = a[mid].x;
	int cnt = 0;
	for (int i = l, j = mid + 1; i <= mid || j <= r;) {
		for (; i <= mid && md - a[i].x > ans; ++i);
		for (; j <= r && a[j].x - md > ans; ++j);
		if (i <= mid && (j > r || a[i].y < a[j].y))b[cnt++] = a[i++];
		else b[cnt++] = a[j++];
	}
	for (int i = 0; i < cnt; ++i)
		for (int j = i + 1; j < cnt&&b[j].y - b[i].y <= ans; ++j)
			ans = min(ans, dis(b[i], b[j]));
	/*对y轴进行归并排序*/
	 cnt = 0;
	for (int i = l, j = mid + 1; i <= mid || j <= r;) {
		if (i <= mid && (j > r || a[i].y < a[j].y))b[cnt++] = a[i++];
		else b[cnt++] = a[j++];
	}
	//将排好序的点放回a中
	memcpy(a + l, b, sizeof(ip)*cnt);
}
// 计算最近点对的距离
// n：n个点
// X, Y：分别表示x轴坐标和y轴坐标，下标从0开始
// 返回值：最近的距离
double getAnswer(int n, vector<int> X, vector<int> Y) {
	/* 请在这里设计你的算法 */
	for (int i = 0; i < n; i++)
		a[i + 1] = ip(X[i], Y[i]);
	ans = 1e100;
	sort(a + 1, a + 1 + n);
	solve(1, n);
	return ans;
}

// ================= 代码实现结束 =================

int main() {
	int n;
	scanf("%d", &n);
	vector<int> X, Y;
	for (int i = 1; i <= n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		X.push_back(x);
		Y.push_back(y);
	}
	printf("%.2f\n", getAnswer(n, X, Y));
	return 0;
}


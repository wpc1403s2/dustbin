#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
const int N = 21, mo = 23333;
int f[N][N][N][N][N][6];
int dp(int a, int b, int c, int d, int e, int last)
{
	if ((a | b | c | d | e) == 0)return 1;
	if (f[a][b][c][d][e][last] !=-1)
		return f[a][b][c][d][e][last];
	long long ret = 0;
	if (a)
	{
		ret += dp(a - 1, b, c, d, e, 1)*(a - (last == 2));
	}
	if (b)
	{
		ret += dp(a+1, b - 1, c, d, e, 2)*(b - (last == 3));
		
	}
	if (c)
	{
		ret += dp(a, b+1, c - 1, d, e, 3)*(c - (last == 4));
		
	}
	if (d)
	{
		ret += dp(a, b, c+1, d - 1, e, 4)*(d - (last == 5));
	}
	if (e)
	{
		ret += dp(a, b, c, d+1, e - 1, 5)*e;
	}
	f[a][b][c][d][e][last] = ret % mo;
	return f[a][b][c][d][e][last];


}
int b[6];
int getAnswer(int m, vector<int>a)
{
	memset(f, -1, sizeof f);
	for (int i = 0; i < m; ++i)b[a[i]]++;
	return dp(b[1], b[2], b[3], b[4], b[5], 0);
}
int main() {
	int m;
	scanf("%d", &m);
	vector<int> a;
	for (int i = 0; i < m; ++i) {
		int x;
		scanf("%d", &x);
		a.push_back(x);
	}
	printf("%d\n", getAnswer(m, a));
	return 0;
}

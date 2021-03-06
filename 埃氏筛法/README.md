
> 原文：hushhw's blog——[“埃氏筛法”思想运用](https://hushhw.cn/posts/learn/d033fe5e.html)

# 何为“埃氏筛法”

> 埃拉托斯特尼筛法，简称埃氏筛或爱氏筛，是一种由希腊数学家埃拉托斯特尼所提出的一种简单检定素数的算法。要得到自然数n以内的全部素数，必须把不大于根号n的所有素数的倍数剔除，剩下的就是素数。


# 求n以内的素数个数
给你一个数n,请问n以内有多少个素数?一般来说,要是对一个整数进行素数判断，首先想到的是写个函数判断是否为素数，然后调用这个函数，时间复杂度为O(n^(½)，但是要求n以内的素数就略显吃力了。这里就可以用埃氏筛法来处理这个问题。

```
#include <iostream>
#include <cstdio>
using namespace std;
const int SIZE = 1e7;

int prime[SIZE];		//第i个素数
bool is_prime[SIZE];	//true表示i是素数

int slove(int n){
	int p=0;
	for(int i=0; i<=n; i++)
		is_prime[i] = true;		//初始化
	is_prime[0] = is_prime[1] = false;	//0,1不是素数
	for(int i=2; i<=n; i++){
		if(is_prime[i]){
			prime[p++] = i;
			for(int j=2*i; j<=n; j+=i)  //将i的倍数全部设为false
				is_prime[j] = false;
		}
	}
	return p;
}

int main(){
	int n;
	while(cin>>n){
		int res = slove(n);
		cout<<res<<endl;
		for(int i=0; i<res; i++)
			cout<<prime[i]<<endl;
	}
}
```
看代码说明，埃氏筛法是通过把不大于n的所有素数的倍数剔除，剩下的就是素数，这里最小的素数是2，将表中所有2的倍数都除去，剩下最小的数是3，不能被更小的数整除，所以是素数。再将表中3的倍数的数除去。以此类推。如果表中最小的数字是m，m就是素数。然后将表中所有m的倍数都除去……


# 利用埃氏筛法的思想解题

链接：https://www.nowcoder.net/acm/contest/71/A
来源：牛客网


> 找一找
> 时间限制：C/C++ 1秒，其他语言2秒
> 空间限制：C/C++ 262144K，其他语言524288K
> 64bit IO Format: %lld
> 题目描述
> 给定n个正整数，请找出其中有多少个数x满足：在这n个数中存在数y=kx，其中k为大于1的整数
> 输入描述:
> 第一行输入一个n
> 接下来一行输入n个正整数ai
> 输出描述:
> 输出符合条件个数
> 示例1
> 输入
> 5
> 1 2 3 4 5
> 输出
> 2
> 说明
> 5个数中1和2符合条件，1是后面每个数的因子，2是4的因子
> 备注:
> 1≤n,a
> i
> ≤1000000

```
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

const int N=1e6+5;
int b[N],a[N],sum;
int main()
{
	int n;
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>a[i],b[a[i]]=1;
	for(int i=0; i<n; i++)
	{
		if(a[i]==1)
		{
			sum++;
			continue;
		}
		for(int j=a[i]+a[i]; j<N; j+=a[i])
			if(b[j]==1)
			{
				sum++;
				break;
			}
	}
	printf("%d\n",sum);
	system("pause");
	return 0;
}
```
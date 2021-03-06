> “在信息学竞赛中，有一类与数位相关的区间统计问题。这类问题往往具有比较浓厚的数学味道，无法暴力求解，需要在数位上进行地推等操作。”——刘聪《浅谈数位类统计问题》

这类问题往往需要一些预处理，这里就要用到数位dp。

数位DP是解决把一个数字区间里所有数字按位拆分再进行计算或计数的问题的动态规划算法。



## 基本思想与方法

题目中经常需要统计区间[l, r]的满足题意的数的个数，这往往可以转换成求[0,r] - [0,l)的问题。对于求区间[0,n]有一个通用的方法：

​	对于一个小于n的数，肯定是从高位到低位出现某一位<n的那一位，比如n=58(n为十进制)，x=49时，此时x的十位小于n，x=51时，此时x的个位小于n。

有了这个性质，我们可以从高位到低位枚举第一次<n对应位是哪一位。这样之前的位确定了，之后的位就不受n的限制即从00...0~99...9，可以先预处理，然后这时就可以直接统计答案。

预处理f数组。$F[i, st]$代表的是位数为i，状态为st的方案数。这里的st根据题目需要确定。如i=4，$F[i, st]$也就是0000~9999的符合条件的数的个数。

决策第i位是多少（0~9），F[i, st] = F[i, st] + F[i-1, st']，st'为相对应的状态。



## 例题

### 【Hdu2089 吉利数】

> 题意：
>
> 区间[l,r]内数字的数位不含62且不含4的数的个数，0<l<=r<1000000
>
> 如62315包含62，所以不合法

参照前面提到的思路，先预处理一个f数组，然后统计[0, m] - [0, n)。

f[i, j]表示开头为j 的i 位数中不包含"62"或"4"的数有多少个。如f[2, 6]包含60，61，63，65，66，67，68，69。我们这里再举个栗子f[3, 0]：表示从1~100中满足条件的个数、（这里就不枚举了、、、）【0,99】

那么f[3, 1]呢？表示从100~200中满足条件的个数【100,199】

具体看代码：

```c++
int dp[10][10];

void init(){
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for(int i=1; i<=7; i++){		
		for(int j=0; j<10; j++){	//枚举第i位数上的数字
			for(int k=0; k<10; k++){//枚举第i-1为数上的数字
				if(j!=4 && !(j==6 && k==2))//满足条件
					dp[i][j] += dp[i-1][k];
			}
		}
	}
}
```

完整代码如下：

```c++
#include <iostream>
#include <string>
using namespace std;

int dp[10][10];

void init(){
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for(int i=1; i<=7; i++){		
		for(int j=0; j<10; j++){	//枚举第i位数上的数字
			for(int k=0; k<10; k++){//枚举第i-1为数上的数字
				if(j!=4 && !(j==6 && k==2))//满足条件
					dp[i][j] += dp[i-1][k];
			}
		}
	}
}

int solve(int n){
	init();
	int digit[10];			//存储每位数字
	int len = 1;			//位数
	while(n){
		digit[len++]=n%10;
		n /= 10;
	}
	int ans=0;				//记录满足条件的结果
	for(int i=len; i>=1; i--){	//从最高为开始遍历
		for(int j=0; j<digit[i]; j++){
			if(j!=4 && !(digit[i+1]==6 && j==2))
				ans += dp[i][j];
		}
		if(digit[i]==4 || (digit[i+1]==6 && digit[i]==2)) ////第i位已经不满足条件，则i位以后都不可能满足条件，结束循环  
			break;
	}
	return ans;
}

int main(){
	int l,r;
	while(cin>>l>>r){
		if(l+r==0)
			break;
		else
			cout<<solve(r+1)-solve(l)<<endl;
	}
	return 0;
}
```

另外一种方法：`记忆化的数位dp`

通常而言，有四个参数必须 dp( pos, flag, limit ) 
pos表示当前**正在**枚举的数位。 
flag标志已经枚举的前缀是否某种性质（前面的数位和，是否含有某个数，前一个枚举的数等等。。），当然flag可以有多个。 
limit表示当前是否为上限，有时还会记录是否有前导0。 
相较而言，记忆化搜索更容易编写，需要维护的细节更少。



回到这题上面来，数位上不能有4也不能有连续的62，没有4的话在枚举的时候判断一下，不枚举4就可以保证状态合法了，所以这个约束没有记忆化的必要，而对于62的话，涉及到两位，当前一位是6或者不是6这两种不同情况我计数是不相同的，所以要用状态来记录不同的方案数。

dp[pos]\[sta]表示当前第pos位，前一位是否是6的状态，这里sta只需要去0和1两种状态就可以了，不是6的情况可视为同种，不会影响计数。

```c++
#include <iostream>
#include <string>
using namespace std;

int dp[10][2]; //dp[i][j]表示，当前第i位，前一位是否是6的状态
int a[20];
int l,r,tot;

//pos表示当前位置，pre表示前一个数，sta表示当前状态，也就是之前是否为6
//lim表示当前是否是有限制的，比如967，当我们第一个数选择9时，第二个数就只能选择0-6了
int dfs(int pos, int pre, int sta, int lim){
	int cur=0;
	if(pos==0) return 1; //如果执行到0了，当前构成的数可行
	if(!lim && dp[pos][sta]!=-1) return dp[pos][sta];
	int up = lim? a[pos]:9; //是否有限制判断
	for(int i=0; i<=up; i++){
		if(i==4 || (pre==6 && i==2)) //如果当前数字为4，或者前一个数字为6，当前位2，排除
			continue;
		cur += dfs(pos-1, i, i==6, lim&&i==a[pos]);
	}
	if(!lim) dp[pos][sta]=cur;
	return cur;
}

int solve(int x){
	tot = 0;	//tot用来记录位数
	while(x){
		a[++tot]=x%10;
		x /= 10;
	}
	return dfs(tot,-1,0,1);
}

int main(){
	while(~scanf("%d%d",&l,&r)&&(l+r)){
		memset(dp, -1, sizeof(dp));
		printf("%d\n", solve(r)-solve(l-1));
	}
	return 0;
}

```



### 【hdu 3555 Bomb】

> 题意：
> 统计1~n之间含有49的数字的个数(1 <= n <= 10000)\

```c++
#include <iostream>
#include <string>
using namespace std;

int dp[10][10];


void init(){
	memset(dp, 0, sizeof(dp));
	dp[0][0]=1;
	for(int i=1; i<=5; i++){
		for(int j=0; j<10; j++){
			for(int k=0; k<10; k++){
				if(!(j==4 && k==9))
					dp[i][j] += dp[i-1][k];
			}
		}
	}
}

int solve(int n){
	init();
	int num[10];
	int ans=0;
	int tot=1;
	while(n){
		num[tot++] = n%10;
		n /= 10;
	}
	for(int i=tot; i>=1; i--){
		for(int j=0; j<num[i]; j++){
			if(!(j==9 && num[i+1]==4))
				ans += dp[i][j];
		}
		if(num[i]==9 && num[i+1]==4)
			break;
	}
	return ans;
}

int main(){
	int n;
	while(~scanf("%d",&n)){
		cout<<n - solve(n)<<endl;
	}
	return 0;
}
```



```c++
#include <iostream>
#include <string>
using namespace std;

const int N=20;
int dp[N][10][2]; //dp[i][j][z],i表示当前位数，j表示上一位，istrue表示是否符合49
int dig[N];

int dfs(int pos, int pre, int istrue, int limit){
	cout<<limit<<endl;
	if(pos < 0) return istrue;
	if(!limit && dp[pos][pre][istrue]!=-1)
		return dp[pos][pre][istrue];
	int last = limit? dig[pos]:9;
	int ret = 0;
	for(int i=0; i<=last; i++){
		ret += dfs(pos-1, i, istrue || (pre==4 && i==9), limit && (i==last));
	}
	if(!limit){
		dp[pos][pre][istrue] = ret;
	}
	return ret;
}

int solve(int n){
	int len=0;
	while(n){
		dig[len++] = n%10;
		n /= 10;
	}
	return dfs(len-1, 0, 0, 1); //从高位开始递归
}

int main(){
	memset(dp, -1, sizeof(dp));
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		cout<<solve(n)<<endl;
	}
	return 0;
}
```


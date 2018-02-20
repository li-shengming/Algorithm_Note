﻿/*
 *	威佐夫博弈
 */

/*
取石子 (四） 
时间限制：1000 ms  |  内存限制：65535 KB 
难度：4 
描述 
有两堆石子，数量任意，可以不同。游戏开始由两个人轮流取石子。游戏规定，每次有两种不同的取法，一是可以在任意的一堆中取走任意多的石子；二是可以在两堆中同时取走相同数量的石子。最后把石子全部取完者为胜者。现在给出初始的两堆石子的数目，如果轮到你先取，假设双方都采取最好的策略，问最后你是胜者还是败者。 
输入 
输入包含若干行，表示若干种石子的初始情况，其中每一行包含两个非负整数a和b，表示两堆石子的数目，a和b都不大于1,000,000,000。 
输出 
输出对应也有若干行，每行包含一个数字1或0，如果最后你是胜者，则为1，反之，则为0。 
样例输入 
2 1 8 4 4 7 样例输出 
0 1 0


#include <iostream>
#include <string>
using namespace std;

int main(){
	int m,n;
	while(cin>>m>>n){
		if(m>n)
			swap(m,n);
		int k = n-m;
		int data = floor(k*(1.0+sqrt(5.0))/2.0);
		if(data==m)
			cout<<0<<endl;
		else
			cout<<1<<endl;
	}
	return 0;
}
*/

/*
Wythoff Game 
时间限制：1000 ms  |  内存限制：65535 KB 
难度：1 
描述 
最近ZKC同学在学博弈，学到了一个伟大的博弈问题--威佐夫博弈。 
相信大家都学过了吧？没学过？没问题。我将要为你讲述一下这个伟大的博弈问题。 有两堆石子，数量任意，可以不同。游戏开始由两个人轮流取石子。 游戏规定，每次有两种不同的取法： 
一是可以在任意的一堆中取走任意多的石子； 二是可以在两堆中同时取走相同数量的石子。 最后把石子全部取完者为胜者。 
我们今天要做的是求前n个必败态。 
什么是必败态？比如我们把（a，b）称为一种状态，a，b分别为两堆石子中所剩的数目。如果a=0，b=0，我们说该种状态为必败态，因为我不能再进行游戏，即使是可以进行，那也是必败的，你知道，游戏的我们都是非常聪明的。（0,0）（1,2）（3,5）...都是必败态，我们今天要做的就是求前n个必败态。不会？好吧！ 
我再告诉你：假设第n个必败态为（a，b）a为前n-1个必败态中没有出现的最小自然数，b=a+n。这下大家应该明白了吧。好吧，我们的任务就的要前n个必败态。规定第0个必败态为（0,0）。 
输入 
多组数据。 
输入为一个数n（0<=n<=100000）。 
输出 
按照要求求出前n个必败态。输出格式看下面样例。 
样例输入 
  3 
  1 
  样例输出 
  (0,0)(1,2)(3,5)(4,7) 
  (0,0)(1,2) 
  

#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
using namespace std;

typedef struct node{
	int a,b;
}N;

N res[100001];

int main(){
	int n;
	res[0].a = 0;
	res[0].b = 0;
	for(int i=1; i<100001; i++){
		res[i].a = (1+sqrt(5))*i/2;
		res[i].b = res[i].a+i;
	}
	while(scanf("%d",&n)!=EOF){
		for(int i=0; i<=n; i++){
			printf("(%d,%d)", res[i].a, res[i].b);
		}
		printf("\n");
	}
	return 0;
}
*/


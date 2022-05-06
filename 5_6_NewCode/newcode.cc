#include<iostream>
#include<math.h>

using namespace std;

//标题：猴子分桃
/*
 *【猴子分桃】老猴子辛苦了一辈子，给那群小猴子们留下了一笔巨大的财富——一大堆桃子。老猴子决定把这些桃子分给小猴子。
第一个猴子来了，它把桃子分成五堆，五堆一样多，但还多出一个。它把剩下的一个留给老猴子，自己拿走其中的一堆。
第二个猴子来了，它把桃子分成五堆，五堆一样多，但又多出一个。它把多出的一个留给老猴子，自己拿走其中的一堆。
后来的小猴子都如此照办。最后剩下的桃子全部留给老猴子。
这里有n只小猴子，请你写个程序计算一下在开始时至少有多少个桃子，以及最后老猴子最少能得到几个桃子。
 * */

int main()
{
  int n;
  while(cin>>n){
    if(n==0){
      break;
    }
    long total=pow(5,n)-4;   //总共的桃子个数
    int left=pow(4,n)+n-4;     //老猴子最少得到的桃子个数
    cout<<total<<" "<<left<<endl; 
  }
  return 0;
}

//HJ3 明明的随机数
/*
 *描述
明明生成了NN个1到500之间的随机整数。请你删去其中重复的数字，即相同的数字只保留一个，把其余相同的数去掉，然后再把这些数从小到大排序，按照排好的顺序输出。

数据范围： 1 \le n \le 1000 \1≤n≤1000  ，输入的数字大小满足 1 \le val \le 500 \1≤val≤500 
 * */

#include<iostream>
#include<set>

using namespace std;

int main()
{
    int n;
    while(cin>>n){
        set<int> st;
        for(int i=0;i<n;++i){
            int tmp;
            cin>>tmp;
            st.insert(tmp);
        }
        for(const auto& e:st){
            cout<<e<<endl;
        }
    }
    return 0;
}

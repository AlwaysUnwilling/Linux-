#include<iostream>
#include<vector>

using namespace std;

//标题：求正数数组的最小不可组成和
/*
 *给定一个全是正数的数组arr，定义一下arr的最小不可组成和的概念： 1，arr的所有非空子集中，把每个子集内的所有元素加起来
会出现很多的值，其中最小的记为min，最大的记为max； 2，在区间[min,max]上，如果有一些正数不可以被arr某一个子集相加得到，那么这些正数中最小的那
个，就是arr的最小不可组成和； 3，在区间[min,max]上，如果所有的数都可以被arr的某一个子集相加得到，那么max+1是arr的最小不可组成和；
 * */

//动态规划

class Solution {
public:
	/**
	 *	正数数组中的最小不可组成和
	 *	输入：正数数组arr
	 *	返回：正数数组中的最小不可组成和
	 */
    //将问题转化为在数组dp中j(min<=j<=max)个空间中最大能存放arr数组中的元素和
	int getFirstUnFormedNum(vector<int> arr, int len) {
        int min=arr[0];
        int max=0;
        for(const auto& e:arr){
            if(e<min){
                min=e;
            }
            max+=e;
        }
        vector<int> dp(max+1,0);
        for(int i=0;i<len;++i){
            for(int j=max;j>=arr[i];--j){        
                //由于数组中的每个元素只能存放一次，因此如果顺序更新dp可能会造成重复存放元素
                //因此需要逆序存放:例如dp[3]=dp[3]+3; dp[6]=dp[3]+3;
                dp[j]=std::max(dp[j],dp[j-arr[i]]+arr[i]);
            }
        }
        for(int i=min;i<max+1;++i){
            if(i!=dp[i]){
                return i;
            }
        }
        return max+1;
    }
};

//标题：有假币
/*
 *居然有假币！ 现在猪肉涨了，但是农民的工资却不见涨啊，没钱怎么买猪肉啊。nowcoder这就去买猪肉，结果找来的零钱中有假币！！！可
惜nowcoder 一不小心把它混进了一堆真币里面去了。只知道假币的重量比真币的质量要轻，给你一个天平（天平两端能容纳无限个硬币），请用最快的时间把那个
可恶的假币找出来。
 * */

#include<iostream>

using namespace std;

//三分法：每次都分成三堆：其中保证俩堆数量相等：n/3的余数只能是0、1、2，我们可以分为：
//   1、余数为0；正好三分；2、余数为1或2，我们把余数不为0的都处理为给其中俩个数各+1；
int main()
{
    int n;
    while(cin>>n){
        if(n==0){
            break;
        }
        int count=0;
        while(n>1){
            count++;
            n=n/3+(n%3==0?0:1);
        }
        cout<<count<<endl;
    }
    return 0;
}

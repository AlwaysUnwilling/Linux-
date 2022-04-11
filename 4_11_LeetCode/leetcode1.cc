#include<iostream>
#include<set>

using namespace std;

//357. 统计各位数字都不同的数字个数
//给你一个整数 n ，统计并返回各位数字都不同的数字 x 的个数，其中 0 <= x < 10n 。

//暴力
class Solution {
public:
    int GetMaxNum(int n)
    {
        int ret=1;
        while(n--){
            ret*=10;
        }
        return ret;
    }
    int countNumbersWithUniqueDigits(int n) {
        int max=GetMaxNum(n);
        int count=0;
        for(size_t i=0;i<max;++i){
            if(i/10==0){
                count++;
                continue;
            }
            set<int> st;
            int tmp=i;
            while(tmp/10){
                bool flag=st.insert(tmp%10).second;
                if(flag){
                    tmp/=10;
                    if(tmp/10==0 && st.insert(tmp).second){
                        count++;
                    }
                }else{
                    break;
                }
            }
        }
        return count;
    }
};

//排列组合:
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) {
            return 1;
        }
        if (n == 1) {
            return 10;
        }
        int ans = 10, cur = 9;
        for (int i = 0; i < n - 1; ++i) {
            cur *= 9 - i;
            ans += cur;
        }
        return ans;
    }
};

//动态规划
/*
n=0，数字有{0}1个。

n=1，数字有{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}9个。

n=2，数字包括两部分之和，一部分为n=1的所有9个答案，另一部分为长度为2的新增数字。为长度为2的新增数字可以在n=1的所 有9个数字基础上进行拼接。例如：

从n=1的数字列表{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}中随便取出一个除0以外的数字（因为0不能作为起始数字！），我们取2好了。通过在2的尾巴处拼接一位数字可以得到新的合法数字有：

{20， 21，23，24，25，26，27，28，29}，

可以看到，除了不能在尾巴处拼接一个2（两个连续的2就非法了！），0-9种一共有9个数字可以拿来拼接在尾巴处。新增答案为9个。同理，对于n=1数字列表{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}中的其他任意非0数也可以进行拼接操作，一共可以新增9*9个答案。

最终，n=2的合法数字，n=1时的答案+ 长度为2的数字之和（新增9*9个答案）= 10 + 81 = 91。

n=3时同理，只不过此时可以用拼接的数字减少为了8个，此时答案为10 + 9 * 9 + 9 * 9 * 8 = 739。

n=4时同理，只不过此时可以用拼接的数字减少为了7个，此时答案为10 + 9 * 9 + 9 * 9 * 8 + 9 * 9 * 8 * 7 = 5275。

通过归纳不难得到，假设 dp[i] 即 n = i时的答案，则动态转移方程为：

dp[i] = dp[i-1] + (dp[i-1] - dp[i-2])*(11-i)

转移的初始条件为

dp[0] = 1

dp[1] = 10
*/

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n==0){
            return 1;
        }
        int* dp=new int[n+1];
        dp[0]=1;
        dp[1]=10;
        for(size_t i=2;i<=n;++i){
            dp[i]=dp[i-1]+(dp[i-1]-dp[i-2])*(10-i+1);
        }
        int ret=dp[n];
        delete [] dp;
        return ret;
    }
};<Paste>


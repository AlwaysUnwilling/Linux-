#include<iostream>
#include<vector>

using namespace std;

//【微信红包】
/*
 *春节期间小明使用微信收到很多个红包，非常开心。在查看领取红包记录时发现，某个红包金额出现的次数超过了红包总数的一半。请帮小明找到该红包金额。写出
具体算法思路和代码实现，要求算法尽可能高效。
给定一个红包的金额数组 gifts 及它的大小 n ，请返回所求红包的金额。
若没有金额超过总数的一半，返回0。
 * */

class Gift {
public:
  int getValue(vector<int> gifts, int n) {
    if(n==0) return 0;
    if(n==1) return gifts[0];
    int ret=0;
    int count=0;
    for(auto e:gifts){
      if(count==0){
        ret=e;
        count++;
      }else{
        if(ret==e){
          count++;
        }else{
          count--;
        }
      }
    }
    count=0;
    for(auto e:gifts){
      if(e==ret){
        count++;
      }
    }
    return count*2>n?ret:0;
  }
};

//AB37 最长上升子序列(一)
/*
 *描述
 给定一个长度为 n 的数组 arr，求它的最长严格上升子序列的长度。
 * */

/*
 *将其分解为子问题，即分解成求解n个 以0到n-1下标的数为结尾的子序列的最大长度的问题。
可以用一个dp数组保存每个数做结尾时对应的最大长度。
假设一个以第i个元素arr[i]结尾的子序列Si，那么Si的长度是由i在Si中的前一个元素arr[j]决定的，Si的长度就等于Sj的长度加一。
这前面一个数arr[j]必须要满足两个条件：
  arr[j]<arr[i],这样才能构成严格上升
  dp[j]的值在i之前的所有dp中最大，这样我们求的才是最大长度。
 * */

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    vector<int> dp(n,1);//以i下标的数为结尾的子序列的长度
    
    for(int i=1;i<n;i++){
        int mx=0;
        for(int j=0;j<i;j++){
            //每一个元素的dp值==在它之前的，比它小的元素中最大的dp值加一
            if(arr[i]>arr[j])
                mx=max(mx,dp[j]);
        }
        dp[i]=mx+1;
    }
    int res=1;
    for(int i=0;i<n;i++)
        res=max(res,dp[i]);
    cout<<res;
    return 0;
}


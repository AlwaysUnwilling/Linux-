#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

//699. 掉落的方块
/*
 *在二维平面上的 x 轴上，放置着一些方块。

给你一个二维整数数组 positions ，其中 positions[i] = [lefti, sideLengthi] 表示：第 i 个方块边长为 sideLengthi ，其左侧边与 x 轴上坐标点 lefti 对齐。

每个方块都从一个比目前所有的落地方块更高的高度掉落而下。方块沿 y 轴负方向下落，直到着陆到 另一个正方形的顶边 或者是 x 轴上 。一个方块仅仅是擦过另一个方块的左侧边或右侧边不算着陆。一旦着陆，它就会固定在原地，无法移动。

在每个方块掉落后，你必须记录目前所有已经落稳的 方块堆叠的最高高度 。

返回一个整数数组 ans ，其中 ans[i] 表示在第 i 块方块掉落后堆叠的最高高度。
 * */

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> ans(positions.size());
        int height=0;
        int width=0;
        for(int i=0;i<positions.size();++i){
            int left1=positions[i][0];
            int right1=positions[i][1]+positions[i][0];
            ans[i]=positions[i][1];  //记录当前方块的高度及它所在的左右坐标
            //遍历i前的所有方块的左右坐标是否与i方块有重合
            //有重合则更新ans[i]的高度;无重合则更新新的高度ans[i]
            for(int j=0;j<i;++j){    
                int left2=positions[j][0];
                int right2=positions[j][1]+positions[j][0];
                if(right1>left2 && right2>left1){
                    ans[i]=max(ans[i],positions[i][1]+ans[j]);
                }
            }
        }
        for(int i=1;i<ans.size();++i){
            ans[i]=max(ans[i],ans[i-1]);
        }
        return ans;
    }
};

//467. 环绕字符串中唯一的子字符串
/*
 *把字符串 s 看作 "abcdefghijklmnopqrstuvwxyz" 的无限环绕字符串，所以 s 看起来是这样的：

"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd...." 。
现在给定另一个字符串 p 。返回 s 中 不同 的 p 的 非空子串 的数量 。 
 * */


class Solution {
public:
    int findSubstringInWraproundString(string p) {
        if(p.size()==0){
            return 0;
        }
        vector<int> count(26);
        int k=0;
        for(int i=0;i<p.size();++i){
            if(i && (p[i]-p[i-1]+26)%26==1){
                k++;
            }else{
                k=1;
            }
            count[p[i]-'a']=max(count[p[i]-'a'],k);
        }
        int num=0;
        for(const auto& e:count){
            num+=e;
        }
        return num;
    }
};

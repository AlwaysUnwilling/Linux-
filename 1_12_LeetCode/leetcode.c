/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Wed 12 Jan 2022 07:07:26 PM CST
    > About:数组形式的整数加法:对于非负整数 X 而言，X 的数组形式是每位数字按从左到右的顺序形成的数组。例如，如果 X = 1231，那么其数组形式为 [1,2,3,1]。

给定非负整数 X 的数组形式 A，返回整数 X+K 的数组形式。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-to-array-form-of-integer
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<stdio.h>

int* addToArrayForm(int* num, int numSize, int k, int* returnSize) {
    int* res = malloc(sizeof(int) * fmax(10, numSize + 1));
    *returnSize = 0;
    for (int i = numSize - 1; i >= 0; --i) {
        int sum = num[i] + k % 10;
        k /= 10;
        if (sum >= 10) {
            k++;
            sum -= 10;
        }
        res[(*returnSize)++] = sum;
    }
    for (; k > 0; k /= 10) {
        res[(*returnSize)++] = k % 10;
    }
    for (int i = 0; i < (*returnSize) / 2; i++) {
        int tmp = res[i];
        res[i] = res[(*returnSize) - 1 - i];
        res[(*returnSize) - 1 - i] = tmp;
    }
    return res;
}


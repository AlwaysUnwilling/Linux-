#include<iostream>
#include<vector>

using namespace std;

//标题：杨辉三角的变形
/*
 *            1
 *          1 1 1
 *        1 2 3 2 1
 *      1 3 6 7 6 3 1
 *    1 4 10 16 19 16 10 4 1
 *以上三角形的数阵，第一行只有一个数1，以下每行的每个数，是恰好是它上面的数、左上角数和右上角的数，3个数之和（如果不存在某个数，认为该数就是0）。
求第n行第一个偶数出现的位置。如果没有偶数，则输出-1。例如输入3,则输出2，输入4则输出3，输入2则输出-1。
 * */


int FindIndex_1(int n)
{
  //生成杨辉三角
  int m=2*n-1; //第n行元素的个数
  vector<vector<int>> ivv(n,vector<int>(m,0));
  ivv[0][0]=1;
  for(int i=0;i<n;++i){
    ivv[i][0]=ivv[i][2*i]=1;//第一列和最后一列赋值为1；
    for(int j=1;j<2*i;++j){
      if(j==1){ //第二列
        ivv[i][j]=ivv[i-1][j-1]+ivv[i-1][j];
      }else if(j==2*i-1){
        //倒数第二列
        ivv[i][j]=ivv[i-1][j-2]+ivv[i-1][j-1];
      }else{
        ivv[i][j]=ivv[i-1][j-2]+ivv[i-1][j-1]+ivv[i-1][j];
      }
    }
  }
  for(int i=0;i<m;++i){
    if(ivv[n-1][i]%2==0){
      return i+1;
    }
  }
  return -1;
}
int FindIndex_2(int n)
{
  if(n<=2) return -1;  //前俩行没有偶数
  //奇数行的第二列一定是偶数
  //偶数行（4的倍数）的偶数在第3个位置；其他偶数都在第四个位置
  if(n%2==1) return 2;
  if(n%4==0) return 3;
  return 4;
}
int main()
{
  int n,index=0;
  while(cin>>n){
    index=FindIndex_1(n);
    cout<<index<<endl;
  }
  return 0;
}

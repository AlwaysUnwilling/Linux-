#include<iostream>
#include<vector>
#include<string>

//标题：最近公共祖先:
//【最近公共祖先】
//将一棵无穷大满二叉树的结点按根结点一层一层地从左往右编号，根结点编号为1。现给定a，b为两个结点。设计一个算法，返回a、b最近的公共祖先的编号。注意其祖先也可能是结点本身。

class LCA {
public:
int getLCA(int a, int b) {
// write code here
	if(a==1 || b==1){
	return 1;
	}
	set<int> ap;
	while(a/2){
		ap.insert(a/2);
		a/=2;
	}
	while(b/2){
		int tmp=b/2;
		auto it=ap.find(tmp);
		if(it!=ap.end()){
			return tmp;
		}
		b/=2;
	}
	return -1;
	}
};


//标题：求最大连续bit数 :
//【求最大连续bit数】
//求一个int类型数字对应的二进制数字中1的最大连续数，例如3的二进制为00000011，最大连续2个1

int Get1Nums(int n)
{
  int max=0;
  int tmp=1;
  for(size_t i=1;i<32;++i){
  if(n&tmp){
  int count=0;
  while(n&tmp){
  count++;
  tmp=(tmp<<1);
  }
  if(max<count){
  max=count;
  }
  }else{
  tmp=(tmp<<1);
  }
  }
  return max;
  }
int main()
{
  int n=0;
  std::cin>>n;
  std::cout<<Get1Nums(n)<<std::endl;
  return 0;
}


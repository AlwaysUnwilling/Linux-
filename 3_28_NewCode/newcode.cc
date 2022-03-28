#include<iostream>
#include<vector>
#include<string>


/*下面程序的输出结果是 B
int x = 1;
do{
printf("%2d\n",x++);
}while(x--);
char p1[15]= "abcd",*p2= "ABCD", str[50]= "xyz";
strcpy(str+2,strcat(p1+2,p2+1));
printf("%s",str);
#include<iosteam.h>
void main(){
int n[][3] = {10,20,30,40,50,60};
int (*p)[3];
p=n;
cout<<p[0][0]<<","<<*(p[0]+1)<<","<<(*p)[2]<<endl;<Paste>
}
A 10,30,50
B 10,20,30
C 20,40,60
D 10,30,60
*/
/*解析：数组n是一个俩行三列的二维数组；p是一个数组指针，该指针指向具有三个int类型元素的一段
连续空间。数组名表示数组首元素的地址，n中的第一个元素的类型是int[3];n的二维数组中，首元素
的地址就是int[3];即p=n就是让p指针指向int[3];所以p[0][0]=10;*(p[0]+1)=p[0][1]=20;
(*p)[2]=p[0][2]=20;*/

/*：统计回文:
【统计回文】“回文串”是一个正读和反读都一样的字符串，比如“level”或者“noon”等等就是回文串。花花非常喜欢这种拥有对称美的回文串，生日的时候她
得到两个礼物分别是字符串A和字符串B。现在她非常好奇有没有办法将字符串B插入字符串A使产生的字符串是一个回文串。你接受花花的请求，帮助她寻找有多少
种插入办法可以使新串是一个回文串。如果字符串B插入的位置不同就考虑为不一样的办法。*/

bool IsPalString(std::string& str)
{
  int left=0;
  int right=str.size()-1;
  while(left<right)
  {
    if(str[left]!=str[right])
    {
      return false;
		}
		++left;
		--right;
	}
	return true;
}
int GetPalNums(std::string& A,std::string& B)
{
  int count =0;
  std::string tmp;
  for(size_t i=0;i<=A.size();++i)
  {
    tmp=A;
    if(IsPalString(tmp.insert(i,B)))
    {
      count++;
    }
  }
  return count;
}
int main()
{
  std::string A;
  std::string B;
  std::cin>>A;
  std::cin>>B;
  std::cout<<GetPalNums(A,B)<<std::endl;
  return 0;
}


/*标题：连续最大和:
【连续最大和】一个数组有 N 个元素，求连续子数组的最大和。*/

void VectorInit(std::vector<int>& v,size_t& n)
{
  std::cin>>n;
  v.resize(n);
  for(size_t i=0;i<n;++i)
  {
    std::cin>>v[i];
  }
}
int GetSubVecMax(std::vector<int>& v)
{
  int sum = 0;
  int end = 0;
  int negMax = 0;
  int max = 0;
  while(end<v.size())
  {
    if (end == 0 && v[end]<0) {
      negMax = v[end++];
      while(end < v.size() && v[end] < 0)
      {
        if (negMax < v[end])
        {
          negMax = v[end];
        }
        end++;
      }
      if(end>=v.size())
      {
        return negMax;
      }
    }
    else
    {
      if (sum + v[end] >= 0)
      {
        sum += v[end++];
        if (max < sum)
        {
          max = sum;
        }
        while (end<v.size() && sum + v[end] >= 0)
        {
          sum += v[end++];
          if (max < sum)
          {
            max = sum;
          }
        }
        sum = 0;
      }
      else
      {
        end++;
      }
    }
  }
  return max;
}
int main()
{
  size_t n=0;
  std::vector<int> v;
  VectorInit(v,n);
  std::cout<<GetSubVecMax(v)<<std::endl;
  return 0;
}


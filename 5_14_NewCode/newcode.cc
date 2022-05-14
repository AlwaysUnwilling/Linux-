#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

//标题：收件人列表
/*
 *【收件人列表】NowCoder每天要给许多客户写电子邮件。正如你所知，如果一封邮件中包含多个收件人，收件人姓名之间会用一个逗号和空格隔开；如果收件人姓
名也包含空格或逗号，则姓名需要用双引号包含。
现在给你一组收件人姓名，请你帮他生成相应的收件人列表。
 * */

int main()
{
  int n;
  while(cin>>n){
    vector<string> nameList(n,"");
    string name;
    getchar();
    for(int i=0;i<n;++i){
      getline(cin,name);
      nameList[i]=name;
    }
    for(int i=0;i<n;++i){
      if(nameList[i].find(' ')!=string::npos || nameList[i].find(',')!=string::npos){
        cout<<"\""<<nameList[i]<<"\"";
      }else{
        cout<<nameList[i];
      }
      if(i<n-1){
        cout<<", ";
      }
    }
    cout<<endl;
  }
  return 0;
}

//标题：养兔子
/*
 *一只成熟的兔子每天能产下一胎兔子。每只小兔子的成熟期是一天。 某人领养了一只小兔子，请问第N天以后，他将会得到多少只兔子。
 * */

string AddString(const string& s1,const string& s2)
{
	if(s1.size()==0 || s2.size()==0){
		return s1.size()>s2.size()?s1:s2;
	}
	int end1=s1.size()-1;
	int end2=s2.size()-1;
	int next=0;
	string sum;
	while(end1>=0 && end2>=0){
		int tmp=next+(s1[end1--]-'0')+(s2[end2--]-'0');
		if(tmp>9){
			tmp-=10;
			next=1;
		}else{
			next=0;
		}
		sum+=tmp+'0';
	}
	while(end1>=0){
		int tmp=next+(s1[end1--]-'0');
		if(tmp>9){
			tmp-=10;
			next=1;
		}else{
			next=0;
		}
		sum+=tmp+'0';
	}
	while(end2>=0){
		int tmp=next+(s2[end2--]-'0');
		if(tmp>9){
			tmp-=10;
			next=1;
		}else{
			next=0;
		}
		sum+=tmp+'0';
	}
	if(next!=0){
		sum+=next+'0';
	}
	reverse(sum.begin(),sum.end());
	return sum;
}
string RabbitNum(int n)
{
	if(n==1){
		return "1";
	}
	if(n==2){
		return "2";
	}
	string s1("1");
	string s2("2");
	string sum;
	for(int i=3;i<=n;++i){
		sum=AddString(s1,s2);
		s1=s2;
		s2=sum;
	}
	return sum;
}
int main()
{
	int n;
	while(cin>>n){
		cout<<RabbitNum(n)<<endl;
	}
	return 0;
}


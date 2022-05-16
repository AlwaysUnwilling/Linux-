#include<iostream>
#include<unordered_set>

using namespace std;

//年会抽奖
/*
今年公司年会的奖品特别给力，但获奖的规矩却很奇葩：
1. 首先，所有人员都将一张写有自己名字的字条放入抽奖箱中；
2. 待所有字条加入完毕，每人从箱中取一个字条；
3. 如果抽到的字条上写的就是自己的名字，那么“恭喜你，中奖了！”
现在告诉你参加晚会的人数，请你计算有多少概率会出现无人获奖？
 * */

/*
 *该题为经典的问题：**错排问题**

用A、B、C……表示写着ｎ位友人名字的信封，a、b、c……表示ｎ份相应的写好的信纸。把错装的总数为记作D(n)。假设把**ａ错装进Ｂ里了**，包含着这个错误的一切错装法分两类：  

- b装入Ａ里，这时每种错装的其余部分都与A、B、a、b无关，应有D(n－2)种错装法。  
- ｂ装入A、B之外的一个信封，这时的装信工作实际是把（除a之外的）n－1份信纸ｂ、ｃ……装入（除B以外的）n－1个信封A、C……，显然这时装错的方法有D(n－1)种。  

 总之在ａ装入B的错误之下，共有错装法D(n－2)＋D(n－1)种。  

 a装入C，装入D……的n－2种错误之下，同样都有D(n－1)＋D(n－2)种错装法，因此D(n)＝(n－1)[D(n－1)＋D(n－2)]

   D(n) = (n-1) [D(n-2) + D(n-1)]  

   特殊地，D(1) = 0, D(2) = 1.

 * */

int main()
{
    long long d[21]={0,0,1};
    long long f[21]={1,1,2};
    for(int i=3;i<=20;++i){
        d[i]=(i-1)*(d[i-1]+d[i-2]);
        f[i]=f[i-1]*i;
    }
    int n=0;
    while(cin>>n){
        double ret=100.0*d[n]/f[n];
        printf("%0.2f\%\n",ret);
    }
    return 0;
}


//抄送列表
/*
NowCoder每天要处理许多邮件，但他并不是在收件人列表中，有时候只是被抄送。他认为这些抄送的邮件重要性比自己在收件人列表里的邮件低，因此他要过滤掉这些次要的邮件，优先处理重要的邮件。
现在给你一串抄送列表，请你判断目标用户是否在抄送列表中。
 * */

int main()
{
    string name;
    size_t end=0;
    while(getline(cin,name)){
        size_t i=0;
        unordered_set<string> s;
        while(i<name.size()){
            if(name[i]=='\"'){
                end=name.find('\"',i+1);
                s.insert(name.substr(i+1,end-i-1));
                i=end+2;
            }else{
                end=name.find(',',i+1);
                if(end==string::npos){
                    s.insert(name.substr(i,name.size()));
                    break;
                }
                s.insert(name.substr(i,end-i));
                i=end+1;
            }
        }
        getline(cin,name);
        if(s.find(name)!=s.end()){
            cout<<"Ignore"<<endl;
        }else{
            cout<<"Important!"<<endl;
        }
    }
    return 0;
}


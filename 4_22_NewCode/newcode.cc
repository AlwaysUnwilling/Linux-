#include<iostream>
#include<vector>
#include<string>
#include<deque>
#include<algorithm>

using namespace std;

//【洗牌】
/*
 *洗牌在生活中十分常见，现在需要写一个程序模拟洗牌的过程。 现在需要洗2n张牌，从上到下依次是第1张，第2张，第3张一直到第2n张。首先，我们把
这2n张牌分成两堆，左手拿着第1张到第n张（上半堆），右手拿着第n+1张到第2n张（下半堆）。接着就开始洗牌的过程，先放下右手的最后一张牌，再放下左手
的最后一张牌，接着放下右手的倒数第二张牌，再放下左手的倒数第二张牌，直到最后放下左手的第一张牌。接着把牌合并起来就可以了。 例如有6张牌，最开始牌
的序列是1,2,3,4,5,6。首先分成两组，左手拿着1,2,3；右手拿着4,5,6。在洗牌过程中按顺序放下了6,3,5,2,4,1。把这六张牌再次合成一组牌之后，我们按照从上往下
的顺序看这组牌，就变成了序列1,4,2,5,3,6。 现在给出一个原始牌组，请输出这副牌洗牌k次之后从上往下的序列。
 * */

void Shuffle(vector<int>& v,int n,int k)
{
	while(k--){
		int left=n-1;
		int right=2*n-2;
		while(left>=1 && right>left){
			int start=left;
			int tmp=v[start];
			while(start<right){
				v[start]=v[start+1];
				start++;
			}
			v[start]=tmp;
			left--;
			right-=2;
		}
	}
}
int main()
{
	int T=0;
	int n=0;
	int k=0;
	cin>>T;
	while(T--){
		vector<int> v;
		cin>>n>>k;
		for(int i=0;i<2*n;++i){
			int tmp;
			cin>>tmp;
			v.push_back(tmp);
		}
		Shuffle(v,n,k);
		for(int i=0;i<2*n;++i){
			cout<<v[i];
			if(i+1<2*n){
				cout<<" ";
			}
		}
		cout<<endl;
	}
	return 0;
}

//【MP3光标位置】
/*
 *MP3 Player因为屏幕较小，显示歌曲列表的时候每屏只能显示几首歌曲，用户要通过上下键才能浏览所有的歌曲。为了简化处理，假设每屏只能显示4首歌曲，光标
初始的位置为第1首歌。
现在要实现通过上下键控制光标移动来浏览歌曲列表，控制逻辑如下：
歌曲总数<=4的时候，不需要翻页，只是挪动光标位置。
光标在第一首歌曲上时，按Up键光标挪到最后一首歌曲；光标在最后一首歌曲时，按Down键光标挪到第一首歌曲。
2. 歌曲总数大于4的时候（以一共有10首歌为例）：
特殊翻页：屏幕显示的是第一页（即显示第1 – 4首）时，光标在第一首歌曲上，用户按Up键后，屏幕要显示最后一页（即显示第7-10首歌），同时光标放到最后一
首歌上。同样的，屏幕显示最后一页时，光标在最后一首歌曲上，用户按Down键，屏幕要显示第一页，光标挪到第一首歌上。
一般翻页：屏幕显示的不是第一页时，光标在当前屏幕显示的第一首歌曲时，用户按Up键后，屏幕从当前歌曲的上一首开始显示，光标也挪到上一首歌曲。光标当
前屏幕的最后一首歌时的Down键处理也类似.
其他情况，不用翻页，只是挪动光标就行。
 * */

void PrintS(string s,int n)
{
  deque<int> dq;
  for(int i=1;i<=4;++i){
    dq.push_back(i);
  }
  int index=1;
  for(auto e:s){
    if(n<=4){
      if(e=='U'){
        index--;
        if(index==0){
          index=n;
        }
      }else{
        index++;
        if(index>n){
          index=1;
        }
      }
    }else{
      if(e=='U'){
        if(index==dq.front()){
          dq.pop_back();
          dq.push_front(index-1);
        }
        index--;
        if(index==0){
          index=n;
          dq.clear();
          int tmp=0;
          while(tmp<4){
            dq.push_front(index-tmp);
            tmp++;
          }
        }
      }else{
        if(index==dq.back()){
          dq.pop_front();
          dq.push_back(index+1);
        }
        index++;
        if(index>n){
          index=1;
          int tmp=0;
          dq.clear();
          while(tmp<4){
            dq.push_back(index+tmp);
            tmp++;
          }
        }
      }
    }
  }
  if(n<=4){
    for(int i=1;i<=n;++i){
      cout<<i<<" ";
    }
    cout<<endl;
  }else{
    for(auto e:dq){
      cout<<e<<" ";
    }
    cout<<endl;
  }
  cout<<index<<endl;
}
int main()
{
  int n=0;
  string s;
  cin>>n>>s;
  PrintS(s,n);
  return 0;
}

#pragma once 

#include<iostream>
#include<string.h>
#include<algorithm>
#include<assert.h>

namespace my_string
{
    class string
    {
    public:
        typedef char* iterator;
        typedef const char* const_iterator;
        string(const char *str="")
        :_str(new char[strlen(str)+1])
        {
            strcpy(_str,str);
            _size=_capacity=strlen(str);
        }
        /*string(const string &str)
            :_str(new char[strlen(str._str)+1])
        {
            strcpy(_str,str._str);
        }
        string& operator=(const string &str)
        {
            if(this!=&str){
                delete[] _str;
                _str=new char[strlen(str._str)+1];
                strcpy(_str,str._str);
            }
            return *this;
        }*/
        /*string& operator=(const char *str)
        {
            if(_str!=str){
                delete[] _str;
                _str=new char[strlen(str)+1];
                strcpy(_str,str);
            }
            return *this;
        }*/

        //现代写法：
        //s1(s)
        string(const string &s)
        :_str(nullptr)
        {
            string tmp(s._str);
            std::swap(_str,tmp._str);
            std::swap(_size,tmp._size);
            std::swap(_capacity,tmp._capacity);
        }
        //s1=s2
        string& operator=(string &s)
        {
            std::swap(_str,s._str);
            std::swap(_size,s._size);
            std::swap(_capacity,s._capacity);
            return *this;
        }
        const char* c_str()
        {
            return _str;
        }
          
        iterator begin()
        {
            return _str;
        }
        const_iterator begin()const
        {
            return _str;
        }
        iterator end()
        {
            return _str+_size;
        }
        const_iterator end()const
        {
            return _str+_size;
        }

        char& operator[](int i)
        {
            assert(i<_size);
            return _str[i];
        }
        const char& operator[](int i)const
        {
            assert(i<_size);
            return _str[i];
        }
        int size()const 
        {
            return  _size;
        }
        int capacity()
        {
            return _capacity;
        }
        bool empty()
        {
            return _size==0;
        }
        void reserve(int size)
        {
            if(size>_capacity){
                char* str=new char[size+1];
                strncpy(str,_str,_size+1);
                delete[] _str;
                _capacity=size;
                _str=str;
            }
        }
        void resize(int size,char ch='\0')
        {
            if(size<=_size){
                _size=size;
                _str[size]='\0';
            }else{
                if(size>_capacity){
                    reserve(size);
                }
                for(int i=_size;i<size;++i){
                    _str[i]=ch;
                }
                _str[size]='\0';
                _size=size;
            }
        }
        void push_back(char x)
        {
            if(_size==_capacity){
                reserve(_capacity==0?4:_capacity*2);
            }
            _str[_size]=x;
            ++_size;
            _str[_size]='\0';
        }
        string& operator+=(const char& c)
        {
            push_back(c);
            return *this;
        }
        string& operator+=(const char* s)
        {
            append(s);
            return *this;
        }
        void append(const string& s)
        {
            int len=_size+s._size;
            if(len>_capacity){
                reserve(len);
            }
            strcpy(_str+_size,s._str);
            _size=len;
        }
        string& insert(int pos,const char ch)
        {
            assert(pos<=_size);
            if(_size==_capacity){
                reserve(_capacity*2);
            }
            char* end=_str+_size;
            while(end>=_str+pos){
                *(end+1)=*end;
                --end;
            }
            _str[pos]=ch;
            _size++;
            return *this;
        }
        string& insert(int pos,const char* s)
        {
            assert(pos<=_size);
            int len=_size+strlen(s);
            if(len>_capacity){
                reserve(len);
            }
            char* end=_str+_size;
            while(end>=_str+pos){
                *(end+strlen(s))=*end;
                --end;
            }
            strncpy(_str+pos,s,strlen(s));
            _size+=strlen(s);
            return *this;
        }
        bool operator>(const string& s)
        {
            int begin=0;
            while(begin<_size && begin<s._size){
                if(_str[begin]>s._str[begin]){
                    return true;
                }else{
                    if(_str[begin]<s._str[begin]){
                        return false;
                    }
                    ++begin;
                }
            }
            while(begin<_size){
                return true;
            }
            return false;
        }
        string& erase(int pos,int len=npos)
        {
            assert(pos<_size);
            if(pos+len>=_size){
                _str[pos]='\0';
                _size=pos;
            }else{
                int end=pos+len;
                while(pos+len<=_size){
                    _str[pos]=_str[pos+len];
                    pos++;
                }
                _size-=len;
            }
            return *this;
        }
        int find(char ch,int size=0)
        {
            for(int i=0;i<_size;++i){
                if(_str[i]==ch){
                    return i;
                }
            }
            return -1;
        }
        
        char* find(const char* s,int size=0)
        {
            assert(size<_size);
            if(strlen(s)==0 || _size==0){
                return nullptr;
            }
           return  strstr((this->_str)+size,s);
        }

        bool operator==(const string& s)
        {
            int begin=0;
            while(begin<_size && begin <s._size){
                if(_str[begin] != s._str[begin]){
                    return false;
                }
                ++begin;
            }
            while(begin==_size && begin==s._size){
                return true;
            }
            return false;
        }
        bool operator<(const string& s)
        {
            return !(*this>s || *this==s);
        }
        bool operator>=(const string& s)
        {
            return *this==s || *this>s;
        }
        bool operator<=(const string& s)
        {
            return *this<s || *this==s;
        }
        bool operator!=(const string& s)
        {
            return !(*this==s);
        }
        void clear()
        {
            _size=0;
            _str[0]='\0';
        }
        ~string()
        {
            delete[] _str;
        }
    private:
        char *_str;
        int _size;
        int _capacity;
        static size_t npos;
    };
   /* 
    std::ostream& operator<<(std::otream& out,const string& s)
    {
        for(int i=0;i<s.size();++i){
            out<<s[i];
        }
        return out;
    }
    std::istream& operator>>(std::istream& in,string& s)
    {
        s.clear();
        //in>>ch;//iostream中in>>会把' '和'\n' 自动忽略掉，下面的循环是拿不到' '和'\n'的会进入死循环中
        while(1){
            char ch=in.get();
            if(ch==' ' || ch=='\n'){
                break; 
            }
            s+=ch;
        }
        return in;
    }*/

    std::ostream& operator<< (std::ostream& out, const string& s)
	{
		for (int i = 0; i < s.size(); ++i)
		{
			out << s[i];
		}
		return out;
	}
	std::istream& operator>> (std::istream& in, string& s)
	{
        s.clear();
		while (1)
		{
			char ch;
			//ch = getchar();
			ch = in.get();
			if (ch == '\n' || ch==' ')
				break;
			else
				s += ch;
		}
		return in;
	}

    size_t string::npos=-1;

    void  MyStringTest1()
    {
        string s1="hello world";
        std::cout<<s1.c_str()<<std::endl;
        string s2(s1);
        std::cout<<s2.c_str()<<std::endl;
        string s3("hello linux!");
        std::cout<<s3.c_str()<<std::endl;
        s3=s1;
        std::cout<<s3.c_str()<<std::endl;
    }
    void MyStringTest2()
    {
        string s1("hello world!");
        for(int i=0;i<s1.size();++i){
            std::cout<<s1[i]<<" ";
        }
        std::cout<<std::endl;
        for(auto ch:s1){
            std::cout<<ch<<" ";
        }
        std::cout<<std::endl;
        string::iterator it=s1.begin();
        while(it!=s1.end()){
            std::cout<<*it<<" ";
            ++it;
        }
        std::cout<<std::endl;
        for(int i=0;i<s1.size();++i){
            s1[i]='x';
        }
        for(auto ch:s1){
            std::cout<<ch<<" ";
        }
        std::cout<<std::endl;
    }
    void MyStringTest3()
    {
        string s1("hello world!");
        s1.push_back('$');
        std::cout<<s1.c_str()<<std::endl;
        s1.append("hello linux!");
        std::cout<<s1.c_str()<<std::endl;
        s1.resize(3);
        std::cout<<s1.c_str()<<std::endl;
        s1.resize(20);
        std::cout<<s1.c_str()<<"size:"<<s1.size()<<std::endl;
        s1.insert(0,'A');
        std::cout<<s1.c_str()<<std::endl;
        s1.insert(3,"Have a nice day!");
        std::cout<<s1.c_str()<<std::endl;
    }
    void MyStringTest4()
    {
        string s1("hello");
        string s2("h");
        string s3("helloworld");
        string s4("hellooo");
        std::cout<<(s1==s2)<<std::endl;
        std::cout<<(s3>s4)<<std::endl;
    }
    void MyStringTest5()
    {
        string s1("hello world");
        string ret=s1.erase(0,1);
        std::cout<<ret.c_str()<<std::endl;
        ret=s1.erase(0,2);
        std::cout<<ret.c_str()<<std::endl;
    }
    void MyStringTest6()
    {
        string s1("hello world!");
        const char* str="llo";
        std::cout<<s1.find(' ')<<std::endl;
        std::cout<<s1.find(str)<<std::endl;
    }
    void MyStringTest7()
    {
        string s1("today is a nice day!");
        std::cout<<s1<<std::endl;
        s1.resize(40);
        s1+="!!!!!!";
        std::cout<<s1<<std::endl;

        std::cin>>s1;
        std::cout<<s1<<std::endl;
        string s2;
        std::cin>>s1>>s2;
        std::cout<<s1<<" "<<s2<<std::endl;
    }
}

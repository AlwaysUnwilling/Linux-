#include<iostream>
#include<string>
#include<vector>
#include<semaphore.h>
#include<functional>

using namespace std;

//1114. 按序打印
/*
 *给你一个类：

public class Foo {
  public void first() { print("first"); }
  public void second() { print("second"); }
  public void third() { print("third"); }
}
三个不同的线程 A、B、C 将会共用一个 Foo 实例。

线程 A 将会调用 first() 方法
线程 B 将会调用 second() 方法
线程 C 将会调用 third() 方法
请设计修改程序，以确保 second() 方法在 first() 方法之后被执行，third() 方法在 second() 方法之后被执行。
 * */

class Foo {
public:
    Foo() {
        sem_init(&firstcond,0,0);
        sem_init(&secondcond,0,0);
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        sem_post(&firstcond);
    }

    void second(function<void()> printSecond) {
        
        sem_wait(&firstcond);
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        sem_post(&secondcond);
    }

    void third(function<void()> printThird) {
        sem_wait(&secondcond);
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
private:
    sem_t firstcond;
    sem_t secondcond;
};

//22. 括号生成
/*
 *数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
 * */

class Solution {
public:
    bool islegal(string& str)
    {
        if(str.size() == 0){
            return true;
        }
        int left = 0;
        int right = 0;
        for(const auto& e:str){
            if(e=='('){
                left++;
            }else{
                right++;
            }
            if(left < right){
                return false;
            }
        }
        return left==right;
    }
    void generateTmp(vector<string>& vs,string& tmp,int n)
    {
        if(tmp.size()==n){
            if(islegal(tmp)){
                vs.push_back(tmp);
            }
            return ;
        }
        tmp+='(';
        generateTmp(vs,tmp,n);
        tmp.pop_back();
        tmp+=')';
        generateTmp(vs,tmp,n);
        tmp.pop_back();
    }
    vector<string> generateParenthesis(int n) {
        vector<string> vs;
        string tmp;
        generateTmp(vs,tmp,n*2);
        return vs;
    }
};

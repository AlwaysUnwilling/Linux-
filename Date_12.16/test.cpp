/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 16 Dec 2021 06:30:13 PM CST
 ************************************************************************/

#include"date.hpp"


int main()
{
    //Date d1(2021,2,28);
    //d1.Print();
    
    //Date d2;
    //d2=d1;
    //d2.Print();

    //Date d3(d1);
    //d3.Print();
    //(d3+100).Print();
    Date d;
	d.Print();
	//Date d1(2020,2,30);
	//d1.Print();
	Date d2(2020, 3, 28);
	d2.Print();
	Date d3 = d2 + 100;
	d3.Print();
	d3 += 10;
	d3.Print();
	d3 = d2;   //也可以连续赋值 int i=0,j=1,k=2;  i=j=k;连续赋值这里是从右往左执行，j=k这个表达式右个返回值是j，然后j在赋值给i
	d3.Print();
	d3 += 100;
	d3.Print();
	d3 -= 10;
	d3.Print();
	d3 --;
	d3.Print();
	d3++;
	d3.Print();
	++d3;
	d3.Print();
	--d3;
	d3.Print();
	
    int ret=d3-d2;
    std::cout<<ret<<std::endl;
    return 0;
}



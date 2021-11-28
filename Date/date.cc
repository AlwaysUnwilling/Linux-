#include<iostream>
using namespace std;


class Date
{
public:
	int GetMonthDay(int year, int month)
	{
		static int MonthDays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month==2 && ((year%4==0 && year%100!=0)|| year%400==0))
			return 29;
		else
		{
			return MonthDays[month];
		}
	}
	Date(int year = 0, int month = 1, int day = 1)
	{
		if (year >= 0 && month >= 1 && month <= 12 && day >= 1 && day <= GetMonthDay(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "非法日期" << endl;
		}
           
		
	}
	Date(const Date& d)  //引用权限缩小使用const 避免d1被误改
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	inline bool operator==(const Date& d)
	{
		return _year == d._year     //这里相当于 d1._year==d.year  ==>  this->_year==d.year;
			&& _month == d._month
			&& _day == d._day;
	}
	bool operator<(const Date& d)
	{
		if (_year < d._year) return true;
		else if (_year == d._year && _month < d._month) return true;
		else if (_year == d._year && _month == d._month && _day < d._day) return true;
		else return false;
	}
	bool operator>(const Date& d)
	{
		return !(*this <= d);
	}
	bool operator<=(const Date& d)
	{
		return *this < d || *this == d;//复用上面的来实现；
	}
	bool operator>=(const Date& d)
	{
		return !(*this < d);
	}
	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}
	Date operator+(int day)
	{
		//Date ret = d2;
		Date ret(*this);
		ret._day += day;    // ==> ret.operator+=(int day);
		//while (ret._day > GetMonthDay(ret._year, ret._month))   //代码冗余  复用Date& operator+=(int day)  实现
		//{
		//	//如果日期不合法就需要往月上进位
		//	ret._day -= GetMonthDay(ret._year, ret._month);
		//	ret._month++;
		//	if (ret._month == 13)
		//	{
		//		ret._year++;
		//		ret._month = 1;
		//	}
		//}
		return ret;
	}
	Date& operator+=(int day)
	{
		if (day < 0)
		{
			return *this -= -day;
		}
		_day += day;
		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month == 13)
			{
				_year++;
				_month = 1;
			}
		}
		return *this;
	}
	Date& operator-=(int day)   //d3-=day
	{
		if (day < 0)
		{
			return *this += -day;
		}
		_day -= day;
		while (_day <= 0)
		{
			_month--;
			if (_month == 0)
			{
				_year--;
				_month = 12;
			}
			_day += GetMonthDay(_year, _month);
		}
		return *this;
	}
	Date operator-(int day)    //d3-=10
	{
		Date ret = *this;
		ret._day -= day;   // ==> ret.operator-=(int day);
		/*while (ret._day <= 0)     //代码冗余  复用Date& operator-=(int day)  实现
		{
			ret._month--;
			if (ret._month == 0)
			{
				ret._year--;
				ret._month = 12;
			}
			ret._day += GetMonthDay(_year, _month);
		}*/
		return ret;
	}
	Date& operator--()   //--d3    默认是前置--
	{
		/*_day--;*/
	/*	while (_day <= 0)
		{
			_month--;
			if (_month == 0)
			{
				_year--;
				_month = 12;
			}
			_day += GetMonthDay(_year, _month);
		}*/
		* this -= 1;
		return *this;
	}
	Date operator--(int)  //后置--   为了构成重载函数
	{
		Date tmp = (*this);
		*this -= 1;
		return tmp;   //返回减之前的
	}
	Date& operator++()  //++ d3  //++d3    默认是前置++
	{
		/*_day++;*/
		/*while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month == 12)
			{
				_year++;
				_month = 1;
			}
		}*/
		* this += 1;
		return *this;
	}
	Date operator++(int)  //d3++   后置++   为了构成重载函数
	{
		Date tmp = (*this);
		* this += 1;
		return tmp;   //返回加之前的
	}
	Date& operator=(const Date& d)  //在自定义类型传参和返回值时，在可以的情况下尽量使用引用。可以减少拷贝构造函数的调用
	{
		if (this != &d)  //防止自己给自己赋值  无意义
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
	int operator-(const Date& d)  //日期减日期
	{
		int flag = -1;//判断相减完后相差天数的正负
		int n = 0;
		Date smaller = *this;  //拷贝构造
		Date Greater = d;
		if (*this > d)
		{
			smaller = d;    //赋值 Date& operator=(const Date& d)
			Greater = *this;
			flag = 1;
		}
		while (smaller != Greater)
		{
			++smaller;
			n++;
		}
		return n*flag;
	}
	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
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
	
	cout << (d3 - d2) << endl;
	//cout << (d1 == d2) << endl;
	//cout << (d1 > d2) << endl;
	//cout << (d1 < d2) << endl;
	//cout << (d1 != d2) << endl;
	//cout << (d1 >= d2) << endl;
	//cout << (d1 <= d2) << endl;
	return 0;
}

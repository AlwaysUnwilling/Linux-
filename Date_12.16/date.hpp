#pragma once
#include<iostream>


class Date
{
public:
    int GetMonthDay(int year,int month)
    {
        static int day_Array[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
        if(month==2 && (year%400==0 || (year%4==0 && year%100!=0))){
            day_Array[2]=29;
        } 
        return day_Array[month];
    }
    Date(int year=0,int month=1,int day=1):
         _year(year),
         _month(month),
         _day(day)
    {
        if(year<0){
            std::cout<<"year error"<<std::endl;
            exit(-1);
        }
        if(month<=0 || month>=13){
            std::cout<<"month error"<<std::endl;
            exit(-1);
        }
        if(day>GetMonthDay(year,month) || day<=0){
            std::cout <<"day error"<<std::endl;
            exit(-1);
        }
    }

    void Print()
    {
        std::cout<<_year<<"-"<<_month<<"-"<<_day<<std::endl; 
    }

    Date& operator=(Date& d)
    {
        if(this==&d){
            return *this;
        }
        this->_year=d._year;
        this->_month=d._month;
        this->_day=d._day;
        return *this;
    }

    Date(const Date& d)
    {
        this->_year=d._year;
        this->_month=d._month;
        this->_day=d._day;
    }

    Date operator+(int day)
    {
        Date tmp=*this;
        tmp._day+=day;
        while(tmp._day>GetMonthDay(tmp._year,tmp._month)){
            tmp._day-=GetMonthDay(tmp._year,tmp._month);
            tmp._month++;
            if(tmp._month>12){
                tmp._year++;
                tmp._month=1;
            }
        }
        return tmp;
    }

    Date& operator+=(int day)
    {
        _day+=day;
        while(_day>GetMonthDay(_year,_month)){
            _day-=GetMonthDay(_year,_month);
            _month++;
            if(_month>12){
                _year++;
                _month=1;
            }
        }
        return *this;
    }

    Date operator-(int day)
    {
        Date tmp=*this;
        while(tmp._day<=day){
            tmp._month--;
            if(tmp._month<=0){
                tmp._year--;
                tmp._month=12;
            }
            tmp._day+=GetMonthDay(tmp._year,tmp._month);
        }
        tmp._day-=day;
        return tmp;
    }

    Date& operator-=(int day)
    {
        if(day<0){
            return *this+=-day;
        }
        while(_day<=day){
            _month--;
            if(_month<=0){
                _month=12;
                _year--;
                if(_year<0){
                    _year=0;
                }
            } 
            _day+=GetMonthDay(_year,_month);
        }
        _day-=day;
        return *this;
    }

    bool operator>(Date& d)
    {
        if(_year>d._year){
            return true;
        }else if(_year==d._year){
            if(_month>d._month){
                return true;
            }else if(_month==d._month){
                if(_day>d._day){
                    return true;
                }
            }
        }
        return false;
    }

    bool operator==(Date& d)
    {
        return _year==d._year
        && _month==d._month
        && _day==d._day;
    }

    bool operator<(Date& d)
    {
        return !(*this>d || *this==d);
    }

    bool operator!=(Date& d)
    {
        return !(*this==d);
    }

    bool operator<=(Date& d)
    {
        return !(*this>d);
    }

    bool operator>=(Date& d)
    {
        return !(*this<d);
    }

    Date& operator++()
    {
        _day++;
        if(_day>GetMonthDay(_year,_month)){
            _day-=GetMonthDay(_year,_month);
            _month++;
            if(_month>12){
                _month=1;
                _year++;
            }
        }
        return *this;
    }
    
    Date operator++(int)
    {
        Date tmp(*this);
        tmp+=1;
        return *this;
    }

    Date& operator--()
    {
        _day--;
        if(_day<=0){
            _month--;
            if(_month<=0){
                _month=12;
                _year--;
            }
            _day+=GetMonthDay(_year,_month);
        }
        return *this;
    }
    
    Date operator--(int)
    {
        Date tmp(*this);
        tmp-=1;
        return *this;
    }


    int operator-(Date& d)
    {
        int count=0;
        int flag=1;
        Date greater(*this);
        Date smaller(d);
        if(*this<d){
            greater=d;
            smaller=*this;
            flag=-1;
        }
        while(smaller<greater){
            ++smaller;
            count++;
        }
        return count*flag;
    }

private:
    int _year;
    int _month;
    int _day;
};

#include<iostream>

using namespace std;

//24505-有理数运算
/*
 *实现对两个有理数的基本运算，包括加、减、乘、除。

输入描述：

每个输入文件只包含一个测试用例，测试用例会给出一行数据，格式为“a1/b1 a2/b2”

分子分母的范围都在长整型的范围内，如果数字为负，则符号只会出现在分子的前面。分母一定是非零数。

输出描述：

针对每个测试用例，都输出四行，分别是这两个有理数的和、差、积和商，格式为“数1 操作符 数2 = 结果”。注意，所有的有理数都将遵循一个简单形式“k a/b”，其中k是整数部分，a/b是最简分数形式，如果该数为负数，则必须用括号包起来。如果除法中的除数为0，则输出“Inf”。结果中所有的整数都在long int的范围内。
 * */

typedef long long int64;
class Rational
{
public:
    Rational(int64 n, int64 d)
    {
        negetive = false;
        isZero = false;
        
        // 在输入时分母永远不可能为0，但是经过运算之后分母可能为0
        if(0 == d)
        {
            isZero = true;
            return;
        }
        
        // 分子小于0，表示为负数
        if(n < 0)
        {
            negetive = !negetive;
        }
        
        // 在输入时分母一定不会小于0， 但是经过计算之后分母也可能会小于0
        if(d < 0)
        {
            negetive = !negetive;
        }
        
        // 如果分数是假分数，必须要将其化简为真分数  比如：5 / 3----> 1 2/3
        integer = n / d;
        numerator = n - integer*d;
        denominator = abs(d);
        
        // 如果不是最简的分数，还需要将其化简为最简的分数： 10 / 15 ----> 2 / 3
        // 只需给分子和分母分别除分子和分母最大公约数
        if(numerator < -1 || numerator > 1)
        {
            int gcd = CalcGCD(abs(numerator), denominator);
            if(gcd)
            {
                numerator /= gcd;
                denominator /= gcd;
            }
        }
        
        totalnumerator = integer*denominator + numerator;
    }
    
    Rational operator+(const Rational& r)const
    {
        int64 n = totalnumerator*r.denominator + r.totalnumerator*denominator;
        int64 d = denominator * r.denominator;
        return Rational(n, d);
    }
    
    Rational operator-(const Rational& r)const
    {
        int64 n = totalnumerator*r.denominator - r.totalnumerator*denominator;
        int64 d = denominator * r.denominator;
        return Rational(n, d);
    }
    
    Rational operator*(const Rational& r)const
    {
        int64 n = totalnumerator*r.totalnumerator;
        int64 d = denominator * r.denominator;
        return Rational(n, d);
    }
    
    Rational operator/(const Rational& r)const
    {
        int64 n = totalnumerator*r.denominator;
        int64 d = denominator * r.totalnumerator;
        return Rational(n, d);
    }
private:
    // 求最大公约数：辗转相除
    int64 CalcGCD(int64 a, int64 b)
    {
        if(0 == b)
            return a;
        
        return CalcGCD(b, a%b);
    }
    
    friend ostream& operator<<(ostream& _cout, const Rational& r)
    {
        if(r.isZero)
        {
            _cout<<"Inf";
            return _cout;
        }
        
        if(0 == r.integer && 0 == r.numerator)
        {
            _cout<<"0";
            return _cout;
        }
        
        // 如果是负数，需要用()括起来
        if(r.negetive)
        {
            _cout<<"(-";
        }
        
        // 输出有理数：整数 + 分数
        // 整数: 可能存在也可能不存在
        if(r.integer)
        {
            _cout<<abs(r.integer);
            
            // 如果分数部分存在，整数和分数之间有一个空格
            if(r.numerator)
            {
                _cout<<" ";
            }
        }
        
        // 分数: 可能存在也可能不存在
        if(r.numerator)
        {
            _cout<<abs(r.numerator)<<"/"<<r.denominator;
        }
        
        if(r.negetive)
        {
            _cout<<")";
        }
        return _cout;
    }
    
private:
    int64 numerator;  // 分子
    int64 denominator;  // 分母
    int64 integer;      // 整数部分
    bool negetive;      // 负数
    bool isZero;        // 分母是否为0
    
    int64 totalnumerator;   // 参与运算的分子：原分子 + 整数部分
};

int main()
{
    int64 n1,d1,n2,d2;
    while(scanf("%lld/%lld %lld/%lld", &n1,&d1,&n2,&d2) != EOF)
    {
        Rational r1(n1,d1);
        Rational r2(n2,d2);
        cout<< r1 <<" + " << r2 << " = " << r1 + r2 << endl;
        cout<< r1 <<" - " << r2 << " = " << r1 - r2 << endl;
        cout<< r1 <<" * " << r2 << " = " << r1 * r2 << endl;
        cout<< r1 <<" / " << r2 << " = " << r1 / r2 << endl;
    }
    return 0;
}



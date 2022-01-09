#include<iostream>
#include<string>


using namespace std;

class Person
{
public:
    Person(const char* name="null")
    :_name(name)
    {}
    Person(const Person& s)
    :_name(s._name)
    {}
    Person& operator=(const Person& s)
    {
        if(this!=&s){
            _name=s._name;
        }
        return *this;
    }
    void PerPrint()
    {
        cout<<_name<<"/";
    }
    ~Person()
    {
        cout<<"~Person()"<<endl;
    }
protected:
    string _name;
};

class Student:public Person
{
public:
    Student(const char* s,int id)
    :Person(s)
    ,_stuID(id)
    {}

    Student(const Student& stu)
    :Person(stu)
    ,_stuID(stu._stuID)
    {}

    void StuPrint()
    {
        PerPrint();
        cout<<_stuID<<endl;
    }
    Student& operator=(const Student& stu)
    {
        if(this!=&stu){
            Person::operator=(stu);
            _stuID=stu._stuID;
        }
        return *this;
    }
    ~Student()
    {
        cout<<"~Student()"<<endl;
    }
private:
    int _stuID=31415926;
};


int main()
{
    Student s1("张三",18);
    s1.StuPrint();
    Student s2(s1);
    s2.StuPrint();
    Student s3("李四",20);
    s3.StuPrint();
    s3=s1;
    s3.StuPrint();
    return 0;
}

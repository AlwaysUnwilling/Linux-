#include<iostream>
#include<memory>
#include<thread>
#include<vector>
#include<windows.h>
#include<thread>
#include<mutex>
using namespace std;
namespace lazy_man
{
	// 懒汉模式 -- 第一次获取对象时，再创建对象
	class Singleton
	{
	public:
		static Singleton* GetInstance()
		{
			//::Sleep(1000);  增加没加锁时出现线程不安全的条件（2个以上线程同时过了判断条件）

			// 双检查
			if (_pinst == nullptr)
			{
				//_mtx.lock();
				unique_lock<mutex> lock(_mtx);
				if (_pinst == nullptr)
				{
					_pinst = new Singleton;
				}
				//_mtx.unlock();
			}

			// ...

			return _pinst;
		}

		static void DelInstance()
		{
			//unique_lock<mutex> lock(_mtx);
			delete _pinst;
			_pinst = nullptr;
		}

		Singleton(const Singleton& s) = delete;

	private:
		Singleton()
		{}

		static Singleton* _pinst;
		static mutex _mtx;
	};

	// 1、如果要手动释放单例对象，可以调用DelInstance
	// 2、如果需要程序结束时，正常释放单例对象，可以加入下面的设计
	class GC
	{
	public:
		~GC()
		{
			Singleton::DelInstance();
		}
	};

	static GC gc;


	Singleton* Singleton::_pinst = nullptr;
	mutex Singleton::_mtx;

	int x()
	{
		//Singleton s1;
		//Singleton s2;
		//cout << Singleton::GetInstance() << endl;
		//cout << Singleton::GetInstance() << endl;
		//cout << Singleton::GetInstance() << endl;
		//Singleton copy(*Singleton::GetInstance());

		vector<std::thread> vthreads;
		int n = 100;
		for (int i = 0; i < n; ++i)
		{
			vthreads.push_back(std::thread([]()
				{
					//cout << std::this_thread::get_id() <<":";
					cout << Singleton::GetInstance() << endl;
				}));
		}

		for (auto& t : vthreads)
		{
			t.join();
		}

		return 0;
	}
}

namespace hungry_man
{
	// 饿汉模式  一开始(main函数之前)就创建对象
	class Singleton
	{
	public:
		static Singleton* GetInstance()
		{
			return &_inst;
		}

		Singleton(const Singleton&) = delete;
	private:
		Singleton()
		{}

		static Singleton _inst;
	};

	Singleton Singleton::_inst;
	// static对象是在main函数之前创建的，这会只有主线程，所以不存在线程安全。


	int x()
	{
		//Singleton s1;
		//Singleton s2;
		//cout << Singleton::GetInstance() << endl;
		//cout << Singleton::GetInstance() << endl;
		//cout << Singleton::GetInstance() << endl;
		//Singleton copy(*Singleton::GetInstance());

		vector<std::thread> vthreads;
		int n = 10;
		for (int i = 0; i < n; ++i)
		{
			vthreads.push_back(std::thread([]()
				{
					//cout << std::this_thread::get_id() <<":";
					cout << Singleton::GetInstance() << endl;
				}));
		}

		for (auto& t : vthreads)
		{
			t.join();
		}

		return 0;
	}
}

//int main()
//{
//	hungry_man::x();
//
//	return 0;
//}

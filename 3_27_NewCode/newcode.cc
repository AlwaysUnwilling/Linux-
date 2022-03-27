#include<iostream>
#include<vector>
#include<string>

/*以下能对二维数组a进行正确初始化的语句是（B）
A int ta[2][] = { {0,1,2},{3,4,5} };
B int ta[][3] = { {0,1,2},{3,4,5} };  
C int ta[2][4] = { {0,1,2},{3,4},{5} };
D int ta[][3] = { {0,,2},{},{3,4,5} };*/
//解析：
//二维数组中，行可以省略，列不能省略。 排除A
//C选项中，数组ta是2行4列的二维数组，而它的初始化中初始化了三行，错误
//D选项中，二维数组的初始化必须是连续的初始化。

//设变量已正确定义，以下不能统计出一行中输入字符个数（不包含回车符）的程序段是（D）
//A n = 0; while (ch = getchar() != '\n')n++;
//B n = 0; while (getchar() != '\n')n++;
//C for (n = 0; getchar() != '\n'; n++);
//D n = 0; for (ch = getchar(); ch != '\n'; n++);
// 解析：for循环的初始化，只执行一次，因此D选项ch一直没有变化。

//32位系统中，定义 **a[3][4], 则变量占用内存空间为(B)。
//A 4
//B 48
//C 192
//D 12
//解析：
//**a[3][4]表示的是一个指针数组，这个数组是二维数组，三行四列，共有12个元素。每个元素都是一个指针，而
//32位系统中指针的大小的是4个字节，因此  **a[3][4]占用内存空间大小为：12*4=48

//假设在一个 32 位 little endian 的机器上运行下面的程序，结果是多少？（B）
//#include <stdio.h>
//int main() {
//    long long a = 1, b = 2, c = 3;
//    printf("%d %d %d\n", a, b, c);
//    return 0;
//}
//A 1, 2, 3
//B 1, 0, 2
//C 1, 3, 2
//D 3, 2, 1
//解析：
//大端：低位存高地址；小端：低位存低地址
//int i = 1;              大端：00 00 00 01
//          ------低地址---------------------------------->高地址
//                        小端：01 00 00 00
//long long  a = 1;       小端  01 00 00 00 00 00 00 00
//long long  b = 2;       小端  02 00 00 00 00 00 00 00
//long long  c = 3;       小端  03 00 00 00 00 00 00 00
//printf("%d %d %d\n", a, b, c) 调用的时候会创建函数栈帧：栈--高地址向低地址增长的
//------低地址---------------------------------- > 高地址 
//---------------------<-<-<-<--<-<---<-----------------函数调用栈
//	     栈顶                                         栈底
//	入栈是从右往左依次入栈，即：c先入栈，b，a的顺序
//	 01 00 00 00 00 00 00 00 02 00 00 00 00 00 00 00 03 00 00 00 00 00 00 00
//打印的时候从栈顶依次出栈：而"%d"打印是按4字节整型打印：因此打印每次只取栈顶4字节
//所以结果就是：01 00 00 00（1）；00 00 00 00（0）；02 00 00 00（2）

//标题：字符串中找出连续最长的数字串：
//【字符串中找出连续最长的数字串】读入一个字符串str，输出字符串str中的连续最长的数字串

#include<iostream>
#include<string>
#include<vector>
std::string GetStrMaxNumSize(std::string& str)
{
	int maxLength = 0;
	std::string retstr;
	int end = 0;
	while (end < str.size())
	{
		if (str[end] >= '0' && str[end] <= '9') {
			int tmpLength = 0;
			std::string tmp;
			while (str[end] >= '0' && str[end] <= '9')
			{
				tmp += str[end];
				tmpLength++;
				end++;
				if (end >= str.size())
				{
					break;
				}
			}
			if (maxLength < tmpLength)
			{
				maxLength = tmpLength;
				retstr = tmp;
			}
		}
		else
		{
			end++;
		}
	}
	return retstr;
}
int main()
{
	std::string str;
	std::cin >> str;
	std::cout << GetStrMaxNumSize(str) << std::endl;
	return 0;
}

//标题：数组中出现次数超过一半的数字:
//【数组中出现次数超过一半的数字】
//给一个长度为 n 的数组，数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
// 保证数组输入非空，且保证有解

//方法1：由于要求的数字是数组中出现次数超过一半的元素。因此对数组排列后，取中位数的下一个元素一定是该数字
//时间复杂度(O(N*log（N))）
#include<algorithm>
class Solution {
public:
	int MoreThanHalfNum_Solution(std::vector<int> numbers) {
		sort(numbers.begin(), numbers.end());
		int mid = ((numbers.size() - 1) > 1) + 1;
		return numbers[mid];
	}
};
//方法2：所有的数字在数组中出现次数超过数组元素的一半，因此将该数字成为众数，其他为非众数
//如果俩个数不相等，就消去这俩个数字，最坏的情况每次消去一个众数和一个非众数，那么最后留下来的
// 一定是众数即所求。如果数组中不一定存在众数，那么最后的结果不一定是众数，需要再进行遍历数字
// 统计该数字出现的次数和数组的大小对比，判断该数字是不是众数
//时间O(n)，空间O(1)
class Solution {
public:
	int MoreThanHalfNum_Solution(std::vector<int> numbers) {
		int count = 0;
		int ret = 0;
		for (auto e : numbers) {
			if (count == 0)
			{
				ret = e;
				count++;
			}
			else
			{
				if (ret == e)
				{
					count++;
				}
				else
				{
					count--;
				}
			}
		}
		return ret;
	}
};

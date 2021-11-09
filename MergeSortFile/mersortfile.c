#include"mersortfile.h"

void Swap(int* element1, int* element2)
{
	int tmp = *element1;
	*element1 = *element2;
	*element2 = tmp;
}
int GetMidIndex(int* a, int begin, int end)
{
	assert(a);
	int mid = (begin + end) / 2;
	if (a[begin] > a[mid])
	{
		if (a[mid] > a[end])
			return mid;
		else if (a[end] < a[begin])
			return end;
		else
			return begin;
	}
	else
	{
		if (a[begin] > a[end])
			return begin;
		else if (a[end] < a[mid])
			return end;
		else
			return mid;
	}
}
int PartSort3(int* a, int begin, int end)
{
	Swap(&a[GetMidIndex(a, begin, end)], &a[end]);
	int key = a[end];
	int cur = begin;
	int prev = begin - 1;
	while (cur < end)
	{
		if (a[cur] < key && ++prev != cur)
			Swap(&a[prev], &a[cur]);
		++cur;
	}
	Swap(&a[++prev], &a[cur]);
	return prev;
}
void QuickSort(int* a, int left, int right)
{
	assert(a);
	if (left >= right)
		return;
	int divindex = PartSort3(a, left, right);
	QuickSort(a, left, divindex - 1);
	QuickSort(a, divindex + 1, right);
}
void _MergeFile(const char* file1, const char* file2, const char* mfile)
{
	FILE* fout1 = fopen(file1, "r");
	if (fout1 == NULL)
	{
		printf("fout1文件打开失败\n");
		exit(-1);
	}
	FILE* fout2 = fopen(file2, "r");
	if (fout2 == NULL)
	{
		printf("fout2文件打开失败\n");
		exit(-1);
	}
	FILE* fin = fopen(mfile, "w");
	if (fin == NULL)
	{
		printf("文件打开失败\n");
		exit(-1);
	}
	int num1, num2;
	int ret1 = fscanf(fout1, "%d\n", &num1);
	int ret2 = fscanf(fout2, "%d\n", &num2);
	while (ret1 != EOF && ret2 != EOF)
	{
		if (num1 < num2)
		{
			fprintf(fin, "%d\n", num1);
			ret1 = fscanf(fout1, "%d\n", &num1);
		}
		else
		{
			fprintf(fin, "%d\n", num2);
			ret2 = fscanf(fout2, "%d\n", &num2);
		}
	}
	while (ret1 != EOF)
	{
		fprintf(fin, "%d\n", num1);
		ret1 = fscanf(fout1, "%d\n", &num1);
	}
	while (ret2 != EOF)
	{
		fprintf(fin, "%d\n", num2);
		ret2 = fscanf(fout2, "%d\n", &num2);
	}
	fclose(fout1);
	fclose(fout2);
	fclose(fin);
}
void MergeSortFile(const char* file)
{
	FILE* fout = fopen(file, "r");
	if (fout == NULL)
	{
		printf("文件打开失败\n");
		exit(-1);
	}
	//分割成一小段一小段的数据，内存排序后写入到小文件中去
	int n = 10;
	int a[10];
	int i = 0;
	int num = 0;
	char subfile[20];
	int filei = 1;
	while (fscanf(fout, "%d\n", &num) != EOF)
	{
		if (i < n-1)//前9个数据读完放到数组中，第10个数据在if语句结束时已经读到，但没有放进到数组中
		{
			a[i++] = num;
		}
		else
		{
			a[i] = num;//把第10个数据放进到数组中，数组中此时才有10个数据
			QuickSort(a, 0, n - 1);
			sprintf(subfile, "%d", filei++);
			FILE* fin = fopen(subfile, "w");
			if (fin == NULL)
			{
				printf("文件打开失败\n");
				exit(-1);
			}
		    for (int i = 0; i < n; i++)
			{
				fprintf(fin, "%d\n", a[i]);
			}
		   fclose(fin);
		   i = 0;

		}
	}
	//利用互相归并到文件，实现整体有序
	//...
	char mfile[100] = "12";
	char file1[100] = "1";
	char file2[100] ;
	for (int i = 2; i <= n; ++i)
	{
		sprintf(file2, "%d", i);
		//读取file1和file2，进行归并出mfile
		_MergeFile(file1, file2, mfile);
		strcpy(file1, mfile);
		//sprintf(file2, "%d", i + 1);
		sprintf(mfile, "%s%d", mfile, i + 1);
	}
	fclose(fout);
}

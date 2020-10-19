
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int currentSortSwaps = 0;

struct Student
{
	char name[3];
	int grade;
};
bool operator<(const Student& lhs, const Student& rhs)
{
	return lhs.grade < rhs.grade;
}
bool operator<=(const Student& lhs, const Student& rhs)
{
	return lhs.grade <= rhs.grade;
}
bool operator>(const Student& lhs, const Student& rhs)
{
	return lhs.grade > rhs.grade;
}
void generateRandomName(char name[3])
{
	for (int i = 0; i < 3; i++)
		name[i] = (char)(65 + rand() % 26);
}
void generateRandomGrade(int& grade)
{
	grade = 2 + rand() % 5;
}
vector<Student> generateRandomStudents(int n)
{
	vector<Student> v(n);
	for (int i = 0; i < n; i++)
	{
		generateRandomName(v[i].name);
		generateRandomGrade(v[i].grade);
	}

	return v;
}

template <class T>
void  Merge(T* arr1, int len1, T* arr2, int len2)
{

	T* result = new T[len1 + len2];
	int cursor1 = 0;
	int cursor2 = 0;
	int resultCursor = 0;
	while (cursor1<len1&&cursor2<len2)
	{
		if (arr1[cursor1] <= arr2[cursor2])
			result[resultCursor++] = arr1[cursor1++];
		else
			result[resultCursor++] = arr2[cursor2++];
	}
	while (cursor1<len1)
		result[resultCursor++] = arr1[cursor1++];


	while (cursor2<len2)
		result[resultCursor++] = arr2[cursor2++];


	//Въпреки,че arr1 е с по-малка големина, можем да си ползволим това да излезем извън масива, понеже знаем, че arr1 с arr2 са слепени     
	for (int i = 0; i<(len1 + len2); i++)
		arr1[i] = result[i];
	delete[] result;

}

template <class T>
void MergeSort(T* arr, int len)
{

	if (len <= 1)
		return;

	int mid = len / 2;

	MergeSort(arr, mid);
	MergeSort(arr + mid, len - mid);

	Merge<T>(arr, mid, arr + mid, len - mid);


}


template <class T>
void swap(T* arr, int i, int j)
{
	currentSortSwaps++;
	T temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

template <class T>
void BubbleSort(T* arr, int len)
{
	for (int j = 0; j<len; j++)
	{
		bool isSwapped = false;
		for (int i = 0; i<len - 1 - j; i++)
		{
			if (arr[i]>arr[i + 1])
			{
				swap(arr, i, i + 1);
				isSwapped = true;
			}
		}
		if (!isSwapped) 
			return;
	}
}

template <class T>
void SelectionSort(T* arr, int size)
{
	for (int i = 0; i<size - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j<size; j++)
		{
			if (arr[j]<arr[minIndex])
				minIndex = j;
		}
		if (i != minIndex)
			swap(arr, i, minIndex);
	}
}

void CountSortForGrades(Student* arr, int len)
{
	int* countArr = new int[5]; //2,3,4,5,6
	for (int i = 0; i < 5; i++)
		countArr[i] = 0;

	for (int i = 0; i < len; i++)
		countArr[arr[i].grade - 2]++;

	for (int i = 1; i < 5; i++)
		countArr[i] += countArr[i - 1];

	Student* result = new Student[len];
	for (int i = 0; i < len; i++)
	{
		Student currentStudent = arr[i];
		int index = countArr[currentStudent.grade - 2]--;
		result[index - 1] = currentStudent;
	}
	for (int i = 0; i < len; i++)
		arr[i] = result[i];
	delete[] result;

}

int main()
{
	vector<Student> v1, v2, v3, v4;
	v1 = v2 = v3 = v4 = generateRandomStudents(101000);

	std::cout << "Generated random students! Sorting..." << endl;
	clock_t begin, end;
	double elapsed;

	begin = clock();
	BubbleSort(&v1[0], v1.size());
	end = clock();
	elapsed = double(end - begin);
	std::cout << "Bubble sort: Time: " << elapsed << ", swaps: " << currentSortSwaps << endl;
	currentSortSwaps = 0;

	begin = clock();
	SelectionSort(&v2[0], v2.size());
	end = clock();
	elapsed = double(end - begin);
	std::cout << "Selection sort: Time: " << elapsed << ", swaps: " << currentSortSwaps << endl;
	currentSortSwaps = 0;

	begin = clock();
	MergeSort(&v3[0], v3.size());
	end = clock();
	elapsed = double(end - begin);
	std::cout << "Merge sort: Time: " << elapsed << endl;

	begin = clock();
	CountSortForGrades(&v4[0], v4.size());
	end = clock();
	elapsed = double(end - begin);
	std::cout << "Count sort: Time: " << elapsed << endl;
}
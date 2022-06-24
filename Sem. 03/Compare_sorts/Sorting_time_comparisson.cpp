
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

	return std::move(v);
}

template <class T> void merge(T* arr1, size_t len1, T* arr2, size_t len2);

template <class T>
void mergeSort(T* arr, int len)
{
	if (len <= 1)
		return;

	size_t mid = len / 2;

	mergeSort(arr, mid);
	mergeSort(arr + mid, len - mid);

	merge<T>(arr, mid, arr + mid, len - mid);

}

template <class T>
void merge(T* arr1, size_t arr1len, T* arr2, size_t arr2len)
{
	T* result = new T[arr1len + arr2len];

	size_t cursor1 = 0, cursor2 = 0, resultCursor = 0;

	while (cursor1 < arr1len && cursor2 < arr2len)
	{
		if (arr1[cursor1] <= arr2[cursor2])
			result[resultCursor++] = arr1[cursor1++];
		else
			result[resultCursor++] = arr2[cursor2++];
	}

	while (cursor1 < arr1len)
		result[resultCursor++] = arr1[cursor1++];

	while (cursor2 < arr2len)
		result[resultCursor++] = arr2[cursor2++];

	//Въпреки,че arr1 е с по-малка големина, можем да си ползволим това да излезем извън масива, понеже знаем, че arr1 с arr2 са слепени     
	for (size_t i = 0; i < (arr1len + arr2len); i++)
		arr1[i] = result[i];
	delete[] result;
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
void bubbleSort(T* arr, int len)
{
	for (int j = 0; j < len; j++)
	{
		size_t right = len - 1;
		size_t lastSwappedIndex = 0;

		for (int i = 0; i < right; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr, i, i + 1);
				lastSwappedIndex = i;
			}
		}

		right = lastSwappedIndex;
	}
}

template <class T>
void selectionSort(T* arr, size_t size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		size_t minIndex = i;

		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[minIndex])
				minIndex = j;
		}

		if (i != minIndex)
			swap(arr, i, minIndex);
	}
}
void countSortForGrades(Student* arr, size_t len)
{
	const size_t GRADES_VALUES_COUNT = 5;

	size_t* countArr = new size_t[GRADES_VALUES_COUNT]; //2,3,4,5,6

	for (int i = 0; i < GRADES_VALUES_COUNT; i++)
		countArr[i] = 0;

	for (int i = 0; i < len; i++)
		countArr[arr[i].grade - 2]++;

	for (int i = 1; i < GRADES_VALUES_COUNT; i++)
		countArr[i] += countArr[i - 1];

	Student* result = new Student[len];
	for (int i = 0; i < len; i++)
	{
		Student currentStudent = arr[i];
		size_t index = countArr[currentStudent.grade - 2]--;
		result[index - 1] = currentStudent;
	}

	for (int i = 0; i < len; i++)
		arr[i] = result[i];
	delete[] result;

}

int main()
{
	vector<Student> v1, v2, v3, v4;
	v1 = v2 = v3 = v4 = generateRandomStudents(20000);

	std::cout << "Generated " << v1.size() <<  " random students! Sorting..." << endl;
	clock_t begin, end;
	double elapsed;

	begin = clock();
	bubbleSort(&v1[0], v1.size());
	end = clock();
	elapsed = double(end - begin);
	std::cout << "Bubble sort: Time: " << elapsed << ", swaps: " << currentSortSwaps << endl;
	currentSortSwaps = 0;

	begin = clock();
	selectionSort(&v2[0], v2.size());
	end = clock();
	elapsed = double(end - begin);
	std::cout << "Selection sort: Time: " << elapsed << ", swaps: " << currentSortSwaps << endl;
	currentSortSwaps = 0;

	begin = clock();
	mergeSort(&v3[0], v3.size());
	end = clock();
	elapsed = double(end - begin);
	std::cout << "Merge sort: Time: " << elapsed << endl;

	begin = clock();
	countSortForGrades(&v4[0], v4.size());
	end = clock();
	elapsed = double(end - begin);
	std::cout << "Count sort: Time: " << elapsed << endl;
}
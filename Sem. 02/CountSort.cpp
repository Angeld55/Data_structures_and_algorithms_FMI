#include <iostream>
#include <string>
using namespace std;


struct Student
{
	std::string name;
	int grade;
};

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
	delete[] countArr;
}

//Homework task: make stable
int main()
{
	Student arr[] = { { "Petur", 4 }, { "Ivan", 6 }, { "Paul", 4 }, { "Vladimir", 5 }, { "Petq", 5 } };

	countSortForGrades(arr, 5);

	for (int i = 0; i < 5; i++)
		cout << "Name: "<< arr[i].name << ", grade: " << arr[i].grade << endl;

}

#include <iostream>
#include <string>
using namespace std;


struct Student
{
	std::string name;
	int grade;
};
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

//Homework task: make stable
int main()
{
	Student arr[] = { { "Petur", 4 }, { "Ivan", 6 }, { "Paul", 4 }, { "Vladimir", 5 }, { "Petq", 5 } };

	CountSortForGrades(arr, 5);

	for (int i = 0; i < 5; i++)
		cout << "Name: "<< arr[i].name << ", grade: " << arr[i].grade << endl;


}

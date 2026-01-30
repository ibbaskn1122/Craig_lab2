// ELEX-4618 Lab 2
// Ethan Bosiak A01314624

#include <iostream>
#include <cctype>
#include "CCourse.h"

using namespace std;

// Array of 100 students max
const int MAX_STUDENTS = 100;

// Struct containing grade variables
struct Student
{
	char studentNum[10];
	float lab;
	float quiz;
	float midterm;
	float final;
};

Student classList[MAX_STUDENTS];
int numStudents = 0;	// No students input on start

// Function prototypes
void print_menu();
void add_student();
void edit_student();
void print_grades();
float calculate_grade(const Student& s);
void input_data();

// Main
int main()
{
	CCourse course;
	char command;

	do
	{
		print_menu();
		cout << "CMD> "; // Prompt for user input
		cin >> command;
		command = toupper(command); // Convert lowercase inputs to uppercase

		// Assign inputs to functions with switch
		switch (command)
		{
		case 'A':
			course.addStudent();
			break;

		case 'E':
			course.editStudent();
			break;

		case 'D':
			course.deleteStudent();
			break;

		case 'P':
			course.printGrades();
			break;

		case 'S':
			course.saveClass();
			break;

		case 'L':
			course.loadClass();
			break;

		case 'Q':
			cout << "exiting program..." << endl;
			break;

		default:
			cout << "Invalid command. Try again." << endl;
		}
	} while (command != 'Q');

	return 0;
}

// Function definitions

// Main menu
void print_menu()
{
	cout << "****************************************" << endl;
	cout << "ELEX-4618 Grade System, by Ethan Bosiak" << endl;
	cout << "****************************************" << endl;
	cout << "(A)dd student" << endl;
	cout << "(E)dit student" << endl;
	cout << "(D)elete student" << endl;
	cout << "(P)rint grades" << endl;
	cout << "(S)ave class" << endl;
	cout << "(L)oad class" << endl;
	cout << "(Q)uit" << endl;
}

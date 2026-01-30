// ELEX-4618 Lab 2
// Ethan Bosiak A01314624

#pragma once

#include <vector>
#include <string>
#include "CStudent.h"

using namespace std;

class CCourse
{
private:
	vector<CStudent> _students;

	// Error checking on inputs
	static string promptStudentNum();
	static float promptGrade(const string& prompt);
	static int promptIndex(const string& prompt, int minVal, int maxVal);
	static string promptFilename(const string& prompt);

	// Validators
	static bool isValidStudentNum(const string& s);
	static bool tryParseGrade(const string& s, float& outGrade);

public:
	// Menu actions
	void addStudent();
	void editStudent();
	void deleteStudent();
	void printGrades() const;
	void saveClass();
	void loadClass();

	// Additional functionalities
	int getNumStudents() const;
};
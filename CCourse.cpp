// ELEX-4618 Lab 2
// Ethan Bosiak A01314624

#include "CCourse.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <regex>
#include <cctype>

using namespace std;

// Get number of students in course
int CCourse::getNumStudents() const
{
	return static_cast<int>(_students.size());
}

// Validate student number format
bool CCourse::isValidStudentNum(const string& s)
{
	// A00xxxxxx or A01xxxxxx (9 digits)
	// A0(0 or 1) + 6 digits
	static const regex pattern("^A0(0|1)[0-9]{6}$");
	return regex_match(s, pattern);
}

// Parse grade 0.0 to 100.0
bool CCourse::tryParseGrade(const string& s, float& outGrade)
{
	try
	{
		size_t idx = 0;
		double val = stod(s, &idx);

		if (idx != s.size())
			return false;

		if (val < 0.0 || val > 100.0)
			return false;

		outGrade = static_cast<float>(val);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

// Prompt for valid student number
string CCourse::promptStudentNum()
{
	while (true)
	{
		string input;
		cout << "Student Number (A00xxxxxx or A01xxxxxx): ";
		cin >> input;

		if (isValidStudentNum(input))
			return input;

		cout << "Invalid student number format. Please try again." << endl;
	}
}

// Prompt for valid grade
float CCourse::promptGrade(const string& prompt)
{
	while (true)
	{
		string input;
		cout << prompt;
		cin >> input;

		float grade = 0.0f;
		if (tryParseGrade(input, grade))
			return grade;

		cout << "Invalid grade. Please enter a number between 0.0 and 100.0." << endl;
	}
}

// Prompt for valid indexed grade
int CCourse::promptIndex(const string& prompt, int minVal, int maxVal)
{
	while (true)
	{
		string input;
		cout << prompt;
		cin >> input;

		try
		{
			size_t idx = 0;
			int val = stoi(input, &idx);
			if (idx != input.size())
				throw exception();
			
			if (val < minVal || val > maxVal)
			{
				cout << "Invalid input. Please enter a number between "
					<< minVal << " and " << maxVal << "." << endl;
				continue;
			}

			return val;

		}
		catch (...)
		{
			cout << "Invalid input. Please enter a number between "
				<< minVal << " and " << maxVal << "." << endl;
		}
	}
}

// Prompt for valid filename
string CCourse::promptFilename(const string& prompt)
{
	// Clear input buffer
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true)
	{
		string filename;
		cout << prompt;
		getline(cin, filename);

		// Trim whitespace
		while (!filename.empty() && isspace(static_cast<unsigned char>(filename.front())))
			filename.erase(filename.begin());
		while (!filename.empty() && isspace(static_cast<unsigned char>(filename.back())))
			filename.pop_back();

		if (!filename.empty())
			return filename;

		cout << "Invalid file name. Please try again." << endl;
	}
}

// Add student to course
void CCourse::addStudent()
{
	cout << "Adding student" << endl;

	CStudent s;
	s.setStudentNum(promptStudentNum());
	s.setLab(promptGrade("Lab Grade (0.0 - 100.0): "));
	s.setQuiz(promptGrade("Quiz Grade (0.0 - 100.0): "));
	s.setMidterm(promptGrade("Midterm Grade (0.0 - 100.0): "));
	s.setFinal(promptGrade("Final Exam Grade (0.0 - 100.0): "));

	_students.push_back(s);
}

// Edit existing student
void CCourse::editStudent()
{
	if (_students.empty())
	{
		cout << "No students to edit." << endl;
		return;
	}

	// Get selected student index
	int index = promptIndex("Student to edit: ", 1, static_cast<int>(_students.size()));
	CStudent& s = _students[index - 1];

	cout << "Editing student: " << s.getStudentNum() << endl;

	s.setStudentNum(promptStudentNum());
	s.setLab(promptGrade("Lab Grade (0.0 - 100.0): "));
	s.setQuiz(promptGrade("Quiz Grade (0.0 - 100.0): "));
	s.setMidterm(promptGrade("Midterm Grade (0.0 - 100.0): "));
	s.setFinal(promptGrade("Final Exam Grade (0.0 - 100.0): "));
}

// Delete student from course
void CCourse::deleteStudent()
{
	if (_students.empty())
	{
		cout << "No students to delete." << endl;
		return;
	}

	// Get selected student index
	int index = promptIndex("Student to delete: ", 1, static_cast<int>(_students.size()));
	_students.erase(_students.begin() + (index - 1));

	cout << "Student deleted." << endl;
}

// Print all student grades
void CCourse::printGrades() const
{
	cout << fixed << setprecision(2);

	cout << "#  Student    Lab   Quiz   Midterm   Final  Final Grade" << endl;

	for (int i = 0; i < static_cast<int>(_students.size()); i++)
	{
		const CStudent& s = _students[i];

		cout << (i + 1) << "  "
			<< s.getStudentNum() << "   "
			<< setw(5) << s.getLab() << "  "
			<< setw(5) << s.getQuiz() << "  "
			<< setw(8) << s.getMidterm() << "  "
			<< setw(5) << s.getFinal() << "  "
			<< setw(11) << s.calculateFinalGrade() << endl;
	}
}

// Save class to file
void CCourse::saveClass()
{
	string filename = promptFilename("Name of save file: ");

	ofstream out(filename);
	if (!out.is_open())
	{
		cout << "Error opening file for writing." << endl;
		return;
	}

	out << fixed << setprecision(2);
	for (const auto& s : _students)
	{
		out << s.getStudentNum() << " "
			<< s.getLab() << " "
			<< s.getQuiz() << " "
			<< s.getMidterm() << " "
			<< s.getFinal() << "\n";
	}

	cout << "Class saved to " << filename << endl;
}

// Load class from file	
void CCourse::loadClass()
{
	string filename = promptFilename("Name of load file: ");

	ifstream in(filename);
	if (!in.is_open())
	{
		cout << "Error opening file for reading." << endl;
		return;
	}

	vector<CStudent> loaded;
	string line;
	int lineNum = 0;

	// Validate and parse each line
	while (getline(in, line))
	{
		lineNum++;

		// Skip empty lines
		bool allSpace = true;
		for (char c : line) { if (!isspace(static_cast<unsigned char>(c)))
			{
				allSpace = false;
				break;
			}
		}

		if (allSpace) continue;
		
		istringstream iss(line);
		string studentNum, labS, quizS, midtermS, finalS;

		// Format validation
		if (!(iss >> studentNum >> labS >> quizS >> midtermS >> finalS))
		{
			cout << "Error parsing line " << lineNum << ". Skipping." << endl;
			continue;
		}

		// Student number validation
		if (!isValidStudentNum(studentNum))
		{
			cout << "Invalid student number on line " << lineNum << ". Skipping." << endl;
			continue;
		}

		// Grade validation
		float lab = 0, quiz = 0, midterm = 0, final = 0;
		if (!tryParseGrade(labS, lab) ||
			!tryParseGrade(quizS, quiz) ||
			!tryParseGrade(midtermS, midterm) ||
			!tryParseGrade(finalS, final))
		{
			cout << "Invalid grade on line " << lineNum << ". Skipping." << endl;
			continue;
		}

		loaded.emplace_back(studentNum, lab, quiz, midterm, final);
	}

	_students = loaded;
	cout << "Class loaded from " << filename << endl;
}
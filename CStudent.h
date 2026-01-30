// ELEX-4618 Lab 2
// Ethan Bosiak A01314624

#pragma once

#include <string>

using namespace std;

// CStudent holds all data for one student
class CStudent
{
private:
	// Attributes
	string _studentNum;
	float _lab;
	float _quiz;
	float _midterm;
	float _final;

public:
	// Constructors
	CStudent();
	CStudent(const string& studentNum, float lab, float quiz, float midterm, float final);

	// Getters
	string getStudentNum() const;
	float getLab() const;
	float getQuiz() const;
	float getMidterm() const;
	float getFinal() const;

	// Setters
	void setStudentNum(const string& studentNum);
	void setLab(float lab);
	void setQuiz(float quiz);
	void setMidterm(float midterm);
	void setFinal(float final);

	// Calculate final grade
	float calculateFinalGrade() const;
};
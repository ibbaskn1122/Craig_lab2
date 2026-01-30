// ELEX-4618 Lab 2
// Ethan Bosiak A01314624

#include "CStudent.h"

// Default constructor
CStudent::CStudent()
{
	_studentNum = "";
	_lab = 0.0f;
	_quiz = 0.0f;
	_midterm = 0.0f;
	_final = 0.0f;
}

// Full constructor
CStudent::CStudent(const string& studentNum, float lab, float quiz, float midterm, float final)
{
	_studentNum = studentNum;
	_lab = lab;
	_quiz = quiz;
	_midterm = midterm;
	_final = final;
}

// Getters
string CStudent::getStudentNum() const { return _studentNum; }
float CStudent::getLab() const { return _lab; }
float CStudent::getQuiz() const { return _quiz; }
float CStudent::getMidterm() const { return _midterm; }
float CStudent::getFinal() const { return _final; }

// Setters
void CStudent::setStudentNum(const string& studentNum) { _studentNum = studentNum; }
void CStudent::setLab(float lab) { _lab = lab; }
void CStudent::setQuiz(float quiz) { _quiz = quiz; }
void CStudent::setMidterm(float midterm) { _midterm = midterm; }
void CStudent::setFinal(float final) { _final = final; }

// Calculate final grade
float CStudent::calculateFinalGrade() const
{
	return (_lab * 0.4f) + (_quiz * 0.1f) + (_midterm * 0.2f) + (_final * 0.3f);
}
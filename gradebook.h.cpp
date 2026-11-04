#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include <string>
#include <vector>

// Constants
const double MIN_GRADE = 0.0;
const double MAX_GRADE = 100.0;
const double PASSING_GRADE = 60.0;

// Function Declarations
std::vector<double> collectValidatedGrades();
double calculateAverage(const std::vector<double>& grades);
char determineLetterGrade(double average);
bool isPassing(double average);
void displaySummary(const std::vector<double>& grades, double average, char letterGrade, bool status);
bool askToRepeat();

#endif
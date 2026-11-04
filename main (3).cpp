#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include "gradebook.h"

// Collects grades from the user with input validation
std::vector<double> collectValidatedGrades() {
    std::vector<double> grades;
    int count = 0;

    std::cout << "How many grades would you like to enter? ";
    while (!(std::cin >> count) || count <= 0) {
        std::cout << "Invalid input. Please enter a positive number of grades: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    for (int i = 0; i < count; ++i) {
        double grade;
        std::cout << "Enter grade #" << (i + 1) << " (0-100): ";
        while (!(std::cin >> grade) || grade < MIN_GRADE || grade > MAX_GRADE) {
            std::cout << "Invalid grade. Enter a value between 0 and 100: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        grades.push_back(grade);
    }

    return grades;
}

// Calculates the arithmetic average of grades
double calculateAverage(const std::vector<double>& grades) {
    if (grades.empty()) return 0.0;
    
    double sum = 0.0;
    for (double grade : grades) {
        sum += grade;
    }
    return sum / grades.size();
}

// Determines standard letter grade based on numeric average
char determineLetterGrade(double average) {
    if (average >= 90.0) return 'A';
    if (average >= 80.0) return 'B';
    if (average >= 70.0) return 'C';
    if (average >= 60.0) return 'D';
    return 'F';
}

// Determines if student passed or failed
bool isPassing(double average) {
    return average >= PASSING_GRADE;
}

// Displays formatted summary of results
void displaySummary(const std::vector<double>& grades, double average, char letterGrade, bool status) {
    std::cout << "\n--- GRADEBOOK SUMMARY ---\n";
    std::cout << "Grades entered: ";
    for (size_t i = 0; i < grades.size(); ++i) {
        std::cout << grades[i] << (i == grades.size() - 1 ? "" : ", ");
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nAverage Score: " << average;
    std::cout << "\nLetter Grade : " << letterGrade;
    std::cout << "\nStatus       : " << (status ? "PASSED" : "FAILED") << "\n";
    std::cout << "-------------------------\n";
}

// Asks user whether to process another record
bool askToRepeat() {
    char choice;
    std::cout << "\nWould you like to process another student? (y/n): ";
    std::cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

int main() {
    std::cout << "=================================\n";
    std::cout << "    Student Gradebook System     \n";
    std::cout << "=================================\n";

    bool keepRunning = true;

    while (keepRunning) {
        std::vector<double> grades = collectValidatedGrades();
        double average = calculateAverage(grades);
        char letterGrade = determineLetterGrade(average);
        bool passed = isPassing(average);

        displaySummary(grades, average, letterGrade, passed);

        keepRunning = askToRepeat();
    }

    std::cout << "\nThank you for using the Gradebook System!\n";
    return 0;
}
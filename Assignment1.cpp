#include <iostream>
using namespace std;

class Student {
private:
    string name, email, regNo;
    float marks;
    char grade;

public:
    // Function to input data
    void inputDetails() {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter Reg No: ";
        cin >> regNo;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    // Function to calculate grade
    void calculateGrade() {
        if (marks >= 70)
            grade = 'A';
        else if (marks >= 60)
            grade = 'B';
        else if (marks >= 50)
            grade = 'C';
        else if (marks >= 40)
            grade = 'D';
        else
            grade = 'F';
    }

    // Function to display details
    void displayStudentDetails() {
        cout << "\nName: " << name;
        cout << "\nEmail: " << email;
        cout << "\nReg No: " << regNo;
        cout << "\nMarks: " << marks;
        cout << "\nGrade: " << grade << endl;
    }

    // Function to return marks (for highest comparison)
    float getMarks() {
        return marks;
    }
};

int main() {
    int n = 3; // number of students
    Student s[n];

    // Input details
    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for student " << i + 1 << endl;
        s[i].inputDetails();
        s[i].calculateGrade();
    }

    // Display details
    cout << "\n--- Student Records ---\n";
    for (int i = 0; i < n; i++) {
        s[i].displayStudentDetails();
    }

    // Find highest marks
    float highest = s[0].getMarks();
    int index = 0;

    for (int i = 1; i < n; i++) {
        if (s[i].getMarks() > highest) {
            highest = s[i].getMarks();
            index = i;
        }
    }

    cout << "\n--- Student with Highest Marks ---\n";
    s[index].displayStudentDetails();

    return 0;
}

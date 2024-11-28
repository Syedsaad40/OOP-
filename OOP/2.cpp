#include <iostream>
#include <string>
using namespace std;


class Payable {
public:
    virtual double calculateSalary() = 0;  
};


class Person {
protected:
    string name;
    int age;
    string address;
   
public:
    Person(string name, int age, string address) {
        this->name = name;
        this->age = age;
        this->address = address;
    }
   
    void displayDetails() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Address: " << address << endl;
    }
};


class Student : public Person {
private:
    string studentID;
    int grades[5];
    int gradeCount;

public:
    Student(string name, int age, string address, string studentID)
        : Person(name, age, address), gradeCount(0) {
        this->studentID = studentID;
    }
   
    void addGrade(int grade) {
        if (gradeCount < 5) {
            grades[gradeCount++] = grade;
        }
    }
   
    double calculateGPA() {
        if (gradeCount == 0) return 0.0;
        double sum = 0;
        for (int i = 0; i < gradeCount; i++) {
            sum += grades[i];
        }
        return sum / gradeCount;
    }
   
    void displayDetails() {
        Person::displayDetails();
        cout << "Student ID: " << studentID << endl;
        cout << "GPA: " << calculateGPA() << endl;
    }
};


class Teacher : public Person, public Payable {
private:
    string teacherID;
    string subject;
    int numClasses;
    double ratePerClass;

public:
    Teacher(string name, int age, string address, string teacherID, string subject, int numClasses, double ratePerClass)
        : Person(name, age, address), teacherID(teacherID), subject(subject), numClasses(numClasses), ratePerClass(ratePerClass) {}

    void assignGrade(Student &student, int grade) {
        student.addGrade(grade);
    }

    double calculateSalary() override {
        return numClasses * ratePerClass;
    }
   
    void displayDetails() {
        Person::displayDetails();
        cout << "Teacher ID: " << teacherID << endl;
        cout << "Subject: " << subject << endl;
        cout << "Salary: $" << calculateSalary() << endl;
    }
};

int main() {

    Teacher teacher("Mr. Smith", 35, "123 Elm Street", "T001", "Math", 20, 50.0);
   

    Student student1("Alice Johnson", 16, "456 Oak Avenue", "S001");
    Student student2("Bob Brown", 17, "789 Pine Road", "S002");
   

    teacher.assignGrade(student1, 85);
    teacher.assignGrade(student1, 90);
    teacher.assignGrade(student1, 88);
   
    teacher.assignGrade(student2, 78);
    teacher.assignGrade(student2, 82);
    teacher.assignGrade(student2, 80);
   

    cout << "\nTeacher Details: \n";
    teacher.displayDetails();
   
    cout << "\nStudent 1 Details: \n";
    student1.displayDetails();
   
    cout << "\nStudent 2 Details: \n";
    student2.displayDetails();
   
    return 0;
}
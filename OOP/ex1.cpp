#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

class Student{
private:
    char *name;
    int age;
    char *major;
public:
    Student(){
        name = nullptr;
        age = 0;
        major = nullptr;
    }
    Student(char *name, int age, char *major){
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        this->age = age;
        this->major = new char[strlen(major)+1];
        strcpy(this->major, major);
    }
    Student(const Student &student){
        name = new char[strlen(student.name)+1];
        strcpy(name, student.name);
        age = student.age;
        major = new char[strlen(student.major)+1];
        strcpy(major, student.major);
    }
    ~Student(){
        delete[] name;
        delete[] major;
    }

    Student &operator=(const Student &student){
        if(this != &student){
            delete[] name;
            delete[] major;
            name = new char[strlen(student.name)+1];
            strcpy(name, student.name);
            age = student.age;
            major = new char[strlen(student.major)+1];
            strcpy(major, student.major);
        }
        return *this;
    }

    char *getName(){
        return name;
    }
    int getAge(){
        return age;
    }
    char *getMajor(){
        return major;
    }

};

class Classroom{
private:
    Student *students;
    int numStudents;
    int capacity;
public:
    Classroom(){
        students = new Student[10];
        numStudents = 0;
        capacity = 10;
    }
    Classroom(Student *students, int numStudents, int capacity){
        this->numStudents = numStudents;
        this->capacity = capacity;
        this->students = new Student[numStudents];
        for(int i=0; i<numStudents; i++){
            this->students[i] = students[i];
        }
    }
    Classroom(const Classroom &classroom){
        numStudents = classroom.numStudents;
        capacity = classroom.capacity;
        students = new Student[numStudents];
        for(int i=0; i<numStudents; i++){
            students[i] = classroom.students[i];
        }
    }
    ~Classroom(){
        delete[] students;
    }

    Classroom &operator=(const Classroom &classroom){
        if(this != &classroom){
            delete[] students;
            numStudents = classroom.numStudents;
            capacity = classroom.capacity;
            students = new Student[numStudents];
            for(int i=0; i<numStudents; i++){
                students[i] = classroom.students[i];
            }
        }
        return *this;
    }

    Student *getStudents(){
        return students;
    }
    int getNumStudents() const {
        return numStudents;
    }

    void add(Student student){
        // if(numStudents < capacity){
        Student *temp = new Student[numStudents+1];
        for(int i=0; i<numStudents; i++){
            temp[i] = students[i];
        }
        temp[numStudents] = student;
        numStudents++;
        delete[] students;
        students = temp;
        // }
    }

    void remove(char *name){
        bool found = false;
        for(int i=0; i<numStudents; i++){
            if(strcmp(students[i].getName(), name) == 0){
                found = true;
                numStudents--;
                // Delete the matching student and shift the remaining students to the left
                for(int j=i; j<numStudents; j++){
                    students[j] = students[j+1];
                }
                i--; // Decrement i so that the next iteration checks the current index again
            }
        }
        if(found){
            // Allocate a new array of size numStudents and copy the students over
            Student *temp = new Student[numStudents];
            for(int i=0; i<numStudents; i++){
                temp[i] = students[i];
            }
            // Free the memory allocated for the original students array and assign the new array
            delete[] students;
            students = temp;
        }
    }

    void printStudents(){
        for(int i=0; i<numStudents; i++){
            cout<<students[i].getName()<<" ("<<students[i].getAge()<<","<<" "<<students[i].getMajor()<<")"<<endl;
        }
        cout<<endl;
    }
};

double findMedianAge(Classroom classroom) {
    int n = classroom.getNumStudents();
    int ages[n];
    for (int i = 0; i < n; i++) {
        ages[i] = classroom.getStudents()[i].getAge();
    }
    sort(ages, ages + n);
    //ako nizata ima paren broj elementi
    if(n % 2 == 0){
        return (double)(ages[(n/2)-1] + ages[n/2])/2.0;
    }
    else{
        return (double)ages[n/2];
    }
}

//DO NOT CHANGE
int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i*numStudents + j] = student;
        }
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;
    cout<<"After removing the elements:"<<endl; /// Added
    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }

    return 0;
}
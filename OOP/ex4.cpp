#include <iostream>
#include <cstring>
using namespace std;
class Student{
private:
    char *name;
    int age;
    char *major;
public:
    Student(char *name="", int age=0,char *major=""){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->age=age;
        this->major=new char[strlen(major)+1];
        strcpy(this->major,major);
    }
    Student(const Student &s){
        this->name=new char[strlen(s.name)+1];
        strcpy(this->name,s.name);
        this->age=s.age;
        this->major=new char[strlen(s.major)+1];
        strcpy(this->major,s.major);
    }
    Student &operator=(const Student &s){
        if (this!=&s){
            delete[]name;
            delete[]major;
            this->name=new char[strlen(s.name)+1];
            strcpy(this->name,s.name);
            this->age=s.age;
            this->major=new char[strlen(s.major)+1];
            strcpy(this->major,s.major);
        }
        return *this;
    }
    ~Student(){
        delete[]name;
        delete[]major;
    }
    char *getName() {
        return name;
    }

    int getAge() {
        return age;
    }
    void print() {
        cout << name << " (" << age << ", " << major << ")"<< endl;
    }
};
class Classroom{
private:
    Student *students;
    int numStudents;
    int capacity;
public:
    Classroom(Student *students=NULL, int numStudents=0, int capacity=0){
        this->numStudents=numStudents;
        this->capacity=capacity;
        this->students = new Student [numStudents];
        for(int i=0;i<numStudents;i++){
            this->students[i]=students[i];
        }
    }
    Classroom(const Classroom &c){
        this->numStudents=c.numStudents;
        this->capacity=c.capacity;
        this->students=new Student [numStudents];
        for(int i=0;i<numStudents;i++){
            this->students[i]=c.students[i];
        }
    }
    Classroom &operator=(const Classroom &c){
        if (this!=&c){
            this->numStudents=c.numStudents;
            this->capacity=c.capacity;
            this->students=new Student [numStudents];
            for(int i=0;i<numStudents;i++){
                this->students[i]=c.students[i];
            }
        }
        return *this;
    }
    ~Classroom(){
        delete[]students;
    }
    int getNumStudents() const {
        return numStudents;
    }

    Student *getStudents() const {
        return students;
    }

    void add(Student s){
        Student *temp = new Student[numStudents+1];
        for(int i=0;i<numStudents;i++){
            temp[i]=students[i];
        }
        temp[numStudents]=s;
        numStudents++;
        delete[]students;
        students=temp;
    }
    void remove(char *name){
        int flag=0;
        for(int i=0;i<numStudents;i++){
            if(strcmp(students[i].getName(),name)==0){
                flag=1;
            }
        }
        if(flag==0){
            return;
        }
        Student *temp = new Student[numStudents-1];
        int j=0;
        for(int i=0;i<numStudents;i++){
            if(!strcmp(students[i].getName(),name)==0){
                temp[j]=students[i];
                j++;
            }
        }
        numStudents--;
        delete[]students;
        students=temp;
    }
    void printStudents(){
        for (int i = 0; i < numStudents; ++i) {
            students[i].print();

        }
        cout<<endl;
    }
};
double findMedianAge(Classroom classroom) {
    int n = classroom.getNumStudents();
    int ages[n],temp;

    for (int i = 0; i < n; i++) {
        ages[i] = classroom.getStudents()[i].getAge();
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if (ages[i]>ages[j]){
                temp=ages[i];
                ages[i]=ages[j];
                ages[j]=temp;
            }
        }
    }
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
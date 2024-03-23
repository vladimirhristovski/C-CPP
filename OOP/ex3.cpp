#include <iostream>
#include <cstring>
using namespace std;

class Student{
private:
    char *name;
    int age;
    char *major;
public:
    Student(){
        this->name=new char [0];
        this->age=0;
        this->major=new char [0];
    }
    Student(char *name,int age, char *major){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->age=age;
        this->major=new char [strlen(major)+1];
        strcpy(this->major,major);
    }
    Student(const Student &s){
        this->name=new char [strlen(s.name)+1];
        strcpy(this->name,s.name);
        this->age=s.age;
        this->major=new char [strlen(s.major)+1];
        strcpy(this->major,s.major);
    }
    Student& operator=(const Student &s){
        if(this!=&s){
            this->name=new char [strlen(s.name)+1];
            strcpy(this->name,s.name);
            this->age=s.age;
            this->major=new char [strlen(s.major)+1];
            strcpy(this->major,s.major);
        }
        return *this;
    }
    ~Student(){
        delete [] name;
        delete [] major;
    }
    char *getName(){
        return name;
    }
    int getAge(){
        return age;
    }
    void print() {
        cout << name << " (" << age << ", " << major << ")" << endl;
    }
};

class Classroom{
private:
    Student *student;
    int numStudents;
    int capacity;
public:

    Classroom(){
        this->numStudents=0;
        this->capacity=0;
        this->student=NULL;

    }
    /*
     Classroom(int capacity){
    	  this->numStudents=0;
        this->capacity=capacity;
        this->student=NULL;

    }
    */
    Classroom(Student *student,int numStudents,int capacity){
        this->numStudents=numStudents;
        this->capacity=capacity;
        this->student=new Student [numStudents];
        for(int i=0;i<numStudents;i++){
            this->student[i]=student[i];
        }

    }

    /*
    Classroom(Student *student=NULL,int numStudents=0,int capacity=0){
    	 this->numStudents=numStudents;
        this->capacity=capacity;
    	this->student=new Student [numStudents];
        for(int i=0;i<numStudents;i++){
            this->student[i]=student[i];
        }

    }
  */
    Classroom(const Classroom &c){
        this->numStudents=c.numStudents;
        this->capacity=c.capacity;
        this->student=new Student [c.numStudents];
        for(int i=0;i<c.numStudents;i++){
            this->student[i]=c.student[i];
        }

    }
    Classroom& operator=(const Classroom &c){
        if(this!=&c){
            this->numStudents=c.numStudents;
            this->capacity=c.capacity;
            this->student=new Student [c.numStudents];
            for(int i=0;i<c.numStudents;i++){
                this->student[i]=c.student[i];
            }
        }
        return *this;

    }
    ~Classroom(){
        delete [] student;
    }
    void add(Student &s){
        Student *temp = new Student [numStudents+1];
        for(int i=0;i<numStudents;i++){
            temp[i]=student[i];
        }

        temp[numStudents++] = s;
        delete [] student;
        student=temp;
    }
    void remove(char name[100]){
        int brojac=0,j=0;
        for (int i=0;i<numStudents;i++){
            if(strcmp(student[i].getName(),name)==0){
                brojac++;
            }
        }
        Student *temp = new Student[brojac];

        for (int i=0;i<numStudents;i++){
            temp[j]=student[i];
            j++;
        }
        delete [] student;
        student=temp;
        numStudents=brojac;
    }

    void printStudents(){
        for (int i = 0; i < numStudents; ++i) {
            student[i].print();

        }
        cout<<endl;
    }
    int getnumStudents(){
        return numStudents;
    }

};
double findMedianAge(Classroom classrooms){
    Student *student;
    Student temp;
    double medijana;
    for(int i=0;i<classrooms.getnumStudents();i++){
        for(int j=i+1;j<classrooms.getnumStudents();j++){
            if (student[i].getAge()>student[j].getAge()){
                temp=student[i];
                student[i]=student[j];
                student[j]=temp;
            }
        }
    }

    if (classrooms.getnumStudents()%2!=0){
        //  for(int i=0;i<classrooms.getnumStudents()/2;i++){
        medijana=(double)student[classrooms.getnumStudents()/2].getAge();
        // }
    }
    else{
        medijana=(double)student[classrooms.getnumStudents()/2].getAge()+(double)student[classrooms.getnumStudents()/2-1].getAge();
    }
    return medijana;
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
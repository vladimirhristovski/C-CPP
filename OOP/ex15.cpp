#include <iostream>
#include <cstring>
using namespace std;
class MobilePhone{
private:
    char model[21];
    int numModel;
    int year;
    void copy (const MobilePhone &other){
        strcpy(this->model,other.model);
        this->year=other.year;
        this->numModel=other.numModel;
    }
public:
    MobilePhone(char *model="", int numModel=0, int year=0){
        strcpy(this->model,model);
        this->year=year;
        this->numModel=numModel;
    }
    MobilePhone(const MobilePhone &other){
        copy(other);
    }
    ~MobilePhone(){}
    friend ostream &operator<<(ostream &o,MobilePhone mb){
        o<<mb.model<<" "<<mb.numModel<<" release year: "<<mb.year<<endl;
        return o;
    }
//    void print() {
//        cout << model << " " << numModel << " release year: " << year <<endl;
//    }
};
class Owner{
protected:
    char name[21];
    char surname[21];
    MobilePhone mobilephone;
    void copy (const Owner &other){
        strcpy(this->name,other.name);
        strcpy(this->surname,other.surname);
        this->mobilephone=other.mobilephone;
    }
public:
    Owner(char *name="", char *surname="", MobilePhone mobilephone=0){
        strcpy(this->name,name);
        strcpy(this->surname,surname);
        this->mobilephone=mobilephone;
    }
    Owner(const Owner &other){
        copy(other);
    }
    ~Owner(){}
    friend ostream &operator<<(ostream &o,Owner mb){
        o<<mb.name<<" "<<mb.surname<<" has a mobile phone: "<<endl;
        o<<mb.mobilephone;
        return o;
    }
};
//DO NOT CHANGE THE MAIN FUNCTION
int main() {
    char model[20];
    int modelNumber;
    int year;
    char name[20];
    char surname[20];

    int testCase;

    cin>>testCase;

    cin>>model;
    cin>>modelNumber;
    cin>>year;
    cin>>name;
    cin>>surname;

    if(testCase==1){
        MobilePhone mobilePhone(model,modelNumber,year);

        Owner owner(name,surname,mobilePhone);
        cout<<owner;
    }
    if(testCase==2){
        MobilePhone mobilePhone(MobilePhone(model,modelNumber,year));

        Owner owner(name,surname,mobilePhone);
        cout<<owner;
    }

}

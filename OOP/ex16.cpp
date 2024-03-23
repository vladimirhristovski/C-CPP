#include <iostream>
#include <cstring>

using namespace std;

class DisciplinaryAction{
private:
    char *name;
    int index;
    char *pricina;

    void copy(const DisciplinaryAction &other){
        this->name = new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->index=other.index;
        this->pricina = new char[strlen(other.pricina)+1];
        strcpy(this->pricina,other.pricina);
    }
public:
    DisciplinaryAction(char *name="", int index=0, char *pricina=""){
        this->name = new char[strlen(name)+1];
        strcpy(this->name,name);
        this->index=index;
        this->pricina = new char[strlen(pricina)+1];
        strcpy(this->pricina,pricina);
    }
    DisciplinaryAction(const DisciplinaryAction &other){
        copy(other);
    }
    ~DisciplinaryAction(){
        delete[]name;
        delete[]pricina;
    }
    DisciplinaryAction &operator = (const DisciplinaryAction &other){
        if(this != &other){
            delete[]name;
            delete[]pricina;
            copy (other);
        }
        return *this;
    }
    void print(){
        cout<<"Student: "<< name <<endl;
        cout<<"Student's index: "<< index <<endl;
        cout<<"Reason: "<< pricina <<endl;
    }

    void setIndex(int index) {
        DisciplinaryAction::index = index;
    }
};


/// Do NOT edit the main() function

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for(int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;

        cin >> name >> index >> reason;

        arr[i] = DisciplinaryAction(name, index, reason);
    }

    cout << "-- Testing operator = & print() --\n";
    arr[0].print();

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    arr[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    merka.print();

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for(int i = 0; i < n; i++)
        arr[i].print();

    return 0;
}
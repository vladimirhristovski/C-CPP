#include <iostream>
#include <cstring>
using namespace std;

class DisciplinaryAction{
private:
    //PRIVATNI PODATOCNI CLENKI
    char *name;
    int index;
    char *reason;
public:
    //CONSTRUCTOR
    DisciplinaryAction(char *name="", int index=0,char *reason=""){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->index=index;
        this->reason=new char[strlen(reason)+1];
        strcpy(this->reason,reason);
    }
    //COPY CONSTRUCTOR
    DisciplinaryAction(const DisciplinaryAction &da){
        this->name=new char[strlen(da.name)+1];
        strcpy(this->name,da.name);
        this->index=da.index;
        this->reason=new char[strlen(da.reason)+1];
        strcpy(this->reason,da.reason);
    }
    //OPERATOR =
    DisciplinaryAction &operator=(const DisciplinaryAction &da){
        if (this!=&da){
            delete[]name;
            delete[]reason;
            this->name=new char[strlen(da.name)+1];
            strcpy(this->name,da.name);
            this->index=da.index;
            this->reason=new char[strlen(da.reason)+1];
            strcpy(this->reason,da.reason);
        }
        return *this;
    }
    //DESTRUCTOR
    ~DisciplinaryAction(){
        delete[]name;
        delete[]reason;
    }
    //SETTER ZA INDEX
    void setIndex(int index) {
        DisciplinaryAction::index = index;
    }
    //GETTER ZA INDEX
    int getIndex() const {
        return index;
    }
    void print(){
        cout<<"Student: "<<name<<"\n"<<"Student's index: "<<index<<"\n"<<"Reason: "<<reason<<endl;
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
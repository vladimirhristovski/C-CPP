#include <iostream>
#include <cstring>
using namespace std;

class DisciplinaryAction {
private:
    char *name;
    int index;
    char *reason;
    int brSesii;

    void copy(const DisciplinaryAction &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->index = other.index;
        this->reason = new char[strlen(other.reason) + 1];
        strcpy(this->reason, other.reason);
        this->brSesii = other.brSesii;
    }

public:
    DisciplinaryAction(char *name = "", int index = 0, char *reason = "", int brSesii = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->index = index;
        this->reason = new char[strlen(reason) + 1];
        strcpy(this->reason, reason);
        this->brSesii = brSesii;
    }

    DisciplinaryAction(const DisciplinaryAction &other) {
        copy(other);
    }

    ~DisciplinaryAction() {
        delete[]name;
        delete[]reason;
    }

    DisciplinaryAction &operator=(const DisciplinaryAction &other) {
        if (this != &other) {
            delete[]name;
            delete[]reason;
            copy(other);
        }
        return *this;
    }

    int getIndex() const {
        return index;
    }

    void setIndex(int index) {
        DisciplinaryAction::index = index;
    }
    DisciplinaryAction &operator++(){
        brSesii++;
        return *this;
    }
    bool operator>=(const DisciplinaryAction & d) {
        if (brSesii >= d.brSesii) {
            return true;
        } else {
            return false;
        }
    }
    friend ostream &operator<<(ostream &o,DisciplinaryAction &p) {
        o<<"Student: "<<p.name<<"\n"<<"Student's index: "<<p.index<<"\n"<<"Reason: "<<p.reason<<"\n"<<"Sessions: "<<p.brSesii<<endl;
        return o;
    }
};
// 1
int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}
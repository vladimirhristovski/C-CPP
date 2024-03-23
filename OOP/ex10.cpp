#include <iostream>
#include <string.h>
using namespace std;

class DeliveryPerson {
    char ID[5];
    char *ime;
    int lokacija;
    int izvrseniDostavi;
    void copy(const DeliveryPerson & other){
        strcpy (this->ID,other.ID);
        this->lokacija=other.lokacija;
        this->izvrseniDostavi=other.izvrseniDostavi;
        this->ime=new char[strlen(other.ime)+1];
        strcpy (this->ime,other.ime);
    }
public:
    DeliveryPerson (char *ID="",char *ime="",int lokacija=0,int izvrsenidostavi=0)
    {
        strcpy (this->ID,ID);
        this->lokacija=lokacija;
        this->izvrseniDostavi=izvrsenidostavi;
        this->ime=new char[strlen(ime)+1];
        strcpy (this->ime,ime);
    }
    DeliveryPerson (const DeliveryPerson & other)
    {
        copy(other);
    }
    ~DeliveryPerson(){
        delete[]ime;
    }

    DeliveryPerson &operator=(const DeliveryPerson & other){
        if(this!=&other) {
            delete[]ime;
            copy(other);
        }
        return *this;
    }
    void print()
    {
        cout<<"ID: "<<ID<<" Name: "<<ime<<" Current location: "<<lokacija<<" # of deliveries: "<<izvrseniDostavi<<endl;
    }

    int getLokacija ()
    {
        return lokacija;
    }
    void setLokacija (int n)
    {
        lokacija=n;
    }
    int getIzvreseni()
    {
        return izvrseniDostavi;
    }
    void setIzvrseni(int n)
    {
        izvrseniDostavi=n;
    }

    const char *getId() const {
        return ID;
    }
};

class DeliveryApp {
    char ime[20];
    DeliveryPerson *niza;
    int brojDostavuvaci;
    void copy(const DeliveryApp & other){
        strcpy (this->ime,other.ime);
        this->brojDostavuvaci=other.brojDostavuvaci;
        this->niza=new DeliveryPerson[this->brojDostavuvaci];
        for (int i=0;i< this->brojDostavuvaci;i++)
        {
            this->niza[i]=other.niza[i];
        }
    }
public:
    DeliveryApp (char *ime="",DeliveryPerson *niza=0,int brojDostavuvaci=0)
    {
        strcpy (this->ime,ime);
        this->brojDostavuvaci=brojDostavuvaci;
        this->niza=new DeliveryPerson[brojDostavuvaci];
        for (int i=0;i<brojDostavuvaci;i++)
        {
            this->niza[i]=niza[i];
        }
    }
    DeliveryApp (const DeliveryApp & other)
    {
        copy(other);
    }
    ~DeliveryApp(){
        delete [] niza;
    }
    DeliveryApp & operator = (const DeliveryApp & other){
        if(this != &other){
            delete[]niza;
            copy(other);
        }
        return *this;
    }
    void addDeliveryPerson (const DeliveryPerson &person){
        for (int i=0;i<brojDostavuvaci;i++)
        {
            if (strcmp(person.getId(),niza[i].getId())==0)
                return;
        }
        DeliveryPerson *tmp=new DeliveryPerson[brojDostavuvaci+1];
        for (int i=0;i<brojDostavuvaci;i++)
        {
            tmp[i]=niza[i];
        }
        delete []niza;
        tmp[brojDostavuvaci]=person;
        brojDostavuvaci++;
        niza=tmp;
    }
    void assignDelivery (int restaurantArea,int customerArea)
    {
        int razlika,flag=1,max;
        int maxDostavi;
        int maxIndeks;
        int flag2=0;
        for (int i=0;i<brojDostavuvaci;i++) {
            if (restaurantArea == niza[i].getLokacija()) {
                flag2++;
                if (flag)
                {
                    maxIndeks=i;
                    maxDostavi=niza[i].getIzvreseni();
                    flag=0;
                }
                if (maxDostavi>niza[i].getIzvreseni())
                {
                    maxIndeks=i;
                    maxDostavi=niza[i].getIzvreseni();
                }

            }
        }
        if (flag2==0)
        {
            for (int j=0;j<brojDostavuvaci;j++)
            {
                if (niza[j].getLokacija()<restaurantArea)
                {
                    razlika=restaurantArea-niza[j].getLokacija();
                }
                else{
                    razlika=niza[j].getLokacija()-restaurantArea;
                }
                if (flag)
                {
                    max=razlika;
                    maxIndeks=j;
                    maxDostavi=niza[j].getIzvreseni();
                    flag=0;
                }
                if (razlika<max)
                {
                    max=razlika;
                    maxIndeks=j;
                    maxDostavi=niza[j].getIzvreseni();
                }
                else if (razlika==max)
                {
                    if (niza[j].getIzvreseni()<maxDostavi)
                    {
                        maxIndeks=j;
                        maxDostavi=niza[j].getIzvreseni();
                    }

                }

            }

        }
        niza[maxIndeks].setLokacija(customerArea);
        niza[maxIndeks].setIzvrseni(niza[maxIndeks].getIzvreseni()+1);
    }


    void print ()
    {
        cout<<ime<<endl;
        if (brojDostavuvaci==0) {
            cout << "EMPTY" << endl;
        }
        for (int i=0;i<brojDostavuvaci;i++)
        {
            niza[i].print();
        }
    }
};

int main() {

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "CONSTRUCTOR DeliveryPerson" << endl;
        DeliveryPerson person("12345", "Stefan", 5);
        person.print();
        cout << "CONSTRUCTOR DeliveryPerson OK" << endl;
    } else if (testCase == 2) {
        cout << "COPY-CONSTRUCTOR DeliveryPerson" << endl;
        DeliveryPerson person = DeliveryPerson("12345", "Stefan", 5);
        person.print();
        cout << "COPY-CONSTRUCTOR DeliveryPerson OK" << endl;
    } else if (testCase == 3) {
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = DeliveryPerson" << endl;
        DeliveryPerson person;
        DeliveryPerson person2("12345", "Stefan", 5);
        person = person2;
        person.print();
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = DeliveryPerson OK" << endl;
    } else if (testCase == 4) {
        cout << "CONSTRUCTOR DeliveryApp" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        app.print();
        cout << "CONSTRUCTOR DeliveryApp OK" << endl;
    } else if (testCase == 5) {
        cout << "DeliveryApp addDeliveryPerson test" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        int n;
        cin >> n;
        char ID[6];
        char name[20];
        int location;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location;
            app.addDeliveryPerson(DeliveryPerson(ID, name, location));
        }
        app.print();
    } else if (testCase == 6) {
        cout << "DeliveryApp addDeliveryPerson test" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        int n;
        cin >> n;
        char ID[6];
        char name[20];
        int location;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location;
            app.addDeliveryPerson(DeliveryPerson(ID, name, location));
        }
        cin >> n; //read assign deliveries
        for (int i = 0; i < n; i++) {
            int restaurantArea, customerArea;
            cin >> restaurantArea >> customerArea;
            app.assignDelivery(restaurantArea, customerArea);
        }
        app.print();
    }
    return 0;
}
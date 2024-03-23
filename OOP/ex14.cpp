#include <iostream>
#include <cstring>
using namespace std;

class InvalidOperation{
protected:

public:
    void showMessageMonths(){
        cout<<"Can't merge events from different months."<<endl;
    }
    void showMessageCapacity(){
        cout<<"Can't merge events which have more guests than the capacity"<<endl;
    }
};

class Event{
protected:
    char *name;
    int guests;
    int month;
    bool active;
    static int MAX_CAPACITY;
    void copy(const Event &other){
        this->name=new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->guests=other.guests;
        this->month=other.month;
        this->active=other.active;
    }
public:
    Event(char *name="",int guests=0,int month=1,bool active= true){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->guests=guests;
        this->month=month;
        this->active=active;
    }
    Event(const Event &other){
        copy(other);
    }
    Event &operator=(const Event &other){
        if (this!=&other){
            delete[]name;
            copy(other);
        }
        return *this;
    }
    ~Event(){
        delete[]name;
    }
    friend ostream &operator<<(ostream &o,Event &e){
        o<<e.name<<" "<<e.month<<" "<<e.guests<<endl;
    }
    Event &operator+(Event &e){
        if(e.month!=this->month){
            throw InvalidOperation();
        }
        if(e.guests>MAX_CAPACITY){
            throw InvalidOperation();
        }
        char *tmp=new char[strlen(e.name)+ strlen(name)+2];
        strcpy(tmp,this->name);
        strcat(tmp,"&");
        strcat(tmp,e.name);
        delete[]name;
        this->name=new char[strlen(tmp)+1];
        strcpy(name,tmp);
        this->guests+=e.guests;
        return *this;
    }

    bool isActive() const {
        return active;
    }

    static int getMAX() {
        return MAX_CAPACITY;
    }

};

int Event::MAX_CAPACITY=1000;



class EventCalendar{
protected:
    int year;
    Event *events;
    int numOfEvents;
    void copy(const EventCalendar &other){
        this->year=other.year;
        this->numOfEvents=other.numOfEvents;
        this->events=new Event [other.numOfEvents];
        for(int i=0;i<other.numOfEvents;i++){
            this->events[i]=other.events[i];
        }
    }
public:
    EventCalendar(int year=0,Event *events=0,int numOfEvents=0){
        this->year=year;
        this->numOfEvents=numOfEvents;
        this->events=new Event [this->numOfEvents];
        for(int i=0;i<numOfEvents;i++){
            this->events[i]=events[i];
        }
    }
    EventCalendar(const EventCalendar &other){
        copy(other);
    }
    EventCalendar &operator=(const EventCalendar &other){
        if(this!=&other){
            delete[]events;
            copy(other);
        }
        return *this;
    }
    ~EventCalendar(){
        delete[]events;
    }
    friend ostream &operator<<(ostream &o,EventCalendar &ec){
        o<<ec.year<<endl;
        for(int i=0;i<ec.numOfEvents;i++){
            if(ec.events[i].isActive()){
                o<<ec.events[i];
            }
        }
        return o;
    }
    EventCalendar &operator+=(const Event &e){
        Event *tmp=new Event [numOfEvents+1];
        for(int i=0;i<numOfEvents;i++){
            tmp[i]=events[i];
        }
        tmp[numOfEvents++]=e;
        delete[]events;
        events=tmp;
        return *this;
    }
};

int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 0) {
        cout << "Event constructor" << endl;
        Event e1("Wedding", 25, 4);
        Event e2("Graduation", 50, 5, false);
        cout << "TEST PASSED" << endl;
    } else if (testCase == 1) {
        cout << "Event copy-constructor and operator =" << endl;
        Event e2("Wedding", 25, 4);
        Event e1 = e2;
        Event e3("Graduation", 50, 5, false);
        e3 = e2;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 2) {
        cout << "Event operator <<" << endl;
        Event e1("Wedding", 25, 4);
        Event e2("Graduation", 50, 5, false);
        cout << e1;
        cout << e2;
    } else if (testCase == 3) {
        cout << "Event operator + (normal behavior)" << endl;
        Event e1("Wedding", 25, 4);
        Event e2("Graduation", 50, 4, false);
        try {
            cout << e1 << "+" << endl << e2 << "-->" << endl;
            cout << (e1 + e2);
        }
        catch(InvalidOperation &e)
        {
            e.showMessageMonths();
        }
        catch (InvalidOperation &e)
        {
            e.showMessageCapacity();
        }
    } else if (testCase == 4) {
        cout << "Event operator + (abnormal behavior)" << endl;
        char name[50];
        int number_guests, month;
        bool active;
        cin >> name >> number_guests >> month >> active;
        Event e1(name, number_guests, month, active);
        cin >> name >> number_guests >> month >> active;
        Event e2(name, number_guests, month, active);
        if (number_guests>Event::getMAX()) {
            try {
                cout << e1 << "+" << endl << e2 << "-->" << endl;
                cout << (e1 + e2);
            } catch (InvalidOperation &e) {
                e.showMessageCapacity();
            }
        }
        else{
            try {
                cout << e1 << "+" << endl << e2 << "-->" << endl;
                cout << (e1 + e2);
            } catch (InvalidOperation &e) {
                e.showMessageMonths();
            }
        }
    } else if (testCase == 5) {
        cout << "EventCalendar constructors" << endl;
        EventCalendar ec1(2020);
        EventCalendar ec2(2021);
        cout << "TEST PASSED" << endl;
    } else if (testCase == 6) {
        cout << "EventCalendar copy-constructor and operator =" << endl;
        EventCalendar ec1(2020);
        EventCalendar ec2(2021);
        EventCalendar ec3 = ec1; //copy constructor;
        ec2 = ec1; //operator =
        cout << "TEST PASSED" << endl;
    } else if (testCase == 7) {
        cout << "EventCalendar operator << (empty)" << endl;
        EventCalendar ec1(2021);
        cout << ec1;
    } else if (testCase == 8) {
        cout << "EventCalendar += and <<" << endl;
        EventCalendar ec(2021);
        int n;
        cin >> n;
        char name[50];
        int number_guests, month;
        bool active;

        for (int i = 0; i < n; i++) {
            cin >> name >> number_guests >> month >> active;
            Event e(name, number_guests, month, active);
            ec += e;
        }
        cout << ec;
    }
    return 0;
}
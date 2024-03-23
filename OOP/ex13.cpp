#include<iostream>
#include<cstring>
using namespace std;

class InvalidTimeException{
public:
    void showMessage(){
        cout<<"The time is not valid"<<endl;
    }
};
class Race{
protected:
    char city[40];
    int year;
    int month;
    float bestTime;
    float distance;
public:
    Race(char *city="",int year=0,int month=0,float bestTime=0.0,float distance=0.0){
        strcpy(this->city,city);
        this->year=year;
        this->month=month;
        this->bestTime=bestTime;
        this->distance=distance;
    }
    virtual float heaviness(){
        return (float)bestTime/distance;
    }
    friend ostream &operator<<(ostream &o,Race &r){
        o<<r.city<<" "<<r.month<<"."<<r.year<<" "<<r.heaviness()<<" "<<endl;
        return o;
    }
};
class CarRace:public Race{
private:
    float *nizaOdNajdobriVreminja;
    int brNaNajdobriVreminja;
    int brNaKrugovi;
    static float CAR_COEF;
    void copy(const CarRace &other){
        this->brNaNajdobriVreminja=other.brNaNajdobriVreminja;
        this->brNaKrugovi=other.brNaKrugovi;
        this->nizaOdNajdobriVreminja=new float [other.brNaNajdobriVreminja];
        for(int i=0;i<other.brNaNajdobriVreminja;i++){
            this->nizaOdNajdobriVreminja[i]=other.nizaOdNajdobriVreminja[i];
        }
    }
public:
    CarRace(char *city="",int year=0,int month=0,float bestTime=0.0,float distance=0.0,float *nizaOdNajdobriVreminja=0,int brNaNajdobriVreminja=0,int brNaKrugovi=0): Race(city,year,month,bestTime,distance){
        this->brNaNajdobriVreminja=brNaNajdobriVreminja;
        this->brNaKrugovi=brNaKrugovi;
        this->nizaOdNajdobriVreminja=new float [brNaNajdobriVreminja];
        for(int i=0;i<brNaNajdobriVreminja;i++){
            this->nizaOdNajdobriVreminja[i]=nizaOdNajdobriVreminja[i];
        }
    }
    CarRace(const CarRace &other){
        copy(other);
    }
    CarRace &operator=(const CarRace &other){
        if(this!=&other){
            delete [] nizaOdNajdobriVreminja;
            copy(other);
        }
        return *this;
    }
    ~CarRace(){
        delete[]nizaOdNajdobriVreminja;
    }
    float heaviness(){
        double tezina=Race::heaviness();
        float tmp = 0;
        for(int i=0;i<brNaNajdobriVreminja;i++){
            tmp+=nizaOdNajdobriVreminja[i];
        }
        float avgBestTime=(tmp/(float)brNaNajdobriVreminja);
        tezina+=(avgBestTime*CAR_COEF);
        if(brNaKrugovi>15){
            return (float)tezina*1.1;
        }
        return (float)tezina;
    }

    static void setKoeficient(float carCoef){
        CAR_COEF = carCoef;
    }

    void setNumberLaps(int brNaKrugovi){
        CarRace::brNaKrugovi = brNaKrugovi;
    }
    CarRace &operator+=(float cr){
        if(cr<10) {
            throw InvalidTimeException();
        }
        float *tmp = new float[brNaNajdobriVreminja+1];
        for (int i = 0; i < brNaNajdobriVreminja; i++) {
            tmp[i] = nizaOdNajdobriVreminja[i];
        }
        tmp[brNaNajdobriVreminja] = cr;
        delete[]nizaOdNajdobriVreminja;
        brNaNajdobriVreminja++;
        nizaOdNajdobriVreminja = tmp;
        return *this;
    }
};
float CarRace::CAR_COEF=0.3;

int main(){
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int izbor;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        Race t(city, year, month, bestTime, length);
        cout<<t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        CarRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        CarRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje novo najdobro vreme za prvata CarRace
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            CarRace* nn = dynamic_cast<CarRace*>(niza[i]);
            if (nn != 0){
                flag = 0;
                (*nn) += best;
                break;
            }
        }


        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        CarRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float vreme1,vreme2;
        cin>>vreme1>>vreme2;
        try{
            mgt+=vreme1;
            mgt+=vreme2;
        }
        catch(InvalidTimeException e)
        {
            e.showMessage();
        }
        cout<<mgt;
    }

    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        CarRace::setKoeficient(0.7);
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }



    return 0;
}
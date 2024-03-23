#include <iostream>
#include <cstring>
using namespace std;

class Product{
private:
    char *ime;
    int cena;
    int popust;
    int kolicina;
public: //Product p; Product p1("pizza"); Product p2("pizza", 15, 20)
    Product(char *ime="ime", int cena=0, int popust=0, int kolicina=0){
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->cena = cena;
        this->popust=popust;
        this->kolicina=kolicina;
    }
    Product(const Product &p){
        this->ime = new char[strlen(p.ime)+1];
        strcpy(this->ime, p.ime);
        this->cena = p.cena;
        this->popust=p.popust;
        this->kolicina=p.kolicina;
    }
    Product &operator=(const Product &p){
        if(this!=&p){
            delete [] ime;
            this->ime = new char[strlen(p.ime)+1];
            strcpy(this->ime, p.ime);
            this->cena = p.cena;
            this->popust=p.popust;
            this->kolicina=p.kolicina;
        }
        return *this;
    }
    ~Product(){
        delete [] ime;
    }
    void print(){//*5/100=1.05
        cout<<ime<<" Regular price: "<<cena<<" Price with discount: "<<cena*(1-popust/100.0)<<" Quantity: "<<kolicina<<endl;
    }
    void zgolemi_procent(int k){
        if(popust+k<=99){
            popust+=k;
        }
    }
    void increment(){
        kolicina++;
    }
    int get_kolicina(){
        return kolicina;
    }
};

class Store{
private:
    char ime[50];
    Product *niza;
    int n;
public:
    Store(char *ime=""){
        strcpy(this->ime, ime);
        niza = new Product[0];
        n=0;
    }
    Store(const Store &s){
        strcpy(this->ime, s.ime);
        n=s.n;
        niza = new Product[n];
        for(int i=0; i<n; i++){
            niza[i] = s.niza[i];
        }
    }
    Store &operator=(const Store &s){
        if(this!=&s){
            strcpy(this->ime, s.ime);
            n=s.n;
            delete [] niza;
            niza = new Product[n];
            for(int i=0; i<n; i++){
                niza[i] = s.niza[i];
            }
        }
        return *this;
    }
    ~Store(){
        delete [] niza;
    }
    void print(){
        cout<<ime<<endl;
        for(int i=0; i<n; i++){
            niza[i].print();
        }
    }
    void add(Product p){
        if(p.get_kolicina()<5){
            return;
        }
        Product *tmp = new Product[n+1];
        for(int i=0; i<n; i++){
            tmp[i] = niza[i];
        }
        tmp[n] = p;
        n++;
        delete [] niza;
        niza = tmp;
    }
    void removeProduct(int kol){
        for(int i=0; i<n; i++){
            if(niza[i].get_kolicina()<kol){
                niza[i].zgolemi_procent(20);
            }
        }
    }
    void removeProductMax(){
        Product pmax = niza[0];
        int index = 0;
        for(int i=0; i<n; i++){
            if(niza[i].get_kolicina()>pmax.get_kolicina()){
                pmax = niza[i];
                index = i;
            }
        }
        Product *tmp = new Product[n-1];
        for(int i=0, j=0; i<n; i++){
            if(i!=index){
                tmp[j] = niza[i];
                j++;
            }
        }
        delete [] niza;
        n--;
        niza=tmp;
    }
};

int main(){
    Product p1("Pizza", 100, 5, 10);
    Product p2("Pizza1", 100, 5, 10);
    p1.print();
    p1.zgolemi_procent(10);
    p1.print();
    p1.increment();
    p1.print();
    Store s("FINKI");
    s.add(p1);
    s.add(p2);
    s.print();
}


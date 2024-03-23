#include <iostream>
#include <cstring>
using namespace std;
//vezbi 8 polimorfizam
//8.6 kolokvium oop
class GT{
protected:
    int v;
public:
    GT(int v){
        this->v=v;
    }
    void print(){
        cout<<v<<endl;
    }
    int get_visina(){
        return v;
    }
    virtual volumen() = 0;//cisto virtuelna f-ja, za da ja naprajme klasata apstraktna
};

class Cilinder : public GT{
private:
    int r;
public:
    Cilinder(int v,int r):GT(v){
        this->r=r;
    }
    float volumen(){
        return 3,14*r*r*v;
    }

};
class Kocka : public GT{
private:
    int a,b;
public:
    Kocka(int v,int a,int b):GT(v){
        this->a=a;
        this->a=a;

    }
    float volumen(){
        return a*b*v;
    }

};

class Konus : public GT{
private:
    int r;
public:
    Konus(int v,int r):GT(v){
        this->r=r;

    }
    float volumen(){
        return 3,14*r*v;
    }

};

int main() {
int n;
cin>>n;
GT **niza=new GT* [n];


    return 0;
}

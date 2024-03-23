#include <iostream>
#include <cstring>
using namespace std;

class FoodItem{
protected:
    char *type;
    int num;
    void copy(const FoodItem &other){
        this->num=other.num;
        this->type=new char[strlen(other.type)+1];
        strcpy(this->type,other.type);
    }
public:
    virtual int getPrice()=0;
    virtual int getTime()=0;
    virtual ~FoodItem(){
        delete[]type;
    }
    FoodItem(char *type="",int num=0){
        this->num=num;
        this->type=new char[strlen(type)+1];
        strcpy(this->type,type);
    }
    FoodItem(const FoodItem &other){
            copy(other);
    }
    FoodItem &operator=(const FoodItem &other){
        if(this!=&other) {
            delete[]type;
            copy(other);
        }
        return *this;
    }

    char *getType() const {
        return type;
    }
};
class Pizza:public FoodItem {
private:
    char *dough;

    void copy(const Pizza &other) {
        this->dough = new char[strlen(other.dough) + 1];
        strcpy(this->dough, other.dough);
    }

public:
    virtual int getPrice() {
        if (strcmp(this->dough, "wholeWheat") == 0) {
            return 250*num;
        }
        if (strcmp(this->dough, "glutenFree") == 0) {
            return 350*num;
        }
    }

    virtual int getTime() {
        return 25;
    }

    ~Pizza() {
        delete[]dough;
    }

    Pizza(char *type = "", int num = 0, char *dough = "") : FoodItem(type, num) {
        this->dough = new char[strlen(dough) + 1];
        strcpy(this->dough, dough);
    }

    Pizza(const Pizza &other) : FoodItem(other) {
        FoodItem::copy(other);
        copy(other);
    }

    Pizza &operator=(const Pizza &other) {
        if (this != &other) {
            FoodItem::copy(other);
            delete[]type;
            copy(other);
        }
        return *this;
    }
};

class Steak:public FoodItem {
private:
    bool cooked;
public:
    virtual int getPrice() {
        return 1300*num;
    }

    virtual int getTime() {
        if (cooked==1) {
            return 20;
        }
        if (cooked==0) {
            return 15;
        }
    }

    Steak(char *type = "", int num = 0, bool cooked = false) : FoodItem(type, num) {
        this->cooked=cooked;
    }
};
FoodItem* getMaxFoodItem(FoodItem *pItem[],int n){
FoodItem *item=pItem[0];
int maxPrice=pItem[0]->getPrice();
for(int i=0;i<n;i++){
    if(maxPrice<pItem[i]->getPrice()){
        maxPrice=pItem[i]->getPrice();
        item=pItem[i];
    }
}
return item;
}

int main() {
    FoodItem *p;
    int n;
    cin>>n;

    char type[30];
    char dough[30];
    bool cooked;
    int size;

    FoodItem *items[n];

    for (int i = 0; i <n; ++i) {
        cin>>type;
        cin>>size;


        if(strcmp(type, "pizza")==0 ) {
            cin>>dough;
            items[i] = new Pizza(type, size, dough);
        }else{
            cin>>cooked;
            items[i] = new Steak(type, size, cooked);
        }


    }

    FoodItem *it = getMaxFoodItem(items, n);
    cout<<"Type: "<<it->getType()<<endl;
    cout<<"The max price is: "<<it->getPrice()<<endl;
    cout<<"Time to cook: "<<it->getTime();
    return 0;
}
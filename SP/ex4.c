#include <stdio.h>

struct President {
    char name [100];
    char surname[100];
    char party[50];
};
typedef struct President President;
struct City {
    char name[100];
    int population;
};
typedef struct City City;
struct Country{
    char name[100];
    President president;
    City capital;
    int population;
};
typedef struct Country Country;
void readPresident(President *p){
    scanf("%s %s %s", p->name,p->surname,p->party);
}
void readCity(City *c){
    scanf("%s %d", c->name,&c->population);
}
void readCountry(Country *c){
    scanf("%s",c->name);
    readPresident(&c->president);
    readCity(&c->capital);
    scanf("%d", &c->population);
}
void printPresident(President p){
    printf("President: %s %s %s ", p.name,p.surname,p.party);
}
void printCity(City c){
    printf("Capital: %s %d ", c.name,c.population);
}
void printCountry(Country c){
    printf("%s ",c.name);
    printPresident(c.president);
    printCity(c.capital);
    printf("%d\n", c.population);
}
int compare(Country c1,Country c2){
    if(c1.capital.population>c2.capital.population){
        return 1;
    }
    else if (c1.capital.population<c2.capital.population){
        return -1;
    }
    else{
        return 0;
    }
}
int max(int *niza,int n){
    int max = niza[0];
    for(int i=0;i<n;i++){
        if(niza[i]>max){
            max=niza[i];
        }
    }
    return max;
}
void printCountryWithLargestCapital(Country *countries,int n){
    Country max = countries[0];
    for(int i=0;i<n;i++){
        if(compare(countries[i],max)>0){
            max=countries[i];
        }
    }
    printCountry(max);
}

int main() {
    Country countries[100];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        readCountry(&countries[i]);
    }
    printCountryWithLargestCapital(countries,n);

    return 0;
}

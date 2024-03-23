#include <iostream>
#include <cstring>
using namespace std;

class Book {
private:
    char *name;
    int *isbn;
    int numPages;

    void copy(const Book &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->isbn = new int[5];
        for(int i=0;i<5;i++){
            this->isbn[i]=other.isbn[i];
        }
        this->numPages = other.numPages;
    }

public:
    Book(char *name = "",int *isbn=new int[0], int numPages = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->isbn = new int[5];
        for(int i=0;i<5;i++){
            this->isbn[i]=isbn[i];
        }
        this->numPages = numPages;
    }

    Book(const Book &other) {
        copy(other);
    }

    ~Book() {
        delete[]name;
        delete[]isbn;
    }

    Book &operator=(const Book &other) {
        if (this != &other) {
            delete[]name;
            delete[]isbn;
            copy(other);
        }
        return *this;
    }

    bool operator==(const Book & b) {
        for(int i=0;i<5;i++) {
            if (this->isbn[i] != b.isbn[i]) {
                return false;
            }
        }
        return true;
    }
    friend ostream &operator<<(ostream &o,Book &p) {
        o<<"Title: "<<p.name<<"ISBN: [ ";
        for(int i=0;i<5;i++){
            if (i==4) {
                o << p.isbn[i];
            }
            else{
                o << p.isbn[i] <<" ";
            }
        }
        o<<" ]"<<endl;
        return o;
    }

    int getNumPages() const {
        return numPages;
    }
};

class BorrowABook{
private:
    char nameBook[101];
    Book *niza;
    int brKnigi;

    void copy(const BorrowABook &other) {
        strcpy(this->nameBook, other.nameBook);
        this->brKnigi = other.brKnigi;
        this->niza=new Book[other.brKnigi];
        for(int i=0;i<other.brKnigi;i++){
            this->niza[i]=other.niza[i];
        }
    }

public:
    BorrowABook(char *nameBook = "", Book *niza=0, int brKnigi = 0) {
        strcpy(this->nameBook, nameBook);
        this->brKnigi = brKnigi;
        this->niza=new Book[brKnigi];
        for(int i=0;i<brKnigi;i++){
            this->niza[i]=niza[i];
        }
    }

    BorrowABook(const BorrowABook &other) {
        copy(other);
    }

    ~BorrowABook() {
        delete[]niza;
    }

    BorrowABook &operator=(const BorrowABook &other) {
        if (this != &other) {
            delete[]niza;
            copy(other);
        }
        return *this;
    }
    BorrowABook &operator+=(const Book & b){
        Book *tmp=new Book[brKnigi+1];
        for(int i=0;i<brKnigi;i++){
            tmp[i]=niza[i];
        }
        tmp[brKnigi++]=b;
        delete[]niza;
        niza=tmp;
        return *this;

    }
    BorrowABook &operator-=(const Book & b){
        Book *tmp=new Book[brKnigi-1];
        for(int i=0,j=0;i<brKnigi;i++){
            if(niza[i] == b) {
                continue;
            }
            else{
                tmp[j++] = niza[i];
            }
        }
        brKnigi--;
        delete[]niza;
        niza=tmp;
        return *this;

    }
    void printNumberOfPages(int max){
        cout<<nameBook<<endl;
        for(int i=0;i<brKnigi;i++){
            if(max<niza[i].getNumPages()){
                cout<<niza[i];
            }
        }
    }
};
// 2
/// Do NOT edit the main() function
int main()
{
    BorrowABook library("FINKI-Library");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char title[100];
        int isbn[5];
        int pages;

        cin>>title;

        for (int i=0;i<5;i++)
            cin>>isbn[i];

        cin>>pages;

        Book nov=Book(title,isbn,pages);

        //adding a new book
        library+=nov;
    }

    //the book which has the same isbn as some previous one
    char title[100];
    int isbn[5];
    int pages;
    cin>>title;
    for (int i=0;i<5;i++)
        cin>>isbn[i];
    cin>>pages;

    Book greshka=Book(title,isbn,pages);

    //deleting a book
    library-=greshka;

    library.printNumberOfPages(150);

    return 0;
}
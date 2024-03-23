#include <iostream>
#include <cstring>
using namespace std;

class Game{
protected:
    char title[6];
public:
    Game(char *title=""){
        strcpy(this->title,title);
    }
    virtual void displayInfo(){
        cout<<"Game: "<<title<<endl;
    }
    virtual int complexity()=0;
};
class BoardGame:virtual public Game{
protected:
    int maxPlayers;
public:
    BoardGame(char *title="",int maxPlayers=0): Game(title){
        this->maxPlayers=maxPlayers;
    }
    int complexity() override{
        if(maxPlayers>6){
            return 10;
        }
        else if(3<maxPlayers&&maxPlayers<6){
            return 5;
        }
        else if(maxPlayers<3){
            return 3;
        }
    }
    void displayInfo() override{
        Game::displayInfo();
        cout<<"Max players: "<<maxPlayers<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }
};
class CardGame:virtual public Game{
protected:
    int numCards;
public:
    CardGame(char *title="",int numCards=0): Game(title){
        this->numCards=numCards;
    }
    int complexity() override{
        if(numCards>20){
            return 10;
        }
        else if(10<numCards && numCards<20){
            return 5;
        }
        else if(numCards<10){
            return 3;
        }
    }
    void displayInfo() override{
        Game::displayInfo();
        cout<<"Number of cards: "<<numCards<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }

    int getNumCards() const {
        return numCards;
    }
};
class BoardCardGame:public BoardGame,public CardGame{
public:
    BoardCardGame(char *title="",int numCards=0,int maxPlayers=0): Game(title),CardGame(title,numCards), BoardGame(title,maxPlayers){
    }
    int complexity() override{
        return (CardGame::complexity()+BoardGame::complexity())/2;
    }
    void displayInfo() override{
        Game::displayInfo();
        cout<<"Complexity: "<<complexity()<<endl;
    }
};
Game *mostComplexCardGame(Game **games, int n){
    Game *mostComplex= nullptr;
    int complexity=0;
    int flag = 0;
    for(int i=0;i<n;i++){
        CardGame *card=dynamic_cast<CardGame*>(games[i]);
        if(card){
            if(flag==0) {
                complexity = card->complexity();
                flag= 1;
            }
            if(flag && (complexity < card->complexity())){
                complexity=card->complexity();
                mostComplex=card;
            }
        }
    }
    return mostComplex;
}

int main() {
    char title[50];
    int maxPlayers;
    int numCards;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>title;
        BoardCardGame boardCardGame(title, 8, 15);
        boardCardGame.displayInfo();
    }
    else {

        cin >> n;

        Game **g = new Game *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> title >> maxPlayers;

                g[i] = new BoardGame(title, maxPlayers);
            } else {
                cin >> title >> numCards;

                g[i] = new CardGame(title, numCards);
            }

        }

        mostComplexCardGame(g,n)->displayInfo();

    }

    return 0;
}
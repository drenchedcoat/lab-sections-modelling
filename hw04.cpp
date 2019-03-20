#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


//--------------WARRIOR CLASS----------------
class Warrior{
private:
    string name;
    int hp;
    bool stat = false; // true= is hired, false= is fired/nobleless
public:
    //constructor
    Warrior (const string& hisName, const int& hisHP) : name(hisName), hp(hisHP) {}

    //setters
    void setHP(const int& newHP) { hp = newHP; }
    bool status() const { return stat; }
    void makeStat(const bool& boole) { stat = boole; }

    //getters
    string getName() const { return name; }
    int getHP() const { return hp; }

};


//--------------NOBLE CLASS----------------
class Noble{
private:
    string name;
    vector<Warrior*> warriors;
    double strength = 0;
public:
    //constructor
    Noble(const string& nobleName) : name(nobleName){}

    //getters
    int getStr()const { return strength; }
    string getName() const { return name; }

    //for ever warrior, decrease its hp by percentage passed in
    //if passed in is 0, they die, if 1, no change, if .5, hp halved, etc
    void decreaseBy(const double& percent){

        for (Warrior* warrior : warriors){
            warrior->setHP(warrior->getHP()*percent); //set hp of each warrior
            if (percent == 0){ warrior->makeStat(false); } //death case
        }strength = strength*percent; //set noble hp
    }

    bool hire(Warrior &newGuy){
        if (newGuy.status()==false){
            warriors.push_back(&newGuy); // adds warrior to noble class' vector
            strength += newGuy.getHP(); //noble is strengthened
            newGuy.makeStat(true); //set noble to busy af
            return true;
        }
        //if warrior already has a noble
        cout << "Could not hire, already in a noble." << endl;
        return false;
    }

    void display() const {
        cout << name << " has an army of " << warriors.size() << endl;
        for (Warrior* warrior : warriors){
            cout << "\t" << warrior->getName() << ": " << warrior->getHP() << endl;
        }
    }

    bool fire(Warrior &thisGuy){ //returns false if warrior not in noble
        for (size_t i = 0; i < warriors.size(); ++i){
            if (warriors[i] == &thisGuy) {
                cout << warriors[i]->getName() << ", you're fired! -- " << name << endl;
                strength -= warriors[i]->getHP(); //decrease noble HP when fired
                warriors[i]->makeStat(false); //warrior is now available for new noble
                warriors.erase(warriors.begin() + i); //remove from noble's vector
                return true;
            }
        }
        cout << "Could not fire, warrior not in this noble!" << endl;
        return false; //if the warrior doesn't exist in noble, return false
    }


    void battle(Noble &enemyNoble){
        cout << name << " battles " << enemyNoble.getName() << endl;

        //if any are dead
        if (strength==0 && enemyNoble.getStr()==0) { //if both dead
            cout << "OH, NO! They're both dead! Yuck!" << endl;
        } else if (strength == 0) { //if self is dead
            cout << "He's dead, " << enemyNoble.getName() << endl;
        } else if (enemyNoble.getStr()==0){  //if enemy is dead
            cout << "He's dead, " << name << endl;
        }

        //if both alive
        else{
            if (strength > enemyNoble.getStr()){ //if self stronger than enemy
                this->decreaseBy(1-(enemyNoble.getStr() / strength)); //decrease self noble hp
                enemyNoble.decreaseBy(0); //kill all of enemyNoble
                cout << name << " defeats " << enemyNoble.getName() << endl;


            } else if (strength < enemyNoble.getStr()){ // if enemy stronger
                enemyNoble.decreaseBy(1-(strength / enemyNoble.getStr())); //decrease enemyNoble hp
                this->decreaseBy(0); //kill all of self
                cout << enemyNoble.getName() << " defeats " << name << endl;

            } else { // kill both party woohoo
                decreaseBy(0);
                enemyNoble.decreaseBy(0);

                cout << "Mutual Annihalation: " << name << " and "
                     << enemyNoble.getName() << " die at each other's hands" << endl;
            }
        }
    }
};




//-------------------MAIN----------------------
int main() {

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);

    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();


    art.fire(cheetah);
    art.display();

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

}

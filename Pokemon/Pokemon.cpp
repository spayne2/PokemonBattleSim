#include <iostream>
#include <string>
#include <ctime>
using namespace std;

enum class Type { Fire, Water, Grass, Normal };

class Pokemon
{
private:
    string name;
    int level;
    int health;
    int maxHealth;
    Type type;
    bool knockedOut;
public:
    Pokemon()
    {
        name = "";
        level = 1;
        health = 1;
        maxHealth = 1;
        type = Type::Normal;
        knockedOut = false;
    }
    //To create a pokemon, give it a name, type, and level. Its max health is determined by its level. Its starting health is its max health and it is not knocked out when it starts.
    Pokemon(string n, int l, int h, int mh, Type t, bool ko)
    {
        name = n;
        level = l;
        health = h;
        maxHealth = mh;
        type = t;
        knockedOut = ko;
        srand(time(NULL));
    }
    string getType()
    {
        if (type==Type::Fire)
        {
            return "Fire";
        }
        else if (type == Type::Water)
        {
            return "Water";
        }
        else
        {
            return "Grass";
        }
    }
    //Printing a pokemon will tell you its name, its type, its level and how much health it has remaining
    void display()
    {
        cout << "This level " << level << " " << name << " has " << health << " hp remaining , they are a " << getType() << " type pokemon" << endl;
    }

    void revive()
    {
        //Reviving a pokemon will flip it's status to False
        knockedOut = false;
        health = 1;
        cout << name << " was revived!" << endl;
    }

    void knockOut()
    {
        //Knocking out a pokemon will flip its status to True.
        knockedOut = true;
        //A knocked out pokemon can't have any health.
        health = 0;
        cout << name << " was knocked out!" << endl;
    }

    void loseHealth(int amount)
    {
        //Deducts heath from a pokemon and prints the current health reamining
        health -= amount;
        if (health <= 0)
        {// Makes sure the health doesn't become negative. Knocks out the pokemon.
            health = 0;
            knockOut();
        }
        else
        {
            cout << name << " now has " << health << " remaining " << endl;
        }
    }

    void gainHealth(int amount)
    {//Adds to a pokemon's health
        //If a pokemon goes from 0 heath, then revive it
        if (health == 0)
        {
            revive();
        }
        health += amount;
        //Makes sure the heath does not go over the max health
        if (health >= maxHealth)
        {
            health = maxHealth;
        }
        cout << name << " now has " << health << " remaining " << endl << endl;
    }

    void attack(Pokemon &otherPokemon)
    {//Checks to make sure the pokemon isn't knocked out
        if (knockedOut)
        {
            cout << name << " can't attack becuase it is knocked out " << endl;
        }//If the pokemon attacking has a disadvantage, then it deals damage equal to half its level to the other pokemon
        else if ((type == Type::Fire && otherPokemon.type == Type::Water) || (type == Type::Water && otherPokemon.type == Type::Grass) || (type == Type::Grass && otherPokemon.type == Type::Fire))
        {//damage dealt is a random number between 0 and the level
            float damage = (1+rand()%level) * 0.5; //for weak type it is half;
            cout << name << " attacked " << otherPokemon.name << " for " << damage << " damage " << endl;
            cout << "Its not very effective." << endl;
            otherPokemon.loseHealth(damage);
        }//f the pokemon attacking has neither advantage or disadvantage, then it deals damage equal to its level to the other pokemon
        else if (type == otherPokemon.type)
        {//damage dealt is a random number between 0 and the level
            int damage = (1+rand() % level);
            cout << name << " attacked " << otherPokemon.name << " for " << damage << " damage " << endl;
            otherPokemon.loseHealth(damage);
        }//If the pokemon attacking has advantage, then it deals damage equal to double its level to the other pokemon
        else if ((type == Type::Fire && otherPokemon.type == Type::Grass) || (type == Type::Water && otherPokemon.type == Type::Fire) || (type == Type::Grass && otherPokemon.type == Type::Water))
        {//damage dealt is a random number between 0 and the level
            int damage = (1+rand() % level) * 2; //time 2 for strong type
            cout << name << " attacked " << otherPokemon.name << " for " << damage << " damage " << endl;
            cout << "Its super effective." << endl;
            otherPokemon.loseHealth(damage);
        }
        cout << endl;
    }
    string getName()
    {
        return name;
    }
    bool isKnockedOut()
    {
        return knockedOut;
    }

};
class Trainer
{
private:
    //A trainer has a one pokemon, a number of potions and a name. When the trainer gets created, they are assigned a pokemon
    Pokemon pokemon;
    string name;
    int numOfPotions;

public:
    Trainer(Pokemon p, string n, int pot) 
    {
        pokemon = p;
        name = n;
        numOfPotions = pot;
    }
    void display()
    {//displa the trainer name and thier pokemon to the screen
        cout << "Trainer " << name << " has the pokemon " << pokemon.getName() << endl;
    }

    void usePotion()
    {//Uses a potion on the active pokemon, assuming you have at least one potion.
       
        if (numOfPotions > 0)
        {
            cout << name << " Used a potion ";
            //decrement number of potions
            numOfPotions -= 1;
            //a potion restores 20 health;
            pokemon.gainHealth(20);           
        }
        else
        {
            cout << "You do not have any potions" << endl;
        }
        
    }
    void attackOtherTrainer(Trainer &otherTrainer)
    {//attack the other trainers pokemon;
        pokemon.attack(otherTrainer.pokemon);
    }
    Pokemon getPokemon()
    {
        return pokemon;
    }
    string getName()
    {
        return name;
    }
    int getNumOfPotions()
    {
        return numOfPotions;
    }
};
void getBattleAction(Trainer &trainer1, Trainer &trainer2)
{//get the trainers input for attack or use potion
    int trainerInput;
    cout << trainer1.getName() << ": Choose your action:" << endl;
    cout << "1. Attack " << endl;
    cout << "2. Potion " << endl;
    cin >> trainerInput;
    switch (trainerInput)
    { //if the trainer uses 1,the attack the other trainers pokemon
    case 1:
        trainer1.attackOtherTrainer(trainer2);
        break;
    case 2://if the trainer uses 2, the use a potion ont thier own potion
        trainer1.usePotion();
        break;
    default:
        break;
    }
}

int main()
{//Three objects that are of Pokemon type. Charmander is a fire type, Squirtle is a Water type, and Bulbasaur is a Grass type.
   Pokemon charmander("Charmander", 10, 50, 50, Type::Fire, false);
   Pokemon Squirtle("Squirtle", 12, 60, 60, Type::Water, false);
   Pokemon Bulbasaur("Bulbasaur", 8, 40, 40, Type::Grass, false);

   //invite trainers to enter thier names
   cout << "Welcome to pokemon battle simulator" << endl;
   cout << "Trainer 1: Please enter your name " << endl;
   string trainer1name;
   getline(cin, trainer1name);

   Trainer trainer1(charmander, trainer1name, 5);

   cout << "Trainer 2: Please enter your name " << endl;
   string trainer2name;
   getline(cin, trainer2name);

   Trainer trainer2(Bulbasaur, trainer2name, 5);
   //display trainer information to the screen
   trainer1.display();
   trainer1.getPokemon().display();

   trainer2.display();
   trainer2.getPokemon().display();
   bool stillBattling = true;


   while (stillBattling) //keep the game loop going
   {
       getBattleAction(trainer1, trainer2);
       getBattleAction(trainer2, trainer1);// if a pokemon is knocked out then declare the other trainer the winner
       
       if (trainer1.getPokemon().isKnockedOut()&&trainer1.getNumOfPotions()==0) //if a pokemon is knocked out then end the battle and the trainer as no potions then it is game over
       {
           stillBattling = false;
           cout << trainer1.getName()<<"'s pokemon is knocked out " << trainer2.getName()<<" wins" << endl;
       }
       else if (trainer2.getPokemon().isKnockedOut() && trainer2.getNumOfPotions()==0)
       {
           stillBattling = false;
           cout << trainer2.getName() << "'s pokemon is knocked out " << trainer1.getName() << " wins" << endl;
       }
      
   }
  
}



#include <iostream>
#include <string>
#include <ctime>
using namespace std;

enum class Type { Fire, Water, Grass, Normal }; // Use enum for types. This makes the code easier, and we don't need string comparissons.

class Pokemon
{
private:
    string name; //the pokemons name
    int level; //the pokemons level, this is used to caclulate damage for an attack
    int health;// the pokemons current health, if this gets to 0 they are knocked out
    int maxHealth; // the maximum health the pokemon can have
    Type type;// the pokemons elemental type, this is used in attacking to check for effectiveness
    bool knockedOut; // if this is true, the pokemon is kockedout (note this could be replace with just a fuction that checks if helth is less than 0 but I wanted to have a varaible)
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
    //To create a pokemon, give it a name, type, and level. Its starting health is its max health and it is not knocked out when it starts.
    Pokemon(string n, int l, int mh, Type t)
    {
        name = n;
        level = l;
        health = mh;
        maxHealth = mh;
        type = t;
        knockedOut = false;
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
    //Printing a pokemon will give you all the info about the pokemon: its name, its type, its level and how much health it has remaining
    void display()
    {
        cout << "This level " << level << " " << name << " has " << health << " hp remaining , they are a " << getType() << " type pokemon" << endl << endl;
    }

    void revive()
    {
        //Reviving a pokemon will set knockedOut to false
        knockedOut = false;
        if (health <= 0) { //safety check, if the pokemon has somehow been revived but the health is still 0 or less then set it to 1.
            health = 1;
        }
        cout << name << " was revived!" << endl;
    }

    void knockOut()
    {
        //Knocking out a pokemon change knockedOut to true
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
        }//If the pokemon attacking has a disadvantage, then it only does half damage
        else if ((type == Type::Fire && otherPokemon.type == Type::Water) || (type == Type::Water && otherPokemon.type == Type::Grass) || (type == Type::Grass && otherPokemon.type == Type::Fire))
        {//damage dealt is a random number between 1 and the level
            float damage = (1+rand()%level) * 0.5; //for weak type it is half;
            cout << name << " attacked " << otherPokemon.name << " for " << damage << " damage " << endl;
            cout << "Its not very effective." << endl;
            otherPokemon.loseHealth(damage);
        }//f the pokemon attacking has neither advantage or disadvantage then there is no modifier
        else if (type == otherPokemon.type)
        {//damage dealt is a random number between 1 and the level
            int damage = (1+rand() % level);
            cout << name << " attacked " << otherPokemon.name << " for " << damage << " damage " << endl;
            otherPokemon.loseHealth(damage);
        }//If the pokemon attacking has advantage, then it deals double damage
        else if ((type == Type::Fire && otherPokemon.type == Type::Grass) || (type == Type::Water && otherPokemon.type == Type::Fire) || (type == Type::Grass && otherPokemon.type == Type::Water))
        {//damage dealt is a random number between 1 and the level
            int damage = (1+rand() % level) * 2; //times 2 for strong type
            cout << name << " attacked " << otherPokemon.name << " for " << damage << " damage " << endl;
            cout << "Its super effective." << endl;
            otherPokemon.loseHealth(damage);
        }
        cout << endl;
    }
    string getName() //return the pokemons name
    {
        return name;
    }
    bool isKnockedOut() //check if the pokemon is knocked out
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
    {//display the trainer name and thier pokemon to the screen
        cout << "Trainer " << name << " has the pokemon " << pokemon.getName() << endl;
    }

    void usePotion()
    {//Uses a potion on pokemon, assuming you have at least one potion.
       
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
    void attackOtherTrainer(Trainer &otherTrainer) //trainer is passed by reference
    {//attack the other trainers pokemon;
        pokemon.attack(otherTrainer.pokemon);
    }
    Pokemon getPokemon() //return the pokemon object
    {
        return pokemon;
    }
    string getName() //return the trainers name
    {
        return name;
    }
    int getNumOfPotions()// return the number of potions, this is used as a check alongside if the pokemon is knocked out
    {
        return numOfPotions;
    }
};
//trainers are passed by reference, so that the values are operated on correctly.
void getBattleAction(Trainer &trainer1, Trainer &trainer2)
{//get the trainers input for attack or use potion
    int trainerInput;
    cout << trainer1.getName() << ": Choose your action:" << endl;
    cout << "1. Attack " << endl;
    cout << "2. Potion: You have " << trainer1.getNumOfPotions() << " potions remaining" << endl;
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
   Pokemon charmander("Charmander", 10, 50, Type::Fire); //constructure is the name, the level, the health and the type
   Pokemon Squirtle("Squirtle", 12, 60, Type::Water);
   Pokemon Bulbasaur("Bulbasaur", 8, 40, Type::Grass);

   //invite trainers to enter thier names
   cout << "Welcome to pokemon battle simulator" << endl;
   cout << "Trainer 1: Please enter your name " << endl;
   string trainer1name;
   getline(cin, trainer1name);

   Trainer trainer1(charmander, trainer1name, 5);

   cout << "Trainer 2: Please enter your name " << endl;
   string trainer2name;
   getline(cin, trainer2name);

   cout << endl;

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
       
       if (trainer1.getPokemon().isKnockedOut() && trainer1.getNumOfPotions()==0) //if a pokemon is knocked out then end the battle and the trainer as no potions then it is game over
       {
           stillBattling = false; //the battle will only end if a pokemon is knocked out and the trainer as no potions
           cout << trainer1.getName()<<"'s pokemon is knocked out " << trainer2.getName()<<" wins" << endl;
       }
       else if (trainer2.getPokemon().isKnockedOut() && trainer2.getNumOfPotions()==0)
       {
           stillBattling = false; //the battle will only end if a pokemon is knocked out and the trainer as no potions
           cout << trainer2.getName() << "'s pokemon is knocked out " << trainer1.getName() << " wins" << endl;
       }      
   }
  
}



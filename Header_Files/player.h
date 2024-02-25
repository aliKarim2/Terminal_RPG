#pragma once

#include <iostream>
#include <iomanip>
#include "Header_Files\enemy.h"
#include "Header_Files\item.h"
#include "Header_Files\armor.h"
#include "Header_Files\weapon.h"
#include "Header_Files\potion.h"
#include "Header_Files\placedObject.h"
// class Item;
// class Enemy;
// class Boss;
// class Weapon;
// class Armor;
// class Potion;

class Player : public placedObject{
    std::string name;
    unsigned int score = 0; //goes up as more enemies killed


    //HP
    int maxHP = 300;
    int HP = 100;
    
    std::shared_ptr<Weapon> currentWeapon;
    std::shared_ptr<Armor> currentArmor;
    std::vector<std::shared_ptr<Potion>> currentPotions;
    static const int MAX_POTIONS;
    
    //Damage
    unsigned int damage = 500; //TEST VALUE
    unsigned int damageMult = 1;
    unsigned int totalDamage = damage * damageMult;


public:
    Player(const std::string& myName) 
    : name(myName), currentPotions(MAX_POTIONS, nullptr), currentArmor(nullptr), currentWeapon(nullptr){
        //currentPotions has size 5, with all nullPtr (empty potions)

        const Coord ORIGIN = {0,0};
        coord = ORIGIN;

        
    }

    void Update(){//loads every time user inputs
        const int FW = 50; //screen length
        //calculate what has changed

        /*What is shown
        Score: 0                                         Coords: <0,0>
                                                         HP: 100
                                                         DMG: 500
        
        
        */


        //Output stuff
        std::cout << "Score: " << std::left << std::setw(FW) << score; //HP Bar
        std::cout << "Coords: " << '<' << coord.x << ',' << coord.y << '>'; //Coord Bar
        std::cout << '\n';
        std::cout << std::right << std::setw(FW+11) << "HP: " << HP;
        std::cout << '\n';
        std::cout << std::right << std::setw(FW+12) << "DMG: " << totalDamage;
        std::cout << '\n';
        
    }
    void move(){//moves player (wasd)
        Update();

        // const int tries = 3;
        const char INVALID = '~';

        std::string input;
        bool validationReq;

        bool valid = false;

        std::cout << "\n\n\n\n";
        
        std::cout << "Move (wasd):\n";
        do{
            valid = false; //reset to false every time
            std::cin >> input; //get input


            //checks if input is char and is wasd
            if(input.size() == 1){//if char
                //make lowercase
                input[0] = tolower(input[0]);
        
                //wasd requirement boolean expression
                validationReq = (input[0] == 'w' || input[0] == 'a' || input[0] == 's' || input[0] == 'd');

                //check wasd
                if(validationReq){
                    // std::cout << "VALID INPUT!\n";
                    valid = true;
                }
            }
            //if not, then valid will be false

                
                
            //error msg
            if(!valid){
                std::cout << "Enter 'w' 'a' 's' or 'd'\n";
            }

        }while(!valid);    

    //    std::cout << "INPUT WAS: " << input << '\n';

        //change string into char
        char myChar = input[0];

        //calculate change in position
        switch(myChar){
            case 'w': coord.y++;
                break;
            case 's': coord.y--;
                break;
            case 'a': coord.x--;
                break;
            case 'd': coord.x++;
                break;
        }

        const int BOUNDS = 5;


        //check bounds
        if(coord.x > BOUNDS)
            coord.x = BOUNDS;
        else if(coord.x < -BOUNDS)
            coord.x = -BOUNDS;
        
        if(coord.y > BOUNDS)
            coord.y = BOUNDS;
        else if(coord.y < -BOUNDS)
            coord.y = -BOUNDS;


        //Show new Info
        // Update();
    }
    int atkChoice(){

        const int EXIT_VALUE = -1;
        const int MAX_TRIES = 3;
        int tries = 0;

        const int FW = 50;
        int op;
        bool valid = false;

        //output the line seperating info from choices
        std::cout << std::left;
        std::cout << std::setw(FW) << std::setfill('_') << '_' << std::endl; 
        std::cout << std::setfill(' ');

        //give choices
        std::cout << std::right;
        std::cout << std::setw(FW/2 - 5) << "(1)" << "ATTACK" << '\n';
        std::cout << std::setw(FW/2 - 5) << "(2)" << "ITEM" << '\n';
        std::cout << std::setw(FW/2 - 5) << "(3)" << "RUN" << '\n';


        //make sure op is 1 2 or 3
        do{
            std::cin >> op;

            valid = false;
            if(op == 1 || op == 2 || op == 3){ //check if 1-3
                std::cout << "VALID BATTLE OP\n";
                valid = true;
            }
            
            if(MAX_TRIES - tries == 0){
                return EXIT_VALUE;
            }

            //error msg
            if(!valid){
                std::cout << "Enter 1-3. " << MAX_TRIES - tries << " tries remaining.\n";
            }
            

            tries++; //add to tries

        }while(!valid);

        //calculate what to do based on op
        switch(op){
            case 1: std::cout << "attacks!\n";
                break;
            case 2: std::cout << "Uses item!\n";
                break;
            case 3: std::cout << "Runs away!\n";
                break;
            default: std::cout << "Critical Error!\n";
                break;
        }

        return op;
    }


    void setWeapon(std::shared_ptr<Weapon> weapon){
        currentWeapon = weapon;
    }
    void setArmor(std::shared_ptr<Armor> armor){
        currentArmor = armor;
    }
    bool addPotion(std::shared_ptr<Potion> potion){
        bool filled = false;

        

        //Loop thru currentPotions vector and find the first empty slot
        for(int i = 0; i < currentPotions.size(); i++){
            if(currentPotions[i] == nullptr){
                //if a slot is empty, fill it
                currentPotions[i] = potion;
                filled = true;
                break;
            }
        }
        if(!filled){
            // std::cout << "ERROR IN PLAYER.H addPotion: NO SLOTS AVAILABLE?\n";
            return false; //return false in case of filled list error
        }
        return true;
    }
    

    //getters and setters
    void changeScore(int value){
        score += value;

        if(score < 0)
            score = 0;
        
    }
    unsigned int getScore(){return score;}
    
    Coord getCoord(){return coord;}
    
    std::string getName(){return name;}

    int getHP(){return HP;}
    int getMaxHP(){return maxHP;}
    void setHP(int value){
    HP = value;
        if(HP < 0)
            HP = 0;
    }

    unsigned int getDamage(){return damage;}
    unsigned int getDamageMult(){return damageMult;}
    unsigned int getTotalDamage(){return totalDamage;}

    std::shared_ptr<Armor>& getArmor(){return currentArmor;}
    std::shared_ptr<Weapon>& getWeapon(){return currentWeapon;}
    std::vector<std::shared_ptr<Potion>>& getPotions(){return currentPotions;}
    // std::shared_ptr<Armor> getArmor(){return currentArmor;}

   };
const int Player::MAX_POTIONS = 5;

// const int Player::xValues = 21;
// const int Player::yValues = 21;

// bool Player::map[Player::xValues][Player::yValues] = {{false}};  // All values initialized to false

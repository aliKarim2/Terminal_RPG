#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "Header_Files/random.h"
#include "Header_Files/chest.h"
#include "Header_Files/placedObject.h"

class Player;



class Enemy : public placedObject{
private:
    static std::vector<Coord> usedCoords;
    
    //Constructor Functions
   
protected:
    virtual void fillLists()=0;

    // std::vector<std::shared_ptr<Item>> loot;
    Chest dropLoot;

    // static const int ENEMY_SCORE_MULTIPLIER;
    std::string name;
    int HP;
    int ID; //holds the index of enemy in respective vector (enemies or bosses)

    int damage;
    int damageMult = 1;
    
    int scoreValue; //score given when killed
    
public:
    bool test = false;
    Enemy(){
    //Coord
        makeCoord();
    }
    
    ~Enemy(){

        // if(!test)
            // std::cout << name << " DIED!!!\n";
    }

    virtual void make(int ct)=0;
    
    virtual void showInfo(){
        const int FW = 20;
        std::cout << std::left;
        std::cout << name << '\n';
        std::cout << "HP: " << HP << '\n';
        std::cout << "ATK: " << damage;
        std::cout << '\n';
    }
    


    //sets enemy spawn out of player bounds so can't fight anymore
    void setOutOfBounds(){
        //10,10 is out of bounds for player
        coord.x = 12;
        coord.y = 12;
    }

    //GETTERS and SETTERS
    std::string getName()const{return name;}
    int getHP()const{return HP;}
    int getDamage()const{return damage;}
    int getDamageMult()const{return damageMult;}
    int getTotalDamage()const{return damage * damageMult;}
    int getScore()const{return scoreValue;}
    int getXcoord()const{return coord.x;}
    int getYcoord()const{return coord.y;}
    int getID()const{return ID;}
    void setHP(int value){
            HP = value;
            if(HP < 0)
                HP = 0;
        }
    
    Coord getCoord()const{return coord;}
    void displayCoord(){
        std::cout << coord.x << ' ' << coord.y;
    }


    Chest getLoot(){return dropLoot;}

    static std::vector<Coord> getUsedCoords(){return usedCoords;}


};
//initialize static variables
std::vector<Coord> Enemy::usedCoords;


// std::vector<int> Enemy::usedEnemyNames;
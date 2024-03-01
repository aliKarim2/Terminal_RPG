#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "random.h"
#include "chest.h"
#include "placedObject.h"

class Player;



class Enemy : public placedObject{
private:
    static std::vector<Coord> usedCoords;
    
    //Constructor Functions`
   
protected:
    virtual void fillLists()=0;

    // std::vector<std::shared_ptr<Item>> loot;
    Chest dropLoot;

    // static const int ENEMY_SCORE_MULTIPLIER;
    std::string name;
    int HP;

    int damage;
    int damageMult = 1;
    
    int scoreValue; //score given when killed
    
public:
    bool test = false;
    Enemy(){
    //Coord
        makeCoord();


    //Damage and HP
        const int MIN_STAT = 200;
        const int MAX_STAT = 400;


        int statpts = Random::getRandomInt(MIN_STAT,MAX_STAT); //stat points will be equal to boss hp + damage for balancing purposes
        
        
        damage = Random::getRandomInt(statpts/5, 4*statpts/5); //damage can be 1/5 statpts to 4/5 statpts
        HP = (statpts - damage); //HP will be based off of precalculated damage

    //Score drop
        scoreValue = statpts; //add a multiplier in child classes if needed


    }
    
    virtual ~Enemy(){

        // for(const auto& item : dropLoot.getLoot()){
        //     item->overrideDestructor(); //set all items in chest as test objects, so that they dont have destructor msg
        // }


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
    void setHP(int value){
            HP = value;
            if(HP < 0)
                HP = 0;
        }
    
    Coord getCoord()const{return coord;}
    void displayCoord()const{
        std::cout << coord.x << ' ' << coord.y;
    }


    Chest getDrops()const{return dropLoot;}



};
//initialize static variables
std::vector<Coord> Enemy::usedCoords;


// std::vector<int> Enemy::usedEnemyNames;
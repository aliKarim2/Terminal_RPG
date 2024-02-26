#pragma once
#include <iostream>
#include "item.h"


class Weapon : public Item{
    static std::vector<std::shared_ptr<Weapon>> weapons;

    int damage;


    //constructor functions
    void makeName() override{
        std::string legendaryNames [4] = { "Excalibur of Flame", "Cutlass of Divination", 
                                           "Longsword of Fury", "Saber of Transcendence"};
        std::string epicNames [4] = { "Thunderous Broadsword", "Majestic Rapier", "Hero's Blade", "Arcane's Edge"};
        std::string rareNames [4] = { "Grand Blade", "Flame Spear", "Shining Katana", "Steel Scimitar"};
        std::string uncommonNames [4] = { "Sharp Edge", "Swift Scimitar", "Trusty Blade", "Iron Stake"};
        std::string commonNames [4] = { "Training Stick", "Wooden Pole", "Stone Axe", "Dull Sword"};

        
            int index = Random::getRandomInt(0, 3);
            // std::cout << "INDEX: " << index << '\n';    

            name = "ERROR"; //set to default value (should be changed later)

            switch(rarity.level){
                case Level::LEGENDARY:
                    name = legendaryNames[index];
                    break;
                case Level::EPIC:
                    name = epicNames[index];
                    break;
                case Level::RARE:
                    name = rareNames[index];
                    break;
                case Level::UNCOMMON:
                    name = uncommonNames[index];
                    break;
                case Level::COMMON:
                    name = commonNames[index];
                    break;
                default:
                    std::cout << "ERROR in weapon.h makeName()\n";
            }        
    }
    void makeDamage(){
        /*
        DAMAGE = rarityDMG + SPREAD
        - Legendary ex: 450 + 26
        - Epic: 350 + 30
        - Rare: 250 + 10


        all dmg will be %5
        L   450-500
        E   350-400
        R   250-300
        U   150-200
        C   50-100 
        */
       //min strength for each rarity level
       const int legendaryDamage = 450;
       const int epicDamage = 350;
       const int rareDamage = 250;
       const int uncommonDamage = 150;
       const int commonDamage = 50;

       const int SPREAD = Random::getRandomInt(0,50);

       /*
       this line correctly spawns a value between 450-500 that is a multiple of 5
       legendaryDamage + SPREAD - (legendaryDamage + SPREAD) % 5;

       legDMG = 450, let SPREAD = 13

       450 + 13 - (450+13) %5
       463 - 463 % 5
       463 - 3

       return 460
       */

        damage = 9999; //set it to a default value

        switch(rarity.level){
                case Level::LEGENDARY:
                    damage = legendaryDamage + SPREAD - (legendaryDamage + SPREAD) % 5;
                    break;

                case Level::EPIC:
                    damage = epicDamage + SPREAD - (epicDamage + SPREAD) % 5;
                    break;

                case Level::RARE:
                    damage = rareDamage + SPREAD - (rareDamage + SPREAD) % 5;
                    break;

                case Level::UNCOMMON:
                    damage = uncommonDamage + SPREAD - (uncommonDamage + SPREAD) % 5;
                    break;

                case Level::COMMON:
                    damage = commonDamage + SPREAD - (commonDamage + SPREAD) % 5;
                    break;
                default:
                    std::cout << "ERROR in weapon.h makeName()\n";
        }
        
    }

public:
    Weapon(){
    //DAMAGE
        makeDamage(); 

    //NAME
        makeName();
    }
    Weapon(float myRarityBegin, float myRarityEnd){
        makeRarity(myRarityBegin, myRarityEnd); //makes rarity specific (override default rarity from item.h)
    //DAMAGE
        makeDamage(); 

    //NAME
        makeName();
    }
    ~Weapon()override{
        // if(!test)
        //     std::cout << "Weapon destructor!\n";
    }
    virtual void make(int ct) override{
        for (int i = 0; i < ct; i++){
            std::shared_ptr<Weapon> ptr = std::make_shared<Weapon>();
            personalizedListIndex = Item::getList().size();
            itemListIndex = weapons.size();

            weapons.push_back(ptr); //add to list
            Item::getList().push_back(ptr);
        }
    }

    std::string getItemType()const override{return "(WEAPON)";}
    static std::vector<std::shared_ptr<Weapon>>& getList(){return weapons;}
    int getDamage()const{return damage;}
};

std::vector<std::shared_ptr<Weapon>> Weapon::weapons;

#pragma once
#include <iostream>
#include "item.h"


class Armor : public Item{
    static std::vector<std::shared_ptr<Armor>> armors;
    int HP;

    void makeName()override{
        /*NAME FORMULA
        adj + swordName

        - exalted blade
        - flaming spear
        - basic spear
        - Dull stick
        */
    //    std::cout << "MAKING ARMOR NAMES"
        std::string legendaryNames [4] = { "Celestial Aegis", "Terasteel Battlegear", "Supreme Bulwark", "Divine Drapes"};
        std::string epicNames [4] = { "Dark Knight's Platings", "Wizard's Drapes", "Emerald Gear", "Revered Raiments" };
        std::string rareNames [4] = { "Veteran's Metal Gear", "Steel Armor", "Masterful Cloak", "Protective Platings" };
        std::string uncommonNames [4] = { "Chainmail Armor", "Soldier Uniform", "Iron Armor", "Basic Platings" };
        std::string commonNames [4] = { "Raggedy Garments", "Ordinary Coverings", "Civilian Attire", "Leather Paddings" };


        //if its default
        name = "ERROR";   

        int index = Random::getRandomInt(0, 3);
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
                std::cout << "ERROR in armor.h makeName()\n";
        }

             
    }
    int makeHP(){
        /*
       this line correctly spawns a value between 450-500 that is a multiple of 5
       legendaryHealth + SPREAD - (legendaryHealth + SPREAD) % 5;

       legDMG = 450, let SPREAD = 13

       450 + 13 - (450+13) %5
       463 - 463 % 5
       463 - 3

       return 460
       */
        //min strength for each rarity level
        const int legendaryHealth = 450;
        const int epicHealth = 350;
        const int rareHealth = 250;
        const int uncommonHealth = 150;
        const int commonHealth = 50;

        const int SPREAD = Random::getRandomInt(0,50);

    
        switch(rarity.level){
            case Level::LEGENDARY:
                return legendaryHealth + SPREAD - (legendaryHealth + SPREAD) % 5;

            case Level::EPIC:
                return epicHealth + SPREAD - (epicHealth + SPREAD) % 5;

            case Level::RARE:
                return rareHealth + SPREAD - (rareHealth + SPREAD) % 5;

            case Level::UNCOMMON:
                return uncommonHealth + SPREAD - (uncommonHealth + SPREAD) % 5;

            case Level::COMMON:
                return commonHealth + SPREAD - (commonHealth + SPREAD) % 5;

            default:
                std::cout << "ERROR in weapon.h makeName()\n";
        }


        return 0;
    }

public:
    Armor(){
    //Name
        makeName();

    //HP
        HP = makeHP();
    }

    Armor(float myRarityBegin, float myRarityEnd){
        makeRarity(myRarityBegin, myRarityEnd); //makes rarity specific
    //Name
        makeName();

    //HP
        HP = makeHP();
    }
    
    ~Armor()override{
        if(!test)
            std::cout << "Armor destructor!\n";

    }

    virtual void make(int ct) override{
        for (int i = 0; i < ct; i++){

            std::shared_ptr<Armor> ptr = std::make_shared<Armor>();
            armors.push_back(ptr); //add to list
            Item::getList().push_back(ptr);
        }
    }

    std::string getItemType()const override{return "ARMOR";}
    int getHP()const{return HP;}
    static std::vector<std::shared_ptr<Armor>>& getList(){return armors;}


};
std::vector<std::shared_ptr<Armor>> Armor::armors;

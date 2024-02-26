#pragma once
#include <iomanip>
#include <iostream>
#include "enemy.h"
#include "armor.h"
#include "weapon.h"
#include "potion.h"
#include "placedObject.h"


class Chest : public placedObject{

    static std::vector<std::shared_ptr<Chest>> chests;

    std::vector<std::shared_ptr<Item>> loot;

    
    void makeLoot(float raritySpreadBegin, float raritySpreadEnd){
        
       int items = Random::getRandomInt(2,3);
        for(int i = 0; i < items; i++){
            
            int itemType = Random::getRandomInt(1,4);
            int x;
            //I want more potions to be made then armor/weapons
            //1/8 chance for armor, same for weapon
            //6/8 chance for potion
            switch (itemType)
            {
            case 1:
                loot.push_back(std::make_shared<Armor>(raritySpreadBegin, raritySpreadEnd));
                break;
            case 2:
                loot.push_back(std::make_shared<Weapon>(raritySpreadBegin, raritySpreadEnd));
                break;
            case 3:
            case 4:
                loot.push_back(std::make_shared<Potion>(raritySpreadBegin, raritySpreadEnd));
                break;
            default:
                std::cout << "CRIT ERROR IN CHEst.h makeCoord\n";
                break;
            }

        }
    }
public:

    //Constructor for PLACEABLE Chests found in map
    Chest(){

      makeLoot(0.0f, 1.0f); //default values
      makeCoord();
    }

    //Constructor for loot (doesnt need coords bc it will be with an enemy)
    Chest(float begin, float end){ 

      makeLoot(begin, end); //specified values
    }

    ~Chest(){

        for(const auto& item : loot){
            item->overrideDestructor(); //set all items in chest as test objects, so that they dont have destructor msg
        }


    }
    void make(int ct){
        for (int i = 0; i < ct; i++){
            chests.push_back(std::make_shared<Chest>()); //add to list
        }
    }
    

        
    void showContents(){
        const int FW = 40;
        std::cout << std::left;
        std::cout << std::setw(FW+36) << std::setfill('-') << '-' << std::endl; 
        std::cout << std::setfill(' ');
        for(int i = 0; i < loot.size(); i++){
            std::cout << std::left; //set output left

            std::cout << "ITEM " << i+1 << ": "; //items will be from 2-4 or smth like that


            if(loot[i] == nullptr){
                std::cout << "EMPTY\n";
            }
            else{
                //display: NAME    (TYPE) (RARITY)
                std::cout << std::setw(FW) << loot[i]->getName();
                std::cout << '\t';
                std::cout << std::right;
                //8 is size of biggest item type (potion) and (weapon)
                std::cout << std::setw(8) << loot[i]->getItemType() << ' ';

                std::cout << loot[i]->getRarityLevel();
                std::cout << '\n';
            }
            
        }
        std::cout << std::left;
        std::cout << std::setw(FW+36) << std::setfill('-') << '-' << std::endl; 
        std::cout << std::setfill(' ');
        
    }
    
    static std::vector<std::shared_ptr<Chest>>& getList(){return chests;}
    std::vector<std::shared_ptr<Item>>& getLoot(){return loot;}
};
std::vector<std::shared_ptr<Chest>> Chest::chests;

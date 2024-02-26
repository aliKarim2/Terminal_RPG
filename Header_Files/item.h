#pragma once
// #include "game.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "random.h"
enum class Level{
    COMMON,
    UNCOMMON,
    RARE,
    EPIC,
    LEGENDARY

};
struct Rarity{
    std::string title;
    Level level;

};

/*HOW TO PROPERLY DELETE ITEMS
    1. IF Item is being used then set its place to another item (can be null if wanted)
        ex if it was a weapon used by player
        player.setWeapon(otherWeaponName);
    
    2. erase item from its specialized list (weapons, armors, potions)
        ex if it was a weapon
        weaponList.erase(weaponList.begin() + index of item in weaponList)
    3. erase item from item list
            itemList.erase(itemList.begin() + index of item in items list);

    */
    
class Item{
private:
    static std::vector<std::shared_ptr<Item>> items;

    virtual void makeName()=0;
    virtual void make(int ct)=0;
    
protected:
    int personalizedListIndex;
    int itemListIndex;
    //CONSTRUCTOR FUNCTIONS
    void makeRarity(float raritySpreadBegin, float raritySpreadEnd){
        //the spread will be on avg higher for bosses, lower for chests/minions
        float generatedFloat = Random::getRandomFloat(raritySpreadBegin, raritySpreadEnd);
        /*
        1-.9    L
        .9-.7   E
        .7-.4   R
        .4-.2   U
        .2-0    C

        lower values are inclusive; .9 would be L, .899 would be E
        */

        //ASSIGN rarityLevel
        {
            //MIN VALUES TO GET VALUE:
            const float LEG = 0.9f; //(need at least .9 for LEG)
            const float EPC = 0.7f;
            const float RAR = 0.4f;
            const float UNC = 0.2f;

            if(1.0f >= generatedFloat && generatedFloat >= LEG){
                rarity.level = Level::LEGENDARY;
                rarity.title = "LEGENDARY";
            }
            else if(LEG > generatedFloat && generatedFloat >= EPC){
                rarity.level = Level::EPIC;
                rarity.title = "EPIC";
            }
            else if(EPC > generatedFloat && generatedFloat >= RAR){
                rarity.level = Level::RARE;
                rarity.title = "RARE";
            }
            else if(RAR > generatedFloat && generatedFloat >= UNC){
                rarity.level = Level::UNCOMMON;
                rarity.title = "UNCOMMON";
            }
            else if(UNC > generatedFloat && generatedFloat >= 0.0f){
                rarity.level = Level::COMMON;
                rarity.title = "COMMON";
            }  
        }
    }

    std::string name; //will be decided by children
    Rarity rarity;  //decided in constructor

public:
    bool test = false;

    Item(float beginRaritySpread = 0.0f, float endRaritySpread = 1.0f){
        makeRarity(beginRaritySpread, endRaritySpread); //default range


    }
    virtual ~Item(){
        // if(!test)
            // std::cout << "ITEM DESTRUCTOR\n";
        // std::cout << name << " DELETED\n";
    }
    std::string getName()const{return name;}
    std::string getRarityLevel()const{return '(' + rarity.title + ')';}
    static std::vector<std::shared_ptr<Item>>& getList(){return items;}
    virtual std::string getItemType()const=0;
    virtual int getPersonalizedIndex()const{return personalizedListIndex;} //returns index of obj in weapon,armor,potions vector
    virtual int getItemsIndex(){return itemListIndex;}   //returns index of obj in items array


    void overrideDestructor(){
            test = true;
    }

};

std::vector<std::shared_ptr<Item>> Item::items;

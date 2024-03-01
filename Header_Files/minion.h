#pragma once

#include "enemy.h"

class Player;



class Minion : public Enemy{
private:
    //SPAWN VARIABLES
    static std::vector<int> xList;
    static std::vector<int> yList;

    //USED TO GET ENEMY NAMES
    static std::vector<std::string> nameList;
    static std::vector<int> usedNames;
    static bool initialized; //makes sure nameList is only called once
    void fillLists()override{
        if(!initialized){
            std::string sampleName;
            std::ifstream inFile;
            const std::string FILE_NAME = "enemyNameList.txt";
            inFile.open(FILE_NAME);

            if(inFile.is_open()){
                while(std::getline(inFile, sampleName)){//while inFile is getting a sampleName
                    // std::cout << sampleName << " added!\n";
                    nameList.push_back(sampleName);

                }
            }
            else{
                std::cerr << "ERROR OPENING ENEMY NAME FILE";
            }
            // inFile.close();
            // std::cout << "FILLING NAMELIST!\n";
            
        }

    }
    
protected:

    
    static std::vector<std::unique_ptr<Minion>> minions; //holds all minions + bosses

public:
    Minion(){
        
        ID = minions.size();

        // std::cout << "ENTER CONST\n"; 
        const int MIN_STAT = 200;
        const int MAX_STAT = 400;

    //NAME
        fillLists();//fill nameList  
        int index = Random::getRandomInt(0, nameList.size()-1, usedNames);//gets an index between 0 and size of vector
        bool used = false;
        name = nameList[index]; //set name to a randomly selected name
        usedNames.push_back(index);
    //DAMAGE AND HP

        const int STAT_MULTIPLIER = 5;

        damage *= STAT_MULTIPLIER;
        HP     *= STAT_MULTIPLIER;

    //SCORE DROP
        const int MINION_SCORE_MULTIPLIER = 1000;
        //score should be based on strength of enemy (statpts)
        scoreValue *= MINION_SCORE_MULTIPLIER;
       
    //LOOT
        static const float BEGIN = 0.0f;
        static const float END = 1.0f;

        dropLoot = Chest(BEGIN, END);

    }
    
    ~Minion() override {

        // if(!test)
            // std::cout << name << " DIED!!!\n";
        for(const auto& item : dropLoot.getLoot()){
            item->overrideDestructor(); //set all items in chest as test objects, so that they dont have destructor msg
        }
       
    }

    virtual void make(int ct){
        for (int i = 0; i < ct; i++){
            minions.push_back(std::make_unique<Minion>()); //add to list
        }
    }
    
    
    virtual void showInfo(){
        const int FW = 20;
        std::cout << std::left;
        std::cout << name << '\n';
        std::cout << "HP: " << HP << '\n';
        std::cout << "ATK: " << damage;
        std::cout << '\n';
    }
    static void showAllMinions(){
        for(const auto& e : minions){
            std::cout << e->getName() << '\n';
        }
    }
    static std::vector<std::unique_ptr<Minion>>& getList(){return minions;}



};
//initialize static variables
std::vector<std::unique_ptr<Minion>> Minion::minions;
bool Minion::initialized = false;
std::vector<std::string> Minion::nameList;
std::vector<int> Minion::xList;
std::vector<int> Minion::yList;
std::vector<int> Minion::usedNames;

// std::vector<int> Minion::usedMinionNames;
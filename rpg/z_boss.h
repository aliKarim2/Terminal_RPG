#pragma once
#include <vector>
#include <sstream>
#include <string>
#include "z_enemy.h"

class Enemy;

//struct for boss ability
struct Ability{
        std::string name;
        double damageMult;
        std::vector<std::string> effects;
        double chance;
    };



class Boss : public Enemy{
private:
    static std::vector<int> usedNames;
    static std::vector<std::unique_ptr<Boss>> bosses; //list of bosses

    Ability ability;
    

    //USED FOR CONSTRUCTOR
    static std::vector<Ability> abilityList;
    static std::vector<std::string> bossNameList;

    static bool initialized; //makes sure fillList is only called once
    void fillLists()override{
         if(!initialized){
                std::ifstream inFile;
                std::string sampleName;
                const std::string BOSSNAME = "bossNameList.txt";
                const std::string ABILITYNAME = "bossAbilityList.txt";
                inFile.open(BOSSNAME);
                
                if(inFile.is_open()){
                    // std::cout << "FILLED BOSSNAMES!\n";
                    while(std::getline(inFile, sampleName)){//while inFile is getting a sampleName
                        // std::cout << sampleName << " added!\n";
                        bossNameList.push_back(sampleName);

                    }
                }
                else{
                    std::cerr << "ERROR OPENING BOSS NAME FILE";
                }
                inFile.close(); //close bossname file

                inFile.open(ABILITYNAME); //open ability name file
                if(inFile.is_open()){
                    std::string line;
                    while(std::getline(inFile, line)){//while inFile is getting a sampleName


                        Ability myAbility; //to hold sample values

                        std::istringstream iss(line); //to extract data

                        //reading from iss, extracting sampleName, then looking for next thing seperated by a tab
                        std::getline(iss, myAbility.name, '\t');

                        iss >> myAbility.damageMult;
                    
                        //Ability effects are seperated with spaces
                        std::string sampleEffect;

                        while(iss >> sampleEffect){ //while effects are found (while a string is found)
                            if(sampleEffect[0] == 'H' || sampleEffect[0] == 'D' || sampleEffect[0] == 'W'){
                                myAbility.effects.push_back(sampleEffect); //add them to vector
                            }                        
                            else{
                                // sampleEffect = std::stod(sampleEffect);
                                myAbility.chance = std::stod(sampleEffect);
                            }
                        }
                        abilityList.push_back(myAbility);
                    }
                }
                else{
                    std::cerr << "ERROR OPENING ABILITY NAME FILE";
                    
                }
                inFile.close();


                // std::cout << "FILLING bossNameList!\n";
                
            }
    }

public:

    Boss(){
        ID = bosses.size();

        //Numbers that determine the overall of a boss
        const int MIN_STAT = 700;
        const int MAX_STAT = 1000;
        
    //NAME
        fillLists();//fill bossNameList  
        //name becomes a random name in bossNameList
        int index = Random::getRandomInt(0, bossNameList.size(), usedNames);//gets an index between 0 and size of vector
        name = bossNameList[index]; //set name to a randomly selected name
        usedNames.push_back(index);
    //DAMAGE AND HP
        //A number to represent the overall of a boss
        int statpts = Random::getRandomInt(MIN_STAT,MAX_STAT);//stat points will be equal to boss hp + damage for balancing purposes

        damage = Random::getRandomInt(statpts/5, 4*statpts/5); //damage can be 1/5 statpts to 4/5 statpts (so HP is 1/5 to 4/5)
        HP = statpts - damage; //HP will be based off of precalculated damage

    //SCORE DROP
        const int BOSS_SCORE_MULTIPLIER = 10; //bosses will generally have x10 higher score than normal enemies

        //score should be based on strength of boss (statpts)
        scoreValue = statpts * BOSS_SCORE_MULTIPLIER;

    //SPAWN POINT
        //occurs in enemy constructor
        

    //ABILITY 
        //Ability list is already filled 
        index = Random::getRandomInt(0, abilityList.size());//gets an index between 0 and size of vector
        ability = abilityList[index];
       
        // bosses.push_back(std::make_unique<Boss>(*this));//add boss to boss list

    //LOOT
        static const float BEGIN = 0.5f;
        static const float END = 1.0f;

        dropLoot = Chest(BEGIN, END);

    }
    virtual ~Boss() = default;

    void make(int ct) override{
        for (int i = 0; i < ct; i++){
            bosses.push_back(std::make_unique<Boss>()); //add to list
        }
    }

    

    //getters and setters
    std::string getAbilityName(){return ability.name;}
    double getAbilityDamageMult(){return ability.damageMult;}
    double getAbilityChance(){return ability.chance;}
    
    void listAbilityEffects(){
        if(!ability.effects.empty()){
            for(std::string s : ability.effects){
            std::cout << s << '\t';
            }       
        }
        else    
            std::cout << "NO EFFECTS!\n";
    }

    // char symbol() override{
    //     const char SYMBOL = 'B';
    //     return SYMBOL;
    // }

    virtual void addToList(){
        // std::cout << "ADD TO BOSSES\n";
        bosses.push_back(std::make_unique<Boss>(*this));  
    }
    



    void showInfo() override{
        const int FW = 20;
        std::cout << std::left;
        std::cout << name << '\n';
        std::cout << "HP: " << HP << '\n';
        std::cout << "ATK: " << damage;
        std::cout << "ULT: " << ability.damageMult * damage;
        std::cout << '\n';
    }
    
    static std::vector<std::unique_ptr<Boss>>& getList(){return bosses;}

};
std::vector<std::unique_ptr<Boss>> Boss::bosses;
bool Boss::initialized = false;
std::vector<std::string> Boss::bossNameList;
std::vector<Ability> Boss::abilityList;
std::vector<int> Boss::usedNames;


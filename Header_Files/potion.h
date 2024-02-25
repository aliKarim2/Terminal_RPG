#pragma once
#include <iostream>
#include <string>
#include "Header_Files\item.h"
#include "Header_Files\random.h"

class Potion : public Item {

    static std::vector<std::shared_ptr<Potion>> potions;

    char type; //Heal, Strength, Weakness
    int potency; //1-100, a percent  
    bool energized; //has ability to skip enemy turn
    std::string description;


    //Constructor Functions
    std::string makeName() override{
        std::string myName = "NAMEERROR"; //set name to error 
        /*NAME FORMULA
        //Energized(y/n) + adjective + potion + effect (healing/dmg/weakness)
        //Ultimate potion of vitality
        //Basic splash potion of weakening
        //Strong potion of enragement
        */
        
        std::string legendaryNames [4] = { "Ultimate", "Mystical", "Supreme", "Arcane"};
        std::string epicNames [4] = { "Formidable", "Enchanted", "Grand", "Glorious" };
        std::string rareNames [4] = { "Powerful", "Strong", "Potent", "High" };
        std::string uncommonNames [4] = { "Standard", "Simple", "Normal", "Basic" };
        std::string commonNames [4] = { "Dull", "Mundane", "Rudementary", "Ordinary" };


    
        //parts of potion name
        std::string adj = "";
        std::string pot = "";
        std::string fx = "";

        //Get Adjectives
        {
            int index = Random::getRandomInt(0, 3);
            // std::cout << "INDEX: " << index << '\n';
            if(rarity.level == Level::LEGENDARY){
                // std::cout << "IN LEG";
                // std::cout << '\n';
                
                adj = legendaryNames[index];
            }   
            else if(rarity.level == Level::EPIC){
                adj = epicNames[index];
                // std::cout << "IN EPC";
                // std::cout << '\n';
                

            }     
            else if(rarity.level == Level::RARE){
                adj = rareNames[index];
                // std::cout << "IN RAR";
                // std::cout << '\n';
                
            }     
            else if(rarity.level == Level::UNCOMMON){
                adj = uncommonNames[index];
                // std::cout << "IN UNC";
                // std::cout << '\n';
                
                
            }     
            else if(rarity.level == Level::COMMON){
                adj = commonNames[index];
                // std::cout << "IN COM";
                // std::cout << '\n'; 
            }     
        }

        //determine fx string based on potion type
        switch(type){
            case 'H':
                fx = "Of Vitality";

                break;
            case 'S':
                fx = "Of Vigor";
                break;
            case 'W':
                fx = "Of Weakening";
                pot += "Splash ";
                break;
            default:
                std::cerr << "CRIT ERROR IN MAKENAME() POTION.H\n";
        }
        pot += "Potion";


        // {
        //     std::cout << "RARITY";
        //     std::cout << rarity.title;
        //     std::cout << '\n';
        //     std::cout << "ADJ: ";
        //     std::cout << adj;
        //     std::cout << '\n';
        //     std::cout << "POT: ";
        //     std::cout << pot;
        //     std::cout << '\n';
        //     std::cout << "FX: ";
        //     std::cout << fx;
        //     std::cout << '\n';
        // }
        
        
        //add energized if needed
        myName = energized ? "Energized " : "";

        //construct name
        myName += adj + ' ' + pot + ' ' + fx;

        return myName;
    }
    std::string makeDescription(){
        std::string verb;
        std::string amount;
        switch (type){
            case 'H':
                verb = "Heals player for";

                break;
            case 'S':
                verb = "Strengthens player damage by";

                break;
            case 'W':
                verb = "Weakens enemy damage by";

                break;
            default:
                std::cout << "\n\n\nERROR IN POTION.H, EFFECT NOT HAVE VALID CHAR\n\n\n";
                break;
        }

        std::string myDescription = verb + ' ' + std::to_string(potency);

        // if(type == 'H')
        //     myDescription += " HP.";
        // else
            myDescription += "%.";


        return myDescription;
    }
    char makeType(){
        // char can be:
        // H: heals player
        // S: increase player damageMult
        // W: weakens enemy strength
        int x = Random::getRandomInt(1,3);
        char myType;
        switch (x)
        {
        case 1:
            myType = 'H';
            break;
        case 2:
            myType = 'S';
            break;
        case 3:
            myType = 'W';
            break;
        default:
            std::cout << "ERROR in potion.h makeName effect\n";
            break;
        }
        return myType;
    }
    int makePotency(){
         /*
        Potency is from 0000-9999 X
                        0-80,
        Legendary potion of weakness should at most remove 80%? of strength?
        If potency was 8000,
        it could heal 80% of HP
        add 80% of attack dmg  500 -> 900
        remove 80% of dmg

        Common potions should at least: (25%?)
        heal 25% HP 
        add 25% dmg 500 -> 625
        remove 25% dmg

        L:  80%
        E:  65%
        R:  50%
        U:  35%
        C:  25%

        ====

        500 -> 900
        500 -> 825
        500 -> 750
        500 -> 675
        500 -> 625

        */

        switch(rarity.level){
            case(Level::LEGENDARY):
                return 80;

            case(Level::EPIC):
                return 65;

            case(Level::RARE):
                return 50;     

            case(Level::UNCOMMON):
                return 35;  

            case(Level::COMMON):
                return 25;  

            default:
                std::cerr << "UNKNOWN RARITY in potion.h constructor\n";
        }

        //if no valid level return invalid thing
        std::cerr << "INVALIDITY IN potion.h makePotency!";
        return -1;
    }

public:
    Potion(){
    //POTION TYPE 
        type = makeType();

    //POTENCY
       potency = makePotency();

    //ENERGIZED
        //each potion has equal chance to be energized
        const int ODDS = 3;
        energized = (Random::getRandomInt(1,ODDS) == 1) ? true : false; // 1/ODDS (1/3) chance to get energized here

    //DESCRIPTION
        description = makeDescription();

    //NAME
        name = makeName();
    }
    Potion(float myRarityBegin, float myRarityEnd){
        makeRarity(myRarityBegin, myRarityEnd); //makes rarity specific
    //POTION TYPE 
        type = makeType();

    //POTENCY
       potency = makePotency();

    //ENERGIZED
        //each potion has equal chance to be energized
        const int ODDS = 3;
        energized = (Random::getRandomInt(1,ODDS) == 1) ? true : false; // 1/ODDS (1/3) chance to get energized here

    //DESCRIPTION
        description = makeDescription();

    //NAME
        name = makeName();
    }
    ~Potion()override{
        std::cout << "Potion destructor!\n";

    }
    
    virtual void make(int ct) override{
        for (int i = 0; i < ct; i++){
            std::shared_ptr<Potion> ptr = std::make_shared<Potion>();

            personalizedListIndex = Item::getList().size();
            itemListIndex = potions.size();

            potions.push_back(ptr); //add to list
            Item::getList().push_back(ptr);
        }
    }
    
    
    //GETTERS
    std::string getItemType()const override{return "POTION";}
    char getType()const{return type;}
    int getPotency()const{return potency;}
    bool getEnergized()const{return energized;}
    std::string getDescription()const{return description;}
    static std::vector<std::shared_ptr<Potion>>& getList(){return potions;}

};
std::vector<std::shared_ptr<Potion>> Potion::potions;

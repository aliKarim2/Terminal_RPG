#include <iostream>
#include <vector>

//Header Files
#include "z_player.h" //includes everything else 
// #include "z_minion.h"
#include "z_boss.h" //includes enemy
#include "z_minion.h" //includes enemy
// #include "z_item.h"
// #include "z_potion.h"
// #include "z_weapon.h"
// #include "z_armor.h"
#include "z_chest.h"

int main(){

//shorthand variable names (same values)
    std::vector<std::unique_ptr<Minion>>& minionList = Minion::getList();
    std::vector<std::unique_ptr<Boss>>& bossList = Boss::getList();
    

    std::vector<std::shared_ptr<Item>>& itemList = Item::getList();
    std::vector<std::shared_ptr<Potion>>& potionList = Potion::getList();
    std::vector<std::shared_ptr<Weapon>>& weaponList = Weapon::getList();
    std::vector<std::shared_ptr<Armor>>& armorList = Armor::getList();

    std::vector<std::shared_ptr<Chest>>& chestList = Chest::getList(); //all PLACABLE chests


    //instantiate objects
    {       
        const int MINION_SPAWN = 10; 
        const int BOSS_SPAWN = 5;
        const int ARMOR_SPAWN = 10;
        const int WEAPON_SPAWN = 10;
        const int POTION_SPAWN = 10;
        const int CHEST_SPAWN = 10;

        Minion minionTest;
        Boss bossTest;
        
        Armor armorTest;
        Weapon weaponTest;
        Potion potionTest;
        
        Chest chestTest;

        //make them test obj so destructor is not called
        minionTest.test = true;
        bossTest.test = true;
        armorTest.test = true;
        weaponTest.test = true;
        potionTest.test = true;
        
        // std::cout << "C1\n";
        minionTest.make(MINION_SPAWN);
        bossTest.make(BOSS_SPAWN);

        weaponTest.make(WEAPON_SPAWN);
        armorTest.make(ARMOR_SPAWN);
        potionTest.make(POTION_SPAWN);

        chestTest.make(CHEST_SPAWN);
        // std::cout << "C4\n";


    }

    Player player("REDF");
    Chest chest;

    bool validInput;
    int choice;
    std::cout << "You Found a Chest!\n";
    std::cout << "CONTENTS: \n";


    do{
        chest.showContents();

        std::cout << "Select an item or -1 to leave:\n";
        //INPUT VALIDATION
        do{
            if (!(std::cin >> choice)) { //if input not int
                std::cin.clear();  // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
                std::cout << "Invalid input. Please enter a number." << std::endl;
            } else {
                if(choice >= 1 && choice <= chest.getLoot().size()){ //if input is valid number (is an item #)
                    break;  // Exit the loop if input is valid
                } 
                else if(choice == -1){
                    return 0; //exit function
                }
                else {
                    std::cout << "Enter a number between (1 - " << chest.getLoot().size() << ") or -1 to leave.\n";
                }    
            }
        }while(true);        

        choice -= 1;
        //Now, input should be a valid int
        std::cout << "You picked: " << chest.getLoot()[choice]->getName() << '\n';
        std::cin.get();  

        //Determine item type and act accoordingly
        {
            if (std::shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(chest.getLoot()[choice])) {
                std::cout << "You picked a weapon.\n";
                std::cout << "Adding it...\n";
                player.setWeapon(weapon);
                std::cout << "Added it\n";
                

            } else if (std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(chest.getLoot()[choice])) {
                std::cout << "You picked a potion.";
                std::cout << "Adding it...\n";
                if(!player.addPotion(potion)){
                    std::cout << "You have the max amount of potions!\n";
                }
                else
                    std::cout << "Added it\n";

            } else if (std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(chest.getLoot()[choice])) {
                std::cout << "You picked an armor.";
                std::cout << "Adding it...\n";
                player.setArmor(armor);
                std::cout << "Added it\n";
                
            
            }
        }

        

        
        // std::cout << "Current Weapon: ";
        // if(player.getWeapon() != nullptr) {
        //     std::cout << player.getWeapon()->getName() << '\n';                      
        // }              
        // else{
        //     std::cout << "NULLPTR\n";
        // }    
        // std::cin.get();                    
        // std::cout << "Current Armor: ";    
        // if(player.getArmor() != nullptr) {
        //     std::cout << player.getArmor()->getName() << '\n';                      
        // }              
        // else{
        //     std::cout << "NULLPTR\n";
        // }   
        // std::cin.get();                    
        // std::cout << "Current Potions: \n";                      
        // for(const auto& potion : player.getPotions()){
        //     if(potion != nullptr){
        //         std::cout << '-' << potion->getName();
        //         std::cout << '\n';
        //     }
        //     else{
        //         std::cout << "-NULLPTR\n";
        //     }
        // }        

        std::cin.get();                    

    }while(choice != -1); //while player has chest open


    std::cout << "Program Terminated";

  return 0;
}

#include <iostream>
#include <vector>

//Header Files
#include "Header_Files/player.h" //includes everything else 
// #include "Header_Files/minion.h"
#include "Header_Files/boss.h" //includes enemy
#include "Header_Files/minion.h" //includes enemy
// #include "Header_Files/item.h"
// #include "Header_Files/potion.h"
// #include "Header_Files/weapon.h"
// #include "Header_Files/armor.h"
#include "Header_Files/chest.h"

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

        // Minion minionTest;
        // Boss bossTest;
        
        Armor armorTest;
        Weapon weaponTest;
        Potion potionTest;
        Chest chestTest;

        //make them test obj so destructor is not called
        // minionTest.test = true;
        // bossTest.test = true;
        armorTest.test = true;
        weaponTest.test = true;
        potionTest.test = true;
        chestTest.test = true;
        
        // std::cout << "C1\n";
        // minionTest.make(MINION_SPAWN);
        // bossTest.make(BOSS_SPAWN);

        // weaponTest.make(WEAPON_SPAWN);
        // armorTest.make(ARMOR_SPAWN);
        // potionTest.make(POTION_SPAWN);

        // chestTest.make(CHEST_SPAWN);
        // std::cout << "C4\n";


    }

    // Player player("REDF");
    // Chest chest;

    
    // Armor a1;

    // std::cout <<  a1.getRarityLevel();

    // std::cout << '\n';

    // Armor a2(0.9f, 1.0f);                 //generates only legendary 
    // std::cout << '\n';
    // std::cout <<  a2.getRarityLevel();
    


    std::cin.get();
    std::cout << "Program Terminated";

  return 0;
}

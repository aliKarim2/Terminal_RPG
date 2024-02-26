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


  std::cin.get();
  //instantiate objects
  {       
    const int ARMOR_SPAWN = 1;
    const int WEAPON_SPAWN = 1;
    const int POTION_SPAWN = 1;
    const int CHEST_SPAWN = 1;

  std::cout << "C0.1\n";
    
    Minion minionTest;
    std::cout <<  minionTest.getDrops().getLoot().size() << '\n';
    // Boss bossTest;

    minionTest.getDrops().showContents();

    std::cin.get();

    std::cout << "C0.15`\n";    


    Armor armorTest;
    Weapon weaponTest;
    Potion potionTest;
    Chest chestTest;

  std::cout << "C0.2\n";

    //make them test obj so destructor is not called
    minionTest.test = true;
    // bossTest.test = true;
    armorTest.test = true;
    weaponTest.test = true;
    
    potionTest.test = true;
    
    std::cout << "C1\n";
   

    // minionTest.make(5);
    // bossTest.make(5);

    weaponTest.make(WEAPON_SPAWN);
    armorTest.make(ARMOR_SPAWN);
    potionTest.make(POTION_SPAWN);

    chestTest.make(CHEST_SPAWN);
    
    std::cout << "C4\n";

    std::cout << "\nArmors size: ";
    std::cout << armorList.size();
    std::cout << "\nWeapons size: ";    
    std::cout << weaponList.size();
    std::cout << "\nPotions size: ";    
    std::cout << potionList.size();
    std::cout << "\nItems size: ";
    std::cout << itemList.size();
    std::cout << "\nChests size: ";
    std::cout << chestList.size();

  
    }
    std::cout << "\nALL MAKE\n";

    // Player player("REDF");
    // Chest chest;

    
    // Armor a1;

    // std::cout <<  a1.getRarityLevel();

    // std::cout << '\n';

    // Armor a2(0.9f, 1.0f);                 //generates only legendary 
    // std::cout << '\n';
    // std::cout <<  a2.getRarityLevel();
    


    std::cin.get();
    std::cout << "\nProgram Terminated-------------------------\n";

  return 0;
}

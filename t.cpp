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
int openChest(Player& player, Chest& chest);

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
    const int ARMOR_SPAWN = 1;
    const int WEAPON_SPAWN = 1;
    const int POTION_SPAWN = 1;
    const int CHEST_SPAWN = 6;
    const int BOSS_SPAWN = 1;
    const int MINION_SPAWN = 1;

  // std::cout << "C0.1\n";
    
    Minion minionTest;
    Boss bossTest;

    // std::cout << "C0.15`\n";    


    Armor armorTest;
    Weapon weaponTest;
    Potion potionTest;
    Chest chestTest;

  // std::cout << "C0.2\n";

    //make them test obj so destructor is not called
    minionTest.test = true;
    bossTest.test = true;
    armorTest.test = true;
    weaponTest.test = true;
    
    potionTest.test = true;
    
    // std::cout << "C1\n";
   

    // minionTest.make(5);
    // bossTest.make(5);


    minionTest.make(MINION_SPAWN);
    bossTest.make(BOSS_SPAWN);

    weaponTest.make(WEAPON_SPAWN);
    armorTest.make(ARMOR_SPAWN);
    potionTest.make(POTION_SPAWN);

    chestTest.make(CHEST_SPAWN);
    
    // std::cout << "C4\n";

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
    std::cout << "\nALL MAKE\n\n\n";

    Player player("REDF");


    player.viewInventory();




    std::cin.get();

    Chest chest1;

    openChest(player, chest1);

    // openChest(player, *chestList[0]);
    // openChest(player, *chestList[1]);
    // openChest(player, *chestList[2]);
    // openChest(player, *chestList[3]);
    // openChest(player, *chestList[4]);

    std::cout << "CLOSED CHEST NOW\n";

    player.viewInventory();

    std::cin.ignore();
    std::cin.get();



    openChest(player, *chestList[5]);

    std::cout << "CLOSED CHEST NOW\n";

    player.viewInventory();
    


    std::cin.get();
    std::cout << "\nProgram Terminated-------------------------\n";

  return 0;
}



int openChest(Player& player, Chest& chest){
  int choice;
  std::cout << "You Found a Chest!\n";
  std::cout << "CONTENTS: \n";


  do{
    chest.showContents(); //show chest inventory

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

    if(chest.getLoot()[choice] == nullptr){
      std::cout << "You picked an empty slot! Pick a slot with an item in it!\n";
      continue;
    }

    std::cout << "You picked: " << chest.getLoot()[choice]->getName() << '\n';

    //Determine item type and act accoordingly
    {
      if (std::shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(chest.getLoot()[choice])) {

          /*Swap the chest item and player item
          we have to use chest.getLoot() 
          when swapping to get the reference 
          (address) of the item for a permanent swap
          */
          std::shared_ptr<Weapon> temp = weapon;
          chest.getLoot()[choice] = player.getWeapon(); 
          player.setWeapon(temp);

        
          std::cout << "Weapon successfully added to your inventory!\n";
          
      } else if (std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(chest.getLoot()[choice])) {

          if(!player.addPotion(potion)){ //returns false if potion list is full
            std::cout << "You have the max amount of potions!\n";
          }
          else{
            std::cout << "Successfully added it to your inventory!\n";
            chest.getLoot()[choice] = nullptr;//replace loot with null ptr
          }
            
      } else if (std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(chest.getLoot()[choice])) {

          std::shared_ptr<Armor> temp = armor;
          chest.getLoot()[choice] = player.getArmor();
          player.setArmor(temp);          

          player.setArmor(armor);//replace player item with selected loot
          std::cout << "Successfully added it to your inventory!\n";

          // chest.getLoot()[choice] = nullptr;//replace loot with null ptr
      }
    }             

  }while(choice != -1); //while player has chest open


  return 0;
}

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


int newGame(Player& player);
void instructions();
bool fight(Player& player, Enemy& minion); //when a fight occurs; return false if player loses
int openChest(Player& player, Chest& chest);


int main(){

    std::string playerName = "tester1";
    int menuOp;
    bool valid;

    // std::cout << "Welcome to Game!\n";
    // std::cout << "Enter your name ";
    // std::cin >> playerName;

    Player p1(playerName);

    // std::cout << "Hello " << playerName;

    // return 0;
    newGame(p1); //enter a new game

   
    std::cout << "\n\n\nProgram Terminated\n\n\n";
  return 0;
}


int newGame(Player& player){
    bool running = true;

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
    
    std::cout << "LOCATIONS\n";
    std::cout << "CHEST: ";
    std::cout << chestList[0]->getCoord() << '\n';
    std::cout << "MINION: ";
    std::cout << minionList[0]->getCoord() << '\n';
    std::cout << "BOSS: ";
    std::cout << bossList[0]->getCoord() << '\n';


    // std::cout << "BOSSES LOOT\n";
    // for(const auto& boss : bossList){
    //     boss->getLoot().showContents();
    //     std::cout << '\n';
    //     std::cin.get();
    // }


    std::cin.get();
    // return 0;

    // std::cout << minionList[0]->getCoord() << '\n'; //WORKSSSSS



    // player.Update();



    std::cout << "\n\n\n";


 

//while game is running
bool event = false; //checks if an event (encounter player vs object) occurs
while(running){
    player.move();
    if(player.getCoord() == Coord{-1,-1}){
        break; //EXIT CASE
    }

    /*CODE CHECKS IF ENCOUNTERS OCCUR
    for all enemies in array:
    - check if their positon matches with player's
    - if so, fight!
    - if a fight happened, break out of loop; impossible for more than one minion to be on same square
    */
    for(const auto& minion : minionList){

        if(player.getCoord() == minion->getCoord()){ //if player is on same square as minion
            if(!fight(player, *minion)){ //if they fight and player loses
                std::cout << "You lose!\n";
                running = false; //end game
                break;
            }
            else{//if player won
                player.changeScore(minion->getScore());//add minion drop score to player

                std::cout << "YOU WON!\n";

                //deletes defeated minion
                minionList.erase(minionList.begin() + minion->getID());

            
            }
        
        }
    }
    //same for bosses
    for(const auto& b : bossList){
        if(player.getCoord() == b->getCoord()){ //if player is on same square as minion
            if(!fight(player, *b)){ //if they fight and player loses
                std::cout << "You lose!\n";
                running = false;
                break;
            }
            else{//if player won
                player.changeScore(b->getScore());//add minion drop score to player

                std::cout << "YOU WON!\n";
                //delete erased boss
                bossList.erase(bossList.begin() + b->getID());

                


                // minion::showAllEnemies();
            }
        
        }
    }
    for(const auto& chest : chestList){
        if(player.getCoord() == chest->getCoord()){
            std::cout << "OPEN CHEST!!!\n\n";

            // chest->showContents();
            openChest(player, *chest);
            // chestList.erase(chestList.begin/);
            //make it so that player can take all of the contents from chest if he wants

            std::cin.get();
        }
    }    
}
    
  
    


    return 0;
}
void instructions(){
    std::cout << "HOW2PLAY\n";

}
bool fight(Player& player, Enemy& minion){

    const int ATK = 1;
    const int ITEM = 2;
    const int RUN = 3;
    bool fighting = true;
    std::cout << "minion APPROACHING!\n";

    const bool WIN = true;
    const bool LOSE = false;
    bool outcome;


while(fighting){ //while fight happening

   

    player.Update();
    minion.showInfo();
    

    //player turn
    switch(player.atkChoice()){
        //set minion's hp to his current hp minus player's ATK
        case ATK: minion.setHP(minion.getHP() - player.getTotalDamage());
            break;
        case ITEM: std::cout << "open inventory (NI)\n";
            break;
        case RUN: std::cout << "Fight ends and loses score? (NI)\n";
            break;
        default: std::cout << "Crit error!\n";
    }

    if(minion.getHP() <= 0){ //if minion dead
        // std::cout << "Player Wins!\n";

        // player.changeScore(minion.getScore());//add minion drop score to player (do this in newGame())

        outcome = WIN; //outcome to win
        break;
    }

    //minion turn
    //Set player HP to his current hp minus minion ATK
    player.setHP(player.getHP() - minion.getTotalDamage());

    if(player.getHP() <= 0){ //if minion dead
        // std::cout << "minion Wins!\n";
        outcome = LOSE;
        break;
    }
    
}   

    std::cout << "THE FIGHT IS OVER!\n";

    player.Update();
    minion.showInfo();

    return outcome;
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


    return 0;
}

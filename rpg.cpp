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
        const int BOSS_SPAWN = 10;
        // const int ARMOR_SPAWN = 10;
        // const int WEAPON_SPAWN = 10;
        // const int POTION_SPAWN = 10;
        const int CHEST_SPAWN = 2;

        Minion minionTest;
        Boss bossTest;
        
        Armor armorTest;
        Weapon weaponTest;
        Potion potionTest;
        
        Chest chestTest;

        //make them test obj so destructor is not called
        minionTest.test = true;
        bossTest.test = true;
        // armorTest.test = true;
        // weaponTest.test = true;
        // potionTest.test = true;
        
        // std::cout << "C1\n";
        minionTest.make(MINION_SPAWN);
        bossTest.make(BOSS_SPAWN);

        // weaponTest.make(WEAPON_SPAWN);
        // armorTest.make(ARMOR_SPAWN);
        // potionTest.make(POTION_SPAWN);

        chestTest.make(CHEST_SPAWN);
        // std::cout << "C4\n";


    }
    
    std::cout << "LOCATIONS\n";
    // std::cout << "CHEST: ";
    // std::cout << chestList[0]->getCoord() << '\n';
    std::cout << "MINION: ";
    std::cout << minionList[0]->getCoord() << '\n';
    std::cout << "Boss: ";
    std::cout << bossList[0]->getCoord() << '\n';


    // openChest(player, *chestList[0]);
    // openChest(player, *chestList[1]);

    // std::cin.get();

    // player.useItem();

    // std::cin.get();
  

    std::cout << "\n\n\n";


 

//while game is running
bool event = false; //checks if an event (encounter player vs object) occurs
while(running){
    player.move();
    if(player.getCoord() == Coord{-1,-1}){
        break; //EXIT CASE
    }

    /*CODE CHECKS IF ENCOUNTERS OCCUR
    for all minions and bosses in a list:
    - check if their positon matches with player's
    - if so, fight!
    - if a fight happened, break out of loop; impossible for more than one minion to be on same square

    for all chests in a list
    - check if position match with player
    - run openChest()
    - delete chest and the items in it
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
                auto it = std::remove_if(minionList.begin(), minionList.end(), [](const auto& m){
                    return m->getHP() == 0;
                });
                minionList.erase(it, minionList.end());

                //Let player loot the minion's loot after death
                openChest(player, minion->getDrops());


                //state enemies remaining
                std::cout << "Enemies remaining: " << minionList.size() << '\n';
                

                //Give next coord
                if(minionList.size() >= 1){
                    std::cout << minionList[0]->getCoord() << '\n';
                }

                break;
            }
        
        }
    }

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

            chestList.erase(chestList.begin() + chest->getID());
            //make it so that player can take all of the contents from chest if he wants


            // std::cin.get();
        }
    }    
}
 
    return 0;
}
void instructions(){
    std::cout << "HOW2PLAY\n";

}
bool fight(Player& player, Enemy& enemy){

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
    enemy.showInfo();
    

    //player turn
    switch(player.atkChoice()){
        //set enemy's hp to his current hp minus player's ATK
        case ATK: 
            enemy.setHP(enemy.getHP() - player.getTotalDamage());
            break;
        case ITEM:
        
            {
                const char HEAL = 'H';
                const char STRENGTH = 'S';
                const char WEAKNESS = 'W';

                int potionSlot = player.useItem();

                if(potionSlot == -1){ //if it returns an error bc no potions availa//////////////////////////////////////

                    std::cout << "you had no potions...\n";
                    std::cout << "FIX LATER!\n";
                    return 0;
                }

                std::shared_ptr<Potion> chosenPot = player.getPotions()[potionSlot];
                
                //if potion is energized
                if(chosenPot->getEnergized()){
                    //skip enemy turn
                }


                switch (chosenPot->getPotionType()){
                    case HEAL:


                        //set player's hp to its own hp plus the heal affect
                        //heal affect is equal to the potions potency (a number) as a percent (/100) times the hp of the player
                        player.setHP(player.getHP() + (player.getMaxHP() * (chosenPot->getPotency()/100)));
                        break;

                    case STRENGTH:
                        //set player's damage mult to pot effect 
                        //getPotency returns a number, /100 to get the percent
                        player.setDamageMult(player.getDamageMult() + chosenPot->getPotency()/100);
                        break;
                    case WEAKNESS:
                        //set ENEMY's damage mult to pot effect (should be < 1)

                        enemy.setDamageMult(enemy.getDamageMult() - chosenPot->getPotency()/100);

                        break;
                    default:
                        std::cerr << "ERROR IN FIGHT SWITCH rgp.cpp\n";
                        break;
                }

            } 
            



            break;
        case RUN: std::cout << "Fight ends and loses score? (NI)\n";
                    player.useItem();

            break;
        default: std::cout << "Crit error!\n";
    }

    if(enemy.getHP() <= 0){ //if minion dead
        // std::cout << "Player Wins!\n";

        // player.changeScore(minion.getScore());//add minion drop score to player (do this in newGame())

        outcome = WIN; //outcome to win
        break;
    }

    //minion turn
    //Set player HP to his current hp minus minion ATK
    player.setHP(player.getHP() - enemy.getTotalDamage());

    if(player.getHP() <= 0){ //if minion dead
        // std::cout << "minion Wins!\n";
        outcome = LOSE;
        break;
    }
    
}   

    std::cout << "THE FIGHT IS OVER!\n";

    player.Update();
    enemy.showInfo();

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
#include <iostream>
#include <vector>
#include <memory>

class Item {
public:
static std::vector<std::shared_ptr<Item>> items;

    Item(){}
    ~Item(){
        std::cout << "ITEM DESTRUCTOR CALL!\n";
    }
};

class Potion : public Item {
public:
    static std::vector<std::shared_ptr<Potion>> potions;

    Potion(){}
    ~Potion(){
        std::cout << "Potion DESTRUCTOR CALL!\n";
    }

};

class Weapon : public Item {
public:
    static std::vector<std::shared_ptr<Weapon>> weapons;
    Weapon(){}
    ~Weapon(){
        std::cout << "Weapon DESTRUCTOR CALL!\n";
    }
    static void make(int ct){
        for(int i = 0; i < ct; i++){
            std::shared_ptr<Weapon> w1 = std::make_shared<Weapon>(); //reference 1
            items.push_back(w1); //ref 2
            weapons.push_back(w1); // ref 3
        }
        
    }

};
std::vector<std::shared_ptr<Item>> Item::items;
std::vector<std::shared_ptr<Potion>> Potion::potions;
std::vector<std::shared_ptr<Weapon>> Weapon::weapons;


int main() {
    

    // makeWeapon(1);
    Weapon::make(10);
    std::cout << "CT: " << Item::items[0].use_count() << '\n';


    // Accessing items in the vectors
    std::cout << "Potion count: " << Potion::potions.size() << std::endl;
    std::cout << "Weapon count: " << Weapon::weapons.size() << std::endl;
    std::cout << "Total items count: " << Item::items.size() << std::endl;
    std::cout << '\n';
    std::cin.get();

    std::cout << "ERASED FROM ITEMS\n";
    Item::items.erase(Item::items.begin()); //ref-1
    std::cout << '\n';
    

    // Accessing items in the vectors
    std::cout << "Potion count: " << Potion::potions.size() << std::endl;
    std::cout << "Weapon count: " << Weapon::weapons.size() << std::endl;
    std::cout << "Total items count: " << Item::items.size() << std::endl;

    std::cin.get();
    std::cout << "ERASED FROM WEAPONS\n";
    Weapon::weapons.erase(Weapon::weapons.begin()); //ref-1

    std::cout << '\n';
    
// Accessing items in the vectors
    std::cout << "Potion count: " << Potion::potions.size() << std::endl;
    std::cout << "Weapon count: " << Weapon::weapons.size() << std::endl;
    std::cout << "Total items count: " << Item::items.size() << std::endl;
    std::cin.get();
std::cout << '\n';


    std::cout << "program terminated\n";
    std::cin.get();
    return 0;
}
// void makeWeapon(int x)
//     for(int i = 0; i < x; i++){
//         std::shared_ptr<Weapon> w1 = std::make_shared<Weapon>(); //reference 1
//         items.push_back(w1); //ref 2
//         weapons.push_back(w1); // ref 3
//         std::cout << "CT: " << items[0].use_count() << '\n';

//     }
//     std::cout << "CT: " << items[0].use_count() << '\n';

// }
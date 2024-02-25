#pragma once
#include <iostream>
#include <vector>
#include "Header_Files\random.h"

struct Coord{
    int x;
    int y;

};
bool operator==(const Coord p1, const Coord p2){
    return (p1.x == p2.x && p1.y == p2.y);
}
std::ostream& operator<<(std::ostream& stream, const Coord& other){
    return stream << '(' << other.x << ' ' << other.y << ')';
}

class placedObject{
    
protected:
    Coord coord;
    void makeCoord(){
            bool overlapping = false;
            Coord newCoord;

            const int MAP_BORDER = 5;
            do{
                overlapping = false;
                newCoord.x = Random::getRandomInt(-MAP_BORDER, MAP_BORDER); // Random x coordinate between -5 and 5
                newCoord.y = Random::getRandomInt(-MAP_BORDER, MAP_BORDER); // Random y coordinate between -5 and 5

                if(newCoord.x == 0 && newCoord.y == 0){ //player spawns at 0,0 so enemies cant spawn there
                    overlapping = true;
                }
                else{
                    for (const auto& Coord : usedCoords) {

                        if (newCoord == Coord) {
                            // std::cout << "overlap\n";
                            overlapping = true;
                            break; // Overlapping
                        }
                    }   
                }
                
            } while (overlapping);

            usedCoords.push_back(newCoord);

            coord = newCoord;
        }

    static std::vector<Coord> usedCoords;

    
public:
    placedObject(){
        // makeCoord();
    }

    Coord getCoord(){return coord;}
    
};
std::vector<Coord> placedObject::usedCoords;

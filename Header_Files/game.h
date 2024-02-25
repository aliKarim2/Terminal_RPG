#pragma once
#include <iostream>


class Game{
    int x;
    virtual void make(int ct)=0;
    

public:
    Game(){
        
    } 
    int getX(){return x;}      

};
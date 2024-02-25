#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
class Random{
       
    public:
        static int getRandomInt(int start, int end){
            // Set up a random number generator
            static std::random_device rd;  // Use hardware entropy if available

            std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

            // Define a distribution (for example, integers between 1 and 100)
            std::uniform_int_distribution<> distribution(start, end);

            // Generate and print a random number
            return distribution(gen);
        }
        static int getRandomInt(int start, int end, std::vector<int> used){
            int num;
            // Set up a random number generator
            static std::random_device rd;  // Use hardware entropy if available

            std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

            // Generate and print a random number

            // Define a distribution (for example, integers between 1 and 100)
                std::uniform_int_distribution<> distribution(start, end);
            if(!used.empty()){
                do{
                    num = distribution(gen); //make new number

                    //find returns used.end() if num is nowhere to be seen in the vector
                    if(std::find(used.begin(), used.end(), num) == used.end()){ //checks if num is already in used
                        //we found good number
                        break;
                    }

                }while(true);
            }
            else{
                num = distribution(gen);
            }
            




            return num;
        }
        
        static double getRandomDouble(double start, double end){
            // Seed the random number generator
            std::random_device rd;
            std::default_random_engine generator(rd());

            // Create a uniform real distribution
            std::uniform_real_distribution<double> distribution(start, end);

            // Generate and return a random double
            return distribution(generator);
        }
        static float getRandomFloat(float start, float end){
            // Seed the random number generator
            std::random_device rd;
            std::default_random_engine generator(rd());

            // Create a uniform real distribution
            std::uniform_real_distribution<float> distribution(start, end);

            // Generate and return a random double
            return distribution(generator);
        }
};
#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> twoSum(std::vector<int> nums, int target) {
    std::unordered_map<int, int> map;
    //                  index, num
    int result;
    std::vector<int> solution;

    if(nums.size() == 2){
        return {0,1};
    }
    
    for(int i = 0; i < nums.size(); i++){
        map[nums[i]] = i; // now all of nums are in the map
    }

    for(int i = 0; i < nums.size(); i++){
        result = target - nums[i];

        //check to see if result is in nums
        if((map.count(result) !=0) && map[result] != i){ 
            //map.count(result) returns amount of entries with result index (if its 0 then it doesnt exist)
            //map[result] != i checks to see if the index of result is equal to i. (not allowed)

            //so basically this if checks:
        //if: "result" exists as an element in "map" AND the output of putting "result" into "map" is not equal to i


            return {i, map[result]};

            //map[result] returns index where result value is
        }


        // auto it = map.find(result);

        // if(it != map.end()){
        //     std::cout << i << ',' << it->second << '\n';
        // } 
    }


    // std::cout << "INN\n";
    return solution;

}


int main(){

    twoSum({2,7,11,15}, 9);

    std::cout << "Program Terminated";

  return 0;
}
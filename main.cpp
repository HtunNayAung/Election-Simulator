#include "view.h"
#include "controller.h"
#include<vector>

int main(int argc, char const *argv[]){
    if(argc == 3){
        int n = std::atoi(argv[1]);
        if(n < 1 || n > 10){
            std::cerr << "The number of electoral divisions should be in the range 1 to 10 inclusive.\n";
            return 1;
        }
        int m = std::atoi(argv[2]);
        if(m < 1 || n > 30){
            std::cerr << "The campaigning days should be in the range 1 to 30 inclusive.\n";
            return 1;
        }
        ElectionController ec;
        ec.startSimulation(n, m);
    } else{
        std::cerr << "Please provide arguments in the following order\nNumber of electoral divisions | Number of campaigning days \n";
        return 1;  
    }

    return 0;
    
}
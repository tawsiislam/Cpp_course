#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <string>
#include <map>
#include <random>
#include <functional>
#include "waterManager.h"

using namespace std;

bool printInCompiler = true; //True will print in compiler and false willl not
WaterManager waterManagerObject;
std::unordered_map<std::thread::id, std::string> mapThreadID;

void printThirsty(std::thread::id thread_id){
    if(printInCompiler){
        cout << mapThreadID.at(thread_id) << " is thirsty." << endl;
    }
}

void printState(std::thread::id thread_id, bool animalEntering){
    if(printInCompiler){
        if(animalEntering == true){
            cout << mapThreadID.at(thread_id) << " enters the water cave. There are inside: Hyenas: " + to_string(waterManagerObject.hyenasInside) + " and Gnus: " + to_string(waterManagerObject.gnusInside) << endl;
        }
        else if(animalEntering == false){
            cout << mapThreadID.at(thread_id) << " finished drinking and exits the water cave. There are inside: Hyenas: " + to_string(waterManagerObject.hyenasInside) + " and Gnus: " + to_string(waterManagerObject.gnusInside) << endl;
        }
    }
}

void WaterManager::hyenaEnters(){
    printThirsty(std::this_thread::get_id());
    std::unique_lock<std::mutex> SOMELOCK(mutexVariable);
    CONDITIONVAR.wait(SOMELOCK, [this] {return gnusInside == 0;});
	hyenasInside += 1;
    printState(std::this_thread::get_id(),true);
}
void WaterManager::gnuEnters(){
    printThirsty(std::this_thread::get_id());
    std::unique_lock<std::mutex> SOMELOCK(mutexVariable);
    CONDITIONVAR.wait(SOMELOCK, [this] {return hyenasInside == 0;});
	gnusInside += 1;
    printState(std::this_thread::get_id(),true);
}
void WaterManager::hyenaLeaves(){
    mutexVariable.lock();
    hyenasInside-=1;
    printState(std::this_thread::get_id(),false);
    mutexVariable.unlock();
    CONDITIONVAR.notify_all();
}
void WaterManager::gnuLeaves(){
    mutexVariable.lock();
    gnusInside-=1;
    printState(std::this_thread::get_id(),false);
    mutexVariable.unlock();
    CONDITIONVAR.notify_all();
}

class Gnu{
    public:
        int id;
        Gnu(int id) : id(id){}

    void operator()(){
        int sleep = rand() % 5 + 3;
        int drink = rand() % 5; 
        std::this_thread::sleep_for(std::chrono::seconds(sleep));
        waterManagerObject.gnuEnters();
        std::this_thread::sleep_for(std::chrono::seconds(drink));
        waterManagerObject.gnuLeaves();
    }
};

std::ostream & operator<<(std::ostream & os, const Gnu & g) {
    os << "Gnu " << g.id;
    return os;
}

// void gnu(){
//     srand(time(NULL));
//         int sleep = rand() % 5 + 4;
//         srand(time(NULL));
//         int drink = rand() % 5; 
//         std::this_thread::sleep_for(std::chrono::seconds(sleep));
//         waterManagerObject.gnuEnters();
//         std::this_thread::sleep_for(std::chrono::seconds(drink));
//         waterManagerObject.gnuLeaves();
// }

void hyena(){
    //srand(time(NULL));
    int sleep = rand() % 5 + 3;
    //srand(time(NULL));
    int drink = rand() % 5; 
    std::this_thread::sleep_for(std::chrono::seconds(sleep));
    waterManagerObject.hyenaEnters();
    std::this_thread::sleep_for(std::chrono::seconds(drink));   
    waterManagerObject.hyenaLeaves();
}

int main(int argc, const char * argv[]) {
    std::vector<thread> threadvec;
    int nrGnus = 4;
    int nrHyenas = 3;
    for (int i = 0; i < nrGnus; i++){
        Gnu g = Gnu(i);
        std::function<void(void)> threadGnu = g;
        threadvec.push_back(thread(threadGnu));
        mapThreadID.insert({threadvec.back().get_id(),"Gnu "+ to_string(i+1)});
    }

    for (int i = 0; i < nrHyenas; i++){
        threadvec.push_back(thread(hyena));
        mapThreadID.insert({threadvec.back().get_id(),"Hyena "+ to_string(i+1)});

    }

    for (auto& thread : threadvec){
	    thread.join();
    }
    return 0;
}

#ifndef waterManager_h
#define waterManager_h
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <thread>

using namespace std;

class WaterManager{

    public:
        std::condition_variable CONDITIONVAR;
        std::mutex mutexVariable;
        std::atomic<int> hyenasInside;
        std::atomic<int> gnusInside;

        //void printState(std::thread::id thread_id, bool animalEntering, bool thirsty);
        void hyenaEnters();
        void gnuEnters();
        void hyenaLeaves();
        void gnuLeaves();
};

#endif /*WATERMANAGER_H*/
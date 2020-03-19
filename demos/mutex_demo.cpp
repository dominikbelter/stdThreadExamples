#include <future>         // std::async, std::future
#include <iostream>
#include <chrono>
#include <random>
#include "Defs/eigen3.h"

class Robot{
public:
    Robot() : leftWheelOrder("left_wheel_order"), rightWheelOrder("right_wheel_order"), maxOrdersNo(20){
    }
    virtual ~Robot(){
    }
    /// go forward
    void goForward(void);
    /// go forward with mutex
    void goForwardMtx(void);

private:
    /// move left wheel
    void moveLeftWheel(void);
    /// move right wheel
    void moveRightWheel(void);
    /// move left wheel mtx
    void moveLeftWheelMtx(void);
    /// move right wheel mtx
    void moveRightWheelMtx(void);

    /// sound made by left wheel
    std::string leftWheelOrder;
    /// sound made by right wheel
    std::string rightWheelOrder;
    /// max orders no
    size_t maxOrdersNo;
    /// mutex to avoid data races
    /// prevent sending orders moving left and right wheel at the same time
    std::mutex mtxWheels;
};

void Robot::goForward(void){
    std::thread t1(&Robot::moveLeftWheel, this);
    std::thread t2(&Robot::moveRightWheel, this);
    t1.join();
    t2.join();
}

void Robot::moveLeftWheel(void){
    for (size_t iterNo=0;iterNo<maxOrdersNo;iterNo++){
        std::cout << leftWheelOrder << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
void Robot::moveRightWheel(void){
    for (size_t iterNo=0;iterNo<maxOrdersNo;iterNo++){
        std::cout << rightWheelOrder << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void Robot::goForwardMtx(void){
    std::thread t1(&Robot::moveLeftWheelMtx, this);
    std::thread t2(&Robot::moveRightWheelMtx, this);
    t1.join();
    t2.join();
}

void Robot::moveLeftWheelMtx(void){
    for (size_t iterNo=0;iterNo<maxOrdersNo;iterNo++){
        mtxWheels.lock();
        std::cout << leftWheelOrder << "\n";
        mtxWheels.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
void Robot::moveRightWheelMtx(void){
    for (size_t iterNo=0;iterNo<maxOrdersNo;iterNo++){
        mtxWheels.lock();
        std::cout << rightWheelOrder << "\n";
        mtxWheels.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main()
{
    try {
        std::cout << "Mutex example\n";
        Robot robot;

        std::cout << "Without mutex: sometimes orders are sent to both wheels at the same time (we've got data race)\n";
        robot.goForward();

        std::cout << "\nWith mutex: only one order/line\n";
        robot.goForwardMtx();
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}

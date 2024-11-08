#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "./../CabAllocationSystem/CabAllocationSystem.h"
#include "./../User/User.h"

class ConsoleUI
{
private:
    CabAllocationSystem &cabAllocationSystem;
    User &currentUser;

 
    void displayMenu() const;
    void displayCabs(const std::vector<Cab> &cabs) const;
    void displayUserInfo() const;
    void requestCab();
    void completeTrip();

public:
    ConsoleUI(CabAllocationSystem &cabAllocSys, User &currentUser);

   
    void processUserInput();
};

#endif
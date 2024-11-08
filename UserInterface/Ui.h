#ifndef UI_H
#define UI_H

#include "./../CabAllocationSystem/CabAllocationSystem.h"
#include "./../User/User.h"

class ConsoleUI
{
private:
    CabAllocationSystem &cabAllocationSystem;
    User currentUser;

public:
    ConsoleUI(CabAllocationSystem &cabAllocSys, User &currentUser);

    void displayMenu();
    void processUserInput(CabAllocationSystem &cabAllocSys, User &currentUser);
};

#endif

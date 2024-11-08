#include <iostream>
#include "Location/Location.h"
#include "Cab/Cab.h"
#include "Trip/Trip.h"
#include "CabAllocationSystem/CabAllocationSystem.h"
#include "CabSearch/CabSearch.h"
#include "Auth/AuthSystem.h"
#include "User/UserFactory.h"
#include "Auth/AuthHelper.h"
#include "User/User.h"
#include "UserInterface/Ui.h"

int main(){

  AuthSystem authSystem;
  
  User user1 = UserFactory::createUser(1, "Abhishek", "pass1");
  User user2 = UserFactory::createUser(2, "Rana", "pass2");
  User user3 = UserFactory::createUser(3, "Vipul", "pass3");
  User user4 = UserFactory::createUser(3, "Raj", "pass4");
  authSystem.addUser(user1);
  authSystem.addUser(user2);
  authSystem.addUser(user3);
  authSystem.addUser(user4);

  int authenticationSuccessful = AuthenticationHelper::performAuthentication(authSystem);
  User currentUser = authSystem.getUser(authenticationSuccessful);
  int currentUserId = -1;

  if (authenticationSuccessful != -1)
  {
       
        currentUserId = authenticationSuccessful;
  }
  else
  {
        std::cerr << "Authentication failed. Exiting the program." << std::endl;
        exit(EXIT_FAILURE);
  }

  CabAllocationSystem cabAllocationSystem;

    Cab cab1(1, Location(37.7749, -122.4194)); 
    Cab cab2(2, Location(34.0522, -118.2437));
    Cab cab3(3, Location(31.0522, -129.2437));
    Cab cab4(4, Location(40.7128, -74.0060));   
    Cab cab5(5, Location(41.8781, -87.6298));   
    Cab cab6(6, Location(29.7604, -95.3698));   
    Cab cab7(7, Location(33.4484, -112.0740));  
    Cab cab8(8, Location(39.7392, -104.9903)); 
    Cab cab9(9, Location(32.7157, -117.1611)); 
    Cab cab10(10, Location(47.6062, -122.3321)); 

    cabAllocationSystem.addCab(cab1);
    cabAllocationSystem.addCab(cab2);
    cabAllocationSystem.addCab(cab3);
    cabAllocationSystem.addCab(cab4);
    cabAllocationSystem.addCab(cab5);
    cabAllocationSystem.addCab(cab6);
    cabAllocationSystem.addCab(cab7);
    cabAllocationSystem.addCab(cab8);
    cabAllocationSystem.addCab(cab9);
    cabAllocationSystem.addCab(cab10);

    std::cout << "Initial Cab Locations:" << std::endl;
    std::cout << "Cab 1: (" << cab1.getCurrentLocation().getLatitude() << ", " << cab1.getCurrentLocation().getLongitude() << ")" << std::endl;
    std::cout << "Cab 2: (" << cab2.getCurrentLocation().getLatitude() << ", " << cab2.getCurrentLocation().getLongitude() << ")" << std::endl;
    std::cout << "Cab 3: (" << cab3.getCurrentLocation().getLatitude() << ", " << cab3.getCurrentLocation().getLongitude() << ")" << std::endl;
    std::cout << "Cab 4: (" << cab1.getCurrentLocation().getLatitude() << ", " << cab1.getCurrentLocation().getLongitude() << ")" << std::endl;
    std::cout << "Cab 5: (" << cab2.getCurrentLocation().getLatitude() << ", " << cab2.getCurrentLocation().getLongitude() << ")" << std::endl;
    std::cout << "Cab 6: (" << cab3.getCurrentLocation().getLatitude() << ", " << cab3.getCurrentLocation().getLongitude() << ")" << std::endl;
    std::cout << "Cab 7: (" << cab1.getCurrentLocation().getLatitude() << ", " << cab1.getCurrentLocation().getLongitude() << ")" << std::endl;
    std::cout << "Cab 8: (" << cab2.getCurrentLocation().getLatitude() << ", " << cab2.getCurrentLocation().getLongitude() << ")" << std::endl;
    std::cout << "Cab 9: (" << cab3.getCurrentLocation().getLatitude() << ", " << cab3.getCurrentLocation().getLongitude() << ")" << std::endl;
    std::cout << "Cab 10: (" << cab3.getCurrentLocation().getLatitude() << ", " << cab3.getCurrentLocation().getLongitude() << ")" << std::endl;

    ConsoleUI consoleUI(cabAllocationSystem, currentUser);

   
    std::cout << "\n==== Smart Cab Allocation System ====\n";
    consoleUI.processUserInput(cabAllocationSystem, currentUser);
    std::cout << "====================================\n";











}
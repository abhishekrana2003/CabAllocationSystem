#include "Ui.h"
#include <iostream>
#include <vector>
#include "./../CabAllocationSystem/CabAllocationSystem.h"
#include "./../CabSearch/CabSearch.h"
#include "./../Trip/Trip.h"

ConsoleUI::ConsoleUI(CabAllocationSystem &cabAllocSys, User &currentUser) : cabAllocationSystem(cabAllocSys), currentUser(currentUser){};

void ConsoleUI::displayMenu()
{
    std::cout << "\n ================================== \n";
    std::cout << "|   Smart Cab Allocation System   |\n";
    std::cout << "|==================================| \n";
    std::cout << "| 1. Display Nearby Cab Locations  |\n";
    std::cout << "| 2. Request a Cab                 |\n";
    std::cout << "| 3. Trip completed                |\n";
    std::cout << "| 4. Get UserID and user location  |\n";
    std::cout << "| 5. Exit                          |\n";
    std::cout << "|==================================|\n";
}

void ConsoleUI::processUserInput(CabAllocationSystem &cabAllocSys, User &currentUser)
{
    int choice;
    double userLatitudeStart, userLongitudeStart, userLatitudeEnd, userLongitudeEnd;

    std::cout << "Enter your current latitude: ";
    std::cin >> userLatitudeStart;
    std::cout << "Enter your current longitude: ";
    std::cin >> userLongitudeStart;

    currentUser.setCurrentLocation(Location(userLatitudeStart, userLongitudeStart));

    Location tripStartLocation(userLatitudeStart, userLongitudeStart);

    std::vector<Cab> allCabs = cabAllocSys.getAllCabs();

    // Display initial cab locations
    std::cout << "Initial Cab Locations:" << std::endl;
    for (const auto &cab : allCabs)
    {
        std::cout << "Cab ID: " << cab.getCabId() << ", Location: (" << cab.getCurrentLocation().getLatitude() << ", " << cab.getCurrentLocation().getLongitude() << ")" << std::endl;
    }

    EmployeeCabSearch employeeCabSearch(tripStartLocation, cabAllocSys);

    std::vector<Cab> nearbyCabs;

    do
    {
        displayMenu();
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Display Cab Locations

            std::cout << "Enter your current latitude: ";
            std::cin >> userLatitudeStart;
            std::cout << "Enter your current longitude: ";
            std::cin >> userLongitudeStart;

            currentUser.setCurrentLocation(Location(userLatitudeStart, userLongitudeStart));

            Location tripStartLocation(userLatitudeStart, userLongitudeStart);

            try
            {
                EmployeeCabSearch employeeCabSearch(tripStartLocation, cabAllocSys);

                nearbyCabs = employeeCabSearch.suggestNearbyCabs();

                // Display suggested nearby cabs
                std::cout << "|==========================================|" << std::endl;
                std::cout << "| Suggested Nearby Cabs:            |" << std::endl;
                std::cout << "|==========================================|" << std::endl;
                for (const auto &cab : nearbyCabs)
                {
                    std::cout << "| Cab ID: " << cab.getCabId() << ", Location: (" << cab.getCurrentLocation().getLatitude() << ", " << cab.getCurrentLocation().getLongitude() << ") |" << std::endl;
                }
                std::cout << "|==========================================|" << std::endl;
            }
            catch (const std::exception &e)
            {
                // Handle exception
                std::cerr << "Error: " << e.what() << std::endl;
            }

            break;
        }

        case 2:
        {

            // Request a Cab
            if (currentUser.getCurrentTripID() != -1)
            {
                std::cout << "You already have a trip booked. Please complete the trip before booking another one." << std::endl;
                break;
            }

            std::cout << "Enter your current latitude: ";
            std::cin >> userLatitudeStart;
            std::cout << "Enter your current longitude: ";
            std::cin >> userLongitudeStart;

            currentUser.setCurrentLocation(Location(userLatitudeStart, userLongitudeStart));

            Location tripStartLocation(userLatitudeStart, userLongitudeStart);

            std::vector<Cab> allCabs = cabAllocSys.getAllCabs();

            EmployeeCabSearch employeeCabSearch(tripStartLocation, cabAllocSys);

            nearbyCabs = employeeCabSearch.suggestNearbyCabs();

            if (nearbyCabs.empty())
            {
                std::cout << "No cabs available." << std::endl;
                break;
            }

            std::cout << "Enter your destination latitude: ";
            std::cin >> userLatitudeEnd;
            std::cout << "Enter your destination longitude: ";
            std::cin >> userLongitudeEnd;

            Location tripEndLocation(userLatitudeEnd, userLongitudeEnd);

            Trip trip(tripStartLocation, tripEndLocation);

            Cab bestCab(-1, Location(0.0, 0.0));
            bool cabFound = false;

            try
            {
                bestCab = cabAllocSys.findBestCab(trip);
                cabFound = true;
                // Proceed with using bestCab
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
                std::cerr << "Exiting the program." << std::endl;
                // Perform cleanup or additional actions if needed
                exit(EXIT_FAILURE);
            }

            // Display the best cab information only if a cab was found
            if (cabFound)
            {
                // Find the best cab fare
                double fare = cabAllocSys.calculateFareForBestCab(bestCab, tripStartLocation, tripEndLocation);

                std::cout << "|==============================================|" << std::endl;
                std::cout << "| Best Cab for the Trip:                       |" << std::endl;
                std::cout << "| Cab ID: " << bestCab.getCabId() << std::endl;
                std::cout << "| Current Location of Cab: (" << bestCab.getCurrentLocation().getLatitude() << ", " << bestCab.getCurrentLocation().getLongitude() << ")" << std::endl;
                std::cout << "| Trip Start Location: (" << tripStartLocation.getLatitude() << ", " << tripStartLocation.getLongitude() << ")" << std::endl;
                std::cout << "| Trip End Location: (" << tripEndLocation.getLatitude() << ", " << tripEndLocation.getLongitude() << ")" << std::endl;
                std::cout << "| Fare for the trip: $" << fare << std::endl;
                std::cout << "|==============================================|" << std::endl;

                std::cout << "| Do you want to book the cab? (0/1)           |" << std::endl;
                int book;
                std::cin >> book;
                if (book == 0)
                {
                    std::cout << "| Cab not booked.                               |" << std::endl;
                    break;
                }
                std::cout << "| Booking the cab...                           |" << std::endl;
                bestCab.bookCab();
                currentUser.setCurrentTripID(bestCab.getCabId());
                std::cout << "| Cab booked!                                  |" << std::endl;
            }
            else
            {
                std::cout << "No cabs available." << std::endl;
            }

            break;
        }

        case 3:
        {
            // Trip completed. Update cab location and set isFree to true

            if (currentUser.getCurrentTripID() == -1)
            {
                std::cout << "You do not have a trip booked. Please book a trip before completing one." << std::endl;
                break;
            }

            std::cout << "|==============================================|" << std::endl;
            std::cout << "| Trip completed!                               |" << std::endl;
            std::cout << "|==============================================|" << std::endl;

            Cab currentCab = cabAllocSys.getCabByID(currentUser.getCurrentTripID());
            Location tripEnd(userLatitudeEnd, userLongitudeEnd);
            currentCab.setCurrentLocation(tripEnd);
            
            currentCab.unbookCab();
            currentUser.setCurrentTripID(-1);

            auto &cabs = employeeCabSearch.getAllCabs();

            cabs[currentCab.getCabId() - 1] = currentCab;

            currentUser.setCurrentLocation(tripEnd);

            std::cout << "\n";

            // Dispay user location
            std::cout << "|==============================================|" << std::endl;
            std::cout << "| User Location: (" << currentUser.getCurrentLocation().getLatitude() << ", " << currentUser.getCurrentLocation().getLongitude() << ")" << std::endl;

            // Display updated cab locations
            std::cout << "Updated Cab Location:" << std::endl;
            std::cout << "Cab ID: " << currentCab.getCabId() << ", Location: (" << currentCab.getCurrentLocation().getLatitude() << ", " << currentCab.getCurrentLocation().getLongitude() << ")" << std::endl;

            break;
        }

        // get my userID and location

        case 4:
        {
            try
            {
                // Get user ID
                int userID = currentUser.getUserID();

                // Get user location
                Location userLocation = currentUser.getCurrentLocation();
                double userLatitude = userLocation.getLatitude();
                double userLongitude = userLocation.getLongitude();
                int currentCabID = currentUser.getCurrentTripID();

                std::cout << "+----------------------------------------+" << std::endl;
                std::cout << "| User ID: " << userID << std::endl;
                std::cout << "| User Location: (" << userLatitude << ", " << userLongitude << ")" << std::endl;
                std::cout << "| Currently Booked CabID: " << currentCabID << std::endl;
                std::cout << "+----------------------------------------+" << std::endl;
            }
            catch (const std::exception &e)
            {
                // Handle exception
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        case 5:
            std::cout << "Exiting the program. Goodbye!\n";
            break;

        default:
            std::cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
    } while (choice != 5);
}

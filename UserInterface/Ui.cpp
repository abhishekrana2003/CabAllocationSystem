#include "Ui.h"
#include <iostream>
#include <vector>
#include "./../CabAllocationSystem/CabAllocationSystem.h"
#include "./../CabSearch/CabSearch.h"
#include "./../Trip/Trip.h"

ConsoleUI::ConsoleUI(CabAllocationSystem &cabAllocSys, User &currentUser)
    : cabAllocationSystem(cabAllocSys), currentUser(currentUser) {}

void ConsoleUI::displayMenu() const
{
    std::cout << "\n==================================\n";
    std::cout << "|   Smart Cab Allocation System   |\n";
    std::cout << "|=================================|\n";
    std::cout << "| 1. Display Nearby Cab Locations |\n";
    std::cout << "| 2. Request a Cab                |\n";
    std::cout << "| 3. Complete Trip                |\n";
    std::cout << "| 4. View User Info               |\n";
    std::cout << "| 5. Exit                         |\n";
    std::cout << "===================================\n";
}

void ConsoleUI::displayCabs(const std::vector<Cab> &cabs) const
{
    if (cabs.empty())
    {
        std::cout << "No cabs available.\n";
        return;
    }
    std::cout << "| Suggested Nearby Cabs:           |\n";
    for (const auto &cab : cabs)
    {
        std::cout << "| Cab ID: " << cab.getCabId() << ", Location: (" 
                  << cab.getCurrentLocation().getLatitude() << ", " 
                  << cab.getCurrentLocation().getLongitude() << ") |\n";
    }
}

void ConsoleUI::displayUserInfo() const
{
    std::cout << "+----------------------------------------+\n";
    std::cout << "| User ID: " << currentUser.getUserID() << "\n";
    std::cout << "| User Location: (" << currentUser.getCurrentLocation().getLatitude()
              << ", " << currentUser.getCurrentLocation().getLongitude() << ")\n";
    std::cout << "| Current Trip ID: " << currentUser.getCurrentTripID() << "\n";
    std::cout << "+----------------------------------------+\n";
}

void ConsoleUI::requestCab()
{
    if (currentUser.getCurrentTripID() != -1)
    {
        std::cout << "You already have a trip booked. Complete it before requesting another.\n";
        return;
    }

    double startLat, startLon, endLat, endLon;
    std::cout << "Enter your current latitude: ";
    std::cin >> startLat;
    std::cout << "Enter your current longitude: ";
    std::cin >> startLon;
    currentUser.setCurrentLocation(Location(startLat, startLon));

    EmployeeCabSearch employeeCabSearch(Location(startLat, startLon), cabAllocationSystem);
    auto nearbyCabs = employeeCabSearch.suggestNearbyCabs();

    if (nearbyCabs.empty())
    {
        std::cout << "No nearby cabs available.\n";
        return;
    }

    displayCabs(nearbyCabs);

    std::cout << "Enter your destination latitude: ";
    std::cin >> endLat;
    std::cout << "Enter your destination longitude: ";
    std::cin >> endLon;

    try
    {
        Cab bestCab = cabAllocationSystem.findBestCab(Trip(Location(startLat, startLon), Location(endLat, endLon)));
        double fare = cabAllocationSystem.calculateFareForBestCab(bestCab, Location(startLat, startLon), Location(endLat, endLon));
        std::cout << "Best Cab ID: " << bestCab.getCabId() << " with fare: $" << fare << "\n";

        std::cout << "Do you want to book this cab? (1 = Yes, 0 = No): ";
        int book;
        std::cin >> book;
        if (book == 1)
        {
            bestCab.bookCab();
            currentUser.setCurrentTripID(bestCab.getCabId());
            std::cout << "Cab booked successfully!\n";
        }
        else
        {
            std::cout << "Cab booking cancelled.\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void ConsoleUI::completeTrip()
{
    if (currentUser.getCurrentTripID() == -1)
    {
        std::cout << "You do not have an active trip.\n";
        return;
    }

    try
    {
        Cab currentCab = cabAllocationSystem.getCabByID(currentUser.getCurrentTripID());
        std::cout << "Enter trip end latitude: ";
        double endLat;
        std::cin >> endLat;
        std::cout << "Enter trip end longitude: ";
        double endLon;
        std::cin >> endLon;

        Location endLocation(endLat, endLon);
        currentCab.setCurrentLocation(endLocation);
        currentCab.unbookCab();
        currentUser.setCurrentTripID(-1);
        std::cout << "Trip completed successfully!\n";
        displayUserInfo();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void ConsoleUI::processUserInput()
{
    int choice;
    do
    {
        displayMenu();
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            displayCabs(EmployeeCabSearch(currentUser.getCurrentLocation(), cabAllocationSystem).suggestNearbyCabs());
            break;
        case 2:
            requestCab();
            break;
        case 3:
            completeTrip();
            break;
        case 4:
            displayUserInfo();
            break;
        case 5:
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
    } while (choice != 5);
}
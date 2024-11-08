#include "AuthHelper.h"

int AuthenticationHelper::performAuthentication(AuthSystem &authSystem)
{
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    int userID = authSystem.authenticateUser(username, password);

    if (userID != -1)
    {
        std::cout << "Authentication successful. Access granted." << std::endl;
        return userID;
    }
    else
    {
        std::cout << "Authentication failed. Access denied." << std::endl;
        return -1;
    }
}
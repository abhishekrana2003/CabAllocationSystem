# Smart Cab Allocation System

## Overview

The **Smart Cab Allocation System** is designed to optimize cab allocation based on real-time location data, enhancing user experience and improving operational efficiency. Developed with C++ for performance and modularity, this system includes core functionalities for admin and employee interactions.

### Key Features

1. **Admin's Cab Allocation Optimization**:
   - **Objective**: Minimize overall travel distance by allocating the nearest cab to each trip's start location.
   - **Approach**:
     - Implements an algorithm to find the closest available cab.
     - Tests show effectiveness in reducing travel time and distance.

2. **Employee's Cab Search Optimization**:
   - **Objective**: Suggest nearby cabs currently in use for improved user experience.
   - **Approach**:
     - Uses real-time data to display engaged cabs near the employee's location.
     - Performance is evaluated based on user feedback and system responsiveness.

3. **Real-Time Location Integration**:
   - **Objective**: Ensure accurate, up-to-date cab location data.
   - **Approach**:
     - Integrates a real-time tracking system to maintain reliability.
     - Addresses potential data latency for smooth, responsive cab allocation.

### Tech Stack

- **Language**: C++ for performance and efficiency.
- **Object-Oriented Programming**: Encapsulation, polymorphism, and inheritance for modular and reusable code.
- **Real-Time Data Handling**: Manages dynamic cab and trip data.
- **Algorithm Development**: Proximity-based allocation algorithm designed with C++ OOP principles.

### System Architecture

- **Authentication**: Secure access via username and password authentication.
- **Cab Allocation Algorithm**:
  - **Time Complexity**: \( O(nlog(n)) \) where \( n \) is the number of cabs.
  - **Space Complexity**: \( O(n) \), for storing cab location data.
- **OOP Design**:
  - **Encapsulation**: Data and methods encapsulated within classes.
  - **Polymorphism**: Flexible functions, e.g., `getAllCabs()`.
  - **Modularity**: Organized into components, allowing for easy updates and extensions.

# SKROT-NAV
A general navigation system for a debris-collecting spacecraft, placed in a simulated earth orbit with the idea of being able to be used in real space (not possible at current state). This code is part of my upper secondary school graduation project.

![screenshot of skrot-nav from 2025-02-07](https://github.com/owlbeatsmusic/skrot-nav/blob/main/docs/images/screenshot_2025-02-07.png?raw=true)

> [!NOTE]
> Everything from this point forward in the README file is **translated** from **swedish** to **english** by ChatGPT 4o and is part of my graduation project.

<br>

## 1.2 Purpose
By programming a custom navigation system, the goal is to gain a better understanding of how the subsystems are structured and to gain insight into the availability of resources in the field. The 'general' characteristic of the navigation system was chosen with the aim of creating a template to enhance the accessibility of constructing a navigation system in space for a debris-collecting spacecraft.

<br>

## 1.5 Method

### 1.5.1 Introduction  
This method will primarily involve an account and explanation of the program's structure. The most overarching division of the program consists of the engine and the navigation system. The engine manages the simulation in which the navigation system operates, as well as handling the visual user interface. The navigation system is the actual program that, in practice, would run on the spacecraft in space.

Initially, the programming environment will be briefly described, followed by the engine and finally the navigation system. The engine can be compared to the environment surrounding the navigation system and consists of three parts. The first part is the space simulation, which calculates forces and updates position. The second part is the downlink simulation, which handles communication with Earth. The last part is the renderer, which manages the user interface and thus the connection between the program and the user.

The navigation system is primarily divided into the core, which serves as the foundation of the navigation system, the flight path determination, which creates the route for collecting space debris, and finally the position determination, which is necessary for flight path creation. The navigation system also includes a component for communication and a component for interaction with devices such as RADAR.

![project-structure-overview](https://github.com/owlbeatsmusic/skrot-nav/blob/main/docs/images/project-overview-diagram.png?raw=true)

**Figure 1**: Diagram of the overall file structure and the interaction between the engine (`/src/engine/`) and the navigation system (`/src/nav/`).  

The primary purpose of the navigation system is to serve as a template for practical applications while remaining operational within the simulation. The components should be independent, as the navigation system must be separable from the engine and applicable in real-world scenarios. The entire codebase is also open-source to facilitate practical use. Open-source means that the code is publicly available on the internet. The two-part structure of the program, consisting of the engine and the navigation system, thus forms the foundation of the entire project.

There is also a third component in the overall structure: utility functions. These functions are general, meaning they can be used across various parts of the program and are not specific to any single component. An example of a utility function is the function "vector_normalize()" in the file "/src/common/vector.c", which calculates the normal of a vector.

To begin planning the engine and navigation system, relevant sources were consulted. NASA’s "Basics of Spaceflight", a website written by Dave Doody (Doody, 2024), provides an overview of the fundamentals of spaceflight. The site discusses various types of spacecraft, their components, and how navigation works in space. The latter is of particular interest for this study, along with the technical specifications of some components. The broad division of the navigation system is to create and control flight paths. To generate these flight paths, information about the spacecraft's position (Doody, 2024) and the position of nearby debris is required.

---

</br>

### 1.5.2 Programming Environment  
The entire project is programmed in the C programming language and follows the ISO9899:1999 standard, which is the C standard from 1999. Compilation and most of the code adhere to NASA's Jet Propulsion Laboratory (JPL) standard for C (JPL, 2009).  

---

</br>

### 1.5.3 The Engine  

#### 1.5.3.1 Space Simulation (`src/engine/space.c`)  
The engine is developed before the navigation system. The space simulation is limited to the minimal requirements necessary for the navigation system to function. This limitation is due to the fact that the simulation is not the primary focus of the study, and time for the project is restricted. The goal of the space simulation is to generate space debris and simulate both the debris and the debris-collecting spacecraft’s orbit around Earth. The core of this part of the engine is a loop that primarily updates all positions using Euler’s method. The loop repeats a variable number of times (steps) with an interval of ∆t. For each step, a function calculates the gravitational force exerted on each object to determine acceleration, which is then used to calculate the object’s velocity using Euler’s method:  

$v_x = a_x \cdot \Delta t$

$v_y = a_y \cdot \Delta t$

$v_z = a_z \cdot \Delta t$

The initial positions of all objects, i.e., the spacecraft and space debris, are randomly placed in Low Earth Orbit (LEO). For them to follow a correct orbital path around Earth, their initial velocity must be set to orbital velocity and the velocity direction must be perpendicular to the position vector. This is achieved by calculating the magnitude of the vector using the orbital velocity formula and determining the vector direction by taking the cross product of the position vector with an arbitrary vector. Finally, the object's velocity is set. These calculations are represented in the program as follows:  

```c
int r = vector_distance(position, earth_pos);
float orbital_velocity = sqrt(G * M / r);

Vector3 temp_vector = {0, 0, 1};
Vector3 velocity_direction = vector_cross_product(position, temp_vector);
velocity_direction = vector_normalize(velocity_direction);

SpaceObject temp_space_object = {
    type,
    (Vector3){ position.x, position.y, position.z },
    (Vector3){ velocity_direction.x * orbital_velocity,
               velocity_direction.y * orbital_velocity, 
               velocity_direction.z * orbital_velocity }, 
    mass
};
```

---

</br>

#### 1.5.3.2 Renderer (`src/engine/renderer.c`)  
The graphical user interface is not directly relevant to the research question, similar to the space simulation, but its goal is to quickly visualize necessary information for the user to verify the navigation system's functionality. The most important function of the renderer is to display Earth’s orbit to illustrate the position of space debris and the spacecraft. This representation is done through views showing a 2D image of two axes.  

```c
View renderer_views[] = {
    {0, 0, -1, RENDERER_SPACE_WIDTH/2, 'x', 'z'}, 
    {1, 0, -1, RENDERER_SPACE_WIDTH,   'x', 'z'},
    {2, 0, -1, RENDERER_SPACE_WIDTH,   'x', 'y'},
};
```

In this list of views, the order in which they appear in the user interface can be modified with the first two arguments. The scale of the view is determined by the fourth argument, which specifies the width of the view. The third argument determines whether the view should center and follow an object, where `-1` means no object is followed. In the file `main.c`, the first view is set to follow the spacecraft:  

```c
renderer_views[0].center_object_index = nav_spaceobjects_index;
```

#### 1.5.3.3 The Downlink
(src/engine/downlink.c)
The downlink is the communication from the spacecraft to Earth. The goal of the downlink simulation is both to send requests for information from the spacecraft, such as the active flight path, and to receive and respond to requests from the spacecraft.

---

</br>

### 1.5.4 The Navigation System (`src/nav/`)  
The navigation system is fundamentally controlled from the core, where the central process, or loop, resides. In this process, the navigation system is initiated by starting its primary function: the creation of a flight path. A flight path is the trajectory planned by the navigation system to reach space debris. The debris is located by compiling retrieved and collected information. Before generating the flight path, the spacecraft's position in space must be determined, which requires calculations based on data from the downlink.

![navigation-system-diagram](https://github.com/owlbeatsmusic/skrot-nav/blob/main/docs/images/navigation-system-diagram.png?raw=true)

**Figure 2**. Diagram of the main interactions between the navigation system components for the flight path determination subsystem. Flight path, object detection, optimal flight path, and deviations from the planned route are handled in flight_path.c. Position determination is managed in position.c. Communication is handled in communication.c, and device management takes place in devices.c.

</br>

#### 1.5.4.1 Navigation: Core (`src/nav/core.c`)  
The flight path component of the program manages four different aspects, categorized as follows: controlling the program through the central process and connecting the navigation system with the simulation. This means that the core also serves as the starting point of the system. Consequently, the core handles system shutdown and other fundamental functions. The system and the internal clock are initialized and linked to the simulation through the following function (pseudocode):

```c
nav_core_create() {
    nav_spaceobjects_index = space_append_spaceobject();
    start_time = time(NULL);
    nav_core_proc_main_internal();
}
```

</br>

#### 1.5.4.2 Navigation: Flight Path (`src/nav/flight_path.c`)  

The flight path component of the program manages four different aspects, categorized as follows: flight path creation, space debris localization, maneuver planning and execution, and deviations from the planned flight path. The primary focus is on initiating and updating the flight path.

This process occurs in three steps:

Determining the spacecraft’s own position (1.5.4.3).
Locating nearby debris.
Creating and executing the necessary maneuvers.
The position of space debris is identified by scanning the spacecraft's surroundings using selected devices such as RADAR and LIDAR.

</br>

#### 1.5.4.3 Navigation: Position (`src/nav/position.c`)  

The position component of the program manages three different aspects, categorized as follows: evaluation and prediction of position, collision detection, and request and configuration of measurement data. The evaluation of the spacecraft's position begins by sending measurement data requests to the downlink. Once the requested information arrives from the downlink, it is used to calculate the spacecraft's position.

The process from requesting to configuring measurement data is described here. In NASA’s "Basics of Spaceflight", the three most important measurements for determining position in space are highlighted. These are the spacecraft’s distance from Earth, radial velocity, and position in Earth's sky. This information must be retrieved from the downlink, which occurs by first sending a request for the data. The request is a communication data packet containing variables for the different measurements, a unique ID, and a request ID.

The packet is sent to the file communication.c, where it is forwarded to the transmitter in devices.c. From there, the packet is sent to the downlink. In the downlink, a new packet is created, with its request ID set to the original request packet's ID. The requested information is then included in the new packet. Finally, the packet is sent back to communication.c on the spacecraft. From there, the information about the requested measurement data is updated in position.c.

![request-set-diagram](https://github.com/owlbeatsmusic/skrot-nav/blob/main/docs/images/request-set-diagram.png?raw=true)

**Figure 3**. Diagram of the request and configuration of measurement data. The information is retrieved from the downlink and set in the program’s position component (src/nav/position.c).

</br>

#### 1.5.4.4 Navigation: Communication (`src/nav/communication.c`)  
(src/nav/communication.c)
The communication part of the program handles three sections, categorized as follows: packet handling, request queue system, and event file interpretation. Packet handling consists of four functions: creating packets, sending packets, receiving packets, and storing packets.

The packets consist of information sent between different subsystems and between the spacecraft and Earth. There are two types of packets: communication packets and health packets. Communication packets are used for general communication and are either of the receiving type, such as a data request, or of the sending type, such as manual control instructions from Earth. The health packet is mainly used for checking physical devices and contains information such as temperature and pressure.

---

</br>


### 2. Conclusion  

The program structure was largely completed. Several systems necessary for real-world applications, such as launch and return protocols, are missing. However, a basic framework for the most essential subsystems of a space debris collection navigation system has been implemented.  Given the research question('how should a navigation system for a debris collecting spacecraft be structured'), which focuses only on structuring the system, and since the purpose of the program is to serve as a template, many subsystems have not been implemented or simulated. Missing systems include device simulations and a flight path determination algorithm.

---

</br>

### Main Sources
Doody, D. (2024-10-04). Basics of Spaceflight. From NASA: https://science.nasa.gov/learn/basics-of-space-flight/

JPL. (2009-03-03). JPL Institutional Coding Standard for the C Programming Language. From: https://yurichev.com/mirrors/C/JPL_Coding_Standard_C.pdf
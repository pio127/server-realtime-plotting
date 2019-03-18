# Realtime plotting
Created for IoT purpose to plot data received from other device.
Uses linux sockets so it works only under systems based on linux kernel.
# Required libraries :
 - Nlohmann JSON library(https://github.com/nlohmann/json)
 - matlplotlib wrapped for C++(https://github.com/lava/matplotlib-cpp)
 
Server requires only JSON library and client requires both of them.
They can be included as header only or build and installed. However matplotlib wrapper needs python libraries to work
so they must be found by CMake.

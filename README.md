# Realtime plotting
Created for IoT purpose to plot data received from other device.

# Required libraries :
 - Nlohmann JSON library(https://github.com/nlohmann/json)
 - matlplotlib wrapped for C++(https://github.com/nlohmann/json)
Server requires only JSON library and client requires both of them.
They can be included as header only or build and installed. However matplotlib wrapper needs python libraries to work
so they must be found by CMake.

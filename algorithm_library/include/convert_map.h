#include<iostream>

std::pair<int, int> realWorld_to_myWorld(double lat_big, double lat_small, double lon_big, double lon_small, double res);
std::pair<double, double> myWorld_to_realWorld(int myWorld_x, int myWorld_y, double res, double lat_small, double lon_small);

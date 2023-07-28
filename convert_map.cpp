#include<iostream>

std::pair<int, int> realWorld_to_myWorld(double lat_big, double lat_small, double lon_big, double lon_small, double res) {

    double temp_x = (lat_big - lat_small) / res + 1;
    int myWorld_x = static_cast<int>(temp_x);
    double temp_y = (lon_big - lon_small) / res + 1 ;
    int myWorld_y = static_cast<int>(temp_y);
    return std::make_pair(myWorld_x, myWorld_y);
}

std::pair<double, double> myWorld_to_realWorld(int myWorld_x, int myWorld_y, double res, double lat_small, double lon_small) {
    double temp_x = static_cast<double>(myWorld_x);
    double realWorld_x = (temp_x-1) * res + lat_small;
    double temp_y = static_cast<double>(myWorld_y);
    double realWorld_y = (temp_y-1) * res + lon_small;
    return std::make_pair(realWorld_x, realWorld_y);
}
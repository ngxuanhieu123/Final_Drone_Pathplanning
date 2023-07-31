#include<iostream>
#include"map.h"
float update_G_cost(Node& A, Node& B)
{
    int x = A.x;
    int x1 = B.x;
    int y = A.y;
    int y1 = B.y;
    float G = A.G_cost + sqrt(pow((x - x1), 2) + pow((y - y1), 2));
    return G;
}

float calculate_H_cost(Node& A, Node& Final) {
    int hx = A.x;
    int hy = A.y;
    int x1 = Final.x;
    int y1 = Final.y;
    float H;
    H = sqrt(pow((hx - x1), 2) + pow((hy - y1), 2));
    return H;
}

float calculate_J_cost(Node& A) {
    float J = A.H_cost + A.G_cost;
    return J;
}


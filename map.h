#include<iostream>
#include<cmath>
#include<vector>
#include<limits>

#include"convert_map.h"
struct Node
{
public:
    int x, y;
    float G_cost;
    float H_cost;
    float J_cost;
    Node* parent;
    std::vector<Node*>neighbor;
    bool check_childNode = 0;
    bool check_visited = 0;
    bool check_obs = 0;
    Node() {
    }
};

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

class Map
{
private:
    //float min_x, min_y, max_x, max_y;
    int Map_x;
    int Map_y;
    Node* point;
    Node* StartNode;
    Node* FinalNode;
    //std:: vector<std::vector<std::pair<float, float>>> real_Obs;
    std::vector<Node*> Obs;
public:
    Map(int x, int y) : Map_x(x), Map_y(y) {
        point = new Node[Map_x * Map_y];
        for (int iy = 0; iy < Map_y; iy++) {
            for (int ix = 0; ix < Map_x; ix++) {
                point[iy * Map_x + ix].x = ix;
                point[iy * Map_x + ix].y = iy;
            }
        }
        for (int i = 0; i < Map_x * Map_y; i++) {
            point[i].G_cost = std::numeric_limits<float>::infinity();
        }
    }
};
#ifndef MAP_H
#define MAP_H
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



class Map
{
public:
    //float min_x, min_y, max_x, max_y;
    int Map_x;
    int Map_y;
    Node* point;
    Node* StartNode;
    Node* FinalNode;
    //std:: vector<std::vector<std::pair<float, float>>> real_Obs;
    std::vector<Node*> Obs;
    
    void get_map(){
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
    void setup_map(){
        Map_x = 5;
        Map_y = 3;
    }
};

#endif
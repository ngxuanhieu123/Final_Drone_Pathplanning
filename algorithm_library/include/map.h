#ifndef MAP_H
#define MAP_H
#include<iostream>
#include<cmath>
#include<vector>
#include<limits>
#include <fstream>
#include <string>
#include"convert_map.h"
struct Node
{
public:
    int x, y;
    float G_cost;
    float H_cost;
    float J_cost;
    Node* parent;
    std::vector<Node*> ChildNodes;
    bool check_childNode = 0;
    bool check_visited = 0;
    bool check_obs = 0;
    bool check_result = 0;
    Node() {
    }
};



class Map
{
public:
    double min_lat, min_lon, max_lat, max_lon;
    int Map_x;
    int Map_y;
    Node* point;
    Node* StartNode;
    Node* FinalNode;
    //std:: vector<std::vector<std::pair<float, float>>> real_Obs;
    std::vector<Node*> Obs;

    Map(){
        Map_x = 33;
        Map_y = 42;
    }

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
        for(int i = 0; i < Map_x*Map_y; i++){
            if (point[i].x - 1 >= 0 && point[i].y + 1 >= 0 && point[i].x - 1 < Map_x && point[i].y + 1 < Map_y) {
                Node* ChildNode_1 = &point[(point[i].y + 1) * Map_x + point[i].x - 1];
                point[i].ChildNodes.push_back(ChildNode_1);
            }
            if (point[i].x >= 0 && point[i].y + 1 >= 0 && point[i].x < Map_x && point[i].y + 1 < Map_y) {
                Node* ChildNode_2 = &point[(point[i].y + 1) * Map_x + point[i].x];
                point[i].ChildNodes.push_back(ChildNode_2);
            }
            if (point[i].x + 1 >= 0 && point[i].y + 1 >= 0 && point[i].x + 1 < Map_x && point[i].y + 1 < Map_y) {
                Node* ChildNode_3 = &point[(point[i].y + 1) * Map_x + point[i].x + 1];
                point[i].ChildNodes.push_back(ChildNode_3);
            }
            if (point[i].x + 1 >= 0 && point[i].y >= 0 && point[i].x + 1 < Map_x && point[i].y < Map_y) {
                Node* ChildNode_4 = &point[(point[i].y) * Map_x + point[i].x + 1];
                point[i].ChildNodes.push_back(ChildNode_4);
            }
            if (point[i].x + 1 >= 0 && point[i].y - 1 >= 0 && point[i].x + 1 < Map_x && point[i].y - 1 < Map_y) {
                Node* ChildNode_5 = &point[(point[i].y - 1) * Map_x + point[i].x + 1];
                point[i].ChildNodes.push_back(ChildNode_5);
            }
            if (point[i].x >= 0 && point[i].y - 1 >= 0 && point[i].x < Map_x && point[i].y - 1 < Map_y) {
                Node* ChildNode_6 = &point[(point[i].y - 1) * Map_x + point[i].x];
                point[i].ChildNodes.push_back(ChildNode_6);
            }
            if (point[i].x - 1 >= 0 && point[i].y - 1 >= 0 && point[i].x - 1 < Map_x && point[i].y - 1 < Map_y) {
                Node* ChildNode_7 = &point[(point[i].y - 1) * Map_x + point[i].x - 1];
                point[i].ChildNodes.push_back(ChildNode_7);
            }
            if (point[i].x - 1 >= 0 && point[i].y >= 0 && point[i].x - 1 < Map_x && point[i].y < Map_y) {
                Node* ChildNode_8 = &point[(point[i].y) * Map_x + point[i].x - 1];
                point[i].ChildNodes.push_back(ChildNode_8);
            }
        }
    }

    void get_Start(double sx, double sy){
        std::pair<int, int> new_start;
        new_start = realWorld_to_myWorld(sx,min_lat,sy,min_lon,0.0001);
        StartNode = &point[new_start.second*Map_x + new_start.first];
    }

    void get_Final(double fx, double fy){
        std::pair<int, int> new_final;
        new_final = realWorld_to_myWorld(fx,min_lat,fy,min_lon,0.0001);
        FinalNode = &point[new_final.second*Map_x + new_final.first];
    }

    std::vector<std::pair<int, int>> path_smoothing(std::vector<std::pair<int, int>> result){
    if(result.empty()){

    }
    else{
        for(int i=0; i<result.size(); i++){
            Node check_point = point[(result[i].second)*Map_x+result[i].first];
            for(int j =0; j < check_point.ChildNodes.size(); j++){
                for(int k=0; k<Obs.size(); k++){
                    if(check_point.ChildNodes[j]==Obs[k]){
                        check_point.check_result = 1;
                        break;
                    }
                    break;
                }
            }
        }
        for(int i=0; i<result.size(); i++){
            Node check_point = point[(result[i].second)*Map_x+result[i].first];
            if(check_point.check_result != 1){
                result.erase(result.begin()+i);
            }
        }
    }
    return result;
    };
};

#endif
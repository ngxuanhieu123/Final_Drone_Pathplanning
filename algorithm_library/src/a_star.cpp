#include<iostream>
#include<vector>

#include"map.h"
#include"a_star.h"
#include"necessary_function.h"
std::vector<std::pair<int,int>> a_star(Map World_Map){
    Node* CurrentNode;
    World_Map.StartNode->G_cost = 0;
    World_Map.StartNode->parent = World_Map.StartNode;
    CurrentNode = World_Map.StartNode;
    std::vector<Node*> Visited; // queue to store all nodes have been visited
    //Visited.push_back(World_Map.StartNode);
    World_Map.StartNode->check_visited = 1;
    std::vector<Node*> Q; // queue to store all nodes have been taken into consideration
    while (CurrentNode != World_Map.FinalNode)
    {
        std::vector<Node*> ChildNodes;
        if (CurrentNode->x - 1 >= 0 && CurrentNode->y + 1 >= 0 && CurrentNode->x - 1 < World_Map.Map_x && CurrentNode->y + 1 < World_Map.Map_y) {
            Node* ChildNode_1 = &World_Map.point[(CurrentNode->y + 1) * World_Map.Map_x + CurrentNode->x - 1];
            ChildNodes.push_back(ChildNode_1);
        }
        if (CurrentNode->x >= 0 && CurrentNode->y + 1 >= 0 && CurrentNode->x < World_Map.Map_x && CurrentNode->y + 1 < World_Map.Map_y) {
            Node* ChildNode_2 = &World_Map.point[(CurrentNode->y + 1) * World_Map.Map_x + CurrentNode->x];
            ChildNodes.push_back(ChildNode_2);
        }
        if (CurrentNode->x + 1 >= 0 && CurrentNode->y + 1 >= 0 && CurrentNode->x + 1 < World_Map.Map_x && CurrentNode->y + 1 < World_Map.Map_y) {
            Node* ChildNode_3 = &World_Map.point[(CurrentNode->y + 1) * World_Map.Map_x + CurrentNode->x + 1];
            ChildNodes.push_back(ChildNode_3);
        }
        if (CurrentNode->x + 1 >= 0 && CurrentNode->y >= 0 && CurrentNode->x + 1 < World_Map.Map_x && CurrentNode->y < World_Map.Map_y) {
            Node* ChildNode_4 = &World_Map.point[(CurrentNode->y) * World_Map.Map_x + CurrentNode->x + 1];
            ChildNodes.push_back(ChildNode_4);
        }
        if (CurrentNode->x + 1 >= 0 && CurrentNode->y - 1 >= 0 && CurrentNode->x + 1 < World_Map.Map_x && CurrentNode->y - 1 < World_Map.Map_y) {
            Node* ChildNode_5 = &World_Map.point[(CurrentNode->y - 1) * World_Map.Map_x + CurrentNode->x + 1];
            ChildNodes.push_back(ChildNode_5);
        }
        if (CurrentNode->x >= 0 && CurrentNode->y - 1 >= 0 && CurrentNode->x < World_Map.Map_x && CurrentNode->y - 1 < World_Map.Map_y) {
            Node* ChildNode_6 = &World_Map.point[(CurrentNode->y - 1) * World_Map.Map_x + CurrentNode->x];
            ChildNodes.push_back(ChildNode_6);
        }
        if (CurrentNode->x - 1 >= 0 && CurrentNode->y - 1 >= 0 && CurrentNode->x - 1 < World_Map.Map_x && CurrentNode->y - 1 < World_Map.Map_y) {
            Node* ChildNode_7 = &World_Map.point[(CurrentNode->y - 1) * World_Map.Map_x + CurrentNode->x - 1];
            ChildNodes.push_back(ChildNode_7);
        }
        if (CurrentNode->x - 1 >= 0 && CurrentNode->y >= 0 && CurrentNode->x - 1 < World_Map.Map_x && CurrentNode->y < World_Map.Map_y) {
            Node* ChildNode_8 = &World_Map.point[(CurrentNode->y) * World_Map.Map_x + CurrentNode->x - 1];
            ChildNodes.push_back(ChildNode_8);
        }
        // update parent node and G_cost of ChildNode
        for (int i = 0; i < ChildNodes.size(); i++) {
            float Temp_G = update_G_cost(*CurrentNode, *ChildNodes[i]);
            if (Temp_G < ChildNodes[i]->G_cost) {
                ChildNodes[i]->G_cost = Temp_G;
                ChildNodes[i]->parent = CurrentNode;
            }
        }
        // Store childnodes into Q queue
        for (int i = 0; i < Q.size(); i++) {
            for (int j = 0; j < ChildNodes.size(); j++) {
                if (ChildNodes[j] == Q[i]) {
                    ChildNodes[j]->check_childNode = 1;
                    break;
                }
            }
        }
        for (int i = 0; i < ChildNodes.size(); i++) {
            for (int j = 0; j < World_Map.Obs.size(); j++) {
                if (World_Map.Obs[j] == ChildNodes[i]) {
                    ChildNodes[i]->check_obs = 1;
                    break;
                }
            }
        }
        for (int i = 0; i < ChildNodes.size(); i++) {
            if (ChildNodes[i]->check_childNode != 1 && ChildNodes[i]->check_visited != 1 && ChildNodes[i]->check_obs != 1) {
                Q.push_back(ChildNodes[i]);
            }
        }
        // Find the node has the lowest J cost in Q queue and assign it as current node
        Node* Q_min;
        Q_min = Q[0];
        for (int i = 0; i < Q.size(); i++) {
            Q[i]->H_cost = calculate_H_cost(*Q[i], *World_Map.FinalNode);
            Q[i]->J_cost = calculate_J_cost(*Q[i]);
        }
        for (int i = 0; i < Q.size(); i++) {
            for (int j = 0; j < World_Map.Obs.size(); j++) {
                if (Q[i] == World_Map.Obs[j]) {
                    Q[i]->J_cost = std::numeric_limits<float>::infinity();
                    break;
                }
            }
        }
        for (int i = 0; i < Q.size(); i++) {
            if (Q[i]->check_visited != 1 && Q[i]->J_cost < Q_min->J_cost) {
                Q_min = Q[i];
            }
        }
        CurrentNode = Q_min;
        CurrentNode->check_visited = 1;
        for (int i = 0; i < Q.size(); i++) {
            if (Q[i]->check_visited == 1) {
                Q.erase(Q.begin() + i);
            }
        }
        Visited.push_back(CurrentNode);
    }

    std::vector<Node*> Path;
    //Path.push_back(World_Map.FinalNode);
    Node* trackback;
    trackback = Visited[Visited.size() - 1];

    while (trackback->parent != World_Map.StartNode) {
        trackback = trackback->parent;
        Path.insert(Path.begin(), trackback);
    }
    std::vector<std::pair<int, int>> result;
    for (int i = 0; i < Path.size(); i++) {
        result.push_back(std::make_pair(Path[i]->x, Path[i]->y));
    }

    return result;
};

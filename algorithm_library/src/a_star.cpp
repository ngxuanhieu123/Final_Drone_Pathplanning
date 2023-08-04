#include<iostream>
#include<vector>

#include"map.h"
#include"a_star.h"
#include"necessary_function.h"
std::vector<std::pair<int,int>> a_star(Map World_Map){
    std::vector<std::pair<int, int>> result;
    if(World_Map.StartNode == World_Map.FinalNode){
        
    }
    else{
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
            // update parent node and G_cost of ChildNode
            for (int i = 0; i < CurrentNode->ChildNodes.size(); i++) {
                float Temp_G = update_G_cost(*CurrentNode, *(CurrentNode->ChildNodes[i]));
                if (Temp_G < CurrentNode->ChildNodes[i]->G_cost) {
                    CurrentNode->ChildNodes[i]->G_cost = Temp_G;
                    CurrentNode->ChildNodes[i]->parent = CurrentNode;
                }
            }
            // Store childnodes into Q queue
            for (int i = 0; i < Q.size(); i++) {
                for (int j = 0; j < CurrentNode->ChildNodes.size(); j++) {
                    if (CurrentNode->ChildNodes[j] == Q[i]) {
                        CurrentNode->ChildNodes[j]->check_childNode = 1;
                        break;
                    }
                }
            }
            for (int i = 0; i < CurrentNode->ChildNodes.size(); i++) {
                for (int j = 0; j < World_Map.Obs.size(); j++) {
                    if (World_Map.Obs[j] == CurrentNode->ChildNodes[i]) {
                        CurrentNode->ChildNodes[i]->check_obs = 1;
                        break;
                    }
                }
            }
            for (int i = 0; i < CurrentNode->ChildNodes.size(); i++) {
                if (CurrentNode->ChildNodes[i]->check_childNode != 1 && CurrentNode->ChildNodes[i]->check_visited != 1 && CurrentNode->ChildNodes[i]->check_obs != 1) {
                    Q.push_back(CurrentNode->ChildNodes[i]);
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
        
        for (int i = 0; i < Path.size(); i++) {
            result.push_back(std::make_pair(Path[i]->x, Path[i]->y));
        }
    }
    return result;
};

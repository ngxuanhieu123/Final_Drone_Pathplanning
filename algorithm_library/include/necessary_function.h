#ifndef NF
#define NF

#include<iostream>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include"map.h"
float update_G_cost(Node& A, Node& B);
float calculate_H_cost(Node& A, Node& Final);
float calculate_J_cost(Node& A);
bool validate_received_mess(const std::string &payload);
#endif
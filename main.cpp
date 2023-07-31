#include <iostream>
#include<cstdlib>
#include<cstring>
#include<mqtt/async_client.h>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

//include for main algorithm
#include <iostream>
#include <cmath>
#include <vector>
#include<limits>
#include <utility>
#include <iomanip>

#include"map.h"
#include"a_star.h"
#include"necessary_function.h"

const std::string SERVER_ADDRESS = "tcp://42.96.40.234:1883";
const std::string ClIENT_ID = "Path_Planning";
const std::string TOPIC_2 = "algo_return_ver_11";
const std::string TOPIC= "user_setup_ver_11";
const int QOS = 1;

const int TIMEOUT = 10000;

class callback : public virtual mqtt::callback {
private:
    mqtt::async_client& client_;
public:
    explicit callback(mqtt::async_client& client) : client_(client) {}

    void connection_lost(const std::string& cause) override {
        std::cout << "\nConnection lost" << std::endl;
        if (!cause.empty())
            std::cout << "\tCause: " << cause << std::endl;
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override {
        std::cout << "\nDelivery complete" << std::endl;
    }

    void message_arrived(mqtt::const_message_ptr msg) override {
        int error = 0;
        rapidjson::Value err_mess(rapidjson::kStringType);
        std::string payload = msg->to_string();
        std::cout << "Received message: " << payload << std::endl;
        std::vector<std::pair<int, int>> result;

        rapidjson::Document document;
        if (document.Parse(payload.c_str()).HasParseError()) {
            error = 1;      
        }
        else{
            document.Parse(payload.c_str());
            if(document.HasMember("pathID") == 0 || document.HasMember("start")== 0 || document.HasMember("final")==0){
                error = 2;
            }
            else{
                rapidjson::Value& id = document["pathID"];
                rapidjson::Value& s = document["start"];
                rapidjson::Value& f = document["final"];
                if(id.IsNumber() == 0 || s.IsArray() == 0 || s.Size() != 2 || f.IsArray() == 0 || f.Size() != 2){
                    error = 3;
                }
                else{
                    rapidjson::Value& pathID = id;
                    rapidjson::Value& sx = s[0];
                    rapidjson::Value& sy = s[1];
                    rapidjson::Value& fx = f[0];
                    rapidjson::Value& fy = f[1];
                    if(sx.IsNumber()==0 || sy.IsNumber()==0 || fx.IsNumber()==0 || fy.IsNumber()==0){
                        error = 4;
                    }
                    else{
                        error = 0;
                    }
                }
            }
        }
        switch(error){
            case 0:
                err_mess = "No error";
            break;
            case 1:
                err_mess = "Invalid format";
            break;
            case 2:
                err_mess = "Lack of arguments";
            break;
            case 3:
                err_mess = "Datatype of arguments are invalid";
            break;
            case 4:
                err_mess = "Value of arguments are invalid";
            break;
        }
        if(error == 0){
            Map mymap;
            mymap.setup_map();
            mymap.get_map();
            //mymap.FinalNode;
            //mymap.StartNode;
            //handle Final == Start
            result = a_star(mymap);
            //path_smoothing
        }
    }
};

int main(){
}
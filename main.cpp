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
        rapidjson::Value err_check(rapidjson::kFalseType);
        rapidjson::Value err_mess(rapidjson::kStringType);
        std::string payload = msg->to_string();
        std::cout << "Received message: " << payload << std::endl;
        std::vector<std::pair<int, int>> result;
        std::vector<std::pair<int, int>> new_result;
        std::string payload_2;
        
        rapidjson::Document path;
        path.SetObject();

        if(validate_received_mess(payload)){
            rapidjson::Document document;
            document.Parse(payload.c_str());
            rapidjson::Value& pathID = document["pathID"];
            double start_x = document["start"][0].GetDouble();
            double start_y = document["start"][1].GetDouble();
            double final_x = document["final"][0].GetDouble();
            double final_y = document["final"][1].GetDouble();
            Map mymap;
            mymap.get_map();
            mymap.get_Start(start_x, start_y);
            mymap.get_Final(final_x, final_y);

            rapidjson::Value array1(rapidjson::kArrayType);
            rapidjson::Value array2(rapidjson::kArrayType);
            result = a_star(mymap);
            new_result = mymap.path_smoothing(result);
            for(int i = 0; i < new_result.size(); i++){
                std::pair<double,double> temp = myWorld_to_realWorld(new_result[i].first, new_result[i].second, 0.0001,mymap.min_lat,mymap.min_lon);
                array1.PushBack(temp.first, path.GetAllocator());
                array2.PushBack(temp.second,path.GetAllocator());
            }
            err_check = false;
            path.AddMember("pathID", pathID, path.GetAllocator());
            path.AddMember("x_path", array1, path.GetAllocator());
            path.AddMember("y_path", array2, path.GetAllocator());
            path.AddMember("isError", err_check, path.GetAllocator());

            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            path.Accept(writer);

            payload_2 = buffer.GetString();
        }
        else{
            err_mess = "invalid input format";
            path.AddMember("error_mess", err_mess, path.GetAllocator());
            path.AddMember("isError", err_check, path.GetAllocator());
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            path.Accept(writer);

            payload_2 = buffer.GetString();
        }
        mqtt::message_ptr pub_msg = mqtt::make_message(TOPIC_2, payload_2);
        client_.publish(pub_msg);
    }
};

int main(){
    mqtt::async_client client(SERVER_ADDRESS, ClIENT_ID);

    callback cb(client);
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    try {
        client.connect(connOpts)->wait();
        client.subscribe(TOPIC,QOS);
        std::cout << "Subscribed to topic: " << TOPIC << std::endl;


        // Keep the subscriber running until interrupted
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        
        client.unsubscribe(TOPIC)->wait();
        client.disconnect()->wait();
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
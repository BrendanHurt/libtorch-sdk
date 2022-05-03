#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <limits>

//torch
#include <torch/torch.h>
#include <torch/script.h>
#include <dirent.h>
#include <ATen/ATen.h>

//grpc & proto
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "proto/sdk_transport.grpc.pb.h"
#include "proto/sdk_transport.pb.h"
#include "typing.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::Status;

//flower namespace elements
using namespace flower_sdk;

/**
 * -really just to test if the client can properly receive messages
 * -
 */

//class that the server uses to do the do
class FlowerServiceSDKImpl final : public FlowerServiceSDK::Service {
public:
    FlowerServiceSDKImpl() {
        server_network = std::make_shared<Network>();

        server_msg = new ServerMessage();
        reconnect_msg = new ServerMessage_Reconnect();
        parameters_msg = new ServerMessage_GetParameters();
        fit_msg = new ServerMessage_FitIns();
        evaluate_msg = new ServerMessage_EvaluateIns();
        properties_msg = new ServerMessage_PropertiesIns();
        evaluate_params = new Parameters();
        fit_params = new Parameters();
    }
    ~FlowerServiceSDKImpl() {}

    /**-----------------Join-----------------
     * 
    */
   Status Join(ServerContext* context,
            ServerReaderWriter<ServerMessage, ClientMessage>* stream) override {
        //figure out how to check for connection
        //once a connection is received:
        //  1. test get_parameters message
        //  2. test fit_ins messages
        //          send some dummy values & see if the model updates
        //  3. test evaluate_ins messages
        //          send some dummy values & see if the model updates
        //  4. test properties_ins messages
        //          send some dummy values & see if the model updates


        //probably just need to do some repurposing of the current methods
        //in here, so they just save the client model to a file and send
        //dummy messages to the client to see if it updates
    }

    /////////////////////////////////////////////////////////////
    //receive client messages

    /**-----------------client disconnect-----------------*/
    void get_disconnect_res(const ClientMessage_Disconnect& disconnect_msg) {
        //figure out what to do with that
    }

    /**-----------------client parameters-----------------*/
    void get_parameters_res(const ClientMessage_ParametersRes& parameters_res) {
        writer.open("logs/serverParams.txt", std::ios::out);
        writer << parameters_res.parameters().parameters(0) << std::endl;
        writer << parameters_res.parameters().parameters(1) << std::endl;
        writer << parameters_res.parameters().parameters(2) << std::endl;
        writer.close();
    }

    /**-----------------client fit-----------------*/
    void get_fit_res(const ClientMessage_FitRes& fit_res) {
        google::protobuf::Map<std::string, flower_sdk::Scalar>::const_iterator it;
        writer.open("logs/serverFit.txt", std::ios::out);

        writer << fit_res.parameters().parameters(0) << "\n\n\n";
        writer << fit_res.num_examples() << std::endl;

        for (it = fit_res.metrics().begin();
                it != fit_res.metrics().end(); it++) {
            writer << it->first << " " << it->second.string();
        }
        writer.close();

        //also save the params so they can be sent back
        fit_params->add_parameters(fit_res.parameters().parameters(0));
        fit_params->set_tensor_type("ndArray");

        //do the same thing for the evaluate ins, since client doesn't
        //send evaluate params to the server
        evaluate_params->add_parameters(fit_res.parameters().parameters(0));
        evaluate_params->set_tensor_type("ndArray");
    }

    /**-----------------client evaluate-----------------*/
    void get_evaluate_res(const ClientMessage_EvaluateRes evaluate_res) {
        google::protobuf::Map<std::string, flower_sdk::Scalar>::const_iterator it;
        writer.open("logs/serverEvaluate.txt", std::ios::out);

        writer << evaluate_res.num_examples() << std::endl;
        writer << evaluate_res.loss() << std::endl;

        for (it = evaluate_res.metrics().begin();
                it != evaluate_res.metrics().end(); it++) {
            writer << it->first << " " << it->second.string();
        }
        writer.close();
    }

    /**-----------------client properties-----------------*/
    void get_properties_res(const ClientMessage_PropertiesRes& properties_res) {
        google::protobuf::Map<std::string, flower_sdk::Scalar>::const_iterator it;
        writer.open("logs/serverProps.txt", std::ios::out);

        for (it = properties_res.properties().begin();
                it != properties_res.properties().end(); it++) {
            writer << it->first << " " << it->second.string();
        }
        writer.close();
    }

    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    //send server messages
    void send_reconnect_msg(ServerMessage& server_msg) {
        reconnect_msg->set_seconds(1000); //dummy value
    }

    //server doesn't seem to send parameters back?
    /*void send_parameters(ServerMessage& server_msg) {
        for (x : parameters_res.parameters()) {
            params->add_parameters(x);
        }
        params->set_tensor_type("ndArray");

        //put this into its own method?
        parameters_msg->set_allocated_parameters(params);
    }*/

    void send_fit_ins(ServerMessage& server_msg) {
        //setting fit_params currently in get_fit_res, probably change it later
        fit_params->set_tensor_type("ndArray");
        fit_msg->set_allocated_parameters(fit_params);

        bool flags[5] = {0,1,0,0,0};
        test_map(fit_msg->mutable_config(), flags);

        //now actually put the fit_ins into the server message
        server_msg.set_allocated_fit_ins(fit_msg);
    }

    void send_evaluate_ins(ServerMessage& server_msg) {
        evaluate_params->set_tensor_type("ndArray");
        evaluate_msg->set_allocated_parameters(evaluate_params);

        std::string first = "num_examples";
        std::string anotherFirst = "num_epochs";
        flower_sdk::Scalar second;
        second.set_sint64(1000);
        (*evaluate_msg->mutable_config())[first] = second;
        (*evaluate_msg->mutable_config())[anotherFirst] = second;


        //now actually put the fit_ins into the server message
        server_msg.set_allocated_evaluate_ins(evaluate_msg);
    }

    void send_properties_ins(ServerMessage& server_msg) {

        std::string first = "num_examples";
        std::string anotherFirst = "num_epochs";
        flower_sdk::Scalar second;
        second.set_sint64(1000);
        (*properties_msg->mutable_config())[first] = second;
        (*properties_msg->mutable_config())[anotherFirst] = second;

        //now actually put the fit_ins into the server message
        server_msg.set_allocated_properties_ins(properties_msg);
    }

private:

    const flower_sdk::Scalar to_flower(const typing::Scalar& from) const {
        flower_sdk::Scalar new_scalar;
        new_scalar.set_double_(from._double);
        new_scalar.set_sint64(from._int);
        new_scalar.set_bool_(from._bool);
        new_scalar.set_string(from._string);
        //new_scalar.set_bytes(from._bytes);
        return new_scalar;
    }

    //change this to not have to use typing::Scalar later?
    void copy_map(const std::map<std::string, typing::Scalar>& from,
                google::protobuf::Map<std::string, Scalar>* to) {
        if (to->size() != 0) {to->clear();}
        std::map<std::string, Scalar> temp;
        std::map<std::string, typing::Scalar>::const_iterator it;
        for (it = from.begin(); it != from.end(); it++) {
            temp.insert(
                std::pair<std::string, Scalar>(it->first, to_flower(it->second))
            );
        }
        to->insert(temp.begin(), temp.end());
    }


    /*-------remove later-------*/
    void writeToFile(std::string fileName) {
        std::fstream writeTo;

        writeTo.open(fileName, std::ios::out);
        writeTo << server_network->parameters();
        writeTo.close();
    }


    /*========================testing methods==============================*/
    void test_fit() {
        bool flags[5] = {0,0,0,0,0};
        for (int i = 0; i < 5; i++) {
            ServerMessage* server_msg = new ServerMessage;
            ServerMessage_FitIns* msg = new ServerMessage_FitIns();
            Parameters* params = new Parameters();

            params->add_parameters("some temp params");
            params->set_tensor_type("ndArray");
            msg->set_allocated_parameters(params);

            flags[i] = 1;
            test_map(msg->mutable_config(), flags);
            flags[i] = 0;

            //now actually put the fit_ins into the server message
            server_msg->set_allocated_fit_ins(msg);
            server_messages.push_back(*server_msg);
        }
    }

    void test_eval() {
        bool flags[5] = {0,0,0,0,0};
        for (int i = 0; i < 5; i++) {
            ServerMessage* server_msg = new ServerMessage;
            ServerMessage_EvaluateIns* msg = new ServerMessage_EvaluateIns();
            Parameters* params = new Parameters();

            params->add_parameters("some temp params");
            params->set_tensor_type("ndArray");
            msg->set_allocated_parameters(params);

            flags[i] = 1;
            test_map(msg->mutable_config(), flags);
            flags[i] = 0;

            //now actually put the fit_ins into the server message
            server_msg->set_allocated_evaluate_ins(msg);
            server_messages.push_back(*server_msg);
        }
    }

    void test_props() {
        bool flags[5] = {0,0,0,0,0};
        for (int i = 0; i < 5; i++) {
            ServerMessage* server_msg = new ServerMessage;
            ServerMessage_PropertiesIns* msg = new ServerMessage_PropertiesIns();

            flags[i] = 1;
            test_map(msg->mutable_config(), flags);
            flags[i] = 0;

            //now actually put the fit_ins into the server message
            server_msg->set_allocated_properties_ins(msg);
            server_messages.push_back(*server_msg);
        }
    }

    void test_map(google::protobuf::Map<std::string, flower_sdk::Scalar>* msg_map,
                        bool element_flags[]) {
        flower_sdk::Scalar second;
        //////////////////////////////////////////////
        //double
        if (element_flags[0] == true) {
            std::string s_first1 = "testing double 1:";
            std::string s_first2 = "testing double 2:";
            std::string s_first3 = "testing double 3:";
            std::string s_first4 = "testing double 4:";
            std::string s_first5 = "testing double 5:";

            second.set_double_(30.000001);
            (*msg_map)[s_first1] = second;
            second.set_double_(0.0);
            (*msg_map)[s_first2] = second;
            second.set_double_(std::numeric_limits<double>::min());
            (*msg_map)[s_first3] = second;
            second.set_double_(std::numeric_limits<double>::max());
            (*msg_map)[s_first4] = second;
            second.set_double_(56123588.268100); //see if the 0's get cut off?
            (*msg_map)[s_first5] = second;
        }
        //////////////////////////////////////////////
        //sint64
        if (element_flags[1] == true) {
            std::string s_first1 = "testing sint64 1:";
            std::string s_first2 = "testing sint64 2:";
            std::string s_first3 = "testing sint64 3:";
            std::string s_first4 = "testing sint64 4:";

            second.set_sint64(1000);
            (*msg_map)[s_first1] = second;
            second.set_sint64(0);
            (*msg_map)[s_first2] = second;
            //second.set_sint64(std::numeric_limits<long long int>::min());
            second.set_sint64(2);
            (*msg_map)[s_first3] = second;
            //second.set_sint64(std::numeric_limits<long long int>::max());
            second.set_sint64(__LONG_LONG_MAX__);
            (*msg_map)[s_first4] = second;
        }
        //////////////////////////////////////////////
        //bool
        if (element_flags[2] == true) {
            std::string s_first1 = "testing bool 1:";
            std::string s_first2 = "testing bool 1:";
            second.set_bool_(true);
            (*msg_map)[s_first1] = second;
            second.set_bool_(false);
            (*msg_map)[s_first2] = second;
        }
        //string
        if (element_flags[3] == true) {
            std::string s_first1 = "testing string 1";
            second.set_string("a string to put in here");
            (*msg_map)[s_first1] = second;
        }
        //bytes
        if (element_flags[4] == true) {
            std::string s_first1 = "testing string 1";
            second.set_bytes("some bytes of data");
            (*msg_map)[s_first1] = second;
        }
    }

    ////////////////////////////////////////////
    //attributes
    ServerMessage*                  server_msg;
    ServerMessage_Reconnect*        reconnect_msg;
    ServerMessage_GetParameters*    parameters_msg;
    ServerMessage_FitIns*           fit_msg;
    ServerMessage_EvaluateIns*      evaluate_msg;
    ServerMessage_PropertiesIns*    properties_msg;
    Parameters*                     evaluate_params;
    Parameters*                     fit_params;

    std::fstream writer, logger;
    std::vector<ClientMessage> client_messages;
    std::vector<ServerMessage> server_messages;
    std::shared_ptr<Network> server_network;
    std::mutex server_lock;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    FlowerServiceSDKImpl server_service;
    int num;

    /*--------------------figure out what these do later---------------------*/
    //grpc::EnableDefaultHealthCheckService(true);
    //grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;

    //make a lister address
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials(), &num);
    //set "serverService" to be the instance that communication is going through
    //in this case it's a synchronous service
    builder.RegisterService(&server_service);
    //now actually assemble the service
    std::unique_ptr<Server> server(builder.BuildAndStart());
    //server = builder.BuildAndStart();
    std::cout << "Server listening on: " << server_address << std::endl;
    std::cout << "AddListeningPort returns: " << num << std::endl;
    server->Wait();
}

int main (int argc, char* argv[]) {
    RunServer();

    return 0;
}

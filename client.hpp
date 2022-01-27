#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include "typing.h"     //c++ version of typing.py

//torch
#include <torch/torch.h>
#include <torch/script.h>
#include <dirent.h>
#include <ATen/ATen.h>

//grpc
#include <grpcpp/grpcpp.h>
#include "proto/sdk_transport.grpc.pb.h"
#include "proto/sdk_transport.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;

//flower namespace elements
using namespace flower_sdk;

class Client {
//private methods
    //sending messages to server
    void disconnect_to_proto(ClientMessage& client_msg);
    void parameters_to_proto(ClientMessage& client_msg);
    void fit_to_proto(ClientMessage& client_msg);
    void evaluate_to_proto(ClientMessage& client_msg);
    void properties_to_proto(ClientMessage& client_msg);

    //getting messages from server
    void reconnect_from_proto(const ServerMessage& server_msg);
    void fit_from_proto(const ServerMessage& server_msg);
    void evaluate_from_proto(const ServerMessage& server_msg);
    void properties_from_proto(const ServerMessage& server_msg);
    void server_ins_to_file();
    void write_scalar(std::fstream& writer, const flower_sdk::Scalar& scalar);

    static void model_thread(
        std::shared_ptr<ClientReaderWriter<ClientMessage, ServerMessage>>& stream,
        const std::vector<ClientMessage>& client_messages) {
        for (int i = 0; i < client_messages.size(); i++) { //foreach?
            stream->Write(client_messages[i]);
        }
        stream->WritesDone();
    }

    //doing the message sending
    grpc::Status Join();
    void serialize_client_model(std::vector<ClientMessage>& client_messages);

    //dealing with maps
    void copy_map(const std::map<std::string, typing::Scalar>& from,
                google::protobuf::Map<std::string, Scalar>* to);
    

public:
    Client(std::shared_ptr<Channel> channel);
    ~Client();
    
    //set messages
    void set_parameters(const std::vector<std::string>& layers);

    void set_fit(const torch::Tensor& fit,
            int num_examples, 
            const std::map<std::string, typing::Scalar>& metrics);

    void set_evaluate(float loss, int num_examples,
                const std::map<std::string, typing::Scalar>& metrics);

    void set_properties(const std::map<std::string, typing::Scalar>& props);

    //sending the model
    grpc::Status transport_model();
    const flower_sdk::Scalar to_flower(const typing::Scalar& from) const;

    ///////////////////////////////////////////////////////////////////////////
    //Test methods, remove later
    void test_eval();
    void test_params();
    void test_fit();
    void print_scalar(const Scalar& scalar);
    void write_to_file(std::string file_name, const std::stringstream& stream);

private: //attributes

    Reason disconnect_reason, reconnect_reason;

    int reconnect_time;
    //determine a method for checking which fields a user has saved
    
    //reduces the amount of allocating & deallocating these
    std::vector<ClientMessage>      client_messages;
    ClientMessage_Disconnect*       disconnect_res_msg;
    ClientMessage_ParametersRes*    parameters_res_msg;
    ClientMessage_FitRes*           fit_res_msg;
    ClientMessage_EvaluateRes*      evaluate_res_msg;
    ClientMessage_PropertiesRes*    properties_res_msg;

    //same idea for these?
    ServerMessage_Reconnect*        reconnect_msg;
    ServerMessage_FitIns*           fit_ins_msg;
    ServerMessage_EvaluateIns*      evaluate_ins_msg;
    ServerMessage_PropertiesIns*    properties_ins_msg;

    /*for reading parameters into parameters_res and fit_res, seems like
      add_paramters does a shallow copy, so there has to be 2 of them
    */
    flower_sdk::Parameters* parameters_msg;
    flower_sdk::Parameters* fit_parameters_msg;
    //flower_sdK::Parameters* get_fit_params;
    
    //keep these?
    std::string params_tensor_type = "parameters";
    std::string fit_tensor_type = "fit";
    std::string tensorType = "numpy.ndarray";
    
    std::unique_ptr<FlowerServiceSDK::Stub> stub_;

};

#endif
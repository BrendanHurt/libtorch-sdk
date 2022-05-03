#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include "typing.hpp"     //c++ version of typing.py

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
//  maybe make into individual ones like w/ grpc
using namespace flower_sdk;

class Client {
//private methods
    //sending messages to server
    ClientMessage* disconnect_to_proto(ClientMessage& client_msg);
    ClientMessage* parameters_to_proto(ClientMessage& client_msg);
    ClientMessage* fit_to_proto();
    ClientMessage* evaluate_to_proto(ClientMessage& client_msg);
    ClientMessage* properties_to_proto(ClientMessage& client_msg);

    //////////////////////////////////////////////////////////
    //getting messages from server
    void reconnect_from_proto(const ServerMessage& server_msg);

    //take in a const server message ref and module pointer?
    //  module pointer might allow for directly updating the model
    void fit_from_proto(const ServerMessage& server_msg);
    void evaluate_from_proto(const ServerMessage& server_msg);
    void properties_from_proto(const ServerMessage& server_msg);
    void server_ins_to_file();
    void write_scalar(std::fstream& writer, const flower_sdk::Scalar& scalar);
    //////////////////////////////////////////////////////////

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
    //dealing with maps
    void copy_map(const std::map<std::string, typing::Scalar>& from,
        google::protobuf::Map<std::string, Scalar>* to);
    
    

public:
    Client(std::shared_ptr<Channel> channel);
    ~Client();
    
    //figure out how to handle
    virtual void fit(int num_examples, const std::map<std::string, typing::Scalar>& metrics) = 0;
    virtual void evaluate(float loss, int num_examples, const std::map<std::string, typing::Scalar>& metrics) = 0;
    virtual void set_properties(const std::map<std::string, typing::Scalar>& props);
    virtual void save_parameters() = 0;
    virtual void load_parameters() = 0;

    //getters for the server info will go here
    /*
    void get_server_fit();
    void get_server_evaluate();
    void get_server_properties();
    */

    //sending the model
    grpc::Status transport_model();
    const flower_sdk::Scalar to_flower(const typing::Scalar& from) const;

private:
    torch::nn::Module *model; //question mark

    //fit
    std::vector<std::string> fit_params; //for fit_ins (necessary?)
    int fit_num_examples;
    google::protobuf::Map<std::string, Scalar> *fit_configs; //allocate in constructor?
    std::string tensorType = "numpy.ndarray";
    //evaluate
    std::vector<std::string> eval_params; //used for eval_ins
    float eval_loss;
    int eval_num_examples;
    google::protobuf::Map<std::string, Scalar> *eval_configs;
    //properties
    google::protobuf::Map<std::string, Scalar> *props_configs;
    
    std::unique_ptr<FlowerServiceSDK::Stub> stub_;

};

#endif

/**
 * Setting parameters from server:
 * method 1:
 * -figure out how to access submodules in a torch::nn::Module
 * -then you can use torch::load for each of the server's parameters
 * -don't really have to worry about tensor_type, not really being used
 * -idea: maybe make a method for loading into modules
 * -(might have to add checks to see if there's a different number of 
 *   modules than the the server has)
 * 
 * method 2 (seems a little extreme):
 * -back up the model into a file at the end of each cycle
 * -deallocate the model & reallocate the new one from the server
 */

/**
 * Setting maps from the server
 * -clear the map
 * -copy the server's map
 * 
 * things to change with Scalar
 * -make accessors & mutators
 * -remove/change to_flower
 * -look up how std::optional actually works
 */

/**
 * Methods for user to set the model
 * -make them have the same params as the current set_x methods
 * -have them set the attributes in client
 * -don't have to return anything, maybe verification? probably not
 * -change the current set_x methods to be to_proto methods (just rename)
 */

/**
 * things to do later on:
 * -add more error checking for server messages
 * -get the set_reconnect to work with wifi & power issues
 */
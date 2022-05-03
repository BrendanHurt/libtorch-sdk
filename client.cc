#include "client.hpp"


////////////////////////////////////////////////////////////////////////////////////
//new methods to fix things

/**
 * Process:
 * 1. server contacts client either by sending get_parameters or x_ins
 *      i) get_parameters: pack up the model parameters & send them back
 *      ii) x_ins: update the client model based on the instructions
 * 
 * 2. client runs the model for x number of epochs (based on properties)
 * 
 * 3. client sends back the fit, eval, and props after training(/evaling?)
 */

//check to see if stream can write derived messages
grpc::Status newJoin() {
    ClientContext context;
    ClientMessage client_msg;
    ServerMessage server_msg;
    grpc::Status status;
    std::shared_ptr<ClientReaderWriter<ClientMessage, ServerMessage>> stream(
        stub_->Join(&context)
    );

    //read messages from the server
    while(stream->Read(&server_msg)) {
        
        //send model to the server
        if (server_msg.has_get_parameters()) {
            //make a method that returns a client_msg w/ the params
            //Write that message here (then maybe wait till server response?)
        }

        //update the model based on server instructions
            //use the from_proto methods
        if (server_msg.has_fit_ins()) {
            //clear the fit params & set them to the server params
            //clear the metrics & set them to the server configs
            fit_from_proto(server_msg.fit_ins());
        }
        if (server_msg.has_evaluate_ins()) {
            //clear the eval params & set them to the server params
            //clear the metrics & set them to the server configs
            evaluate_from_proto(server_msg.evaluate_ins());
        }
        if (server_msg.has_properties_ins()) {
            properties_from_proto(server_msg.properties_ins());
        }

        //disconnect the client from the server
            //if a time's received, wait that long & reconnect
            //can worry about wifi & power ones later
        if (server_msg.has_reconnect()) {
            if (server_msg.reconnect()->seconds() > 0) {
                ClientMessage *disc_msg = new ClientMessage();
                ClientMessage_Disconnect *disc = new ClientMessage_Disconnect();

                disc->set_disconnect(1);
                disc_msg->set_allocated_disconnect(disc);
                stream->Write(disc_msg);

                sleep(server_msg.reconnect()->seconds);
            } else {
                return status; //maybe do a break?
            }
        }
    }

    //run the model

    //serialize & send the model
    //  -call the to_proto methods & push the retunrs onto client_messages
    //  -write all of the client messages

    return status;
}

//kinda the equivalent of the dummy server's "runServer" method
void start_client() {
    //initialized the client
    //call connect to the server
    //call join?
}



//(consider this in a bit)
//change from having each msg_res be an attribute of client?
// pros:
//  -more memory efficient (messages are only created when they're needed)
//cons:
//  -more allocating & deallocating of messages (is this a con?)
//  -might be better to just clear them out & reassign the values

////////////////////////////////////////////////////////////////////////////////////


//==========================================================================
//private methods

//----------------------------------------------
//prive set methods
void set_disconnect() {}

//----------------------------------------------
//to_proto methods
void Client::disconnect_to_proto(ClientMessage& client_msg) {
    client_msg.set_allocated_disconnect(disconnect_res_msg);
}
void Client::parameters_to_proto(ClientMessage& client_msg) {
    client_msg.set_allocated_parameters_res(parameters_res_msg);
}
void Client::fit_to_proto(ClientMessage& client_msg) {
    ClientMessage *client_msg = new ClientMessage();
    ClientMessage_FitRes *fit = new ClientMessage_FitRes();
    ClientMessage_ParametersRes *params_msg = new ClientMessage_ParametersRes();

    for (auto x : fit_params) {
        params_msg->add_parameters(x);
    }

    fit->set_allocated_parameters(params_msg);
    fit->set_num_examples(fit_num_examples);
    fit->mutable_metrics = fit_configs;
    client_msg.set_allocated_fit(fit);
    return client_msg;
}
void Client::evaluate_to_proto(ClientMessage& client_msg) {
    ClientMessage* client_msg = new ClientMessage();
    ClientMessage_EvaluateRes eval = new ClientMessage_EvaluateRes();

    eval->set_num_examples(num_examples);
    eval->set_loss(loss);
    eval->mutable_metrics = eval_configs;
    client_msg->set_allocated_evaluate_res(eval);
    return client_msg;
}
void Client::properties_to_proto(ClientMessage& client_msg) {
    client_msg.set_allocated_properties_res(properties_res_msg);
}


//////////////////////////////////////////
//functions for user to load model received from the server
//don't need a reconnect_from_proto, can be handled in an if-else
void Client::fit_from_proto(const ServerMessage_FitIns& server_fit) {

    if (!fit_params.empty()) {fit_params.clear();}
    if (!fit_configs.empty()) {fit_configs.clear();}

    //get the parameters from the fit_msg
    for (auto x : server_fit->parameters->parameters()) {
        fit_params.push_back(x);
    }
    //get the config from the fit_msg
    //  probably have to change how copy_map works
    copy_map(server_fit->mutable_configs, fit_configs);
}
void Client::evaluate_from_proto(const ServerMessage_EvaluateIns& server_eval) {
    if (!fit_params.empty()) {fit_params.clear();}
    if (!fit_configs.empty()) {fit_configs.clear();}

    //get the parameters from the fit_msg
    for (auto x : server_eval->parameters->parameters()) {
        eval_params.push_back(x);
    }
    //get the config from the fit_msg
    //  probably have to change how copy_map works
    copy_map(server_eval->mutable_configs, eval_configs);
}
void Client::properties_from_proto(const ServerMessage_PropertiesIns& server_props) {
    if (!fit_configs.empty()) {fit_configs.clear();}
    copy_map(server_props->mutable_configs, props_configs);
}

//probably just gunna get rid of these two
void Client::server_ins_to_file() {
    //starting with fit
    std::fstream writer;
    writer.open("serverIns.txt", std::ios::out);
    //--------------------------------------
    //modularize fit section later

    for (int i = 0; i < fit_ins_msg->parameters().parameters_size(); i++) {
        writer << fit_ins_msg->parameters().parameters(i) << "\n\n";
    }

    google::protobuf::Map<std::string, flower_sdk::Scalar>::const_iterator it;
    for (it = fit_ins_msg->config().cbegin(); it != fit_ins_msg->config().cend(); it++) {
        writer << "Fit:\n" << it->first;
        write_scalar(writer, it->second); //probably a better way to do this
    }
    writer << "\n\n";
    //--------------------------------------

    //--------------------------------------
    //modularize properties section later
    //google::protobuf::Map<std::string, flower_sdk::Scalar>::const_iterator it;
    for (it = properties_ins_msg->config().cbegin();
        it != properties_ins_msg->config().cend();
        it++) {
        writer << "Properties:\n" << it->first;
        write_scalar(writer, it->second); //probably a better way to do this
    }
    writer << "\n\n";
    //--------------------------------------

    //--------------------------------------
    //modularize evaluate section later

    for (int i = 0; i < evaluate_ins_msg->parameters().parameters_size(); i++) {
        writer << evaluate_ins_msg->parameters().parameters(i) << "\n\n";
    }

    //google::protobuf::Map<std::string, flower_sdk::Scalar>::const_iterator it;
    for (it = evaluate_ins_msg->config().cbegin();
        it != evaluate_ins_msg->config().cend();
        it++) {
        writer << "Evaluate:\n" << it->first;
        write_scalar(writer, it->second); //probably a better way to do this
    }
    writer << "\n\n";
    //--------------------------------------

    writer.close();
}
void Client::write_scalar(std::fstream& writer, const flower_sdk::Scalar& scalar) {
    if (scalar.has_double_()) {
        writer << " double; " << scalar.double_() << std::endl;
    } else if (scalar.has_sint64()) {
        int converter = scalar.sint64();
        writer << " sint64: " << converter << std::endl;
    } else if (scalar.has_bool_()) {
        writer << " bool: " << scalar.bool_() << std::endl;
    } else if (scalar.has_string()) {
        writer << " string: " << scalar.string() << std::endl;
    } else if (scalar.has_bytes()) { //maybe write to a different file?
        writer << " bytes: " << scalar.bytes() << std::endl;
    } else {
        writer << "Scalar is empty\n";
    }
}


grpc::Status Client::Join() {
    ClientContext context;
    ClientMessage client_msg;
    ServerMessage server_msg;
    grpc::Status status;

    serialize_client_model(client_messages);

    std::shared_ptr<ClientReaderWriter<ClientMessage, ServerMessage>> stream(
        stub_->Join(&context)
    );
    std::thread model_writer(model_thread, std::ref(stream), std::ref(client_messages));

    //modularize this?
    while(stream->Read(&server_msg)) {
        //add deserializing here later
        std::cout << "got the server message\n";

        //handle the server messages here
        //probably modularize later
        if (server_msg.has_fit_ins()) {
            std::cout << "has fit ins\n";
            fit_from_proto(server_msg);
        }
        if (server_msg.has_properties_ins()) {
            properties_from_proto(server_msg);
        }
        if (server_msg.has_evaluate_ins()) {
            evaluate_from_proto(server_msg);
        }
    }
    server_ins_to_file();

    model_writer.join();
    status = stream->Finish();
    !status.ok() ? std::cout << "Join rpc failed\n" : std::cout << "Join succeeded\n";
    std::cout << "exiting streaming method\n";
    return status;
}
void Client::copy_map(const std::map<std::string, typing::Scalar>& from,
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


//========================================================================
//public methods
Client::Client(std::shared_ptr<Channel> channel)
    : stub_(FlowerServiceSDK::NewStub(channel)) {}
Client::~Client() {}

/*----------making them pure virtual, remove later----------------
void Client::set_client_fit(const torch::nn::Module& fit,
            int num_examples, 
            const std::map<std::string, typing::Scalar>& metrics) {
    
    if (!fit_configs->empty()) {fit_configs->clear();}
    if (!fit_paramters.empty()) {fit_parameters.clear();}

    fit_parameters = serialize_parameters(fit); //probably not gunna work
    fit_num_examples = num_examples;
    copy_map(metrics, fit_configs);
}

void Client::set_client_evaluate(float loss,
                int num_examples,
                const std::map<std::string, typing::Scalar>& metrics) {
                    
    if (!eval_configs.empty()) {eval_configs.clear();}

    eval_loss = loss;
    eval_num_examples = num_examples;
    copy_map(metrics, eval_configs);
}
*/

//fix along with typing::Scalar
void Client::set_client_properties(const std::map<std::string, typing::Scalar>& props) {
    if (!props_configs.empty()) {props_configs.clear();}
    copy_map(props, properties_res_msg->mutable_properties());
}


//probably going to remove later
grpc::Status Client::transport_model() {
    std::cout << "in transport_model\n";
    return Join();
}

//change up after figuring out how std::optional works
const flower_sdk::Scalar Client::to_flower(const typing::Scalar& from) const {
    flower_sdk::Scalar new_scalar;
    new_scalar.set_double_(from._double);
    new_scalar.set_sint64(from._int);
    new_scalar.set_bool_(from._bool);
    new_scalar.set_string(from._string);
    new_scalar.set_bytes(from._bytes);
    return new_scalar;
}

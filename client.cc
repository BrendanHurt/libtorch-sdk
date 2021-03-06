#include "client.hpp"

//==========================================================================
//private methods

//remove later
/*void map_from_proto(const google::protobuf::Map<std::string, flower_sdk::Scalar>* from,
                std::map<std::string, typing::Scalar>& to) {
    std::map<std::string, typing::Scalar> temp;
    google::protobuf::Map<std::string, flower_sdk::Scalar>::const_iterator it;
    for (it = from->cbegin(); it != from->cend(); it++) {
        temp.insert(
            std::pair<std::string, typing::Scalar>(it->first, from_flower(it->second))
        );
    }
    to.insert(temp.begin(), temp.end());
}*/

//////////////////////////////////////////
//methods for user to send model to server

void Client::disconnect_to_proto(ClientMessage& client_msg) {
    disconnect_res_msg->set_reason(disconnect_reason);
    client_msg.set_allocated_disconnect(disconnect_res_msg);
}

void Client::parameters_to_proto(ClientMessage& client_msg) {
    client_msg.set_allocated_parameters_res(parameters_res_msg);
}

void Client::fit_to_proto(ClientMessage& client_msg) {
    client_msg.set_allocated_fit_res(fit_res_msg);
}

void Client::evaluate_to_proto(ClientMessage& client_msg) {
    client_msg.set_allocated_evaluate_res(evaluate_res_msg);
}

void Client::properties_to_proto(ClientMessage& client_msg) {
    client_msg.set_allocated_properties_res(properties_res_msg);
}


//////////////////////////////////////////
//functions for user to load model received from the server

void Client::reconnect_from_proto(const ServerMessage& server_msg) {
    //reconnect_time = server_msg.reconnect.seconds;
}

void Client::fit_from_proto(const ServerMessage& server_msg) {
    //copy over the fit tensor (should only be one?)
    for (int i = 0; i < server_msg.fit_ins().parameters().parameters_size(); i++) {
        fit_ins_msg->mutable_parameters()->add_parameters(
            server_msg.fit_ins().parameters().parameters(i)
        );
    }

    //copy the config from server_msg to fit_ins_msg
    fit_ins_msg->mutable_config()->insert(
        server_msg.fit_ins().config().begin(), server_msg.fit_ins().config().end()
    );
}

void Client::evaluate_from_proto(const ServerMessage& server_msg) {
    //copy over the fit tensor (should only be one?)
    for (int i = 0; i < server_msg.evaluate_ins().parameters().parameters_size(); i++) {
        evaluate_ins_msg->mutable_parameters()->add_parameters(
            server_msg.evaluate_ins().parameters().parameters(i)
        );
    }

    //copy the config from server_msg to evaluate_ins_msg
    evaluate_ins_msg->mutable_config()->insert(
        server_msg.evaluate_ins().config().begin(),
        server_msg.evaluate_ins().config().end()
    );
}

void Client::properties_from_proto(const ServerMessage& server_msg) {
    properties_ins_msg->mutable_config()->insert(
        server_msg.properties_ins().config().begin(),
        server_msg.properties_ins().config().end()
    );
}

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

    //read model from a server message
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

//serialize model
//add checking to only add messages that have content in 'em
void Client::serialize_client_model(std::vector<ClientMessage>& client_messages) {
    std::cout << "in serialize model\n";
    ClientMessage disconnect_msg, params_msg,
        fit_msg, evaluate_msg, properties_msg;

    //add an if here later
    disconnect_to_proto(disconnect_msg);

    if (parameters_res_msg->has_parameters()) {
        std::cout << "adding parameters messsage\n";
        parameters_to_proto(params_msg);
        client_messages.push_back(params_msg);
    } else {
        std::cout << "parameters empty\n";
    }
    if (fit_res_msg->num_examples() != 0) { //better if statement?
        std::cout << "adding fit message\n";
        fit_to_proto(fit_msg);
        client_messages.push_back(fit_msg);
    } else {
        std::cout << "fit empty\n";
    }
    if (evaluate_res_msg->loss() != 0) { //better if statement?
        std::cout << "adding evaluate message\n";
        evaluate_to_proto(evaluate_msg);
        client_messages.push_back(evaluate_msg);
    } else {
        std::cout << "evaluate empty\n";
    }
    if (properties_res_msg->properties_size() != 0) {
        std::cout << "adding properties message\n";
        properties_to_proto(properties_msg);
        client_messages.push_back(properties_msg);
    } else {
        std::cout << "properties empty\n";
    }
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
    : stub_(FlowerServiceSDK::NewStub(channel)) {
    //disconnect_reason = 0;

    //client_msg = new ClientMessage();
    disconnect_res_msg = new ClientMessage_Disconnect();
    parameters_res_msg = new ClientMessage_ParametersRes();
    fit_res_msg = new ClientMessage_FitRes();
    evaluate_res_msg = new ClientMessage_EvaluateRes();
    properties_res_msg = new ClientMessage_PropertiesRes();
    parameters_msg = new Parameters();
    fit_parameters_msg = new Parameters();

    //server messages
    fit_ins_msg = new ServerMessage_FitIns();
    properties_ins_msg = new ServerMessage_PropertiesIns();
    evaluate_ins_msg = new ServerMessage_EvaluateIns();
    reconnect_msg = new ServerMessage_Reconnect();
}
Client::~Client() {}

void Client::set_parameters(const std::vector<std::string>& layers) {
    if (parameters_res_msg->has_parameters()) {parameters_res_msg->clear_parameters();}
    if (parameters_msg->parameters_size() != 0) {parameters_msg->clear_parameters();}

    for (size_t i = 0; i < layers.size(); i++) {
        parameters_msg->add_parameters(layers[i]);
    }
    parameters_msg->set_tensor_type(params_tensor_type);
    parameters_res_msg->set_allocated_parameters(parameters_msg);
}

void Client::set_fit(const torch::Tensor& fit,
            int num_examples, 
            const std::map<std::string, typing::Scalar>& metrics) {
    std::stringstream buffer;

    //clear messages if they've already been set
    if (fit_res_msg->has_parameters()) {fit_res_msg->clear_parameters();}
    if (fit_res_msg->metrics_size() != 0) {fit_res_msg->clear_metrics();}
    if (fit_parameters_msg->parameters_size() != 0) {fit_parameters_msg->clear_parameters();}

    torch::save(fit, buffer);
    fit_parameters_msg->add_parameters(buffer.str());
    fit_parameters_msg->set_tensor_type(fit_tensor_type);
    fit_res_msg->set_allocated_parameters(fit_parameters_msg);
    fit_res_msg->set_num_examples(num_examples);
    
    //metrics
    copy_map(metrics, fit_res_msg->mutable_metrics());
}

void Client::set_evaluate(float loss,
                int num_examples,
                const std::map<std::string, typing::Scalar>& metrics) {
    if (evaluate_res_msg->metrics_size() != 0) {evaluate_res_msg->clear_metrics();}
    evaluate_res_msg->set_loss(loss);
    evaluate_res_msg->set_num_examples(num_examples);
    copy_map(metrics, evaluate_res_msg->mutable_metrics());
}

void Client::set_properties(const std::map<std::string, typing::Scalar>& props) {
    /*if (properties_res_msg->properties_size() != 0) {
        properties_res_msg->clear_properties();
    }*/
    copy_map(props, properties_res_msg->mutable_properties());
}

grpc::Status Client::transport_model() {
    std::cout << "in transport_model\n";
    return Join();
}

const flower_sdk::Scalar Client::to_flower(const typing::Scalar& from) const {
    flower_sdk::Scalar new_scalar;
    new_scalar.set_double_(from._double);
    new_scalar.set_sint64(from._int);
    new_scalar.set_bool_(from._bool);
    new_scalar.set_string(from._string);
    new_scalar.set_bytes(from._bytes);
    return new_scalar;
}

/*const typing::Scalar from_flower(const flower_sdk::Scalar& from) const {
    typing::Scalar to;
    if (from.has_double_()) {
        to._double = from.double_();
    }
    if (from.has_sint64()) {
        to._int = from.sint64();
    }
    if (from.has_bool_()) {
        to._bool = from.bool_();
    }
    if (from.has_string()) {
        to._string = from.string();
    }
    if (from.has_bytes()) {
        to._bytes = from.bytes();
    }
    return to;
}*/


///////////////////////////////////////////////////////////////////////////
//Test methods, remove later
void Client::test_eval() {
    std::cout << "Client loss: " << evaluate_res_msg->loss() << std::endl;
    std::cout << "Client num_examples: " << evaluate_res_msg->num_examples() 
        << std::endl;
}

void Client::test_params() {
    std::fstream writer;
    writer.open("clientParams.txt", std::ios::out);
    for (int i = 0; i < parameters_res_msg->parameters().parameters_size(); i++) {
        writer << parameters_res_msg->parameters().parameters(i);
        writer << "\n\n";
    }
    writer.close();
}

void Client::test_fit() {
    std::fstream writer;
    writer.open("clientFit.txt", std::ios::out);
    writer << fit_res_msg->parameters().parameters(0);
    writer.close();

    google::protobuf::Map<std::string, Scalar>::const_iterator it;
    for (it = fit_res_msg->metrics().begin(); 
            it != fit_res_msg->metrics().end(); 
            it++) {
        std::cout << it->first << " ";
        print_scalar(it->second);
    }
}

void Client::print_scalar(const Scalar& scaler) {
    std::cout << scaler.double_() << " ";
    std::cout << scaler.sint64() << " ";
    std::cout << scaler.bool_() << " ";
    std::cout << scaler.string() << " ";
    std::cout << scaler.bytes() << std::endl;
}

void Client::write_to_file(std::string file_name, const std::stringstream& stream) {
    std::fstream writer;

    writer.open(file_name, std::ios::out);
    writer << stream.str();
    writer.close();
}

///////////////////////////////////////////////////////////////////////////

/*
Client (ModelPasser or some other name?):
    Process:
        1. User passes details of their model to the client (or some structure)
        2. Client serializes these and sends them to the server
        3. Client receives details from the server and deserializes these
        4. Client then returns these to the user

    Attributes:
        Class/Struct: Parameters, Evaluate, Properties, Fit
        int: disconnect_reason, reconnect_time

        Shared pointer for Network(remove later?)

        Unique pointer for stub_

    Methods:
        -Deserialize server messages
        -put user's model into the client message (handles serialization)
            -separate methods for: parameters, fit, eval, properties, disconnect
        -get model returned from the server to the user
            -separate methods for: parameters, fit, eval, properties, reconnect

        add a method for connecting to the server?
*/
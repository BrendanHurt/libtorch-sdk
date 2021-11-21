#include "proto/sdk_transport.pb.h"
#include "proto/sdk_transport.grpc.pb.h"
//make a client.h?

using namespace flower_sdk; //for the sake of my sanity

std::tuple<ClientMessage, int, bool> handle (
    Client client, ServerMessage server_msg) {
    
    //if the client disconnected from the server?
    if (server_msg.HasField("reconnect")) {
        ClientMessage disconnect_msg;
        int sleep_duration;
        disconnect_msg, sleep_duration = _reconnect(server_msg.reconnect);
        return std::tuple<ClientMessage, int, bool>(
            disconnect_msg, sleep_duration, false
        );
    }
    //get the server message's parameters
    if (server_msg.HasField("get_parameters")) {
        return std::tuple<ClientMessage, int, bool>(
            _get_parameters(client), 0, true
        );
    }
    //get the server message's fit instructions
    if (server_msg.HasField("fit_ins")) {
        return _fit(client, server_msg.fit_ins), 0, true;
    }
    //get the server message's evaluate instructions
    if (server_msg.HasField("evaluate_ins")) {
        return _evaluate(client, server_msg.evaluate_ins), 0, true;
    }
    //get the server message's properties instructions
    if (server_msg.HasField("properties_ins")) {
        return _get_properties(client, server_msg.evaluate_ins), 0, true;
    }

    //make an exception for unkown messages & put it here
}

//checks if the client had to reconnect to the server?
std::tuple<ClientMessage, int> _reconnect(
    const ServerMessage.Reconnect& reconnect_msg) {
    int reason = Reason.ACK;
    int sleep_duration = 0;

    if (reconnect_msg.seconds != 0) {
        reason = Reason.RECONNECT;
        sleep_duration = reconnect_msg.sleep_duration;
    }
    ClientMessage disconnect_msg;
    disconnect_msg.Disconnect.Reason = reason;
    return disconnect_msg, sleep_duration; //put it into a tuple?
}

//puts the parameters into a client message so they can be sent to the server?
ClientMessage _get_parameters(const Client& client) {
    ClientMessage parameters_res_proto;
    parameters_res_proto.ParametersRes = client.get_parameters();
    return parameters_res_proto;
}

//puts the fit into a client message so they can be sent to the server?
ClientMessage _fit(const Client& client, const ServerMessage.FitIns& fit_msg) {
    ClientMessage fit_res;
    //deserialize from proto
    fit_res.FitRes = fit_msg;
    //put it into fit_res
    //return fit_res
}

//puts the evaluate into a client message so they can be sent to the server?
ClientMessage _evaluate(Client client) {
    //deserialize from proto
    //put it into evaluate_res
    //return evaluate_res
}

//puts the properties into a client message so they can be sent to the server?
ClientMessage _get_properties(Client client) {
    //deserialize from proto
    //put it into properties_res
    //return properties_res
}


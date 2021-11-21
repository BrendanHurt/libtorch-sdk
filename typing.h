//create kinda a mixture of serde and typing?
#ifndef __TYPING_H__
#define __TYPING_H__

#include <sstream>
#include <string>
#include <map>
#include "proto/sdk_transport.pb.h"
//=======================================================================
// Types

namespace typing {
//struct Weights {};

struct Scalar {
    //come up with better variable names
    double _double;
    bool _bool;
    std::string _bytes;
    int _int;
    std::string _string;

    //user can pass in which type?
    //  pass in a char/enum & use a switch case?
    const flower_sdk::Scalar to_flower() const {
        flower_sdk::Scalar new_scalar;
        new_scalar.set_double_(this->_double);
        new_scalar.set_sint64(this->_int);
        new_scalar.set_bool_(this->_bool);
        new_scalar.set_string(this->_string);
        new_scalar.set_bytes(this->_bytes);
        return new_scalar;
    }
};

struct Metrics {
    std::map<std::string, Scalar> metrics;
};

struct Config {
    std::map<std::string, Scalar> configs;
};

struct Properties {
    std::map<std::string, Scalar> properties;
};

//=======================================================================
// Classes
// make them into structs instead?
struct Parameters {
    std::stringstream parameters;
    std::string tensorType;
};

//Response when parameters are requested
struct ParametersRes {
    Parameters parameters;
};

//Instructions from server for fit
struct FitIns {
    Parameters parameters;
    Config config;
};

//Client's response to fit request
struct FitRes {
    Parameters parameters;
    int num_examples;
    //add deprecated variables?
    Metrics metrics;
};

//Instructions from server for evaluating
struct EvaluateIns {
    Parameters parameters;
    Config config;
};

//Client's response to evaluate request
struct EvaluateRes {
    float loss;
    int num_examples;
    //add deprecated variables?
    Metrics metrics;
};

//Instructions from server for the properties
struct PropertiesIns {
    Config config;
};

//Client's response to properties request
struct PropertiesRes {
    Properties properties;
};

//Client's reconnect message to server
struct Reconnect {
    int seconds;
};

//Client's disconnect message
struct Disconnect {
    std::string reason;
};

}

#endif
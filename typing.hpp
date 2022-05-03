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

//credit the person with the idea for using std::optional
struct Scalar {
    //come up with better variable names
    std::optional<double>           _double;
    std::optional<bool>             _bool;
    std::optional<std::string>      _bytes;
    std::optional<long long int>    _int;
    std::optional<std::string>      _string;

    //convert this scalar to one that will work with protobuf
    flower_sdk::Scalar* to_flower (const typing::Scalar& scalar) {
        flower_sdk::Scalar newScalar = new flower_sdk::Scalar();

        if (scalar._double) {
            newScalar.set_double_(value);
        } else if (scalar._int) {
            newScalar.set_sint64(value);
        } else if (scalar._bool) {
            newScalar.set_bool_(value);
        } else if (scalar._string) {
            newScalar.set_string(value);
        } else if (scalar._bytes) {
            newScalar.set_bytes(value);
        } else {
            return nullptr;
        }
        
        return newScalar;
    }
};

}

#endif
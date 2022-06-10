//
// Created by andrew on 2022/6/10.
//

#ifndef DLMS_JSON_PROXY_H
#define DLMS_JSON_PROXY_H
#include <utility>

#include "json.hpp"

using json = nlohmann::json;

class JsonProxy {
public:
    explicit JsonProxy(json  json) : jsoObject(std::move(json)) {}
    explicit JsonProxy(json& json) : jsoObject(json) {}
    explicit JsonProxy(json&& json) : jsoObject(json) {}

    JsonProxy(std::string& path, std::string& filename);

    explicit JsonProxy(std::string& filename);




    json& GetJsonObj() {
        return jsoObject;
    }




private:
    json jsoObject;
};


#endif //DLMS_JSON_PROXY_H

//
// Created by andrew on 2022/6/10.
//

#ifndef DLMS_JSON_PROXY_H
#define DLMS_JSON_PROXY_H

#include <utility>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include "json.hpp"
#include "status.h"

using json = nlohmann::json;

class JsonProxy {
public:
    JsonProxy() = default;

    explicit JsonProxy(json json) : jsonObj(std::move(json)) {}

    explicit JsonProxy(json &json) : jsonObj(json) {}

    explicit JsonProxy(json &&json) : jsonObj(json) {}

    JsonProxy(std::string &path, std::string &filename) {
        std::string file = path + "/" + filename;
        std::ifstream f(file.c_str());
        jsonObj = json::parse(f);
    }

    explicit JsonProxy(std::string &filename) {}

    json &GetJsonObj() {
        return jsonObj;
    }

private:
    json jsonObj;
};


#endif //DLMS_JSON_PROXY_H

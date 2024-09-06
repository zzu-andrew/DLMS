/**
 * @file JsonProxy.h
 * @brief Definition of the JsonProxy class.
 *
 * This file contains the declaration of the JsonProxy class, which provides 
 * various constructors for handling JSON objects and files.
 */

#ifndef DLMS_JSON_PROXY_H
#define DLMS_JSON_PROXY_H

#include <utility>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include "json.hpp"
#include "status.h"

using json = nlohmann::json;
/**
 * @brief A class to handle JSON objects.
 *
 * This class provides constructors to initialize a JSON object from various 
 * sources such as another JSON object, a JSON file, or a string containing 
 * the file path and filename.
 */
class JsonProxy {
public:
    /**
     * @brief Default constructor.
     *
     * This constructor initializes a JsonProxy object with an empty JSON object.
     */
    JsonProxy() = default;

    /**
     * @brief Constructor to initialize with a JSON object.
     *
     * This constructor initializes a JsonProxy object with the given JSON object, 
     * moving it into the internal JSON object.
     *
     * @param json The JSON object to initialize with.
     */
    explicit JsonProxy(json json) : jsonObj(std::move(json)) {}

    /**
     * @brief Constructor to initialize with a reference to a JSON object.
     *
     * This constructor initializes a JsonProxy object with a reference to the 
     * provided JSON object.
     *
     * @param json The JSON object reference to initialize with.
     */
    explicit JsonProxy(json &json) : jsonObj(json) {}

    /**
     * @brief Constructor to initialize with an r-value reference to a JSON object.
     *
     * This constructor initializes a JsonProxy object with the given JSON object, 
     * moving it into the internal JSON object.
     *
     * @param json The JSON object r-value reference to initialize with.
     */
    explicit JsonProxy(json &&json) : jsonObj(json) {}

    /**
     * @brief Constructor to initialize with a file path and filename.
     *
     * This constructor initializes a JsonProxy object by reading the specified 
     * JSON file and parsing it into the internal JSON object.
     *
     * @param path The file path where the JSON file is located.
     * @param filename The name of the JSON file.
     */
    JsonProxy(std::string &path, std::string &filename) {
        std::string file = path + "/" + filename;
        std::ifstream f(file.c_str());
        jsonObj = json::parse(f);
    }

    /**
     * @brief Constructor to initialize with a filename.
     *
     * This constructor initializes a JsonProxy object by reading the specified 
     * JSON file and parsing it into the internal JSON object. (Implementation TODO)
     *
     * @param filename The name of the JSON file.
     */
    explicit JsonProxy(std::string &filename) {
        // Implementation logic for this constructor could be added here
    }

    /**
     * @brief Get the internal JSON object.
     *
     * This method returns a reference to the internal JSON object.
     *
     * @return A reference to the internal JSON object.
     */
    json &GetJsonObj() {
        return jsonObj;
    }

private:
    json jsonObj; ///< The internal JSON object managed by this proxy.
};


#endif //DLMS_JSON_PROXY_H

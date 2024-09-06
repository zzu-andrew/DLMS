/**
 * @file IContext.h
 * @brief Interface for context operations in a system.
 *
 * This file contains the IContext interface which provides
 * methods to initialize, start, stop, reset processes, and
 * manage plugins.
 */

#ifndef DLMS_DLMS_BASH_H
#define DLMS_DLMS_BASH_H
#include <iostream>
#include <functional>
#include "status.h"
#include "thread_manager.h"


class Plugin;
/**
 * @brief Interface for context operations.
 *
 * This class defines an interface for managing the lifecycle of 
 * a process and handling plugins. 
 */
class IContext {
public:


public:
    /// Destructor
    virtual ~IContext() = default;

    /**
     * @brief Initializes the main process.
     *
     * This method is responsible for setting up the initial state
     * of the main process.
     *
     * @return 0 if success, other values indicate failure.
     */
    virtual Status Init() = 0;

    /**
     * @brief Starts the main process.
     *
     * This method will start the execution of the main process.
     *
     * @return 0 if success, other values indicate failure.
     */
    virtual Status Start() = 0;

    /**
     * @brief Stops the main process.
     *
     * This method is called to stop the execution of the main process.
     *
     * @return 0 if success, other values indicate failure.
     */
    virtual Status Stop() = 0;

    /**
     * @brief Resets the main process.
     *
     * This method will reset the main process state.
     *
     * @return 0 if success, other values indicate failure.
     */
    virtual Status Reset() = 0;

    /**
     * @brief Gets a plugin object.
     *
     * This method retrieves a plugin instance based on the plugin name
     * and type provided.
     *
     * @param[in] pluginName The name of the plugin.
     * @param[in] type The type of the plugin.
     * @return A pointer to the plugin object if found, nullptr otherwise.
     */
    virtual Plugin *GetPlugin(std::string &pluginName, std::string &type) = 0;

    /**
     * @brief Dispatches a work function to a thread.
     *
     * This method assigns a work function to be executed by a thread.
     *
     * @param[in] workFunction The function to be executed by the thread.
     * @return 0 if success, other values indicate failure.
     */
    virtual Status Dispatch(Func workFunction) = 0;
};


class IConfig {
public:
    virtual ~IConfig() = default;





};












#endif //DLMS_DLMS_BASH_H

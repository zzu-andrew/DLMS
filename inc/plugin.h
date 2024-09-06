/**
 * @file Plugin.h
 * @brief Definitions and interfaces for Plugin and related types.
 *
 * This file contains the enum definitions and class declarations
 * for Plugin and related components. The Plugin class provides
 * an interface for initializing, starting, stopping, resetting, 
 * and communicating with plugins.
 */

#ifndef DLMS_PLUGIN_H
#define DLMS_PLUGIN_H
#include <iostream>
#include <memory>

#include "dlms_bash.h"

/*
 * 实际项目中随时可以替换成动态库插件形式，这里为demo代码采用直接链接编译的方式使用
 * */

/**
 * @brief Enum representing the type of data a plugin service might handle.
 *
 * This enum is used to specify the type of input and output data 
 * the service functions in a plugin can process.
 */
enum PluginServiceType {
    String = 0x1,
    JSON = 0x2,
    Binary = 0x4,
    Integer = 0x8,
};

/**
 * @brief Enum representing different notification types.
 *
 * This enum is used to specify the type of notifications 
 * that can be issued by the plugin.
 */
enum NotifyTypes {
    NetBroken = 0,
    Quit = 1,
};

class IContext;
/**
 * @brief Interface class for Plugin.
 *
 * This class provides an abstract interface for plugin management,
 * including initialization, starting, stopping, resetting, and 
 * communication with plugins.
 */
class Plugin {
public:
    /**
     * @brief Enum representing the status of a plugin.
     *
     * This enum is used to specify the current status of the plugin.
     */
    enum PluginStatus : uint8_t {
        PLUGIN_UNKNOWN = 0, ///< Unknown status
        PLUGIN_INIT = 1,    ///< Plugin initialized
        PLUGIN_RUNNING = 2, ///< Plugin is running
        PLUGIN_STOP = 3,    ///< Plugin stopped
        PLUGIN_Reset = 4,   ///< Plugin reset
    };
    //

public:
    virtual ~Plugin() = default;

    /**
     * @brief Initialize the plugin.
     *
     * This method performs the necessary initialization for the plugin.
     *
     * @param lpIDlms Pointer to the main framework object.
     * @param pluginName Name of the plugin.
     * @return Status code indicating success or failure.
     */
    virtual Status Init(IContext *lpIDlms, std::string pluginName) = 0;

    /**
     * @brief Start the plugin.
     *
     * This method starts the plugin execution.
     *
     * @return Status code indicating success or failure.
     */
    virtual Status Start() = 0;

    /**
     * @brief Stop the plugin.
     *
     * This method stops the plugin execution.
     *
     * @return Status code indicating success or failure.
     */
    virtual Status Stop() = 0;

    /**
     * @brief Reset the plugin.
     *
     * This method resets the plugin state.
     *
     * @return Status code indicating success or failure.
     */
    virtual Status Reset() = 0;

    /**
     * @brief Get the plugin name.
     *
     * This method returns the name of the plugin.
     *
     * @return The name of the plugin.
     */
    virtual std::string GetName() = 0;

    /**
     * @brief Send a synchronous message to the plugin.
     *
     * This method sends a synchronous message to the plugin and waits for a response.
     *
     * @param in Type of the input data.
     * @param lpInData Pointer to the input data.
     * @param out Type of the output data.
     * @param lpOutData Pointer to the output data.
     * @return Status code indicating success or failure.
     */
    virtual Status SendSync(PluginServiceType in, void *lpInData, PluginServiceType out, void *lpOutData) = 0;

    /**
     * @brief Send an asynchronous message to the plugin.
     *
     * This method sends an asynchronous message to the plugin without waiting for a response.
     *
     * @param in Type of the input data.
     * @param lpInData Pointer to the input data.
     * @return Status code indicating success or failure.
     */
    virtual Status SendAsync(PluginServiceType in, void *lpInData) = 0;

    /**
     * @brief Notify the plugin with input data.
     *
     * This method sends a notification to the plugin with the specified input data.
     *
     * @param in Type of the input data.
     * @param lpInData Pointer to the input data.
     * @return Status code indicating success or failure.
     */
    virtual Status Notify(PluginServiceType in, void *lpInData) = 0;

    /**
     * @brief Post a message to the plugin.
     *
     * This method posts a message to the plugin.
     *
     * @param in Type of the input data.
     * @param lpInData Pointer to the input data.
     * @return Status code indicating success or failure.
     */
    virtual Status PostMessage(PluginServiceType in, void *lpInData) = 0;

    /**
     * @brief Check if the plugin supports a certain service type.
     *
     * This method checks whether the plugin supports the specified service type.
     *
     * @param serviceType The service type to check.
     * @return true if the service type is supported, false otherwise.
     */
    virtual bool Support(PluginServiceType serviceType) = 0;

protected:
    volatile PluginStatus pluginStatus{PLUGIN_UNKNOWN}; ///< The current status of the plugin
    std::string pluginType; ///< The type of the plugin
};

#ifdef __cplusplus
extern "C" {

/**
 * @brief Get the version of the plugin framework.
 *
 * This function returns a string representing the version of the
 * plugin framework being used.
 *
 * @return A C-string containing the version information.
 */
const char *GetVersion();

/**
 * @brief Create a new plugin instance.
 *
 * This function creates a new instance of a plugin based on the provided
 * plugin type. The created plugin instance is returned as a pointer.
 *
 * @param pluginType The type of the plugin to be created.
 * @return A pointer to the newly created plugin instance.
 */
Plugin *CreatePlugin(const char *pluginType);

/**
 * @brief Delete an existing plugin instance.
 *
 * This function deletes an existing plugin instance, releasing any
 * resources associated with it.
 *
 * @param plugin The pointer to the plugin instance to be deleted.
 */
void DeletePlugin(Plugin *plugin);

} // extern "C"
#endif // __cplusplus


#endif //DLMS_PLUGIN_H

/**
 * @file Status.h
 * @brief Definition of the Status class for error handling and reporting.
 *
 * This file contains the definition of the Status class, which provides
 * utilities for creating and handling various statuses or outcomes of operations.
 */

#ifndef DLMS_STATUS_H
#define DLMS_STATUS_H
#include <string>
#include <cstring>
#include <cassert>
/**
 * @brief A class for representing the status or outcome of an operation.
 *
 * The Status class is used for error handling and reporting. It provides
 * methods for creating different types of status messages, checking the 
 * status type, and converting the status to a string representation.
 */
class Status {
public:
    /// Create a success status.
    Status() noexcept : state_(nullptr) {}

    /// Destructor.
    ~Status() { delete[] state_; }

    /// Copy constructor.
    Status(const Status &rhs);

    /// Copy assignment operator.
    Status &operator=(const Status &rhs);

    /// Move constructor.
    Status(Status &&rhs) noexcept : state_(rhs.state_) { rhs.state_ = nullptr; }

    /// Move assignment operator.
    Status &operator=(Status &&rhs) noexcept;

    /// Return a success status.
    static Status Ok() { return Status(); }

    /**
     * @brief Return a NotFound status.
     *
     * @param msg Primary message.
     * @param msg2 Secondary message (optional).
     * @return A Status object indicating a NotFound error.
     */
    static Status NotFound(const std::string &msg, const std::string &msg2 = std::string()) {
        return Status(kNotFound, msg, msg2);
    }

    /**
     * @brief Return a Corruption status.
     *
     * @param msg Primary message.
     * @param msg2 Secondary message (optional).
     * @return A Status object indicating a Corruption error.
     */
    static Status Corruption(const std::string &msg, const std::string &msg2 = std::string()) {
        return Status(kCorruption, msg, msg2);
    }

    /**
     * @brief Return a NotSupported status.
     *
     * @param msg Primary message.
     * @param msg2 Secondary message (optional).
     * @return A Status object indicating a NotSupported error.
     */
    static Status NotSupported(const std::string &msg, const std::string &msg2 = std::string()) {
        return Status(kNotSupported, msg, msg2);
    }

    /**
     * @brief Return an InvalidArgument status.
     *
     * @param msg Primary message.
     * @param msg2 Secondary message (optional).
     * @return A Status object indicating an InvalidArgument error.
     */
    static Status InvalidArgument(const std::string &msg, const std::string &msg2 = std::string()) {
        return Status(kInvalidArgument, msg, msg2);
    }

    /**
     * @brief Return an IOError status.
     *
     * @param msg Primary message.
     * @param msg2 Secondary message (optional).
     * @return A Status object indicating an IOError.
     */
    static Status IOError(const std::string &msg, const std::string &msg2 = std::string()) {
        return Status(kIOError, msg, msg2);
    }

    /**
     * @brief Return an OutOfMemory status.
     *
     * @param msg Primary message.
     * @param msg2 Secondary message (optional).
     * @return A Status object indicating an OutOfMemory error.
     */
    static Status OutOfMemory(const std::string &msg, const std::string &msg2 = std::string()) {
        return Status(kOutOfMemory, msg, msg2);
    }

    /// Returns true if the status indicates success.
    bool ok() const { return (state_ == nullptr); }

    /// Returns true if the status indicates a NotFound error.
    bool IsNotFound() const { return code() == kNotFound; }

    /// Returns true if the status indicates a Corruption error.
    bool IsCorruption() const { return code() == kCorruption; }

    /// Returns true if the status indicates an IOError.
    bool IsIOError() const { return code() == kIOError; }

    /// Returns true if the status indicates a NotSupported error.
    bool IsNotSupportedError() const { return code() == kNotSupported; }

    /// Returns true if the status indicates an InvalidArgument error.
    bool IsInvalidArgument() const { return code() == kInvalidArgument; }

    /// Returns true if the status indicates an OutOfMemory error.
    bool IsOutOfMemory() const { return code() == kOutOfMemory; }

    /**
     * @brief Return a string representation of this status suitable for printing.
     *
     * @return A string representation of the status.
     */
    std::string ToString() const {
        if (state_ == nullptr) {
            return "OK";
        } else {
            char tmp[30];
            const char *type;
            switch (code()) {
                case kOk:
                    type = "OK";
                    break;
                case kNotFound:
                    type = "NotFound: ";
                    break;
                case kCorruption:
                    type = "Corruption: ";
                    break;
                case kNotSupported:
                    type = "Not implemented: ";
                    break;
                case kInvalidArgument:
                    type = "Invalid argument: ";
                    break;
                case kIOError:
                    type = "IO error: ";
                    break;
                case kOutOfMemory:
                    type = "Out of memory: ";
                    break;
                default:
                    std::snprintf(tmp, sizeof(tmp),
                                  "Unknown code(%d): ", static_cast<int>(code()));
                    type = tmp;
                    break;
            }
            std::string result(type);
            uint32_t length;
            std::memcpy(&length, state_, sizeof(length));
            result.append(state_ + 5, length);
            return result;
        }
    }

private:
    /**
     * @brief Enum representing the different status codes.
     */
    enum Code {
        kOk = 0,            ///< Success status
        kNotFound = 1,      ///< Not found error
        kCorruption = 2,    ///< Corruption error
        kNotSupported = 3,  ///< Not supported error
        kInvalidArgument = 4,///< Invalid argument error
        kIOError = 5,       ///< I/O error
        kOutOfMemory = 6,   ///< Out of memory error
    };

    /**
     * @brief Get the status code.
     *
     * @return The status code of this status.
     */
    Code code() const {
        return (state_ == nullptr) ? kOk : static_cast<Code>(state_[4]);
    }

    /**
     * @brief Constructor to create a status with a specific code and messages.
     *
     * @param code The status code.
     * @param msg The primary message.
     * @param msg2 The secondary message (optional).
     */
    Status(Code code, const std::string &msg, const std::string &msg2) {
        assert(code != kOk);
        const auto len1 = static_cast<uint32_t>(msg.size());
        const auto len2 = static_cast<uint32_t>(msg2.size());
        const uint32_t size = len1 + (len2 ? (2 + len2) : 0);
        char *result = new char[size + 5];
        std::memcpy(result, &size, sizeof(size));
        result[4] = static_cast<char>(code);
        std::memcpy(result + 5, msg.data(), len1);
        if (len2) {
            result[5 + len1] = ':';
            result[6 + len1] = ' ';
            std::memcpy(result + 7 + len1, msg2.data(), len2);
        }
        state_ = result;
    }

    /**
     * @brief Copy the internal state.
     *
     * This method creates a copy of the given state.
     *
     * @param state The state to copy.
     * @return A pointer to the copied state.
     */
    static const char *CopyState(const char *state) {
        uint32_t size;
        std::memcpy(&size, state, sizeof(size));
        char *result = new char[size + 5];
        std::memcpy(result, state, size + 5);
        return result;
    }

    /// The internal state of the status. OK status has a null state_.
    const char *state_;
};

/// Copy constructor implementation.
inline Status::Status(const Status &rhs) {
    state_ = (rhs.state_ == nullptr) ? nullptr : CopyState(rhs.state_);
}

/// Copy assignment operator implementation.
inline Status &Status::operator=(const Status &rhs) {
    // The following condition catches both aliasing (when this == &rhs),
    // and the common case where both rhs and *this are ok.
    if (state_ != rhs.state_) {
        delete[] state_;
        state_ = (rhs.state_ == nullptr) ? nullptr : CopyState(rhs.state_);
    }
    return *this;
}

/// Move assignment operator implementation.
inline Status &Status::operator=(Status &&rhs) noexcept {
    std::swap(state_, rhs.state_);
    return *this;
}


#endif //DLMS_STATUS_H

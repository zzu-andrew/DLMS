//
// Created by wangyz38535 on 2022/6/29.
//

#ifndef DLMS_DLMS_MACRO_H
#define DLMS_DLMS_MACRO_H

#define POINTER_SAFE(lp)        ((nullptr == (lp)) ? "null" : (lp))

/**
 * @brief Utility function to convert a pointer to a safe string representation.
 *
 * This function checks if the given pointer is nullptr and returns a string 
 * indicating the pointer state.
 *
 * @tparam T Type of the pointer.
 * @param ptr Pointer to be checked.
 * @return "null" if the pointer is nullptr; the original pointer otherwise.
 */
template <typename T>
constexpr const char* pointerSafe(T* ptr) {
    return (nullptr == ptr) ? "null" : reinterpret_cast<const char*>(ptr);
}


#endif //DLMS_DLMS_MACRO_H

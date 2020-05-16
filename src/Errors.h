
#ifndef SRC_ERRORS_H
#define SRC_ERRORS_H


#include <string>

/**
 * @file Errors.h
 * @brief This is the implementation and declaration of error classes
 */
/**
 * @brief Class made to throw types of errors
 */
class Error{
protected:
    std::string info;                                       /**<string containing the cause of the error*/
public:
    /**
     * @brief Construct a new Error object
     *
     * @param Info Information about the error
     */
    Error(std::string Info): info(Info) { };
    /**
     * @brief Get the Info parameter
     *
     * @return std::string
     */
    virtual std::string getInfo() const {return info;};
};


/**
 * @brief Error for wrong inputs
 *
 */
class WrongInput_option: Error{
public:
    WrongInput_option(const std::string &input): Error(input){ }
    std::string getInfo() const {return info;};
};


#endif //SRC_ERRORS_H

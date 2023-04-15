#ifndef HOTEL_PARAMETEREXCEPTION_H
#define HOTEL_PARAMETEREXCEPTION_H

#include <string>
#include <stdexcept>

// Wyjątki, gdy przekazywany argument jest niewłaściwy

class ParameterException : public std::logic_error {
public:
    explicit ParameterException(const std::string& what_arg) : std::logic_error(what_arg) {}
};


#endif //HOTEL_PARAMETEREXCEPTION_H

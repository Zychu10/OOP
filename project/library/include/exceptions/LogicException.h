#ifndef HOTEL_LOGICEXCEPTION_H
#define HOTEL_LOGICEXCEPTION_H

#include <string>
#include <stdexcept>

class LogicException : public std::logic_error {
public:
    explicit LogicException(const std::string& what_arg) : std::logic_error(what_arg) {}
};

#endif //HOTEL_LOGICEXCEPTION_H

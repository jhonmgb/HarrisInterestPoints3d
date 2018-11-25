#include "Communicator/exception.h"

Exception::Exception()
{
    this->message = "";
}

Exception::Exception(ExceptionType error, string message)
{
    this->type = error;
    this->message = message;
}

Exception::~Exception()
{
    delete this;
}

/**
 * @brief getType Get the type of the exception
 * @return a type between the ExceptionType enumeration.
 */
ExceptionType Exception::getType()
{
    return type;
}

/**
 * @brief what returns the error message
 * @return a C string.
 */
const char * Exception::what() const noexcept
{
    return message.c_str();
}

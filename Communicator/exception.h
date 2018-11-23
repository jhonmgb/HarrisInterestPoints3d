#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

using std::string;
using std::exception;

enum ExceptionType { ERROR_WHILE_READING};

class Exception : public exception
{
private:
    ExceptionType type;
    string message;

public:
    Exception();
    Exception(ExceptionType error, string message);
    ~Exception();

    /**
     * @brief getType Get the type of the exception
     * @return a type between the ExceptionType enumeration.
     */
    ExceptionType getType();

    /**
     * @brief what returns the error message
     * @return a C string.
     */
    virtual const char * what() const noexcept;
};

#endif // EXCEPTION_H

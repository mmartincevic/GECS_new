#ifndef GECS_CUSTOM_EXCEPTION_H
#define GECS_CUSTOM_EXCEPTION_H

#pragma once

#include <exception>
#include <string>

namespace gecs {
    class GException : public std::exception {
    public:
        explicit GException(const std::string& message)
            : msg(message) {}

        virtual const char* what() const noexcept override {
            return msg.c_str();
        }

    private:
        std::string msg;
    };
}
// throw gecs::GException("An error occurred in SomeFunctionThatCanFail.");
#endif // GECS_CUSTOM_EXCEPTION_H
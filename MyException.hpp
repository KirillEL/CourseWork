#pragma once
#include <iostream>

class MyException {
    private:
        const char* message;
    
    public:
        MyException(const char* msg) {
            message = msg;
        }

        const char* What() {
            return message;
        }
};
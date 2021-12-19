#pragma once
#include <exception>


class MyException
{
public:
    MyException(const char *msg) : m_msg(msg) {}

    const char* What() {return this->m_msg;}

private:
const char* m_msg;
};
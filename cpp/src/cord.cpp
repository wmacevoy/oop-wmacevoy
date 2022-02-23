#include "cord.h"

#include <stdexcept>
#include <iostream>

namespace power
{
    static double checkedLength(double length) {
        if (length > 0.0)
        {
            return length;
        }
        else
        {
            throw std::out_of_range("length must be positive");
        }
    }

    Cord::Cord(int constructedOn, double length, const std::string &connector, double capacity)
        : m_constructedOn(constructedOn), m_length(checkedLength(length)), m_connector(connector), m_capacity(capacity)
    {
        std::cout << "Cord@" 
             << (void*) this 
             << " from line " << m_constructedOn << " constructed." 
             << std::endl;
    }

    Cord::~Cord()
    {
        std::cout << "Cord@" 
             << (void*) this 
             << " from line " << m_constructedOn << " destructed." 
             << std::endl;
    }


    double Cord::length() const
    {
        return m_length;
    }

    void Cord::length(double value)
    {
        m_length=checkedLength(value);
    }
}
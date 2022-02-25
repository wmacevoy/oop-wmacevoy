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
    Cord::Cord(const Cord &copy) 
      : m_constructedOn(copy.m_constructedOn), 
        m_length(copy.m_length), 
        m_capacity(copy.m_capacity), 
        m_connector(copy.m_connector)
      {
        std::cout << "Cord@" 
             << (void*) this 
             << " copied from " << (const void*) &copy 
             << std::endl;

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
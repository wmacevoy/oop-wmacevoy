#pragma once

#include <string>
#include <memory>

namespace power {
  class Cord {
      public: Cord(const Cord &copy);
      public: const int m_constructedOn;
      private: double m_length;
      private: std::string m_connector;
      private: double m_capacity;
      public: Cord(int constructedOn, double length, const std::string &connector, double capacity);
      public: double length() const;
      public: void length(double value);
      public: ~Cord();
  };
  typedef std::shared_ptr < Cord > SPCord;

}
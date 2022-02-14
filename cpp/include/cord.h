#pragma once

#include <string>

namespace power {
  class Cord {
      private: double m_length;
      private: std::string m_connector;
      private: double m_capacity;
      public: Cord(double length, const std::string &connector, double capacity);
      public: double length() const;
      public: void length(double value);
  };

}
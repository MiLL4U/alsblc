#include "person.hpp"

using std::string;

Person::Person() : m_name(""), m_height(0), m_weight(0) {}

Person::Person(const string &name, const double &height, const double &weight)
    : m_name(name), m_height(height), m_weight(weight) {}

void Person::set_name(const string &name) { m_name = name; }
string Person::get_name() const { return m_name; }

void Person::set_height(const double &height) { m_height = height; }
double Person::get_height() const { return m_height; }

void Person::set_weight(const double &weight) { m_weight = weight; }
double Person::get_weight() const { return m_weight; }

double Person::get_bmi() const {
    return m_weight / ((m_height / 100) * (m_height / 100));
}
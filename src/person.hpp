#ifndef _PERSON_HPP_
#define _PERSON_HPP_

#include <string>

using std::string;

class Person {
    std::string m_name;
    double m_height;
    double m_weight;

   public:
    Person();
    Person(const std::string &name, const double &height, const double &weight);

    void set_name(const string &name);
    string get_name() const;

    void set_height(const double &height);
    double get_height() const;

    void set_weight(const double &weight);
    double get_weight() const;

    double get_bmi() const;
};

#endif /* _PERSON_HPP_ */

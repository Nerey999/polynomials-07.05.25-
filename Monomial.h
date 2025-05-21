#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cmath>

class Monomial {
 public:
    Monomial(std::string);
    std::string get_monomial() const;
    std::string get_monomial_with_sign() const;

    int coefficient_sign() const;
    std::string get_coefficient() const;
    double get_double_coefficient() const;
    void set_coefficient(double);
    void add_coefficient(double);
    std::vector<int> dividers_coefficient();
    
    double value_in(std::map<char, double>) const;
    Monomial derivative_one(char) const;
    friend bool operator> (Monomial, Monomial);
    friend bool operator< (Monomial, Monomial);
    friend bool operator== (Monomial, Monomial);
    friend bool operator!= (Monomial, Monomial);
    friend Monomial get_quotient (Monomial, Monomial);
    friend Monomial operator* (Monomial, Monomial);
 private:
    double coefficient;
    std::vector<int> powers;
    std::vector<std::pair<int, char> > powers_with_sort;
    std::map<char, int> powers_map;
};

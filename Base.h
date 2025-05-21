#pragma once
#include <list>
#include "Polynomial.h"
#include "Filter.h"

class Base {
public:
    void add(std::string);
    void add(Polynomial);
    void erase(int);
    void clear();
    std::vector<std::string> get_base();
    Polynomial get(int);
    Polynomial sum_polynomials(int, int);
    Polynomial sub_polynomials(int, int);
    Polynomial mul_polynomials(int, int);
    std::pair<Polynomial, Polynomial> div_polynomials(int, int);
    bool equal_polynomials(int, int);
private:
    Filter filter;
    std::list<Polynomial> polynomials;
};


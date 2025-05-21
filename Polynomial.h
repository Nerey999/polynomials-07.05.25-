#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <regex>
#include "Monomial.h"

class Polynomial{
 public:
    Polynomial(std::string);
    Polynomial();
    std::vector<char> used_perems() const;
    std::string get_polynomial() const;
    double value_in(std::map<char, double>) const;
    Polynomial derivative(int, char);
    Polynomial derivative_one(char);
    std::vector<int> roots();
    
    friend Polynomial operator- (Polynomial);
    friend Polynomial operator+ (Polynomial, Polynomial);
    friend Polynomial operator- (Polynomial, Polynomial);
    friend Polynomial operator* (Polynomial, Monomial);
    friend Polynomial operator* (Monomial, Polynomial);
    friend Polynomial operator* (Polynomial, Polynomial);
    friend std::pair<Polynomial, Polynomial> operator/ (Polynomial, Polynomial);
    friend bool operator== (Polynomial, Polynomial);
 private:
    void delete_zero_monomials();
    void merge_equal_monomials();
    void sort_list();
    std::list<Monomial> polynomial;
    std::vector<int> used;
};
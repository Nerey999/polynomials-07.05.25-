#include "Base.h"

void Base::add(std::string polynomial_str) {
    std::string error = filter.check(polynomial_str);
    if (error != "") {
        throw error;
        return;
    }
    polynomial_str.erase(
        remove_if(
            polynomial_str.begin(),
            polynomial_str.end(),
            isspace
        ),
    polynomial_str.end());
    
    Polynomial polynomial(polynomial_str);

    polynomials.push_back(polynomial);
}

void Base::add(Polynomial polynomial) {
    polynomials.push_back(polynomial);
} 

void Base::erase(int inx) {
    if (inx >= polynomials.size()) throw "Segmentation error";
    auto i = polynomials.begin();
    for (int cnt = 0; cnt < inx; cnt++) {
        i++;
    }
    polynomials.erase(i);
}

void Base::clear() {
    polynomials.clear();
}

std::vector<std::string> Base::get_base() {
    std::vector<std::string> base;
    for (auto x : polynomials) {
        base.push_back(x.get_polynomial());
    }
    return base;
}

Polynomial Base::get(int inx) {
    if (inx >= polynomials.size()) throw "Segmentation error";
    auto it = polynomials.begin();
    for (int i = 0; i < inx; i++) {
        it++;
    }
    return *it;
}

Polynomial Base::sum_polynomials(int first, int second) {
    return Polynomial(get(first) + get(second));
}

Polynomial Base::sub_polynomials(int first, int second) {
    return Polynomial(get(first) - get(second));
}

Polynomial Base::mul_polynomials(int first, int second) {
    return Polynomial(get(first) * get(second));
}

std::pair<Polynomial, Polynomial> Base::div_polynomials(int first, int second) {
    return get(first) / get(second);
}

bool Base::equal_polynomials(int first, int second) {
    return get(first) == get(second);
}
#include "Polynomial.h"

Polynomial::Polynomial(std::string polynomial_str) {
    used.resize(26);

    std::regex re("(?=[+-])");

    std::vector<std::string> parts(
        std::sregex_token_iterator(polynomial_str.begin(), polynomial_str.end(), re, -1),
        std::sregex_token_iterator()
    );

    for (int i = 0; i < parts.size(); i++) {
        polynomial.push_back(Monomial(parts[i]));
    } 

    sort_list();
    delete_zero_monomials();
    merge_equal_monomials();
}

Polynomial::Polynomial() {
    used.resize(26);
    sort_list();
    delete_zero_monomials();
    merge_equal_monomials();
}

std::vector<char> Polynomial::used_perems() const {
    std::string polynomial_str = get_polynomial();
    std::set<char> symbols;
    for (int i = 0; i < polynomial_str.size(); i++) {
        if (isalpha(polynomial_str[i])) {
            symbols.insert(polynomial_str[i]);
        }
    }
    std::vector<char> answer;
    for (auto x : symbols) {
        answer.push_back(x);
    }
    return answer;
}

std::string Polynomial::get_polynomial() const {
    std::string polynomial_str = "";
    for (auto it = polynomial.begin(); it != polynomial.end(); it++) {
        if (it == polynomial.begin()) polynomial_str += it->get_monomial();
        else {
            polynomial_str += it->get_monomial_with_sign();
        }
    }
    if (polynomial_str == "") {
        polynomial_str += "0";
    }
    return polynomial_str;
}

double Polynomial::value_in(std::map<char, double> values) const {
    double answer = 0;
    for (auto x : polynomial) {
        answer += x.value_in(values);
    }
    return answer;
}

Polynomial Polynomial::derivative(int n, char symbol) {
    Polynomial answer = *this;
    for (int i = 0; i < n; i++) {
        answer = answer.derivative_one(symbol);
    }
    return answer;
}

Polynomial Polynomial::derivative_one(char symbol) {
    std::string new_polynomial = "";
    for (auto x : polynomial) {
        new_polynomial += x.derivative_one(symbol).get_monomial_with_sign();
    }
    return Polynomial(new_polynomial);
}

std::vector<int> Polynomial::roots() {
    std::vector<char> perems_used = used_perems();
    if (perems_used.size() != 1) {
        throw "Roots can be find in polynomial with only one variable";
    }
    std::vector<int> answers;
    std::vector<int> to_check = polynomial.rbegin()->dividers_coefficient();
    for (int i = 0; i < to_check.size(); i++) {
        std::map<char, double> m;
        m[perems_used[0]] = to_check[i];
        if (value_in(m) == 0) {
            answers.push_back(to_check[i]);
        }
    }
    return answers;
}


void Polynomial::delete_zero_monomials() {
    polynomial.remove_if([](const Monomial& monomial) {
        return monomial.get_coefficient() == "0";
    });
}

void Polynomial::merge_equal_monomials() {
    std::map<Monomial, double> polynomial_map;
    for (auto it = polynomial.begin(); it != polynomial.end(); it++) {
        polynomial_map[*it]+=it->get_double_coefficient();
    }
    polynomial.clear();
    for (std::pair<Monomial, double> monomial : polynomial_map) {
        monomial.first.set_coefficient(monomial.second);
        polynomial.push_back(monomial.first);
    }
    sort_list();
    delete_zero_monomials();
}

void Polynomial::sort_list() {
    polynomial.sort([](Monomial a, Monomial b) { return a > b; });
}


Polynomial operator- (Polynomial polynomial) {
    for (auto& x : polynomial.polynomial) {
        x.set_coefficient(-x.get_double_coefficient());
    }
    return polynomial;
}

Polynomial operator+ (Polynomial first, Polynomial second) {
    std::string new_polynomial = "";
    auto i = first.polynomial.begin(), j = second.polynomial.begin();
    while (i != first.polynomial.end() and j != second.polynomial.end()) {
        if (*i > *j) {
            new_polynomial += i->get_monomial_with_sign();
            i++;
        } else if (*i == *j) {
            Monomial monomial(i->get_monomial_with_sign());
            monomial.set_coefficient(i->get_double_coefficient() + j->get_double_coefficient());
            if (monomial.get_double_coefficient() != 0) {
                new_polynomial += monomial.get_monomial_with_sign();
            }
            i++; j++;
        } else {
            new_polynomial += j->get_monomial_with_sign();
            j++;
        }
    }
    while (i != first.polynomial.end()) {
        new_polynomial += i->get_monomial_with_sign();
        i++;
    }
    while (j != second.polynomial.end()) {
        new_polynomial += j->get_monomial_with_sign();
        j++;
    }
    return Polynomial(new_polynomial);
}

Polynomial operator-(Polynomial first, Polynomial second) {
    return first + (-second);
}

bool operator==(Polynomial first, Polynomial second) {
    if (first.polynomial.size() != second.polynomial.size()) {
        return false;
    }
    auto fir = first.polynomial.begin();
    auto sec = second.polynomial.begin();
    for (fir = first.polynomial.begin(), sec = second.polynomial.begin();
         fir != first.polynomial.end() and sec != second.polynomial.end();) {
        if (*fir != *sec) return false;
        fir++; sec++;
    }
    return true;
}

Polynomial operator* (Polynomial polynomial, Monomial monomial) {
    std::string res_polynomial = "";
    for (auto x : polynomial.polynomial) {
        res_polynomial += (x * monomial).get_monomial_with_sign();
    }
    return Polynomial(res_polynomial);
}

Polynomial operator* (Monomial monomial, Polynomial polynomial) {
    std::string res_polynomial = "";
    for (auto x : polynomial.polynomial) {
        res_polynomial += (x * monomial).get_monomial_with_sign();
    }
    return Polynomial(res_polynomial);
}

Polynomial operator* (Polynomial first, Polynomial second) {
    std::string res_polynomial = "";
    for (auto x : first.polynomial) {
        for (auto y : second.polynomial) {
            res_polynomial += (x * y).get_monomial_with_sign();
        }
    }
    return Polynomial(res_polynomial);
}

std::pair<Polynomial, Polynomial> operator/ (Polynomial first, Polynomial second) {
    std::vector<char> first_used = first.used_perems();
    std::vector<char> second_used = second.used_perems();
    if (first_used.size() > 1 or second_used.size() > 1) {
        throw "division can only be done with polynomials in one variable";
    }
    if (first_used.size() == 1 and second_used.size() == 1 and
        first_used[0] != second_used[0]) {
            throw "Variable must be equal";
    }
    std::pair<Polynomial, Polynomial> answer;
    while (true) {
        Monomial divisible = first.polynomial.size() > 0 ? *first.polynomial.begin() : Monomial("0");
        Monomial divisor  = second.polynomial.size() > 0 ? *second.polynomial.begin() : Monomial("0");
        Monomial quotient = get_quotient(divisible, divisor);
        answer.first = answer.first + Polynomial(quotient.get_monomial());
        first = first - quotient * second;
        if (first == answer.second) {
            break;
        }
        answer.second = first;
    }
    return answer;
}
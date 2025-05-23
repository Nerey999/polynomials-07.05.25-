#include "Monomial.h"

Monomial::Monomial(std::string monomial) {
    powers.resize(26);
    std::stringstream in(monomial);
    if (monomial == "") {
        coefficient = 0;
        return;
    }
    if (!(in >> coefficient)) {
        coefficient = 1;
    }
    if (monomial[0] == '-' and isalpha(monomial[1])) {
        coefficient *= -1;
    }
    for (int i = 0; i < monomial.size(); i++) {
        if (isalpha(monomial[i])) {
            if (i + 1 >= monomial.size() or monomial[i+1] != '^') {
                powers[monomial[i]-'a']++;
            } else {
                std::string power;
                char symbol = monomial[i];
                i+=2;
                while (i < monomial.size() and isdigit(monomial[i])) {
                    power += monomial[i];
                    i++;
                }
                i--;
                powers[symbol - 'a'] += stoi(power); // тут будет переполнение
            }
        }
    }

    // map for powers sort
    for (int i = 0; i < powers.size(); i++) {
        if (powers[i] != 0) {
            powers_map['a'+i] = powers[i];
        }
    }

    // powers vector with normal sort {power, char}
    for (auto element : powers_map) {
        char ch = element.first;
        int power = element.second;
        powers_with_sort.push_back({power, ch});
    }
    std::sort(powers_with_sort.begin(), powers_with_sort.end(), 
        [](const std::pair<int, char> &first, const std::pair<int, char> &second) { 
            if (first.first != second.first) return first.first > second.first;
            return first.second < second.second;
        }
    );
}

std::string Monomial::get_monomial() const{
    std::string monomial = "";
    if (coefficient == 0) return "0";
    if (coefficient != 1 and coefficient != -1) {
        monomial += get_coefficient();
    }
    
    
    for (auto element : powers_with_sort) {
        int power = element.first;
        char ch = element.second;
        if (power == 1) monomial += ch;
        else {
            monomial += ch;
            monomial += '^';
            monomial += std::to_string(power);
        }
    }

    if (coefficient == 1 and monomial == "") {
        monomial += "1";
    }
    if (coefficient == -1) {
        monomial = "-" + monomial;
        if (monomial == "-") {
            monomial += "1";
        }
    }
    return monomial;
}

std::string Monomial::get_monomial_with_sign() const{
    return (this->coefficient_sign() == 1 ? "+" : "") + 
                               this->get_monomial();
}


int Monomial::coefficient_sign() const {
    return coefficient >= 0 ? 1 : -1;
}

void Monomial::set_coefficient(double new_coefficient) {
    coefficient = new_coefficient;
}

void Monomial::add_coefficient(double value) {
    coefficient += value;
}

std::vector<int> Monomial::dividers_coefficient() {
    std::vector<int> ans{0};
    if ((int)coefficient != coefficient) return ans;
    for(int i = 1; i <= std::abs(coefficient); i++) {
        if (std::abs((int)coefficient) % i == 0) {
            ans.push_back(i);
            ans.push_back(-i);
        }
    }
    std::sort(ans.begin(), ans.end());
    return ans;
}

std::string Monomial::get_coefficient() const {
    std::stringstream buff;
    buff << std::fixed << std::setprecision(10) << coefficient;
    std::string coefficient_str = buff.str();
    int lastNonZero = coefficient_str.find_last_not_of('0');
    if (lastNonZero != std::string::npos) {
        coefficient_str = coefficient_str.substr(0, lastNonZero + 1);
    }
    if (!coefficient_str.empty() && coefficient_str.back() == '.') {
        coefficient_str.pop_back();
    }
    return coefficient_str;
}

double Monomial::get_double_coefficient() const {
    return coefficient;
}


double Monomial::value_in(std::map<char, double> values) const {
    double answer = 1;
    for (auto x : powers_with_sort) {
        answer *= std::pow(values[x.second], x.first);
    }
    if (powers_with_sort.size() == 0) answer = 1;
    return coefficient * answer;
}

Monomial Monomial::derivative_one(char symbol) const {
    if (powers_with_sort.size() == 0) {
        return Monomial("0");
    }
    if (powers[symbol-'a'] == 0) {
        return Monomial("0");
    }
    std::string new_monomial = "";
    new_monomial += std::to_string(this->get_double_coefficient() 
                    * std::max(1, powers[symbol-'a']));
    for (auto element : powers_with_sort) {
        int power = element.first;
        char ch = element.second;
        new_monomial += ch;
        new_monomial += '^';
        if (ch == symbol) {
            new_monomial += std::to_string(std::max(0, power-1));
        } else {
            new_monomial += std::to_string(power);
        }
    }
    return Monomial(new_monomial);
}

bool operator>(Monomial first, Monomial second) {
    std::vector<std::pair<int, char> >& fst = first.powers_with_sort;
    std::vector<std::pair<int, char> >& sec = second.powers_with_sort;
    for (int i = 0; i < std::min(fst.size(), 
                        sec.size()); i++) {
        if (fst[i] == sec[i]) continue;
        if (fst[i].first != sec[i].first) return fst[i].first > sec[i].first;
        return fst[i].second < sec[i].second;
    }
    return fst.size() > sec.size();
}

bool operator<(Monomial first, Monomial second) {
    std::vector<std::pair<int, char> >& fst = first.powers_with_sort;
    std::vector<std::pair<int, char> >& sec = second.powers_with_sort;
    for (int i = 0; i < std::min(fst.size(), 
                        sec.size()); i++) {
        if (fst[i] == sec[i]) continue;
        if (fst[i].first != sec[i].first) return fst[i].first < sec[i].first;
        return fst[i].second > sec[i].second;
    }
    return fst.size() < sec.size();
}

bool operator== (Monomial first, Monomial second) {
    if (first.powers_with_sort.size() != second.powers_with_sort.size()) return false;
    if (first.get_double_coefficient() != second.get_double_coefficient()) return false;
    for (int i = 0; i < first.powers_with_sort.size(); i++) {
        if (first.powers_with_sort[i] != second.powers_with_sort[i]) {
            return false;
        }
    }
    return true;
}

bool operator!= (Monomial first, Monomial second) {
    return !(first == second);
}

Monomial get_quotient (Monomial first, Monomial second) {
    if (first.powers_with_sort.size() > 1 or second.powers_with_sort.size() > 1) {
        throw "division can only be done with polynomials in one variable";
    }
    if (first.powers_with_sort.size() == 1 and second.powers_with_sort.size() == 1 and
        first.powers_with_sort[0].second != second.powers_with_sort[0].second) {
            throw "Variable must be equal";
    }
    if (second.coefficient == 0) {
        throw "Division by zero";
    }
    if (first.powers_with_sort.size() == 0 and second.powers_with_sort.size() == 0) {
        std::string new_monomial = "";
        new_monomial += std::to_string(first.coefficient / second.coefficient);
        return Monomial(new_monomial);
    }
    if (first.powers_with_sort.size() == 1 and second.powers_with_sort.size() == 0) {
        std::string new_monomial = "";
        new_monomial += std::to_string(first.coefficient / second.coefficient);
        new_monomial += first.powers_with_sort[0].second;
        new_monomial += "^";
        new_monomial += std::to_string(first.powers_with_sort[0].first);
        return Monomial(new_monomial);
    }
    if ((first.powers_with_sort.size() == 0 and second.powers_with_sort.size() == 1) or 
        (first.powers_with_sort[0].first < second.powers_with_sort[0].first)) {
            return Monomial("0");
    }
    std::string new_monomial = "";
    new_monomial += std::to_string(first.coefficient / second.coefficient);
    new_monomial += first.powers_with_sort[0].second;
    new_monomial += "^";
    new_monomial += std::to_string(first.powers_with_sort[0].first - 
                                   second.powers_with_sort[0].first);
    return Monomial(new_monomial);
}

Monomial operator* (Monomial first, Monomial second) {
    std::string new_monomial = "";
    new_monomial += std::to_string(first.coefficient * second.coefficient);
    for (int i = 0; i < first.powers.size(); i++) {
        if (first.powers[i] + second.powers[i] != 0) {
            std::string cur = "";
            cur += (char)('a' + i);
            cur += "^" + std::to_string(first.powers[i] + second.powers[i]);
            new_monomial += cur;
        }
    }
    return Monomial(new_monomial);
}


#include "Monomial.h"
#include "Polynomial.h"
#include "Base.h"
#include "Filter.h"
#include <iostream>
#include <algorithm>

int main() {
    /*
    add x^2 + 2x + 1
    add x + 1
    div 1 2
    */
    // std::cout << (Polynomial("x") / Polynomial("-x")).get_polynomial() << '\n';
    // std::cout << get_quotient(Monomial("18.02x^85"), Monomial("-2x^80")).get_monomial() << '\n';
    Base base;
    while (true) {
        std::string full_line;
        std::getline(std::cin, full_line);
        std::stringstream in_line(full_line);
        std::string command = "";
        in_line >> command;
        if (command == "") {
            continue;
        } else if (command == "exit") {
            exit(0);  
        } else if (command == "help") {
            std::cout << "help to show this text\n" 
                      << "add [polynomial] to add polynomial in base\n"
                      << "base to show polynomial base\n"
                      << "clear to clear base\n"
                      << "sum [inx1] [inx2] to sum polynomials\n" 
                      << "sub [inx1] [inx2] to subtract polynomials\n"
                      << "delete [inx] to delete monomial\n"
                      << "value [inx] to find value with set values in inx polynomial\n"
                      << "equal [inx1] [inx2] to check in polynomials is equal\n"
                      << "mul [inx1] [inx2] to multiplicate polynomials\n"
                      << "der [inx] to take the derivative\n"
                      << "div [inx1] [inx2] to division polynomials\n"
                      << "roots [inx] to find integer roots\n"
                      << "exit to close program\n";
        } else if (command == "add") {
            std::string polynomial_str;
            std::getline(in_line, polynomial_str);
            try {
                base.add(polynomial_str);
            } catch (std::string error_message) {
                std::cout << error_message << '\n';
            }
        } else if (command == "base") {
            std::vector<std::string> data_base = base.get_base();
            if (data_base.size() == 0) {
                std::cout << "Пока что тут ничего нет.\n";
            }
            for (int i = 0; i < data_base.size(); i++) {
                std::cout << i + 1 << " " << data_base[i] << '\n';
            } 
        } else if (command == "clear") {
            base.clear();  
        } else if (command == "sum") {
            // std::cout << "Напишите индексы тех многочленов которые вы хотите сложить: ";
            // std::string full_sum_line;
            // std::getline(std::cin, full_sum_line);
            // std::stringstream in_sum(full_sum_line);
            int inx1 = -1, inx2 = -1;
            // in_sum >> inx1 >> inx2;
            in_line >> inx1 >> inx2;
            inx1--; inx2--;
            try {
                Polynomial answer = base.sum_polynomials(inx1, inx2);
                std::cout << "Ответ это: " << answer.get_polynomial() << ".\n";
                        base.add(answer);
                // while (true) {
                //     std::cout << "Добавить в базу?(y/n) ";
                //     std::string full_sum_yn_line;
                //     std::getline(std::cin, full_sum_yn_line);
                //     std::stringstream in_sum_yn(full_sum_yn_line);
                //     char ans;
                //     in_sum_yn >> ans;
                //     if (ans == 'y') {
                //         base.add(answer);
                //         break;
                //     } else if (ans == 'n') {
                //         break;
                //     }
                // }
            } catch (const char* error_message) {
                std::cout << error_message << '\n';
            }
        } else if (command == "sub") {
            int inx1 = -1, inx2 = -1;
            in_line >> inx1 >> inx2;
            inx1--; inx2--;
            try {
                Polynomial answer = base.sub_polynomials(inx1, inx2);
                std::cout << "Ответ это: " << answer.get_polynomial() << ".\n";
                        base.add(answer);
            } catch (const char* error_message) {
                std::cout << error_message << '\n';
            }
        } else if (command == "delete") {
            int inx = -1;
            in_line >> inx;
            inx--;
            try {
                base.erase(inx);
            } catch (const char* error_message) {
                std::cout << error_message << '\n';
            }
        } else if (command == "value") {
            int inx = -1;
            in_line >> inx;
            inx--;
            try {
                std::vector<char> perems = base.get(inx).used_perems();
                if (perems.size() == 0) {
                    std::cout << "Получается " << base.get(inx).get_polynomial() << '\n';
                    continue;
                }
                std::cout << "Введите значения для ";
                for (auto x : perems) {
                    std::cout << x << ' ';
                }
                std::cout << "соответственно: ";
                std::string value_line;
                std::getline(std::cin, value_line);
                std::stringstream in_value(value_line);
                std::map<char, double> values;
                for (int i = 0; i < perems.size(); i++) {
                    double value;
                    in_value >> value;
                    values[perems[i]] = value;
                }
                std::cout << "Получается " << base.get(inx).value_in(values) << '\n';
            } catch (const char* error_line) {
                std::cout << error_line << '\n';
            }
        } else if (command == "equal") {
            int inx1 = -1, inx2 = -1;
            in_line >> inx1 >> inx2;
            inx1--; inx2--;
            try {
                if (base.equal_polynomials(inx1, inx2)) {
                    std::cout << "Они равны\n";
                } else {
                    std::cout << "Они не равны\n";
                }
            } catch (const char* error_message) {
                std::cout << error_message << '\n';
            }
        } else if (command == "mul") {
            int inx1 = -1, inx2 = -1;
            in_line >> inx1 >> inx2;
            inx1--; inx2--;
            try {
                Polynomial answer = base.mul_polynomials(inx1, inx2);
                std::cout << "Ответ это: " << answer.get_polynomial() << ".\n";
                        base.add(answer);
            } catch (const char* error_message) {
                std::cout << error_message << '\n';
            }
        } else if (command == "der") {
            int inx = -1;
            in_line >> inx;
            inx--;
            try {
                Polynomial answer = base.get(inx);
                std::cout << "Введите для какого символа брать производную и какую: ";
                std::string der_line;
                std::getline(std::cin, der_line);
                std::stringstream in_der(der_line);
                char symbol = 'x';
                int n = 1;
                in_der >> symbol >> n;
                answer = answer.derivative(n, symbol);
                std::cout << "Получается " << answer.get_polynomial() << '\n';
                base.add(answer);
            } catch (const char* error_line) {
                std::cout << error_line << '\n';
            }
        } else if (command == "div") {
            int inx1 = -1, inx2 = -1;
            in_line >> inx1 >> inx2;
            inx1--; inx2--;
            try {
                std::pair<Polynomial, Polynomial> answer = base.div_polynomials(inx1, inx2);
                std::cout << "Частное: " << answer.first.get_polynomial() << ".\n"
                          << "Остаток: " << answer.second.get_polynomial() << ".\n";
                base.add(answer.first);
                base.add(answer.second);
            } catch (const char* error_message) {
                std::cout << error_message << '\n';
            }
        } else if (command == "roots") {
            int inx = -1;
            in_line >> inx;
            inx--;
            try {
                std::vector<int> answer = base.get(inx).roots();
                if (answer.size() == 0) {
                    std::cout << "Целых корней нет\n";
                    continue;
                }
                std::cout << "Целые корни: ";
                for(auto x : answer) {
                    std::cout << x << ' ';
                } std::cout << '\n';
            } catch (const char* error_message) {
                std::cout << error_message << '\n';
            }
        } else {
            std::cout << "incorrect command, use help\n";
        }
    }
    return 0;
}
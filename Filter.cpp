#include "Filter.h"

std::string Filter::check(std::string for_check) {
    inx = 0;
    current = for_check;
    try {
        s1();
    } catch (const char* error_message) {
        std::string new_error_message = error_message;
        new_error_message += " in position ";
        new_error_message += std::to_string(inx);
        return new_error_message.c_str();
    }
    return "";
}

void Filter::s1() {
    if (inx >= current.size()) throw "You made a mistake in the first character.";
    inx++;
    if (current[inx-1] == ' ') {
        s1();
        return;
    }
    if (isalpha(current[inx-1]) and current[inx-1] >= 'a') {
        s3();
        return;
    }
    if (isdigit(current[inx-1])) {
        s7();
        return;
    }
    if (current[inx-1] == '+' or current[inx-1] == '-') {
        s2();
        return;
    }
    throw "You made a mistake in the first character.";
}

void Filter::s2() {
    if (inx >= current.size()) throw "You didn't enter a monomial after the sign.";
    inx++;
    if (current[inx-1] == ' ') {
        s2();
        return;
    }
    if (isalpha(current[inx-1]) and current[inx-1] >= 'a') {
        s3();
        return;
    }
    if (isdigit(current[inx-1])) {
        s7();
        return;
    }
    throw "You didn't enter a monomial after the sign.";
}

void Filter::s3() {
    if (inx >= current.size()) return;
    inx++;
    if (current[inx-1] == ' ') {
        s3();
        return;
    }
    if (current[inx-1] == '^') {
        s4();
        return;
    }
    if (current[inx-1] == '+' or current[inx-1] == '-') {
        s2();
        return;
    }
    if (isalpha(current[inx-1]) and current[inx-1] >= 'a') {
        s3();
        return;
    }
    throw "You made a mistake in the monomial";
}

void Filter::s4() {
    if (inx >= current.size()) throw "You made a mistake after the degree sign";
    inx++;
    if (current[inx-1] == ' ') {
        s4();
        return;
    }
    if (isdigit(current[inx-1])) {
        s5();
        return;
    }
    throw "You made a mistake after the degree sign";
}

void Filter::s5() {
    if (inx >= current.size()) return;
    inx++;
    if (current[inx-1] == ' ') {
        s6();
        return;
    }
    if (isdigit(current[inx-1])) {
        s5();
        return;
    }
    if (isalpha(current[inx-1]) and current[inx-1] >= 'a') {
        s3();
        return;
    }
    if (current[inx-1] == '+' or current[inx-1] == '-') {
        s2();
        return;
    }
    throw "You made a mistake in the degree indicator.";
}

void Filter::s6() {
    if (inx >= current.size()) return;
    inx++;
    if (current[inx-1] == ' ') {
        s6();
        return;
    }
    if (isalpha(current[inx-1]) and current[inx-1] >= 'a') {
        s3();
        return;
    }
    if (current[inx-1] == '+' or current[inx-1] == '-') {
        s2();
        return;
    }
    throw "Spaces are not allowed";
}

void Filter::s7() {
    if (inx >= current.size()) return;
    inx++;
    if (isalpha(current[inx-1]) and current[inx-1] >= 'a') {
        s3();
        return;
    }
    if (isdigit(current[inx-1])) {
        s7();
        return;
    }
    if (current[inx-1] == '.') {
        s8();
        return;
    }
    if (current[inx-1] == ' ') {
        s6();
        return;
    }
    if (current[inx-1] == '+' or current[inx-1] == '-') {
        s2();
        return;
    }
    throw "You made a mistake in the coefficient";
}

void Filter::s8() {
    if (inx == current.size()) throw "You made a mistake after the comma";
    inx++;
    if (isdigit(current[inx-1])) {
        s9();
        return;
    }
    throw "You made a mistake after the comma";
}

void Filter::s9() {
    if (inx == current.size()) return;
    inx++;
    if (isdigit(current[inx-1])) {
        s9();
        return;
    }
    if (isalpha(current[inx-1]) and current[inx-1] >= 'a') {
        s3();
        return;
    }
    if (current[inx-1] == '-' or current[inx-1] == '+') {
        s2();
        return;
    }
    throw "You made a mistake in the material coefficient.";
}

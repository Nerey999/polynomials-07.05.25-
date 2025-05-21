#include "Filter.h"

std::string Filter::check(std::string for_check) {
    inx = 0;
    current = for_check;
    try {
        s1();
    } catch (const char* error_message) {
        std::string new_error_message = error_message;
        new_error_message += " в позиции ";
        new_error_message += std::to_string(inx);
        return new_error_message.c_str();
    }
    return "";
}

void Filter::s1() {
    if (inx >= current.size()) throw "Вы ошиблись в первом символе";
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
    throw "Вы ошиблись в первом символе";
}

void Filter::s2() {
    if (inx >= current.size()) throw "Вы не ввели одночлен после знака";
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
    throw "Вы не ввели одночлен после знака";
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
    throw "Вы ошиблись в одночлене";
}

void Filter::s4() {
    if (inx >= current.size()) throw "Вы ошиблись после знака степени";
    inx++;
    if (current[inx-1] == ' ') {
        s4();
        return;
    }
    if (isdigit(current[inx-1])) {
        s5();
        return;
    }
    throw "Вы ошиблись после знака степени";
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
    throw "Вы ошиблись в показателе степени";
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
    throw "Пробел недопустим";
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
    throw "Вы ошиблись в коэфиценте";
}

void Filter::s8() {
    if (inx == current.size()) throw "Вы ошиблись после запятой";
    inx++;
    if (isdigit(current[inx-1])) {
        s9();
        return;
    }
    throw "Вы ошиблись после запятой";
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
    throw "Вы ошиблись в вещественном коэфиценте";
}

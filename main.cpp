#include <iostream>
#include <string>
#include <vector>


class Long_long {

public:
    int sign;
    std::vector<int> numbers;
    long exponent;

    Long_long () {
        sign = 1;
        numbers = std::vector<int>(1, 0);
        exponent = 1;
    }

    void copypaste (Long_long& number) {
        sign = number.sign;
        exponent = number.exponent;
        numbers = std::vector<int>(number.numbers);
    }

    void enter_from_string (std::string string) {
        int i;

        if (string[0] == '-') {
            sign = -1;
            i = 1;
        }

        else {
            sign = 1;
            i = 0;
        }

        exponent = string.length() - i;

        while (i < string.length()) {

            if (string[i] == '.')
                exponent = sign == 1 ? i : i - 1;
            else
                numbers.push_back(string[i] - '0');

            i++;
        }

        del_zeroes();

    }

    void del_zeroes() {
        int n = std::max((long) 1, exponent);

        while (numbers.size() > (n + 1) && numbers[numbers.size() - 1] == 0)
            numbers.erase(numbers.end() - 1);

        while (numbers.size() > 1 && numbers[0] == 0) {
            numbers.erase(numbers.begin());
            exponent--;
        }

        while (numbers.size() > 1 && numbers[numbers.size() - 1] == 0 && numbers.size() - 1 != exponent) {
            numbers.erase(numbers.end() - 1);
        }

        if (numbers.size() == 1 && numbers[0] == 0) {
            exponent = 1;
            sign = 1;
        }
    }

    void printing () {

        std::string last_symbol = " ";

        if (sign == -1) {
            std::cout << "-";
            last_symbol = "-";
        }

        if (exponent >= 0) {
            int i = 0;

            while(i < numbers.size() && i < exponent) {
                last_symbol = numbers[i];
                std::cout << numbers[i++];
            }

            while (i < exponent) {
                std::cout << "0";
                last_symbol = "0";
                i++;
            }

            if (i < numbers.size()) {
                std::cout << numbers[i++];
                std::cout << ".";
                last_symbol = ".";

                while(i < numbers.size()) {
                    last_symbol = numbers[i];
                    std::cout << numbers[i++];
                }

            }
        }

        else {
            std::cout << "0.";
            last_symbol =  "0.";
            long size = numbers.size();

            for (long i = 0; i < -exponent - 1; i++) {
                std::cout << "0";
                last_symbol =  "0";
            }

            for (int i = 0; i < numbers.size(); i++) {
                std::cout << numbers[i];
                last_symbol = numbers[i];
            }

        }

    }

};

Long_long addition (Long_long& number_1, Long_long& number_2);
Long_long subtraction(Long_long& number_1, Long_long& number_2);
bool smaller (Long_long& number_1, Long_long& number_2);
bool smaller_equal (Long_long& number_1, Long_long& number_2);
bool not_equal (Long_long& number_1, Long_long& number_2);
bool bigger_equal (Long_long& number_1, Long_long& number_2);

Long_long inverted_number (Long_long& number) {
    if (number.numbers.size() == 1 && number.numbers[0] == 0) {
        std::cout << "Wrong input";
    }

    const int accuracy = 1000;

    Long_long local_number;
    local_number.copypaste(number);
    local_number.sign = 1;

    Long_long dividend;
    dividend.enter_from_string("1");

    Long_long something;
    something.enter_from_string("1");

    Long_long result;
    result.sign = number.sign;
    result.exponent = 1;
    result.numbers = std::vector<int>();

    while (smaller(local_number, something)) {
        local_number.exponent++;
        result.exponent++;
    }

    while (smaller(dividend, local_number)) {
        dividend.exponent++;
    }

    result.exponent -= dividend.exponent - 1;

    int numbers = 0;
    int total_numbers = accuracy + std::max((long) 0, result.exponent);
    Long_long zero;
    zero.enter_from_string("0");

    do {
        int div = 0;

        while (bigger_equal(dividend, local_number)) {
            div++;
            dividend = subtraction(dividend, local_number);
        }

        dividend.exponent++;
        dividend.del_zeroes();
        result.numbers.push_back(div);
        numbers++;
    } while (not_equal(dividend, zero) && numbers < total_numbers);

    result.exponent--;
    result.exponent--;
    return result;
}

bool bigger (Long_long& number_1, Long_long& number_2) {
    if (number_1.sign != number_2.sign)
        return number_1.sign > number_2.sign;

    if (number_1.exponent != number_2.exponent) {

        if (number_1.exponent == 1 && number_1.numbers[0] == 0 && number_1.numbers.size() == 1 && number_1.exponent > number_2.exponent) {

            if (number_2.sign > 0) {
                return false;
            }

            else {
                return true;
            }

        }

        else if (number_2.exponent == 1 && number_2.numbers[0] == 0 && number_2.numbers.size() == 1 && number_2.exponent > number_1.exponent) {

            if (number_1.sign > 0) {
                return true;
            } else {
                return false;
            }
        }

        else {

            if (number_1.sign != -1) {
                return number_1.exponent > number_2.exponent;
            }

            else if (number_1.sign == -1) {
                return number_1.exponent < number_2.exponent;
            }

        }

    }

    std::vector<int> vector_1(number_1.numbers);
    std::vector<int> vector_2(number_2.numbers);
    int size = std::max(vector_1.size(), vector_2.size());

    while (vector_1.size() != size) {
        vector_1.push_back(0);
    }

    while (vector_2.size() != size) {
        vector_2.push_back(0);
    }

    for (int i = 0; i < size; i++) {
        if (vector_1[i] != vector_2[i]) {

            if (number_1.sign != -1) {
                return (vector_1[i] > vector_2[i]);
            }

            else if (number_1.sign == -1) {
                return (vector_1[i] < vector_2[i]);
            }
        }

    }
    return false;
}

bool smaller (Long_long& number_1, Long_long& number_2) {
    if (number_1.sign != number_2.sign)
        return number_1.sign < number_2.sign;

    if (number_1.exponent != number_2.exponent) {

        if (number_1.exponent == 1 && number_1.numbers[0] == 0 && number_1.numbers.size() == 1 && number_1.exponent > number_2.exponent) {

            if (number_2.sign > 0) {
                return true;
            }

            else {
                return false;
            }

        }

        else if (number_2.exponent == 1 && number_2.numbers[0] == 0 && number_2.numbers.size() == 1 && number_2.exponent > number_1.exponent) {

            if (number_1.sign > 0) {
                return false;
            }

            else {
                return true;
            }

        }

        else {

            if (number_1.sign != -1) {
                return number_1.exponent < number_2.exponent;
            }

            else if (number_1.sign == -1) {
                return number_1.exponent > number_2.exponent;
            }
        }
    }

    std::vector<int> vector_1(number_1.numbers);
    std::vector<int> vector_2(number_2.numbers);
    int size = std::max(vector_1.size(), vector_2.size());

    while (vector_1.size() != size) {
        vector_1.push_back(0);
    }

    while (vector_2.size() != size) {
        vector_2.push_back(0);
    }

    for (int i = 0; i < size; i++) {
        if (vector_1[i] != vector_2[i]) {

            if (number_1.sign != -1) {
                return (vector_1[i] < vector_2[i]);
            }

            else if (number_1.sign == -1) {
                return (vector_1[i] > vector_2[i]);
            }
        }

    }
    return false;
}

bool equal(Long_long& number_1, Long_long& number_2) {

    if (number_1.sign != number_2.sign) {
        return false;
    }

    if (number_1.exponent != number_2.exponent) {
        return false;
    }

    if (number_1.numbers.size() != number_2.numbers.size()) {
        return false;
    }

    for (int i = 0; i < number_1.numbers.size(); i++) {

        if (number_1.numbers[i] != number_2.numbers[i]) {
            return false;
        }

    }

    return true;

}

bool not_equal (Long_long& number_1, Long_long& number_2) {
    return !(equal(number_1, number_2));
}

bool bigger_equal (Long_long& number_1, Long_long& number_2) {
    return ((equal(number_1, number_2)) || (bigger(number_1, number_2)));
}

bool smaller_equal (Long_long& number_1, Long_long& number_2) {
    return ((equal(number_1, number_2)) || (smaller(number_1, number_2)));
}

Long_long multiplication (Long_long& number_1, Long_long& number_2) {

    int size = number_1.numbers.size() + number_2.numbers.size();

    Long_long answer_m;

    answer_m.sign = number_1.sign * number_2.sign;
    answer_m.numbers = std::vector<int>(size, 0);

    if (number_1.exponent >= 0 && number_2.exponent >= 0) {
        answer_m.exponent = (number_1.exponent + 1) * (number_2.exponent + 1);
    }

    else if (number_1.exponent < 0 && number_2.exponent < 0) {
        answer_m.exponent = -1 * (number_1.exponent) * (number_2.exponent);
    }

    else if (number_1.exponent >= 0 && number_2.exponent < 0) {
        answer_m.exponent = -1 * number_1.exponent + number_2.exponent + 1;
    }

    else if (number_2.exponent >= 0 && number_1.exponent < 0) {
        answer_m.exponent = -1 * number_2.exponent + number_1.exponent + 1;
    }

    for (int i = 0; i < number_1.numbers.size(); i++)
        for (int j = 0; j < number_2.numbers.size(); j++)
            answer_m.numbers[i + j + 1] += number_1.numbers[i] * number_2.numbers[j];

    for (int i = size - 1; i > 0; i--) {
        answer_m.numbers[i - 1] += answer_m.numbers[i] / 10;
        answer_m.numbers[i] %= 10;
    }

    answer_m.del_zeroes();

    return answer_m;
}

Long_long subtraction(Long_long& number_1, Long_long& number_2) {

    if (number_1.sign == 1 && number_2.sign == 1) {
        bool key = bigger(number_1, number_2);
        long exponent_1 = number_1.exponent;
        long exponent_2 = number_2.exponent;
        long exponent = std::max(exponent_1, exponent_2);

        std::vector<int> vector_1(number_1.numbers);
        std::vector<int> vector_2(number_2.numbers);

        while (exponent_1 != exponent) {
            vector_1.insert(vector_1.begin(), 0);
            exponent_1++;
        }

        while (exponent_2 != exponent) {
            vector_2.insert(vector_2.begin(), 0);
            exponent_2++;
        }

        int size = std::max(vector_1.size(), vector_2.size());

        while (vector_1.size() != size) {
            vector_1.push_back(0);
        }

        while (vector_2.size() != size) {
            vector_2.push_back(0);
        }

        int len = 1 + size;

        Long_long answer_s;

        if (key) {
            answer_s.sign = 1;
        }

        else {
            answer_s.sign = -1;
        }

        answer_s.numbers = std::vector<int>(len, 0);

        for (int i = 0; i < size; i++) {
            answer_s.numbers[i + 1] = vector_1[i] - vector_2[i];
        }

        for (int i = len - 1; i > 0; i--) {

            if (answer_s.numbers[i] < 0) {
                answer_s.numbers[i] += 10;
                answer_s.numbers[i - 1]--;
            }

        }

        answer_s.exponent = exponent + 1;
        answer_s.del_zeroes();

        return answer_s;
    }

    else if (number_1.sign == -1 && number_2.sign == -1) {
        number_1.sign *= -1;
        number_2.sign *= -1;
        return subtraction(number_2, number_1);
    }

    else {
        number_2.sign *= -1;
        return addition(number_1, number_2);
    }

}

Long_long addition (Long_long& number_1, Long_long& number_2) {

    if (number_1.sign == number_2.sign) {
        long exponent_1 = number_1.exponent;
        long exponent_2 = number_2.exponent;
        long exponent = std::max(exponent_1, exponent_2);

        std::vector<int> vector_1(number_1.numbers);
        std::vector<int> vector_2(number_2.numbers);

        while (exponent_1 != exponent) {
            vector_1.insert(vector_1.begin(), 0);
            exponent_1++;
        }

        while (exponent_2 != exponent) {
            vector_2.insert(vector_2.begin(), 0);
            exponent_2++;
        }

        int size = std::max(vector_1.size(), vector_2.size());

        while (vector_1.size() != size) {
            vector_1.push_back(0);
        }

        while (vector_2.size() != size) {
            vector_2.push_back(0);
        }

        int len = 1 + size;

        Long_long answer_a;

        answer_a.sign = number_1.sign;
        answer_a.numbers = std::vector<int>(len, 0);

        for (int i = 0; i < size; i++) {
            answer_a.numbers[i + 1] = vector_1[i] + vector_2[i];
        }

        for (int i = len - 1; i > 0; i--) {
            answer_a.numbers[i - 1] += answer_a.numbers[i] / 10;
            answer_a.numbers[i] %= 10;
        }

        answer_a.exponent = exponent + 1;
        answer_a.del_zeroes();

        return answer_a;
    }

    else if (number_1.sign == -1) {
        number_1.sign *= -1;
        return subtraction(number_2, number_1);
    }

    else {
        number_2.sign *= -1;
        return subtraction(number_1, number_2);
    }

}

void division(Long_long& number_1, Long_long& number_2) {

    Long_long local_number = inverted_number(number_2);
    Long_long answer_d = multiplication(number_1, local_number);

    int i = answer_d.numbers.size() - 1 - std::max((long)0, number_1.exponent);
    int n = std::max((long) 0, answer_d.exponent);

    if (i > n && answer_d.numbers[i] == 9) {
        while (i > n && answer_d.numbers[i] == 9)
            i--;

        if (answer_d.numbers[i] == 9) {
            answer_d.numbers.erase(answer_d.numbers.begin() + n, answer_d.numbers.end());

            if (answer_d.sign == -1) {
                Long_long minus;
                minus.enter_from_string("-1");
                answer_d = addition(answer_d, minus);
            }

            else {
                Long_long plus;
                plus.enter_from_string("1");
                answer_d = addition(answer_d, plus);
            }
        }

        else {
            answer_d.numbers.erase(answer_d.numbers.begin() + i + 1, answer_d.numbers.end());
            answer_d.numbers[i]++;
        }

    }

    answer_d.printing();
}

void solving (Long_long& number_1, std::string string, Long_long& number_2) {

    if (string == "*") {
        Long_long answer_loc = multiplication(number_1, number_2);
        answer_loc.printing();
    }

    else if (string == "+") {
        Long_long answer_loc = addition(number_1, number_2);
        answer_loc.printing();
    }

    else if (string == "/") {
        division(number_1, number_2);
    }

    else if (string == "-") {
        Long_long answer_loc = subtraction(number_1, number_2);
        answer_loc.printing();
    }

    else if (string == "==") {
        equal(number_1, number_2);
    }

    else if (string == "!=") {
        not_equal(number_1, number_2);
    }

    else if (string == ">") {
        std::cout << bigger(number_1, number_2);
    }

    else if (string == "<") {
        std::cout << smaller(number_1, number_2);
    }

    else if (string == ">=") {
        bigger_equal(number_1, number_2);
    }

    else if (string == "<=") {
        smaller_equal(number_1, number_2);
    }

}


int main () {

    Long_long number_1, number_2;
    std::string string_1, string_2, operation;

    std::cout << "Please, enter the first number: " << std::endl;
    std::cin >> string_1;

    std::cout << "Please, enter operation: " << std::endl;
    std::cin >> operation;

    std::cout << "Please, enter the second number: " << std::endl;
    std::cin >> string_2;

    number_1.enter_from_string(string_1);
    number_2.enter_from_string(string_2);

    solving(number_1, operation, number_2);

    return 0;
}

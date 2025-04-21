#include <iostream>

#include <string>

#include <cctype>

#include <vector>

using namespace std;

bool is_digit(char c);

bool sign(char c);

bool unsigned_integer(const string& str);

bool order(const string& str);

bool is_mantissa(const string& str);

bool is_material(const string& str);

int main() {
    vector <string> test_strings = {

        "123.45E+6",
        "-0.001E-3",
        "3.14",
        "42",
        "abc",
        "E+123",
        "-E-456"
    };
 

    for (const auto& testing_string : test_strings) {
        bool result = is_material(testing_string);
        cout << "String: \"" << testing_string << "\", Result: " << boolalpha << result << endl; 
    }
}

bool is_digit(char c) {
    return string("0123456789").find(c) != string::npos;
}

bool sign(char c) {
    if (c == '+' || c == '-') {
        return true;
    }
    else {
        return false;
    }
}

bool unsigned_integer(const string& str) {
    if (str.empty()) {
        return false;
    }
    if (is_digit(str[0])) {
        return true;
    }

    else if (is_digit(str[0]) && unsigned_integer(str.substr(1))) {
        return true;
    }
    else {
        return false;
    }
}

bool order(const string& str) {
    if (str.size() > 1 && str[0] == 'E') {
        string rest_of_string = str.substr(1);
        if (sign(rest_of_string[0]) && unsigned_integer(rest_of_string.substr(1))) {
            return true;
        }

    }
    return false;
}

bool is_mantissa(const string& str) {
    if (unsigned_integer(str)) {
        return true;
    }
    size_t dot_position = str.find('.');
    if (dot_position != string::npos) {
        string start_part = str.substr(0, dot_position);
        string end_part = str.substr(dot_position + 1); // îò ýëåìåíòà òî÷êè +1 è äî êîíöà
        if (!start_part.empty() && is_digit(start_part[0]) && unsigned_integer(start_part) && unsigned_integer(end_part)) {
            return true;
        }
    }
    else {
        return false;
    }
}

bool is_material(const string& str) {
    if (is_mantissa(str)) {
        return true;
    }
    else if (!str.empty() && (sign(str[0])) && is_mantissa(str.substr(1)) && order(str.substr(1 + to_string(stod(str.substr(1))).size()))) {
        return true;

    }

    return false;

}







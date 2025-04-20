#include <iostream>

#include <string>

#include <cctype>

#include <vector>

using namespace std;

bool is_cyfra(char c);

bool znak(char c);

bool is_cheloe_bez_znaka(const string& str);

bool poryadok(const string& str);

bool is_mantissa(const string& str);

bool is_veshchestvennoe(const string& str);

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
        bool result = is_veshchestvennoe(testing_string);
        cout << "String: \"" << testing_string << "\", Result: " << boolalpha << result << endl; 
    }
}

bool is_cyfra(char c) {
    return string("0123456789").find(c) != string::npos;
}

bool znak(char c) {
    if (c == '+' || c == '-') {
        return true;
    }
    else {
        return false;
    }
}

bool is_cheloe_bez_znaka(const string& str) {
    if (str.empty()) {
        return false;
    }
    if (is_cyfra(str[0])) {
        return true;
    }

    else if (is_cyfra(str[0]) && is_cheloe_bez_znaka(str.substr(1))) {
        return true;
    }
    else {
        return false;
    }
}

bool poryadok(const string& str) {
    if (str.size() > 1 && str[0] == 'E') {
        string rest_of_string = str.substr(1);
        if (znak(rest_of_string[0]) && is_cheloe_bez_znaka(rest_of_string.substr(1))) {
            return true;
        }

    }
    return false;
}

bool is_mantissa(const string& str) {
    if (is_cheloe_bez_znaka(str)) {
        return true;
    }
    size_t dot_position = str.find('.');
    if (dot_position != string::npos) {
        string start_part = str.substr(0, dot_position);
        string end_part = str.substr(dot_position + 1); // от элемента точки +1 и до конца
        if (!start_part.empty() && is_cyfra(start_part[0]) && is_cheloe_bez_znaka(start_part) && is_cheloe_bez_znaka(end_part)) {
            return true;
        }
    }
    else {
        return false;
    }
}

bool is_veshchestvennoe(const string& str) {
    if (is_mantissa(str)) {
        return true;
    }
    else if (!str.empty() && (znak(str[0])) && is_mantissa(str.substr(1)) && poryadok(str.substr(1 + to_string(stod(str.substr(1))).size()))) {
        return true;

    }

    return false;

}







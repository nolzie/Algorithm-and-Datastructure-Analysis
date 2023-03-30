#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

std::string subtract(std::string i1, std::string i2, int b){
    int zeros = std::max(i1.length(), i2.length()) - std::min(i1.length(), i2.length());
    if (i1.length() > i2.length()) {
        i2.insert(0, zeros, '0');
    } else {
        i1.insert(0, zeros, '0');
    }
    
    std::string result;
    int borrow = 0;
    for (int i = i1.length() - 1; i >= 0; i--) {
        int digit_i1 = i1[i] - '0';
        int digit_i2 = i2[i] - '0';
        int diff = digit_i1 - digit_i2 - borrow;
        if (diff < 0) {
            diff += b;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.insert(0, std::to_string(diff));
    }
    
    while (result.length() > 1 && result[0] == '0') {
        result.erase(0, 1);
    }
    
    return result;
}

std::string add_school(std::string i1, std::string i2, int b){
    if (i1.length() > i2.length()){
        
        int zeros = i1.length() - i2.length();
        for (int i =0; i < zeros; i++){
            i2.insert(0,"0");
        }
    } else if (i1.length() < i2.length()){
        
        int zeros = i2.length() - i1.length();
        for (int i =0; i < zeros; i++){
            i1.insert(0,"0");
        }
    }

    int carry = 0;
    std::string sum;
    for (int i = i1.length() -1; i >= 0; i--){
        int digit_sum = (i1[i] - '0') + (i2[i] - '0') + carry;
        carry = digit_sum / b;
        digit_sum = digit_sum % b;
        sum = std::to_string(digit_sum) + sum;
    }

    if (carry != 0) {
        sum = std::to_string(carry) + sum;
    }

    return sum;
}

int char_to_digit(char c, int base) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else {
        throw std::invalid_argument("Invalid character");
    }
}

char digit_to_char(int digit, int base) {
    if (digit >= 0 && digit <= 9) {
        return '0' + digit;
    } else {
        throw std::invalid_argument("Invalid digit");
    }
}

int from_base(std::string s, int base) {
    // converts a number some input base to base 10
    int result = 0;
    for (char c : s) {
        int digit = char_to_digit(c, base);
        result = result * base + digit;
    }
    return result;
}

std::string to_base(int n, int base) {
    // converts a number in base 10 to some base provided
    if (n == 0) {
        return "0";
    }
    std::string result;
    while (n > 0) {
        int digit = n % base;
        result.insert(0, 1, digit_to_char(digit, base));
        n /= base;
    }
    return result;
}

std::string karatsuba_multiply(std::string i1, std::string i2, int b){

    int n = std::max(i1.length(), i2.length());
    i1 = i1.insert(0, n - i1.length(), '0');
    i2 = i2.insert(0, n - i2.length(), '0');

    if (n <= 1) {
        int product = from_base(i1, b) * from_base(i2, b);
        return to_base(product, b);
    }

    int k = n / 2;
    std::string i1_left = i1.substr(0, k);
    std::string i1_right = i1.substr(k);
    std::string i2_left = i2.substr(0, k);
    std::string i2_right = i2.substr(k);

    std::string z2 = karatsuba_multiply(i1_left, i2_left, b);
    std::string z0 = karatsuba_multiply(i1_right, i2_right, b);
    std::string z1 = karatsuba_multiply(add_school(i1_left, i1_right, b), add_school(i2_left, i2_right, b), b);
    z1 = subtract(z1, z0, b);
    z1 = subtract(z1, z2, b);

    std::string s_z2 = z2.insert(z2.length(), 2 * (n - k), '0');
    std::string s_z1 = z1.insert(z1.length(), n - k, '0');
    std::string s_i1_i2 = add_school(add_school(s_z2, s_z1, b), z0, b);

    return s_i1_i2.erase(0, std::min(s_i1_i2.find_first_not_of('0'), s_i1_i2.size()-1));
}


int main(){
    std::string i1, i2;
    int b;
    std::cin >> i1 >> i2 >> b;

    std::string sum = add_school(i1,i2,b);
    std::string product = karatsuba_multiply(i1,i2,b);
    std::string quotient = "0";

    std::cout << sum << " " << product << " " << quotient << std::endl;

    return 0;
}
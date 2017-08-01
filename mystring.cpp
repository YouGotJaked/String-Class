#include <iostream>
#include <cassert>
#include "mystring.h"

namespace coen70_lab5 {

    // CONSTRUCTORS and DESTRUCTOR

    string::string(const char str[ ]) {
        allocated = 0;
        current_length = strlen(str);
        sequence = NULL;
        reserve(current_length + 1);
        sequence[0] = '\0';
        strncpy(sequence, str, allocated);
    }

    string::string(const string& source) {
        current_length = source.current_length;
        reserve(current_length + 1);
        strncpy(sequence, source.sequence, allocated);
    }

    string::~string() {
        delete[] sequence;
    }

    // MODIFICATION MEMBER FUNCTIONS

    void string::operator+=(const string& addend) {
        reserve(current_length + addend.length() + 1);
        strncat(sequence, addend.sequence, allocated - current_length);
        current_length += addend.length();
    }

    void string::operator+=(const char addend[ ]) {
        string res(addend);
        *this += res;
    }

    void string::operator+=(char addend) {
        char tmp[2];
        tmp[0] = addend;
        tmp[1] = '\0';
        string res(tmp);
        *this += res;
    }

    void string::reserve(size_t n) {
        //don't reserve memory if allocated is already the right size
        if (n != allocated) {
            //don't allocate less than what's being used
            if (n < allocated) {
                n = allocated;
            }
            char *temp = sequence;
            sequence = new char[n];
            assert(sequence != NULL);

            if (temp != NULL) {
                strncpy(sequence, temp, n);
                delete[] temp;
            }
            allocated = n;
        }
    }

    void string::operator=(const string& source) {
        //don't self copy
        if (this != &source) {
            current_length = source.current_length;
            allocated = source.allocated;
            strncpy(sequence, source.sequence, allocated);
        }
    }

    void string::insert(const string& source, unsigned int position) {
        assert(position <= length());

        string newStr;
        newStr.reserve(current_length + source.current_length + 1);

        current_length += source.current_length;
        for (int i = 0; i < position; i++) {
            newStr += sequence[i];
        }

        newStr += source;

        char c = sequence[position];
        while (c != '\0') {
            newStr += c;
            c = sequence[++position];
        }
        newStr += '\0';
        *this = newStr;
    }

    void string::replace(char c, unsigned int position) {
        assert(position < length());

        sequence[position] = c;
    }

    // CONSTANT MEMBER FUNCTIONS

    char string::operator[ ](size_t position) const {
        assert(position < length());

        return sequence[position];
    }

    int string::search(char c) const {
        for (int i = 0; i < current_length; i++) {
            if (c == sequence[i]) {
                return i;
            }
        }
        return -1; //not found
    }

    unsigned int string::count(char c) const {
        int count = 0;

        for (int i = 0; i < current_length; i++) {
            if (c == sequence[i]) {
                count++;
            }
        }
        return count;
    }

    // FRIEND FUNCTIONS

    std::ostream& operator<<(std::ostream& outs, const string& source) {
        outs << source.sequence;
        return outs;
    }

    bool operator==(const string& s1, const string& s2) {
        return (strcmp(s1.sequence, s2.sequence) == 0);
    }

    bool operator!=(const string& s1, const string& s2) {
        return !(s1 == s2);
    }

    bool operator>=(const string& s1, const string& s2) {
        return (s1 > s2 || s1 == s2);
    }

    bool operator<=(const string& s1, const string& s2) {
        return (s1 < s2 || s1 == s2);
    }

    bool operator>(const string& s1, const string& s2) {
        return (strcmp(s1.sequence, s2.sequence) > 0);
    }

    bool operator<(const string& s1, const string& s2) {
        return (strcmp(s1.sequence, s2.sequence) < 0);
    }

    // NON-MEMBER FUNCTIONS for the string class

    string operator+(const string& s1, const string& s2) {
        string s3;

        s3 += s1;
        s3 += s2;

        return s3;
    }

    std::istream& operator>>(std::istream& ins, string& target) {
        //ignore white space
        while (ins && isspace(ins.peek())) {
            ins.ignore();
        }

        char tmp;

        //clear target
        target = "";

        //read from stream
        while (ins && !isspace(ins.peek())) {
            ins >> tmp;
            target += tmp;
        }
        return ins;
    }

    void getline(std::istream& ins, string& target, char delimiter) {
        delimiter = '\n';

        char tmp;
        int count = 0;

        while (ins && isspace(ins.peek())) {
            ins.ignore();
        }

        while (ins && target[count] != delimiter) {
            ins >> tmp;
            count++;
        }
    }
}

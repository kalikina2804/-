#ifndef POLAND_H
#define POLAND_H

#endif // POLAND_H
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

inline double r;
struct Stack{
    double num;
    char znak;
    Stack * next;
};

Stack * top1 = nullptr, * top2 = nullptr;

int prior(char ch) {
    if (ch == '+' || ch == '-'){
        return 1;
    }
    if (ch == '/' || ch == '*') {
        return 2;
    }
    if (ch == '(') {
        return 0;
    }
    if (ch == '^'){
        return 3;
    }
    return -1;
}

void push(Stack * &t, double n, char ch) {
    Stack * p = (Stack*)malloc(sizeof(Stack));
    (*p).num = n;
    (*p).znak = ch;
    (*p).next = t;
    t = p;
}

Stack pop(Stack * &t){
    Stack * p = (Stack*)malloc(sizeof(Stack));
    p = t;
    t = (*t).next;
    return *p;
}

bool apply(char znak){
    if (znak == 'S' || znak == 'C' || znak == 'T' || znak == 'Q' || znak == 'L' || znak == 'A'){
        double x = pop(top1).num;
        if (znak == 'S') push(top1, sin(x), '@');
        else if (znak == 'C') push(top1, cos(x), '@');
        else if (znak == 'T') push(top1, tan(x), '@');
        else if (znak == 'A') push(top1, abs(x), '@');
        else if (znak == 'Q'){
            if (x < 0) {
                // cout << "Error." << '\n';
                return false;
            }
            push(top1, sqrt(x), '@');
        }
        else if (znak == 'L'){
            if (x <= 0) {
                // cout << "Error." << '\n';
                return false;
            }
            push(top1, log(x), '@');
        }
        return true;
    }
    if (top1 == nullptr || top1->next == nullptr) return false;
    double scnd = pop(top1).num;
    double frst = pop(top1).num;
    if (znak == '+'){
        push(top1, frst + scnd, '@');
        return true;
    }
    else if (znak == '-'){
        push(top1, frst - scnd, '@');
        return true;
    }
    else if (znak == '*'){
        push(top1, frst * scnd, '@');
        return true;
    }
    else if (znak == '/'){
        if (scnd == 0){
            // cout << "Error." << endl;
            return false;
        }
        push(top1, frst / scnd, '@');
        return true;
    }
    else if (znak == '^'){
        push(top1, pow(frst, scnd), '@');
        return true;
    }

    return false;
}

bool error(string s){
    int balance = 0;
    for (int i = 0; i < s.size(); i++){
        if (s[i] == '('){
            balance++;
        }
        else if(s[i] == ')'){
            balance--;
        }
        if (balance < 0){
            return true;
        }
    }
    if (balance != 0){
        return true;
    }

    if (!isdigit(s[0]) && s[0] != '(' && s[0] != 'S' && s[0] != 'C' && s[0] != 'T' && s[0] != 'Q' && s[0] != 'L' && s[0] != 'A') return true;

    for (int i = 1; i < s.size(); i++){
        if (isdigit(s[i - 1]) && s[i] == '(') {
            // cout << 1 << ' ';
            return true;
        }
        else if (isdigit(s[i]) && s[i - 1] == ')') {
            // cout << 2 << ' ';
            return true;
        }
        else if (s[i - 1] == '(' && !isdigit(s[i]) && s[i] !='.' && s[i] != '-' && s[i] != '(' && s[i] != 'S' && s[i] != 'C' && s[i] != 'T' && s[i] != 'Q' && s[i] != 'L' && s[i] != 'A'){
            // cout << 3 << ' ';
            return true;
        }
        else if (s[i] == ')' && !isdigit(s[i - 1]) && s[i] !='.' && s[i] != ')'){
            // cout << 4 << ' ';
            return true;
        }
        else if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && (s[i - 1] == '+' || s[i - 1] == '-' || s[i - 1] == '*' || s[i - 1] == '/')){
            // cout << 5 << ' ';
            return true;
        }
        else if (!isdigit(s[i]) && s[i] !='.' && s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '(' && s[i] != ')' && s[i] != '^' && s[i] != 'S' && s[i] != 'C' && s[i] != 'T' && s[i] != 'Q' && s[i] != 'L'  && s[i] != 'A'){
            // cout << 6 << ' ';
            return true;
        }
    }

    if (!isdigit(s[s.size() - 1]) && s[s.size() - 1] != ')') return true;

    return false;
}


string replase(string s, string f, char t){
    string ans = "";
    if (s.size() < f.size()) return s;
    for (int i = 0; i < s.size(); i++){
        if(i + (int)f.size() <= s.size() && s.substr(i, f.size()) == f) {
            ans += t;
i += (int)f.size() - 1;
        }
        else {
            ans += s[i];
        }
        //i += f.size() - 1;
    }
    //cout << ans << '\n';
    return ans;
}

double calculate (string fs, double &p){
string outspace = "";
    for (char c : fs) {
        if (c != ' ') outspace += c;
    }
    fs = outspace;

    if (fs[0] == '-') fs = "0" + fs;

    fs = replase(fs, "sqrt", 'Q');
    fs = replase(fs, "sin", 'S');
    fs = replase(fs, "cos", 'C');
    fs = replase(fs, "tg", 'T');
    fs = replase(fs, "ln", 'L');
    fs = replase(fs, "abs", 'A');


    if (error(fs)){
        //cout << "Error." << endl;
        return 0;
    }

    string s = "";
    s += fs[0];
    for (int i = 1; i < fs.size(); i++){
        if (fs[i] == '-' && fs[i - 1] == '(') s = s + "0";
        s += fs[i];
    }




    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) {
            string number = "";
            while (isdigit(s[i])) {
                number += s[i];
                i++;
            }
            if (s[i] == '.'){
                number += s[i];
                i++;
                while (isdigit(s[i])) {
                number += s[i];
                i++;
            }
            }
            i--;
            push(top1, stod(number), '@');
        }
        else if (s[i] == '('){
            push(top2, 0, '(');
        }
        else if (s[i] == ')'){
            while (top2 != nullptr && (*top2).znak != '('){
                if (!apply(pop(top2).znak)){
                 //   cout << "Error." << '\n';
                    return 0;
                }
            }
            pop(top2);

            if (top2 != nullptr && ((*top2).znak == 'S' || (*top2).znak == 'C' || (*top2).znak == 'T' || (*top2).znak == 'Q' || (*top2).znak == 'L' || (*top2).znak == 'A' )) {
                if (!apply(pop(top2).znak)) {
                 //   cout << "Error." << '\n';
                    return 0;
                }
            }
        }
        else if (s[i] == 'S' || s[i] == 'C' || s[i] == 'T' || s[i] == 'L' || s[i] == 'Q' || s[i] == 'A') {
            push(top2, 0, s[i]);
        }
        else {
            while (top2 != nullptr && prior((*top2).znak) >= prior(s[i])){
                if (!apply(pop(top2).znak)){
                  //  cout << "Error." << '\n';
                    return 0;
                }
            }
            push(top2, 0, s[i]);
        }
    }

    while (top1 != nullptr && (*top1).next != nullptr){
        if (top2 == nullptr) {
            //cout << "Error." << endl;
            return 0;
        }
        if (!apply(pop(top2).znak)){
           // cout << "Error." << '\n';
            return 0;
        }
    }
    p = pop(top1).num;   // cout << fixed << r << endl;
    return 1;

}



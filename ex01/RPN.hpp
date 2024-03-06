#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <stack>
#include <string>
class RPN
{
    private:
        std::string _expression;
        std::stack<int> stack;
        int _a;
        int _b;
        int _result;
    public:
        RPN(std::string expression);
        ~RPN();
        void calculate();
};
#endif
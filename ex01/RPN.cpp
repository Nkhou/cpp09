#include "RPN.hpp"

RPN::RPN(std::string expression) : _expression(expression)
{
}

RPN::~RPN()
{
}
void RPN::calculate()
{
   size_t pos = 0;
    while ((pos = _expression.find(" " , pos)) != std::string::npos)
    {
        std::cout << _expression.substr(0, pos) << std::endl;
        if (_expression[pos + 1] == '+' || _expression[pos + 1] == '-' || _expression[pos + 1] == '*' || _expression[pos + 1] == '/' || _expression[pos + 1] == '%')
        {
            _b = stack.top();
            stack.pop();
            _a = stack.top();
            stack.pop();
            if (_expression[pos + 1] == '+')
                _result = _a + _b;
            else if (_expression[pos + 1] == '-')
                _result = _a - _b;
            else if (_expression[pos + 1] == '*')
                _result = _a * _b;
            else if (_expression[pos + 1] == '/')
                _result = _a / _b;
            else if (_expression[pos + 1] == '%')
                _result = _a % _b;
            stack.push(_result);
        }
        else
            stack.push(std::stoi(_expression.substr(0, pos)));
        // stack.push(std::stoi(_expression.substr(0, pos)));
    }
}
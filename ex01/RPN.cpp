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
   (void)_a;
    (void)_b;
    (void)_result;
    while ((pos = _expression.find(" " , pos)) != std::string::npos)
    {
        if (( _expression[pos + 1] == '+' || _expression[pos + 1] == '-' || _expression[pos + 1] == '*' || _expression[pos + 1] == '/' ))
        {
            if (stack.empty())
                throw std::runtime_error("Invalid expression");
            _b = stack.top();
            stack.pop();
            if (stack.empty())
            {
                _a = _result;
            }
            else
            {
                _a = stack.top();
                stack.pop();
            }
            if (_expression[pos + 1] == '+')
                _result = _a + _b;
            else if (_expression[pos + 1] == '-')
                _result = _a - _b;
            else if (_expression[pos + 1] == '*')
                _result = _a * _b;
            else if (_expression[pos + 1] == '/')
                _result = _a / _b;
            stack.push(_result);
        }
        else
            stack.push(std::stoi(_expression.substr(0, pos)));
        pos++;
        // stack.push(std::stoi(_expression.substr(0, pos)));
    }
    std::cout << "Result: " << _result << std::endl;
}
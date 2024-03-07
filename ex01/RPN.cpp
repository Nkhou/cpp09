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
   size_t pos2 = 0;
   (void)_a;
    (void)_b;
    (void)_result;
    while (_expression[pos] != '\0')
    {
        if (_expression[pos] != ' ' && _expression[pos] != '+' && _expression[pos] != '-' && _expression[pos] != '*' && _expression[pos] != '/')
        {
            if (_expression[pos] < '0' || _expression[pos] > '9')
                throw std::runtime_error("Error");
        }
        if (_expression[pos] == ' ')
        {
            if (_expression[pos - 1] >= '0' && _expression[pos - 1] <= '9')
            {
                stack.push(std::stoi(_expression.substr(pos2, pos - pos2)));
                pos2 = pos + 1;
            }
            else
            {
                if (stack.size() < 2)
                throw std::runtime_error("Invalid expression");
                _b = stack.top();
                stack.pop();
                _a = stack.top();
                stack.pop();
                if (_expression[pos -1 ] == '+')
                    _result = _a + _b;
                else if (_expression[pos - 1] == '-')
                    _result = _a - _b;
                else if (_expression[pos -1 ] == '*')
                {
                    _result = _a * _b;
                }
                else if (_expression[pos - 1] == '/')
                    _result = _a / _b;
                else
                    throw std::runtime_error("Error");
                stack.push(_result);
                pos2 = pos + 1;
            }
        }
        pos++;
    }
    if (_expression[pos - 1] != ' ')
    {
        if (_expression[pos - 1] >= '0' && _expression[pos - 1] <= '9')
        {
            stack.push(std::stoi(_expression.substr(pos2, pos - pos2)));
        }
        else
        {
            if (stack.size() < 2)
                throw std::runtime_error("Error");
            _b = stack.top();
            stack.pop();
            _a = stack.top();
            stack.pop();
            if (_expression[pos -1 ] == '+')
                _result = _a + _b;
            else if (_expression[pos - 1] == '-')
                _result = _a - _b;
            else if (_expression[pos -1 ] == '*')
            {
                _result = _a * _b;
            }
            else if (_expression[pos - 1] == '/')
                _result = _a / _b;
            else
                throw std::runtime_error("Error");
            stack.push(_result);
        }
    }
    if (stack.size() != 1)
    {
        throw std::runtime_error("Error");
    }
    std::cout << _result << std::endl;
}
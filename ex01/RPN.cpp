#include "RPN.hpp"

RPN::RPN(std::string expression) : _expression(expression)
{
}
RPN::RPN()
{
}
RPN::RPN(const RPN& rpn)
{
    _expression = rpn._expression;
    stack = rpn.stack;
    _a = rpn._a;
    _b = rpn._b;
    _result = rpn._result;
}
RPN& RPN::operator=(const RPN& rpn)
{
    if (this != &rpn)
    {
        _expression = rpn._expression;
        stack = rpn.stack;
        _a = rpn._a;
        _b = rpn._b;
        _result = rpn._result;
    }
    return *this;
}
RPN::~RPN()
{
}
void RPN::checkExpression()
{
    size_t pos = 0;
    std::string str;
    while (_expression[pos] != '\0')
    {
        if (_expression[pos] == ' ' && _expression[pos + 1] == ' ')
        {
            pos++;
            continue;
        }
        if (_expression[pos] >= '0' && _expression[pos] <= '9')
        {
           if (_expression[pos + 1] && (_expression[pos + 1] == '+' || _expression[pos + 1] == '-' || _expression[pos + 1] == '*' || _expression[pos + 1] == '/'))
           {
               str = str + _expression[pos];
               str = str + ' ';
           }
           else
            str = str + _expression[pos];
        }
        else if (_expression[pos + 1] && _expression[pos + 1] != ' ' && (_expression[pos] == '+'
        || _expression[pos] == '-' || _expression[pos] == '*' || _expression[pos] == '/'))
        {
               str = str + _expression[pos];
               str = str + ' ';
        }
        else
            str = str + _expression[pos];
        pos++;
    }
    _expression = str;
}
void RPN::calculate()
{
   size_t pos = 0;
   size_t pos2 = 0;
   (void)_a;
    (void)_b;
    (void)_result;
    checkExpression();
    if (_expression.length() == 1)
    {
        size_t d = std::atoi(_expression.c_str());
        if (d < 0 || d > 9)
            throw std::runtime_error("Error");
        std::cout << d << std::endl;
        return ;
    }
    while (_expression[pos] != '\0')
    {
        if (_expression[pos] != ' ' && _expression[pos] != '+' && _expression[pos] != '-' && _expression[pos] != '*' && _expression[pos] != '/')
        {
            if (_expression[pos] < '0' || _expression[pos] > '9')
                throw std::runtime_error("Error");
        }
        if (_expression[pos] == ' ')
        {
            if (_expression[pos] && _expression[pos + 1] == ' ')
            {
                pos++;
                continue;
            }
            if (_expression[pos - 1] >= '0' && _expression[pos - 1] <= '9')
            {
                size_t d = std::atoi(_expression.substr(pos2, pos - pos2).c_str());
                if (d < 0 || d > 9)
                    throw std::runtime_error("Error");

                stack.push(d);
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
                if (_expression[pos - 1 ] == '+')
                    _result = _a + _b;
                else if (_expression[pos - 1] == '-')
                    _result = _a - _b;
                else if (_expression[pos -1 ] == '*')
                {
                    _result = _a * _b;
                }
                else if (_expression[pos - 1] == '/')
                {
                    if (_b == 0)
                        throw std::runtime_error("Error");    
                    _result = _a / _b;
                }
                else if (_expression[pos - 1] != ' ')
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
            size_t d = std::atoi(_expression.substr(pos2, pos - pos2).c_str());
            if (d < 0 || d > 9)
                throw std::runtime_error("Error");
            stack.push(d);
        }
        else
        {
            if (stack.size() < 2)
                throw std::runtime_error("Error");
            _b = stack.top();
            stack.pop();
            _a = stack.top();
            stack.pop();
            if (_expression[pos - 1 ] == '+')
                _result = _a + _b;
            else if (_expression[pos - 1] == '-')
                _result = _a - _b;
            else if (_expression[pos -1 ] == '*')
            {
                _result = _a * _b;
            }
            else if (_expression[pos - 1] == '/')
            {
                    if (_b == 0)
                        throw std::runtime_error("Error");    
                    _result = _a / _b;
            }
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
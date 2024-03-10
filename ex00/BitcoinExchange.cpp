#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}
BitcoinExchange::BitcoinExchange(BitcoinExchange const &src)
{
    in = src.in;
}
BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &src)
{
    if (this != &src)
    {
        in = src.in;
    }
    return *this;
}

const char* BitcoinExchange::EmptyFile::what() const throw()
{
    return "Empty file";
}
void BitcoinExchange::checkFirstLine(std::string line)
{
    if (line != "date | value")
        throw std::runtime_error("Invalid file format");
}
int BitcoinExchange::checkDate(std::string date)
{
    if (date.length() != 10)
    {
        std::cout << "Error: bad input => " << date << std::endl;
        return 1;
    }
    if (date[4] != '-' || date[7] != '-')
    {
        std::cout << "Error: bad input => " << date << std::endl;
        return 1;
    }
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (date[i] < '0' || date[i] > '9')
        {
            std::cout << "Error: bad input => " << date << std::endl;
            return 1;
        }
    }
    return 0;
}
int BitcoinExchange::checkValue(std::string value)
{
    if (value.length() == 0)
    {
        std::cout << "Error: bad input => " << value << std::endl;
        return (1);
    }
    if ( value.length() >= 10)
    {
        std::cout << "Error: too large a number. "<< std::endl;
        return (1);
    }
    if (atoi(value.c_str()) < 0)
    {
        std::cout << "Error: not a positive number."<< std::endl;
        return (1);
    }
    int dot = 0;
    for (size_t i = 0; i < value.length(); i++)
    {
        if (value[i] < '0' || value[i] > '9')
        {
            if (value[i] == '.' && i != 0 && i != value.length() - 1)
            {
                dot++;
                if (dot > 1)
                {
                    std::cout << "Error: bad input => " << value << std::endl;
                    return (1);
                }
                continue;
            }
            if (value[i] == '+' && i == 0 && value.length() > 1)
                continue;
            std::cout << "Error: bad input => " << value << std::endl;
            return 1;
        }
    }
    return 0;
}
std::string strtrim(std::string s)
{
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    if (start == std::string::npos || end == std::string::npos)
        return "";
    return s.substr(start, end - start + 1);
}
void BitcoinExchange::storDate(void)
{
    std::string date;
    std::string value;
    std::string file = "data.csv";
    std::ifstream ifs(file);
    if (!ifs.is_open())
        throw std::runtime_error("File not found"); 
    std::getline(ifs, date);
    if (date != "date,exchange_rate")
        throw std::runtime_error("Invalid file format");
    while (std::getline(ifs, date))
    {
        size_t pos = 0;
        pos = date.find(",", pos);
        in[date.substr(0, pos)] = std::stof(date.substr(pos + 1, date.length()));
    }
}

float BitcoinExchange::getDate(std::string date)
{
    t_date date1;
    t_date date2;
    date1.year = std::stoi(date.substr(0, 4));
    if (date1.year < 2009 || date1.year > 2022)
        return -1;
    date1.month = std::stoi(date.substr(5, 2));
    if (date1.month < 1 || date1.month > 12)
        return -1;
    date1.day = std::stoi(date.substr(8, 2));
    if (date1.day < 1 || date1.day > 31)
        return -1;
    if (date1.month == 2 && date1.day > 29 && date1.year % 4 == 0)
        return -1;
    if (date1.month == 2 && date1.day > 28 && date1.year % 4 != 0)
        return -1;
    if (date1.month <= 7 && date1.month % 2 == 0 && date1.day > 30)
        return -1;
    if (date1.month > 7 && date1.month % 2 != 0 && date1.day > 30)
        return -1;
    float sum = -1;
    if (in.find(date) == in.end())
    {
        for (std::map<std::string, float>::iterator it = in.begin(); it != in.end(); it++)
        {
            date2.year = std::stoi(it->first.substr(0, 4));
            date2.month = std::stoi(it->first.substr(5, 2));
            date2.day = std::stoi(it->first.substr(8, 2));
            if (date1.year < date2.year || (date1.year == date2.year && date1.month < date2.month) || (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day))
            {
                return sum;
            }   
            sum = it->second;
        }
    }
    return in[date];
}
void BitcoinExchange::readFile(char *filename)
{
    std::string line;
    std::string file = filename;
    float sum;
    std::ifstream ifs(file);
    if (!ifs.is_open())
        throw std::runtime_error("File not found");
    std::getline(ifs, line);
    checkFirstLine(line);
    int i;
    i = 0;
    storDate();
    while (std::getline(ifs, line))
    {
        size_t pos = 0;
        pos = line.find("|", pos);
        if (strtrim(line).length() == 0 || strtrim(line) == "\n")
        {
            i++;
            continue;
        }
        int d = checkDate(strtrim(line.substr(0, pos)));
        if (d)
        {
            i++;
            continue;
        }
        sum = getDate(strtrim(line.substr(0, pos)));
        if (sum == -1 && !d)
        {
            std::cout << "Error: date not found => " << strtrim(line.substr(0, pos)) << std::endl;
            i++;
            continue;
        }
        if (pos == std::string::npos || pos == 0)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            i++;
            continue;
        }
        int c;
            c = checkValue(strtrim(line.substr(pos + 1, line.length())));
        if (sum == -1 && !d)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            i++;
            continue;
        }
        else if (!c)
        {
            float sum1 = std::stof(strtrim(line.substr(pos + 1, line.length())));
            if (sum1 >  1000)
            {
                std::cout << "Error: bad input => " << strtrim(line.substr(pos + 1, line.length())) << std::endl;
                i++;
                continue;
            }
            std::cout << strtrim(line.substr(0, pos)) << " => " << strtrim(line.substr(pos + 1, line.length())) << " = " << sum * sum1 << std::endl;
        } 
        i++;
    }
    if (in.size() == 0)
        throw std::runtime_error("Empty file");   
   
}
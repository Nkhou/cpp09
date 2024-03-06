#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}
// void BitcoinExchange::checkLine(std::string line)
// {
    
// }
// void BitcoinExchange::storLine(std::string storLine, int i, size_t pos)
// {
//     // size_t pos = 0;
//     // pos = storLine.find("|", pos);
//     // in.insert(std::pair<unsigned int, double>(i, std::stod(storLine.substr(pos + 1, storLine.length()))));
//     if (pos == std::string::npos || pos == 0)
//     {
//         in[i] = std::stof(storLine);
//         return;
//     }
//     in[i] = std::stof(storLine.substr(pos + 1, storLine.length()));
// }
const char* BitcoinExchange::EmptyFile::what() const throw()
{
    return "Empty file";
}
void BitcoinExchange::checkFirstLine(std::string line)
{
    if (line != "date | value")
        throw std::runtime_error("Invalid file format");
}
void BitcoinExchange::checkDate(std::string date)
{
    if (date.length() != 10)
    {
        std::cout << "Error: bad input => " << date << std::endl;
        return ;
    }
    if (date[4] != '-' || date[7] != '-')
    {
        std::cout << "Error: bad input => " << date << std::endl;
        return ;
    }
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (date[i] < '0' || date[i] > '9')
        {
            std::cout << "Error: bad input => " << date << std::endl;
            return ;
        }
    }
}
void BitcoinExchange::checkValue(std::string value)
{
    if (value.length() == 0)
    {
        std::cout << "Error: bad input => " << value << std::endl;
        return ;
    }
    if ( value.length() >= 10)
    {
        std::cout << "Error: too large a number. " << value << std::endl;
        return ;
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
                    return ;
                }
                continue;
            }
            if (value[i] == '-' && i == 0 && value.length() > 1)
                continue;
            std::cout << "Error: bad input => " << value << std::endl;
            return ;
        }
    }
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
// float BitcoinExchange::getAverage(std::string date1, std::string date2)
// {
//     float sum;
//     int i;
//     i = 0;
//     sum = 0;
//     for (std::map<std::string, float>::iterator it = in.begin(); it != in.end(); it++)
//     {
//         if (it->first >= date1 && it->first <= date2)
//         {
//             sum += it->second;
//             i++;
//         }
//     }
//     if (i == 0)
//         throw std::runtime_error("No data");
//     return sum / i;
// }
float BitcoinExchange::getDate(std::string date)
{
    if (in.find(date) == in.end())
    {
        
    }
    return in[date];
}
void BitcoinExchange::readFile(char *filename)
{
    std::string line;
    std::string file = filename;
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
        checkDate(strtrim(line.substr(0, pos)));
        if (pos == std::string::npos || pos == 0)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            i++;
            continue;
        }
        checkValue(strtrim(line.substr(pos + 1, line.length())));
        getDate(strtrim(line.substr(0, pos)));
        i++;
    }
    if (in.size() == 0)
        throw std::runtime_error("Empty file");   
   
}
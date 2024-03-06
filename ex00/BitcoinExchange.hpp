#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H
#include<iostream>
#include <map>
#include <string>
#include <exception> 
#include <utility>      
#include <fstream>
#include <cstdlib>

typedef struct s_date
{
    int year;
    int month;
    int day;
}               t_date; 
class BitcoinExchange
{
    private:
        std::map<std::string , float> in;
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        void readFile(char *filename);
        void checkLine(std::string line);
        void storLine(std::string storLine, int i, size_t pos);
        void checkFirstLine(std::string line);
        void checkDate(std::string date);
        int checkValue(std::string value);
        void storDate(void);
        float getDate(std::string date);
        float getAverage(std::string date1, std::string date2);
        class EmptyFile : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
};



#endif
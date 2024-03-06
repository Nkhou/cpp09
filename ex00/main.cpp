#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    try
    { 
        BitcoinExchange b;  
        if (ac != 2)
            throw BitcoinExchange::EmptyFile();
        b.readFile(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
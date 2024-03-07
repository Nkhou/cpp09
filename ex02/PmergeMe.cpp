#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    output = "";
}
PmergeMe::PmergeMe(char* argv[], int argc)
{
    parseArgs(argv, argc);
}

PmergeMe::PmergeMe(const PmergeMe& pmergeMe)
{
    args = pmergeMe.args;
    files = pmergeMe.files;
    output = pmergeMe.output;
}
PmergeMe::~PmergeMe()
{
    args.clear();
    files.clear();
    output.clear();
}
PmergeMe& PmergeMe::operator=(const PmergeMe& pmergeMe)
{
    if (this != &pmergeMe)
    {
        args = pmergeMe.args;
        files = pmergeMe.files;
        output = pmergeMe.output;
    }
    return *this;
}
void PmergeMe::checkIsString(char *argv)
{
    int i = 0;
    while (argv[i] != '\0')
    {
        if (!isdigit(argv[i]) && (argv[i] != '-') && argv[i] != '+')
        {
            throw std::invalid_argument("");
        }
        else if (argv[i] == '-' || argv[i] == '+')
        {
            if (i != 0)
            {
                throw std::invalid_argument("");
            }
        }
        i++;
    }
}
void PmergeMe::parseArgs(char* argv[], int argc)
{
    double k = 0;
    int d = 1;
    if (argc %  2 == 0)
    {
        output = argv[1];
        d = 2;
    }
    for (int i = d; i < argc; i++)
    {
        checkIsString(argv[i]);
        k = strtod(argv[i], NULL);
        if (k > 2147483647 || k < 0)
        {
            throw std::invalid_argument("");
        }
        if (i != d)
        {
            files.push_back(std::make_pair(atoi(argv[i]), atoi(argv[i - 1])));
            args.push_back(std::make_pair(atoi(argv[i]), atoi(argv[i - 1])));
            i++;
        }
    }
}
void PmergeMe::printargs()
{
    for (std::vector<std::pair<unsigned int, unsigned int> >::iterator it = args.begin(); it != args.end(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
}
void PmergeMe::sortPairs()
{
    for (std::vector<std::pair<unsigned int, unsigned int> >::iterator it = args.begin(); it != args.end(); it++)
    {
        if (it->first < it->second)
        {
            std::swap(it->first, it->second);
        }
    }
}
void PmergeMe::sortFirstPair()
{
    std::sort(args.begin(), args.end());
    // printargs();
}
void PmergeMe::bainarySearch(std::vector<unsigned int> d2)
{
    std::vector<unsigned int>::iterator it;
    for (std::vector<unsigned int>::iterator it2 = d2.begin(); it2 != d2.end(); it2++)
    {
        it = std::lower_bound(d2.begin(), d2.end(), *it2);
        std::cout << "hello " <<*it << std::endl;
    }
}
void PmergeMe::storIndouble()
{
    std::vector<unsigned int> d;
    std::vector<unsigned int> d2;
    for (std::vector<std::pair<unsigned int, unsigned int> >::iterator it = args.begin(); it != args.end(); it++)
    {
        d.push_back(it->first);
        d2.push_back(it->second);
    }
    if (d2.size() > 0)
    {
        d.push_back(d2.back());
        d2.pop_back();
    }
    bainarySearch(d2);
    // d.push_back(d2.begin());
    for (std::vector<unsigned int>::iterator it = d.begin(); it != d.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "----------------" << std::endl;
    for (std::vector<unsigned int>::iterator it = d2.begin(); it != d2.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}
void PmergeMe::run(char* argv[], int argc)
{
    parseArgs(argv, argc);
    sortPairs();
    sortFirstPair();
    storIndouble();
    // insertSort();
}

#include "PmergeMe.hpp"

int PmergeMe::jacobsthal(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
    }
}
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
void PmergeMe::bainarySearch(std::vector<unsigned int> d2, std::vector<unsigned int> d)
{
    (void)d2;
    int jab_index = 3;
    int javSave = 0;
    int m = d2.size();
    while (1)
    {
        int jab_inv = jacobsthal(jab_index);
        while (jab_inv > jab_index)
        {
            std::vector<unsigned int>::iterator pos = std::lower_bound(d.begin(), d.end(), d2[jab_inv - m - 1]);
            std::cout << "pos: " << d2[jab_inv - m - 1] << std::endl;
            d.insert(pos, d2[jab_inv - m - 1]);
            jab_inv--;
        }
        if (jab_index > m)
        {
            jab_index = m;
            break;
        }
        javSave = jab_index;
        jab_index++;
    }
    for (std::vector<unsigned int>::iterator it = d.begin(); it != d.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}
void PmergeMe::storIndouble()
{
    std::vector<unsigned int> d;
    std::vector<unsigned int> d2;
    // d.push_back(args.begin());
    for (std::vector<std::pair<unsigned int, unsigned int> >::iterator it = args.begin(); it != args.end(); it++)
    {
        if (it == args.begin())
        {
            d.push_back(it->second);
        }
        d.push_back(it->first);
        d2.push_back(it->second);
    }
    bainarySearch(d2 , d);
}
void PmergeMe::run(char* argv[], int argc)
{
    parseArgs(argv, argc);
    sortPairs();
    sortFirstPair();
    storIndouble();
    // insertSort();
}

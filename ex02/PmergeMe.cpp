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
void PmergeMe::sortPairsD()
{
    for (std::deque<std::pair<unsigned int, unsigned int> >::iterator it = files.begin(); it != files.end(); it++)
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
void PmergeMe::sortFirstPairD()
{
    std::sort(files.begin(), files.end());
    // printargs();
}
template <typename T>
void PmergeMe::bainarySearch(T d2, T d)
{
    int javSave = 1;
    int saveForLater = 3;
    int jab_inv;
    int ex = 0;
    int m = d2.size();
    while (1)
    {
        if (javSave == 1)
            jab_inv = jacobsthal(javSave + 2);
        else
            jab_inv = jacobsthal(javSave);
        if (jab_inv >= m)
        {
            jab_inv = m;
            ex = 1;
        }
        saveForLater = jab_inv;
        while (jab_inv > javSave)
        {
            typename T::iterator pos = std::lower_bound(d.begin(), d.end(), d2[jab_inv - 1]);
            d.insert(pos, d2[jab_inv - 1]);
            jab_inv--;
        }
        javSave = saveForLater + 1;
        if (ex == 1)
        {
            break;
        }
    }
    for (typename T::iterator it = d.begin(); it != d.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}

void PmergeMe::storIndouble()
{
    std::vector<unsigned int> d;
    std::vector<unsigned int> d2;
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
void PmergeMe::storIndoubleD()
{
    std::deque<unsigned int> d;
    std::deque<unsigned int> d2;
    for (std::deque<std::pair<unsigned int, unsigned int> >::iterator it = files.begin(); it != files.end(); it++)
    {
        if (it == files.begin())
        {
            d.push_back(it->second);
        }
        d.push_back(it->first);
        d2.push_back(it->second);
    }
    bainarySearch(d2 , d);
}
void PmergeMe::sortVector()
{
    sortPairs();
    sortFirstPair();
    storIndouble();
}
void PmergeMe::sortDeque()
{
    
    sortPairsD();
    sortFirstPairD();
    storIndoubleD();
}
void PmergeMe::run(char* argv[], int argc)
{
    parseArgs(argv, argc);
    sortVector();
    sortDeque();
    // insertSort();
}

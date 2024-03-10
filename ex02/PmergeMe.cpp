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
    output = -5;
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
    // output.clear();
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
        checkIsString(argv[1]);
        output = strtod(argv[1], NULL);
        if (k > 2147483647 || k < 0)
        {
            throw std::invalid_argument("");
        }
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
        size = i - 1;
    }
    if (size == 0)
    {
        throw std::invalid_argument("");
    }
    std::cout << "Before:  ";
    for (int i = 1 ; i < argc; i++)
    {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
}
void PmergeMe::printargs()
{
    std::cout<< "Before:  " << output<< " " ;
    for (std::vector<std::pair<unsigned int, unsigned int> >::iterator it = args.begin(); it != args.end(); it++)
    {
        std::cout << it->first << " " << it->second << " ";
    }
    std::cout << std::endl;
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

void PmergeMe::sortf(std::vector<std::pair<unsigned int, unsigned int> >::iterator &it)
{
    std::vector<std::pair<unsigned int, unsigned int> >::iterator it2 = it;
    it2++;
    if (it2 == args.end())
    {
        return;
    }
    if (it != args.end())
    {
        if (it2->first < it->first)
        {
            std::swap(*it, *it2);
            it++;
        }
        else
        {
            it++;
        }
        sortf(it);
    }
}
void PmergeMe::sortfD(std::deque<std::pair<unsigned int, unsigned int> >::iterator &it)
{
    std::deque<std::pair<unsigned int, unsigned int> >::iterator it2 = it;
    it2++;
    if (it2 == files.end())
    {
        return;
    }
    if (it != files.end())
    {
        if (it2->first < it->first)
        {
            std::swap(*it, *it2);
            it++;
        }
        else
        {
            it++;
        }
        sortfD(it);
    }
}

void PmergeMe::sortFirstPair()
{
    std::vector<std::pair<unsigned int, unsigned int> >::iterator it = args.begin();
    sortf(it);
}

void PmergeMe::sortFirstPairD()
{
    std::deque<std::pair<unsigned int, unsigned int> >::iterator it = files.begin();
    sortfD(it);
}
template <typename T>
void PmergeMe::bainarySearch(T &d2, T &d)
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
    if (output != -5)
    {
        typename T::iterator pos = std::lower_bound(d.begin(), d.end(), output);
        d.insert(pos, output);
    }
}
template <typename T>
void PmergeMe::storIndouble(T &d)
{
    T d2;
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

void PmergeMe::sortVector(std::vector<unsigned int> &d)
{
    clock_t time_req;
    time_req = clock();
    sortPairs();
    sortFirstPair();
    storIndouble(d);
    time_req = clock() - time_req;
    std::cout << "Time to process a range of " << size << " elements with std::vector  :  "<< (double)time_req/CLOCKS_PER_SEC * 1000000 << " us" << std::endl;
    
}
void PmergeMe::sortDeque(std::deque<unsigned int> &d)
{
    clock_t time_req;
    time_req = clock();
    sortPairsD();
    sortFirstPairD();
    storIndouble(d);
    time_req = clock() - time_req;
    std::cout << "Time to process a range of " << size << " elements with std::deque  :  "<< (double)time_req/CLOCKS_PER_SEC * 1000000 << " us" << std::endl;
}
void PmergeMe::run(char* argv[], int argc)
{
    std::vector<unsigned int> d;
    std::deque<unsigned int> d1;
    parseArgs(argv, argc);
    sortVector(d);
    sortDeque(d1);
    std::cout << "After:  ";
    for (std::vector<unsigned int>::iterator it = d.begin(); it != d.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

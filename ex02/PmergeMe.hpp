#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
template <typename T>
struct greaterThan {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};
class PmergeMe {
    private:
        std::vector<std::pair<unsigned int, unsigned int> > args;
        std::deque<std::pair<unsigned int, unsigned int> > files;
        std::string output;
        void parseArgs(char* argv[], int argc);
        void mergeFiles();
        void checkIsString(char *argv);
    public:
        PmergeMe();
        PmergeMe(char* argv[], int argc);
        PmergeMe(std::vector<unsigned int> args, std::deque<unsigned int> files, std::string output);
        PmergeMe(const PmergeMe& pmergeMe);
        void sortPairs();
        bool isSorted();
        ~PmergeMe();
        PmergeMe& operator=(const PmergeMe& pmergeMe);
        void run(char* argv[], int argc);
        void sortFirstPair();
        void printargs();
        void storIndouble();
        void bainarySearch(std::vector<unsigned int> d2);
        // bool greaterThan(unsigned int a, unsigned int b);
};
#endif
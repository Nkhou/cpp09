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
        void sortPairsD();
        bool isSorted();
        ~PmergeMe();
        PmergeMe& operator=(const PmergeMe& pmergeMe);
        void run(char* argv[], int argc);
        void sortFirstPair();
        void sortFirstPairD();
        void printargs();
        void storIndouble();
        void storIndoubleD();
        int jacobsthal(int n);
        void sortVector();
        void sortDeque();
        template <typename T>
        void bainarySearch(T d2, T d);
        // bool greaterThan(unsigned int a, unsigned int b);
};
#endif
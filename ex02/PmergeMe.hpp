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

        int size;
        int output;
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
        void storIndoubleD(std::deque<unsigned int> &d);
        int jacobsthal(int n);
        void sortVector(std::vector<unsigned int> &d);
        void sortDeque(std::deque<unsigned int> &d);
        template <typename T>
        void storIndouble(T &d);
        template <typename T>
        void bainarySearch(T &d2, T &d);
};
#endif
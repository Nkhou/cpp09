#include"PmergeMe.hpp"
int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            throw std::invalid_argument("");
        }
        PmergeMe pmergeMe;
        pmergeMe.run(argv, argc);
    } catch (std::exception& e) {
        std::cerr << "Error " << std::endl;
    }
  return 0;
}
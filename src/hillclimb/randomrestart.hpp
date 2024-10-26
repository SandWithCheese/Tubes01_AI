#ifndef RANDOMRESTART_HPP
#define RANDOMRESTART_HPP

#include "hillclimb.hpp"
#include "../cube/magicfive.hpp"

using namespace std;

class RandomRestart : public HillClimb {
    private: 
        int max_restart;
    public:
        RandomRestart(int max_restart);
        RandomRestart(const MagicFive& other, int max_restart);

        void solve() override;
};

#endif
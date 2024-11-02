#ifndef RANDOMRESTART_HPP
#define RANDOMRESTART_HPP

#include "hillclimb.hpp"
#include "../cube/magicfive.hpp"

using namespace std;

class RandomRestart : public HillClimb {
    private: 
        int max_restart = 100;
    public:
        RandomRestart();
        RandomRestart(const MagicFive& other);

        void solve() override;
};

#endif
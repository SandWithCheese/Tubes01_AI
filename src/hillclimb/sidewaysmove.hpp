#ifndef SIDEWAYSMOVE_HPP
#define SIDEWAYSMOVE_HPP

#include "hillclimb.hpp"
#include "../cube/magicfive.hpp"

class SidewaysMove : public HillClimb {
public:
    SidewaysMove(int maxSidewaysMoves);
    SidewaysMove(const MagicFive& other, int maxSidewaysMoves);
    ~SidewaysMove();

    void solve() override;

private:
    int maxSidewaysMoves;
};

#endif

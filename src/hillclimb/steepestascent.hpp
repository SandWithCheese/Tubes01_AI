#ifndef STEEPESTASCENT_HPP
#define STEEPESTASCENT_HPP

#include "hillclimb.hpp"
#include "../cube/magicfive.hpp"

class SteepestAscent : public HillClimb {
public:
    SteepestAscent();
    SteepestAscent(const MagicFive& other);
    virtual ~SteepestAscent();

    virtual void solve() override;
};

#endif

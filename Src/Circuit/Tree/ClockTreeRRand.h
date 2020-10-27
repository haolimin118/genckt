#ifndef GENCKT_CIRCUIT_TREE_CLOCKTREERRAND_H
#define GENCKT_CIRCUIT_TREE_CLOCKTREERRAND_H

/*
 * @filename : ClockTreeRRand.h
 * @author   : Hao Limin
 * @date     : 2020.09.07
 * @desp     : Clock Tree with random fanout, only R.
 * @ref      : Doc/Tree/ClockTreeRRand.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class ClockTreeRRand : public CktBase
{
public:
    ClockTreeRRand(int scale, const std::string &typeName);
    virtual ~ClockTreeRRand();

public:
    int Generate(std::ofstream &fout) override;

private:
    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    int               m_outNode;

};

#endif // GENCKT_CIRCUIT_TREE_CLOCKTREERRAND_H

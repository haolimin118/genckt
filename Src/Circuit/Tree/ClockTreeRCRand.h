#ifndef GENCKT_CIRCUIT_TREE_CLOCKTREERCRAND_H
#define GENCKT_CIRCUIT_TREE_CLOCKTREERCRAND_H

/*
 * @filename : ClockTreeRCRand.h
 * @author   : Hao Limin
 * @date     : 2020.09.07
 * @desp     : Clock Tree with random fanout, RC.
 * @ref      : Doc/Tree/ClockTreeRCRand.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class ClockTreeRCRand : public CktBase
{
public:
    ClockTreeRCRand(int scale, const std::string &typeName);
    virtual ~ClockTreeRCRand();

public:
    int Generate(std::ofstream &fout) override;

private:
    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;

};

#endif // GENCKT_CIRCUIT_TREE_CLOCKTREERCRAND_H

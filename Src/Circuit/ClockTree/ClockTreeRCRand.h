#ifndef GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERCRAND_H
#define GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERCRAND_H

/*
 * @filename : ClockTreeRCRand.h
 * @author   : Hao Limin
 * @date     : 2020.09.07
 * @desp     : Clock Tree with random fanout, RC.
 * @ref      : Doc/ClockTree/ClockTreeRCRand.png
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
    DISALLOW_COPY_AND_ASSIGN(ClockTreeRCRand);
    
    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    int               m_outIndex;

};

#endif // GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERCRAND_H

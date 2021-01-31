#ifndef GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREER_H
#define GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREER_H

/*
 * @filename : ClockTreeR.h
 * @author   : Hao Limin
 * @date     : 2020.09.05
 * @desp     : Clock Tree, only R.
 * @ref      : Doc/ClockTree/ClockTreeR.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class ClockTreeR : public CktBase
{
public:
    ClockTreeR(int scale, const std::string &typeName);
    virtual ~ClockTreeR();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(ClockTreeR);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    int               m_outIndex;

};

#endif // GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREER_H

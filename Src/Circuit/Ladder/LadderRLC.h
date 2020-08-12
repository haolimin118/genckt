#ifndef GENCKT_CIRCUT_LADDER_LADDERRLC_H
#define GENCKT_CIRCUT_LADDER_LADDERRLC_H

/*
 * @filename : LadderRLC.h
 * @athor    : Hao Limin
 * @date     : 2020.08.12
 * @desp     : RLC ladder circuit.
 * @ref      : Doc/Ladder/LadderRLC.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class LadderRLC : public CktBase
{
public:
    LadderRLC(int scale, const std::string &typeName);
    virtual ~LadderRLC();

public:
    int Generate(std::ofstream &fout) override;

private:
    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;

};

#endif // GENCKT_CIRCUT_LADDER_LADDERRLC_H
#ifndef GENCKT_CIRCUIT_LADDER_LADDERRC_H 
#define GENCKT_CIRCUIT_LADDER_LADDERRC_H 

/*
 * @filename : LadderRC.h
 * @author   : Hao Limin
 * @date     : 2020.08.12
 * @desp     : RC ladder circuit.
 * @ref      : Doc/Ladder/LadderRC.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class LadderRC : public CktBase
{
public:
    LadderRC(int scale, const std::string &typeName);
    virtual ~LadderRC();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(LadderRC);

    int GenerateCkt() override;
    int GenerateCmd() override;

    int               m_outIndex;
    std::stringstream m_ss;

};

#endif // GENCKT_CIRCUIT_LADDER_LADDERRC_H 
#ifndef GENCKT_CIRCUIT_LADDER_LADDERRC_H 
#define GENCKT_CIRCUIT_LADDER_LADDERRC_H 

/*
 * @filename : LadderRC.h
 * @author   : Hao Limin
 * @date     : 2020.08.12
 * @desp     : RC ladder circuit.
 * @ref      : Doc/LadderRC.png
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
    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;

};

#endif // GENCKT_CIRCUIT_LADDER_LADDERRC_H 
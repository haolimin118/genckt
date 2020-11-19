#ifndef GENCKT_CIRCUIT_RLINE_RLINE_H
#define GENCKT_CIRCUIT_RLINE_RLINE_H

/*
 * @filename : RLine.h
 * @author   : Hao Limin
 * @date     : 2020.11.19
 * @desp     : RLine, for testing HD-TICER algorithm.
 * @ref      : Doc/RLine/RLine.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class RLine : public CktBase
{
public:
    RLine(int scale, const std::string &typeName);
    virtual ~RLine();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(RLine);

    int GenerateCkt() override;
    int GenerateCmd() override;

    int                m_outIndex;
    std::stringstream  m_ss;
};

#endif // GENCKT_CIRCUIT_RLINE_RLINE_H
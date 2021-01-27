#ifndef genckt_CIRCUIT_PG_PGR_H
#define genckt_CIRCUIT_PG_PGR_H

/*
 * @filename : PGR.h
 * @date     : 2021.01.26
 * @weather  : Cloudy
 * @author   : Hao Limin
 * @email    : haolimin01@sjtu.edu.cn
 * @desp     : powergrid R case.
 * @ref      : Doc/PG/powergrid.png
 */

#include "Circuit/CktBase.h"
#include <sstream>
#include <vector>

class PGR : public CktBase
{
public:
    PGR(int scale, const std::string &typeName);
    virtual ~PGR();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(PGR);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::vector<std::string>    m_outs;
    std::stringstream           m_ss;
};

#endif // genckt_CIRCUIT_PG_PGR_H
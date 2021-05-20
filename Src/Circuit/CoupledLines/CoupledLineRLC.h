#ifndef GENCKT_CIRCUIT_COUPLEDLINES_COUPLEDLINERLC_H
#define GENCKT_CIRCUIT_COUPLEDLINES_COUPLEDLINERLC_H

/*
 * @filename : CoupledLineRLC.h
 * @author   : Hao Limin
 * @email    : haolimin01@sjtu.edu.cn
 * @date     : 2021.05.17
 * @weathor  : Mostly Sunny
 * @desp     : Two coupled RLC lines.
 * @ref      : Doc/CoupledLine/CoupledLineRLC.png
 */


#include "Circuit/CktBase.h"
#include <sstream>
#include <vector>

class CoupledLineRLC : public CktBase
{
public:
    CoupledLineRLC(int scale, const std::string &typeName);
    virtual ~CoupledLineRLC();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(CoupledLineRLC);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    std::vector<int>  m_outs;
};


#endif // GENCKT_CIRCUIT_COUPLEDLINES_COUPLEDLINERLC_H
#ifndef GNECKT_CIRCUIT_COUPLEDLINES_COUPLEDLINEMRC_H
#define GNECKT_CIRCUIT_COUPLEDLINES_COUPLEDLINEMRC_H

/*
 * @filename : CoupledLineMRC.h
 * @author   : Hao Limin
 * @date     : 2020.11.08
 * @desp     : Two coupled multi RC lines.
 * @ref      : Doc/CoupledLine/CoupledLineRC.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class CoupledLineMRC : public CktBase
{
public:
    CoupledLineMRC(int scale, const std::string &typeName);
    virtual ~CoupledLineMRC();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(CoupledLineMRC);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    std::string       m_outNode;
};

#endif // GNECKT_CIRCUIT_COUPLEDLINES_COUPLEDLINEMRC_H
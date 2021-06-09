#ifndef GNECKT_CIRCUIT_COUPLEDLINES_COUPLEDLINERC_H
#define GNECKT_CIRCUIT_COUPLEDLINES_COUPLEDLINERC_H

/*
 * @filename : CoupledLineRC.h
 * @author   : Hao Limin
 * @date     : 2020.08.13
 * @desp     : Two coupled RC lines
 * @ref      : Doc/CoupledLine/CoupledLineRC.png
 */

#include "Circuit/CktBase.h"
#include <sstream>
#include <vector>

class CoupledLineRC : public CktBase
{
public:
    CoupledLineRC(int scale, const std::string &typeName);
    virtual ~CoupledLineRC();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(CoupledLineRC);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream         m_ss;
    std::vector<std::string>  m_outs;
};

#endif // GNECKT_CIRCUIT_COUPLEDLINES_COUPLEDLINERC_H
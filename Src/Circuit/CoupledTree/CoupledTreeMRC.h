#ifndef GNECKT_CIRCUIT_COUPLEDTREE_COUPLEDTREEMRC_H
#define GNECKT_CIRCUIT_COUPLEDTREE_COUPLEDTREEMRC_H

/*
 * @filename : CoupledTreeMRC.h
 * @author   : Hao Limin
 * @date     : 2020.11.08
 * @desp     : Two coupled multi RC lines.
 * @ref      : Doc/CoupledTree/CoupledTreeRC.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class CoupledTreeMRC : public CktBase
{
public:
    CoupledTreeMRC(int scale, const std::string &typeName);
    virtual ~CoupledTreeMRC();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(CoupledTreeMRC);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    std::string       m_outNode;
};

#endif // GNECKT_CIRCUIT_COUPLEDTREE_COUPLEDTREEMRC_H
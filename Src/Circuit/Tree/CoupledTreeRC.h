#ifndef GNECKT_CIRCUIT_TREE_COUPLEDTREERC_H
#define GNECKT_CIRCUIT_TREE_COUPLEDTREERC_H

/*
 * @filename : CoupledTreeRC.h
 * @author   : Hao Limin
 * @date     : 2020.08.13
 * @desp     : Two coupled RC lines
 * @ref      : Doc/Tree/CoupledTreeRC.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class CoupledTreeRC : public CktBase
{
public:
    CoupledTreeRC(int scale, const std::string &typeName);
    virtual ~CoupledTreeRC();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(CoupledTreeRC);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    int               m_outIndex;

};

#endif // GNECKT_CIRCUIT_TREE_COUPLEDTREERC_H
#ifndef GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERCLINK_H
#define GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERCLINK_H

/*
 * @filename : ClockTreeRCLink.h
 * @date     : 2021.01.31
 * @weather  : Mostly Cloudy 
 * @author   : Hao Limin
 * @email    : haolimin01@sjtu.edu.cn
 * @desp     : ClockTreeRC + some R links.
 */

#include "Circuit/CktBase.h"
#include <sstream>
#include <vector>

class ClockTreeRCLink : public CktBase
{
public:
    ClockTreeRCLink(int scale, const std::string &typeName);
    virtual ~ClockTreeRCLink();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(ClockTreeRCLink);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream         m_ss;
    std::vector<std::string>  m_outs;
};

#endif // GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERCLINK_H
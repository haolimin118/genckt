#ifndef GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERLINK_H
#define GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERLINK_H

/*
 * @filename : ClockTreeRLink.h
 * @date     : 2021.01.28
 * @weather  : Sunny
 * @author   : Hao Limin
 * @email    : haolimin01@sjtu.edu.cn
 * @desp     : ClockTreeR + some R links.
 * @modified : 2021.01.31
 */

#include "Circuit/CktBase.h"
#include <sstream>
#include <vector>

class ClockTreeRLink : public CktBase
{
public:
    ClockTreeRLink(int scale, const std::string &typeName);
    virtual ~ClockTreeRLink();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(ClockTreeRLink);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream        m_ss;
    std::vector<std::string> m_outs;
};

#endif // GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERLINK_H
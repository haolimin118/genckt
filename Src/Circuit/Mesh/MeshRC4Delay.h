#ifndef GENCKT_CIRCUIT_MESH_MESHRC4DELAY_H
#define GENCKT_CIRCUIT_MESH_MESHRC4DELAY_H

/*
 * @filename : MeshRC4Delay.h
 * @author   : Hao Limin
 * @date     : 2021.06.14
 * @desp     : RC Mesh circuit for measuring delay.
 * @ref      : Doc/Ladder/MeshRC.png
 */

#include "Circuit/CktBase.h"
#include <sstream>
#include <vector>

class MeshRC4Delay : public CktBase
{
public:
    MeshRC4Delay(int scale, const std::string &typeName);
    virtual ~MeshRC4Delay();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(MeshRC4Delay);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    std::vector<int>  m_outIndex;

};

#endif // GENCKT_CIRCUIT_MESH_MESHRC4DELAY_H

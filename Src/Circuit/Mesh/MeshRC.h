#ifndef GENCKT_CIRCUIT_MESH_MESHRC_H 
#define GENCKT_CIRCUIT_MESH_MESHRC_H 

/*
 * @filename : MeshRC.h
 * @author   : Hao Limin
 * @date     : 2020.10.26
 * @desp     : RC Mesh circuit.
 * @ref      : Doc/Ladder/MeshR.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class MeshRC : public CktBase
{
public:
    MeshRC(int scale, const std::string &typeName);
    virtual ~MeshRC();

public:
    int Generate(std::ofstream &fout) override;

private:
    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;

};

#endif // GENCKT_CIRCUIT_MESH_MESHRC_H 
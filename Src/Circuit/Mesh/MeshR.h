#ifndef GENCKT_CIRCUIT_MESH_MESHR_H 
#define GENCKT_CIRCUIT_MESH_MESHR_H 

/*
 * @filename : MeshR.h
 * @author   : Hao Limin
 * @date     : 2020.10.09
 * @desp     : R Mesh circuit.
 * @ref      : Doc/Ladder/MeshR.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class MeshR : public CktBase
{
public:
    MeshR(int scale, const std::string &typeName);
    virtual ~MeshR();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(MeshR);
    
    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    int               m_outIndex;

};

#endif // GENCKT_CIRCUIT_MESH_MESHR_H 
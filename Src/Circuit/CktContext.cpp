#include "CktContext.h"
#include <cassert>
#include "CktBase.h"
#include "AllCkt.h"
#include "Define/Define.h"

using std::ofstream;

CktContext::CktContext(CktType type, int scale, AnalysisType anaType)
{
    m_ckt = nullptr;

    switch (type) {
        case LADDERRC:
            m_ckt = new LadderRC(scale, "RC ladder");
            break;
        case LADDERRLC:
            m_ckt = new LadderRLC(scale, "RLC ladder");
            break;
        case COUPLEDLINERC:
            m_ckt = new CoupledLineRC(scale, "Coupled RC line");
            break;
        case COUPLEDLINEMRC:
            m_ckt = new CoupledLineMRC(scale, "Coupled MRC line");
            break;
        case COUPLEDLINERLC:
            m_ckt = new CoupledLineRLC(scale, "Coupled RLC line");
            break;
        case CLOCKTREER:
            m_ckt = new ClockTreeR(scale, "Clock R tree");
            break;
        case CLOCKTREERC:
            m_ckt = new ClockTreeRC(scale, "Clock RC tree");
            break;
        case CLOCKTREERLC:
            m_ckt = new ClockTreeRLC(scale, "Clock RLC tree");
            break;
        case CLOCKTREERRAND:
            m_ckt = new ClockTreeRRand(scale, "Clock R tree (random fanout)");
            break;
        case CLOCKTREERCRAND:
            m_ckt = new ClockTreeRCRand(scale, "Clock RC tree (random fanout)");
            break;
        case CLOCKTREERCLINK:
            m_ckt = new ClockTreeRCLink(scale, "Clock RC tree (plus some R links)");
            break;
        case CLOCKTREEMESH:
            m_ckt = new ClockTreeMesh(scale, "Clock tree mesh (fixed scale=8)");
            break;
        case MESHR:
            m_ckt = new MeshR(scale, "Mesh R");
            break;
        case MESHRC:
            m_ckt = new MeshRC(scale, "Mesh RC");
            break;
        case MESHRC4DELAY:
			m_ckt = new MeshRC4Delay(scale, "Mesh RC for measuring delay");
			break;
        case MESHRLC:
            m_ckt = new MeshRLC(scale, "Mesh RLC");
            break;
        case RLINE:
            m_ckt = new RLine(scale, "R Line");
            break;
        case POWERGRIDR:
            m_ckt = new PGR(scale, "powergrid R");
            break;
        default:;
    }

    m_ckt->SetAnalysisType(anaType);

}

int CktContext::executeGeneration(ofstream &fout)
{
    if (NOT m_ckt)
        return ERROR;
    return m_ckt->Generate(fout);
}

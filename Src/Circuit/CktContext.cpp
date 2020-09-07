#include "CktContext.h"
#include <cassert>
#include "CktBase.h"
#include "AllCkt.h"
#include "Define/Define.h"

using std::ofstream;

CktContext::CktContext(CktType type, int scale)
{
    m_ckt = nullptr;

    switch (type) {
        case LADDERRC:
            m_ckt = new LadderRC(scale, "RC ladder");
            break;
        case LADDERRLC:
            m_ckt = new LadderRLC(scale, "RLC ladder");
            break;
        case COUPLEDTREERC:
            m_ckt = new CoupledTreeRC(scale, "Coupled RC tree");
            break;
        case CLOCKTREER:
            m_ckt = new ClockTreeR(scale, "Clock R tree");
            break;
        case CLOCKTREERC:
            m_ckt = new ClockTreeRC(scale, "Clock RC tree");
            break;
        case CLOCKTREERRAND:
            m_ckt = new ClockTreeRRand(scale, "Clock R tree (random fanout)");
            break;
        case CLOCKTREERCRAND:
            m_ckt = new ClockTreeRCRand(scale, "Clock RC tree (random fanout)");
            break;
        default:;
    }

}

int CktContext::executeGeneration(ofstream &fout)
{
    if (NOT m_ckt)
        return ERROR;
    return m_ckt->Generate(fout);
}

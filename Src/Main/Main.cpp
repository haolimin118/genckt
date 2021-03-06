#include <iostream>
#include <string>
#include <fstream>
#include "Circuit/CktContext.h"
#include "Define/Define.h"
#include <gflags/gflags.h>

using namespace std;

// default params
static int          scale = 1;
static CktType      cktType = LADDERRC;
static string       pathname = "genckt.sp";
static AnalysisType anaType = OP;

DEFINE_string(t, "ladderrc",  "Set method to generate circuit.");
DEFINE_int64(s,  1,           "Set circuit scale.");
DEFINE_string(o, "genckt.sp", "Set output netlist pathname.");
DEFINE_string(a, "op",        "Set analysis type.");

static void ParseCommandLineArgs(int argc, char **argv);
static void InitProjectInfo();
static void GenerateNetlist();


/* use gflags to parse command line args */
static void ParseCommandLineArgs(int argc, char **argv)
{
    InitProjectInfo();

    google::ParseCommandLineFlags(&argc, &argv, true);

    if (FLAGS_s <= 0) {
        cout << "[ERROR] scale <= 0" << endl;
        EXIT;
    }
    scale = FLAGS_s;

    string flag_cktType = FLAGS_t;
    if (flag_cktType.compare("ladderrc") == 0) {
        cktType = LADDERRC;
    } else if (flag_cktType.compare("ladderrlc") == 0) {
        cktType = LADDERRLC;
    } else if (flag_cktType.compare("coupledlinerc") == 0) {
        cktType = COUPLEDLINERC;
    } else if (flag_cktType.compare("coupledlinerlc") == 0) {
        cktType = COUPLEDLINERLC;
    } else if (flag_cktType.compare("coupledlinemrc") == 0) {
        cktType = COUPLEDLINEMRC;
    } else if (flag_cktType.compare("clocktreer") == 0) {
        cktType = CLOCKTREER;
    } else if (flag_cktType.compare("clocktreerc") == 0) {
        cktType = CLOCKTREERC;
    } else if (flag_cktType.compare("clocktreerlc") == 0) {
        cktType = CLOCKTREERLC;
    } else if (flag_cktType.compare("clocktreerrand") == 0) {
        cktType = CLOCKTREERRAND;
    } else if (flag_cktType.compare("clocktreercrand") == 0) {
        cktType = CLOCKTREERCRAND;
    } else if (flag_cktType.compare("clocktreerclink") == 0) {
        cktType = CLOCKTREERCLINK;
    } else if (flag_cktType.compare("clocktreemesh") == 0) {
        cktType = CLOCKTREEMESH;
    } else if (flag_cktType.compare("meshr") == 0) {
        cktType = MESHR;
    } else if (flag_cktType.compare("meshrc") == 0) {
        cktType = MESHRC;
    } else if (flag_cktType.compare("meshrc4delay") == 0) {
        cktType = MESHRC4DELAY;
    } else if (flag_cktType.compare("meshrlc") == 0) {
        cktType = MESHRLC;
    } else if (flag_cktType.compare("rline") == 0) {
        cktType = RLINE;
    } else if (flag_cktType.compare("powergridr") == 0) {
        cktType = POWERGRIDR;
    } else {
        cout << "[ERROR] Circuit type is unknown" << endl;
        EXIT;
    }
    
    pathname = FLAGS_o;

    string flag_anaType = FLAGS_a;
    if (flag_anaType.compare("op") == 0) {
        anaType = OP;
    } else if (flag_anaType.compare("dc") == 0) {
        anaType = DC;
    } else if (flag_anaType.compare("ac") == 0) {
        anaType = AC;
    } else if (flag_anaType.compare("tran") == 0) {
        anaType = TRAN;
    } else {
        cout << "[ERROR] Analysis type is unknown" << endl;
        EXIT;
    }

    google::ShutDownCommandLineFlags();

    /* dump summary */
    printf("[NOTE] Pathname(%s), cktType(%s), scale(%d), anaType(%s)\n",
        pathname.c_str(), flag_cktType.c_str(), scale, flag_anaType.c_str());

}


static void InitProjectInfo()
{
    google::SetVersionString("0.1");
    google::SetUsageMessage("Usage: genckt <options>\n\n"
                            "options:\n"
                            "-o        set generated netlist pathname.\n"
                            "-s        set circuit scale.\n"
                            "-m        set circuit type.\n"
                            "-a        set analysis type.\n"
                            "Circuit Types:\n"
                            "ladderrc\n"
                            "ladderrlc\n"
                            "coupledlinerc\n"
                            "coupledlinerlc\n"
                            "coupledlinemrc\n"
                            "clocktreer\n"
                            "clocktreerc\n"
                            "clocktreerlc\n"
                            "clocktreerrand\n"
                            "clocktreercrand\n"
                            "clocktreerclink\n"
                            "clocktreemesh\n"
                            "meshr\n"
                            "meshrc\n"
                            "meshrc4delay\n"
                            "meshrlc\n"
                            "rline\n"
                            "powergridr");
}


/* Generate netlist */
static void GenerateNetlist()
{
    ofstream fout(pathname, ios::out);
    if (NOT fout.is_open()) {
        cout << "Can't open " << pathname << endl;
        EXIT;
    }

    // comment
    CktContext *context = new CktContext(cktType, scale, anaType);
    int error = context->executeGeneration(fout);
    if (error)
        cout << "[ERROR] Generate netlist failed." << endl;

    fout.close();
}


int main(int argc, char **argv)
{
    ParseCommandLineArgs(argc, argv);
    GenerateNetlist();

    cout << "\n[NOTE] Finished!" << endl;
    return 0;
}


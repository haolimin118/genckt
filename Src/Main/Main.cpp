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
    } else if (flag_cktType.compare("coupledtreerc") == 0) {
        cktType = COUPLEDTREERC;
    } else if (flag_cktType.compare("clocktreer") == 0) {
        cktType = CLOCKTREER;
    } else if (flag_cktType.compare("clocktreerc") == 0) {
        cktType = CLOCKTREERC;
    } else if (flag_cktType.compare("clocktreerrand") == 0) {
        cktType = CLOCKTREERRAND;
    } else if (flag_cktType.compare("clocktreercrand") == 0) {
        cktType = CLOCKTREERCRAND;
    } else if (flag_cktType.compare("meshr") == 0) {
        cktType = MESHR;
    } else if (flag_cktType.compare("meshrc") == 0) {
        cktType = MESHRC;
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
                            "coupledtreerc\n"
                            "clocktreer\n"
                            "clocktreerc\n"
                            "clocktreerrand\n"
                            "clocktreercrand\n"
                            "meshr\n"
                            "meshrc");
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


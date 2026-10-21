#include "command.h"
using namespace std;

commandType getCommand(const std::string& command) {

    if (command == "MPUSH") return commandType::MPUSH;
    if (command == "MSET") return commandType::MSET;
    if (command == "MGET") return commandType::MGET;
    if (command == "MREMOVE") return commandType::MREMOVE;
    if (command == "MINSERT") return commandType::MINSERT;
    if (command == "MSIZE") return commandType::MSIZE;
    if (command == "MDEL") return commandType::MDEL;

    if (command == "SLPUSHBACK") return commandType::SLPUSHBACK;
    if (command == "SLPUSHFRONT") return commandType::SLPUSHFRONT;
    if (command == "SLPUSHAFTER") return commandType::SLPUSHAFTER;
    if (command == "SLPUSHBEFORE") return commandType::SLPUSHBEFORE;
    if (command == "SLSET") return commandType::SLSET;
    if (command == "SLGET") return commandType::SLGET;
    if (command == "SLREMOVE") return commandType::SLREMOVE;
    if (command == "SLINSERT") return commandType::SLINSERT;
    if (command == "SLSIZE") return commandType::SLSIZE;
    if (command == "SLDEL") return commandType::SLDEL;
    if (command == "SLPOPBACK") return commandType::SLPOPBACK;
    if (command == "SLPOPFRONT") return commandType::SLPOPFRONT;
    if (command == "SLPOPAFTER") return commandType::SLPOPAFTER;
    if (command == "SLPOPBEFORE") return commandType::SLPOPBEFORE;

    if (command == "DLPUSHBACK") return commandType::DLPUSHBACK;
    if (command == "DLPUSHFRONT") return commandType::DLPUSHFRONT;
    if (command == "DLPUSHAFTER") return commandType::DLPUSHAFTER;
    if (command == "DLPUSHBEFORE") return commandType::DLPUSHBEFORE;
    if (command == "DLSET") return commandType::DLSET;
    if (command == "DLGET") return commandType::DLGET;
    if (command == "DLREMOVE") return commandType::DLREMOVE;
    if (command == "DLINSERT") return commandType::DLINSERT;
    if (command == "DLSIZE") return commandType::DLSIZE;
    if (command == "DLDEL") return commandType::DLDEL;
    if (command == "DLPOPBACK") return commandType::DLPOPBACK;
    if (command == "DLPOPFRONT") return commandType::DLPOPFRONT;
    if (command == "DLPOPAFTER") return commandType::DLPOPAFTER;
    if (command == "DLPOPBEFORE") return commandType::DLPOPBEFORE;

    if (command == "SPUSH") return commandType::SPUSH;
    if (command == "SPOP") return commandType::SPOP;

    if (command == "QPUSH") return commandType::QPUSH;
    if (command == "QPOP") return commandType::QPOP;

    if (command == "TADD") return commandType::TADD;
    if (command == "TFIND") return commandType::TFIND;
    if (command == "TDEL") return commandType::TDEL;

    if (command == "PRINT") return commandType::PRINT;
    if (command == "HELP") return commandType::HELP;
    if (command == "EXIT") return commandType::EXIT;
    return commandType::UNKNOWN; 
}

void printHelp(){
    std::cout <<
"MPUSH,      SLPUSHBACK,   DLPUSHBACK,   SPUSH,   QPUSH,   TADD,\n"
"            SLPUSHFRONT,  DLPUSHFRONT,\n"
"            SLPUSHAFTER,  DLPUSHAFTER,\n"
"            SLPUSHBEFORE, DLPUSHBEFORE,\n"
"MSET,       SLSET,        DLSET,\n"
"MGET,       SLGET,        DLGET,                 TFIND,\n"
"MREMOVE,    SLREMOVE,     DLREMOVE,\n"
"MINSERT,    SLINSERT,     DLINSERT,\n"
"MSIZE,      SLSIZE,       DLSIZE,\n"
"MDEL,       SLDEL,        DLDEL,                 TDEL,\n"
"            SLPOPBACK,    DLPOPBACK,    SPOP,    QPOP,\n"
"            SLPOPFRONT,   DLPOPFRONT,\n"
"            SLPOPAFTER,   DLPOPAFTER,\n"
"            SLPOPBEFORE,  DLPOPBEFORE,\n"
"PRINT, HELP, EXIT\n";
}
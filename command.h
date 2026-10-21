#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>

enum class commandType {

    MPUSH,      SLPUSHBACK,     DLPUSHBACK,     SPUSH,      QPUSH,      TADD,
                SLPUSHFRONT,    DLPUSHFRONT,
                SLPUSHAFTER,    DLPUSHAFTER,
                SLPUSHBEFORE,   DLPUSHBEFORE,
    MSET,       SLSET,          DLSET,
    MGET,       SLGET,          DLGET,                                  TFIND,
    MREMOVE,    SLREMOVE,       DLREMOVE,
    MINSERT,    SLINSERT,       DLINSERT,
    MSIZE,      SLSIZE,         DLSIZE,
    MDEL,                                                               TDEL,
                SLPOPBACK,      DLPOPBACK,      SPOP,       QPOP,
                SLPOPFRONT,     DLPOPFRONT,
                SLPOPAFTER,     DLPOPAFTER,
                SLPOPBEFORE,    DLPOPBEFORE,
    PRINT, HELP, EXIT,     
    UNKNOWN
};

commandType getCommand(const std::string& command);
void printHelp();

#endif
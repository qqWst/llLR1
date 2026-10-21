package main

import (
	"fmt"
	"strings"
)

type commandType int

const (
	MPUSH commandType = iota
	SLPUSHBACK
	DLPUSHBACK
	SPUSH
	QPUSH
	TADD
	SLPUSHFRONT
	DLPUSHFRONT
	SLPUSHAFTER
	DLPUSHAFTER
	SLPUSHBEFORE
	DLPUSHBEFORE
	MSET
	SLSET
	DLSET
	MGET
	SLGET
	DLGET
	TFIND
	MREMOVE
	SLREMOVE
	DLREMOVE
	MINSERT
	SLINSERT
	DLINSERT
	MSIZE
	SLSIZE
	DLSIZE
	MDEL
	TDEL
	SLPOPBACK
	DLPOPBACK
	SPOP
	QPOP
	SLPOPFRONT
	DLPOPFRONT
	SLPOPAFTER
	DLPOPAFTER
	SLPOPBEFORE
	DLPOPBEFORE
	PRINT
	HELP
	EXIT
	UNKNOWN
)

var commandNames = map[string]commandType{
	"MPUSH": MPUSH, "SLPUSHBACK": SLPUSHBACK, "DLPUSHBACK": DLPUSHBACK,
	"SPUSH": SPUSH, "QPUSH": QPUSH, "TADD": TADD,
	"SLPUSHFRONT": SLPUSHFRONT, "DLPUSHFRONT": DLPUSHFRONT,
	"SLPUSHAFTER": SLPUSHAFTER, "DLPUSHAFTER": DLPUSHAFTER,
	"SLPUSHBEFORE": SLPUSHBEFORE, "DLPUSHBEFORE": DLPUSHBEFORE,
	"MSET": MSET, "SLSET": SLSET, "DLSET": DLSET,
	"MGET": MGET, "SLGET": SLGET, "DLGET": DLGET, "TFIND": TFIND,
	"MREMOVE": MREMOVE, "SLREMOVE": SLREMOVE, "DLREMOVE": DLREMOVE,
	"MINSERT": MINSERT, "SLINSERT": SLINSERT, "DLINSERT": DLINSERT,
	"MSIZE": MSIZE, "SLSIZE": SLSIZE, "DLSIZE": DLSIZE,
	"MDEL": MDEL, "TDEL": TDEL,
	"SLPOPBACK": SLPOPBACK, "DLPOPBACK": DLPOPBACK, "SPOP": SPOP, "QPOP": QPOP,
	"SLPOPFRONT": SLPOPFRONT, "DLPOPFRONT": DLPOPFRONT,
	"SLPOPAFTER": SLPOPAFTER, "DLPOPAFTER": DLPOPAFTER,
	"SLPOPBEFORE": SLPOPBEFORE, "DLPOPBEFORE": DLPOPBEFORE,
	"PRINT": PRINT, "HELP": HELP, "EXIT": EXIT,
}

func getCommand(s string) commandType {
	if c, ok := commandNames[strings.ToUpper(s)]; ok {
		return c
	}
	return UNKNOWN
}

func printHelp() {
	fmt.Println(`Доступные команды:
  MPUSH <имя> <значение>              - добавить в конец массива
  MSET/MGET <имя> <индекс> [значение]
  MINSERT <имя> <индекс> <значение>
  MREMOVE <имя> <индекс>
  MSIZE <имя>
  MDEL <имя>

  SLPUSHBACK/SLPUSHFRONT <имя> <значение>
  SLPUSHAFTER/SLPUSHBEFORE <имя> <цель> <значение>
  SLSET/SLGET <имя> <индекс> [значение]
  SLINSERT <имя> <индекс> <значение>
  SLREMOVE <имя> <значение>
  SLPOPBACK/SLPOPFRONT <имя>
  SLPOPAFTER/SLPOPBEFORE <имя> <цель>
  SLSIZE <имя>

  DLPUSHBACK/DLPUSHFRONT <имя> <значение>
  DLPUSHAFTER/DLPUSHBEFORE <имя> <цель> <значение>
  DLSET/DLGET <имя> <индекс> [значение]
  DLINSERT <имя> <индекс> <значение>
  DLREMOVE <имя> <значение>
  DLPOPBACK/DLPOPFRONT <имя>
  DLPOPAFTER/DLPOPBEFORE <имя> <цель>
  DLSIZE <имя>

  SPUSH/SPOP <имя> [значение]
  QPUSH/QPOP <имя> [значение]

  TADD <имя> <значение>
  TFIND <имя> <значение>
  TDEL <имя>

  PRINT <array|slist|dlist|stack|queue|tree> <имя>
  HELP
  EXIT`)
}
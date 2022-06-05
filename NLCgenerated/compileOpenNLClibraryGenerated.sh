#!/bin/sh
rm *.o
head -c -1 -q makefile.OpenNLClibraryPart1 NLCgeneratedList.txt makefile.OpenNLClibraryPart3 > makefile
make

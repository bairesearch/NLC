OpenNLCI/OpenGIAI installation instructions (quick):

- Install QT Creator 3.5.1 with QT 5.5.1 (UB16: sudo apt-get install qtcreator qtbase5-dev qtdeclarative5-dev libqt5svg5 qbs).
- Install OpenNLC/OpenGIA dependencies (see opennlc.net/opengia.net for more information).
- Open NLCIglobalDefs.hpp and configure all input folders.
- Open SHAREDglobalDefs.hpp and ensure that COMPILE_NLCI or COMPILE_GIAI is activated.
- Open and build OpenNLCI.pro/OpenGIAI.pro with QT creator.
- Ensure that all input files are copied to NLCinput (minimally: NLCrules.xml and GIArules.xml) or GIAinput (minimally: GIArules.xml).
- Ensure that stanford-corenlp-full-2016-10-31/execute-stanfordCoreNLPServer.sh has been executed (assuming NLCI/GIAI is configured to execute GIA/NLC with Stanford Parser/CoreNLP and NLPclient=true).
- Execute NLCI/GIAI binary from build-GIAI-Desktop/build-NLCI-Desktop.

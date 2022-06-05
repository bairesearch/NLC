OpenNLCI/OpenGIAI installation instructions (quick):

- UB20: Install QT Creator 4.11.0 with QT 5.12.8 - sudo apt-get install qtcreator qtbase5-dev qtdeclarative5-dev libqt5svg5 qbs
- UB16: Install QT Creator 3.5.1 with QT 5.5.1 - sudo apt-get install qtcreator qtbase5-dev qtdeclarative5-dev libqt5svg5 qbs
- Install OpenNLC/OpenGIA dependencies.
- Open NLCIglobalDefs.hpp and configure all input folders.
- Open SHAREDglobalDefs.hpp and ensure that COMPILE_OPEN_NLCI or COMPILE_OPEN_GIAI is activated.
- Open and build OpenNLCI.pro/OpenGIAI.pro with QT creator.
- Ensure that all input files are copied to NLCinput (minimally: NLCrules.xml and GIA*ules.xml) or GIAinput (minimally: GIA*ules.xml).
- Ensure that stanford-corenlp-full-2016-10-31/execute-stanfordCoreNLPServer.sh has been executed (assuming OpenNLCI/OpenGIAI is configured to execute OpenGIA/OpenNLC with Stanford Parser/CoreNLP and NLPclient=true).
- Execute OpenNLCI/OpenGIAI binary from build-GIAI-Desktop/build-OpenNLCI-Desktop.

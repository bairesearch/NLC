 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCImain.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2p1a 05-June-2022
 * Requirements: 
 * /
 *******************************************************************************/


#include "NLCImain.hpp"
#include "NLCImainWindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	NLCImainWindowClass window;
	window.resize(NLCI_MAIN_WINDOW_WIDTH, NLCI_MAIN_WINDOW_HEIGHT);
	window.show();
	return app.exec();
}



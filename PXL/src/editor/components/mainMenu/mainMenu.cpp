
#include "mainMenu.h"
#include "engine.h"
#include "menu.h"
#include "eventListener.h"

 MainMenu::MainMenu(Engine & engine) {


}

void MainMenu::init() {

	m_menu = new Menu(this->getLayout()->getPosition(), this->getLayout()->getSize(), "segoeui");

	Menu::MenuItem* fileMenu = m_menu->addMenuItem("File");
	fileMenu->addChild("New", NULL, "Ctrl + N", "PLUS_CIRCLED");
	fileMenu->addChild("Open...", NULL, "Ctrl + O", "FOLDER_OPENED");
	fileMenu->addSeparator();
	fileMenu->addChild("Save", NULL, "Ctrl + S", "FLOPPY_DISK");
	fileMenu->addChild("Save as...", NULL, "Ctrl + Shift + S", "FLOPPY_DISK");
	fileMenu->addSeparator();
	fileMenu->addChild("Import", NULL, "", "REPLY");
	fileMenu->addChild("Export", NULL, "", "FORWARD");
	fileMenu->addSeparator();
	fileMenu->addChild("Quit", &MainMenu::exitApplication, "Ctrl + Q", "EXIT");

	Menu::MenuItem* editMenu = m_menu->addMenuItem("Edit");
	editMenu->addChild("Undo", NULL, "Ctrl + Z");
	editMenu->addSeparator();
	editMenu->addChild("Cut", NULL, "Ctrl + X");
	editMenu->addChild("Copy", NULL, "Ctrl + C");
	editMenu->addChild("Paste", NULL, "Ctrl + V");
	editMenu->addSeparator();
	editMenu->addChild("Preferences...", &MainMenu::openPreferencesModal, "", "COG");

	Menu::MenuItem* windowMenu = m_menu->addMenuItem("Window");
	windowMenu->addChild("Fullscreen", &MainMenu::setFullscreen, "F11", "RESIZE_FULL");

	Menu::MenuItem* helpMenu = m_menu->addMenuItem("Help");
	helpMenu->addChild("Documentation", NULL, "", "HELP_CIRCLED");

	this->getLayout()->addWidget(m_menu);
}

 MainMenu::~MainMenu() {

	delete m_menu;
}


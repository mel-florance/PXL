#include "widgetState.h"

WidgetState::WidgetState()
{
	this->addState("dragged");
	this->addState("draggable");
	this->addState("hovered");
	this->addState("focused");
	this->addState("active");
	this->addState("visible");
	this->addState("closable");
	this->addState("checked");
	this->addState("checkable", true);
}

WidgetState::~WidgetState()
{

}

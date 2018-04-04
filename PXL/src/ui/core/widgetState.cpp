#include "widgetState.h"

WidgetState::WidgetState()
{
	this->addState("dragged");
	this->addState("draggable");
	this->addState("hovered");
	this->addState("focused");
	this->addState("active");
	this->addState("visible");
}

WidgetState::~WidgetState()
{

}

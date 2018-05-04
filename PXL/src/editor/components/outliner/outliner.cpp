
#include "outliner.h"
#include "engine.h"
#include "window.h"
#include "table.h"

 Outliner::Outliner(Engine & engine) {

	
}

void Outliner::init() {

	m_window = new Window("Outliner", this->getLayout()->getPosition(), this->getLayout()->getSize(), "segoeui");
	m_window->setDrawingShadow(false);

	Table* m_table = new Table(glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 299.0f), "segoeui");
	m_table->setExpandModeY(Widget::ExpandMode::LAYOUT);
	m_table->setExpandModeX(Widget::ExpandMode::LAYOUT);
	m_table->setPositionModeY(Widget::ExpandMode::LAYOUT);
	m_table->setPositionModeX(Widget::ExpandMode::LAYOUT);
	m_table->setMarginRight(13.0f);

	m_table->setName("outliner_table");

	m_window->addChild(m_table);
	this->getLayout()->addWidget(m_window);

	std::vector<Mesh*> meshes = this->getEngine()->getSceneManager()->getCurrentScene()->getMeshes();

	Table::Row* row = (Table::Row*)m_table->addRow();
	row->addColumn("Name");
	row->addColumn("Vertices");
	row->addColumn("Id");

	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		Table::Row* row = (Table::Row*)m_table->addRow();
		row->addColumn(meshes[i]->getName());
		row->addColumn(std::to_string(meshes[i]->getVertexCount()));
		row->addColumn(std::to_string(meshes[i]->getId()));
	}
}

 Outliner::~Outliner() {

	delete m_window;
	delete m_table;
}


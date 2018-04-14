#include "outliner.h"
#include "../../mesh/mesh.h"
#include "../..//core/engine.h"

Outliner::Outliner(Engine* engine) : EditorComponent(engine)
{
	
}

void Outliner::init()
{
	m_window = new Window("outliner", this->getLayout()->getPosition(), this->getLayout()->getSize(), "segoeui");
	m_window->setDrawingShadow(false);

	Table* m_table = new Table(glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 299.0f), "segoeui");
	m_table->setName("outliner_table");

	m_window->addChild(m_table);
	this->getLayout()->addWidget(m_window);

	std::vector<Mesh*> meshes = this->getEngine()->getSceneManager()->getCurrentScene()->getMeshes();

	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		Table::Row* row = (Table::Row*)m_table->addRow();
		row->addColumn(meshes[i]->getName());
		row->addColumn(std::to_string(meshes[i]->getVertexCount()));
		row->addColumn("lol");
	}
}

Outliner::~Outliner()
{
	delete m_window;
	delete m_table;
}

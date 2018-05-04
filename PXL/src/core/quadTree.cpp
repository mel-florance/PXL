
#include "quadTree.h"

 QuadTree::QuadTree() {

	m_topLeft = glm::vec2();
	m_botRight = glm::vec2();
	m_node = nullptr;
	m_topLeftTree = nullptr;
	m_topRightTree = nullptr;
	m_botLeftTree = nullptr;
	m_botRightTree = nullptr;
}

 QuadTree::QuadTree(const glm::vec2 & topLeft, const glm::vec2 & botRight) {

	m_node = nullptr;
	m_topLeftTree = nullptr;
	m_topRightTree = nullptr;
	m_botLeftTree = nullptr;
	m_botRightTree = nullptr;
	m_topLeft = topLeft;
	m_botRight = botRight;
}

void QuadTree::insert(Node & node) {

	if (node == nullptr)
		return;

	if (!inBoundary(node->m_position))
		return;

	if (abs(m_topLeft.x - m_botRight.x) <= 1 &&
		abs(m_topLeft.y - m_botRight.y) <= 1)
	{
		if (m_node == nullptr)
			m_node = node;
		return;
	}

	if ((m_topLeft.x + m_botRight.x) * 0.5f >= node->m_position.x)
	{
		if ((m_topLeft.y + m_botRight.y) * 0.5f >= node->m_position.y) 
		{
			if (m_topLeftTree == nullptr)
			{
				m_topLeftTree = new QuadTree(
					glm::vec2(m_topLeft.x, m_topLeft.y),
					glm::vec2((m_topLeft.x + m_botRight.x) * 0.5f, (m_topLeft.y + m_botRight.y) * 0.5f)
				);
			}

			m_topLeftTree->insert(node);
		}
		else
		{
			if (m_botLeftTree == nullptr)
			{
				m_botLeftTree = new QuadTree(
					glm::vec2(m_topLeft.x, (m_topLeft.y + m_botRight.y) * 0.5f),
					glm::vec2((m_topLeft.x + m_botRight.x) * 0.5f, m_botRight.y)
				);
			}

			m_botLeftTree->insert(node);
		}
	}
	else
	{
		if ((m_topLeft.y + m_botRight.y) * 0.5f >= node->m_position.y)
		{
			if (m_topRightTree == nullptr)
			{
				m_topRightTree = new QuadTree(
					glm::vec2((m_topLeft.x + m_botRight.x) * 0.5f, m_topLeft.y),
					glm::vec2(m_botRight.x, (m_topLeft.y + m_botRight.y) * 0.5f)
				);
			}

			m_topRightTree->insert(node);
		}
		else
		{
			if (m_botRightTree == nullptr)
			{
				m_botRightTree = new QuadTree(
					glm::vec2((m_topLeft.x + m_botRight.x) * 0.5f, (m_topLeft.y + m_botRight.y) * 0.5f),
					glm::vec2(m_botRight.x, m_botRight.y)
				);
			}

			m_botRightTree->insert(node);
		}
	}
}

Node QuadTree::search(const glm::vec2 & position) {

	if (!inBoundary(position))
		return nullptr;

	if (m_node != nullptr)
		return m_node;

	if ((m_topLeft.x + m_botRight.x) * 0.5f >= position.x)
	{
		if ((m_topLeft.y + m_botRight.y) * 0.5f >= position.y)
		{
			if (m_topLeftTree == nullptr)
				return nullptr;
			return m_topLeftTree->search(position);
		}
		else
		{ 
			if (m_botLeftTree == nullptr)
				return nullptr;
			return m_botLeftTree->search(position);
		}
	}
	else
	{
		if ((m_topLeft.y + m_botRight.y) * 0.5f >= position.y)
		{
			if (m_topRightTree == nullptr)
				return nullptr;
			return m_topRightTree->search(position);
		}
		else
		{
			if (m_botRightTree == nullptr)
				return nullptr;

			return m_botRightTree->search(position);
		}
	}
}

bool QuadTree::inBoundary(const glm::vec2 & position) {

	return (position.x >= m_topLeft.x &&
		position.x <= m_botRight.x &&
		position.y >= m_topLeft.y &&
		position.y <= m_botRight.y);
}

 QuadTree::~QuadTree() {

	if (m_node != nullptr)
		delete m_node;
	if (m_topLeftTree != nullptr)
		delete m_topLeftTree;
	if (m_topRightTree != nullptr)
		delete m_topRightTree;
	if (m_botLeftTree != nullptr)
		delete m_botLeftTree;
	if (m_botRightTree != nullptr)
		delete m_botRightTree;
}


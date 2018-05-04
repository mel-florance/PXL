#pragma once

#include <cmath>

#include <glm\glm.hpp>

struct Node 
{
	int m_data;
	glm::vec2 m_position;
	Node(const glm::vec2& position, int data) 
	{
		m_position = position; 
		m_data = data; 
	}

	Node()
	{
		m_data = 0;
	}
};

class QuadTree
{
public:
	QuadTree();
	QuadTree(const glm::vec2& topLeft, const glm::vec2& botRight);

	void insert(Node* node);
	Node* search(const glm::vec2& position);
	bool inBoundary(const glm::vec2& position);

	~QuadTree();

private:
	glm::vec2 m_topLeft;
	glm::vec2 m_botRight;

	Node* m_node;

	QuadTree* m_topLeftTree;
	QuadTree* m_topRightTree;
	QuadTree* m_botLeftTree;
	QuadTree* m_botRightTree;
};
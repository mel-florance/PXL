#ifndef _QUADTREE_H
#define _QUADTREE_H


struct Node {
    int m_data;

    glm::vec2 m_position;

    inline  Node(const glm::vec2 & position, int data);

    inline  Node();

};
inline  Node::Node(const glm::vec2 & position, int data) {
}

inline  Node::Node() {
}

class QuadTree {
  public:
     QuadTree();

     QuadTree(const glm::vec2 & topLeft, const glm::vec2 & botRight);

    void insert(Node & node);

    Node search(const glm::vec2 & position);

    bool inBoundary(const glm::vec2 & position);

     ~QuadTree();


  private:
    glm::vec2 m_topLeft;

    glm::vec2 m_botRight;

    Node * m_node;

    QuadTree * m_topLeftTree;

    QuadTree * m_topRightTree;

    QuadTree * m_botLeftTree;

    QuadTree * m_botRightTree;

};
#endif

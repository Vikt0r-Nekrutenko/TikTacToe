#ifndef NODE_HPP
#define NODE_HPP

#include "vec2d.hpp"
#include <fstream>
#include <vector>

using namespace stf;

class Node
{
  public:
  Node(Node *prev);
  Node* isMoveExist(const Vec2d& mv);
  void backpropagation();
  void backpropagation(uint8_t winner);

  void save(std::ofstream& file) const;
  void load(std::ifstream& file, Node* prev);

  Node *previous = nullptr;
  std::vector<Node*> next;

  uint8_t board[9];
  stf::Vec2d move {-1, -1};
  uint16_t wins = 0u;
  uint16_t games = 0u;
  uint8_t player {'o'};
};

#endif // NODE_HPP

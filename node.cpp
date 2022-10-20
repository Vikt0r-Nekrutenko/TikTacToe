#include "node.hpp"
#include <cstring>

Node::Node(Node *prev) : previous(prev) { memset(board, 'e', 9); }

Node *Node::isMoveExist(const Vec2d &mv)
{
    for(auto m : next) {
        if(m->move == mv) {
            return m;
        }
    }
    return this;
}

Node *Node::getMaxMove()
{
    Node* max = this;
    for(auto m : next) {
        if(max == this || m->wins > max->wins) {
            max = m;
        }
    }
    return max;
}

void Node::backpropagation() {
    // wins += 0.5;
    ++games;
    if(previous != nullptr)
        previous->backpropagation();
}

void Node::backpropagation(uint8_t winner)
{
    if(player == winner)
        ++wins;
    ++games;
    if(previous != nullptr)
        previous->backpropagation(winner);
}

void Node::save(std::ofstream& file) const
{
  file << player << " " <<
          move.x << " " <<
          move.y << " " <<
          wins << " " <<
          games << " ";
  for(uint8_t i : board) {
    file << i << " ";
  }
  file << next.size();
  file << std::endl;

  for(auto n : next) {
    n->save(file);
  }
}

void Node::load(std::ifstream& file, Node* prev)
{
  size_t next_c = 0;
  file >> player >> move.x >> move.y >> wins >> games;

  for(uint8_t& i : board) file >> i;
  file >> next_c;

  for(size_t i = 0; i < next_c; ++i) {
    next.push_back(new Node(prev));
    next.back()->load(file, next.back());
  }
}

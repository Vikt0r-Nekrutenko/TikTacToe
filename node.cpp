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

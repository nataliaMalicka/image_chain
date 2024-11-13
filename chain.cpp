#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
clear();
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
Node* lastNode = walk(head_, size());
Node* copiedNode = new Node(ndata);
lastNode->next = copiedNode;
length_++;
}


/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 * 
 */
void Chain::swap(int i, int j)
{
Node* nodeOne = walk(head_, i);
Node* prevToNodeOne = walk(head_, i - 1);

Node* nodeTwo = walk(head_, j);
Node* prevToNodeTwo = walk(head_, j - 1);

prevToNodeOne->next = prevToNodeTwo->next;
nodeTwo->next = nodeOne->next; 
nodeOne->next = nodeTwo->next;
prevToNodeTwo->next = prevToNodeOne->next;
}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
    Node* currNode = head_->next;
    head_->next = NULL; 
    while (currNode != NULL) {
        Node* toAdd = currNode;
        currNode = currNode->next;
        toAdd->next = head_->next;
        head_->next = toAdd;
    }
}

/*
* Modifies the current chain by "rotating" every k nodes by one position.
* In every k node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/
void Chain::rotate(int k)
{
    if (k <= 1) {
        return;
    }

    Node* prev = head_;
    Node* first = head_->next;
    Node* last = NULL;

    while (first != NULL) {
        last = walk(first, k - 1);
        if (last == NULL)
        {
            return;
        }

        prev->next = first->next;
        first->next = last->next;
        last->next = first;

        prev = first;
        first = prev->next;
    }
}

/**
 * Destroys ALL dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
Node* currNode = head_;
while (currNode != NULL) {
    Node* toDelete = currNode;
    currNode = currNode->next;
    delete toDelete;
}
length_=0;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
    head_ = new Node();
    head_->next = head_;
    width_ = other.width_;
    height_ = other.height_;
    length_ = 0;

Node* currNode = other.head_->next;
while (currNode != NULL) {
    insertBack(currNode->data);
    currNode = currNode->next;
}
}

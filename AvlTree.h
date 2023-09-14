//
// Created by Elijah on 11/7/2022.
//

#ifndef FINALPROJEXAMPLES_AVLTREE_H
#define FINALPROJEXAMPLES_AVLTREE_H

#define DEBUG

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x (with rebalancing)
// void remove( x )       --> Remove x (with rebalancing)
// bool contains( x )     --> Return true if x is present
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************

template<typename Comparable, typename Other>
class AvlTree {
private:
    //i have add a templeted vector to hold the documents and vector of int for the occurances of word withing a DocumentContents



    struct AvlNode {
        Comparable element;
        Other docs;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable &ele, const Other &v, AvlNode *lt, AvlNode *rt, int h = 0)
                : element{ele}, docs{v}, left{lt}, right{rt}, height{h} {}

    };

    AvlNode *root;
    AvlNode *curr;
    stack<AvlNode*> minStack;

public:
    /**
     * @brief Construct a new Avl Tree object
     */
    AvlTree() : root{nullptr} {
    }


    /**
     * @brief Copy constructor
     */
    AvlTree(const AvlTree &rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    ~AvlTree() {
        makeEmpty();
    }

    /**
     * Copy assignment operator
     */
    AvlTree &operator=(const AvlTree &rhs) {
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }

        return *this;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }
    void PrintPersistnece(ostream& Os){
        PrintP(Os,root);

    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree() const {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }

    /**
     * Print the tree structure.
     */
    void prettyPrintTree() const {
        prettyPrintTree("", root, false);
    }

    /**
     * Make the tree empty.
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x, const Other &d) {
        insert(x, d, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }


    Other &find(const Comparable &x) {
        AvlNode *node = find(x, root);
        if (node == nullptr) {
            node = insert(x, Other(), root);
        }
        return node->docs;
    }

    void setCurr() {
        fill(root);
        if (!minStack.empty()) {
            curr = minStack.top();
            minStack.pop();
        }
    }

    pair<Comparable, Other> getCurr() {
        return {curr->element, curr->docs};
    }

    bool hasNext() {
        return curr != nullptr;
    }

    void nextCurr() {
        if (minStack.empty()) {
            curr = nullptr;
        } else {
            curr = minStack.top();
            minStack.pop();
            if (curr->right != nullptr)
                fill(curr->right);
        }
    }

    void fill(AvlNode* n) {
        while (n != nullptr) {
            minStack.push(n);
            n = n->left;
        }
    }



private:
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */

    //I change my inser function to also implement the documents and the occurances of a word in that DocumentContents
    AvlNode *insert(const Comparable &x, const Other &d, AvlNode *&t) {
        if (t == nullptr) {
            //if it is a new word then push back the DocumentContents and the occurance of that word in that doucment to 1
            t = new AvlNode{x, d, nullptr, nullptr, 0};
            return t;
        } else if (x < t->element) {
            AvlNode *temp = insert(x, d, t->left);
            balance(t);
            return temp;
        } else if (t->element < x) {
            AvlNode *temp = insert(x, d, t->right);
            balance(t);
            return temp;
        } else {
            return t;
        }
    }

    AvlNode *find(const Comparable &key, AvlNode *&t) {
        if (t == nullptr || key == t->element) {
            return t;
        } else if (key < t->element) {
            return find(key, t->left);
        } else {
            return find(key, t->right);
        }
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable &x, AvlNode *&t) {
        throw std::runtime_error("Not implemented yet!");
        // same as in a binary search tree


        // don't forget to balance
        balance(t);
    }
    void PrintP(ostream& Ost,AvlNode *x){
        if(x== nullptr){
            return;
        }
        Ost << x->element;


        PrintP(Ost,x->left);
        PrintP(Ost,x->right);
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode *findMin(AvlNode *t) const {
        if (t == nullptr)
            return nullptr;

        if (t->left == nullptr)
            return t;

        return findMin(t->left);
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(const Comparable &x, AvlNode *t) const {
        if (t == nullptr)
            return false;

        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true; // Match
    }
    /****** NONRECURSIVE VERSION*************************
        bool contains( const Comparable & x, AvlNode *t ) const
        {
            while( t != nullptr )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else
                    return true;    // Match
            return false;   // No match
        }
    *****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t) {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const {
        if (t == nullptr)
            return nullptr;

        return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
    }

    // Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const {

        if (node == nullptr)
            return;

        std::cout << prefix;
        std::cout << (isRight ? "├──" : "└──");
        // print the value of the node
        std::cout << node->element << " ";
        //prints docs and occurances of that word in that doc
//        for (auto pair : node->docs) {
//            cout <<
//        }
        cout << std::endl;

        // enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);

    }

    // Avl manipulations

    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const {
        return t == nullptr ? -1 : t->height; //if nullptr set height to -1
    }

    static const int ALLOWED_IMBALANCE = 1; // 1 is the default; more will make balancing cheaper
    // but the search less efficient.

    // Assume t is balanced or within one of being balanced since we check this after each manipulation
    void balance(AvlNode *&t) //t is alpa
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) >
            ALLOWED_IMBALANCE)  //case1/2 is the difference more than one/unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t); // case 1 (outside)
            else
                doubleWithLeftChild(t); // case 2 (inside)
        } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) //case3/4 unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t); // case 4 (outside)
            else
                doubleWithRightChild(t); // case 3 (inside)
        }

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2) {
#ifdef DEBUG
        //cout << "need to rotateWithLeftChild for node " << k2->element << endl;
        // cout << "Before:" << endl;
        // prettyPrintTree();
#endif

        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
#ifdef DEBUG
        // cout << "After:" << endl;
        // prettyPrintTree();
#endif
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1) {
#ifdef DEBUG
        //cout << "need to rotateWithRightChild for node " << k1->element << endl;
        // cout << "Before:" << endl;
        // prettyPrintTree();

#endif

        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
#ifdef DEBUG
        //cout << "After:" << endl;
        // prettyPrintTree();
#endif
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3) {
#ifdef DEBUG
        //cout << "doubleWithLeftChild" << endl;
#endif
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1) {
#ifdef DEBUG
        //cout << "doubleWithRightChild" << endl;
#endif
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};

#endif //FINALPROJEXAMPLES_AVLTREE_H

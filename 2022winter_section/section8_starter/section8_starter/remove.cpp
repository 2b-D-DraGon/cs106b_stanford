/*
 * CS106B Section Handout Test Harness: Section 8
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Neel Kishnani for 
 * CS106B Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "testing/SimpleTest.h"
#include "node.h"
#include "utility.h"
#include "error.h"
#include "set.h"
using namespace std;

/*
 * Function: removeFrom
 * ---------------------
 * Given the root of a tree and a key to remove,
 * removes the key in-place.
 */

void removeFrom(Node*& root, int value) {
    Node* parent=nullptr;

    Node* cur=root;

    while(1){//找到匹配值以及其父节点
        if(value<cur->data&&cur->left!=nullptr){
            parent=cur;
            cur=cur->left;
        }
        if(value>cur->data&&cur->right!=nullptr){
            parent=cur;
            cur=cur->right;
        }
        if(value==cur->data){
            break;
        }
        break;
    }

    if(parent->left==cur){
        if(cur->left==nullptr&&cur->right==nullptr){//叶子节点
            parent->left=nullptr;
            delete cur;
            cur=nullptr;
        }

        else if(cur->left!=nullptr&&cur->right==nullptr){//只存在一个子节点
            parent->left=cur->left;
            delete cur;
            cur=nullptr;
        }

        else if(cur->left==nullptr&&cur->right!=nullptr){//只存在一个子节点
            parent->left=cur->right;
            delete cur;
            cur=nullptr;
        }
        else{//找左子树的最大值

            Node* childLeft=cur->left;
            Node* childParent=cur;


            while(childLeft->right!=nullptr){
                childParent=childLeft;
                childLeft=childLeft->right;
            }

            //此时childLeft是左子树最大值的节点，childParent是最大值节点的父节点

            cur->data=childLeft->data;

            delete childLeft;
            childParent->right=nullptr;

        }

    }
}

PROVIDED_TEST("Simple tests for remove function") {
    Node* tree = createTreeFromVector({/* Level 1*/ 5, /* Level 2*/ 3, EMPTY});
    Node* modified = createTreeFromVector({ 5 });
    removeFrom(tree, 3);
    EXPECT(treeEqual(tree, modified));
    freeTree(tree);
    freeTree(modified);
}

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
 * Function: areEqual
 * -------------------
 * Write a function that take as input pointers to the roots
 * of two binary trees (not necessarily binary search trees),
 * then returns whether the two trees have the exact same
 * shape and contents. Note that there is a solution for this
 * in this folder, but give this a try before looking!
 */

bool areEqual(Node* one, Node* two) {

    bool ret=true;

    if(one==nullptr&&two==nullptr){//如果两者为空则直接为true
        return true;
    }

    else if(one!=nullptr&&two!=nullptr){//两者都不为空再判断
        if(one->data!=two->data){//先判断这个节点是否相等
            return false;
        }

        if(one->left!=nullptr&&two->left!=nullptr){//都有左子树
            ret=ret&&areEqual(one->left,two->left);
            if(!ret){
                return false;
            }
        }
        else if(one->left==nullptr&&two->left==nullptr){//都没左子树，遍历结束
            return true;
        }
        else{
            return false;
        }

        if(one->right!=nullptr&&two->right!=nullptr){//都有右子树
            ret=ret&&areEqual(one->right,two->right);
            if(!ret){
                return false;
            }
        }
        else if(one->right==nullptr&&two->right==nullptr){//都没右子树
            return true;
        }
        else{
            return false;
        }

        return ret;
    }
    else{
        return false;
    }
}

PROVIDED_TEST("Simple Tests for Tree Equality") {
    Node *a = nullptr;
    Node *b = nullptr;

//    EXPECT(areEqual(a,b));

//    a = createTreeFromVector({/* Level 1*/ 1});
//    EXPECT(!areEqual(a,b));

//    b = createTreeFromVector({/* Level 1*/ 1});
//    EXPECT(areEqual(a,b));

//    // same values but different structure
//    freeTree(a);
//    a = createTreeFromVector({/* Level 1*/ 1, /* Level 2*/ 3, EMPTY});

//    freeTree(b);
//    b = createTreeFromVector({/* Level 1*/ 1, /* Level 2*/ EMPTY, 3});

//    EXPECT(!areEqual(a, b));

//    freeTree(a);
//    freeTree(b);

//    // one tree is a subset of another but not equal
//    a = createTreeFromVector({/* Level 1*/ 1, /* Level 2*/ 2, 3});
//    b = createTreeFromVector({/* Level 1*/ 1, /* Level 2*/ 2, 3, /* Level 3*/ 4, EMPTY, EMPTY, 2});
//    EXPECT(!areEqual(a, b));

//    // complex trees that are equal
//    freeTree(a);
//    freeTree(b);

    a = createTreeFromVector({/* Level 1*/ 1, /* Level 2*/ 2, 3, /* Level 3*/ 4, 7, EMPTY, 2, /* Level 4 */ 5});
    b = createTreeFromVector({/* Level 1*/ 1, /* Level 2*/ 2, 3, /* Level 3*/ 4, 7, EMPTY, 2, /* Level 4 */ 5});
    EXPECT(areEqual(a, b));

    freeTree(a);
    freeTree(b);
}


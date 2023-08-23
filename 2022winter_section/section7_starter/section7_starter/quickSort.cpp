/*
 * CS106B Section Handout Test Harness: Section 7
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Neel Kishnani for 
 * Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */
#include <iostream>
#include <string>
#include "testing/SimpleTest.h"
#include "cell.h"
#include "utility.h"
#include "error.h"
using namespace std;

/*
 * Function: quickSort
 * --------------------
 * Takes in a linked list and sorts it in-place using the 
 * quickSort algorithm.
 */



void quicksort(Cell*& list) {

    if(list->next->next=nullptr){
        return;
    }

    Vector<Cell*> lessV;//分的三个组
    Vector<Cell*> moreV;//存的是各个节点的地址
    Vector<Cell*> equalV;

    int valueF=list->value;
    Cell* cur=list->next;

    equalV.add(list);

    while(cur!=nullptr){

        if(cur->value==valueF){
            equalV.add(cur);
        }
        if(cur->value>valueF){
            moreV.add(cur);
        }
        if(cur->value<valueF){
            lessV.add(cur);
        }
        cur=cur->next;
    }


}

/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("Small test for quickSort") {
    Cell* list = createListFromVector({7, 5, 87, 41, 137, 1, 2});
    Cell* sorted = createListFromVector({1, 2, 5, 7, 41, 87, 137});
    quicksort(list);
    EXPECT(listEqual(list, sorted));
    freeList(list);
    freeList(sorted);
}

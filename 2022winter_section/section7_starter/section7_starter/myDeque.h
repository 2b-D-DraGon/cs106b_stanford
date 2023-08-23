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

#pragma once

#include <string>

class Deque {
public:
    Deque();
    ~Deque();

    /* Seems like all containers have the next two functions. :-) */
    bool isEmpty() const;
    int  size() const;

    /* Adds a value to the front or the back of the deque. */
    void pushFront(int value);
    void pushBack(int value);

    /* Looks at, but does not remove, the first/last element of the deque. */
    int peekFront() const;
    int peekBack() const;

    /* Returns and removes the first or last element of the deque. */
    int popFront();
    int popBack();
private:
    struct Cell {
           int value;
           Cell* next;
           Cell* prev;
       };
       Cell* head;
       Cell* tail;
       int   numElems; // Cache for efficiency; makes size() run in time O(1).

       /* Creates a new cell initialized to a given value, but whose next and prev
        * pointers are uninitialized. This cell is intended to be used inside the
        * linked list, and therefore the size field is adjusted appropriately.
        */
       Cell* makeCell(int value);

       /* Destroys the given cell, which is presumed to be in the linked list. */
       void destroy(Cell* toRemove);
};

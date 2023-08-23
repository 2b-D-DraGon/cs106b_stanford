/*
 * CS106B Section Handout Test Harness: Section 4
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified for Qt and Ed by Neel
 * Kishnani for Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "vector.h"
using namespace std;

/*
 * Function: isMeasurable
 * -----------------------
 * Write a recursive function that determines whether it is
 * possible to measure out the desired target amount with a
 * given set of weights, which is stored in the vector weights.
 */



bool isMeasurableRec(int target,Vector<int>& remainingWeights,Vector<int> &rWeight){

    int weightOfRight =0;

    for(int num:rWeight){
        weightOfRight+=num;
    }

    if(target==weightOfRight){//如果左右相等 则返回true
        return true;
    }
    else{//如果左右不相等并且已经没有了则返回false
        if(remainingWeights.isEmpty()){
            return false;
        }
    }

    int num =remainingWeights[0];
    remainingWeights.remove(0);//除去第一个数
    //放右边 改rWeights以及remianingWeights
    rWeight.add(num);
    bool Rside=isMeasurableRec(target,remainingWeights,rWeight);
    rWeight.remove(rWeight.size()-1);//新添加的给删除

    //放左边，则为改target and remianingWeights
    bool Lside=isMeasurableRec(target+num,remainingWeights,rWeight);

    //以及不放
    bool noneOfSides=isMeasurableRec(target,remainingWeights,rWeight);

    //将num放回去
    remainingWeights.insert(0,num);

    return Rside||Lside||noneOfSides;
}

bool isMeasurable(int target, const Vector<int>& weights) {
    /* todo: remove these lines and implement this function! */

    Vector<int>rWeight={};
    Vector<int> remainingWeights=weights;
    return isMeasurableRec(target,remainingWeights,rWeight);
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Run the provided examples.") {
    EXPECT_EQUAL(isMeasurable(2, {1, 3}), true);
    EXPECT_EQUAL(isMeasurable(5, {1, 3}), false);
    EXPECT_EQUAL(isMeasurable(6, {1, 3, 7}), true);
}

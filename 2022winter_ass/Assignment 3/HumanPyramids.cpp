#include "HumanPyramids.h"
#include "strlib.h"
#include "grid.h"
using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */

double weightOnBackOfMeo(int row, int col, int pyramidHeight,Grid<double>& tableOfCal) {
    /* TODO: Delete the next few lines and implement this function. */


    if(row<0||col<0||col>row||row>=pyramidHeight||col>=pyramidHeight){
        error("out bounds! ");
    }

    if(row==0&&col==0){
        return 0;
    }
    if(col==0){//左边界
        if(tableOfCal.get(row-1,col)!=0.0){
            return 80.0+tableOfCal.get(row-1,col)/2.0;
        }else{
            double returnValue=80+weightOnBackOfMeo(row-1,col,pyramidHeight,tableOfCal)/2.0;
            tableOfCal.set(row,col,returnValue);
            return returnValue;
        }
    }
    else if(col==row){//右边界
        if(tableOfCal.get(row-1,col-1)!=0.0){
            return 80.0+tableOfCal.get(row-1,col-1)/2.0;
        }else{
            double returnValue=80+weightOnBackOfMeo(row-1,col-1,pyramidHeight,tableOfCal)/2.0;
            tableOfCal.set(row,col,returnValue);
            return returnValue;
        }
    }
    else{
        if(tableOfCal.get(row-1,col-1)!=0.0&&tableOfCal.get(row-1,col)!=0.0){//如果上面的两个都存在则直接返回两个的一半
            return 160+tableOfCal.get(row-1,col-1)/2.0+tableOfCal.get(row-1,col)/2.0;
        }
        else if(tableOfCal.get(row-1,col-1)==0.0&&tableOfCal.get(row-1,col)!=0.0){//如果一个存在一个不存在
            double returnValueOfLeft=weightOnBackOfMeo(row-1,col-1,pyramidHeight,tableOfCal);//计算出来不存在的
            tableOfCal.set(row,col,160+returnValueOfLeft/2.0+tableOfCal.get(row-1,col)/2.0);//插入
            return tableOfCal.get(row,col);//返回插入值
        }
        else if(tableOfCal.get(row-1,col-1)!=0.0&&tableOfCal.get(row-1,col)==0.0){
            double returnValueOfRight=weightOnBackOfMeo(row-1,col,pyramidHeight,tableOfCal);//计算出来不存在的
            tableOfCal.set(row,col,160+returnValueOfRight/2.0+tableOfCal.get(row-1,col-1)/2.0);
            return tableOfCal.get(row,col);
        }
        else{//两边都不存在
            double returnValueOfLeft=weightOnBackOfMeo(row-1,col-1,pyramidHeight,tableOfCal);//计算出来不存在的
            double returnValueOfRight=weightOnBackOfMeo(row-1,col,pyramidHeight,tableOfCal);//计算出来不存在的
            tableOfCal.set(row,col,160+returnValueOfRight/2.0+returnValueOfLeft/2.0);
            return tableOfCal.get(row,col);
        }
    }

}

double weightOnBackOf(int row, int col, int pyramidHeight) {
    /* TODO: Delete the next few lines and implement this function. */


    Grid<double> tableOfCal(pyramidHeight,pyramidHeight,0.0);

    return weightOnBackOfMeo(row,col,pyramidHeight,tableOfCal);
}






/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */














/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */
//    SHOW_ERROR("This test is configured to always fail until you delete this line from\n         HumanPyramids.cpp. Once you have implemented memoization and want\n         to check whether it works correctly, remove the indicated line.");

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */

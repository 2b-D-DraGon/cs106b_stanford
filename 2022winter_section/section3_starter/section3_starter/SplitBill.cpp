/*
 * CS106B Section Handout Test Harness: Section 3
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
#include "set.h"
#include "error.h"
using namespace std;

/*
 * Function: listPossiblePayments
 * -------------------------------
 * Write a function that takes as input a total amount of money
 * to pay (in dollars) and a set of all the people who ordered
 * something, then lists off every possible way you could split
 * the bill, assuming everyone pays a whole number of dollars.
 */
//void listPossiblePayments(int total, const Set<string>& people) {  自己的实现

//    if(people.isEmpty())//为空则此次递归完毕
//    {
//        return;
//    }


//    Set<string> people1;
//    people1+=people;//将people的值复制到peolpe1
//    people1.remove(people1.first());//每次将最前面的一个去掉

//    if(total==0)//剩余值为零时则将剩下所有的输出等于0
//    {
//        for(string person:people)
//        {
//            cout<<person <<":$0 ";
//        }
//        cout<<endl;
//        return;
//    }

//    if(people.size()==1)
//    {
//        cout<<people.first()<<":$"<<total<<endl;
//        return;
//    }

//    for(string person:people1)
//    {

//        for(int j = total;j>=0;j--)//从大到小排列
//        {

//            cout<<people.first()<<":$"<<j<<" ";
//            listPossiblePayments(total-j,people1);
//        }
//    }


//    return;
//}


void listPossiblePaymentsRec(int total, const Set<string>& people,
                             const Map<string, int>& payments) {

    if(people.size()==1)
    {
        Map<string,int> finalpayments=payments;
        finalpayments[people.first()]=total;
        cout<<finalpayments<<endl;
    }
    else{
        for(int payment =0;payment<=total;payment++)
        {
            Map<string,int> updatepayments=payments;
            updatepayments[people.first()]=payment;
            listPossiblePaymentsRec(total-payment,people-people.first(),updatepayments);
        }

    }

}

void listPossiblePayments(int total, const Set<string>& people) {
    /* Edge cases: we can't pay a negative total, and there must be at least one
     * person.
     */
    if (total < 0) error("Guess you're an employee?");
    if (people.isEmpty()) error("Dine and dash?");

    listPossiblePaymentsRec(total, people, {});
}
/* * * * * Provided Tests Below This Point * * * * */

/*
 * Since this is a void function, we don't have a return value to verify with.
 * We will instead just run your code to make sure there is no obvious error.
 */
PROVIDED_TEST("Provided Test: Run the provided example. There should be 15 entries.") {
    Set<string> s = {"A", "B", "C"};
    listPossiblePayments(4, s);
}

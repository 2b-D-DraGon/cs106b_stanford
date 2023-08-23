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
#include "map.h"
using namespace std;

/*
 * Function: listLegalOrderingsOf
 * -------------------------------
 * Write a function that takes as input a Map representing the
 * prerequisite structure, then lists all possible orders in which
 * you could complete those tasks without violating the
 * prerequisites. The prereqs map is structured so that each key
 * is a task and each value is the set of that task’s immediate prerequisites.
 * See section handout for more details
 */

//bool v1Contains(Vector<string> v1,string name){
//    for(string naMe:v1){//遍历v1
//        if(naMe==name){
//            return true;
//        }
//    }
//    return false;
//}

//void printList(Vector<string> v1,Map<string, Set<string>> prereq,int total)
//{

//    if(v1.size()==total){//容器中已满则输出容器
//        cout<<v1<<endl;
//        return;
//    }

//    else{//遇见就判断是否包含前提条件 不包含就不添加，包含就添加
//        for(string name : prereq){//遍历key
//            int i=0;
//            for(string nAme:prereq[name]){//遍历value的前提条件
//                if(v1Contains(v1,nAme)){
//                    i++;
//                    continue;
//                }
//                else{
//                    break;//不包含就在暂时不考虑这个课
//                }
//            }
//            if(i==prereq[name].size()){//运行到这里是就是要么break，直接退出。要么就是都包含了
//                v1.add(name);//添加了就进行下一次的递归
//            }
//            printList(v1,prereq,total);
//        }
//    }


//}

//void listLegalOrderingsOf(const Map<string, Set<string>>& prereqs) {

//    Vector<string> v1;
//    if(v1.isEmpty()){//寻找开头
//        for(string name : prereqs){
//            if(prereqs[name].equals({ }))
//            {
//                v1.add(name);
//            }
//        }
//    }

//    Map<string, Set<string>> prereq;
//    prereq+=prereqs;
//    prereq.remove(v1[0]);

//    int n=0;
//    for(string name:prereq){
//        n+=prereq[name].size();
//    }

//    printList(v1,prereq,n);
//}

void listLegalOrderingsRec(const Map<string, Set<string>>& prereqs,
                           const Vector<string>& tasksPerformed,
                           const Set<string>& tasksRemaining) {

    if(tasksRemaining.isEmpty()){//待做的事情如果为空则说明这次的递归已经到达的尽头
        cout<<tasksPerformed<<endl;
    }

    Set<string> taskDone;

    for(string task:tasksPerformed){
        taskDone+=task;
    }

    for(string task: tasksRemaining){
        if(prereqs[task].isSubsetOf(taskDone)){
            Vector<string> newTasks=tasksPerformed;
            newTasks+=task;

            Set<string> remainingTasks=tasksRemaining;
            remainingTasks.remove(task);

            listLegalOrderingsRec(prereqs,newTasks,remainingTasks);
        }
    }



}

void listLegalOrderingsOf(const Map<string, Set<string>>& prereqs) {
    Set<string> tasks;

    for(string task:prereqs){
        tasks+=task;
    }


    listLegalOrderingsRec(prereqs,{},tasks);
}


/* * * * * Provided Tests Below This Point * * * * */

/*
 * Since this is a void function, we don't have a return value to verify with.
 * We will instead just run your code to make sure there is no obvious error.
 */
PROVIDED_TEST("Provided Test: Run the provided example. There should be 16 entries.") {
    Map<string, Set<string>> prereqs = {
        {"CS103", { "CS106A" }},
        {"CS106A", { }},
        {"CS106B", { "CS106A" }},
        {"CS107", { "CS106B" }},
        {"CS109", { "CS103", "CS106B" }},
        {"CS110", { "CS107" }},
        {"CS161", { "CS109" }}
    };
    listLegalOrderingsOf(prereqs);
}

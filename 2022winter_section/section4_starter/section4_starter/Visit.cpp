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
#include "set.h"
#include "map.h"
#include "cmath"
using namespace std;

/*
 * Function: canVisitAllSites
 * ---------------------------
 * Write a function that takes as input a list of all the
 * sites you’d like to visit and an amount of free time
 * available to you and returns whether it’s possible to
 * visit all those sites in the allotted time (assume you’ve
 * already factored inthe cost of speaking at each site
 * and that you’re just concerned about the travel time.)
 */

double timeCost(GPoint a,GPoint b){

    double x =(a.x-b.x)*(a.x-b.x);
    double y=(a.y-b.y)*(a.y-b.y);

    return sqrt(x+y);
}

bool canVisitAllSitesRec(Vector<GPoint>& sites, double travelTimeAvailable,GPoint lastDes,Vector<GPoint>& result,Map<GPoint,bool> onceGone){
//    if(sites.isEmpty()&&travelTimeAvailable>=0){//当目的地已经没有了 并且还有空余时间则可行
//        return true;
//    }
    // base
    if(sites.size()==1&&timeCost(sites[0],lastDes)<travelTimeAvailable){//只剩最后一个目的地
        return true;
    }
//    else if(!sites.isEmpty()&&travelTimeAvailable>=0)
    else{
        //不去这个地方，那么剩余的不变，旅行时间不变，上一个目的地不变，旅行记录不变但是将这个位置给放到最后
        if(onceGone[sites[0]]){
            return false;
        }
        GPoint noGoStr=sites[0];
        sites=sites.subList(1,sites.size()-1);//截取除了第一个以外的其他子串
        sites.add(noGoStr);//将这个目的地放在最后
        onceGone[noGoStr]=true;
        bool noGo=canVisitAllSitesRec(sites,travelTimeAvailable,lastDes,result,onceGone);

        //undo
        sites=sites.subList(0,sites.size()-1);
        sites.insert(0,noGoStr);

        //去这个地方,改变剩余的没去的地方，旅行时间改变，目的地改变，结果改变
        double cost=timeCost(sites[0],lastDes);//计算时间消耗
        result.add(sites[0]);//将这个添加进已经去的地方
        sites=sites.subList(1,sites.size()-1);//将这个给去掉
        bool Go=canVisitAllSitesRec(sites,travelTimeAvailable-cost,sites[0],result,onceGone);

        //undo
        sites.insert(0,noGoStr);

        return Go||noGo;

    }
//    return false;
}

//bool canVisitAllSitesRec(Vector<GPoint>& sites, double travelTimeAvailable,GPoint lastDes){
//    if(sites.isEmpty()&&travelTimeAvailable>=0){//当目的地已经没有了 并且还有空余时间则可行
//        return true;
//    }
//    else if(!sites.isEmpty()&&travelTimeAvailable>=0){
//        double cost=timeCost(sites[0],lastDes);
//        lastDes=sites[0];
//        sites=sites.subList(1,sites.size()-1);
//        return canVisitAllSitesRec(sites,travelTimeAvailable-cost,lastDes);
//    }
//    return false;
//}

bool canVisitAllSites(const Vector<GPoint>& sites, double travelTimeAvailable) {
    /* todo: remove these lines and implement this function! */
    Vector<GPoint> site=sites;
    site=site.subList(1,site.size()-1);
    Vector<GPoint> result;
    result.add(sites[0]);

    Map<GPoint,bool> onceGone;
    for(GPoint address:sites){
        onceGone.put(address,false);
    }

    return canVisitAllSitesRec(site,travelTimeAvailable,sites[0],result,onceGone);
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Simple examples!") {
    Vector<GPoint> sites1 = {{0, 0}, {5, 5}};
    Vector<GPoint> sites2 = {{0, 0}, {2, 2}, {5, 5}};
    EXPECT_EQUAL(canVisitAllSites(sites1, 8), true);
    EXPECT_EQUAL(canVisitAllSites(sites2, 8), true);
}

#include "DisasterPlanning.h"
using namespace std;

/* TODO: Refer to DisasterPlanning.h for more information about this function.
 * Then, delete this comment.
 */





/* 这个是我自己写的 其他案例都能通过 但是最后两个指数级的案例无法通过，证明我的递归不够简洁
bool canBeMadeDisasterReadyRec(const Map<string, Set<string>>& roadNetwork,
                               int numCities,
                               Set<string>& supplyLocations,
                               Set<string>& tempLocations,
                               Set<string>& remainingCity,
                               Set<string>& isOver,
                               Set<string>& notSet) {

    if(numCities==0){//剩余量为零
        if(isOver.size()==roadNetwork.size()){//当所有城市全部被覆盖
            supplyLocations=tempLocations;
            return true;
        }
        else{
            return false;
        }
    }

    if(isOver.size()==roadNetwork.size()){//当所有城市全部被覆盖
        supplyLocations=tempLocations;
        return true;
    }

    bool ret=false;


    //首先将自己设定为灾难放置城市

    int numForLoop;

    string cityNow=remainingCity.first();//记录当前判断的城市名


    Set<string> nerOfCityNow=roadNetwork[cityNow];//记录当前判断的城市的邻居城市

    Set<string> newOver={};

    //处理边缘情况，如果此城市已经是被覆盖且只有一个邻居时（因为还在队列中说明邻居是已放置的）这是没有必要去判断这个城市

    if(isOver.contains(cityNow)&&nerOfCityNow.size()==1){
        remainingCity.remove(cityNow);
        ret=ret||canBeMadeDisasterReadyRec(roadNetwork,//进行已经将这个城市设定为放置城市后的递归
                                  numCities,
                                  supplyLocations,
                                  tempLocations,
                                  remainingCity,
                                  isOver,
                                  notSet);
        remainingCity.add(cityNow);

        return ret;
    }


    //若此城市不是边缘情况


    if(!isOver.contains(cityNow)){//将此城市设定为覆盖范围内
        isOver.add(cityNow);
        newOver.add(cityNow);
    }

    numForLoop=nerOfCityNow.size();

    for(int i=0;i<numForLoop;i++){
        if(!isOver.contains(nerOfCityNow.first())){//将此城市设的所有邻居城市定为覆盖范围内
            isOver.add(nerOfCityNow.first());//并且记录新加的覆盖城市用以回溯
            newOver.add(nerOfCityNow.first());
        }
        nerOfCityNow.remove(nerOfCityNow.first());
    }

    remainingCity.remove(cityNow);//此城市已经被考虑，所以删除

    tempLocations.add(cityNow);//暂时将这个城市放入设置城市队列

    ret=ret||canBeMadeDisasterReadyRec(roadNetwork,//进行已经将这个城市设定为放置城市后的递归
                              numCities-1,
                              supplyLocations,
                              tempLocations,
                              remainingCity,
                              isOver,
                              notSet);

    numForLoop=newOver.size();

    for(int i=0;i<numForLoop;i++){//回溯 并且NEWOVER此时为空
        isOver.remove(newOver.first());
        newOver.remove(newOver.first());
    }

    remainingCity.add(cityNow);

    tempLocations.remove(cityNow);

    nerOfCityNow=roadNetwork[cityNow];//恢复

    if(ret){
        return true;
    }










    //如果不准备将这个城市设定为灾难放置城市，那么就需要将邻居城市放置为灾难城市。都要判断前面是否希望此邻居城市被设置为放置城市
    //如果邻居城市为1，那么就必须将此邻居城市设定为放置城市
    //如果邻居城市不为1时多了一种情况，不将我设置的情况还有一种就是我已经被覆盖，那么这时邻居城市也不一定要设置为放置城市











    //邻居城市唯一,这时候还要不允许下面的递归将我设定为放置城市的情况发生，所以要设置一个标志表示不允许再将我设置为放置城市(notSet)

    if(isOver.contains(cityNow)){//如果我已经被覆盖，并且我的这个邻居的邻居数目不为1（也就是我的邻居不需要一定是放置城市也能被覆盖的情况），
        //这时可以将我和这个邻居都设置为不放置，它并不需要我这个邻居来决定，而是可以自己决定自己，所以仍然在待处理的状态中

        remainingCity.remove(cityNow);//表示已处理此城市

        ret=ret||canBeMadeDisasterReadyRec(roadNetwork,//进行已经将这个城市设定为放置城市后的递归
                                  numCities,
                                  supplyLocations,
                                  tempLocations,
                                  remainingCity,
                                  isOver,
                                  notSet);

        remainingCity.add(cityNow);
    }


    if(nerOfCityNow.size()==1&&!tempLocations.contains(cityNow)){

        if(!notSet.contains(nerOfCityNow.first())){//前面允许此邻居城市被设置为放置城市
            Set<string> nerOfNer=roadNetwork[nerOfCityNow.first()];

            notSet.add(cityNow);

            if(!isOver.contains(nerOfCityNow.first())){//将城市设定为已覆盖
                isOver.add(nerOfCityNow.first());
                newOver.add(nerOfCityNow.first());
            }

            numForLoop=nerOfNer.size();

            for(int i=0;i<numForLoop;i++){//将所有邻居城市设定为已覆盖
                if(!isOver.contains(nerOfNer.first())){
                    isOver.add(nerOfNer.first());
                    newOver.add(nerOfNer.first());
                }
                nerOfNer.remove(nerOfNer.first());
            }

            tempLocations.add(nerOfCityNow.first());//将此城市暂定为放置城市

            remainingCity.remove(nerOfCityNow.first());//表示已处理此城市

            remainingCity.remove(cityNow);//表示不需要再处理此城市或者此城市的邻居


            ret=ret||canBeMadeDisasterReadyRec(roadNetwork,//进行已经将这个城市设定为放置城市后的递归
                                      numCities-1,
                                      supplyLocations,
                                      tempLocations,
                                      remainingCity,
                                      isOver,
                                      notSet);

            numForLoop=newOver.size();

            for(int i=0;i<numForLoop;i++){//回溯 并且NEWOVER此时为空
                isOver.remove(newOver.first());
                newOver.remove(newOver.first());
            }

            tempLocations.remove(nerOfCityNow.first());

            remainingCity.add(nerOfCityNow.first());

            remainingCity.add(cityNow);

            notSet.remove(cityNow);

            if(ret){
                return true;
            }
        }
        else{
            return false;//只有一个邻居城市 我不设置为，邻居也不设置为，不可能完成，所以直接返回false
        }
    }
    else{//邻居城市不为一

        int numOfCityNowNer=nerOfCityNow.size();

        for(int i =0;i<numOfCityNowNer;i++){//对每个邻居进行判断

            Set<string> nerOfNer=roadNetwork[nerOfCityNow.first()];//得出此邻居的邻居

            if(tempLocations.contains(nerOfCityNow.first())){//如果邻居已经被放置了
                nerOfCityNow.remove(nerOfCityNow.first());
                continue;
            }

            notSet.add(cityNow);//希望下次选择邻居城市的时候，不选择将这个城市设定为邻居城市

            if(!isOver.contains(nerOfCityNow.first())){//将城市设定为已覆盖
                isOver.add(nerOfCityNow.first());
                newOver.add(nerOfCityNow.first());
            }

            numForLoop=nerOfNer.size();

            for(int i=0;i<numForLoop;i++){//将所有邻居城市设定为已覆盖
                if(!isOver.contains(nerOfNer.first())){
                    isOver.add(nerOfNer.first());
                    newOver.add(nerOfNer.first());
                }
                nerOfNer.remove(nerOfNer.first());
            }

            tempLocations.add(nerOfCityNow.first());//将此城市暂定为放置城市

            remainingCity.remove(nerOfCityNow.first());//表示已处理此城市

            remainingCity.remove(cityNow);//表示不需要再处理此城市或者此城市的邻居

            ret=ret||canBeMadeDisasterReadyRec(roadNetwork,//进行已经将这个城市设定为放置城市后的递归
                                      numCities-1,
                                      supplyLocations,
                                      tempLocations,
                                      remainingCity,
                                      isOver,
                                      notSet);

            numForLoop=newOver.size();

            for(int i=0;i<numForLoop;i++){//回溯 并且NEWOVER此时为空
                isOver.remove(newOver.first());
                newOver.remove(newOver.first());
            }

            tempLocations.remove(nerOfCityNow.first());

            remainingCity.add(nerOfCityNow.first());

            remainingCity.add(cityNow);

            notSet.remove(cityNow);

            nerOfCityNow.remove(nerOfCityNow.first());//进行下一次循环的判断

            if(ret){
                return true;
            }
        }

    }


    return ret;
}


bool canBeMadeDisasterReady(const Map<string, Set<string>>& roadNetwork,
                            int numCities,
                            Set<string>& supplyLocations) {

    if(numCities<0) error("numCities shoule be positive");

    if(numCities==0&&roadNetwork.size()!=0) {
        return false;
    }


    if(roadNetwork.size()==0) return true;

    Vector<string> keysOfCity=roadNetwork.keys();

    Set<string> remainingCity;

    int n=keysOfCity.size();

    Set<string> isOver={};

    Set<string> tempLocations={};

    Set<string> notSet={};//当设置邻居城市的时候判断前面希不希望在将此邻居城市设定为放置城市

    for(int i=0;i<n&&numCities>0;i++){
        if(roadNetwork[keysOfCity[i]].isEmpty()){//如果有不连接的,提前处理掉
            numCities--;
            isOver.add(keysOfCity[i]);
            tempLocations.add(keysOfCity[i]);
            supplyLocations.add(keysOfCity[i]);
        }
        else{//否则就放入待处理城市中
            remainingCity.add(keysOfCity[i]);
        }
    }

    if(numCities==0){
        if(isOver.size()==roadNetwork.size())
        {
            return true;
        }
        else{
            return false;
        }
    }

    if(remainingCity.isEmpty()){//如果为空则证明所有的城市都被分配了
        return true;
    }

    return canBeMadeDisasterReadyRec(roadNetwork,
                                     numCities,
                                     supplyLocations,
                                     tempLocations,
                                     remainingCity,
                                     isOver,
                                     notSet);
}

*/

//别人的答案 非常神奇的算法 让人很无奈又羡慕
bool DisasterHelper(const Map<string, Set<string>>& roadNetwork,
                    int numCities,
                    Set<string>& supplyLocations,
                    Set<string>& uncoveredCity) {
    /* if all cities have been covered ,return ture. */
    if (uncoveredCity.isEmpty()){
        return true;
    }
    else if (numCities == 0 && !uncoveredCity.isEmpty()){
        return false;
    }
    /* An empty net always stays ready */
    if (roadNetwork.isEmpty()){
        return true;
    }

    string city = uncoveredCity.first();

    /* choose the city as supplylocation */
    supplyLocations.add(city);
    Set<string> trythis = uncoveredCity - city - roadNetwork[city];
    if(DisasterHelper(roadNetwork, numCities - 1, supplyLocations,trythis)){
        return true;
    }
    else{
        supplyLocations.remove(city);
    }

    /* choose surrounding cities as supplylocation */
    for (string neighbor: roadNetwork[city]){
        supplyLocations.add(neighbor);
        trythis = uncoveredCity - neighbor - roadNetwork[neighbor];
        if(DisasterHelper(roadNetwork, numCities - 1, supplyLocations,trythis)){
            return true;
        }
        else{
            supplyLocations.remove(neighbor);
        }
    }
    return false;
}


bool canBeMadeDisasterReady(const Map<string, Set<string>>& roadNetwork,
                            int numCities,
                            Set<string>& supplyLocations) {
    if (numCities < 0){
        error("Haiya!Negtive number!");
    }
    Set<string> uncoveredCity;
    for (string city: roadNetwork){
        uncoveredCity += city;
    }
    return DisasterHelper(roadNetwork, numCities, supplyLocations, uncoveredCity);
}







/* * * * * * * Test Helper Functions Below This Point * * * * * */



#include "GUI/SimpleTest.h"

/* This is a helper function that's useful for designing test cases. You give it a Map
 * of cities and what they're adjacent to, and it then produces a new Map where if city
 * A links to city B, then city B links back to city A. We recommend using this helper
 * function when writing tests, though you won't need it in your implementation of the main
 * canBeMadeDisasterReady function.
 */
Map<string, Set<string>> makeSymmetric(const Map<string, Set<string>>& source) {
    Map<string, Set<string>> result = source;

    for (const string& from: source) {
        for (const string& to: source[from]) {
            result[from] += to;
            result[to] += from;
        }
    }

    return result;
}

/* This helper function tests whether a city has been covered by a set of supply locations
 * and is used by our testing code. You're welcome to use it in your tests as well!
 */
bool isCovered(const string& city,
               const Map<string, Set<string>>& roadNetwork,
               const Set<string>& supplyLocations) {
    if (supplyLocations.contains(city)) return true;

    for (string neighbor: roadNetwork[city]) {
        if (supplyLocations.contains(neighbor)) return true;
    }

    return false;
}


/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Add your own custom tests here! */


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Reports an error if numCities < 0") {
    Set<string> supply;
    EXPECT_ERROR(canBeMadeDisasterReady({}, -137, supply));
}

PROVIDED_TEST("Works for map with no cities.") {
    Set<string> locations;

    /* The number of cities we use really doesn't matter here. */
    EXPECT(canBeMadeDisasterReady({}, 0, locations));
    EXPECT_EQUAL(locations.size(), 0);

    EXPECT(canBeMadeDisasterReady({}, 137, locations));
    EXPECT_EQUAL(locations.size(), 0);
}

PROVIDED_TEST("Works for map with one city.") {
    Map<string, Set<string>> map = makeSymmetric({
         { "Solipsist", {} }
    });

    /* Shouldn't matter how many cities we use, as long as it isn't zero! */
    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT( canBeMadeDisasterReady(map, 1, locations1));
    EXPECT( canBeMadeDisasterReady(map, 2, locations2));
}

PROVIDED_TEST("Works for map with one city, and produces output.") {
    Map<string, Set<string>> map = makeSymmetric({
         { "Solipsist", {} }
    });

    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(canBeMadeDisasterReady(map, 2, locations2));

    /* Don't check locations0; since the function returned false, the values there
     * can be anything.
     */
    Set<string> expected = { "Solipsist" };
    EXPECT_EQUAL(locations1, expected);
    EXPECT_EQUAL(locations2, expected);
}

PROVIDED_TEST("Works for map with two linked cities.") {
    Map<string, Set<string>> map = makeSymmetric({
         { "A", { "B" } },
         { "B", {     } }
    });

    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(canBeMadeDisasterReady(map, 2, locations2));
}

PROVIDED_TEST("Works for map with two linked cities, and produces output.") {
    Map<string, Set<string>> map = makeSymmetric({
         { "A", { "B" } },
    });

    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(canBeMadeDisasterReady(map, 2, locations2));

    EXPECT_EQUAL(locations1.size(), 1);
    EXPECT(locations1.isSubsetOf({"A", "B"}));

    EXPECT(locations2.size() <= 2);
    EXPECT(locations2.isSubsetOf({"A", "B"}));
}

PROVIDED_TEST("Works for four disconnected cities.") {
    Map<string, Set<string>> map = makeSymmetric({
        { "A", { } },
        { "B", { } },
        { "C", { } },
        { "D", { } }
    });

    Set<string> locations0, locations1, locations2, locations3, locations4;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(!canBeMadeDisasterReady(map, 2, locations2));
    EXPECT(!canBeMadeDisasterReady(map, 3, locations3));
    EXPECT(canBeMadeDisasterReady(map, 4, locations4));
}

PROVIDED_TEST("Works for four disconnected cities, and produces output.") {
    Map<string, Set<string>> map = makeSymmetric({
        { "A", { } },
        { "B", { } },
        { "C", { } },
        { "D", { } }
    });

    Set<string> locations0, locations1, locations2, locations3, locations4;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(!canBeMadeDisasterReady(map, 2, locations2));
    EXPECT(!canBeMadeDisasterReady(map, 3, locations3));
    EXPECT(canBeMadeDisasterReady(map, 4, locations4));

    Set<string> expected = { "A", "B", "C", "D" };
    EXPECT_EQUAL(locations4, expected);
}

PROVIDED_TEST("Can solve ethene example, regardless of ordering.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over the cities when making decisions is sensitive
     * to the order of those cities' names. This test looks at a map like
     * this one, trying out all possible orderings of the city names:
     *
     *             *
     *             |
     *        * -- * -- * -- *
     *                  |
     *                  *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * cities. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly
     * covering and uncovering cities at each step. On the other hand, if
     * your code runs into issues here, it may indicate that the way in which
     * you're covering and uncovering cities accidentally uncovers a city that
     * you have previously covered.
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* Ethene arrangement:
         *
         *        0
         *       1234
         *         5
         */
        Map<string, Set<string>> map = makeSymmetric({
            { cities[2], { cities[0], cities[1], cities[3] } },
            { cities[3], { cities[4], cities[5] } }
        });

        /* We should be able to cover everything with two cities:
         * city 2 and city 3.
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        /* We should not be able to cover everything with one city. */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Can solve ethene example, regardless of ordering, and produces output.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over the cities when making decisions is sensitive
     * to the order of those cities' names. This test looks at a map like
     * this one, trying out all possible orderings of the city names:
     *
     *             *
     *             |
     *        * -- * -- * -- *
     *                  |
     *                  *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * cities. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly
     * covering and uncovering cities at each step. On the other hand, if
     * your code runs into issues here, it may indicate that the way in which
     * you're covering and uncovering cities accidentally uncovers a city that
     * you have previously covered.
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* Ethene arrangement:
         *
         *        0
         *       1234
         *         5
         */
        Map<string, Set<string>> map = makeSymmetric({
            { cities[2], { cities[0], cities[1], cities[3] } },
            { cities[3], { cities[4], cities[5] } }
        });

        /* We should be able to cover everything with two cities:
         * city 2 and city 3.
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        EXPECT_EQUAL(chosen.size(), 2);
        EXPECT(chosen.contains(cities[2]));
        EXPECT(chosen.contains(cities[3]));

        /* We should not be able to cover everything with one city. */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Works for six cities in a line, regardless of order.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over the cities when making decisions is sensitive
     * to the order of those cities' names. This test looks at a map like
     * this one, trying out all possible orderings of the city names:
     *
     *        * -- * -- * -- * -- * -- *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * cities in a line. If your code is able to solve the problem correctly
     * for all of those orderings, there's a good chance that you're correctly
     * covering and uncovering cities at each step. On the other hand, if
     * your code runs into issues here, it may indicate that the way in which
     * you're covering and uncovering cities accidentally uncovers a city that
     * you have previously covered.
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* Linear arrangement. */
        Map<string, Set<string>> map;
        for (int i = 1; i + 1 < cities.size(); i++) {
            map[cities[i]] = { cities[i - 1], cities[i + 1] };
        }

        map = makeSymmetric(map);

        /* We should be able to cover everything with two cities, specifically,
         * the cities one spot in from the two sides.
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        /* We should not be able to cover everything with one city. */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Works for six cities in a line, regardless of order, and produces output.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over the cities when making decisions is sensitive
     * to the order of those cities' names. This test looks at a map like
     * this one, trying out all possible orderings of the city names:
     *
     *        * -- * -- * -- * -- * -- *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * cities in a line. If your code is able to solve the problem correctly
     * for all of those orderings, there's a good chance that you're correctly
     * covering and uncovering cities at each step. On the other hand, if
     * your code runs into issues here, it may indicate that the way in which
     * you're covering and uncovering cities accidentally uncovers a city that
     * you have previously covered.
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* Linear arrangement. */
        Map<string, Set<string>> map;
        for (int i = 1; i + 1 < cities.size(); i++) {
            map[cities[i]] = { cities[i - 1], cities[i + 1] };
        }

        map = makeSymmetric(map);

        /* We should be able to cover everything with two cities, specifically,
         * the cities one spot in from the two sides.
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        EXPECT_EQUAL(chosen.size(), 2);
        EXPECT(chosen.contains(cities[1]));
        EXPECT(chosen.contains(cities[4]));

        /* We should not be able to cover everything with one city. */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

/* The "Don't Be Greedy" sample world. */
const Map<string, Set<string>> kDontBeGreedy = makeSymmetric({
    { "A", { "B" } },
    { "B", { "C", "D" } },
    { "C", { "D" } },
    { "D", { "F", "G" } },
    { "E", { "F" } },
    { "F", { "G" } },
});

PROVIDED_TEST("Solves \"Don't be Greedy\" from the handout.") {
    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 1, locations1));
    EXPECT( canBeMadeDisasterReady(kDontBeGreedy, 2, locations2));
}

PROVIDED_TEST("Solves \"Don't be Greedy\" from the handout, and produces output.") {
    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 1, locations1));
    EXPECT( canBeMadeDisasterReady(kDontBeGreedy, 2, locations2));

    Set<string> expected = {"B", "F"};
    EXPECT_EQUAL(locations2, expected);
}

PROVIDED_TEST("Solves \"Don't be Greedy,\" regardless of ordering, and produces output.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over the cities when making decisions is sensitive
     * to the order of those cities' names. This test looks at a map like
     * this one, trying out all possible orderings of the city names:
     *
     *     0       4
     *     |       |
     *     1 - 2 - 3
     *      \ / \ /
     *       5   6
     *
     * There are 7! = 5,040 possible permutations of the ordering of these seven
     * cities. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly
     * covering and uncovering cities at each step. On the other hand, if
     * your code runs into issues here, it may indicate that the way in which
     * you're covering and uncovering cities accidentally uncovers a city that
     * you have previously covered.
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F", "G" };
    do {
        Map<string, Set<string>> map = makeSymmetric({
            { cities[1], { cities[0], cities[2], cities[5] } },
            { cities[2], { cities[3], cities[5], cities[6] } },
            { cities[3], { cities[4], cities[6] } },
        });

        /* We should be able to cover everything with two cities. */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        /* Those cities should be 1 and 3. */
        EXPECT_EQUAL(chosen, { cities[1], cities[3] });

        /* We should not be able to cover everything with one city. */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Stress test: 6 x 6 grid. (This should take at most a few seconds.)") {
    Map<string, Set<string>> grid;

    /* Build the grid. */
    char maxRow = 'F';
    int  maxCol = 6;
    for (char row = 'A'; row <= maxRow; row++) {
        for (int col = 1; col <= maxCol; col++) {
            if (row != maxRow) {
                grid[row + to_string(col)] += (char(row + 1) + to_string(col));
            }
            if (col != maxCol) {
                grid[row + to_string(col)] += (char(row) + to_string(col + 1));
            }
        }
    }
    grid = makeSymmetric(grid);

    Set<string> locations;
    EXPECT(canBeMadeDisasterReady(grid, 10, locations));
}

PROVIDED_TEST("Stress test: 6 x 6 grid, with output. (This should take at most a few seconds.)") {
    Map<string, Set<string>> grid;

    /* Build the grid. */
    char maxRow = 'F';
    int  maxCol = 6;
    for (char row = 'A'; row <= maxRow; row++) {
        for (int col = 1; col <= maxCol; col++) {
            if (row != maxRow) {
                grid[row + to_string(col)] += (char(row + 1) + to_string(col));
            }
            if (col != maxCol) {
                grid[row + to_string(col)] += (char(row) + to_string(col + 1));
            }
        }
    }
    grid = makeSymmetric(grid);   

    Set<string> locations;
    EXPECT(canBeMadeDisasterReady(grid, 10, locations));

    for (char row = 'A'; row <= maxRow; row++) {
        for (int col = 1; col <= maxCol; col++) {
            EXPECT(isCovered(row + to_string(col), grid, locations));
        }
    }
}


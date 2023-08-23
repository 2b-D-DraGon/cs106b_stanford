/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
#include "strlib.h"
using namespace std;


string onlyConnectize(string phrase) {
    /* TODO: The next few lines just exist to make sure you don't get compiler warning messages
     * when this function isn't implemented. Delete these lines, then implement this function.
     */

    string test="";

    if(phrase.size()==0)//返回条件如果字符串为零则返回
    {
        return "";
    }
    char letter = phrase[0];//取第一个字符
    int n = phrase.size();
    phrase=phrase.substr(1,n-1);


    if(!isalpha(letter))//先判断是否为字母
    {
       //进行下一次递归
        test+=""+onlyConnectize(phrase);
        cout<<test<<endl;
        return test;
    }
    else
    {
        letter=toUpperCase(letter);
        if(letter=='A'||letter=='E'||letter=='I'||letter=='O'||letter=='U')//判断是否为元音如果是的话就弹出
        {
            test+=""+onlyConnectize(phrase);
            cout<<test<<endl;
            return test;
        }
        else
        {
            test=charToString(letter)+onlyConnectize(phrase);
            cout<<test<<endl;
            return test;
            //return charToString(letter)+=onlyConnectize(phrase);
        }
    }
}




/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */







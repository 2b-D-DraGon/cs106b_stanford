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
using namespace std;

/*
 * Function: matches
 * ------------------
 * Your task is to write a function that takes as input a
 * string and a pattern, then returns whether that string
 * matches the pattern.
 */

bool matchesStar(string& text, string& pattern){
    if(text.size()==0){
        return true;
    }
    else if(text[0]==pattern[0]){//如果字符一样则继续递归
        text=text.substr(1,text.size()-1);
        pattern=pattern.substr(1,pattern.size()-1);
        return matchesStar(text,pattern);
    }
    else if('*'==pattern[0]){//*的情况
        if(pattern.size()==1){
            return true;
        }
        else if(pattern[1]==text[0]){//如果到了就将 *和字符 删掉
            text=text.substr(1,text.size()-1);
            pattern=pattern.substr(2,pattern.size()-2);
            return matchesStar(text,pattern);
        }
        else{//如果没到 就删去第一个 因为一定匹配
            text=text.substr(1,text.size()-1);
            return matchesStar(text,pattern);
        }
    }

    return false;
}

bool matchesDot(string& text, string& pattern){
    if(text.size()!=pattern.size()){//长度不相等 直接淘汰
        return false;
    }
    else if(text.size()==0){//剩余值为0，达到结尾
        return true;
    }
    else{

        if(pattern[0]=='.'){//  .直接给淘汰，一定匹配
            text=text.substr(1,text.size()-1);
            pattern=pattern.substr(1,pattern.size()-1);
            return matchesDot(text,pattern);
        }
        else if(pattern[0]==text[0]){// 不是.则需要字符一样
            text=text.substr(1,text.size()-1);
            pattern=pattern.substr(1,pattern.size()-1);
            return matchesDot(text,pattern);
        }
//        else{//都不符合就不是
//            return false;
//        }

    }
    return false;

}

bool matchesQuestion(string& text, string& pattern){
    if(text.size()==0){
        return true;
    }
    else if(text.size()==pattern.size()){//长度相等的情况
        if(pattern[0]=='?'){//  ？直接给跳过，一定匹配，然后截取长度
            text=text.substr(1,text.size()-1);
            pattern=pattern.substr(1,pattern.size()-1);
            return matchesQuestion(text,pattern);
        }
        else if(pattern[0]==text[0]){// 不是.则需要字符一样，然后截取长度进行下一次的判断
            text=text.substr(1,text.size()-1);
            pattern=pattern.substr(1,pattern.size()-1);
            return matchesQuestion(text,pattern);
        }
        return false;//都不符合 则错误

    }
    else if(text.size()==pattern.size()-1){//长度等于-1的情况
        if(pattern[0]=='?'){//  ？直接给淘汰，一定匹配
            pattern=pattern.substr(1,pattern.size()-1);
            return matchesQuestion(text,pattern);
        }
        else if(pattern[0]==text[0]){// 不是.则需要字符一样
            text=text.substr(1,text.size()-1);
            pattern=pattern.substr(1,pattern.size()-1);
            return matchesQuestion(text,pattern);
        }
        return false;
    }

    return false;

}

bool matches(const string& text, const string& pattern) {

    //...最好比较，非...的字符是否一样且长度是否一样

    int size=pattern.size();

    string textCopy=text;
    string patternCopy=pattern;

    //查看符合哪种匹配
    for(int i=0;i<size;i++){
        if(pattern[i]=='.'){
            return matchesDot(textCopy, patternCopy);
        }
        if(pattern[i]=='?'){
            return matchesQuestion(textCopy, patternCopy);
        }
        if(pattern[i]=='*'){
            return matchesStar(textCopy, patternCopy);
        }
    }

    return false;
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Testing *") {
    EXPECT_EQUAL(matches("apple", "a*"), true);
    EXPECT_EQUAL(matches("apply", "a*"), true);
    EXPECT_EQUAL(matches("apoplexy", "a*"), true);
    EXPECT_EQUAL(matches("Amicus", "a*"), false);
    EXPECT_EQUAL(matches("banana", "a*"), false);
    EXPECT_EQUAL(matches("ramadan", "*a*"), true);
    EXPECT_EQUAL(matches("amadan", "*a*"), true);

}

PROVIDED_TEST("Provided Test: Testing .") {
    EXPECT_EQUAL(matches("three", "th..."), true);
    EXPECT_EQUAL(matches("threshold", "th..."), false);
}

PROVIDED_TEST("Provided Test: Testing ?") {
    EXPECT_EQUAL(matches("color", "colo?r"), true);
    EXPECT_EQUAL(matches("colour", "colo?r"), true);
    EXPECT_EQUAL(matches("colouxr", "colo?r"), false);
}

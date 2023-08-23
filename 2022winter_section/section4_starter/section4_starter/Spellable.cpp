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
#include <string>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "set.h"
#include "strlib.h"
using namespace std;

/*
 * Function: isElementSpellable
 * -----------------------------
 * Write a function that accepts as input a string and a Set<string>
 * containing all element symbols (stored with the proper
 * capitalization), then returns whether that string can be
 * written using only element symbols.
 */

bool ifElementSame(const string &text,const string &symbol){
    return startsWith(toLowerCase(text),toLowerCase(symbol));
}


bool isElementSpellable(const string& text, const Set<string>& symbols) {
  /* todo: remove these lines and implement this function! */
    if(text==""){
        return true;
    }
    else{
        for(string symbol:symbols){
            if(ifElementSame(text,symbol)
               &&isElementSpellable(text.substr(symbol.length()),symbols)){
                return true;
            }
        }
        return false;
   }
}


//string isElementSpellable(const string& text, const Set<string>& symbols) {//最终升级版本 v3.0,裁剪

//    //base: if text is empty return ""
//    if(text.size()==0){
//        return "";
//    }

//    string bestString="";

//    for(string word:symbols){//symbols是不变的，因为并不是只有一次的遍历

//        word=toLowerCase(word);//都变成小写 有利于比较
//        int index=toLowerCase(text).find(word[0]);//开始一个一个的找

//        for(int i =1;i<word.size()&&index!=string::npos;i++){
//            index=text.find(word[i],index+1);//如果单词中有这个成分就假设他可以裁剪
//        }

//        if(index!=string::npos){//如果所有字符都有，那么就从找到的最后字符的下一个开始进行下一次的查找
//            string with=word+isElementSpellable(text.substr(index+1),symbols);
//            if(bestString.size()<with.size()) bestString=with;//因为找到了所有的可能 所以要比较 谁长取谁
//        }

//    }

//    return bestString;
//}



/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Verify that the solution works on examples from the handout.") {
  Set<string> symbols = {
    "H", "He", "Li", "Be", "B",
    "C", "N", "O", "F", "Ne", "Na",
    "Mg", "Al", "Si", "P", "S", "Cl",
    "Ar", "K", "Ca", "Sc", "Ti", "V",
    "Cr", "Mn", "Fe", "Co", "Ni",
    "Cu", "Zn", "Ga", "Ge", "As",
    "Se", "Br", "Kr", "Rb", "Sr",
    "Y", "Zr", "Nb", "Mo", "Tc",
    "Ru", "Rh", "Pd", "Ag", "Cd",
    "In", "Sn", "Sb", "Te", "I",
    "Xe", "Cs", "Ba", "La", "Ce",
    "Pr", "Nd", "Pm", "Sm", "Eu",
    "Gd", "Tb", "Dy", "Ho", "Er",
    "Tm", "Yb", "Lu", "Hf", "Ta",
    "W", "Re", "Os", "Ir", "Pt",
    "Au", "Hg", "Tl", "Pb",
    "Bi", "Po", "At", "Rn", "Fr",
    "Ra", "Ac", "Th", "Pa", "U",
    "Np", "Pu", "Am", "Cm", "Bk",
    "Cf", "Es", "Fm", "Md", "No",
    "Lr", "Rf", "Db", "Sg", "Bh",
    "Hs", "Mt", "Ds", "Rg", "Cn",
    "Nh", "Fl", "Mc", "Lv", "Ts",
    "Og"
  };
  EXPECT_EQUAL(isElementSpellable("feline", symbols), true);
  EXPECT_EQUAL(isElementSpellable("interesting", symbols), false);
  EXPECT_EQUAL(isElementSpellable("CHeMoWIZrDy", symbols), true);
}

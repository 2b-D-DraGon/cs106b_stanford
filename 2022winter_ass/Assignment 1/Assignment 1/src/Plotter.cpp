#include "Plotter.h"
#include "strlib.h"
using namespace std;

//stringToReal
void runPlotterScript(istream& input) {//进行拆分 将所有单词拆分
    PenStyle pen={1,"red"};
    Vector<string> v1;

    double x1,y1;//实际所在的位置
    int index =0;//落笔时为1

    for (string line; getline(input, line); ) {
        line=toLowerCase(line);//转化成小写
        if(startsWith(line,"moveabs")){
            v1+= stringSplit(line,' ');
            int n = v1.size();

            if(index==1)//如果笔落下了的状态就是直接绘画并更新
            {
                drawLine(x1,y1,stringToReal(v1[n-2]),stringToReal(v1[n-1]),pen);
                x1=stringToReal(v1[n-2]);
                y1=stringToReal(v1[n-1]);
            }
            else{//如果笔没有落下则直接更新位置即可
                x1=stringToReal(v1[n-2]);
                y1=stringToReal(v1[n-1]);
            }
        }
        else if(startsWith(line,"moverel")){
            v1+= stringSplit(line,' ');
            int n = v1.size();
            if(index==1)
            {
                drawLine(x1,y1,x1+stringToReal(v1[n-2]),y1+stringToReal(v1[n-1]),pen);//相对位置
                x1+=stringToReal(v1[n-2]);//记录相对位置
                y1+=stringToReal(v1[n-1]);
            }
            else{//没落笔，只更新实际位置
                x1+=stringToReal(v1[n-2]);//记录相对位置
                y1+=stringToReal(v1[n-1]);
            }
        }
        else if(startsWith(line,"penup")){
            index = 0;

        }
        else if(startsWith(line,"pendown")){
            index = 1;

        }
    }



}

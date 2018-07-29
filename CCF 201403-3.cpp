/*
 试题编号：    201403-3
 试题名称：    命令行选项
 时间限制：    1.0s
 内存限制：    256.0MB
 问题描述：
 问题描述
 　　请你写一个命令行分析程序,用以分析给定的命令行里包含哪些选项。每个命令行由若干个字符串组成,它们之间恰好由一个空格分隔。这些字符串中的第一个为该命令行工具的名字,由小写字母组成,你的程序不用对它进行处理。在工具名字之后可能会包含若干选项,然后可能会包含一 些不是选项的参数。
 　　选项有两类:带参数的选项和不带参数的选项。一个合法的无参数选项的形式是一个减号后面跟单个小写字母,如"-a" 或"-b"。而带参数选项则由两个由空格分隔的字符串构成,前者的格式要求与无参数选项相同,后者则是该选项的参数,是由小写字母,数字和减号组成的非空字符串。
 　　该命令行工具的作者提供给你一个格式字符串以指定他的命令行工具需要接受哪些选项。这个字符串由若干小写字母和冒号组成,其中的每个小写字母表示一个该程序接受的选项。如果该小写字母后面紧跟了一个冒号,它就表示一个带参数的选项,否则则为不带参数的选项。例如, "ab:m:" 表示该程序接受三种选项,即"-a"(不带参数),"-b"(带参数), 以及"-m"(带参数)。
 　　命令行工具的作者准备了若干条命令行用以测试你的程序。对于每个命令行,你的工具应当一直向后分析。当你的工具遇到某个字符串既不是合法的选项,又不是某个合法选项的参数时,分析就停止。命令行剩余的未分析部分不构成该命令的选项,因此你的程序应当忽略它们。
 输入格式
 　　输入的第一行是一个格式字符串,它至少包含一个字符,且长度不超过 52。格式字符串只包含小写字母和冒号,保证每个小写字母至多出现一次,不会有两个相邻的冒号,也不会以冒号开头。
 　　输入的第二行是一个正整数 N(1 ≤ N ≤ 20),表示你需要处理的命令行的个数。
 　　接下来有 N 行,每行是一个待处理的命令行,它包括不超过 256 个字符。该命令行一定是若干个由单个空格分隔的字符串构成,每个字符串里只包含小写字母,数字和减号。
 输出格式
 　　输出有 N 行。其中第 i 行以"Case i:" 开始,然后应当有恰好一个空格,然后应当按照字母升序输出该命令行中用到的所有选项的名称,对于带参数的选项,在输出它的名称之后还要输出它的参数。如果一个选项在命令行中出现了多次,只输出一次。如果一个带参数的选项在命令行中出 现了多次,只输出最后一次出现时所带的参数。
 样例输入
 albw:x
 4
 ls -a -l -a documents -b
 ls
 ls -w 10 -x -w 15
 ls -a -b -c -d -e -l
 样例输出
 Case 1: -a -l
 Case 2:
 Case 3: -w 15 -x
 Case 4: -a -b
 */

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

map<string, bool> rec(string rule) {
    map<string, bool> r;
    for (int i = 0; i < rule.size(); i++) {
        if (rule[i + 1] == ':' && i != rule.size() - 1) {
            string temp = "-";
            temp = temp + rule[i];
            //加入map
            r[temp] = true;
            //跳过 :
            i++;
        }
        else {
            string temp = "-";
            temp = temp + rule[i];
            r[temp] = false;
        }
    }
    return r;
}

vector<string> factory(string s) {
    vector<string> vt;
    string st;
    int i = 0;
    for (int j = i; j < s.size(); j++) {
        if (s[j] == ' ') {
            st = s.substr(i, j - i);
            vt.push_back(st);
            i = j + 1;
        }
    }
    st = s.substr(i, s.size() - i);
    vt.push_back(st);
    return vt;
}

bool isLegal(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') {
            if (s[i] < 'a' || s[i] > 'z') {
                if (s[i] != '-') {
                    return false;
                }
            }
        }
    }
    return true;
}

map<string, string> run(vector<string> sv, map<string, bool> rule) {
    map<string, string> temp;
    map<string, bool>::iterator mit;
    for (int i = 1; i < sv.size(); i++) {
        string st = sv[i];
        //判定是否符合规则
        mit = rule.find(sv[i]);
        if (mit == rule.end()) {
            //不符合规则
            break;
        }
        bool hasPara = mit->second;
        //有参数
        if (hasPara) {
            if (i != sv.size() - 1 && isLegal(sv[i + 1])) {
                temp[sv[i]] = sv[i + 1];
                i++;
            }
            else
                break;
        }
        //无参数
        else {
            temp.insert(make_pair(sv[i], ""));
        }
    }
    return temp;
}

int main() {
    string rule;
    cin >> rule;
    //识别rule。并返回一个map，key = “rule”， value = bool(带参)/false(不带参)
    map<string, bool> r = rec(rule);
    //接收命令个数
    int n;
    cin >> n;
    getchar();
    map<string, string> sm[n];
    //接收命令
    for (int i = 0; i < n; i++) {
        char arr[256];
        gets(arr);
        string s = string(arr);
        //处理字符串，将结果存入一个vector里面
        vector<string> vt = factory(s);
        sm[i] = run(vt, r);
    }
    //输出vector
    map<string, string>::iterator it;
    for (int i = 0; i < n; i++) {
        printf("Case %d: ", i + 1);
        for (it = sm[i].begin(); it != sm[i].end(); it++) {
            if (it->second == "") {
                cout << it->first << " ";
            }
            else {
                cout << it->first << " " << it->second << " ";
            }
        }
        cout << endl;
    }
    return 0;
}








#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <iomanip>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "../headers/sanpham.h"
#include "../headers/nhanvien.h"
#include <ctime>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif


extern string currentNvPath;
extern string currentPdPath;
extern string currentBillPath;
extern string currentTPath;
extern string currentDtPath;
using namespace std;
//ctrl s ctrl ssssss ròiok day nua
extern const string null;

//importan
bool checkExisted(string newID);
bool checkTableExist(string newID);
vector<string> TrimFields(string beChangeID, const string& line);
string LinkedFields(vector<string>& fields) ;
bool checkProduct(string pID);
void printBillLine(const string& name, int quantity, float price) ;


//supliment
string currentDateTime();
string getDateTime();
string formatMoney(long long n);
void centerText(const string& text, int width = 40, char fill = ' ');
inline bool folderExists(const string& path) {
    DIR* dir = opendir(path.c_str());
    if (dir) {
        closedir(dir);
        return true;
    }
    return false;
}

inline void ensureDir(const string& path) {
    #ifdef _WIN32
        _mkdir(path.c_str());
    #else
        
        mkdir(path.c_str(), 0777);
    #endif
}




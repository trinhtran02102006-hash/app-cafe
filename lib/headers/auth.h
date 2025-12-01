#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "../untils/untils.h"

using namespace std;


struct UserDataPaths {
    string nhanvienPath;
    string sanphamPath;
    string tablesPath;
    string hoadonPath;
    string dongtienPath;
};

class User {
private:
    string uid;
    string username;
    string email;
    string password;
    UserDataPaths dataPaths;

public:
    
    User() {}
    User(string uid_, string username_, string email_, string pwd_, UserDataPaths paths_)
        : uid(uid_), username(username_), email(email_), password(pwd_), dataPaths(paths_) {}

    
    static User* Login(const string& identifier, const string& password);
    static bool Register(const string& username, const string& email, const string& password);
    static string generateNextUID();
    static bool checkEmailExists(const string& email);
    static bool checkUsernameExists(const string& username);

   
    void createUserFiles();
    void setGlobalPaths();
    
 
    string getUID() const { return uid; }
    string getUsername() const { return username; }
    string getEmail() const { return email; }
    UserDataPaths getDataPaths() const { return dataPaths; }
};

// Global session - current logged in user
extern User* currentUser;

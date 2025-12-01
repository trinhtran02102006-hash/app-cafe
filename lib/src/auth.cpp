#include "../headers/auth.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define USERS_PATH "data/users/users.txt"

// Global current user
User* currentUser = nullptr;

// Hàm tạo UID tiếp theo
string User::generateNextUID() {
    ifstream in(USERS_PATH);
    int maxUID = 0;
    
    if (in.is_open()) {
        string line;
        while (getline(in, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string uid;
            getline(ss, uid, '|');
            
            // Chuyển uid từ string sang int để tìm max
            try {
                int currentUID = stoi(uid);
                if (currentUID > maxUID) {
                    maxUID = currentUID;
                }
            } catch (...) {
                continue;
            }
        }
        in.close();
    }
    
    // Tạo UID mới = maxUID + 1, format 2 chữ số
    int newUID = maxUID + 1;
    stringstream ss;
    ss << setw(2) << setfill('0') << newUID;
    return ss.str();
}

// Kiểm tra email đã tồn tại chưa
bool User::checkEmailExists(const string& email) {
    ifstream in(USERS_PATH);
    if (!in.is_open()) {
        return false;
    }
    
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string uid, username, userEmail;
        getline(ss, uid, '|');
        getline(ss, username, '|');
        getline(ss, userEmail, '|');
        
        if (userEmail == email) {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

// Kiểm tra username đã tồn tại chưa
bool User::checkUsernameExists(const string& username) {
    ifstream in(USERS_PATH);
    if (!in.is_open()) {
        return false;
    }
    
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string uid, uname;
        getline(ss, uid, '|');
        getline(ss, uname, '|');
        
        if (uname == username) {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

// Tạo các file dữ liệu cho user mới
void User::createUserFiles() {
    // Đảm bảo các folder tồn tại
    ensureDir("data/users");
    ensureDir("data/nhanvien");
    ensureDir("data/sanpham");
    ensureDir("data/tables");
    ensureDir("data/dongtien");
    ensureDir("data/hoadon");
    
    // Tạo subfolder cho hoadon của user này
    ensureDir(dataPaths.hoadonPath);
    
    // Tạo các file trống
    ofstream nvFile(dataPaths.nhanvienPath);
    nvFile.close();
    
    ofstream spFile(dataPaths.sanphamPath);
    spFile.close();
    
    ofstream tbFile(dataPaths.tablesPath);
    tbFile.close();
    
    ofstream dtFile(dataPaths.dongtienPath);
    dtFile.close();
}

// Set global paths để các module khác sử dụng
void User::setGlobalPaths() {
    currentNvPath = dataPaths.nhanvienPath;
    currentPdPath = dataPaths.sanphamPath;
    currentTPath = dataPaths.tablesPath;
    currentBillPath = dataPaths.hoadonPath;
    currentDtPath = dataPaths.dongtienPath;
}

// Đăng ký user mới
bool User::Register(const string& username, const string& email, const string& password) {
    // Kiểm tra username đã tồn tại
    if (checkUsernameExists(username)) {
        cout << "\n>>> Username da ton tai! <<<\n";
        return false;
    }
    
    // Kiểm tra email đã tồn tại
    if (checkEmailExists(email)) {
        cout << "\n>>> Email da ton tai! <<<\n";
        return false;
    }
    
    // Tạo UID mới
    string newUID = generateNextUID();
    
    // Tạo data paths
    UserDataPaths paths;
    paths.nhanvienPath = "data/nhanvien/" + newUID + "_nhanvien.txt";
    paths.sanphamPath = "data/sanpham/" + newUID + "_sanpham.txt";
    paths.tablesPath = "data/tables/" + newUID + "_tables.txt";
    paths.hoadonPath = "data/hoadon/" + newUID + "_hoadon";
    paths.dongtienPath = "data/dongtien/" + newUID + "_dongtien.txt";
    
    // Tạo user object
    User newUser(newUID, username, email, password, paths);
    
    // Tạo các file cho user
    newUser.createUserFiles();
    
    // Lưu thông tin user vào users.txt
    ensureDir("data/users");
    ofstream out(USERS_PATH, ios::app);
    if (!out.is_open()) {
        cout << "Loi: Khong the mo file users.txt!" << endl;
        return false;
    }
    
    out << newUID << "|"
        << username << "|"
        << email << "|"
        << password << "|"
        << paths.nhanvienPath << "|"
        << paths.sanphamPath << "|"
        << paths.tablesPath << "|"
        << paths.hoadonPath << "|"
        << paths.dongtienPath << endl;
    
    out.close();
    return true;
}

// Đăng nhập - có thể dùng username hoặc email
User* User::Login(const string& identifier, const string& password) {
    ifstream in(USERS_PATH);
    if (!in.is_open()) {
        return nullptr;
    }
    
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string uid, username, userEmail, userPassword;
        string nvPath, spPath, tbPath, hdPath, dtPath;
        
        getline(ss, uid, '|');
        getline(ss, username, '|');
        getline(ss, userEmail, '|');
        getline(ss, userPassword, '|');
        getline(ss, nvPath, '|');
        getline(ss, spPath, '|');
        getline(ss, tbPath, '|');
        getline(ss, hdPath, '|');
        getline(ss, dtPath, '|');
        
        // Kiểm tra identifier (username hoặc email) và password
        if ((username == identifier || userEmail == identifier) && userPassword == password) {
            UserDataPaths paths;
            paths.nhanvienPath = nvPath;
            paths.sanphamPath = spPath;
            paths.tablesPath = tbPath;
            paths.hoadonPath = hdPath;
            paths.dongtienPath = dtPath;
            
            in.close();
            return new User(uid, username, userEmail, userPassword, paths);
        }
    }
    
    in.close();
    return nullptr;
}

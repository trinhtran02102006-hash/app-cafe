#include <iostream>
#include <limits>
#include <iomanip>
#include "lib/headers/menu.h"
#include "lib/headers/auth.h"
#include "lib/headers/ui_helper.h"

using namespace std;

void printAuthHeader() {
    cout << "\n";
    cout << "╔═══════════════════════════════════════════════════════╗\n";
    cout << "║                                                       ║\n";
    cout << "║           🍰 CAFE MANAGEMENT SYSTEM 🍰                 ║\n";
    cout << "║                                                       ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n";
}

void printAuthMenu() {
    cout << "\n┌─────────────────────────────────┐\n";
    cout << "│         AUTHENTICATION            │\n";
    cout << "├───────────────────────────────────┤\n";
    cout << "│  [1] 🔐 Dang nhap                 │\n";
    cout << "│  [2] ✍️  Dang ki                  │\n";
    cout << "│  [0] 🚪 Thoat                     │\n";
    cout << "└───────────────────────────────────┘\n";
}

int main() {
    int choice;
    
    printAuthHeader();
    
    // Auth Menu Loop
    do {
        printAuthMenu();
        
        cout << "\n➤ Lua chon cua ban: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1: {
                // Login
                printBox("DANG NHAP");
                
                string identifier, password;
                cout << "\n📧 Username hoac Email: ";
                getline(cin, identifier);
                cout << "🔑 Password: ";
                getline(cin, password);
                
                User* user = User::Login(identifier, password);
                if(user != nullptr) {
                    cout << "\n╔═════════════════════════════════════════════╗\n";
                    cout << "║          DANG NHAP THANH CONG! 🎉             ║\n";
                    cout << "╠═══════════════════════════════════════════════╣\n";
                    cout << "║  👤 User: " << left << setw(35) << user->getUsername() << "║\n";
                    cout << "║  📧 Email: " << left << setw(34) << user->getEmail() << "║\n";
                    cout << "╚═══════════════════════════════════════════════╝\n";
                    
                    currentUser = user;
                    
                    // Set global paths for current user
                    user->setGlobalPaths();
                    
                    cout << "\n⏳ Loading system...\n";
                    
                    // Vào main menu
                    showMenu();
                    
                    // Logout sau khi thoát menu
                    printInfo("Da dang xuat khoi he thong");
                    delete currentUser;
                    currentUser = nullptr;
                } else {
                    printError("Sai username/email hoac password!");
                }
                break;
            }
            case 2: {
                // Register
                printBox("DANG KI TAI KHOAN MOI");
                
                string username, email, password;
                
                cout << "\n👤 Username: ";
                getline(cin, username);
                while(username.empty() || username.find('|') != string::npos) {
                    cout << "Username khong duoc de trong hoac chua ky tu '|'! Nhap lai: ";
                    getline(cin, username);
                }

                cout << "📧 Email: ";
                getline(cin, email);
                while(email.empty() || email.find('|') != string::npos) {
                    cout << "Email khong duoc de trong hoac chua ky tu '|'! Nhap lai: ";
                    getline(cin, email);
                }

                cout << "🔑 Password: ";
                getline(cin, password);
                while(password.empty() || password.find('|') != string::npos) {
                    cout << "Password khong duoc de trong hoac chua ky tu '|'! Nhap lai: ";
                    getline(cin, password);
                }
                
                if(User::Register(username, email, password)) {
                    cout << "\n╔═════════════════════════════════════════════╗\n";
                    cout << "║          DANG KI THANH CONG! ✨               ║\n";
                    cout << "╠═══════════════════════════════════════════════╣\n";
                    cout << "║  Tai khoan cua ban da duoc tao!               ║\n";
                    cout << "║  Hay dang nhap de su dung he thong.           ║\n";
                    cout << "╚═══════════════════════════════════════════════╝\n";
                }
                break;
            }
            case 0:
                cout << "\n╔═════════════════════════════════════════════╗\n";
                cout << "║             Cam on ban da su dung!            ║\n";
                cout << "║                  Tam biet! 👋                 ║\n";
                cout << "╚═══════════════════════════════════════════════╝\n\n";
                break;
            default:
                printError("Lua chon khong hop le! Vui long chon 0-2.");
        }
    } while(choice != 0);
    
    return 0;
}
#include "../headers/menu.h"
#include "../headers/ui_helper.h"

static Table currentTable;
static bool currentTableLoaded = false;


vector<Product> plist() {
    vector<Product> pTemp;
    ifstream in(currentPdPath);
    string line;
    int i = 1;
    while(getline(in, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, name, tCost, tPrice;
        long cost, price;
        
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, tCost, '|');
        getline(ss, tPrice, '|');

        if(!tCost.empty()) cost = stof(tCost);
        if(!tPrice.empty()) price = stof(tPrice);

        pTemp.push_back({id, name, cost, price});
    }
    return pTemp;
};

vector<Table> tablist() {
    vector<Table> pTemp;
    ifstream in(currentTPath);
    string line;
    int i = 1;
    while(getline(in, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, cusName, state;
        
        getline(ss, id, '|');
        getline(ss, cusName, '|');
        getline(ss, state, '|');
    
        pTemp.push_back({id, cusName, static_cast<bool>(stoi(state))});
    }
    return pTemp;
};

vector<Staff> slist() {
    vector<Staff> sTemp;
    ifstream in(currentNvPath);
    string line;
    int i = 1;
    while(getline(in, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, name, age, phoneNum, temp;
        float salary = 0;
        
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, age, '|');
        getline(ss, phoneNum, '|');
        getline(ss, temp, '|');

        if(!temp.empty()) salary = stof(temp);

        sTemp.push_back({id, name, age, phoneNum, salary});
    }
    return sTemp;
};

void showMenu() {
    int choose;
    vector<pair<string,string>> orders;
    Product p;
    do {
        printHeader("🍰 MENU CHINH 🍰");
        
        printMenuHeader("CHUC NANG");
        printMenuOption(1, "📋", "Show Menu & Order");
        printMenuOption(2, "💰", "Tinh tien");
        printMenuOption(3, "🪑", "Quan li ban");
        printMenuOption(4, "🍽️", "Quan li san pham");
        printMenuOption(5, "👤", "Quan li nhan vien");
        printMenuOption(6, "📊", "Quan li doanh thu");
        printMenuOption(0, "🚪", "Thoat");
        printMenuFooter();

        printPrompt("Lua chon cua ban"); cin >> choose;
    switch(choose) {
       case 1: {
    string choose;
    int qty;
    string tableID;

    cout << "Nhap so ban cua khach: ";
    cin >> tableID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!checkTableExist(tableID)) {
        cout << "\nBan nay khong ton tai!\n";
        break;
    }

    // load ban tu file
    Table temp;
    Table thisTable = temp.findByID(tablist(), tableID);

    // neu ban da co nguoi dat truoc → hoi xac nhan
    if (thisTable.getState()) {
        char cusCheck;
        cout << "\nBan nay da co nguoi dat truoc.\n"
             << "Co phai day la khach hang \"" 
             << thisTable.getCustomer() 
             << "\" khong? (y/n): ";
        cin >> cusCheck;

        if (tolower(cusCheck) != 'y') {
            cout << "\nKhong phai khach!!\n";
            break;
        }
    }

    // ok → load currentTable
    currentTable = thisTable;
    currentTableLoaded = true;

    // bat dau order
    do {
        cout << string(40, '-') << endl
             << "Show Menu & Order" << endl
             << string(40, '-') << endl;

        cout << "\n*Bam phim 0 de hoan tat order*\n" << endl;

        p.ShowMenuToCustomer();

        cout << "\nMon khach chon (id): ";
        cin >> choose;

        if (choose != "0") {
            cout << "Nhap so luong: ";
            cin >> qty;

            if (checkProduct(choose)) {
                currentTable.addOrder(choose, qty);
            } else {
                cout << "Khong co mon do!\n";
            }
        }

    } while (choose != "0");

    break;
} //ctrl s thu cai

        case 2: {
            centerText("TINH TIEN");
            string tableID;
            cout << "\nNhap so ban: "; cin >> tableID; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(!checkTableExist(tableID)) {
                cout << endl << "Ban nay khong ton tai!" << endl;
            }
            else {
                if (!currentTableLoaded || currentTable.getID() != tableID) {
                    cout << "\nBan nay chua order!" << endl;
                    break;
                }
                char billPrint; bool print = false;
                int voucher = 0;
                cout << "\nVoucher: "; cin >> voucher; cout << endl;
                cout << "\nBan co muon in hoa don khong? (y/n): "; cin >> billPrint; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(tolower(billPrint) == 'y') {
                    print = true;
                }
                cout << string(16, ' ') << "HOA DON" << endl;
                currentTable.TinhTien(plist(), voucher, print);
                cout << string(40, '-') << endl << endl;
                currentTableLoaded = false;
            }
            break;
        }
        case 3: {
            // Quan li ban
            int action;
            Table table;
            do {
                printHeader("🪑 QUAN LI BAN 🪑");
                printMenuHeader("CHUC NANG");
                printMenuOption(1, "➕", "Them ban moi");
                printMenuOption(2, "🗑️", "Xoa ban");
                printMenuOption(3, "📋", "Danh sach ban");
                printMenuOption(4, "📝", "Khach dat ban");
                printMenuOption(5, "👀", "Xem ban da dat");
                printMenuOption(6, "❌", "Huy dat ban");
                printMenuOption(7, "🍽️", "Xem order cua ban");
                printMenuOption(0, "🔙", "Quay lai");
                printMenuFooter();
                
                printPrompt("Lua chon cua ban"); cin >> action;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if(action >= 1 && action <= 7) {
                    QuanLiBan(action, table);
                } else if(action != 0) {
                    printError("Lua chon khong hop le!");
                }
            } while(action != 0);
            break;
        }
        case 4: {
            // Quan li san pham
            int action;
            Product p;
            do {
                printHeader("🍽️ QUAN LI SAN PHAM 🍽️");
                printMenuHeader("CHUC NANG");
                printMenuOption(1, "➕", "Them san pham");
                printMenuOption(2, "✏️", "Sua thong tin san pham");
                printMenuOption(3, "🗑️", "Xoa san pham");
                printMenuOption(4, "📋", "Hien thi danh sach san pham");
                printMenuOption(0, "🔙", "Quay lai");
                printMenuFooter();
                
                printPrompt("Lua chon cua ban"); cin >> action;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if(action >= 1 && action <= 4) {
                    QuanLiSanPham(p, action);
                } else if(action != 0) {
                    printError("Lua chon khong hop le!");
                }
            } while(action != 0);
            break;
        }
        case 5: {
            // Quan li nhan vien
            int action;
            Staff s;
            do {
                printHeader("👤 QUAN LI NHAN VIEN 👤");
                printMenuHeader("CHUC NANG");
                printMenuOption(1, "➕", "Them nhan vien");
                printMenuOption(2, "✏️", "Sua thong tin nhan vien");
                printMenuOption(3, "🗑️", "Xoa nhan vien");
                printMenuOption(4, "💰", "Tinh luong nhan vien");
                printMenuOption(5, "📋", "Hien thi danh sach nhan vien");
                printMenuOption(0, "🔙", "Quay lai");
                printMenuFooter();
                
                printPrompt("Lua chon cua ban"); cin >> action;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if(action >= 1 && action <= 5) {
                    QuanLiNhanVien(s, action, slist());
                } else if(action != 0) {
                    printError("Lua chon khong hop le!");
                }
            } while(action != 0);
            break;
        }
        case 6: {
            // Quan li doanh thu
            int action;
            DongTien dt;
            do {
                printHeader("📊 QUAN LI DOANH THU 📊");
                printMenuHeader("CHUC NANG");
                printMenuOption(1, "📅", "Doanh thu hom nay");
                printMenuOption(2, "📆", "Doanh thu tuan nay");
                printMenuOption(3, "📊", "Doanh thu thang nay");
                printMenuOption(4, "💵", "Loi nhuan hom nay");
                printMenuOption(5, "💴", "Loi nhuan tuan nay");
                printMenuOption(6, "💶", "Loi nhuan thang nay");
                printMenuOption(7, "📈", "San luong");
                printMenuOption(0, "🔙", "Quay lai");
                printMenuFooter();
                
                printPrompt("Lua chon cua ban"); cin >> action;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                QuanLiDongTien(dt, action);
            } while(action != 0);
            break;
        }
        case 0: {
            // Exit
            break;
        }
        default: {
            printError("Lua chon khong hop le! Vui long chon 0-6.");
            break;
        }
    } // end switch
} while(choose != 0);
}
 



void QuanLiNhanVien(Staff& s, int action, vector<Staff> slist) {
    switch(action) {
        case 1: {
            //them nhan vien
            string id;
            cout << "Nhap so cccd: "; cin >> id;
            if(checkExisted(id)) {
                cout << "Nhan vien nay da co trong danh sach!";
            }
            else {
                string name, age, phoneNum; float basicSalary;

                cout << "Nhap ten: "; cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                getline(cin, name); 

                cout << "Nhap tuoi: ";  
                getline(cin, age);

                cout << "Nhap so dien thoai: "; 
                getline(cin, phoneNum); 

                cout << "Nhap luong co ban (theo gio): "; cin >> ws >> basicSalary;
 
                s.ThemNhanVien(id, name, age, phoneNum, basicSalary);
            } 
            break;
        } //end case 1
        case 2: {
            //sua thong tin
            string id;
            cout << "Nhap so cccd: "; cin >> id;
            if(!checkExisted(id)) {
                cout << "Nhan vien nay khong co trong danh sach!";
            }
            else {
                int inforChosen;
                do {
                cout << "1. Chinh sua ten nhan vien"                << endl
                     << "2. Chinh sua tuoi cua nhan vien"           << endl
                     << "3. Chinh sua so dien thoai cua nhan vien"  << endl
                     << "4. Chinh sua luong co ban cua nhan vien"   << endl
                     << "0. Thoat"                                  << endl
                     << "\n: "; cin >> inforChosen;
                if(inforChosen >= 1 && inforChosen <= 6) {
                switch(inforChosen) {
                    case 1: {
                        s.ChinhSuaThongTin(id, 1);
                        break;
                    }
                    case 2: {
                        s.ChinhSuaThongTin(id, 2);
                        break;
                    }
                    case 3: {
                        s.ChinhSuaThongTin(id, 3);
                        break;
                    }
                    case 4: {
                        s.ChinhSuaThongTin(id, 4);
                        break;
                    }
                    default: {
                        cout << "Vui long chon (1-4) !!!";
                        break;
                    }
                }
            }
            } while (inforChosen >= 1 && inforChosen <= 5);
            }
            break;
        } //end case 2
        case 3: {
            string id;
            cout << "Nhap so cccd: "; cin >> id;
            if(!checkExisted(id)) {
                cout << "Nhan vien nay khong co trong danh sach!";
            }
            else {
                s.XoaNhanVien(id);
            }
            break;
        } //end case 3
        case 4: {
            string id;
            cout << "Nhap so cccd: "; cin >> id;
            if(!checkExisted(id)) {
                cout << "Nhan vien nay khong co trong danh sach!";
            }
            auto nv = s.findByID(slist, id);
            int SoGioCong; float TienThuong = 0, TienPhat = 0, TienUng = 0;
            cout << "Nhap so gio cong: "; cin >> SoGioCong;
            cout << "Nhap so tien thuong: "; cin >> TienThuong;
            cout << "Nhap so tien phat: "; cin >> TienPhat;
            cout << "Nhap so tien ung truoc: "; cin >> TienUng;
            float salary = 0;
            salary = nv.TinhLuong(SoGioCong, TienThuong, TienPhat, TienUng);
            cout.imbue(locale(""));
            cout << endl << string(3, '-') << " Luong cua nhan vien " << nv.getName() << ": "
                 << fixed << setprecision(0) << formatMoney((long long)salary) << " VND " << string(3, '-');
            cout << endl;
            break;
        }//end case 4
        case 5: {
            s.ShowDanhSach();
        }//end case 5
    }

}

void QuanLiSanPham(Product& p, int action) {
    switch(action) {
        case 1: {
            //them san pham
            string id;
            cout << "Nhap id mon: "; cin >> id;
            if(checkProduct(id)) {
                cout << "Mon nay da co trong menu!";
            }
            else {
                string name; long cost, price; 

                cout << "Nhap ten mon: "; cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                getline(cin, name); 

                cout << "Nhap tien von: ";  
                cin >> cost;

                cout << "Nhap doanh thu: "; 
                cin >> price; 
 
                p.ThemSanPham(id, name, cost, price);
            } 
            break;
        }
        case 2: {
            //sua thong tin
            string id;
            cout << "Nhap id mon: "; cin >> id;
            if(!checkProduct(id)) {
                cout << "Mon nay khong co trong menu!";
            }
            else {
                int inforChosen;
                do {
                cout << "1. Chinh sua ten mon"                      << endl
                     << "2. Chinh sua tien von"                     << endl
                     << "3. Chinh sua gia mon"                    << endl
                     << "0. Thoat"                                  << endl
                     << "\n: "; cin >> inforChosen;
                switch(inforChosen) {
                    case 1: {
                        p.SuaSanPham(id, 1);
                        break;
                    }
                    case 2: {
                        p.SuaSanPham(id, 2);
                        break;
                    }
                    case 3: {
                        p.SuaSanPham(id, 3);
                        break;
                    }
                    default: {
                        cout << "Vui long chon (1-3) !!!";
                        break;
                    }
                }
            } while (inforChosen != 0);
            }
            break;
        }
        case 3: {
            string id;
            cout << "Nhap id mon: "; cin >> id;
            if(!checkExisted(id)) {
                cout << "Mon nay khong co trong menu!";
            }
            else {
                p.XoaSanPham(id);
            }
            break;
        }
        case 4: {
            p.ShowSanPham();
        }
    }
}

void QuanLiBan(int act, Table& table) {
    switch(act) {
        case 1: {
            //them ban moi
            string id;
            cout << endl << "Nhap id ban: ";cin >> id; 
            table.ThemBanMoi(id);
            break;
        }
        case 2: {
            string id;
            cout << "Nhap id ban muon xoa: "; cin >> id;
            if(checkTableExist(id)) {
                table.XoaBan(id);
            } else {
                cout << "\nBan nay khong ton tai!" << endl;
            }
            break;
        }
        case 3: {
            table.DanhSachBan();
            break;
        }
        case 4:{
            //khach dat ban
            string id, cusName;
            Table thisTable = table.findByID(tablist(), id);

            cout << "Nhap id ban: ";
            cin >> id;
            cout << "Nhap ten khach dat ban: "; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, cusName); //vi cai nay co dau cach nen dung getline cho do bi mat chu

            if(!checkTableExist(id)) {
                cout << "--- Ban nay khong ton tai!!! ---" << endl;
            }
            else {
                currentTable.DatBan(id, cusName, tablist());
            }
            break;
        }
        case 5: {
            //xem ban da duoc dat truoc
            auto list = tablist();
            if(list.empty()) {
                cout << string(30, '-') << endl
                        << "  Hien tai chua co ai dat ban" << endl
                        << string(30, '-') << endl;
                break;
            }
        
            cout << string(40, '-') << endl
                    << "BAN DA DUOC KHACH DAT TRUOC" << endl
                    << string(40, '-') << endl << endl;
        
            cout << left  << setw(10) << "ID"
                    << left  << setw(15) << "Ten Khach"
                    << endl << string(40, '-') << endl;
        
            for (auto& tab : list) {
                if (tab.getState()) {
                    cout << left  << setw(10) << tab.getID()
                            << left  << setw(15) << tab.getCustomer()
                            << endl << string(40, '-') << endl;
                }
            }
            break;
        }
        case 6: {
            //Huy dat ban
            string id;
            cout << "Nhap id ban can huy: "; cin >> id;
            Table thisTable = table.findByID(tablist(), id);
            //check ban ton tai va trang thai ban true
            if(checkTableExist(id) && thisTable.getState()) {
            thisTable.HuyDatBan(id, tablist());
            }
            else {
                cout << endl << "Ban nay khong ton tai hoac chua co ai dat!" << endl;
            }
            break;
        }
        case 7: {
            string id;
            cout << "\nNhap id ban muon xem order: ";
            cin >> id;
        
            if (!checkTableExist(id)) {
                cout << "\n--- Ban nay khong ton tai trong he thong! ---\n";
                break;
            }
        
            // lấy currentTable nếu nó đang load đúng bàn
            if (!currentTableLoaded || currentTable.getID() != id) {
                cout << "\nBan nay chua co order hoac chua duoc load!\n";
                break;
            }
        
            if (currentTable.getOrders().empty()) {
                cout << "\n------------------------------\n"
                     << "Ban nay chua order!\n"
                     << "------------------------------\n";
            } else {
                cout << "\n----------------------------------------\n"
                     << "ORDER CUA BAN " << id << "\n"
                     << "----------------------------------------\n";
        
                cout << left << setw(10) << "ID"
                     << left << setw(15) << "Ten Mon"
                     << right << setw(10) << "So Luong"
                     << endl << string(60,'-') << endl;
        
                for (auto& p : currentTable.getOrders()) {
                    cout << left << setw(10) << p.first
                         << left << setw(15) << p.first
                         << right << setw(10) << p.second
                         << endl << string(60,'-') << endl;
                }
            }
            break;
        }
        

        default: {
            cout << endl << "--- Vui long chon tu 1 den 7!!! ---" << endl;
            break;
        }
    }
}

void QuanLiDongTien(DongTien& dt, int action) {
    switch(action) {
        case 1: {
            long money = dt.doanhThuHomNay();
            cout << "\nDoanh thu hom nay: "
                 << formatMoney(money) << " VND\n";
            break;
        }
        case 2: {
            long money = dt.doanhThuTuanNay();
            cout << "\nDoanh thu tuan nay: "
                 << formatMoney(money) << " VND\n";
            break;
        }
        case 3: {
            long money = dt.doanhThuThangNay();
            cout << "\nDoanh thu thang nay: "
                 << formatMoney(money) << " VND\n";
            break;
        }
        case 4: {
            long profit = dt.loiNhuanHomNay();
            cout << "\nLoi nhuan hom nay: "
                 << formatMoney(profit) << " VND\n";
            break;
        }
        case 5: {
            long profit = dt.loiNhuanTuanNay();
            cout << "\nLoi nhuan tuan nay: "
                 << formatMoney(profit) << " VND\n";
            break;
        }
        case 6: {
            long profit = dt.loiNhuanThangNay();
            cout << "\nLoi nhuan thang nay: "
                 << formatMoney(profit) << " VND\n";
            break;
        }
        case 7: {
            dt.inSanLuong();
            break;
        }
        case 0: {
            break;
        }
        default: {
            cout << "\nVui long chon tu 0 den 7!!!\n";
            break;
        }
    }
}

#include "../headers/ui_helper.h"

using namespace std;

// ==================== BOX DRAWING ====================

void printBox(const string& title) {
    int width = title.length() + 4;
    cout << "\n";
    cout << "╔";
    for(int i = 0; i < width; i++) cout << "═";
    cout << "╗\n";
    cout << "║  " << title << "  ║\n";
    cout << "╚";
    for(int i = 0; i < width; i++) cout << "═";
    cout << "╝\n";
}

void printHeader(const string& title) {
    int width = 60;
    cout << "\n╔";
    for(int i = 0; i < width; i++) cout << "═";
    cout << "╗\n";
    
    cout << "║" << centerText(title, width) << "║\n";
    
    cout << "╚";
    for(int i = 0; i < width; i++) cout << "═";
    cout << "╝\n";
}

void printSeparator(int width) {
    cout << "├";
    for(int i = 0; i < width; i++) cout << "─";
    cout << "┤\n";
}

void printLine(char fill, int width) {
    for(int i = 0; i < width; i++) cout << fill;
    cout << "\n";
}

void printDoubleLine(int width) {
    for(int i = 0; i < width; i++) cout << "═";
    cout << "\n";
}

// ==================== MESSAGES ====================

void printSuccess(const string& msg) {
    cout << "\n✅ " << msg << "\n";
}

void printError(const string& msg) {
    cout << "\n❌ " << msg << "\n";
}

void printInfo(const string& msg) {
    cout << "\n📌 " << msg << "\n";
}

void printWarning(const string& msg) {
    cout << "\n⚠️  " << msg << "\n";
}

// ==================== MENU ====================

void printMenuOption(int num, const string& icon, const string& text) {
    cout << "│  [" << num << "] " << icon << " " << left << setw(30) << text << "│\n";
}

void printMenuHeader(const string& title) {
    int width = 40;
    cout << "\n┌";
    for(int i = 0; i < width; i++) cout << "─";
    cout << "┐\n";
    
    cout << "│" << centerText(title, width) << "│\n";
    
    cout << "├";
    for(int i = 0; i < width; i++) cout << "─";
    cout << "┤\n";
}

void printMenuFooter() {
    int width = 40;
    cout << "└";
    for(int i = 0; i < width; i++) cout << "─";
    cout << "┘\n";
}

void printSubMenuHeader(const string& title, const string& icon) {
    int width = 50;
    string fullTitle = icon + " " + title + " " + icon;
    
    cout << "\n╔";
    for(int i = 0; i < width; i++) cout << "═";
    cout << "╗\n";
    
    cout << "║" << centerText(fullTitle, width) << "║\n";
    
    cout << "╚";
    for(int i = 0; i < width; i++) cout << "═";
    cout << "╝\n";
}



void printTableBorder(const vector<int>& widths, bool isTop) {
    if(isTop) {
        cout << "┌";
        for(size_t i = 0; i < widths.size(); i++) {
            for(int j = 0; j < widths[i]; j++) cout << "─";
            if(i < widths.size() - 1) cout << "┬";
        }
        cout << "┐\n";
    } else {
        cout << "└";
        for(size_t i = 0; i < widths.size(); i++) {
            for(int j = 0; j < widths[i]; j++) cout << "─";
            if(i < widths.size() - 1) cout << "┴";
        }
        cout << "┘\n";
    }
}

void printTableSeparator(const vector<int>& widths) {
    cout << "├";
    for(size_t i = 0; i < widths.size(); i++) {
        for(int j = 0; j < widths[i]; j++) cout << "─";
        if(i < widths.size() - 1) cout << "┼";
    }
    cout << "┤\n";
}

void printTableHeader(const vector<string>& headers, const vector<int>& widths) {
    printTableBorder(widths, true);
    
    cout << "│";
    for(size_t i = 0; i < headers.size(); i++) {
        cout << " " << left << setw(widths[i] - 2) << headers[i] << " │";
    }
    cout << "\n";
    
    printTableSeparator(widths);
}

void printTableRow(const vector<string>& data, const vector<int>& widths) {
    cout << "│";
    for(size_t i = 0; i < data.size(); i++) {
        cout << " " << left << setw(widths[i] - 2) << data[i] << " │";
    }
    cout << "\n";
}



string padRight(const string& str, int width) {
    if(str.length() >= width) return str;
    return str + string(width - str.length(), ' ');
}

string padLeft(const string& str, int width) {
    if(str.length() >= width) return str;
    return string(width - str.length(), ' ') + str;
}

string centerText(const string& str, int width) {
    if(str.length() >= width) return str;
    int leftPad = (width - str.length()) / 2;
    int rightPad = width - str.length() - leftPad;
    return string(leftPad, ' ') + str + string(rightPad, ' ');
}

// ==================== INPUT ====================

void printPrompt(const string& text) {
    cout << "\n➤ " << text << ": ";
}

void printInputLabel(const string& label, const string& icon) {
    if(icon.empty()) {
        cout << label << ": ";
    } else {
        cout << icon << " " << label << ": ";
    }
}

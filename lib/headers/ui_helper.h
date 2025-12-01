#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

// Box drawing helper functions
void printBox(const string& title);
void printHeader(const string& title);
void printSeparator(int width = 60);
void printLine(char fill = '-', int width = 60);
void printDoubleLine(int width = 60);

// Message functions with icons
void printSuccess(const string& msg);
void printError(const string& msg);
void printInfo(const string& msg);
void printWarning(const string& msg);

// Menu functions
void printMenuOption(int num, const string& icon, const string& text);
void printMenuHeader(const string& title);
void printMenuFooter();
void printSubMenuHeader(const string& title, const string& icon);

// Table functions
void printTableHeader(const vector<string>& headers, const vector<int>& widths);
void printTableRow(const vector<string>& data, const vector<int>& widths);
void printTableSeparator(const vector<int>& widths);
void printTableBorder(const vector<int>& widths, bool isTop = true);

// Formatting helpers
string padRight(const string& str, int width);
string padLeft(const string& str, int width);
string centerText(const string& str, int width);

// Input prompts
void printPrompt(const string& text);
void printInputLabel(const string& label, const string& icon = "");

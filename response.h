#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include <iostream>
#include <vector>

using namespace std;

class Response {
    private:
        vector<string> header;
        vector<vector<string>> resp;
    public:
        void addRow();
        void appendToHeader(string column);
        void appendToLastRow(string value);
        vector<vector<string>> getResponse();
        vector<string> getHeader();
        int getRowNum();
        int getColNum();
};
#endif
#include "response.h"

void Response::addRow() {
    resp.resize(resp.size()+1);
}

void Response::appendToHeader(string column) {
    column.resize(18, ' ');
    header.push_back(column);
}

void Response::appendToLastRow(string value) {
    value.resize(20, ' ');
    resp[resp.size()-1].push_back(value);
}

vector<vector<string>> Response::getResponse() {
    return resp;
}

vector<string> Response::getHeader() {
    return header;
}

int Response::getRowNum() {
    return resp.size();
}

int Response::getColNum() {
    return header.size();
}
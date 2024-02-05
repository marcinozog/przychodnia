#include "response.h"

void Response::addRow() {
    resp.resize(resp.size()+1);
}

void Response::appendToHeader(string column) {
    header.push_back(column);
}

void Response::appendToLastRow(string value) {
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
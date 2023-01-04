/**
 * Option.cc
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#include "Option.h"

inline bool isInteger(const std::string & s) {
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
   char * p ;
   strtol(s.c_str(), &p, 10) ;
   return (*p == 0) ;
}

/**
 * INITIAL METHODS
 *
 */

Option::Option() {

}

Option::Option(string name, string description, bool showOutput) {
    this->name = name;
    this->description = description;
    this->showOutput = showOutput;
}

Option::~Option() {
}

/////////////////
// BOOL OPTION //
/////////////////

BoolOption::BoolOption(string name, string description, bool showOutput, bool defaultValue) : Option(name, description, showOutput) {
    this->defaultValue = defaultValue;
    this->value = this->defaultValue;
}

BoolOption::~BoolOption() {

}

void BoolOption::checkOption(string str, string optionName) {
    if (str.compare("0") != 0 && str.compare("1") != 0) {
        Util::stop(
                        "Error: Option %s has invalid value (%s).", optionName.c_str(), str.c_str());
    }
    value = atoi(str.c_str()) ? true : false;
}

string BoolOption::getValueAsString() {
    return value ? "1" : "0";
}

bool BoolOption::wasChanged() {
    return value != defaultValue;
}

/////////////////
// INT OPTION  //
/////////////////

IntOption::IntOption(string name, string description, bool showOutput, int defaultValue, int max, int min) : Option(name, description, showOutput) {
    this->defaultValue = defaultValue;
    this->max = max;
    this->min = min;
    this->value = this->defaultValue;
}

IntOption::~IntOption() {

}

void IntOption::checkOption(string str, string optionName) {
    if (!isInteger(str)) {
        Util::stop("Error: Option %s has invalid value (%s).", optionName.c_str(), str.c_str());
    }

    value = atoi(str.c_str());
    if (value > max || value < min) {
        Util::stop("Error: Option %s is out of range (%d, min=%d, max=%d).", optionName.c_str(), value, min, max);
    }
}

string IntOption::getValueAsString() {
    return lex(value);
}

bool IntOption::wasChanged() {
    return value != defaultValue;
}


////////////////////
// DOUBLE OPTION  //
////////////////////

DoubleOption::DoubleOption(string name, string description, bool showOutput, double defaultValue, double max, double min) : Option(name, description, showOutput) {
    this->defaultValue = defaultValue;
    this->max = max;
    this->min = min;
    this->value = this->defaultValue;
}

DoubleOption::~DoubleOption() {

}

void DoubleOption::checkOption(string str, string optionName) {
    if (Util::stringToDouble(str, value) != 0) {
        Util::stop("Error: Option %s has invalid value (%s).", optionName.c_str(), str.c_str());
    }

    if (value > max || value < min) {
        Util::stop("Error: Option %s is out of range (%f, min=%f, max=%f).", optionName.c_str(), value, min, max);
    }
}

string DoubleOption::getValueAsString() {
    char buffer[30];
    sprintf(buffer, "%g", value);
    return buffer;
}

bool DoubleOption::wasChanged() {
    return value != defaultValue;
}

////////////////////
// STRING OPTION  //
////////////////////

StringOption::StringOption(string name, string description, bool showOutput, string defaultValue, vector<string> possibleValues) : Option(name, description, showOutput) {
    this->defaultValue = defaultValue;
    this->possibleValues = possibleValues;
    this->value = this->defaultValue;
}

StringOption::~StringOption() {

}

void StringOption::checkOption(string str, string optionName) {
    bool found = false;
    if (!possibleValues.empty()) {
        for (int i = 0; i < (int)possibleValues.size(); i++) {
            if (!possibleValues[i].compare(str)) {
                found = true;
                break;
            }
        }
    } else found = true;

    if (!found) {
        string joined = Util::join(possibleValues, ", ");
        Util::stop("Error: Option %s has invalid value (%s). Possible values are (%s).", optionName.c_str(), str.c_str(), joined.c_str());
    }
    value = str;
}

string StringOption::getValueAsString() {
    return value;
}

bool StringOption::wasChanged() {
    return defaultValue.compare(value) != 0;
}

///////////////////
// ARRAY OPTION  //
///////////////////

ArrayOption::ArrayOption(string name, string description, bool showOutput, int max, int min) : Option(name, description, showOutput) {
    this->defaultValue.resize(0);
    this->value = this->defaultValue;
    this->max = max;
    this->min = min;
}

ArrayOption::~ArrayOption() {

}

void ArrayOption::checkOption(string str, string optionName) {

    if (str.empty()) return;

    vector<string> temp = Util::split(str, ",");

    for (unsigned i = 0; i < temp.size(); i++) {
        if (!isInteger(temp[i])) Util::stop("Error: Option %s has invalid value (%s).", optionName.c_str(), temp[i].c_str());
        value.push_back(atoi(temp[i].c_str()));
        if (value[value.size()-1] < min) Util::stop("In ArrayOption %s, the minimum value is %d.", optionName.c_str(), min);
        if (value[value.size()-1] > max) Util::stop("In ArrayOption %s, the maximum value is %d.", optionName.c_str(), max);
    }

}

string ArrayOption::getValueAsString() {
    string temp = "";
    for (unsigned i = 0; i < value.size(); i++) {
        temp = temp + lex(value[i]);
        if (i < value.size()-1) temp = temp + ",";
    }
    return temp;
}

bool ArrayOption::wasChanged() {
    return value.size() != 0;
}

//////////////////////////
// DOUBLE ARRAY OPTION  //
//////////////////////////

DoubleArrayOption::DoubleArrayOption(string name, string description, bool showOutput, double max, double min) : Option(name, description, showOutput) {
    this->defaultValue.resize(0);
    this->value = this->defaultValue;
    this->max = max;
    this->min = min;
}

DoubleArrayOption::~DoubleArrayOption() {

}

void DoubleArrayOption::checkOption(string str, string optionName) {

    if (str.empty()) return;
    vector<string> temp = Util::split(str, ",");
    
    for (unsigned i = 0; i < temp.size(); i++) {
        double val = 0;
        if (Util::stringToDouble(temp[i], val) != 0)
            Util::stop("Error: Option %s has invalid value (%s).", optionName.c_str(), temp[i].c_str());
        value.push_back(val);
        if (value[value.size()-1] < min) Util::stop("In DoubleArrayOption %s, the minimum value is %g.", optionName.c_str(), min);
        if (value[value.size()-1] > max) Util::stop("In DoubleArrayOption %s, the maximum value is %g.", optionName.c_str(), max);
    }
    
}

string DoubleArrayOption::getValueAsString() {
    string temp = "";
    for (unsigned i = 0; i < value.size(); i++) {
        char buffer[30];
        sprintf(buffer, "%g", value[i]);
        temp = temp + buffer;
        if (i < value.size()-1) temp = temp + ",";
    }
    return temp;
}

bool DoubleArrayOption::wasChanged() {
    return value.size() != 0;
}




///////////////////
// MATRIX OPTION //
///////////////////

MatrixOption::MatrixOption(string name, string description, bool showOutput, int max, int min) : Option(name, description, showOutput) {
    this->defaultValue.resize(0);
    this->value = this->defaultValue;
    this->max = max;
    this->min = min;
}

MatrixOption::~MatrixOption() {

}

void MatrixOption::checkOption(string str, string optionName) {

    if (str.empty()) return;

    vector<string> temp = Util::split(str, ":");

    for (unsigned i = 0; i < temp.size(); i++) {
        vector<string> temp2 = Util::split(temp[i], ",");

        value.push_back(vector<int>());
        for (unsigned j = 0; j < temp2.size(); j++) {
            if (!isInteger(temp2[j])) Util::stop("Error: Option %s has invalid value (%s).", optionName.c_str(), str.c_str());
            value[i].push_back(atoi(temp2[j].c_str()));
            if (value[i][value[i].size()-1] < min) Util::stop("In MatrixOption %s, the minimum value is %d.", optionName.c_str(), min);
            if (value[i][value[i].size()-1] > max) Util::stop("In MatrixOption %s, the maximum value is %d.", optionName.c_str(), max);
        }
    }

    //printf("Size of matrix: %d\n", (int)value.size());
    //Util::printIntMatrix(value);

}

string MatrixOption::getValueAsString() {
    string temp = "";
    for (unsigned i = 0; i < value.size(); i++) {
        for (unsigned j = 0; j < value[i].size(); j++) {
            temp = temp + lex(value[i][j]);
            if (j < value[i].size()-1) temp = temp + ",";
        }
        if (i < value.size()-1) temp = temp + ":";
    }
    return temp;
}

bool MatrixOption::wasChanged() {
    return value.size() != 0;
}


//////////////////////////
// DOUBLE MATRIX OPTION //
/////////////////////////

DoubleMatrixOption::DoubleMatrixOption(string name, string description, bool showOutput, double max, double min) : Option(name, description, showOutput) {
    this->defaultValue.resize(0);
    this->value = this->defaultValue;
    this->max = max;
    this->min = min;
}

DoubleMatrixOption::~DoubleMatrixOption() {

}

void DoubleMatrixOption::checkOption(string str, string optionName) {

    if (str.empty()) return;

    vector<string> temp = Util::split(str, ":");

    for (unsigned i = 0; i < temp.size(); i++) {
        vector<string> temp2 = Util::split(temp[i], ",");

        value.push_back(vector<double>());
        for (unsigned j = 0; j < temp2.size(); j++) {
            if (!isInteger(temp2[j])) Util::stop("Error: Option %s has invalid value (%s).", optionName.c_str(), str.c_str());
            value[i].push_back(atoi(temp2[j].c_str()));
            if (value[i][value[i].size()-1] < min) Util::stop("In DoubleMatrixOption %s, the minimum value is %g.", optionName.c_str(), min);
            if (value[i][value[i].size()-1] > max) Util::stop("In DoubleMatrixOption %s, the maximum value is %g.", optionName.c_str(), max);
        }
    }

    //printf("Size of matrix: %d\n", (int)value.size());
    //Util::printIntMatrix(value);

}

string DoubleMatrixOption::getValueAsString() {
    string temp = "";
    for (unsigned i = 0; i < value.size(); i++) {
        for (unsigned j = 0; j < value[i].size(); j++) {
            temp = temp + lex(value[i][j]);
            char buffer[30];
            sprintf(buffer, "%g", value[i][j]);
            temp = temp + buffer;
            if (j < value[i].size()-1) temp = temp + ",";
        }
        if (i < value.size()-1) temp = temp + ":";
    }
    return temp;
}

bool DoubleMatrixOption::wasChanged() {
    return value.size() != 0;
}




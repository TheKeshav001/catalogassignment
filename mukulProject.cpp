#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <iostream>
#include <fstream>
#include <json/json.h>  // Requires JSON for Modern C++ library
#include <vector>
#include <cmath>

using namespace std;  // Using the standard namespace for simplicity

// Function to convert a number from a given base to decimal
// Takes in the number as a string and its base, and returns the decimal value
long long convertToDecimal(const string& value, int base) {
    long long decimalValue = 0;
    for (char digit : value) {
        decimalValue = decimalValue * base + (isdigit(digit) ? digit - '0' : digit - 'a' + 10);
    }
    return decimalValue;
}
vector<pair<int, long long>> readInputData(const string& filename, int& n, int& k) {
    vector<pair<int, long long>> points;
    
    ifstream file(filename, ifstream::binary);
    Json::Value root;
    file >> root;
    
    n = root["keys"]["n"].asInt();
    k = root["keys"]["k"].asInt();
    
    for (const auto& key : root.getMemberNames()) {
        if (key == "keys") continue;  
        int x = stoi(key); 
        int base = root[key]["base"].asInt(); 
        string value = root[key]["value"].asString();  
        
        long long y = convertToDecimal(value, base);
        
        points.emplace_back(x, y);
    }
    return points;
}

long long findConstantTerm(const vector<pair<int, long long>>& points, int k) {
    long long constantTerm = 0;
    int degree = k - 1;  
    
    for (int i = 0; i <= degree; ++i) {
        long long xi = points[i].first;
        long long yi = points[i].second;
        long long term = yi;  
        
        for (int j = 0; j <= degree; ++j) {
            if (i != j) {
                long long xj = points[j].first;
                term = term * (-xj) / (xi - xj);
            }
        }
        
        constantTerm += term;
    }
    return constantTerm;
}

int main() {
    int n, k;  
    string filename = "input.json"; 
    
    vector<pair<int, long long>> points = readInputData(filename, n, k);
    
    long long constantTerm = findConstantTerm(points, k);
    
    cout << "The constant term (c) is: " << constantTerm << endl;
    return 0;
}
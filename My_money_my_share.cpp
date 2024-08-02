#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> utilFunction(vector<int>& appleWeights, vector<int>& payments) {


    int totalPayment = 0;
    for(auto it : payments){
      totalPayment += it;
    }


    int totalWeight = 0;
    for(auto it : appleWeights){
      totalWeight += it;
    }

    
    vector<double> targetWeights;
    for (int& payment : payments) {
        targetWeights.push_back(totalWeight * (static_cast<double>(payment) / totalPayment));
    }

    vector<vector<int>> distribution(3);
    vector<int> currentWeights(3, 0);

    sort(appleWeights.begin(), appleWeights.end(), greater<int>());

    for (int& weight : appleWeights) {
        int minIndex = 0;
        double minDiff = targetWeights[0] - currentWeights[0];

        for (int i = 1; i < 3; ++i) {
            double diff = targetWeights[i] - currentWeights[i];
            if (diff > minDiff) {
                minDiff = diff;
                minIndex = i;
            }
        }

        distribution[minIndex].push_back(weight);
        currentWeights[minIndex] += weight;
    }

    return distribution;
}

int main() {

    vector<int> payments = {50, 30, 20};  
    vector<int> appleWeights;

    cout << "Enter apple weight in gram (-1 to stop):" << endl;
    while (true) {
        int weight;
        cin >> weight;
        if (weight == -1) {
            break;
        }
        appleWeights.push_back(weight);
    }

    vector<vector<int>> distribution = utilFunction(appleWeights, payments);

    cout << "Distribution :" << endl;
    cout << "Ram:->";
    for ( int& weight : distribution[0]) {
        cout << weight << " ";
    }
    cout << endl;

    cout << "Sham:-> ";
    for ( int& weight : distribution[1]) {
        cout << weight << " ";
    }
    cout << endl;

    cout << "Rahim:-> ";
    for ( int& weight : distribution[2]) {
        cout << weight << " ";
    }
    cout << endl;

    return 0;
}
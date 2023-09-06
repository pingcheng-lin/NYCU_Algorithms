#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

bool compareByX(pair<double, double> p1, pair<double, double> p2) {
    return p1.first < p2.first;
}

bool compareByY(pair<double, double> p1, pair<double, double> p2) {
    return p1.second < p2.second;
}

double myDistance(pair<double, double> p1, pair<double, double> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

double divideConquer(vector<pair<double, double>> point) {
    if(point.size() == 2)
        return myDistance(point[0], point[1]);
    else if(point.size() == 3) {
        double a = myDistance(point[0], point[1]);
        double b = myDistance(point[1], point[2]);
        double c = myDistance(point[0], point[2]);
        return min({a, b, c});
    }

    int mid = ceil(point.size() / 2) - 1;
    vector<pair<double, double>> leftPoint(point.begin(), point.begin() + mid + 1);
    vector<pair<double, double>> rightPoint(point.begin() + mid + 1, point.end());
    double tempMin = min(divideConquer(leftPoint), divideConquer(rightPoint));
    int leftInRange = -1, rightInRange = -1, leftInRangeNum = 0, rightInRangeNum = 0;
    for(auto it = point.begin(); it != point.end(); it++) {
        if((*it).first <= (*it).first - tempMin && (*it).first >= (*it).first + tempMin) {
            point.erase(it);
            it--;
        }
    }
    sort(point.begin(), point.end(), compareByY);
    double mini = tempMin;
    for(int i = 0; i < point.size(); i++) {
        int j = (i - 3) < 0 ? 0 : (i - 3);
        for(; j < i + 3; j++) {
            if(i != j && j < point.size())
                mini = min(mini, myDistance(point[i], point[j]));
        }

    }
    return mini;
}

int main() {
    int time;
    cin >> time;
    for(int k = 0; k < time; k++) {
        int pointNum;
        cin >> pointNum;
        vector<pair<double, double>> point;
        for(int i = 0; i < pointNum; i++) {
            double x, y;
            cin >> x >> y;
            point.push_back(make_pair(x, y));
        }
        sort(point.begin(), point.end(), compareByX);
        cout << divideConquer(point) << endl;
    }
    return 0;
}
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <chrono>
using namespace std;
using namespace chrono;

class Solution {
public:
    int steps = 0; // Track number of operations
    
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<tuple<int, int, int>> intervals; // (left, right, height)
        vector<int> result;
        int max_height = 0;
        
        for (const auto& pos : positions) {
            steps++; // Count each position processed
            
            int left = pos[0];
            int size = pos[1];
            int right = left + size;
            
            // Find the max height under the current square
            int base_height = 0;
            for (const auto& interval : intervals) {
                steps++; // Count each interval checked
                
                int prev_left = get<0>(interval);
                int prev_right = get<1>(interval);
                int prev_height = get<2>(interval);
                
                // Check if intervals overlap
                if (prev_right > left && prev_left < right) {
                    base_height = max(base_height, prev_height);
                    steps++; // Count max operation
                }
            }
            
            // Calculate new height and add interval
            int new_height = base_height + size;
            intervals.emplace_back(left, right, new_height);
            steps++; // Count emplace operation
            
            // Update overall max height
            max_height = max(max_height, new_height);
            steps++; // Count max operation
            result.push_back(max_height);
        }
        
        return result;
    }
};

int main() {
    vector<vector<vector<int>>> testCases = {
        {{1, 2}, {2, 3}, {6, 1}},
        {{100, 100}, {200, 100}},
        {{1, 5}, {2, 2}, {7, 5}}
    };
    
    Solution solution;
    
    for (int i = 0; i < testCases.size(); i++) {
        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "Input: [";
        for (int j = 0; j < testCases[i].size(); j++) {
            cout << "[" << testCases[i][j][0] << "," << testCases[i][j][1] << "]";
            if (j < testCases[i].size() - 1) cout << ", ";
        }
        cout << "]" << endl;
        
        // Time measurement
        auto t1 = high_resolution_clock::now();
        vector<int> result = solution.fallingSquares(testCases[i]);
        auto t2 = high_resolution_clock::now();
        
        auto time_taken = duration_cast<nanoseconds>(t2 - t1).count();
        
        cout << "Output: [";
        for (int j = 0; j < result.size(); j++) {
            cout << result[j];
            if (j < result.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
        
        cout << "Time taken: " << time_taken << " ns" << endl;
        cout << "Number of steps: " << solution.steps << endl << endl;
        
        solution.steps = 0; // Reset step counter for next test case
    }
    
    return 0;
}
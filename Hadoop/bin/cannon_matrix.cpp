#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void initial_row_rotation(vector<vector<int>> &matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        rotate(matrix[i].begin(), matrix[i].begin() + i, matrix[i].end());
    }
}


void rotate_rows_by_one(vector<vector<int>> &matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
       
        rotate(matrix[i].begin(), matrix[i].begin() + 1, matrix[i].end());
    }
}


void initial_column_rotation(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size(); // Number of columns
    for (int j = 0; j < m; ++j) {
        // Extract the j-th column into a temporary vector
        vector<int> temp_column(n);
        for (int i = 0; i < n; ++i) {
            temp_column[i] = matrix[i][j];
        }

        // Rotate the column upward by j positions
        rotate(temp_column.begin(), temp_column.begin() + j, temp_column.end());

        // Write the rotated column back into the matrix
        for (int i = 0; i < n; ++i) {
            matrix[i][j] = temp_column[i];
        }
    }
}


void rotate_columns_by_one(vector<vector<int>> &matrix) {
    int n = matrix.size();    // Number of rows
    int m = matrix[0].size(); // Number of columns

    for (int j = 0; j < m; ++j) {
        // Store the top element of the column temporarily
        int temp = matrix[0][j];

        // Shift all elements in the column upward by 1
        for (int i = 0; i < n - 1; ++i) {
            matrix[i][j] = matrix[i + 1][j];
        }

        // Place the stored top element at the bottom of the column
        matrix[n - 1][j] = temp;
    }
}

vector<vector<int>> elementwise_multiply(const vector<vector<int>> &matrixA, const vector<vector<int>> &matrixB) {
    int rows = matrixA.size();
    int cols = matrixB[0].size();
    vector<vector<int>> result(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] * matrixB[i][j]; 
        }
    }
    return result;
}

int main() {
    int rows, cols;

    
    cout << "Enter the number of rows X columns : ";
    cin >> rows >> cols;
   
   int steps = rows;

    vector<vector<int>> matrixA(rows, vector<int>(cols));
    vector<vector<int>> matrixB(rows, vector<int>(cols));
    vector<vector<int>> currentResult, finalResult;

    
    cout << "Enter elements of matrix A "<<endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrixA[i][j];
        }
    }

    
    cout << "Enter elements of matrix B "<<endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrixB[i][j];
        }
    }

    // Execute the initial rotations
    initial_row_rotation(matrixA);
    initial_column_rotation(matrixB);

    
    currentResult = elementwise_multiply(matrixA, matrixB);
    finalResult = currentResult; // Initialize with the first multiplication result
    
	cout << "\nResult after step 1 (C1):"<<endl;
	for (int i = 0; i < currentResult.size(); ++i) {
	    for (int j = 0; j < currentResult[0].size(); ++j) {
	        cout << currentResult[i][j] << " ";
	    }
	    cout << endl;
	}
	
	steps--;
	
	for (int i = 0; i < steps; ++i) {
	    rotate_rows_by_one(matrixA);
	    rotate_columns_by_one(matrixB);
	
	    
	    currentResult = elementwise_multiply(matrixA, matrixB);
	
	    cout << "\nResult after step " << i + 2 << " (C" << i + 2 << "): "<<endl;
	    for (int r = 0; r < currentResult.size(); ++r) {
	        for (int c = 0; c < currentResult[0].size(); ++c) {
	            cout << currentResult[r][c] << " ";
	        }
	        cout << endl;
	    }
	
	    // Add the current result to the final result
	    for (int r = 0; r < finalResult.size(); ++r) {
	        for (int c = 0; c < finalResult[0].size(); ++c) {
	            finalResult[r][c] += currentResult[r][c];
	        }
	    }
	}
	
	// Display the final accumulated result
	cout << "\nFinal result C = C1 + C2 + C3: "<<endl;
	for (int r = 0; r < finalResult.size(); ++r) {
	    for (int c = 0; c < finalResult[0].size(); ++c) {
	        cout << finalResult[r][c] << " ";
	    }
	    cout << endl;
	}


    return 0;
}


/*
Enter the number of rows X columns : 4 4
Enter elements of matrix A 
2 3 4 5
9 8 7 6
5 4 2 3
8 7 3 4
Enter elements of matrix B 
3 5 7 6
2 7 6 3
7 5 3 2
4 3 2 5

Result after step 1 (C1):
6 21 12 25 
16 35 12 54 
14 9 35 12 
16 40 42 6 

Result after step 2 (C2): 
6 20 10 12 
49 18 63 24 
12 25 24 4 
24 49 9 20 

Result after step 3 (C3): 
28 15 14 9 
24 45 48 14 
15 28 6 15 
14 15 8 48 

Result after step 4 (C4): 
20 10 18 8 
27 56 21 30 
8 10 6 30 
21 12 56 21 

Final result C = C1 + C2 + C3: 
60 66 54 54 
116 154 144 122 
49 72 71 61 
75 116 115 95 

*/

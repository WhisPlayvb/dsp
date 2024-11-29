#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm> // Include this for the rotate function
using namespace std;

// Function to print a matrix
void printMatrix(const vector<vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (const auto &elem : row)
        {
            cout << setw(5) << elem;
        }
        cout << endl;
    }
}


vector<vector<int>> cannonsMatrixMultiplication(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0)); // Initialize result matrix

    // Step 1: Initial Alignment
    vector<vector<int>> A_aligned = A;
    vector<vector<int>> B_aligned = B;

    // Align rows of A
    for (int i = 0; i < n; i++) {
        rotate(A_aligned[i].begin(), A_aligned[i].begin() + i, A_aligned[i].end());
    }
    
    cout<<"\nMatrix A after Rotation :\n";
    printMatrix(A_aligned);
    
    

    // Align columns of B
    for (int j = 0; j < n; j++) {
        vector<int> temp_column(n);
        for (int i = 0; i < n; i++) {
            temp_column[i] = B_aligned[i][j];
        }
        rotate(temp_column.begin(), temp_column.begin() + j, temp_column.end());
        for (int i = 0; i < n; i++) {
            B_aligned[i][j] = temp_column[i];
        }
    }
    cout<<"\nMatrix B after Rotation :\n";
    printMatrix(B_aligned);

    // Step 2: Iterative Multiplication and Alignment
    for (int step = 0; step < n; step++) {
        // Multiply aligned matrices
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A_aligned[i][j] * B_aligned[i][j];
            }
        }
        cout<<"\nResultant Matrix C :\n";
    	printMatrix(C);

        // Shift rows of A left by one position
        for (int i = 0; i < n; i++) {
            rotate(A_aligned[i].begin(), A_aligned[i].begin() + 1, A_aligned[i].end());
        }
        cout<<"\nMatrix A after Rotation :\n";
    	printMatrix(A);

        // Shift columns of B up by one position
        for (int j = 0; j < n; j++) {
            int temp = B_aligned[0][j];
            for (int i = 0; i < n - 1; i++) {
                B_aligned[i][j] = B_aligned[i + 1][j];
            }
            B_aligned[n - 1][j] = temp;
        }
        cout<<"\nMatrix B after Rotation :\n";
    	printMatrix(B);
    }

    return C;
}

vector<vector<int>> Multiply(vector<vector<int>> A,vector<vector<int>> B)
{
	int n=A.size();
	vector<vector<int>> C(n,vector<int>(n,0));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<n;k++)
			{
				C[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
	return C;
}
int main()
{
    int n;
    cout << "Enter the size of the square matrices (n x n): ";
    cin >> n;

    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));

    cout << "Enter elements of matrix A:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
    }

    cout << "Enter elements of matrix B:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> B[i][j];
        }
    }

    cout << "Matrix A:" << endl;
    printMatrix(A);

    cout << "Matrix B:" << endl;
    printMatrix(B);

    vector<vector<int>> C = cannonsMatrixMultiplication(A, B);

    cout << "Resultant Matrix C (A * B) with Canons Matrix Multiplication :" << endl;
    printMatrix(C);
    cout << "Resultant Matrix C (A * B) with Normal Matrix Multiplication :" << endl;
    vector<vector<int>> D = Multiply(A,B);
    printMatrix(D);

    return 0;
}

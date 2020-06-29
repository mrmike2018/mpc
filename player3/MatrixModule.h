#ifndef MPC_MatrixModule_H
#define MPC_MatrixModule_H

#include "MPC_Common_Headers.h"


class MatrixModule {

  public:
    vector <vector <int> > getCofactorVectorMode(vector< vector <int> > A, int k, int l, int n){
        int i = 0, j = 0;
        vector< vector <int> > temp (n);
        //initializing array to zero
        for ( int i = 0 ; i < n ; i++ )
            temp[i].resize(n);

        // Looping for each element of the matrix
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                // Copying into temporary matrix only those element
                // which are not in given row and column
                if (row != k && col != l)
                {
                    temp[i][j++] = A[row][col];

                    // Row is filled, so increase row index and
                    // reset col index
                    if (j == n - 1)
                    {
                        j = 0;
                        i++;
                    }
                }
            }
        }

        return temp;
    }


    /* Recursive function for finding determinant of matrix.
       n is current dimension of A[][]. */
    int determinantVectorMode(vector <vector <int> > A, int n){
        int D = 0; // Initialize result

        //  Base case : if matrix contains single element
        if (n == 1){
            return A[0][0];
        }

        vector <vector <int> > temp (n);       // To store cofactors
        for ( int i = 0 ; i < n ; i++ )
            temp[i].resize(n);

        int sign = 1;  // To store sign multiplier

        // Iterate for each element of first row
        for (int f = 0; f < n; f++)
        {
            temp = getCofactorVectorMode(A, 0, f, n);
            D += sign * A[0][f] * determinantVectorMode(temp, n - 1);

            sign = -sign;
        }

        // Determinant in Zp
        D = D % p;

        return D;
    }


    // Function to get adjoint of A[N][N] in adj[N][N].
    vector <vector <int> > adjointVectorMode(vector <vector <int> > A){
        int n = A.size();
        vector< vector <int> > adj (n);

        for ( int i = 0 ; i < n ; i++ )
            adj[i].resize(n);

        if (n == 1)
        {
            adj[0][0] = 1;
            return adj;
        }

        // temp is used to store cofactors of A[][]
        int sign = 1;

        vector< vector <int> > temp (n);

        for ( int i = 0 ; i < n ; i++ )
            temp[i].resize(n);

        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                temp = getCofactorVectorMode(A, i, j, n);

                // sign of adj[j][i] positive if sum of row
                // and column indexes is even.
                sign = ((i+j)%2==0)? 1: -1;

                // Interchanging rows and columns to get the
                // transpose of the cofactor matrix

                // bringing all numbers in Zp
                PrimeNumModule prmNumModule;

                int tempNum = ((sign)*(determinantVectorMode(temp, n-1))) % p;
                int tempNumInZp =prmNumModule.bringIntoFiniteFieldDomain(tempNum);

                adj[j][i] = tempNumInZp;
            }
        }

        return adj;
    }


    vector <vector <int> > calculateMatrixInverseModpVectorMode (vector <vector <int> > A){
        // Find determinant of A[][]
        int n = A.size();
        int det = determinantVectorMode(A, n);
        if (det == 0)
        {
            cout << "Singular matrix, can't find its inverse! vectorMode";

            exit(-1);
        }

        // Find adjoint
        vector <vector <int> > adj;

        adj = adjointVectorMode(A);

        // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
        PrimeNumModule prmNumModule;
        int determinantInZp = prmNumModule.bringIntoFiniteFieldDomain(det);
        int determinantInverse = prmNumModule.calculateInverseModp(determinantInZp, p);
        int determinantInverseInZp = prmNumModule.bringIntoFiniteFieldDomain(determinantInverse);

        vector <vector <int> > matrixTimesDetInverse = adj;
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                int ijElemnt = (determinantInverseInZp * adj[i][j]) % p;
                matrixTimesDetInverse[i][j] = prmNumModule.bringIntoFiniteFieldDomain(ijElemnt);
            }
        }

        vector <vector <int> > matrixInverse = matrixTimesDetInverse;

        return matrixInverse;
    }


    //this function generates a Vandermonde matrix of an arbitrary dimension
    vector <vector <int> > genegareVandermoneMatrix (int dimension){
        PrimeNumModule myPrimeNumModule;
        vector <vector <int> > Vandermode (dimension);
        for ( int i = 0 ; i < dimension ; i++)
            Vandermode[i].resize(dimension);

        for(int i = 0; i < dimension; i++)
            for(int j = 0; j < dimension; j++)
                //Vandermode[i][j] = myPrimeNumModule.calculatePower(i+1, j);
                Vandermode[i][j] = myPrimeNumModule.modularPower(i+1, j, p);

        return Vandermode;
    }


    // function for multiplying a row vector by a square matrix
    vector <int> multiplyVectorByMatrixModp (vector <int> vec, vector <vector <int> > mat){
        vector <int> result;

        //initializing result to 0:
        for (unsigned i = 0; i < vec.size(); i++)
            result.push_back(0);

        for (unsigned i = 0; i < vec.size(); i++){
            for (unsigned j = 0; j < mat[i].size(); j++){
                result.at(i) = (result.at(i) + vec.at(j) * mat[j][i]) % p;
            }
        }

        return result;
    }
    
    // function for multiplying a row vector by a column vector
    int multiplyVectorByVectorModp (vector <int> rowVec, vector <int> colVec){
        int result = 0;

        for (unsigned i = 0; i < rowVec.size(); i++){
			result = (result + rowVec.at(i) * colVec.at(i)) % p;
        }

        return result;
    }


    // printing a vector
    void printVector (vector <int> vec){
        for(unsigned i = 0; i < vec.size(); i++){
            if(vec[i] < 10)
                cout<<" ";
            cout << vec[i] << " ";
        }
        cout<<endl;
    }


    // printing a matrix, defined by vectors, not arrays.
    void printMatrix (vector <vector <int> > matrix, int m, int n){
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(matrix[i][j] < 10)
                    cout<<" ";
                cout << matrix[i][j] << " ";
            }
            cout<<"\n";
        }
    }


    // printing a matrix, defined by vectors, not arrays, for the case dimension not provided
    void printMatrix (vector <vector <int> > matrix){
        for(unsigned i = 0; i < matrix.size(); i++){
            for(unsigned j = 0; j < matrix.size(); j++){
                if(matrix[i][j] < 10)
                    cout<<" ";
                cout << matrix[i][j] << " ";
            }
            cout<<"\n";
        }
    }
};

#endif   //MPC_MatrixModule_H

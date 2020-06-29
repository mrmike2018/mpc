#ifndef MPC_MPCCalculation_H
#define MPC_MPCCalculation_H

#include "MPC_Common_Headers.h"
#include "MPC_Common_Data.h"

class MPCCalculation {
// This class is responsible for all tasks related to sharing the shares between players

  public:

	/*vector <int> calculateSharesOfMySecret (int myID, int mySecret){
		// evaluate my polynomial on 1, 2, ... numOfPlayers
		vector <int> sharesOfMySecret;
		for(int i = 1; i <= numOfPlayers; i++)
			sharesOfMySecret.push_back(evaluatePolynomialAt(myPoly, i));
		
		return sharesOfMySecret;
	}*/
	
	
	// this is the good function
	// the new function that gets all secret shares and return the sum of the secrets
    //int calculateSumOfShares (vector <vector <int> > sharesOfPlayers){  //fnuction renamed and dimensions of vector are considered in calculation
	/*int calculateSumOfSecrets (vector <vector <int> > sharesOfPlayers){
		
		vector <int> sumOfShares, sumOfSharesPoly;
		
        for(unsigned i = 0; i < sharesOfPlayers[0].size(); i++){
            int sum = 0;
            for(unsigned j = 0; j < sharesOfPlayers.size(); j++){
                sum = (sum + sharesOfPlayers.at(j).at(i)) % p;
            }
			sumOfShares.push_back(sum);
			
        }
		
		vector <vector <int> > xyPointsForInterpolation;
		for(unsigned i = 0; i < sharesOfPlayers[0].size(); i++){
			vector <int> point = {i+1, sumOfShares.at(i)};
			xyPointsForInterpolation.push_back(point);
		}
        int sumOfSecrets = doLagrangeInterpolation(xyPointsForInterpolation, 0);

        return sumOfSecrets;
    }
	*/
	
    // this is the good function
	// the new function that gets all secret shares and return the multiplication of the secrets
    int calculateMultiplicationOfSecrets (vector <vector <int> > sharesOfPlayers){
		
		vector <int> MultiplicationOfShares;
		
	    //~ for(int i = 0; i < sharesOfPlayers[0].size(); i++){
	    for(unsigned i = 0; i < sharesOfPlayers[0].size(); i++){
            int product = 1;
            for(unsigned j = 0; j < sharesOfPlayers.size(); j++){
                product = (product * sharesOfPlayers.at(j).at(i)) % p;
            }
			MultiplicationOfShares.push_back(product);
			
        }
		

        vector <int> multiplicationOfSharesPolyDegreeReduced;
        vector <int> multiplicationOfSharesFinalPoly;
        multiplicationOfSharesPolyDegreeReduced = doDegreeReduction(MultiplicationOfShares);

        // vector for points to send for interpolation
        vector <vector <int> > pointsForIntepolation;

        pointsForIntepolation.push_back({1, multiplicationOfSharesPolyDegreeReduced.at(0)});
        pointsForIntepolation.push_back({2, multiplicationOfSharesPolyDegreeReduced.at(1)});
        pointsForIntepolation.push_back({3, multiplicationOfSharesPolyDegreeReduced.at(2)});

        // getting the very final result, after degree reduction and interpolation and evalation at 0:
        int multiplicationOfSharesFinalResult = doLagrangeInterpolation(pointsForIntepolation, 0);

        return multiplicationOfSharesFinalResult;
    }

    vector <int> doDegreeReduction (vector <int> coefficients){

        vector <int> resultCoefficient;

        cout<<"\n--------------------degree reduction started\n";

        /* generating h polynomials*/
        PolynomialModule myPolyModule;
        vector <vector <int> > hPolys;
        for(int i = 0; i < NumOfPlayers; i++){
            hPolys.push_back(myPolyModule.GetRandCoeff(3, coefficients.at(i), p));
        }
		
        cout<<"\n--------------------h polys:\n";

        for(int i = 0; i < NumOfPlayers; i++)
            myPolyModule.PrintPoly(hPolys[i]);

        //Generating matrix H, similar to the approach of Lecture 10
        vector <vector <int> > matrixH (NumOfPlayers);
        for (int i = 0 ; i < NumOfPlayers; i++)
            matrixH[i].resize(NumOfPlayers);

        for(int i = 0; i < NumOfPlayers; i++)
            for(int j = 0; j < NumOfPlayers; j++){
                //matrixH[i][j] = myPolyModule.Polynomial(hPolys[i], j+1, p);
                matrixH[i][j] = myPolyModule.evaluatePolynomial(hPolys[i], j+1, p);
            }

        //printing H matrix
        MatrixModule myMatrixModule;

        //generating Vandermonde matrix of the dimension of number of players
        vector <vector <int> > VDMmatrix;
        VDMmatrix = myMatrixModule.genegareVandermoneMatrix(NumOfPlayers);
        cout<<"\n--------------------Vandermonde (VDM) matrix (all elements MOD "<< p << "):\n";
        myMatrixModule.printMatrix(VDMmatrix, NumOfPlayers, NumOfPlayers);

        // calculating the inverse of the Vandermonde matrix
        vector <vector <int> > VDMmatrixInverse;
        VDMmatrixInverse = myMatrixModule.calculateMatrixInverseModpVectorMode(VDMmatrix);

        // printing Vandermonde matrix inverse
        cout<<"\n--------------------VDM inverse (all elements MOD "<< p << "):\n";
        myMatrixModule.printMatrix(VDMmatrixInverse, NumOfPlayers, NumOfPlayers);


        /* calculating the product of VDM Inverse by H matrix:
           We only need to multiply the first row of VDM Inverse by H matrix.
           We will get a vector, then by Lagrange interpolation the coefficients of reduced-degree
           polynomial will be achieved */
        vector <int> firstRowOfVDMInverse = VDMmatrixInverse[0];
        cout<<"\n--------------------First row of VDM inverse:"<<endl;
        myMatrixModule.printVector(firstRowOfVDMInverse);

        cout<<"\n--------------------matrix H:\n";
        myMatrixModule.printMatrix(matrixH, NumOfPlayers, NumOfPlayers);

        vector <int> firstRowOfVDMInverseTimesHMatrix =
                        myMatrixModule.multiplyVectorByMatrixModp(firstRowOfVDMInverse, matrixH);

        cout<<"\n--------------------Result of multiplication of first row of VDM inverse by H:"<<endl;
        myMatrixModule.printVector(firstRowOfVDMInverseTimesHMatrix);

        // return results for interpolation
        return firstRowOfVDMInverseTimesHMatrix;
    }


    int doLagrangeInterpolation (vector <vector <int> > xyPoints, int x){

    	PrimeNumModule myPrimeNumMod;

    	int result = 0;
    	int numinator = 1;
    	int denuminator = 1;

    	for ( vector<int>::size_type i = 0; i < xyPoints.size(); i++)
    	{
	        int term = xyPoints.at(i).at(1);

	        numinator = 1;
	        denuminator = 1;
	        for ( vector<int>::size_type j = 0; j < xyPoints.size(); j++)
	        {
	            if (j!=i){
	                numinator = (numinator * myPrimeNumMod.bringIntoFiniteFieldDomain(x - xyPoints[j].at(0))) % p;
	                denuminator = (denuminator * myPrimeNumMod.bringIntoFiniteFieldDomain(xyPoints.at(i).at(0) - xyPoints.at(j).at(0))) % p;
	            }
	        }
	        term = (term * numinator * myPrimeNumMod.calculateInverseModp(denuminator, p)) % p;
	        result = (result + term) % p;
    	}

    	return result;
    }

};

#endif   //MPC_MPCCalculation_H

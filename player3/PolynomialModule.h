#ifndef MPC_PolynomialModule_H
#define MPC_PolynomialModule_H

#include "MPC_Common_Headers.h"

class PolynomialModule{

    public:
    
    //------------------------------------------------------------
    // a[0] = secret, a[1]...a[k-1] = random numbers less than P
    // S is the secret
    // P is the prime number
    vector<int> generateRandomPolynomial(int degree, int S, int P) {
      vector <int> randomPoly;
      //a[0] = S % P ;
      randomPoly.push_back(S % P);

      PrimeNumModule myPrmNumModule;
      for(int i = 1; i <= degree; i++ ) {
        randomPoly.push_back(myPrmNumModule.generateRandomNumber(0, p-1));
      }

      return randomPoly;
    }
    
    
    
    //------------------------------------------------------------
    // Create list of polynomial coefficients:
    // a[0] = secret, a[1]...a[k-1] = random numbers less than P
    // k is the degree of polynomials
    // S is the secret
    // P is the prime number
    vector<int> GetRandCoeff( int k, int S, int P) {

    #ifdef DEBUG
      cout << "->GetRandCoeff k=" << k << " S=" << S << " P=" << P << endl;
    #endif

      vector<int> a (k);
      //srand(time(NULL)); //seed random number generator
      a[0] = S % P ;

      PrimeNumModule myPrmNumModule;
      for( vector<int>::size_type i = 1; i < a.size(); i++ ) {
          //srand(time(NULL)); //seed random number generator
          //a[i] = ( floor( rand() % ( P ) ) );
        a[i] = myPrmNumModule.generateRandomNumber(0, p-1);
      }

    #ifdef DEBUG
      for( vector<int>::iterator i = a.begin(); i != a.end(); ++i ) {
        cout << *i << " ";
      } cout << endl << endl;
    #endif

      return(a);
    }

    //------------------------------------------------------------
    // Evaluate polynomial in mod P
    // a is the polynomial
    // x is the value of the variable
    // P is the prime number
    int Polynomial (vector <int> a, int x, int P){
      int f_x = 0;

      for( vector<int>::size_type i = 0; i < a.size(); i++ ) {
        f_x = (f_x + ( a[i] * (int)pow(x,i) )) % P;
      }

      f_x = f_x % P;

      return( f_x );
    }


    //------------------------------------------------------------
    // Evaluate polynomial in mod P
    // a is the polynomial
    // x is the value of the variable
    // P is the prime number
    int evaluatePolynomial (vector <int> a, int x, int P){
        int f_x = 0;

        PrimeNumModule myPrimeNumModule;

        for( vector<int>::size_type i = 0; i < a.size(); i++ ) {
            //f_x = (f_x + a.at(i) * myPrimeNumModule.modularPower(x, i, P)); // i changed commented this line August 2
            int temp = (a.at(i) * myPrimeNumModule.modularPower(x, i, P)) % P;
            f_x = (f_x + temp ) % p;
        }

        f_x = f_x % P;

        return( f_x );
    }

    //Add polynomial a and polynomial b
    //Returns vector c that is the sum polynomial of a and b
    //------------------------------------------------------------
    vector <int> AddPoly(vector <int> a, vector <int> b)
    {

      if ( a.size() != b.size() ) {
          //throw( runtime_error( "Error, please enter polynomials of equal degree"));
      }

      vector <int> c( a.size() );

      for( vector<int>::size_type i = 0; i < b.size(); i++ ) {
        c[i] = (a[i]+b[i]);
      }

      return c;
    }

    //Multiply polynomial a and polynomial b
    //Returns vector c that is the product of a and b
    //------------------------------------------------------------
    vector <int> MultiPoly(vector <int> a, vector <int> b)
    {

      if ( a.size() != b.size() ) {
          //throw( runtime_error( "Error, please enter polynomials of equal degree"));
      }

      vector <int> c((a.size() + b.size())-1);

      // Take ever term of first polynomial
      for( vector<int>::size_type i = 0; i < a.size(); i++ ) {

        // Multiply the current term of the first polynomial
        //with every term of second polynomial
        for (vector<int>::size_type j = 0; j < b.size(); j++ ){
          c[i+j] = (c[i+j] + a[i]*b[j]) % p;
        }
      }

      return c;
    }


    //Takes a vector and prints to the standard output the
    //polynomial representation
    //------------------------------------------------------------
    void PrintPoly(vector <int> a) {

        for( vector<int>::size_type i = 0; i < a.size(); i++ ) {
            if(i==0)
                cout << a[i];
            else
                cout << a[i] << "x^" << i;
            if( i != a.size() - 1 ){
                cout << " + ";
            }
        }

        cout << endl;
    }
};

#endif   //MPC_PolynomialModule_H

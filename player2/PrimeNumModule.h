#ifndef MPC_PrimeNumModule_H
#define MPC_PrimeNumModule_H

#include "MPC_Common_Headers.h"

using namespace std;

class PrimeNumModule{
    vector<int> primeNumVector;

  public:
    bool isPrimeTrivialDivision(long long int n) {
        // Primality test using trial division method
        if (n <= 1)
            return false;
        if (n == 2)
            return true;
        for (int i = 2; i <= sqrt(n); i++)
            if (n % i == 0)
                return false;
        return true;
    }


    int modularPower(int a, unsigned int m, int n){
        // this function calculates a^m mod n.
        int result = 1;
        a = a % n;  // calculate a mod n, if a > n.


        while (m > 0)
        {
            if (m % 2 == 1)
                result = (result*a) % n;
            m = m>>1;
            a = (a*a) % n;
        }
        return result;
    }


    long long int calculatePower(int a, unsigned int m){
        // this function calculates a^m.
        int result = 1;

        while (m > 0)
        {
            if (m % 2 == 1)
                result = (result*a);
            m = m>>1;
            a = (a*a);
        }
        return result;
    }


    bool isPrimeFermatTest(unsigned int n, int k){

        /* Fermat Test returns true if a number is prime, but
           if the number is composite it returns false with very high probability */

        if (n <= 1 || n == 4)
            return false;
        if (n <= 3)
            return true;

        // Do the test for k times, for more accuracy
        while (k > 0)
        {
            int a = 2 + rand()%(n-4);

            // Fermat theorem
            if (modularPower(a, n-1, n) != 1)
                return false;
            k--;
        }

        return true;
    }


    //~ int calculateInverseModp(int a, int m){
        //~ // A simple way of finding the inverse of a number mod m
        //~ a = a % m;
        //~ for (int i = 1; i < m; i++)
           //~ if ((a * i) % m == 1)
              //~ return i;
    //~ }
    int calculateInverseModp(int a, int m){
        // A simple way of finding the inverse of a number mod m
        int inverseModp;
        a = a % m;
        for (int i = 1; i < m; i++)
           if ((a * i) % m == 1)
				inverseModp = i;
        
        return inverseModp;
    }

    int bringIntoFiniteFieldDomain(int n){
        /*This function receives an integer number and if
          it is not between 0 and p (in finite field Zp)
          then it converts it to a number in Zp, simply
          by adding or subtracting multiples of p to it*/
        if (n >= 0 && n < p)
            return n;

        while (n >= p){
            n = n % p;
        }

        while (n < 0){
            n = n + p;
        }

        return n;
    }


    void SieveOfEratosthenes(int n) {
        /* this method uses an array and the value of array for prime indexes is true
           and for non-prime number it is false.
        */
        bool prime[n+1];
        for (int i=0; i < n+1; i++)
            prime[i] = true;

        for (int i=2; i*i <= n; i++)
        {
            if (prime[i] == true)
            {
                for (int j=i*2; j<=n; j += i)
                    prime[j] = false;
            }
        }

        // Print all prime numbers
        for (int k=2; k<=n; k++)
           if (prime[k])
              cout << k << " ";
    }


    void SieveOfEratosthenes02(int n) {
        // this method uses vectors in C++
        bool prime[n+1];

        for (int i=0; i < n+1; i++)
            prime[i] = true;


        for (int i=2; i*i <= n; i++)
        {
            if (prime[i] == true)
            {
                for (int j=i*2; j<=n; j += i)
                    prime[j] = false;
            }
        }

        // printing prime numbers
        for (int k=2; k<=n; k++)
           if (prime[k]){
                primeNumVector.push_back(k);
           }
    }


    int generateRandomPrime(int n){
        /*This algorithm generates an random prime number.
          It is based on Sieve of Eratosthenes*/

        SieveOfEratosthenes02(n);

        int min = 0;
        int max = primeNumVector.size();

        //srand((unsigned)time(0));
        int randomIntNum = rand() % (max-min + 1) + min;

        int randomPrimeNum = primeNumVector.at(randomIntNum);

        return randomPrimeNum;
    }


    int generateRandomNumber(int min, int max){
        // This function generates a random number between min and max, as its arguments
        int aRandomNum;
        //srand((unsigned)time(0));
        //srand ( time(NULL) );
        //srand((unsigned)time(NULL));
        aRandomNum = rand() % (max-min + 1) + min;

        return aRandomNum;
    }

};

#endif   //MPC_PrimeNumModule_H

#ifndef MPC_DataProcessing_H
#define MPC_DataProcessing_H

#include "MPC_Common_Headers.h"

class DataProcessing{
	
  public:
	
	string vec2str (vector <int> vec){
		stringstream ss;
		copy( vec.begin(), vec.end(), ostream_iterator<int>(ss, ","));
		string resultStr = ss.str();
		resultStr = resultStr.substr(0, resultStr.length()-1);  // removing the last space
		
		return resultStr;
	}
	
	vector <int> str2vec (string str) {
		std::stringstream ss(str);
		
		std::vector<int> resultVec;
		
		int i;

		while (ss >> i)
		{
			resultVec.push_back(i);
			
			//if (ss.peek() == ',')
			if (ss.peek() == ',' || ss.peek() == ' ')
				ss.ignore();
		}
		
		return resultVec;
	}
};

#endif   //MPC_DataProcessing_H

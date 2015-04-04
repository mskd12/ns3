#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
	std::string inputString;
	inputString.assign(argv[1]);

	//cout << inputString << endl;
	ifstream if1(inputString.c_str());
	int a, b;
	std::string line;
	double old = 0;
	double sum = 0;
	int count = 0;

	while(getline(if1,line)) {
		//cout << line << endl;
		stringstream ss(line);
		string part;
		getline(ss, part, ' ');
		double curr = stod(part);
		sum+=(curr-old);
		old = curr;
		count++;
		//cout << curr << " " << part << endl;
		//break;
	}
	if1.close();

	double mean = (sum/count);
	double variance = 0;
	old = 0;
	
	ifstream if2(inputString.c_str());
	
	while(getline(if2,line)) {
		stringstream ss(line);
		string part;
		getline(ss, part, ' ');
		double curr = stod(part);
		variance += ((curr-old) - mean)*((curr-old) - mean);
		old = curr;
	}
	variance = (variance)/count;

	printf("%f\n", sqrt(variance));

	if2.close();
}
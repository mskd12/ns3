#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
	std::string inputString, line;
	inputString.assign(argv[1]);

	//cout << inputString << endl;
	ifstream if1(inputString.c_str());
	int sum = 0, count = 0;

	while(getline(if1,line)) {
		//cout << line << endl;
		stringstream ss(line);
		string part;
		getline(ss, part, ' ');
		getline(ss, part, ' ');
		int curr = stoi(part);
		sum+=curr;
		count+=(curr+1);
		//cout << curr << " " << part << endl;
		//break;
	}
	if1.close();

	cout << float(sum)/count << endl;
}
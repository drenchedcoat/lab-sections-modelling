#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>

using namespace std;

//create  function to decrypt each char
char char_decrpyt(string line,int x, int num){
    if(isupper(line[x])){
        //does not change
        return (char)(line[x]);
    }
    else if (islower(line[x])){
        //changes
        return (char)(((line[x] - num - 'a' + 26) % 26) + 'a');
    }
    else{
        return (char)(line[x]);
    }
}

//create a function to read line and decrypt
string decrypt(string line, int num){
    string newline = "";
    for (size_t x = 0; x < line.size(); x++){
        //decrypt each char here
        newline += char_decrpyt(line,x, num);

    }
    return newline;
}

int main()
{
    ifstream thefile("encrypted.txt");
    if (!thefile) {
		cerr << "Could not find file.\n" << endl;
		exit(1);
	}

	//convert file into vector of lines
	string line;
	vector<string> poem;
	cout << "---SystemOutPrinting original file:---" << endl;
	while (getline(thefile,line)) {
        poem.push_back(line);
        cout << line << endl;
	}

	//reverse-flip lines, without number line
	vector<string> swappedpoem;
	cout << "\n\n---SystemOutPrinting reverse lines file:---" << endl;
	for (size_t x = poem.size()-1; x > 0; x--){
        swappedpoem.push_back(poem[x]);
        cout << poem[x] << endl;
    }

    string strval = poem[0];
    char charval = strval[0];
    int numval = charval - 48;
    cout << numval<< endl;

    cout << "\n\n---SystemOutPrinting decrypted file:---" << endl;
    for (size_t x = 0; x < swappedpoem.size(); x++){
        cout << decrypt(swappedpoem[x], numval) << endl;
    }

    return 0;
}

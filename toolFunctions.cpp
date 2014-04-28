#include "toolFunctions.h"

void openErr(string filename)
{
	cout << "I/O failure when opening file " << filename << endl;
	exit(1);
}

void outputErr()
{
	cout << "I/O failure when outputting file.";
	exit(2);
}

//get the regular express of keywords
string getKeywordExp()
{
	string exp = "(";
	
	ifstream keywordlist(listfilename);
	if (keywordlist.good())
	{
		string temp;
		while (!keywordlist.eof())
		{
			keywordlist >> temp;
			exp.append(temp);
			exp.append("|");
		}
		//delete the last "|"
		exp.erase(exp.length() - 1, 1);

		exp.append(")");
	}
	else
		openErr(listfilename);//exit(1)
	return exp;
}
#include <iostream>
#include <string>
#include <fstream>
#include <regex>//TODO:
#include "toolFunctions.h"
using namespace std;

void highlight(ifstream& source, string& buffer);
void preProcess(ifstream& ifs, string& buffer);
void highlightComment(string& buffer);

void writeHead(string& buffer, string filename);
void writeCode(string& outputBuffer, string& codeBuffer);
void writeFoot(string& buffer);

using namespace std;

int main()
{
	string sourceFileName;
	string outputFileName;
	ifstream ifs;
	ofstream ofs;
	cout<< "*********************   An C/CPP File Syntax Highlightor   *********************"
		<< "*      Simply revise your C/CPP file to html file wiht syntax highlighted      *"
		<< "********************************************************************************"
		<< endl;
	cout << "Pleas input your file name: \n";
	cin >> sourceFileName;
	outputFileName = sourceFileName + ".html";

	//IO part
	ifs.open(sourceFileName);
	if (!ifs.good())
		openErr(sourceFileName);
	ofs.open(outputFileName);
	if (!ofs.good())
		outputErr();
	string codeBuffer;
	string outputBuffer;
	preProcess(ifs, codeBuffer);
	highlightComment(codeBuffer);
	writeHead(outputBuffer,sourceFileName);
	writeCode(outputBuffer, codeBuffer);
	writeFoot(outputBuffer);
	ofs.write(outputBuffer.c_str(), outputBuffer.length());
	ifs.close();
	ofs.close();
	return 0;
}

void highlight(ifstream& source, string& buffer)
{
	string oneLine;
	string newLine;
	regex eKeyword(getKeywordExp());
	getline(source, oneLine);
	regex_replace(oneLine, eKeyword, newLine);
}

void preProcess(ifstream& ifs, string& buffer)
{
	char ch;
	while (ifs.good())
	{
		ch = ifs.get();
		if (ch == '<')
			buffer += "&lt";
		else if (ch == '>')
			buffer += "&gt";
		else
			buffer += ch;
	}
}

void highlightComment(string& buffer)
{
	string temp;
	regex eComment("(/\\*([^*]|[\\r\\n]|(\\*+([^*/]|[\\r\\n])))*\\*+/)|(//.*)");
	string fmt = "<span class=\"comment\">$&</span>";
	temp = regex_replace(buffer, eComment, fmt);
	buffer = temp;
}

void writeHead(string& buffer, string filename)
{
	buffer += "<html>\n";
	buffer += "<head>\n";
	buffer += "<title>" + filename + "</title>\n";
	buffer += "<link href=\"StyleSheet.css\" media=\"all\" rel=\"stylesheet\" type=\"text/css\">\n";
	buffer += "</head>\n";
	buffer += "<body>\n";
	buffer += "<pre>\n";
}

void writeCode(string& outputBuffer, string& codeBuffer)
{
	outputBuffer += codeBuffer;
}

void writeFoot(string& buffer)
{
	buffer += "</pre>\n";
	buffer += "</body>\n";
	buffer += "</html>\n";
}
#include <iostream>
#include <fstream>
using namespace std;

void textStatistics(char name[], float Arr[], int size)
{
	ifstream fin(name);
	int wCount = 0, cCount = 0, sCount = 0, pCount = 1;
	int lCount = 0;
	float avgWords,avgSent;
	char ch;


	if(fin.fail())
	{
		cout<<"Could not open file.";
	}
	else
	{
		while (!fin.eof())
		{
			ch = fin.get();
			if (ch == '.' || ch == '!' || ch == '?')
			{
				sCount++;
				wCount++;
				cCount++;
			}
			else if (ch >= 65 && ch <= 122)
			{
				lCount++;
				cCount++;
			}
			else if(ch >= 33 && ch <= 64 || ch > 122 && ch <= 126)
			{
				cCount++;
			}
			else if (ch == 32)
			{
				wCount++;
				cCount++;
			}

			else if (ch == 10)
			{
				pCount++;
			}
		}
		avgWords = float(lCount)/wCount;
		avgSent = float(wCount)/sCount;

		Arr[0] = cCount;
		Arr[1] = wCount;
		Arr[2] = sCount;
		Arr[3] = pCount;
		Arr[4] = avgWords;
		Arr[5] = avgSent;

	cout << "Character Count: " << cCount << endl << "Word Count: " <<  wCount << endl << "Sentence Count: " << sCount <<
		endl << "Paragraph Count: " << pCount << endl;
	cout << "Average length of word: " << avgWords << endl;
	cout << "Average length of sentence: " << avgSent << endl;
	}
}

int main()
{
	float arr[6];
	textStatistics("C:\\temp\\test2.txt",arr,6);
	return 0;
}
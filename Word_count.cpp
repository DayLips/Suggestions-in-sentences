#include "Word_count.h"

Word_count::Word_count(string word, int count)
{
	this->Word = word;
	this->Count = count;
}

string Word_count::get_Word()
{
	return Word;
}

int Word_count::get_Count()
{
	return Count;
}

void Word_count::add_Count(int t)
{
	this->Count += t;
}

void Word_count::Write()
{
	cout << Word << " - " << Count << endl;
}

Word_count::~Word_count()
{
}

#pragma once
#include<iostream>

using namespace std;

class Word_count
{
public:
	Word_count(string word, int count);
	string get_Word();
	int get_Count();
	void add_Count(int t);
	void Write();
	~Word_count();
private:
	string Word = "";
	int Count = 0;
};


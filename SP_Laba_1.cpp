#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>
#include <Windows.h>
#include "Word_count.h"
#include "Lemmatization.h"


using namespace std;

bool is_invalid_char(char c);
vector<string> Text_to_words(string filename);
unordered_map<string, vector<Word_count>> Markov_Tcep(vector<string> text);
int get_Max_Count(vector<Word_count> words);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");
    string file = "Text.txt";
    vector<string> Text = Text_to_words(file);
    unordered_map<string, vector<Word_count>> chain = Markov_Tcep(Text);
    while (true)
    {
        string predl;
        cout << "Введите предолжение: ";
        getline(cin, predl);
        
        if (predl == "выход") break;

        istringstream iss(predl);
        vector<string> words;
        string word;

        while (iss >> word)
        {
            while (!word.empty() && is_invalid_char(word.front()))
            {
                word.erase(word.begin());
            }
            while (!word.empty() && is_invalid_char(word.back()))
            {
                word.pop_back();
            }
            for (char& c : word) {
                c = tolower(c);
            }
            if (!word.empty())
            {
                istringstream input_stream(word);
                lemmatizer::Lemmatization lemmatizer(input_stream);
                const string* lemma = lemmatizer.next_lemma();
                word = *lemma;
                words.push_back(word);
            }
        }

        bool f = true;
        for (int i = words.size() - 1; i >= 0; i--)
        {
            auto it = chain.find(words[i]);
            if (it != chain.end())
            {
                f = false;
                int max_i = get_Max_Count(chain[words[i]]);
                vector<Word_count> lol = chain[words[i]];
                cout << chain[words[i]][max_i].get_Word() << endl;
                break;
            }
        }
        if (f) cout << "Введите другое предложение!!!" << endl;
        cout << endl;
    }
    
    
}

bool is_invalid_char(char c)
{
    return ispunct(c) || c == '«' || c == '»' || c == '…';
}

vector<string> Text_to_words(string filename)
{
    ifstream fin(filename);
    string line;
    vector<string> words;
    while (getline(fin, line))
    {
        istringstream iss(line);
        string word;
        while (iss >> word)
        {
            while (!word.empty() && is_invalid_char(word.front())) 
            {
                word.erase(word.begin());
            }
            while (!word.empty() && is_invalid_char(word.back())) 
            {
                word.pop_back();
            }
            for (char& c : word) {
                c = tolower(c);
            }
            if (!word.empty()) 
            {
                istringstream input_stream(word);
                lemmatizer::Lemmatization lemmatizer(input_stream);
                const string* lemma = lemmatizer.next_lemma();
                word = *lemma;
                words.push_back(word);
            }
        }
    }
    fin.close();
    return words;
}

unordered_map<string, vector<Word_count>> Markov_Tcep(vector<string> words)
{
    unordered_map<string, vector<Word_count>> markov_tcep;
    for (int i = 0; i < (words.size() - 1); i++)
    {
        string prefix = words[i];
        string suffix = words[i + 1];

        if (markov_tcep[prefix].size() != 0)
        {
            bool flag = true;
            for (int j = 0; j < markov_tcep[prefix].size(); j++)
            {
                if (markov_tcep[prefix][j].get_Word() == suffix)
                {
                    markov_tcep[prefix][j].add_Count(1);
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                markov_tcep[prefix].push_back(Word_count(suffix, 1));
            }
        }
        else
        {
            markov_tcep[prefix].push_back(Word_count(suffix, 1));
        }
    }
    return markov_tcep;
}

int get_Max_Count(vector<Word_count> words)
{
    int t = -1;
    int index = 0;
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i].get_Count() > t)
        {
            t = words[i].get_Count();
            index = i;
        }
    }
    return index;
}
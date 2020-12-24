#include <iostream>
#include <vector>
#include <string>
#include <fstream>
int main()
{
std::vector<std::string> dict;
std::vector<std::string>::iterator it;
std::ifstream inf;
std::string temp, word, sentence;
bool done = false;
char input;
inf.open("dict.txt");
while(!inf.eof())
{
inf >> word;
dict.push_back(word);
}
temp = "";
word = "";
ConstructPatterns(src, delimiters, n, fixed)
{
des = AllocateBuffer() Copy(des, src)
DiscardDelimiters(des, delimiters) dic = InitializePatternsDictionary()
pattern = InitializeNewPattern(des) While(des)
{
node = dic.Insert(pattern) if(!fixed AND node.IsRepeated)
AddWordToPattern(des, pattern) else
pattern = InitializeNewPattern(des) UpdateBuffer(des)
}
}
March 2019
sentence = "";
std::cout << "Press 1 to accept autocomplete word\n" <<
"Press 2 to accept current word\n" << std::endl;
while(!done)
{
std::cin >> input;
if(input == '1')
{
sentence += temp + ' ';
word = "";
std::cout << sentence << std::endl;
}
else if(input == '2')
{
sentence += word + ' ';
word = "";
std::cout << sentence << std::endl;
}
else if(input != '0')
{
word += input;
for(it = dict.begin(); it != dict.end(); ++it)
{
if(word == (*it).substr(0, word.length()))
{
std::cout << (*it) << std::endl;
temp = (*it);
break;
}
}
}
else
done = true;
}
std::cout << sentence << std::endl;
return 0;
}

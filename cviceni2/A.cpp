#include <iostream>
#include <list>
#include <stdio.h>
#include "catch.hpp"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file


std::vector <std::vector<char> > permutation(std::vector<char> in){
	std::vector< std::vector<char> > out;
        
	if (in.size() == 1)
	{
		out.push_back(in);
		return out;
	}

	for (int i = 0; i < in.size(); ++i)
	{
		std::vector<char>shorter = in;
		shorter.erase(shorter.begin()+i);
		std::vector< std::vector <char> > perm = permutation(shorter);
		for (std::vector< std::vector<char> >::iterator it=perm.begin(); it != perm.end(); ++it){
			it->insert(it->begin(),in[i]);
			//(*it).push_front(in.front());
			out.push_back(*it);
		}
	}
}


std::vector <std::vector<char> > combination(std::vector<char> in, int numberOfElements, bool repeat){

	std::vector< std::vector<char> > out;
		std::vector<char> blank; // I need to return 1 empty combination in recursion, so I will be able to add elements to the begin in the for loop
		char first = in[0];
	if (in.size() == 0)
	{
		out.push_back(blank);
		return out;
	}

	if (numberOfElements == 0)
	{
		out.push_back(blank);
		return out;
	}

	if (numberOfElements == in.size() )
	{
		out.push_back(in);
		return out;
	}


	in.erase(in.begin());
	std::vector<std::vector<char> > out1 = combination(in,numberOfElements-1, repeat);	
	std::vector<std::vector<char> > out2 = combination(in,numberOfElements, repeat);	

	for (std::vector< std::vector<char> >::iterator it=out1.begin(); it != out1.end(); ++it){
		it->insert(it->begin() , first);
		out.push_back(*it);
	}

	for (std::vector< std::vector<char> >::iterator it2=out2.begin(); it2 != out2.end(); ++it2){
		out.push_back(*it2);
	}
	return out;
}

std::vector <std::vector<char> > variation(std::vector<char> in, int numberOfElements, bool repeat){

	std::vector<std::vector<char> > out = combination(in,numberOfElements, repeat);	
	std::vector<std::vector<char> > out2;
	std::vector<std::vector<char> > out3;
	for (std::vector<std::vector<char> >::iterator i = out.begin(); i != out.end(); ++i)
	{
		out2 = permutation(*i);
		for (std::vector<std::vector<char> >::iterator it = out2.begin(); it != out2.end(); ++it)
		{
			out3.push_back(*it);
		}
		
	}

	return out3;
}


/**
int main(int argc, char const *argv[])
{
    
	std::vector<char> input;
	input.push_back('A');
	input.push_back('B');
	input.push_back('C');
	std::vector< std::vector <char> > out = permutation(input);
	for (std::vector< std::vector<char> >::iterator it=out.begin(); it != out.end(); ++it){
		for (std::vector< char>::iterator i=it->begin(); i != it->end(); ++i){
			printf("%c", *i);
		}
			printf("\n");
	}

	return 0;
}
**/
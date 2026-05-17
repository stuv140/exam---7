#pragma once
#include<string>
class command {
public:
	command():i(0){}
	bool is(char*);
private:
	int i;
};
bool command::is(char* com)
{
	auto validate = [i](char* com)->bool {
		char ch[3] = {'c','m','d'};
		std::string str = std::string(ch)+std::to_string(i)	;
		return false;
		}
	return true;
}

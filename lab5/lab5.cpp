#include "Stack.h"
bool bracketCheck(const std::string& s){
	Stack<char> charList;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '[' || s[i] == '(' || s[i] == '<' || s[i] == '{')
		{
			charList.push(s[i]);
		}
		else if (s[i] == ']')
		{
			if (charList.top() == '[')
			{
				charList.pop();
			}
			else
				return false;
		}
		else if (s[i] == ')')
		{
			if (charList.top() == '(')
			{
				charList.pop();
			}
			else
				return false;
		}
		else if (s[i] == '>')
		{
			if (charList.top() == '<')
			{
				charList.pop();
			}
			else
				return false;
		}
		else if (s[i] == '}')
		{
			if (charList.top() == '{')
			{
				charList.pop();
			}
			else
				return false;
		}
	}
	if (charList.empty())
		return true;
	else
		return false;
}

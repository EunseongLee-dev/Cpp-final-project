#pragma once
#include <iostream>

class Item
{
private:
	std::string Name;
	std::string Type;
	int			Value;

public:
	Item(std::string _name, std::string _type, int _value);

	std::string GetName() const;

	std::string GetType() const;

	int GetValue() const;
};
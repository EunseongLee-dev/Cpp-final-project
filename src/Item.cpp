#include "Item.h"

Item::Item(std::string _name, std::string _type, int _value)
	:Name(_name)
	,Type(_type)
	,Value(_value)
{
}

std::string Item::GetName() const
{
	return Name;
}

std::string Item::GetType() const
{
	return Type;
}

int Item::GetValue() const
{
	return Value;
}


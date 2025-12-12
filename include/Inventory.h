#pragma once
#include <vector>
#include <memory>
#include <string>

class Item;

class Inventory
{
private:
	std::vector<std::unique_ptr<Item>> Items;

public:

	Inventory();
	~Inventory();

	void AddItem(std::unique_ptr<Item> item);

	void RemoveItem(size_t index);

	Item* GetItem(size_t index) const;

	void PrintInventory() const;

	size_t Count() const;

	
};
#pragma once
#include <string>
#include <vector>

struct HashTableElement
{
  std::string m_key{ "" }; //Key as asked to be string.
  int m_value{ 0 }; //Value as asked to be an integer.
  bool m_is_occupied{ false }; // Check if we already have written some data in this element.
  // In case we delete an entry we simply flag it as deleted until we replace it with another value. 
  // If we check only the occupance, the search may stop wrongfully as the probing may have found a different index because a previous confict.
  bool m_is_deleted{ false }; 
};

struct HashTable
{
private:
  std::vector<HashTableElement> m_table; //This is going to be the fixed size table. It is a vector but we are going to use hashing index for the operations to directly get the index (for O(1) complexity) and avoid iterating as this increases the complexity.
  std::vector<int> m_insertions_orders; //This is going to be helpful to keep track of the operations and return in O(1) complexity the first and the last elements.
  size_t m_active_size; //This is the current size of the HashTable and in general m_active_size <= capacity.
  size_t m_capacity; //Capacity of our HashTable.
public:
  explicit HashTable(size_t _capacity); //Constructor setting the capacity and active size

  int getStringHash(const std::string& _key); // Hash function to compute the hash index of a key 
  void insert(const std::string& _key, int value); //Insertion operation.
  void remove(const std::string& _key); //Removing operation
  int get(const std::string& _key); //Get operation.
  std::pair<std::string, int> get_last(); // Get last inserted pair
  std::pair<std::string, int> get_first(); // Get first inserted pair

  void print(); //Useful for debugging and for showcasing the results.
};
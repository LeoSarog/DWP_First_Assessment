#include "HashTable.h"

#include <iostream>

HashTable::HashTable(size_t _capacity)
  : m_capacity(_capacity)
  , m_active_size(0)
{
  m_table.resize(_capacity);
}

//Getting the string hash ensures is that we do not to need to iterate in order to insert/remove table entries, 
//keeping the complexity to O(1).
int HashTable::getStringHash(
  const std::string& _key)
{
  std::hash<std::string> hashFunc;   // Use the standard hash function for strings
  return hashFunc(_key) % m_capacity; // Modulo to keep within table size
}

void HashTable::insert(
  const std::string& _key, 
  int _value)
{
  int index = getStringHash(_key); // Compute hash index
  int initial_index = index;     // Store the original index for probing

  // Normally if there is not a conflict here (already occupied memory for an entry) we are going to skip this and 
  // directly continue the insertion.
  while (m_table[index].m_is_occupied && !m_table[index].m_is_deleted && m_table[index].m_key != _key) {
    index = (index + 1) % m_capacity; // Linear probing (here we could also implement different types of probing in necessary)
    if (index == initial_index) {
      std::cerr << "Hash table is full!" << std::endl;
      return;
    }
  }

  // If the entry is new or previously deleted
  if (!m_table[index].m_is_occupied || m_table[index].m_is_deleted) {
    m_table[index].m_key = _key;
    m_table[index].m_value = _value;
    m_table[index].m_is_occupied = true;
    m_table[index].m_is_deleted = false;
    m_insertions_orders.push_back(index); // Track the insertion order
    ++m_active_size;
  }
  else {
    // If the key already exists, update its value
    m_table[index].m_value = _value;
  }
}

void HashTable::remove(
  const std::string& _key)
{
  int index = getStringHash(_key);
  int initial_index = index;

  while (m_table[index].m_is_occupied) {
    if (m_table[index].m_key == _key && !m_table[index].m_is_deleted) {
      m_table[index].m_is_deleted = true;
      --m_active_size;
      return;
    }
    index = (index + 1) % m_capacity; // Linear probing
    if (index == initial_index) {
      break;
    }
  }
}

// Get the value for the corresponding key
int HashTable::get(
  const std::string& _key) {
  int index = getStringHash(_key);
  int initial_index = index;

  while (m_table[index].m_is_occupied) {
    if (m_table[index].m_key == _key && !m_table[index].m_is_deleted) {
      return m_table[index].m_value;
    }
    index = (index + 1) % m_capacity; // Linear probing
    if (index == initial_index) {
      break;
    }
  }

  std::cerr << "The following key was not found: " << _key << std::endl;
  return -1; // Return an error code if key is not found for the user to handle it in calling code.
}

//O(1) complexity as we get directly the last element.
std::pair<std::string, int>  HashTable::get_last() {
  if (m_insertions_orders.empty()) {
    std::cerr << "No entries in the hash table!" << std::endl;
    return { "", -1 };
  }

  int index = m_insertions_orders.back(); // Get the last inserted index
  return { m_table[index].m_key, m_table[index].m_value };
}

//O(1) complexity as we get directly the first element.
std::pair<std::string, int> HashTable::get_first() {
  if (m_insertions_orders.empty()) {
    std::cerr << "The hash table is currently empty!" << std::endl;
    return { "", -1 };
  }

  int index = m_insertions_orders.front(); // Get the first inserted index
  return { m_table[index].m_key, m_table[index].m_value };
}

void HashTable::print()
{
  for (const auto& hast_table_element : m_table)
  {
    if (!hast_table_element.m_is_deleted && hast_table_element.m_key.size())
    {
      std::cout << "(" << hast_table_element.m_key << "," << hast_table_element.m_value << ")" << std::endl;
    }
  }
  std::cout << std::endl;
}

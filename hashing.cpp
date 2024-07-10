#include <iostream>
#include <string>
#include<ctime>

using  namespace std;

uint32_t jenkins_hash(const std::string& key) {
  /*
  This function implements a simplified version of the Jenkins one-at-a-time
  hash function for demonstration purposes.

  Args:
      key: The data to be hashed (string)

  Returns:
      A 32-bit hash value (uint32_t)
  */
  uint32_t hash = 0;
  for (char byte : key) {
    hash += static_cast<uint32_t>(byte);
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}

class HashTable {
public:
  HashTable(int size) : size_(size), count_(0) {
    table_ = new std::pair<std::string, int>[size];
  }

  ~HashTable() {
    delete[] table_;
  }

  void insert(const std::string& key, int value) {
    /*
    Inserts a key-value pair into the hash table.

    Args:
        key: The key to insert (string)
        value: The value associated with the key (int in this example)
    */
    uint32_t hash = jenkins_hash(key) % size_;
    int i = hash;
    while (table_[i].first != "" && table_[i].first != key) {
      i = (i + 1) % size_;
      if (i == hash) {
        // Reached full circle, no empty slots
        throw std::runtime_error("Hash table overflow");
      }
    }
    table_[i] = std::make_pair(key, value);
    count_++;
  }

  int get(const std::string& key) const {
    /*
    Retrieves the value associated with a key from the hash table.

    Args:
        key: The key to search for (string)

    Returns:
        The value associated with the key, or -1 if not found
    */
    uint32_t hash = jenkins_hash(key) % size_;
    int i = hash;
    while (table_[i].first != "") {
      if (table_[i].first == key) {
        return table_[i].second;
      }
      i = (i + 1) % size_;
      if (i == hash) {
        // Reached full circle, key not found
        return -1;
      }
    }
    return -1;
  }


private:
  int size_;
  int count_;
  std::pair<std::string, int>* table_;
};

int main() {
    
  srand(time_t(0));

  clock_t _start = clock();
  HashTable hash_table(100);
  hash_table.insert("apple", 1);
  hash_table.insert("banana", 2);
  hash_table.insert("cherry", 44);  // Collision with "apple"
  hash_table.insert("orange", 56);
  hash_table.insert("mango", 8);

  std::cout << hash_table.get("apple") << std::endl;  // Output: 1
  std::cout << hash_table.get("cherry") << std::endl;  // Output: 44 (found due to linear probing)
   std::cout << hash_table.get("banana") << std::endl;  // Output: 2
  std::cout << hash_table.get("orange") << std::endl;  // Output: 56
   std::cout << hash_table.get("mango") << std::endl;  // Output: 8

  clock_t _end = clock();

  std::cout << "Time taken for 5 items in a table of size 100: " << ((_end - _start)/CLOCKS_PER_SEC) << " seconds" << std::endl;



  return 0;
}
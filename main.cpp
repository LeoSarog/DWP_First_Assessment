#include "GutenbergDataset.h"
#include "HashTable.h"
#include "ConnectEndpoint.h"
#include "TradesParser.h"

#include <iostream>
#include <vector>
#include <string>



int runFirstExercise()
{
  size_t dataset_size = 1000;
  size_t fixed_hash_size = 10;

  // Read words from the file
  std::string filename = "98-0.txt"; // Path to the uploaded file
  std::vector<std::string> words = readWords(filename);

  // Check if words are loaded correctly
  if (words.empty()) {
    std::cerr << "No words found in the file!" << std::endl;
    return EXIT_FAILURE;
  }

  // Generate a random dataset of words.
  std::vector<std::string> words_dataset = getRandomWords(words, dataset_size);;

  HashTable hash_table(fixed_hash_size);

  std::cout << "Inserting the following dataset to the HashTable:" << words_dataset[0] << " " << words_dataset[2] << " " << words_dataset[3] << std::endl;

  // Insert some key-value pairs.
  hash_table.insert(words_dataset[0], 9);
  hash_table.insert(words_dataset[2], 32);
  hash_table.insert(words_dataset[3], 4);
  hash_table.print();
  // Update an existing key-value pair.
  hash_table.insert(words_dataset[0], 6);
  hash_table.print();
  // Remove the pair that we updated.
  hash_table.remove(words_dataset[0]);
  hash_table.print();
  // Get a value from an existing key
  int value = hash_table.get(words_dataset[2]);
  std::cout << "We found the following pair using the get function:(" << words_dataset[2] << "," << value << ")" << std::endl;
  // Get a value from a non existing key to ensure that we handle this case.
  hash_table.get("NonExistingKey"); //This is going to log directly that we did not found the key but we could also use the return code to handle it externally.
  // Get the first inserted/updated key-value pair 
  std::pair<std::string, int> first = hash_table.get_first();
  std::cout << "First key-value pair:(" << first.first << "," << first.second << ")" << std::endl;
  // Get the last inserted/updated key-value pair 
  std::pair<std::string, int> last = hash_table.get_last();
  std::cout << "Last key-value pair:(" << last.first << "," << last.second << ")" << std::endl;

  return EXIT_SUCCESS;
}

int runSecondExercise()
{
  //Using the url for the aggTrades for a specific symbol. Here for the example I am using BTCUSDT since I noticed it when visiting your site.
  auto url = "https://fapi.binance.com/fapi/v1/aggTrades?symbol=BTCUSDT";
  auto json = getResponseFromEndpoint(url);

  std::cout << "We got this response from the server\n" << json.str() << std::endl;
  
  //Parsing the raw json string in to a structure representing each trade.
  auto parse_begin = std::chrono::high_resolution_clock::now();
  std::vector<Trade> trades = parseTrades(json.str());
  auto parse_end = std::chrono::high_resolution_clock::now();

  //Print the parsed trades
  std::cout << "[\n";
  for (const auto& trade : trades) {
    std::cout 
      << "\t{\n\t\ta:" << trade.a << ",\n"
      << "\t\tp: " << trade.p << ",\n"
      << "\t\tq: " << trade.q << ",\n"
      << "\t\tf: " << trade.f << ",\n"
      << "\t\tl: " << trade.l << ",\n"
      << "\t\tT: " << trade.T << ",\n"
      << "\t\tm: " << trade.m.c_str() << "\n\t}" << std::endl;
  }
  std::cout << "]";
  
  std::cout << "\nParsing took:" <<
    std::chrono::duration_cast<std::chrono::milliseconds>(parse_end - parse_begin).count() << " ms\n";

  return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{

  if (runFirstExercise() != EXIT_SUCCESS)
    return EXIT_FAILURE;
  if (runSecondExercise() != EXIT_SUCCESS)
    return EXIT_FAILURE;

  std::cout << "Successfuly finished both assignments, closing the program with error code 0";
  return EXIT_SUCCESS;
}
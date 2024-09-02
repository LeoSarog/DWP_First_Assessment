#include "GutenbergDataset.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>

std::string keepOnlyWords(
  std::string& _word)
{
  std::string result;
  for (char c : _word) {
    if (std::isalpha(static_cast<unsigned char>(c))) {
      result += c;  // Keep only letters
    }
  }
  return result;
}

// Avoided extra symbols as the dataset is made mostly by words (at least to make sense).
std::vector<std::string> readWords(
  const std::string& _filename)
{
  std::ifstream file(_filename);
  std::vector<std::string> words;
  std::string word;

  if (file.is_open()) {
    while (file >> word) {
      word = keepOnlyWords(word); // Remove punctuation
      if (!word.empty()) {
        words.push_back(word);
      }
    }
    file.close();
  }
  else {
    std::cerr << "Unable to open file!" << std::endl;
  }

  return words;
}

//It was not necessary from the assessment but I just thought to automatically generate random datasets from the .txt
std::vector<std::string> getRandomWords(
  std::vector<std::string>& _words_container, 
  size_t _words_count)
{

  std::vector<std::string> random_words = _words_container;
  std::srand(static_cast<unsigned int>(std::time(0))); // Seed for randomness
  std::mt19937 rng(std::random_device{}());
  std::shuffle(random_words.begin(), random_words.end(), rng); // Shuffle words

  // Select the first 'numWords' words from the shuffled list
  if (_words_count > random_words.size()) {
    _words_count = random_words.size(); // Adjust if requested number is more than available words
  }

  return std::vector<std::string>(random_words.begin(), random_words.begin() + _words_count);
}

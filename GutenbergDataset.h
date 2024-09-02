#pragma once
#include <string>
#include <vector>

std::string keepOnlyWords(
  std::string& _word);

std::vector<std::string> readWords(
  const std::string& _filename);

std::vector<std::string> getRandomWords(
  std::vector<std::string>& _words_container,
  size_t _words_count);
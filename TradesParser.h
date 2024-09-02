#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

struct Trade {
  long long a; // Aggregate tradeId
  double p;    // Price
  double q;    // Quantity
  long long f; // First tradeId 
  long long l; // Last tradeId
  long long T; // Timestamp
  std::string m;// Was the buyer the maker?
};

//Use of scanf to parse efficiently the raw json/data format.
/*
Caveat, sscanf is fast but does not support directly the bool values. 
We need to parse though at least 5 characters since std::max{length("true"),length("false")} = 5.
So when we parse and we have a "true" value in the json, since we are scanning 5 chars so we get the "true}" token.
This is why I have the following workaround in order to handle the extra "}" and not forward it to our parsed data array.

Note: this approach can also work if the m key was not the last key in each element as we would then get an extra "," 
instead of a "}" and we could pop it in the same exact way.
*/

std::vector<Trade> parseTrades(
  const std::string& _data) {
  std::vector<Trade> trades;
  std::string cleaned_data = _data.substr(1, _data.size() - 2); // Remove the outer brackets
  std::istringstream ss(cleaned_data);
  std::string line;

  while (std::getline(ss, line, '{')) {
    if (line.find('}') == std::string::npos) continue;
    line = line.substr(0, line.find('}') + 1); // Extract the JSON object
    Trade t;
    char temp_buyer_value[6];
    std::sscanf(
      line.c_str(), 
      "\"a\":%lld,\"p\":\"%lf\",\"q\":\"%lf\",\"f\":%lld,\"l\":%lld,\"T\":%lld,\"m\":%5s",
      &t.a, &t.p, &t.q, &t.f, &t.l, &t.T, &temp_buyer_value);
    if (strcmp(temp_buyer_value, "true}") == 0)
    {
      t.m = "true";
    }
    else
    {
      strcpy(t.m.data(), temp_buyer_value);
    }
    trades.push_back(t);
  }

  return trades;
}

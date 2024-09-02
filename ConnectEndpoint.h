#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <map>

#include <curl_easy.h>
#include <curl_form.h>
#include <curl_ios.h>
#include <curl_exception.h>

// This functions wraps a curl request based on a url. 
std::stringstream getResponseFromEndpoint(
  std::string_view _url)
{
  std::stringstream str;
  // This cpp api is actually wrapping the original curl c library in order to
  // Link of the library https://github.com/JosephP91/curlcpp
  curl::curl_ios<std::stringstream> writer(str);

  curl::curl_easy easy(writer);

  easy.add<CURLOPT_URL>(_url.data());
  easy.add<CURLOPT_FOLLOWLOCATION>(1L);
  try
  {
    easy.perform();
  }
  catch (curl::curl_easy_exception error)
  {
    // In case we trigger an error like wrong symbol e.t.c.
    auto errors = error.get_traceback();
    error.print_traceback();
  }

  return str;
}
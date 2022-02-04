// Design and build a "least recently used" cache, which evicts the least
// recently used item. The cache should map from keys to values (allowing you
// to insert and retrieve a value associated with a particular key) and be
// initialized with a max size. When it is full, it should evict the least
// recently used item.

#include <iostream>
#include <string>
#include <thread>



template<typename Key, typename Value>
Value workHard(const Key &request) 
{
  std::this_thread::sleep_for(std::chrono::seconds(3));
  return Value(request);
}

template<>
std::string workHard(const std::string &request) 
{
  static const std::string request_suffix("request");
  static const std::string response_suffix("response");
  std::this_thread::sleep_for(std::chrono::seconds(3));
  size_t request_body_length = request.size() - request_suffix.size(); 
  return request.substr(0, request_body_length) + response_suffix;
}

template<>
std::string workHard(const int& request)
{
  static const std::string response_pref("response ");
   std::this_thread::sleep_for(std::chrono::seconds(3));
  return response_pref + std::to_string(request);
}

template<typename Key, typename Value>
Value getResponse(const Key &request) 
{
  Value response = workHard<Key, Value>(request);
  return response;
}

int main(int argc, char *argv[])
{
      int request = 1;
      std::string response = getResponse<int, std::string>(request); //slow
      response = getResponse<int, std::string>(request); //fast
    	
      request = 2;
      response = getResponse<int, std::string>(request); //slow
      response = getResponse<int, std::string>(request); //fast
    	
      request = 1;
      response = getResponse<int, std::string>(request); //fast
    
      request = 3;
      response = getResponse<int, std::string>(request); //slow
      response = getResponse<int, std::string>(request); //fast
      
      request = 1;
      response = getResponse<int, std::string>(request); //fast
      
      request = 2;
      response = getResponse<int, std::string>(request); //slow

      return 0;
}

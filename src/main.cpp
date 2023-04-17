#include <cpr/cpr.h>
#include <iostream>
std::string API_TOKEN = "de54168c811d44c2bb913ce59210ab28";

std::string json_extract(std::string str, std::string key)
{
  std::string content = "";
  std::string json = str;
  int i = json.find(key);
  // std::cout << i;
  for (i = i; json[i] != ':'; i++)
  {
    continue;
  }
  for (i = i; json[i] != '\"'; i++)
  {
    continue;
  }
  for (i++; json[i] != '\"'; i++)
  {
    content += json[i];
  }
  return content;
}
int main()
{
  // upload a file to google.com
  auto request = cpr::Post(
      cpr::Url{"https://api.assemblyai.com/v2/transcript"},
      cpr::Body{"{\"audio_url\": \"https://bit.ly/3yxKEIY\"}"},
      cpr::Header{{"authorization", API_TOKEN}});

  std::cout << json_extract(request.text, "id") << std::endl;


  while (1)
  {
    auto poll = cpr::Get(
        cpr::Url{"https://api.assemblyai.com/v2/transcript/" + json_extract(request.text, "id")},
        cpr::Header{{"authorization", API_TOKEN}},
        cpr::AcceptEncoding{{"deflate", "gzip", "zlib"}});
    std::cout << json_extract(poll.text, "status") << std::endl;
    if(json_extract(poll.text, "status")=="completed"){
      std::cout << json_extract(poll.text, "text");
      break;
    }
  }
}


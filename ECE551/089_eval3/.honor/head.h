#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <cstdio>
#include <string>
class Choice{
    std::string next_page;
    std::string text;
    int rank;
  public:
 Choice(std::string number, std::string expression, int in_rank):next_page(number), text(expression),rank(in_rank){}
    friend std::ostream & operator <<(std::ostream & s, const Choice & p);
  };
class Page{
  std::string page_name;
  std::vector<Choice> sentence;
  std::vector<std::string> text;
  int status;
public:
  Page(const char * filename):page_name(filename), status(-1) {
    std::ifstream f(filename);
    // check if I can open the file
    if(!f.is_open()){
      throw std::invalid_argument("The file's name is invalid.\n");
    }
    std::string cur;
    int n = 1;
    while(getline(f, cur)){
      if(cur[0] == '#'){
	break;
      }
      if(cur == "WIN"){
	status = 1;
	continue;
      }
      if(cur == "LOSE"){
	status = 2;
	continue;
      }
      status = 0;
      std::string::size_type pos = cur.find_first_of(":");
      if(pos == std::string::npos){
	throw std::invalid_argument("The input is invalid.\n");
      }
      Choice temp(cur.substr(0,pos), cur.substr(pos+1), n++);
      sentence.push_back(temp);
    }
    if(status == -1){
      throw std::invalid_argument("The input is invalid.\n");
    }
    while(getline(f,cur)){
      text.push_back(cur);
    }
  }
  friend std::ostream & operator <<(std::ostream & s, const Page & p);  
};
template <typename T>
std::ostream & operator <<(std::ostream & s, const std::vector<T>& v){
  typename std::vector<T>::const_iterator it = v.begin();
  while(it != v.end()){
    s<<*it<<std::endl;
    ++it;
  }
  return s;
}
std::ostream & operator <<(std::ostream & s, const Choice & c){
  s<<" "<<c.rank<<". "<<c.text;
  return s;
}
std::ostream & operator <<(std::ostream & s, const Page & p){
  s<<p.text<<std::endl;
  if(p.status == 0){
    s<<"What would you like to do?"<<std::endl<<std::endl;
    s<<p.sentence;
  }
  else if(p.status == 1){
    s<<"Congratulations! You have won. Hooray!\n";
  }
  else if(p.status == 2){
    s<<"Sorry, you have lost. Better luck next time!\n";
  }
  return s;
}

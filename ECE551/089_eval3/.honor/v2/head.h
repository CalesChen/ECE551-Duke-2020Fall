#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <cstdio>
#include <string>
#include <sstream>
class Choice{
  //std::string next_page;
    int next_page;
    std::string text;
    int rank;
  public:
  Choice(int number, std::string expression, int in_rank):next_page(number), text(expression),rank(in_rank){}
    int getNext_page() const {return this->next_page;}
    friend std::ostream & operator <<(std::ostream & s, const Choice & p);
    // As I need to check the Whether the choice is valid, so declare the Pages as friend.
    friend class Pages;
  };
class FilenameException: public std::exception{};
class Page{
 protected:
  std::string page_name;
  std::vector<Choice> sentence;
  std::vector<std::string> text;
  int status;
  int n; //This will record the number of choice
public:
  
  Page(const char * filename):page_name(filename), status(-1), n(0) {
    std::ifstream f(filename);
    // check if I can open the file
    if(!f.is_open()){
      throw FilenameException();
    }
    std::string cur;
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

      //std::string temp_int = cur.substr(0,pos);
      int int_str = check_convert(cur.substr(0,pos));
      std::string expre = cur.substr(pos+1);
      n+=1;
      Choice temp(int_str, expre.c_str(), n);
      //Choice temp(cur.substr(0,pos), cur.substr(pos+1), n);
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
  int check_convert(std::string cur){
      int temp_int = atoi(cur.c_str());
      if(temp_int <= 0){
	throw std::invalid_argument("The choice number is invalid.\n");
      }
      //std::stringstream ss;
      //ss << temp_int;
      //std::string res;
      //ss >> res;
      std::vector<Choice>::iterator it = sentence.begin();
      while(it != sentence.end()){
	if(it->getNext_page() == temp_int){
	  throw std::invalid_argument("There is the same number of destination page.\n");
	}
	else{++it;}
      }
      return temp_int;
  }
  friend class Pages;
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
// The Following is related to the cyoa-step2
class PagenumException : public std::exception{};
class NoRefException:public std::exception{};
class NoEndPageException:public std::exception{};
class Pages{
  std::vector <Page> contexts;
  int size;
  std::string dir;
 public:
 Pages(char * dirname):size(1){
    std::string temp(dirname);
    dir = temp + "/page";
    //delete &temp;
    std::string first_name = dir + "1.txt";
    const char * ffn = first_name.c_str();
    Page page1(ffn);
    contexts.push_back(page1);
    bool status = true;
    size += 1;
    std::stringstream s;
    while(status){
      try{
	s.clear();
	s<<dir;
	s<<size;
	s<<".txt";
	std::string temp;
	s>>temp;
	//std::string file_path = dir + temp;
	Page page_temp(temp.c_str());
	contexts.push_back(page_temp);
	size += 1;
      }
      catch(FilenameException & e){
	status = false;
      }
    }
    size -= 1;
  }
  void Check_func(){
    // Check If The pages is all valid and have a reference and there is at lest one win and one lose
    int* check = new int[size]();
    bool status_win = false;
    bool status_lose = false;
    std::vector<Page>::iterator it = contexts.begin();
    while(it != contexts.end()){
      std::vector<Choice>::iterator it_c = it->sentence.begin();
      // Check the 4b, which will check the choice valiation
      while(it_c != it->sentence.end()){
        std::stringstream ss;
        ss<<it_c->next_page;
        int pagenum;
	ss >> pagenum;
        if(pagenum > size){
	  throw PagenumException();
	}
	check[pagenum-1] += 1;
	++it_c;
      }
      // Check the win or lose page
      if(it->status == 1){
	status_win = true;
      }
      if(it->status == 2){
	status_lose = true;
      }
      ++it;
    }

    // Check the check array to see if there is any page have no refrence

    for(int i = 1; i < size; ++i){
      if(check[i] == 0){
	std::cerr <<(i+1)<<"th page has no refrence.\n";
	throw NoRefException();
      }
    }
    // Check the win and lose page
    if(!(status_lose && status_win)){throw NoEndPageException();}
  }
  void play(){
    //symbol mark the end of the program
    bool end = false;
    int next = 0;
    while(!end){
      std::cout<<contexts[next];
      int input;
      std::cin>>input;
      bool choice_vali = (input > contexts[next].n);
      while(std::cin.fail() || choice_vali){
	std::cout<<"That is not a valid choice, please try again."<<std::endl;
	std::cin.clear();
	std::cin.ignore(1024,'\n');
	std::cin>>input;
	choice_vali = (input > contexts[next].n);
      }
      int np;
      std::stringstream ss;
      ss << contexts[next].sentence[input-1].getNext_page();
      ss >> np;
      if(contexts[np-1].status != 0){
	end = true;
      }
      next = np-1;
    }
    std::cout<<contexts[next];
  }
};


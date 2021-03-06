#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>


//YOUR CODE GOES HERE!
template <typename T>
class Matrix
{
private:
    int numRows;
    int numColumns;
    std::vector<std::vector<T> > data;
public:
    Matrix(): numRows(0), numColumns(0), data(0){}
    Matrix(int r, int c ) : numRows(r), numColumns(c), data(r){
        typename std::vector<std::vector<T> > :: iterator it = data.begin();
        while(it != data.end()){
            it->resize(c);
            ++it;
        }
    }
    Matrix(const Matrix<T> & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns),data(rhs.data){}
    
   // ~Matrix(){};
    Matrix<T> & operator=(const Matrix<T> & rhs){
        if(this != &rhs){
            numRows = rhs.numRows;
	    numColumns = rhs.numColumns;
	    data = rhs.data;
        }
        return * this;
    }
    int getRows() const{
        return numRows;
    }
    int getColumns() const{
        return numColumns;
    }
    const std::vector<T> & operator[](int index) const{
        assert(0 <= index && index < numRows);
        return data[index];
    }
    std::vector<T> & operator[](int index){
        assert(0 <= index && index < numRows);
        return data[index];
    }
    bool operator==(const Matrix<T> & rhs) const{
        if(this == &rhs){
            return true;
        }
        if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
            return false;
        }
        return data == rhs.data;
    }
    Matrix<T> operator+(const Matrix<T> & rhs) const {
        assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
        Matrix<T> ans(*this);
        typename std::vector<std::vector<T> > :: iterator it_out = ans.data.begin();
        typename std::vector<std::vector<T> > :: const_iterator it_rhs = rhs.data.begin();
        while(it_out != ans.data.end()){
            typename std::vector<T> :: iterator it_in = it_out->begin();
            typename std::vector<T> :: const_iterator it_in_rhs = it_rhs->begin();
            while(it_in != it_out->end()){
                *it_in += *it_in_rhs;
                ++it_in_rhs;
                ++it_in;
            }
            ++it_out;
            ++it_rhs;
        }
        return ans;
    }
  template <typename O>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<O> & rhs);
};

template <typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  typename std::vector<std::vector<T> > :: const_iterator it = rhs.data.begin();
  while(it != rhs.data.end()){
      if(it != rhs.data.begin()){
          s << ",\n{";
      }
      else {
          s << "{";
      }
      typename std::vector<T> :: const_iterator it_in = it->begin();
      while(it_in != it->end()){
          if(it_in != it->begin()){
              s << ", ";
          }
          s<<*it_in;
          ++it_in;
      }
      s << "}";
      ++it;
  }
  s << " ]";
  return s;
}
#endif
/*template<typename Y>
std::ostream & operator<<(std::ostream & s, const std::vector<Y> & v) {
  s << "[";
  for (size_t i = 0; i < v.size(); i++) {
    if (i > 0) {
      s << ", ";
    }
    s << v[i];
  }
  s << "]";
  return s;
}*/

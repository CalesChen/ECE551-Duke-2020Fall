#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(*rhs.rows[i]);
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(*rhs.rows[i]);
    }
    for (int i = 0; i < numRows; i++) {
      delete[] rows[i];
    }
    delete rows;
    rows = temp;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(0 <= index && index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(0 <= index && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (this == &rhs) {
    return true;
  }
  if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if (*rows[i] != *rhs.rows[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix ans(*this);
  for (int i = 0; i < ans.numRows; i++) {
    for (int j = 0; j < ans.numColumns; j++) {
      //(*ans.rows[i])[j] = (*ans.rows[i])[j] + (*rhs.rows[i])[j];
      ans[i][j] += rhs[i][j];
    }
  }
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << " [";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i < (rhs.getRows() - 1)) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}

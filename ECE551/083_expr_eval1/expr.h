#include <stdio.h>
#include <string.h>

#include <sstream>
#include <string>

class Expression {
 public:
  virtual std ::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  long number;

 public:
  NumExpression(long num) : number(num) {}
  virtual std ::string toString() const {
    std ::stringstream str;
    str << number;
    return str.str();
  }
};
class OpExpression : public Expression {
  const char operation;
  Expression * lhs;
  Expression * rhs;

 public:
  OpExpression(char operation_in, Expression * lhs_in, Expression * rhs_in) :
      operation(operation_in),
      lhs(lhs_in),
      rhs(rhs_in) {}
  virtual std ::string toString() const {
    std ::stringstream str;
    str << "(";
    str << lhs->toString();
    str << " ";
    str << operation;
    str << " ";
    str << rhs->toString();
    str << ")";
    return str.str();
  }
  virtual ~OpExpression() {
    delete lhs;
    delete rhs;
  }
};
class PlusExpression : public OpExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression('+', lhs, rhs) {}
};

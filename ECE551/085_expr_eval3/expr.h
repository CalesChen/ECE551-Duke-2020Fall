#include <string>
#include <string.h>
#include <stdio.h>
#include <sstream>

class Expression{
    public:
        virtual std :: string toString() const = 0; 
        virtual long evaluate() const = 0;
        virtual ~Expression(){}
};

class NumExpression : public Expression{
    long number;
    public:
        NumExpression(long num): number(num){}
        virtual std :: string toString() const {
            std :: stringstream str ;
            str << number;
            return str.str();
        }
        virtual long evaluate() const{
            return number;
        }
};
class OpExpression : public Expression{
    protected:
    const char operation;
    Expression *lhs;
    Expression *rhs;
    public:
    OpExpression(char operation_in, Expression * lhs_in, Expression * rhs_in): operation(operation_in),lhs(lhs_in),rhs(rhs_in) {}
    virtual std :: string toString() const {
            std :: stringstream str ;
            str << "(";
            str << lhs->toString() ;
            str << " ";
            str << operation;
            str << " ";
            str << rhs->toString() ;
            str << ")";
            return str.str();
    }
    virtual ~OpExpression(){
        delete lhs;
        delete rhs;
    }
};
class PlusExpression : public OpExpression {
    public:
    PlusExpression(Expression * lhs_in, Expression * rhs_in): OpExpression('+', lhs_in, rhs_in){}
    virtual long evaluate() const{
        return lhs->evaluate() + rhs->evaluate();
    }
};
class MinusExpression : public OpExpression {
    public:
    MinusExpression(Expression * lhs, Expression * rhs): OpExpression('-', lhs, rhs){}
    virtual long evaluate() const{
        return lhs->evaluate() - rhs->evaluate();
    }
};
class TimesExpression : public OpExpression {
    public:
    TimesExpression(Expression * lhs, Expression * rhs): OpExpression('*', lhs, rhs){}
    virtual long evaluate() const{
        return lhs->evaluate() * rhs->evaluate();
    }
};
class DivExpression : public OpExpression {
    public:
    DivExpression(Expression * lhs, Expression * rhs): OpExpression('/', lhs, rhs){}
    virtual long evaluate() const{
        return lhs->evaluate() / rhs->evaluate();
    }
};
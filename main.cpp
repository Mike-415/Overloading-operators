#include <iostream>
#include <cassert>
#include <stdexcept>
#include <string>
using namespace std;

class Fraction {
public:
    Fraction( int inNumerator = 0, int inDenominator = 1);
    enum RelationalOperators{
        LESS_THAN, GREATER_THAN, LESS_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL, EQUAL, NOT_EQUAL
    };
    enum ArithmeticOperators{
        ADD, SUBTRACT
    };
    friend std::ostream& operator<<(std::ostream& leftOS, const Fraction& rightOperand);
    friend bool operator<(const Fraction& leftOperand, const Fraction& rightOperand);
    friend bool operator>(const Fraction& leftOperand, const Fraction& rightOperand);
    friend bool operator<=(const Fraction& leftOperand, const Fraction& rightOperand);
    friend bool operator>=(const Fraction& leftOperand, const Fraction& rightOperand);
    friend bool operator!=(const Fraction& leftOperand, const Fraction& rightOperand);
    friend bool operator==(const Fraction& leftOperand, const Fraction& rightOperand);

    friend Fraction operator+(const Fraction& leftOperand, const Fraction& rightOperand);
    friend Fraction operator-(const Fraction& leftOperand, const Fraction& rightOperand);
    friend Fraction operator*(const Fraction& leftOperand, const Fraction& rightOperand);
    friend Fraction operator/(const Fraction& leftOperand, const Fraction& rightOperand);

    Fraction operator+=(const Fraction& rightOperand);
    Fraction operator-=(const Fraction& rightOperand);
    Fraction operator*=(const Fraction& rightOperand);
    Fraction operator/=(const Fraction& rightOperand);

    Fraction operator++();
    Fraction operator++(int);
    Fraction operator--();
    Fraction operator--(int);
private:
    int numerator;
    int denominator;
    friend bool compareFractions(const Fraction& leftOperand, const Fraction& rightOperand, RelationalOperators type);
    friend Fraction addOrSubtract(const Fraction& leftOperand, const Fraction& rightOperand, ArithmeticOperators type);
    void simplify(Fraction& original);
};







Fraction::Fraction( int inNumerator, int inDenominator){
    assert(inDenominator != 0);
    numerator = inNumerator;
    denominator = inDenominator;
    simplify(*this);
}






std::ostream& operator<<(std::ostream& leftOutput, const Fraction& rightOperand) {
    leftOutput << rightOperand.numerator << "/" << rightOperand.denominator;
    return leftOutput;
}






bool compareFractions(const Fraction& leftOperand, const Fraction& rightOperand, Fraction::RelationalOperators type){
    int leftProduct = leftOperand.numerator * rightOperand.denominator;
    int rightProduct = leftOperand.denominator * rightOperand.numerator;
    switch(type){
        case Fraction::LESS_THAN:
            return leftProduct < rightProduct;
        case Fraction::GREATER_THAN:
            return leftProduct > rightProduct;
        case Fraction::LESS_THAN_OR_EQUAL:
            return leftProduct <= rightProduct;
        case Fraction::GREATER_THAN_OR_EQUAL:
            return  leftProduct >= rightProduct;
        case Fraction::EQUAL:
            return leftProduct == rightProduct;
        case Fraction::NOT_EQUAL:
            return leftProduct != rightProduct;
    }
}






bool operator<(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::LESS_THAN);
}






bool operator>(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::GREATER_THAN);
}






bool operator<=(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::LESS_THAN_OR_EQUAL);
}






bool operator>=(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::GREATER_THAN_OR_EQUAL);
}






bool operator!=(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::NOT_EQUAL);
}






bool operator==(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::EQUAL);
}






Fraction addOrSubtract(const Fraction& leftOperand, const Fraction& rightOperand, Fraction::ArithmeticOperators type){
    int leftNumerator = (leftOperand.numerator * rightOperand.denominator);
    int rightNumerator = (rightOperand.numerator * leftOperand.denominator);
    int newNumerator;
    switch(type){
        case Fraction::ADD:
            newNumerator = leftNumerator + rightNumerator;
            break;
        case Fraction::SUBTRACT:
            newNumerator = leftNumerator - rightNumerator;
            break;
        default:
            throw std::invalid_argument("Invalid arithmetic operator type");
    }
    int newDenominator = leftOperand.denominator * rightOperand.denominator;
    Fraction sum(newNumerator, newDenominator);
    return sum;
}




Fraction operator+(const Fraction& leftOperand, const Fraction& rightOperand){
    return addOrSubtract(leftOperand, rightOperand, Fraction::ADD);
}






Fraction operator-(const Fraction& leftOperand, const Fraction& rightOperand){
    return addOrSubtract(leftOperand, rightOperand, Fraction::SUBTRACT);
}






Fraction operator*(const Fraction& leftOperand, const Fraction& rightOperand){
    int newNumerator = leftOperand.numerator * rightOperand.numerator;
    int newDenominator = leftOperand.denominator * rightOperand.denominator;
    Fraction product(newNumerator, newDenominator);
    return product;
}






Fraction operator/(const Fraction& leftOperand, const Fraction& rightOperand){
    int newNumerator = leftOperand.numerator * rightOperand.denominator;
    int newDenominator = leftOperand.denominator * rightOperand.numerator;
    Fraction quotient(newNumerator, newDenominator);
    return quotient;
}






Fraction Fraction::operator+=(const Fraction& rightOperand){

    *this = *this + rightOperand;
    return *this;
}






Fraction Fraction::operator-=(const Fraction& rightOperand){

    *this = *this - rightOperand;
    return *this;
}






Fraction Fraction::operator*=(const Fraction& rightOperand){

    *this = *this * rightOperand;
    return *this;
}






Fraction Fraction::operator/=(const Fraction& rightOperand){

    *this = *this / rightOperand;
    return *this;
}







Fraction Fraction::operator++(){
    Fraction one(1);
    *this =  addOrSubtract(*this, one, Fraction::ADD);
    return *this;
}






Fraction Fraction::operator++(int){
    Fraction temp(numerator, denominator), one(1), incrementedFraction;
    incrementedFraction = addOrSubtract(*this, one, Fraction::ADD);
    denominator = incrementedFraction.denominator;
    numerator = incrementedFraction.numerator;
    return temp;
}







Fraction Fraction::operator--(){
    Fraction one(1,1);
    *this = addOrSubtract(*this, one, Fraction::SUBTRACT);
    return *this;
}






Fraction Fraction::operator--(int){
    Fraction temp(numerator, denominator), one(1) , decrementedFraction;
    decrementedFraction = addOrSubtract(*this, one, Fraction::SUBTRACT);
    denominator = decrementedFraction.denominator;
    numerator = decrementedFraction.numerator;
    return temp;
}






/*
void fraction::simplify() {
    bool isNegative = fractionNegative();
    int absNumerator = abs(numerator);
    int smallestNum = (absNumerator < denominator)? absNumerator : denominator;
    while( smallestNum > 1 ){
        if(absNumerator % smallestNum == 0 &&
           denominator  % smallestNum == 0){
            absNumerator /= smallestNum;
            denominator /= smallestNum;
        }
        smallestNum--;
    }
    numerator = (isNegative)? absNumerator * -1 : absNumerator;
}
 */

//Assume that ONLY the numerator could be negative
void Fraction::simplify(Fraction& original){
    int absNumerator = std::abs(original.numerator);
    int smallestNum = (absNumerator < original.denominator)? absNumerator : original.denominator;
    while( smallestNum > 1 ){
        if(absNumerator % smallestNum == 0 &&
           original.denominator  % smallestNum == 0){
            original.numerator /= smallestNum;
            original.denominator /= smallestNum;
        }
        smallestNum--;
    }
}








int main()
{
    Fraction f1(-9,3);
    Fraction f2(5, 45);
    cout << f1 << endl;
    cout << f2 << endl;
}



/*
OUTPUT:



 */
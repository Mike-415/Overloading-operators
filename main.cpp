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
    friend std::istream& operator>>(std::istream& leftIS, Fraction& rightOperand);
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
    void simplify(Fraction& fraction);
};







Fraction::Fraction( int inNumerator, int inDenominator){
    assert(inDenominator != 0);
    numerator = inNumerator;
    denominator = inDenominator;
    simplify(*this);
}






/*
Now modify your overloaded << operator so that improper Fractions
are printed as mixed numbers. Whole numbers should print without a denominator
(e.g. not 3/1 but just 3).

Improper Fractions should be printed as a mixed number with a + sign
between the two parts (2+1/2). Negative Fractions should be printed
with a leading minus sign.



 */
std::ostream& operator<<(std::ostream& leftOutput, const Fraction& rightOperand) {
    if(abs(rightOperand.numerator) > rightOperand.denominator){
        leftOutput << rightOperand.numerator / rightOperand.denominator;
        if(rightOperand.numerator % rightOperand.denominator != 0){
            leftOutput << "+" << abs(rightOperand.numerator % rightOperand.denominator);
            leftOutput << "/" << rightOperand.denominator;
        }
    } else {
        leftOutput << rightOperand.numerator << "/" << rightOperand.denominator;
    }
    return leftOutput;
}







/*
This operator must read exactly one fraction value from input.
You should be able to read any of the formats described above
(mixed number, negative number, whole numbers, etc.).
You may assume that there are no spaces or formatting errors
in the Fractions that you read. This means, for example,
that in a mixed number only the whole number
(not the numerator or denominator) may be negative, and that
in a fraction with no whole number part only the numerator
(not the denominator) may be negative.

Note: You may need to exceed 15 lines for this function.
My solution is about 20 lines long.

Extraction Operator Hints:

Since your extraction operator should not consume anything
after the end of the Fraction being read, you will probably want to use
the .peek() function to look ahead in the input stream and see what
the next character is after the first number is read.
If it's not either a '/'' or a '+', then you are done reading
and should read no further. I have something like this:

    int temp;
    in >> temp;
    if (in.peek() == '+'){
        doSomething...
    } else if (in.peek() == '/'){
        doSomethingElse...
    } else {
        doThirdOption
    }
You don't need to detect or read the minus operator as a separate character.
When you use the extraction operator to read an int, it will interpret a
leading minus sign correctly. So, for example, you shouldn't have
"if (in.peek() == '-')"

The peek() function does not consume the character from the input stream,
so after you use it to detect what the next character is,
the first thing you need to do is get past that character.
One good way to do that would be to use in.ignore(),
which ignores one single character in the input stream.

Here is one example of how processing will work:
if the fraction in the input stream is a mixed number,
you will need to have at least three input operations
so that you can read all three integers in the mixed number.

You can model the syntax of your operator>>() function header
after the operator<<() function syntax you have seen in examples.
Just use istream in the place of ostream
(since we are doing input instead of output).
Also, keep in mind that the right operand will NOT
be const since the extraction operator's purpose
is to modify the right operand.

 */


std::istream& operator>>(std::istream& leftIS, Fraction& rightOperand){
    int firstPortion, secondPortion, thirdPortion;
    leftIS >> firstPortion;
    cout << "firstPortion: " << firstPortion << endl;
    if (leftIS.peek() == '+'){
        leftIS.ignore();
        leftIS >> secondPortion; //Numerator
        leftIS.ignore();
        leftIS >> thirdPortion;  //Denominator
        cout << "secondPortion: " << secondPortion << endl;
        cout << "thirdPortion: " << thirdPortion << endl;

        firstPortion = thirdPortion * firstPortion;
        firstPortion += (firstPortion > 0)? secondPortion : -secondPortion;
        secondPortion = thirdPortion;
        //doSomething...
    } else if (leftIS.peek() == '/'){
        //doSomethingElse...
        leftIS.ignore();
        leftIS >> secondPortion;
    } else {
        //doThirdOption
        secondPortion = 1;
    }
    Fraction temp(firstPortion, secondPortion);
    cout << "temp: " << temp.numerator << "/" << temp.denominator << endl;
    rightOperand = temp;
    return leftIS;
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
    }
    int newDenominator = leftOperand.denominator * rightOperand.denominator;
    Fraction result(newNumerator, newDenominator);
    return result;
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







void Fraction::simplify(Fraction& fraction){
    int absNumerator = std::abs(fraction.numerator);
    int smallestValue = (absNumerator < fraction.denominator)? absNumerator : fraction.denominator;
    while( smallestValue > 1 ){
        if(absNumerator % smallestValue == 0 &&
           fraction.denominator  % smallestValue == 0){
            fraction.numerator /= smallestValue;
            fraction.denominator /= smallestValue;
        }
        smallestValue--;
    }
}






//You need to figure out a way to solve the >> operator problem
//1. Review the readings to see what's different in the function signature
//2. Look at the rubric so you can use the pre-defined if/else statement









int main()
{
    Fraction f1(-9,3);
    Fraction f2(-95, 45);
    Fraction f3;
    cout << f1 << endl;
    cout << f2 << endl;
    cin >> f3;
    cout << "main: f3 = " << f3 << endl;

}



/*
OUTPUT:



 */
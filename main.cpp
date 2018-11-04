#include <iostream>
#include <cassert>
#include <stdexcept>



class Fraction {
public:
    Fraction( int inNumerator = 0, int inDenominator = 1);
    enum RelationalOperators{
        LESS_THAN, GREATER_THAN, LESS_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL, EQUAL, NOT_EQUAL
    };
    enum ArithmeticOperators{
        ADD, SUBTRACT;
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
private:
    int numerator;
    int denominator;
    friend bool compareFractions(const Fraction& leftOperand, const Fraction& rightOperand, RelationalOperators type);
    friend Fraction addOrSubtract(const Fraction& leftOperand, const Fraction& rightOperand, ArithmeticOperators type);
};







Fraction::Fraction( int inNumerator, int inDenominator){
    assert(inDenominator != 0);
    numerator = inNumerator;
    denominator = inDenominator;
}






std::ostream& operator<<(std::ostream& leftOutput, const Fraction& rightOperand)
{
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




//The four basic arithmetic operations (+, -, *, /)
// should be supported.
// Again, they should allow Fractions to be combined
// with other Fractions, AS WELL AS WITH INTEGERS.
// Either Fractions or integers can appear on either side
// of the binary operator.
//
// Only use one function for each operator.

//Don't go to a lot of trouble to find the common denominator
// (when adding or subtracting).
// Simply multiply the denominators together.
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
    Fraction product(newNumerator, newDenominator);
    return product;
}















int main() {
    Fraction f0;
    Fraction f1(5);
    Fraction f2(3,5);

    std::cout << "f0: " << f0 << std::endl;
    std::cout << "f1: " << f1 << std::endl;
    std::cout << "f2: " << f2 << std::endl;

    std::cout << "5/1 < 3/5: " << (f1 < f2) << std::endl;
    std::cout << "3/5 < 3/5: " << (f2 < f2) << std::endl;
    std::cout << "3/5 < 5/1: " << (f2 < f1) << std::endl << std::endl;

    std::cout << "3/5 > 5/1: " << (f2 > f1) << std::endl;
    std::cout << "3/5 > 3/5: " << (f2 > f2) << std::endl;
    std::cout << "5/1 > 3/5: " << (f1 > f2) << std::endl << std::endl;

    std::cout << "5/1 <= 3/5: " << (f1 <= f2) << std::endl;
    std::cout << "3/5 <= 3/5: " << (f2 <= f2) << std::endl;
    std::cout << "3/5 <= 5/1: " << (f2 <= f1) << std::endl << std::endl;

    std::cout << "3/5 >= 5/1: " << (f2 >= f1) << std::endl;
    std::cout << "3/5 >= 3/5: " << (f2 >= f2) << std::endl;
    std::cout << "5/1 >= 3/5: " << (f1 >= f2) << std::endl << std::endl;

    std::cout << "5/1 != 3/5: " << (f1 != f2) << std::endl;
    std::cout << "3/5 != 3/5: " << (f2 != f2) << std::endl;
    std::cout << "3/5 != 5/1: " << (f2 != f1) << std::endl << std::endl;

    std::cout << "5/1 == 3/5: " << (f1 == f2) << std::endl;
    std::cout << "3/5 == 3/5: " << (f2 == f2) << std::endl;
    std::cout << "3/5 == 5/1: " << (f2 == f1) << std::endl << std::endl;

    return 0;
}

/*

Learning Objectives
After the successful completion of this learning unit, you will be able to:

Define syntactically correct overloaded operators in accordance with good programming practice
Implement friend functions
Assignment 11.1 [45 points]
For this assignment you will be building on your Fraction class. However, the changes will be significant, so I would recommend starting from scratch and using your previous version as a resource when appropriate. You'll continue working on your Fraction class for one more week, next week. For this week you are not required to provide documentation and not required to simplify Fractions.

Please keep all of your code in one file for this week. We will separate things into three files for the next assignment. Your class will go first, then your class member function definitions, then main().

Here are the client program and correct output.

Your class should support the following operations on Fraction objects:

Construction of a Fraction from two, one, or zero integer arguments. If two arguments, they are assumed to be the numerator and denominator, just one is assumed to be a whole number, and zero arguments creates a zero Fraction. Use default parameters so that you only need a single function to implement all three of these constructors.

You should check to make sure that the denominator is not set to 0. The easiest way to do this is to use an assert statement: assert(inDenominator != 0); You can put this statement at the top of your constructor. Note that the variable in the assert() is the incoming parameter, not the data member. In order to use assert(), you must #include <cassert>

For this assignment, you may assume that all Fractions are positive. We'll fix that next week.

Printing a Fraction to a stream with an overloaded << operator. Next week we will get fancy with this, but for now just print the numerator, a forward-slash, and the denominator. No need to change improper Fractions to mixed numbers, and no need to reduce.

All six of the relational operators (<, <=, >, >=, ==, !=) should be supported. They should be able to compare Fractions to other Fractions as well as Fractions to integers. Either Fractions or integers can appear on either side of the binary comparison operator. You should only use one function for each operator.

The four basic arithmetic operations (+, -, *, /) should be supported. Again, they should allow Fractions to be combined with other Fractions, as well as with integers. Either Fractions or integers can appear on either side of the binary operator. Only use one function for each operator.

Note that no special handling is needed to handle the case of dividing by a Fraction that is equal to 0. If the client attempts to do this, they will get a runtime error, which is the same behavior they would expect if they tried to divide by an int or double that was equal to 0.

The shorthand arithmetic assignment operators (+=, -=, *=, /=) should also be implemented. Fractions can appear on the left-hand side, and Fractions or integers on the right-hand side.

The increment and decrement (++, --) operators should be supported in both prefix and postfix form for Fractions. To increment or decrement a Fraction means to add or subtract (respectively) one (1).

Additional Requirements and Hints:
You will not be graded on documentation on this assignment. You'll be working on the documentation next week.
The name of your class must be "Fraction". No variations will work.
Use exactly two data members.
You should not compare two Fractions by dividing the numerator by the denominator. This is not guaranteed to give you the correct result every time, because of the way that double values are stored internally by the computer. I would cross multiply and compare the products.
Don't go to a lot of trouble to find the common denominator (when adding or subtracting). Simply multiply the denominators together.
The last two bullets bring up an interesting issue: if your denominators are really big, multiplying them together (or cross multiplying) may give you a number that is too big to store in an int variable. This is called overflow. The rule for this assignment is: don't worry about overflow in these two situations.
My solution has 20 member functions (including friend functions). All of them are less than 4 lines long. I'm not saying yours has to be like this, but it shouldn't be way off.
Do not use as a resource a supplementary text or website if it includes a Fraction class (or rational or ratio or whatever).
Getting Started
Here are some suggestions for those of you who have trouble just figuring out where to start with assignment 1. Remember to use iterative development. That means start with the smallest, simplest subset of the final product that you can, make sure it works, and then start adding things to it one at a time (preferably the simple things first, if possible).

Start with just a default constructor and a stream insertion operator. For now, don't even worry about mixed numbers, just write the stream insertion operator so that it works with proper fractions. Test this out with a client program something like this:

int main(){
	Fraction f1;

	cout << f1;
}
(You should get output of "0/1" because you should have initialized the fraction to 0/1 in your constructor.)

If you have trouble getting this far, be sure to let me know ASAP so I can help!

 */
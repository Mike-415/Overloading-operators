#include <iostream>
#include <fstream>
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
    void simplify();
    void correction();
    //friend void simplify2(Fraction& fraction);
};







Fraction::Fraction( int inNumerator, int inDenominator){
    assert(inDenominator != 0);
    numerator = inNumerator;
    denominator = inDenominator;
    this->simplify();
}






/*
Now modify your overloaded << operator so that improper Fractions
are printed as mixed numbers. Whole numbers should print without a denominator
(e.g. not 3/1 but just 3).

Improper Fractions should be printed as a mixed number with a + sign
between the two parts (2+1/2). Negative Fractions should be printed
with a leading minus sign.
 */
std::ostream& operator<<(std::ostream& leftOS, const Fraction& rightOperand) {
    //cout << "\n\tog: "<< rightOperand.numerator << "/" << rightOperand.denominator << endl;
    if(abs(rightOperand.numerator) > abs(rightOperand.denominator)) {
        leftOS << rightOperand.numerator / rightOperand.denominator;
        if(rightOperand.numerator % rightOperand.denominator != 0){
            leftOS << "+" << abs(rightOperand.numerator % rightOperand.denominator);
            leftOS << "/" << rightOperand.denominator;
        }
    } else {
        if(rightOperand.denominator == 1){
            leftOS << rightOperand.numerator;
        } else {
            leftOS << rightOperand.numerator << "/" << rightOperand.denominator;
        }

    }
    return leftOS;
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
    //cout << "firstPortion: " << firstPortion << endl;
    if (leftIS.peek() == '+'){
        leftIS.ignore();
        leftIS >> secondPortion; //Numerator
        leftIS.ignore();
        leftIS >> thirdPortion;  //Denominator
        //cout << "secondPortion: " << secondPortion << endl;
        //cout << "thirdPortion: " << thirdPortion << endl;

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
    //cout << "first: " << firstPortion << "second: " << secondPortion << endl;
    Fraction temp(firstPortion, secondPortion);
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
    result.simplify();
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
    Fraction *product = new Fraction(newNumerator, newDenominator);
    product->simplify();
    return *product;
}






Fraction operator/(const Fraction& leftOperand, const Fraction& rightOperand){
    int newNumerator = leftOperand.numerator * rightOperand.denominator;
    int newDenominator = leftOperand.denominator * rightOperand.numerator;
    Fraction *quotient = new Fraction(newNumerator, newDenominator);
    quotient->simplify();
    return *quotient;
}






Fraction Fraction::operator+=(const Fraction& rightOperand){
    *this = *this + rightOperand;
    this->simplify();
    return *this;
}






Fraction Fraction::operator-=(const Fraction& rightOperand){
    *this = *this - rightOperand;
    this->simplify();
    return *this;
}






Fraction Fraction::operator*=(const Fraction& rightOperand){
    *this = *this * rightOperand;
    this->simplify();
    return *this;
}






Fraction Fraction::operator/=(const Fraction& rightOperand){

    *this = *this / rightOperand;
    this->simplify();
    return *this;
}







Fraction Fraction::operator++(){
    Fraction one(1);
    *this =  addOrSubtract(*this, one, Fraction::ADD);
    this->simplify();
    return *this;
}






Fraction Fraction::operator++(int){
    Fraction temp(numerator, denominator), one(1), incrementedFraction;
    incrementedFraction = addOrSubtract(*this, one, Fraction::ADD);
    denominator = incrementedFraction.denominator;
    numerator = incrementedFraction.numerator;
    this->simplify();
    return temp;
}







Fraction Fraction::operator--(){
    Fraction one(1,1);
    *this = addOrSubtract(*this, one, Fraction::SUBTRACT);
    this->simplify();
    return *this;
}






Fraction Fraction::operator--(int){
    Fraction temp(numerator, denominator), one(1) , decrementedFraction;
    decrementedFraction = addOrSubtract(*this, one, Fraction::SUBTRACT);
    denominator = decrementedFraction.denominator;
    numerator = decrementedFraction.numerator;
    this->simplify();
    return temp;
}





//The best way to do this is to make the function a
//void function with no parameters that
// reduces the calling object.

//Your simplify() function should also ensure that
//the denominator is never negative.
//If the denominator is negative,
//fix this by multiplying numerator and denominator by -1.
//Also, if the numerator is 0, the denominator should be set to 1.

void Fraction::simplify(){
    this->correction();
    int smallestValue = ( abs(this->numerator) < abs(this->denominator))? abs(this->numerator) : this->denominator;
    while( smallestValue > 1 && this->numerator != 1 && this->denominator != 1){
        if(abs(this->numerator) % smallestValue == 0 && this->denominator  % smallestValue == 0){
            //cout << "absNum: "  << "fractDen: " << fraction.denominator << "small: " << smallestValue << endl;
            this->numerator /= smallestValue;
            this->denominator /= smallestValue;
            //cout << "num: " << fraction.numerator << " den: " << fraction.denominator << endl;
        }
        smallestValue--;
    }
}






void Fraction::correction(){
    if(this->numerator == 0){
        this->denominator = 1;
    }
    // +/- OR -/-
    if((this->numerator > 0 || this->numerator < 0) && this->denominator < 0){
        this->numerator *= -1;
        this->denominator *= -1;
    }
}
//You need to figure out a way to solve the >> operator problem
//1. Review the readings to see what's different in the function signature
//2. Look at the rubric so you can use the pre-defined if/else statement









//TODO: Test with the code you were given
//TODO: Relearn about namespace
//TODO: Relearn about separating files


void BasicTest();
void RelationTest();
void BinaryMathTest();
void MathAssignTest();
bool eof(ifstream& in);
string boolString(bool convertMe);


//TODO: Reread the rubric about the 'simplify' method
//TODO:
int main()
{
    BasicTest();
    RelationTest();
    BinaryMathTest();
    MathAssignTest();
}





void BasicTest()
{
    cout << "\n----- Testing basic Fraction creation & printing\n";
    cout << "(Fractions should be in reduced form, and as mixed numbers.)\n";

    const Fraction fr[] = {Fraction(4, 8),
                           Fraction(-15,21),
                           Fraction(10),
                           Fraction(12, -3),
                           Fraction(),
                           Fraction(28, 6),
                           Fraction(0, 12)};

    for (int i = 0; i < 7; i++){
        cout << "Fraction [" << i <<"] = " << fr[i] << endl;
    }


    cout << "\n----- Now reading Fractions from file\n";
    ifstream in("Fraction.txt");
    assert(in);
    while (!eof(in)) {
        Fraction f;
        if (in.peek() == '#') {
            in.ignore(128, '\n');                       //skip this line, it's a comment
        } else {
            in >> f;
            cout << "Read Fraction = " << f << endl;
        }
    }
}


bool eof(ifstream& in)
{
    char ch;
    in >> ch;
    in.putback(ch);
    return !in;
}





string boolString(bool convertMe) {
    if (convertMe) {
        return "true";
    } else {
        return "false";
    }
}


void RelationTest()
{
    cout << "\n----- Testing relational operators between Fractions\n";

    const Fraction fr[] =  {Fraction(3, 6), Fraction(1,2), Fraction(-15,30),
                            Fraction(1,10), Fraction(0,1), Fraction(0,2)};

    for (int i = 0; i < 5; i++) {
        cout << "Comparing " << fr[i] << " to " << fr[i+1] << endl;
        cout << "\tIs left < right? " << boolString(fr[i] < fr[i+1]) << endl;
        cout << "\tIs left <= right? " << boolString(fr[i] <= fr[i+1]) << endl;
        cout << "\tIs left > right? " << boolString(fr[i] > fr[i+1]) << endl;
        cout << "\tIs left >= right? " << boolString(fr[i] >= fr[i+1]) << endl;
        cout << "\tDoes left == right? " << boolString(fr[i] == fr[i+1]) << endl;
        cout << "\tDoes left != right ? " << boolString(fr[i] != fr[i+1]) << endl;
    }

    cout << "\n----- Testing relations between Fractions and integers\n";
    Fraction f(-3,6);
    int num = 2;
    cout << "Comparing " << f << " to " << num << endl;
    cout << "\tIs left < right? " << boolString(f < num) << endl;
    cout << "\tIs left <= right? " << boolString(f <= num) << endl;
    cout << "\tIs left > right? " << boolString(f > num) << endl;
    cout << "\tIs left >= right? " << boolString(f >= num) << endl;
    cout << "\tDoes left == right? " << boolString(f == num) << endl;
    cout << "\tDoes left != right ? " << boolString(f != num) << endl;

    Fraction g(1,4);
    num = -3;
    cout << "Comparing " << num << " to " << g << endl;
    cout << "\tIs left < right? " << boolString(num < g) << endl;
    cout << "\tIs left <= right? " << boolString(num <= g) << endl;
    cout << "\tIs left > right? " << boolString(num > g) << endl;
    cout << "\tIs left >= right? " << boolString(num >= g) << endl;
    cout << "\tDoes left == right? " << boolString(num == g) << endl;
    cout << "\tDoes left != right ? " << boolString(num != g) << endl;
}





void BinaryMathTest()
{
    cout << "\n----- Testing binary arithmetic between Fractions\n";

    const Fraction fr[] = {Fraction(1, 6), Fraction(1,3),
                           Fraction(-2,3), Fraction(5), Fraction(-4,3)};

    for (int i = 0; i < 4; i++) {
        cout << fr[i] << " + " << fr[i+1] << " = " << fr[i] + fr[i+1] << endl;
        cout << fr[i] << " - " << fr[i+1] << " = " << fr[i] - fr[i+1] << endl;
        cout << fr[i] << " * " << fr[i+1] << " = " << fr[i] * fr[i+1] << endl;
        cout << fr[i] << " / " << fr[i+1] << " = " << fr[i] / fr[i+1] << endl;
    }

    cout << "\n----- Testing arithmetic between Fractions and integers\n";
    Fraction f(-1, 2);
    int num = 4;
    cout << f << " + " << num << " = " << f + num << endl;
    cout << f << " - " << num << " = " << f - num << endl;
    cout << f << " * " << num << " = " << f * num << endl;
    cout << f << " / " << num << " = " << f / num << endl;

    Fraction g(-1, 2);
    num = 3;
    cout << num << " + " << g << " = " << num + g << endl;
    cout << num << " - " << g << " = " << num - g << endl;
    cout << num << " * " << g << " = " << num * g << endl;
    cout << num << " / " << g << " = " << num / g << endl;
}






void MathAssignTest()
{
    cout << "\n----- Testing shorthand arithmetic assignment on Fractions\n";

    Fraction fr[] = {Fraction(1, 6), Fraction(4),
                     Fraction(-1,2), Fraction(5)};

    for (int i = 0; i < 3; i++) {
        cout << fr[i] << " += " << fr[i+1] << " = ";
        cout << (fr[i] += fr[i+1]) << endl;
        cout << fr[i] << " -= " << fr[i+1] << " = ";
        cout << (fr[i] -= fr[i+1]) << endl;
        cout << fr[i] << " *= " << fr[i+1] << " = ";
        cout << (fr[i] *= fr[i+1]) << endl;
        cout << fr[i] << " /= " << fr[i+1] << " = ";
        cout << (fr[i] /= fr[i+1]) << endl;
    }

    cout << "\n----- Testing shorthand arithmetic assignment using integers\n";
    Fraction f(-1, 3);
    int num = 3;
    cout << f << " += " << num << " = ";
    cout << (f += num) << endl;
    cout << f << " -= " << num << " = ";
    cout << (f -= num) << endl;
    cout << f << " *= " << num << " = ";
    cout << (f *= num) << endl;
    cout << f << " /= " << num << " = ";
    cout << (f /= num) << endl;

    cout << "\n----- Testing increment/decrement prefix and postfix\n";
    Fraction g(-1, 3);
    cout << "Now g = " << g << endl;
    cout << "g++ = " << g++ << endl;
    cout << "Now g = " << g << endl;
    cout << "++g = " << ++g << endl;
    cout << "Now g = " << g << endl;
    cout << "g-- = " << g-- << endl;
    cout << "Now g = " << g << endl;
    cout << "--g = " << --g << endl;
    cout << "Now g = " << g << endl;
}


/*
OUTPUT:



 */
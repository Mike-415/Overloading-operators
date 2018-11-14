#include "Fraction.h"

namespace cs_fraction {
    Fraction::Fraction( int inNumerator, int inDenominator){
        assert(inDenominator != 0);
        numerator = inNumerator;
        denominator = inDenominator;
        this->simplify();
    }






    std::ostream& operator<<(std::ostream& leftOS, const Fraction& rightOperand) {
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


 */
    std::istream& operator>>(std::istream& leftIS, Fraction& rightOperand){
        int firstPortion, secondPortion, thirdPortion;
        leftIS >> firstPortion;
        if (leftIS.peek() == '+'){
            leftIS.ignore();
            leftIS >> secondPortion; //Numerator
            leftIS.ignore();
            leftIS >> thirdPortion;  //Denominator
            firstPortion = thirdPortion * firstPortion;
            firstPortion += (firstPortion > 0)? secondPortion : -secondPortion;
            secondPortion = thirdPortion;
        } else if (leftIS.peek() == '/'){
            leftIS.ignore();
            leftIS >> secondPortion;
        } else {
            secondPortion = 1;
        }
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






    void Fraction::simplify(){
        this->correction(); //This function esolves fraction edge cases prior to simplification
        int smallestValue = ( abs(this->numerator) < abs(this->denominator))? abs(this->numerator) : this->denominator;
        while( smallestValue > 1 && this->numerator != 1 && this->denominator != 1){
            if(abs(this->numerator) % smallestValue == 0 && this->denominator  % smallestValue == 0){
                this->numerator /= smallestValue;
                this->denominator /= smallestValue;
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
}


#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>
using namespace std;

// Declare constants
const char PLUS = '+';
const char MINUS = '-';
const char MULTIPLY = '*';
const char DIVIDE = '/';

const unsigned int VAR = 0;

const string EXIT = "0";
const unsigned int FIRST = 1;

#define isExit(n) ( n==EXIT ? true : false )
#define isEqual(n) ( n=="=" ? true : false )

/*
 * Monomial Class Definition
 */

//#ifndef _MONOMIAL_
//#define _MONOMIAL_

class Monomial
{
  private:
    float coefficient;
    char variable;
    int exponent;

  public:
    // Initializer
    Monomial(float coefficient, char variable, int exponent):
      coefficient{coefficient},
      variable{variable},
      exponent{exponent}
    {}

    // Make keys for dictionary including variable and exponent
    string makeKey();

    // Return coefficient
    float getCoeff();

    // Return variable
    char getVar();

    // Make combination for dictionary data type
    pair <string, float> makeDict();
};
//#endif

/*
 * Polynomials Class Definition
 */

//#ifndef _POLYNOMIAL_
//#define _POLYNOMIAL_

class Polynomial
{
  private:
    map<string, float> polynomial;
    map<string, float>::iterator plItr;
    map<string, float>::iterator lastItem = polynomial.end();

    set<char> uniqueVar;
    set<char>::iterator uvItr;

  public:
    // Equal operator overloading
    void operator = (map<string, float> newPoly);
    
    // Check if polynomial is empty
    // returns true if it is empty
    bool isEmpty();

    // Get polynomial map
    map<string, float> getPoly();

    // Get unique variable vector
    set<char> getUniVar();
    
    // Get unique variable vector
    vector<pair<string, float>>::iterator findKey();

    // Insert variables to a unique vector
    void insertUniVar(Monomial mono);

    // Insert new monomial to the dictionary
    void insertMono(Monomial mono);

    // Delete the last item and insert the new item
    void updateMono(string newKey, float newValue);
    
    // Multiply all the values of monomial with -1
    // to change polynomial to negative in the minus operate
    void negativePoly();
    
    // Update exponent in multiply or divide calculation of the same variables
    // returns key in string result of the operating
    string operateSameVar(char opr, string oldKey, string key);

    // Update exponent in divide calculation of different variables
    // returns key in string result from the divide operating
    string divideDiffVar(string oldKey, string key);

    /* Update key and value before insert new monomial */

    // for multiply operators
    void multiplyMono(Monomial mono);
    // for divide operators
    void divideMono(Monomial mono);
    // for plus and minus operators
    void addMono(Monomial mono);

    // Print all items in dictionary
    void printPoly();

    // Do evaluate polynomial with a variable's values dictionary
    // returns a floating point number result from evaluating a polynomial
    float doEvaluate(map<char, float> varDict);
};
//#endif

/*
 * Multi Polynomial Class Definition
 */

//#ifndef _MULTI_POLYNOMIAL_
//#define _MULTI_POLYNOMIAL_

class MultiPolynomials
{
  private:
    vector<pair<Polynomial, char>> multiPolynomials;
    vector<pair<Polynomial, char>>::iterator mpItr;

    set<char> totalUniqueVar;
    set<char>::iterator tuvItr;

  public:
    // Insert new polynomial and operators to vector
    void insertPoly(Polynomial poly, char opr);

    // Insert unique variables from every polynomials
    void insertTotUniVar(Polynomial poly);

    // Get total unique variables set
    set<char> getTotUniVar();

    // Check if the Multi Polynomials is empty
    // return true if it is empty
    bool isEmpty();

    // Search and count for multiply operator
    // returns count number of multiply operator
    unsigned int findMultiply();

    // Do operate after input all polynomials and operators
    // returns a polynomial class result after do all the operating in multiPolynomials
    Polynomial doOperate();

    // Do plus with polynomials
    // returns a polynomial class result from the add operating of all polynomials in the multiPolynomials
    Polynomial operatePlus();

    // Do multiply with polynomials
    // returns a polynomial class result from the multiply operating of 2 polynomials
    Polynomial operateMultiply(Polynomial poly, Polynomial prevPoly);

    // Do multiply multi variables and exponents
    // returns string of key combination from multiply operating
    string multiplyKeys(string key1, string key2);
};

//endif

/*
 * Other Functions
 */

//#ifndef _OTHER_FUNCTIONS_
//#define _OTHER_FUNCTIONS_

// Parse string into smaller variable
void parseStr(
    string str,
    float* coeff,
    char* var,
    int* exp,
    char* opr
);
 
// Unsigned Integer validation
// returns true if n is a integer
bool isInt(string n);

// Floating point number validation
// returns true if n is a floating point number
bool isFloat(string n);

// Convert string to unsigned int
// returns a unsigned int
unsigned int intConvert(string n);

// Convert string to unsigned int
// returns a unsigned int
float floatConvert(string n);

// Other operators validation except =
// returns true for if operator is + - * / 
bool isOtherOpr(string opr, unsigned int index);

// Validate monomial form
// returns true for if the string is in correct form
bool isMonoValid(string str, unsigned int index);

//#endif

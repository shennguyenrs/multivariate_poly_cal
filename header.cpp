#include "header.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <cctype>
#include <regex>
using namespace std;

/*
 * Monomial Class Functions
 */

string Monomial::makeKey()
{
  if(coefficient==0 || exponent==0)
  {
    return "0";
  }

  return variable + to_string(exponent);
}

float Monomial::getCoeff()
{
  return coefficient;
}

char Monomial::getVar()
{
  return variable;
}

pair <string, float> Monomial::makeDict()
{
  return make_pair(makeKey(), getCoeff());
}

/*
 * Polynomials Class Functions
 */

void Polynomial::operator = (map<string, float> newPoly)
{
  polynomial = newPoly;
}

bool Polynomial::isEmpty()
{
  return polynomial.empty();
}

map<string, float> Polynomial::getPoly()
{
  return polynomial;
}

set<char> Polynomial::getUniVar()
{
  return uniqueVar;
}

vector<pair<string, float>>::iterator findKey(string key)
{ 
  vector<pair<string, float>>::iterator itr;

  for(itr=polynomial.begin(); itr!=polynomial.end(); itr++
  {
    string baseKey = itr->second;

    if(key==baseKey)
    {
      return itr;
    }
  }

  return itr=lastItem;
}

void Polynomial::insertUniVar(Monomial mono)
{
  string var = mono.makeKey();

  // Do not insert if var is 0
  if(var!="0")
  {
    uniqueVar.insert(var[VAR]);
  }
}

void Polynomial::insertMono(Monomial mono)
{
  polynomial.insert(mono.makeDict());
}

void Polynomial::updateMono(string newKey, float newValue)
{
  polynomial.erase(prev(lastItem));
  polynomial.insert(make_pair(newKey, newValue));
}

void Polynomial::negativePoly()
{
  // Multiply value of variable to -1 to change the polynomial to negative
  for(plItr=polynomial.begin(); plItr!=polynomial.end(); plItr++)
  {
    plItr->second *= -1;
  }
}

string Polynomial::operateSameVar(char opr, string oldKey, string key)
{
  int oldExp;
  int exp;
  char var;

  stringstream ss;

  // Parse string into variable and exponent
  ss << oldKey;
  ss >> var >> oldExp;

  // Clear stringstream
  ss.clear();

  ss << key;
  ss >> var >> exp;

  // Return bases on operator
  // add the exponent for multiply operator
  if(opr==MULTIPLY)
  {
    return var + to_string(oldExp+exp);
  }

  // minus the exponent for divide operator
  return (oldExp-exp)==0 ?
    "0" : var + to_string(oldExp-exp);
}

string Polynomial::divideDiffVar(string oldKey, string key)
{
  int exp;
  char var;

  set<string> orderedKey;
  set<string>::iterator itr;

  stringstream ss(key);

  // Parse string into variable and exponent
  ss >> var >> exp;

  string newExp = to_string(exp*-1);

  // Ordered key
  orderedKey.insert(oldKey);
  orderedKey.insert(var+newExp);

  // Stream new key in ordered
  ss.clear();

  for(itr=orderedKey.begin(); itr!=orderedKey.end(); itr++)
  {
    ss << *itr;
  }

  string newKey;

  ss >> newKey;

  return newKey;
}

/* Update key and value before insert new monomial for each operators */

void Polynomial::multiplyMono(Monomial mono)
{
  string key = mono.makeKey();
  float value = mono.getCoeff();

  string lastKey = prev(lastItem)->first;

  // Increase the exponent if the last variable is the same
  if(lastKey[VAR]==key[VAR]) // This is only work for one variable in the key
  {
    string newKey = operateSameVar(MULTIPLY, prev(lastItem)->first, key);
    float newValue = prev(lastItem)->second * value;

    updateMono(newKey, newValue);

    return;
  }
  
  // or make the new key combined with new variable
  string newKey = prev(lastItem)->first + key;
  float newValue = prev(lastItem)->second * value;

  updateMono(newKey, newValue);
}

void Polynomial::divideMono(Monomial mono)
{
  string key = mono.makeKey();
  float value = mono.getCoeff();

  string lastKey = prev(lastItem)->first;

  // Remove variable if the last variable is the same
  if(lastKey[VAR]==key[VAR])
  {
    string newKey = operateSameVar(DIVIDE, prev(lastItem)->first, key);
    float newValue = prev(lastItem)->second / value;

    updateMono(newKey, newValue);

    return;
  }

  // or make the new key combined with new variable
  // the exponent of divisor is multiply with -1
  string newKey = divideDiffVar(prev(lastItem)->first, key);
  float newValue = prev(lastItem)->second / value;

  updateMono(newKey, newValue);
}

void Polynomial::addMono(Monomial mono)
{
  string key = mono.makeKey();
  float value = mono.getCoeff();

  plItr = polynomial.find(key);

  // Adds coefficient if the same variable is found
  if(plItr!=lastItem)
  {
    polynomial[key] += value;
    return;
  }
  
  // or make a new items
  insertMono(mono);
}

void Polynomial::printPoly()
{
  for(plItr=polynomial.begin(); plItr!=polynomial.end(); plItr++)
  {
    float coeff = plItr->second;
    string varExp = plItr->first;

    // Do not print + at the beginning
    // and if coefficient is negative
    cout << (coeff<0 || plItr==polynomial.begin() ? " " : " + ") << coeff;

    // Do no print variable if monomial is non-variable monomial
    if(varExp[0]=='0') { continue; }

    // Add caret between variable and exponent
    char var;
    int exp;
    char caret{'^'};
    string withCaret;
    stringstream ss(varExp);
    stringstream ssWithCaret;

    while(ss >> var)
    {
      ss >> exp;
      ssWithCaret << var << caret << exp;
    }
    
    ssWithCaret >> withCaret;

    cout << withCaret;
  }
}

float Polynomial::doEvaluate(map<char, float> varDict)
{
  float result{0};

  for(plItr=polynomial.begin(); plItr!=polynomial.end(); plItr++)
  {
    float coeff = plItr->second;
    string varExp = plItr->first;

    // For non-variable monomial
    if(varExp=="0")
    {
      result += coeff;
      continue;
    }

    char var;
    int exp;
    stringstream ss;
    unsigned int lenVar{0};

    ss << varExp;
    
    while(ss >> var)
    {
      ss >> exp;

      lenVar++;
    }

    // For one variable monomial
    ss.clear();
    ss << varExp;
      
    if(lenVar==1)
    {
      while(ss >> var)
      {
        ss >> exp;

        result += (coeff*pow(varDict.find(var)->second, exp));
      }
      continue;
    }

    // For more than one variables in monomial
    float withoutCoeff{1};

    while(ss >> var)
    {
      ss >> exp;

      withoutCoeff *= pow(varDict.find(var)->second, exp);
    }

    result += coeff*withoutCoeff;
  }

  return result;
}

/*
 * Multi Polynomials Class Functions
 */

void MultiPolynomials::insertPoly(Polynomial poly, char opr)
{
  multiPolynomials.push_back(make_pair(poly, opr));
}

void MultiPolynomials::insertTotUniVar(Polynomial poly)
{
  set<char> uniqueVar = poly.getUniVar();
  set<char>::iterator uvItr;

  // Insert unique variable
  for(uvItr=uniqueVar.begin(); uvItr!=uniqueVar.end(); uvItr++)
  {
    totalUniqueVar.insert(*uvItr);
  }
}

set<char> MultiPolynomials::getTotUniVar()
{
  return totalUniqueVar;
}

bool MultiPolynomials::isEmpty()
{
  return multiPolynomials.empty();
}

unsigned int MultiPolynomials::findMultiply()
{
  unsigned int count{0};

  for(mpItr=multiPolynomials.begin(); mpItr!=multiPolynomials.end(); mpItr++)
  {
    char opr = mpItr->second;
    
    if(opr==MULTIPLY)
    {
      count+=1;
    }
  }

  return count;
}

Polynomial MultiPolynomials::doOperate()
{
  // Do the multiply operators with the polynomials have operator is multiply
  auto count = findMultiply();

  while(count>0)
  {
    for(mpItr=multiPolynomials.begin(); mpItr!=multiPolynomials.end(); mpItr++)
    {
      char opr = mpItr->second;

      if(opr==MULTIPLY)
      {
        Polynomial poly = mpItr->first;
        Polynomial prevPoly = prev(mpItr)->first;

        auto resultPoly = operateMultiply(poly, prevPoly);

        // Remove the previous polynomial in MultiPolynomials
        multiPolynomials.erase(prev(mpItr));

        // Insert the resultPoly to MultiPolynomials at previous polynomials position
        multiPolynomials.insert(prev(mpItr), make_pair(resultPoly, '+'));

        // Remove the polynomial in MultiPolynomials
        multiPolynomials.erase(mpItr);

        break;
      }
    }

    // Decrease count to end loop
    count--;
  }

  // Return a map that added all the remain polynomials in multiPolynomials
  return operatePlus();
}

Polynomial MultiPolynomials::operatePlus()
{
  map<string, float> resultPoly;
  map<string, float>::iterator resultItr;

  // Add all the polynomials in the present vector 
  // to a result dictionary
  for(mpItr=multiPolynomials.begin(); mpItr!=multiPolynomials.end(); mpItr++)
  {
    auto poly = (mpItr->first).getPoly();
    map<string, float>::iterator itr;

    for(itr=poly.begin(); itr!=poly.end(); itr++)
    {
      string key = itr->first;
      float value = itr->second;
      resultItr = resultPoly.find(key);

      // If found the same key
      // add the value only
      if(resultItr!=resultPoly.end())
      {
        resultPoly[key] += value;
        continue;
      }

      // or insert new key and value
      resultPoly.insert(make_pair(key, value));
    }
  }

  // Turn map into Polynomial class
  Polynomial newPoly; 
  newPoly = resultPoly;
  
  return newPoly;
}

Polynomial MultiPolynomials::operateMultiply(Polynomial poly1, Polynomial poly2)
{
  auto poly = poly1.getPoly();
  auto prevPoly = poly2.getPoly();

  map<string, float>::iterator polyItr; 
  map<string, float>::iterator prevItr; 

  map<string, float> resultPoly; 
  map<string, float>::iterator resultItr; 

  for(prevItr=prevPoly.begin(); prevItr!=prevPoly.end(); prevItr++)
  {
    string prevKey = prevItr->first;
    float prevValue = prevItr->second;

    for(polyItr=poly.begin(); polyItr!=poly.end(); polyItr++)
    {
      string key = polyItr->first;
      float value = polyItr->second;

      // Do multiply variable
      string newKey = multiplyKeys(key, prevKey);

      // Do multiply value
      float newValue = prevValue * value;

      // Add value if the same key exist in the result map
      resultItr = resultPoly.find(newKey);

      if(resultItr!=resultPoly.end())
      {
        resultItr->second += newValue;
        continue;
      }

      // Or insert new key and value if not
      resultPoly.insert(make_pair(newKey, newValue));
    }
  }

  // Turn resultPoly to Polynomial class
  Polynomial newPoly;
  newPoly = resultPoly;

  return newPoly;
}

string MultiPolynomials::multiplyKeys(string key1, string key2)
{
  string str;
  char var;
  int exp;
  stringstream ss(key1+key2);

  map<char, int> newKey;
  map<char, int>::iterator nkItr;

  while(ss >> var)
  {

    ss >> exp;

    nkItr = newKey.find(var);

    // If found the exist variable
    // add the exponent only
    if(nkItr!=newKey.end())
    {
      nkItr->second += exp;
      continue;
    }
    
    // If not found the exist variable
    // insert a new variable with its exponent
    newKey.insert(make_pair(var, exp));
  }

  // Make string from the dictionary
  for(nkItr=newKey.begin(); nkItr!=newKey.end(); nkItr++)
  {
    str += (nkItr->first + to_string(nkItr->second));
  }

  return str;
}

/*
 * Other Functions
 */

void parseStr(
  string str,
  float* coeff,
  char* var,
  int* exp,
  char* opr
  )
{
  char caret;
  stringstream ss(str);

  // If the multiply or divide is found at the first
  if(str[0]==MULTIPLY || str[0]==DIVIDE)
  {
    ss >> *opr >> *coeff>> *var >> caret >> *exp;
    return;
  }
  
  ss >> *coeff >> *var >> caret >> *exp;
  *opr = PLUS;
}

bool isInt(string n)
{
  bool result{true};

  // Check every digits for a number
  for(auto x: n)
  {
    if(!isdigit(x))
    {
      result = false;
      return result;
    }
  }

  return result;
}

bool isFloat(string n)
{
  bool result{true};
  char dot = '.';

  // Check every digits for a number
  for(auto x: n)
  {
    if(!isdigit(x) || x!=dot)
    {
      result = false;
      return result;
    }
  }

  // Be true if the second dot is not exist
  bool secondDot = n.find(dot, n.find('.')+1)!=string::npos 
    ? true : false;

  return result && !secondDot;
}

unsigned int intConvert(string n)
{
  unsigned int result{0};
  stringstream ss(n);

  ss >> result;
  
  return result;
}

float floatConvert(string n)
{
  stringstream ss(n);
  float result{0};

  ss >> result;

  return result;
}

bool isOtherOpr(string opr, unsigned int index)
{
  if(index==1)
  {
    return (opr=="+" || opr=="-" || opr==EXIT) ? 
      true : false;
  }

  return (opr=="+" || opr=="-" || opr=="*" || opr=="/" || opr==EXIT) ? 
    true : false;
}

bool isMonoValid(string str, unsigned int index)
{
  regex forFirst("(\\+|-|)([0-9]{1,}|[0-9]{1,}\\.[0-9]{1,})[a-zA-Z]\\^(\\-|)([0-9]{1,})$");
  regex forRest("(\\+|-|\\*|\\/|)(\\+|-|)([0-9]{1,}|[0-9]{1,}\\.[0-9]{1,})[a-zA-Z]\\^(\\-|)([0-9]{1,})$");

  if(index==1)
  {
    return regex_match(str, forFirst);
  }

  return regex_match(str, forRest);
}

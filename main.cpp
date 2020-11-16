#include "header.hpp"

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
  string n;
  
  // Set 2 numbers after the decimal point
  cout << fixed << setprecision(2);

  // Welcome
  cout << "==========================================" << endl; 
  cout << "       Polynomials Calculator + - *       " << endl;
  cout << "==========================================" << endl; 
  cout << endl;

  // User guide
  cout << "User guide" << endl;
  cout << "----------" << endl;
  cout << "0    : Exitcode for any input form" << endl;
  cout << endl;
  cout << "Operators for polynomial" << endl;
  cout << "------------------------" << endl;
  cout << "=    : End the input polynomial" << endl;
  cout << "+    : Add this polynomial to the previous one" << endl;
  cout << "-    : Minus this polynomial to the previous one" << endl;
  cout << "*    : Multiply this polynomial to the previous one" << endl;
  cout << endl;
  cout << "Operators for nominal" << endl;
  cout << "------------------------" << endl;
  cout << "=    : End the input nominal" << endl;
  cout << "+    : Add this nominal to the previous one" << endl;
  cout << "-    : Minus this nominal to the previous one" << endl;
  cout << "*    : Multiply this nominal to the previous one" << endl;
  cout << "/    : Divide this nominal to the previous one" << endl;
  cout << endl;
  cout << "Pattern for inputted monomials" << endl;
  cout << "------------------------" << endl;
  cout << "- Operators:          The first monomial do not allow operators * and / ecxcept the next monomials" << endl; 
  cout << "                      (-) Invalid the first monomial: *10x^2" << endl;
  cout << "                      (+) Valid other monomial:       *10x^2" << endl;
  cout << "- Coefficient:        Do not allow input monomial without coefficient" << endl; 
  cout << "                      (-) Invalid input:                 x^2" << endl;
  cout << "                      (+) Valid input:                 *0x^2" << endl;
  cout << "- Variable:           Do not allow input more than one variable in a monomial" << endl; 
  cout << "                      (-) Invalid input:            /3y^6x^2" << endl;
  cout << "                      (+) Valid input:                 /3y^6" << endl;
  cout << "- Caret & exponent:   Always place caret between variable and exponent" << endl; 
  cout << "                      Only allow integer exponent" << endl; 
  cout << "                      (-) Invalid input:              /5x2.3" << endl;
  cout << "                      (+) Valid input:                 /5x^2" << endl;
  cout << endl;
  
  do
  {
    /* Number of polynomials validation */

    cout << "Enter the number of polynomials to operating (or 0 to exit): ";
    cin >> n;
    
    // Input validation for other date type
    if(!isInt(n))
    {
      cout << "You entered wrong data type!" << endl;
      cout << "Please try again with an  positive integer!" << endl;
      continue;
    }

    // Exit main part when n is 0
    if(isExit(n)) { continue; }

    /* After n is validated */

    // Create Multi Polynomials class;
    MultiPolynomials multiPoly;

    auto numberPoly = intConvert(n);

    unsigned int i{1};

    while(numberPoly>0)
    {
      cout << endl;
      cout << "Enter the polynomial " << i << endl;
      cout << "=======================" << endl; 

      string operate;
      bool exitFromPoly{false};
      bool exitFromMono{false};
      bool nextPoly{false};

      /* Polynomial operator validation */

      do
      {
        // Do not show multiply operator for the first polynomial
        cout << "Enter the operator of polynomial " << i 
          << (i==FIRST ? " (+,-,=): " : " (+,-,*,=): ");

        cin >> operate;

        // End the input polynomial with equal
        if(isEqual(operate)) { break; }

        // Print messages if operator is no valid
        if(!isOtherOpr(operate, i))
        {
          cout << "You inputted invalid operators!" << endl;
          cout << "Please try again!" << endl;
          continue;
        }

        // Exit from input polynomial to top menu with 0
        if(isExit(operate))
        {
          exitFromPoly = true;
          break;
        }

        /* After operator is valid */

        cout << endl;

        // Create a polynomial class
        Polynomial poly;

        string monoStr;
        unsigned int j{1};

        /* Nominals Validation */

        do
        {
          // Print out the present monomials in polynomial
          // because map orders items everytime inserting
          if(!poly.isEmpty())
          {
            cout << "Present Polynomial: ";
            poly.printPoly();
            cout << endl;
          }

          // Do not show multiply and divide operator for the first monomial 
          cout << "Enter monomial with operator " << 
            (j==FIRST ? "(+,-,=): " : "(+,-,*,/,=): ");
          cin >> monoStr;

          // End input nominal with =
          if(isEqual(monoStr)) 
          { 
            nextPoly = true;
            break; 
          }

          // Exit from input nominal to top menu with 0
          if(isExit(monoStr))
          {
            exitFromMono = true;
            break;
          }

          // Print messages if the inputted nominal is not valid
          if(!isMonoValid(monoStr, j))
          {
            cout << "You entered wrong form of nominal!" << endl;
            cout << "Please try again!" << endl;
            continue;
          }

          /* After Nominals is valid */

          // Increase j
          j++;

          float coeff;
          char var;
          int exp;
          char opr;

          // Parse string to variables
          parseStr(monoStr, &coeff, &var, &exp, &opr);

          // Make a new monomial class
          Monomial mono(coeff, var, exp);

          // Insert unique variables to Polynomial class
          poly.insertUniVar(mono);

          // Insert monomial to polynomial
          // also do operate with the exits monomial
          if((j-1)==FIRST)
          {
            poly.insertMono(mono);
            continue;
          }

          // Plus or Minus operating
          if(opr==PLUS || opr==MINUS)
          {
            poly.addMono(mono);
            continue;
          }

          // Multiply operating
          if(opr==MULTIPLY)
          {
            poly.multiplyMono(mono); 
            continue;
          }

          // Divide operating
          if(opr==DIVIDE)
          {
            poly.divideMono(mono);
          }
        }
        while(!isEqual(monoStr) || !isExit(monoStr));

        /* After inputted all Monomials */

        // Do not insert polynomial if it is empty
        // also with the unique variable
        if(!poly.isEmpty())
        {
          multiPoly.insertTotUniVar(poly);

          // Change to negative polynomial if operator of polynomial is minus
          if(operate[0]==MINUS)
          {
            poly.negativePoly();
            multiPoly.insertPoly(poly, PLUS);
            break;
          }

          multiPoly.insertPoly(poly, operate[0]);
          // Print out inputted polynomial
          cout << endl;
          cout << "Your inputted polynomial: ";
          poly.printPoly();
          cout << endl;
        }
        
        // Exit to top menu from inputting Monomials
        if(exitFromMono || nextPoly) { break; }
      }
      while(!isEqual(operate) || !isExit(operate));

      // Exit to top menu from inputting polynomials
      if(exitFromPoly || exitFromMono) { break; }

      // Decrease numberPoly
      numberPoly--;
      i++;
    } 

    /* Calculate the result polynomial */

    cout << endl;

    // Do Multi Polynomial operating if the multiPoly is not empty
    if(multiPoly.isEmpty())
    {
      cout << "You do not have any monomial or polynomial to calculate" << endl;
      continue;
    }

    Polynomial resultPoly = multiPoly.doOperate();

    // Print out the result polynomial
    cout << "Result polynomial" << endl;
    cout << "-----------------" << endl;
    resultPoly.printPoly();
    cout << endl;
    
    /* Ask user for evaluate variable in result polynomial */

    string choose;

    do 
    {
      cout << "Do you want to evaluate this polynomial? (y or n) ";
      cin >> choose;

      // Print messages if input wrong keyword
      if(!isExit(choose) && choose!="y" && choose!="n")
      {
        cout << "You enter wrong choose!" << endl;
        cout << "Please try again!" << endl;
        continue;
      }

      // Exit evaluation step
      if(isExit(choose) || choose=="n") { break; }

      /* Input variable's values and validation */

      set<char> uniqueVar = multiPoly.getTotUniVar();
      set<char>::iterator uvItr = uniqueVar.begin();
      map<char, float> varDict;

      do
      {
        string valueStr;
        cout << "Input value for " << *uvItr << ": ";
        cin >> valueStr;

        if(!isFloat(valueStr) && !isInt(valueStr))
        {
          cout << "Your input is wrong data type!" << endl;
          cout << "Please try again!" << endl;
          continue;
        }

        // Insert validated value and variable to varDict
        float value = floatConvert(valueStr);
        varDict.insert(make_pair(*uvItr, value));

        uvItr++;
      }
      while(uvItr!=uniqueVar.end());

      /* After have a variable dictionary */

      cout << endl;
      cout << "Evaluation Result: " << resultPoly.doEvaluate(varDict) << endl;
      cout << endl;

      break;
    }
    while(choose!="n" || !isExit(choose));
  }
  while(!isExit(n));
  
  return 0;
}

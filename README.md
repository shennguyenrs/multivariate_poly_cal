# Multivariate Polynomials Calculator + - *
>Terminal based application to operating multivariate polynomials on addition, subtract and multiply.

![User Guide](/2020-11-16_23-06.png)
![Input and Evaluating](/2020-11-16_23-05.png)

## Usage
Make output file using the script. This script also includes creating tags that required installed `exuberant-ctags` package.
**This script can only be run on Debian or Ubuntu**
```
sh ./makenrun.sh filename headername
```
``` bash
sh ./makenrun.sh main header
```

## Checklist
- [ ] Input validation
  - [ ] Understand input without coefficent. Ex: x^4, \*y^7
  - [ ] Understand input integer number without variable. Ex: 8, -7
  - [x] Parse inputted string of monomial
  - [x] Check valid inputted monomial pattern with Regex
- [x] Perform addtion or subtract on polynomials or monomials
- [ ] Perform multiply on polynomials. Basically, It can perform basic multiply.
  - [ ] Implement Polynomonial on Vector, so that the inputted monomial will not be changed its order.
  - [ ] Perform multiply and divide inputting monomials continuously. Ex: 4x^3\*5y^2\*12z^7
  - [x] Arrange order of variables in monomials which has more than one variable when multiplying
- [x] Evaluate result polynomial

## Contributions
Your contributions are always welcome.

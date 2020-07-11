#include <iostream>
#include <fstream>
#include "BoolFunc.h"

using std::cout;
using std::endl;

void CheckBasicFuncs() {
  uint TVand[] = { 0x8 }, 
    PDNFand[] = { 0x8 }, 
    PCNFand[] = { 0x7 }, 
    RDNFand[] = { 0x3, 0x3 }, 
    ZPand[] = { 0x8 };
  BoolFunc AndTV(2, TVand, TruthVectorType), 
    AndPDNF(2, PDNFand, PDNFtype), 
    AndPCNF(2, PCNFand, PCNFtype), 
    AndRDNF(2, RDNFand, RDNFtype, 1), 
    AndZP(2, ZPand, ZhegalkinPolynomType);

  cout << "And" << endl;
  cout << "Check right: " << (AndPDNF.CheckRight() && AndPCNF.CheckRight() && AndTV.CheckRight() && AndRDNF.CheckRight() && AndZP.CheckRight()) << endl;
  cout << "Check Linearity: " << AndTV.CheckLinearity() << endl;
  cout << "Check Self Duality: " << AndTV.CheckSelfDuality() << endl;
  cout << "Check 0 Preserving: " << AndTV.Check0Preserving() << endl;
  cout << "Check 1 Preserving: " << AndTV.Check1Preserving() << endl;
  cout << "Check Monotone: " << AndTV.CheckMonotone() << endl << endl;
  AndTV.PrintZP(cout);
  AndTV.PrintRDNF(cout);
  AndTV.PrintKM(cout);

  uint TVor[] = { 0xE }, 
    PDNFor[] = { 0xe }, 
    PCNFor[] = { 0x1 }, 
    RDNFor[] = { 0x1, 0x1, 0x2, 0x2 }, 
    ZPor[] = { 0xE };
  BoolFunc OrTV(2, TVor, TruthVectorType), 
    OrPDNF(2, PDNFor, PDNFtype), 
    OrPCNF(2, PCNFor, PCNFtype), 
    OrRDNF(2, RDNFor, RDNFtype, 2), 
    OrZP(2, ZPor, ZhegalkinPolynomType);

  cout << "Or" << endl;
  cout << "Check right: " << (OrPDNF.CheckRight() && OrPCNF.CheckRight() && OrTV.CheckRight() && OrRDNF.CheckRight() && OrZP.CheckRight()) << endl;
  cout << "Check Linearity: " << OrTV.CheckLinearity() << endl;
  cout << "Check Self Duality: " << OrTV.CheckSelfDuality() << endl;
  cout << "Check 0 Preserving: " << OrTV.Check0Preserving() << endl;
  cout << "Check 1 Preserving: " << OrTV.Check1Preserving() << endl;
  cout << "Check Monotone: " << OrTV.CheckMonotone() << endl << endl;
  OrTV.PrintZP(cout);
  OrTV.PrintRDNF(cout);
  OrTV.PrintKM(cout);

  uint TVimpl[] = { 0xD }, 
    PDNFimpl[] = { 0xD }, 
    PCNFimpl[] = { 0x2 }, 
    RDNFimpl[] = { 0x1, 0x0, 0x2,0x2 }, 
    ZPimpl[] = { 0xB };
  BoolFunc ImplTV(2, TVimpl, TruthVectorType), 
    ImplPDNF(2, PDNFimpl, PDNFtype), 
    ImplPCNF(2, PCNFimpl, PCNFtype), 
    ImplRDNF(2, RDNFimpl, RDNFtype, 2), 
    ImplZP(2, ZPimpl, ZhegalkinPolynomType);
  
  cout << "Implication" << endl;
  cout << "Check right: " << (ImplPDNF.CheckRight() && ImplPCNF.CheckRight() && ImplTV.CheckRight() && ImplRDNF.CheckRight() && ImplZP.CheckRight()) << endl;
  cout << "Check Linearity: " << ImplTV.CheckLinearity() << endl;
  cout << "Check Self Duality: " << ImplTV.CheckSelfDuality() << endl;
  cout << "Check 0 Preserving: " << ImplTV.Check0Preserving() << endl;
  cout << "Check 1 Preserving: " << ImplTV.Check1Preserving() << endl;
  cout << "Check Monotone: " << ImplTV.CheckMonotone() << endl << endl;
  ImplTV.PrintZP(cout);
  ImplTV.PrintRDNF(cout);
  ImplTV.PrintKM(cout);
}

int main() {
  CheckBasicFuncs();

  std::ifstream file("12_8.txt");
  std::istream &f = file;
  BoolFunc BF(false);
  f >> BF;
  cout << "Check right: " << BF.CheckRight() << endl;
  cout << "Check Linearity: " << BF.CheckLinearity() << endl;
  cout << "Check Self Duality: " << BF.CheckSelfDuality() << endl;
  cout << "Check 0 Preserving: " << BF.Check0Preserving() << endl;
  cout << "Check 1 Preserving: " << BF.Check1Preserving() << endl;
  cout << "Check Monotone: " << BF.CheckMonotone() << endl << endl;

  BF.PrintRDNF(cout);
  BF.PrintZP(cout);
  BF.PrintKM(cout);

  return 0;
}
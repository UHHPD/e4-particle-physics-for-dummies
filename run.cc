#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <math.h>

#include "Data.hh"

// generic function comparing two values of some type T used later for int and
// double
template <class T>
bool testEqual(const std::string& name, T expected, T real) {
  if (expected != real) {
    std::cout << "(" << name << ": <" << expected << ">"
              << ", " << real << ") ";
    return false;
  }
  return true;
}

bool testReadingSize() {
  std::cout << "testReadingSize...";
  Data datA("testA");
  return testEqual<int>("size", 1, datA.size());
}

bool testReadingMeasurement() {
  std::cout << "testReadingMeasurement...";
  Data datA("testA");
  return testEqual("measurement", 10., datA.measurement(0));
}

bool testReadingBinEdges() {
  std::cout << "testReadingBinEdges...";
  Data datA("testA");
  return testEqual("bin low", 0., datA.binLow(0)) &&
         testEqual("bin high", 1., datA.binHigh(0));
}

bool testReadingErrors() {
  std::cout << "testReadingErrors...";
  Data datA("testA");
  return testEqual("error", 2., datA.error(0));
}

bool testCopyConstructor() {
  std::cout << "testCopyConstructor...";
  Data a("testA");
  Data b(a);
  Data c = a;  // equivalent to Data c(a)
  return testEqual("measurement", 10., b.measurement(0)) &&
         testEqual("measurement", 10., c.measurement(0));
}

void runTests() {
  std::cout << "running tests...\n";
  std::vector<std::function<bool()> > tests(
      {testReadingSize, testReadingMeasurement, testReadingBinEdges,
       testReadingErrors, testCopyConstructor});
  for (auto test : tests)
    std::cout << (test() ? " ok" : " FAILED!") << std::endl;
}

//bool checkCompatibility(Data& Datas){
//int checkCompatibility ( const Data& in , int n ){
//  double deltay =  sqrt(pow(in[0].measurement(27) - in[1].measurement(27),2));
//  double sigmay = in[0].error(27) + in[1].error(27);
//  return( int(bool(deltay < n*sigmay)) );
//}

int main() {
  using namespace std;

  cout << "******************************************************" << endl;
  runTests();
  cout << "******************************************************" << endl;
  // create an object which holds data of experiment A
  Data datA("exp_A");
  // create an object which holds data of experiment B
  Data datB("exp_B");
  // create an object which holds data of experiment C
  Data datC("exp_C");
  // create an object which holds data of experiment D
  Data datD("exp_D");

  std :: vector < Data > Datas;
  Datas.push_back(datA);
  Datas.push_back(datB);
  Datas.push_back(datC);
  Datas.push_back(datD);
  cout << Datas[0].measurement(27) << endl;

  // here is the data from experiment A
  cout << "bin 27: from " << datA.binLow(27) << " to " << datA.binHigh(27)
       << endl;
  for (int i = 0; i < 4; ++i) {
    cout << "measurement of experiment " << i << " in bin 27: " << Datas[i].measurement(27)
       << endl;
  }
  
  // 1d
  cout << Datas[0].checkCompatibility(Datas[1],2) << endl;
 

  return 0;
}

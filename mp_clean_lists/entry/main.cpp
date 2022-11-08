#include "List.h"
#include <iostream>
#include <time.h>
#include <iomanip>
int main() {
  List<int> test;
  List<int> test2;
  
  test2.insertBack(1);
  test2.insertBack(2);
  test2.insertBack(3);
  test2.insertBack(4);
  test2.insertBack(5);
  test2.insertBack(6);



  test.insertBack(2);
  test.insertBack(5);
  test.insertBack(7);

  clock_t start = clock();
  test2.tripleRotate();
  clock_t end = clock();
  //test.mergeWith(test2);
  
  float elapsed = double(end - start)/CLOCKS_PER_SEC;
  cout<<"Time Measured: "<<setprecision(5)<<elapsed<<" seconds"<<endl;
  test2.print(std::cout);
  cout<<std::endl;
  return 0;
}

#include <iostream>
using namespace std;

int fib_recur(int n){
  if (n<=1){
    return n;
  }
  return fib_recur(n-1)
}

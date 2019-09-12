//Flips a coin an input number of times and prints a string with the results

#include <iostream>
#include <random>
#include <cstdlib>

using namespace std;

void coinFlip(int n)
{
  int i = 0;
  int heads = 0;
  int tails = 0;
  while (i < n)
  {
    default_random_engine flip;
    uniform_int_distribution<int> coin(0,1);
    int result = coin(flip);
    if (result == 1)
    {
      heads ++;
      i ++;
    } 
    else
    {
      tails ++;
      i ++;
    }
  }
  cout << "The results were " << heads << " heads and " << tails << " tails.";
  
}

int main() 
{
  int repeats;
  cout << "How many times do you want to flip? ";
  cin >> repeats;
  coinFlip(repeats);
}

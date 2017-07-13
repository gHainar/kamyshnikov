#include <iostream>
#include <time.h>
#include<vector>
#include<thread>

using namespace std;

int N = 200;

vector<vector<int>> A(N), B(N), C(N);

void multiply(vector<vector<int>>A, vector<vector<int>>B, vector<vector<int>>C, int left, int right)
{
  for (int k = left; k < right; k++) {
    for (int i = left; i< right; ++i) {
      for (int j = left; j < right; ++j)
        C[k][i] += A[k][j] * B[j][i];
    }
  }
}
const int thread_count = 2;
int main()
{
  srand(time(nullptr));
  vector<thread>ths(thread_count);
  int left = 0, right = left + N / thread_count;
  for (int i = 0; i < N; i++) {
    A[i].resize(N);
    B[i].resize(N);
    C[i].resize(N);
    for (int j = 0; j < N; j++) {
      A[i][j] = rand();
      B[i][j] = rand();
    }
  }

  cout << "START!!!\n";
  for (auto &th : ths) {
    th = thread(multiply, A, B, C, left, right);
    left = right;
    right = left + N / thread_count;
  }

  if (N % thread_count != 0) {
    thread th = thread(multiply, A, B, C, right*thread_count, N);
    th.join();
  }
  for (auto &th : ths)
    th.join();
  cout << "Execution time of algorithm's parallel=" << clock() / (double)1000 << endl;
  return 0;
}
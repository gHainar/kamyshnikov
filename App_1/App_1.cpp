#include<iostream>
#include<thread>
#include<vector>
#include<ctime>
#include<algorithm>
#include<mutex>

using namespace std;
mutex sum_lock;
const int thread_count = 4;
const int array_size = 1e8;
const int modul = 1e9 + 7;
vector<int> a(array_size);
long long array_mul = 1;
void thread_function(int left, int right)
{
  long long cur_mul = 1;
  for (int i = left; i<right; ++i)
  {
    if ((cur_mul *= a[i]) % modul != 0) {
      cur_mul = (a[i] * cur_mul) % modul;
    }
    cur_mul *= a[i];
  }
  lock_guard<mutex> _sum_lock(sum_lock);
  cout << "Thread #" << this_thread::get_id() << " is completed" << endl;
  if ((array_mul *= cur_mul) % modul != 0) {
    array_mul = (cur_mul * array_mul) % modul;
  }
  array_mul *= cur_mul;
}
int main()
{
  srand(time(nullptr));
  generate(a.begin(), a.end(), rand);
  vector<thread>ths(thread_count);
  int left = 0, right = left + array_size / thread_count;
  for (auto&th : ths)
  {
    th = thread(thread_function, left, right);
    left = right;
    right = left + array_size / thread_count;
  }
  if (array_size % thread_count != 0) {
    thread th = thread(thread_function, right * thread_count, array_size);
    th.join();
  }
  for (auto&th : ths)
    th.join();
  cout << "Execution time: " << clock() / (double)1000 << endl;
  system("pause");
  return 0;
}
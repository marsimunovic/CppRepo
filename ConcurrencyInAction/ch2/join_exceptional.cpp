#include <thread>
#include <iostream>

// Example: ensure join on exception 

void do_something(int& i)
{
   //do nothing
   (void)(i);
}

struct func
{
   int& i;
   func(int& i_):i(i_){}

   void operator()()
   {
      for(unsigned j = 0; j < 1000000; ++j)
         do_something(i);
   }
};

void do_something_in_current_thread()
{
   //do nothing
}

void f()
{
   int some_local_state = 0;
   func my_func(some_local_state);
   std::thread t(my_func);
   try
   {
      do_something_in_current_thread();
   }
   catch(...)
   {
      t.join();
   }
   t.join();
}

int main()
{
   std::cout << "Calling thread START!\n";
   f();
   std::cout << "Calling thread END!\n";
   return 0;
}

#include <thread>
#include <iostream>

// Example: detached thread referencing non existing local variable

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
      std::cout << "Detached thread START!\n";
      for(unsigned j = 0; j < 1000000; ++j)
         do_something(i);
      std::cout << "Detached thread END!\n";
   }
};

void oops()
{
   int some_local_state = 0;
   func my_func(some_local_state);
   std::thread my_thread(my_func);
   my_thread.detach();
}

int main()
{
   std::cout << "Calling thread START!\n";
   oops();
   std::cout << "Calling thread END!\n";
   return 0;
}

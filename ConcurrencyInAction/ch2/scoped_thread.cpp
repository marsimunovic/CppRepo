#include <thread>
#include <iostream>

// Example: ensure join using RAII idiom 

void do_something(int& i)
{
   //do nothing
   (void)(i);
}

class scoped_thread
{
   std::thread t;
public:
   explicit scoped_thread(std::thread t_):
      t(std::move(t_))
   {
      if(!t.joinable())
         throw std::logic_error("No thread");
   }

   ~scoped_thread()
   {
         t.join();
   }
   scoped_thread(scoped_thread const&) = delete;
   scoped_thread& operator=(scoped_thread const&)=delete;
};

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
   scoped_thread t(std::thread(func(some_local_state)));
   do_something_in_current_thread();
}

int main()
{
   std::cout << "Calling thread START!\n";
   f();
   std::cout << "Calling thread END!\n";
   return 0;
}

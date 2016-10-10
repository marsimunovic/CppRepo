#include <future>
#include <iostream>

int find_the_answer_to_ltuae()
{
   for(int i = 0; i < 100; ++i)
      std::cout << "Searching the answer to Life, the Universe, and Everything" << std::endl;
   std::cout << std::endl;
   return 42;
}

void do_other_stuff()
{
   //do nothing
}

int main()
{
   std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
   do_other_stuff();
   std::cout<< "The answer is " << the_answer.get() << std::endl;
   return 0;
}
   

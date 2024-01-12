#include<iostream>
#include<future>  // to write async we need to include this library

/*
    A  B  C

    option 1 : one after the other. Always complete one thing before starting the next task

        Single Thread Technique
////////////////////////////////////////////////////////////////////////////////////////////


    option 2  : I will complete all task in such way that i "practically start all of them
                at the same time" but keep juggling them based on some criteria

        Multithreaded approach
///////////////////////////////////////////////////////////////////////////////////////////

    option 3 : map number of tasks amongst number of available "workers"

        Parallelism
///////////////////////////////////////////////////////////////////////////////////////////

    option 4 : start a task. Either delegate it to another worker 
                OR do it yourself after some time

                If someone else doing a task, monitor it, wait for their work to be done,\
                take follow-up actions accordingly

        Asynchronous Exection
///////////////////////////////////////////////////////////////////////////////////////////

*/

/*
    2 tasks 
    calculate factorial of 5 
    calculate square of a number given by the user
*/

int square(std::future<int>& ft) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"Hello from square. I have been initialized and started to execute \n";
    int number = ft.get();
    return number*number;
}

int factorial(int number) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    if(number<0) {
        throw std::runtime_error("negative number error!");
    }
    if(number==0 || number==1) {
        return 1;
    }
    else {
        return number * factorial(number-1);
    }
}

int main() {

    // step 1 : make a promise that i will provide you the value (this is told to compiler)
    std::promise<int> pr;
    // it is said that to make a promise it needs to be fulfilled in future so they are 
    // linked together

    // step 2 : A future linked to the promise
    std::future<int> ft = pr.get_future();

    /*
        * OS : launch square (if possible as a new thread)
    */

    std::future<int> result_ft = std::async(std::launch::async, &square, std::ref(ft));

    // use differed std::launch::differed to run activity on same thread

    int val = 0;
    std::cin>>val;
    
    pr.set_value(val); // it sends the signal
    std::cout<<factorial(5);
    std::cout<<"Result of square is: "<< result_ft.get();


}


/*
    Client-Server Architecture

    Future-Promise Architecture :- The model which tells how to communicate with each other

    square calculation :-
        Main needs to delegate the task of square calculation

        - A new thread for square will be registred with OS


    

*/
# Task-Scheduler

This is a simple task scheduler written in modern C++, using the **Async** feature.<br/>
The scheduler uses promise and future to signal and receive the exit signal.

## How to use the scheduler:<br/>
**Method 1:**<br/>
you can pass just a function to the scheduler, and the scheduler will fire it.<br/>
Your function prototype should follow specific guidelines:<br/>
First concern, it should be a void function.<br/>
second concern, it should have a shared future as a first parameter, and you are free about the other parameters,<br/>
that shared future parameter must be there to receive the exit signal from the scheduler.<br/>
<br/>
**Method 2:**<br/>
Pass a class object.<br/>
Your class should follow a specific guideline:<br/>
There is only one concern about using a task as a class, it should inherit a base class "task_worker", and override its virtual function which will be called by the scheduler.<br/>
<br/>
Kindly find the test to find how to use the scheduler by examples.<br/>
<br/>
**Imp Note:**<br/>
There is something weird that I should mention here,<br/>
I have searched the internet about a task scheduler that is implemented using the Async feature, but I couldn't find any.<br/>
I'm not sure if there is some sort of evil about using it, but at least it works fine with me up till now.<br/>

### Notes
**[Async](https://en.cppreference.com/w/cpp/thread/async)**<br/>
The Async function is a new feature in modern C++, it saves you the hassle of creating/managing your threads.<br/>
**[Promise](https://en.cppreference.com/w/cpp/thread/promise), [Future](https://en.cppreference.com/w/cpp/thread/future)**<br/>
Those are used to communicate objects between threads.<br/>
The promise stores a state that the future can monitos to check if there is a signal from the promise or not.<br/>
They act a signal sender and receiver.<br/>

## How to build:
To build the project, create a build folder in the parent directory,<br/>
move to the build folder, and try the command : (cmake ..), and then (make).<br/>
For the test project, apply the same steps inside the test folder.

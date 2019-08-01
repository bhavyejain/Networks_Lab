/**
* @file q2.cpp
* @brief a program to demonstrate zombie and orphan processes
*
* @author Bhavye Jain
* @date July 2019
*/

#include <bits/stdc++.h>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/wait.h>

using namespace std;

int main() {

	cout << "Parent process id: " << getpid() << endl << endl;
	pid_t child_pid = fork();      // Fork from parent process

    if (child_pid > 0) {
    	cout << "Parent active..." << endl;
    	sleep(4);
    	cout << "Parent terminated" << endl;
    }
    else if (child_pid == 0) {        
    	cout << "Child created with pid "<< getpid() << " from parent pid " << getppid() << endl;   	
    	child_pid = fork();        // Fork from child process
    	if(child_pid > 0) {
    		sleep(1);
    		cout << "Child sleeping..." << endl;
    		sleep(2);
    		cout << "Child awake again and active!" << endl;
    		sleep(2);
    		cout << "Child is now orphan!" << endl << endl;
    	}
    	else if(child_pid == 0) {
    		cout << "Grandchild created with pid "<< getpid() << " from parent pid " << getppid() << endl << endl;
    		sleep(1);
    		cout << "Terminating grandchild" << endl;
    		cout << "Grandchild is now zombie" << endl << endl;
    	}
    }
  
    return 0;
}

#include <bits/stdc++.h>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/wait.h>

using namespace std;

int main(){

	cout << "Parent process id: " << getpid() << endl << endl;

	for(int i = 0; i < 2; i++){
		if(fork() == 0){
			cout << "Child " << (i+1) << " with pid "<< getpid() << " from parent pid " << getppid() << endl;

			for(int j = 0; j < 2; j++){
				if(fork() == 0){
					cout << "Grandchild " << (i*2 + 1 + j) << " with pid "<< getpid() << " from parent pid " << getppid() << endl;
					exit(0);	// grandchild process terminates execution
				}
				wait(NULL);		// child process waits for grandchild process to complete  execution
			}
			
			exit(0);		// child process terminates execution
		}
		wait(NULL);			// parent process waits for child process to terminate execution
		cout << endl;
	}
	
	exit(0);
}
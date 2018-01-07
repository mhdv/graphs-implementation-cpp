#ifndef OTHERMETHODS_H
#define OTHERMETHODS_H

#include <iostream>

//
//	SPRAWDZA CZY LICZBA JEST LICZBA PIERWSZA
//

bool isPrime(int number){
	if(number<=1) return false;
	for(int i=2; i<number; i++){
		if(number%i==0) return false;
	}
	return true;
}

//
//	ZNAJDUJE NAJWIEKSZA LICZBE PIERWSZA MNIEJSZA OD PODANEJ
//

int lowerPrime(int prime){
	int actual_number;
	bool isprime = true;
	if(prime<=3) return 3;
	for(int i=prime-1; i>3; i--){
		actual_number=i;
		for(int j=2; j<actual_number; j++){
			if(actual_number%j==0) isprime = false;
		}
		if(isprime==true) return actual_number;
		isprime = true;
	}
	return 3;
}


#endif
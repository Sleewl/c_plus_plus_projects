#include <iostream>

#include "Pet.h"
#include "Cat.h"
#include "Dog.h"
#include "FamilyPets.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Ru");
	const int maxPets = 10;
	FamilyPets family(maxPets);

	Cat cat;
	Cat* pCat = &cat;

	Dog dog;
	Dog* pDog = &dog;

	Pet* pPet = nullptr;

	cat.voice();
	cat.name();

	dog.voice();
	dog.name();
	cout << endl;

	pCat->voice();
	pCat->name();

	pDog->voice();
	pDog->name();
	cout << endl;

	pPet = &cat;
	pPet->voice();
	pPet->name();

	pPet = pDog;
	pPet->voice();
	pPet->name();


	Dog dog1;
	Cat cat1;
	Dog dog2;
	Cat cat2;
	Dog dog3;

	family += dog1;
	family += cat1;
	family += dog2;
	family += cat2;
	family += dog3;

	cout << "Family Pets: " << family << endl;
}

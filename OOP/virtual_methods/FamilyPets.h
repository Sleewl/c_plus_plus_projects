#pragma once
#include "Pet.h"

using namespace std;

#include <iostream>

class FamilyPets {

private:
	int countMax;
	int count;
	const Pet** pett;

public:
	FamilyPets(int countMax);

	void voice() const;
	void name() const;

	FamilyPets& operator+=(const Pet& pet);

	friend bool isInFamilyPets(const FamilyPets& family, const Pet& pet);
	friend ostream& operator<<(ostream& out, const FamilyPets& family);

	~FamilyPets();


};

#include "FamilyPets.h"

#include <iostream>

#include <exception>

using namespace std;

FamilyPets::FamilyPets(int countMaxi) {
	
	pett = new const Pet * [countMaxi];
	countMax = countMaxi;
	count = 0;

}

void FamilyPets::voice() const {
	for (int i = 0; i < count; i++) {
		pett[i]->voice();
	}

}
void FamilyPets::name() const {
	for (int i = 0; i < count; i++) {
		pett[i]->name();
	}

}

FamilyPets& FamilyPets::operator+=(const Pet& pets) {
	if (count < countMax) {
		pett[count] = &pets;
		count++;
	}
	else {
		cerr << "Ошибка, нельзя добавить ещё питомцев" << endl;
		
	}
	return *this;
}

FamilyPets::~FamilyPets() {
	delete[] pett;
	pett = nullptr;
}

bool isInFamilyPets(const FamilyPets& family, const Pet& pet) {
	for (int i = 0; i < family.count; i++) {
		if (family.pett[i] == &pet) {
			cout << typeid(pet).name();
			return true;
		}
	}
	return false;
}
ostream& operator<<(ostream& out, const FamilyPets& family) {
	for (int i = 0; i < family.count; i++) {
		family.pett[i]->name();
		cout << "say: ";
		family.pett[i]->voice();
	}
	return out;
}

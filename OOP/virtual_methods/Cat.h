#pragma once
#include "Pet.h"

#include <string>

class Cat: public Pet {
public:
	virtual void voice() const override;
	virtual void name() const override;

};




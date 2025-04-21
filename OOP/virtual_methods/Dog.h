#pragma once
#include "Pet.h"
class Dog : public Pet{
public:
	virtual void voice() const override;
	virtual void name() const override;

};

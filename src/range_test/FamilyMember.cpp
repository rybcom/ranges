#include "FamilyMember.h"

namespace
{
	int person_usefulness_by_age(int age)
	{
		constexpr int middle_age = 50;
		constexpr int max_age = middle_age * 2;

		if (age <= middle_age)
		{
			return age;
		}
		else if (age < max_age)
		{
			return  max_age - age;
		}
		else
		{
			return 1;
		}

	}

	int person_usefulness_by_owning_car(bool hasCar)
	{
		constexpr int car_usefulness_bonus = 8;

		return hasCar ? car_usefulness_bonus : 0;
	}
}

int FamilyMember::getAwesomeness() const
{
	int sum_usefulness = 0;
	sum_usefulness += getUefulness();
	sum_usefulness += person_usefulness_by_age(_age);
	sum_usefulness += person_usefulness_by_owning_car(_hasOwnCar);

	return sum_usefulness;
}

bool FamilyMember::isEnoughUseful() const
{
	return getAwesomeness() >= FamilyMember::UsefulnessTreshold;
}

bool FamilyMember::operator==(FamilyMember const & rhs) const
{
	return this->getPassportID() == rhs.getPassportID();
}

int FamilyMember::getAwfulness() const
{
	return _crimeScore;
}

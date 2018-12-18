#pragma once

#include "ExportHeader.h"

using PassportID = types::NamedType<int, struct PassportIDType>;
using Usefulness = types::NamedType<int, struct UsefulnessType>;

enum class Sex
{
	Male,
	Female
};

class FAMILYMANAGER_API FamilyMember
{

#pragma region api

public:

	std::size_t getAge() const { return _age; }
	void setAge(std::size_t val) { _age = val; }

	int getPassportID() const { return  _passId; }
	void setPassportID(int val) { _passId = val; }

	std::string getName() const { return name; }
	void setName(std::string val) { name = val; }

	int getUefulness() const { return _uefulness; }
	void setUefulness(int val) { _uefulness = val; }

	int getAwesomeness() const;
	int getAwfulness() const;

	bool isEnoughUseful() const;

	bool HasOwnCar() const { return _hasOwnCar; }
	void setHasOwnCar(bool val) { _hasOwnCar = val; }

	int getCrimeScore() const { return _crimeScore; }
	void setCrimeScore(int val) { _crimeScore = val; }

	Sex getSex() const { return _sex; }
	void setSex(Sex val) { _sex = val; }


	bool operator==(FamilyMember const  & rhs) const;
	

#pragma endregion

#pragma region members

private:

	const static int UsefulnessTreshold = 30;
	std::string name = "empty";
	std::size_t _age = 0;
	int _passId = 0;
	bool _hasOwnCar = false;
	int _uefulness = 0;
	int _crimeScore = 0;
	Sex _sex = Sex::Male;

#pragma endregion


};


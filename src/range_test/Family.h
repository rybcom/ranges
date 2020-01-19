#pragma once
#include <type_traits>
#include <string>
#include <vector>
#include <functional>
#include <numeric>
#include <math.h>
#include <algorithm>
#include <memory>
#include <optional>
#include <xutility>

#include "ranges.h"

#include "FamilyMember.h"

class FamilyMember;

using FamilyMemberPtr = std::unique_ptr<FamilyMember>;
using FamilyMemberRef = std::reference_wrapper<FamilyMember>;
using FamilyMemberList = std::vector<FamilyMember>;


class  Family
{

#pragma region api

public:

	std::optional<FamilyMemberRef> findMember(PassportID passportID) const;

	std::optional<FamilyMemberRef> findMember(FamilyMember member) const;

	std::optional<FamilyMemberRef> appendMemberToFamilyAndGetReference(FamilyMember member);

	bool appendMemberToFamily(FamilyMember member);

	std::optional<FamilyMemberRef> getOldestMember() const;

	std::optional<FamilyMemberRef> getYoungestMember() const;

	int getAwesomeness() const;

	int getAwfulness() const;

	std::size_t getMemberCount() const;
	
	FamilyMemberList const &  getFamilyMemberList() ;



#pragma endregion



#pragma region memebers

private:
	
	FamilyMemberList _members;

#pragma endregion

};


#pragma once
#include "ExportHeader.h"
#include "FamilyMember.h"
#include <type_traits>

class FamilyMember;

using FamilyMemberPtr = std::unique_ptr<FamilyMember>;
using FamilyMemberRef = std::reference_wrapper<FamilyMember>;
using FamilyMemberList = std::vector<FamilyMember>;
using FamilyMemberListRef = std::reference_wrapper<FamilyMemberList>;


class FAMILYMANAGER_API Family
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
	
	FamilyMemberListRef  getFamilyMemberListRef()
	{
		return std::ref(_members);
	}
	
	FamilyMemberList  getFamilyMemberList() ;



#pragma endregion



#pragma region memebers

private:
	
	FamilyMemberList _members;

#pragma endregion

};


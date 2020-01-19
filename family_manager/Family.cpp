#include <algorithm>
#include "Family.h"

namespace
{
	auto compare_person_for_pass_id(PassportID passId)
	{
		return 	[passId](FamilyMember const & mem_a)
		{
			return mem_a.getPassportID() == passId.value;
		};
	}

	auto compare_two_person_for_age()
	{
		return [](FamilyMember const &  member_a, FamilyMember const & member_b) -> bool
		{
			return member_a.getAge() < member_b.getAge();
		};
	}


	auto accumlate_awesomeness_functor = [](int awesomeness, FamilyMember const & mem_a) -> auto
	{
		return mem_a.getAwesomeness() + awesomeness;
	};

	auto accumlate_awfulness_functor = [](int awfulness, FamilyMember const & mem_a) -> auto
	{
		return mem_a.getAwfulness() + awfulness;
	};

}

std::optional<FamilyMemberRef> Family::findMember(FamilyMember member) const
{
	return findMember(PassportID{ member.getPassportID() });
}

std::optional<FamilyMemberRef> Family::findMember(PassportID passportID) const
{
	auto result = _members | views::find_if<FamilyMember>(compare_person_for_pass_id(passportID));

	if_value(result, FamilyMember)
	{
		return *result;
	}

	return {};
}

std::optional<FamilyMemberRef> Family::appendMemberToFamilyAndGetReference(FamilyMember member)
{
	if (appendMemberToFamily(member))
	{
		return findMember(member);
	}

	return {};
}

bool Family::appendMemberToFamily(FamilyMember member)
{
	_members.push_back(member);

	return true;
}

std::optional<FamilyMemberRef> Family::getOldestMember() const
{
	if (_members.size() > 0)
	{
		auto result = _members | views::max_element<FamilyMember>(compare_two_person_for_age());
		return *result;
	}

	return {};
}


std::optional<FamilyMemberRef> Family::getYoungestMember() const
{
	if (_members.size() > 0)
	{

		auto result = _members | views::min_element<FamilyMember>(compare_two_person_for_age());
		return *result;
	}

	return {};
}

int Family::getAwesomeness() const
{
	return ranges::accumulate<int,FamilyMember>(_members, int{ 0 }, accumlate_awesomeness_functor);
}



int Family::getAwfulness() const
{
	return ranges::accumulate<int, FamilyMember>(_members, int{ 0 }, accumlate_awfulness_functor);
}

std::size_t Family::getMemberCount() const
{
	return _members.size();
}


FamilyMemberList const & Family::getFamilyMemberList()
{
	return _members;
}


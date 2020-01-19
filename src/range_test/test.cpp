

#include <iostream>
#include "Family.h"


#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

bool is_male(FamilyMember const& member) { return member.getSex() == Sex::Male; }

std::function<bool(FamilyMember const&)> is_crime_score_under_50 = [](FamilyMember const& member)
{
	return  member.getCrimeScore() < 50;
};
std::function<bool(FamilyMember const&, FamilyMember const&)> compare_by_crime_score = [](FamilyMember const& mem_a, FamilyMember const& mem_b)
{
	return  mem_a.getCrimeScore() < mem_b.getCrimeScore();
};
std::function<std::string(FamilyMember const&)> transform_familymember_to_string = [](FamilyMember const& member)
{
	return  member.getName();
};

TEST_CASE("range testing on family class ")
{

	Family family;

	FamilyMember member;
	member.setAge(12);
	member.setName("Emil");
	member.setPassportID(165342);
	member.setSex(Sex::Male);
	member.setCrimeScore(5);
	family.appendMemberToFamily(member);
	member.setAge(55);
	member.setName("Jonatan");
	member.setPassportID(512324);
	member.setSex(Sex::Male);
	member.setCrimeScore(22);
	family.appendMemberToFamily(member);
	member.setAge(13);
	member.setName("Jozo");
	member.setPassportID(1125342);
	member.setSex(Sex::Male);
	member.setCrimeScore(58);
	family.appendMemberToFamily(member);
	member.setAge(4);
	member.setName("Tomas");
	member.setPassportID(1175343);
	member.setSex(Sex::Male);
	member.setCrimeScore(87);
	family.appendMemberToFamily(member);
	member.setAge(77);
	member.setName("Igor");
	member.setPassportID(2175348);
	member.setSex(Sex::Male);
	member.setCrimeScore(99);
	family.appendMemberToFamily(member);

	SECTION("any_of")
	{
		bool result = family.getFamilyMemberList() | views::any_of<FamilyMember>(
			[](FamilyMember const& member)
			{
				return  member.getAge() > 50;
			});

		REQUIRE(result == true);
	}

	SECTION("all_of")
	{
		bool result = family.getFamilyMemberList() | views::all_of<FamilyMember>(
			[](FamilyMember const& member)
			{
				return  member.getSex() == Sex::Male;
			});
	}

	SECTION("none_of")
	{
		bool result = family.getFamilyMemberList() | views::none_of<FamilyMember>(
			[](FamilyMember const& member)
			{
				return  member.getSex() == Sex::Female;
			});

		REQUIRE(result == true);
	}

	SECTION("filter")
	{
		auto result = family.getFamilyMemberList()
			| views::filter(is_crime_score_under_50)
			| views::transform(transform_familymember_to_string);

		REQUIRE(result.size() == 2);
		REQUIRE(result[0] == "Emil");
		REQUIRE(result[1] == "Jonatan");
	}

	SECTION("count")
	{
		auto result = family.getFamilyMemberList()
			| views::filter<FamilyMember>(std::not_fn(is_crime_score_under_50))
			| views::count<FamilyMember>();
		REQUIRE(result == 3);

	}

	SECTION("count_if")
	{
		auto result = family.getFamilyMemberList()
			| views::count_if<FamilyMember>(std::not_fn(is_crime_score_under_50));

		REQUIRE(result == 3);

	}


	SECTION("for_each")
	{
		auto change_sex_to_female = [](FamilyMember& member)
		{
			member.setSex(Sex::Female);
		};

		family.getFamilyMemberList() | views::for_each<FamilyMember>(change_sex_to_female);
		bool result = family.getFamilyMemberList() | views::all_of<FamilyMember>(std::not_fn(is_male));

		REQUIRE(result == true);
	}


	SECTION("min_element")
	{
		auto result = family.getFamilyMemberList()
			| views::min_element<FamilyMember>(compare_by_crime_score);

		REQUIRE(result->getName() == "Emil");
	}

	SECTION("max_element")
	{
		auto result = family.getFamilyMemberList()
			| views::max_element(compare_by_crime_score);

		REQUIRE(result->getName() == "Igor");


	}

	SECTION("find_if")
	{
		auto result = family.getFamilyMemberList()
			| views::find_if<FamilyMember>([](auto&& member)
				{
					return member.getPassportID() == 2175348;
				});

		REQUIRE(result->getName() == "Igor");

	}

	SECTION("find")
	{
		FamilyMember memberToFind;
		memberToFind.setPassportID(1125342);
		auto result = family.getFamilyMemberList()
			| views::find(memberToFind);

		REQUIRE(result->getName() == "Jozo");
	}



	SECTION("transform")
	{
		auto result = family.getFamilyMemberList()
			| views::transform<FamilyMember, std::string>(transform_familymember_to_string);

		REQUIRE(result.size() == 5);
		REQUIRE(result[0] == "Emil");
		REQUIRE(result[1] == "Jonatan");
		REQUIRE(result[2] == "Jozo");
		REQUIRE(result[3] == "Tomas");
		REQUIRE(result[4] == "Igor");
	}


	SECTION("zip")
	{
		std::vector<int> test_index = { 10,20,30,40,50 };

		auto zip_func = [](FamilyMember const& member, int index) -> std::string
		{
			return member.getName() + " " + std::to_string(index);
		};

		auto result = family.getFamilyMemberList()
			| views::zip<FamilyMember, int, std::string>(test_index, zip_func);

		REQUIRE(result.size() == 5);
		REQUIRE(result[0] == "Emil 10");
		REQUIRE(result[1] == "Jonatan 20");
		REQUIRE(result[2] == "Jozo 30");
		REQUIRE(result[3] == "Tomas 40");
		REQUIRE(result[4] == "Igor 50");
	}


}



TEST_CASE("ranges from map")
{
	FamilyMember member;
	member.setAge(12);
	member.setName("Emil");
	member.setPassportID(165342);
	member.setSex(Sex::Male);
	member.setCrimeScore(5);
	FamilyMember member2;
	member2.setAge(55);
	member2.setName("Jonatan");
	member2.setPassportID(512324);
	member2.setSex(Sex::Male);
	member2.setCrimeScore(66);

	std::map<int, FamilyMember> list = { {165342,member},{512324,member2} };
	auto result = list | views::filter(is_crime_score_under_50) | views::get_first<FamilyMember>();

	REQUIRE(result->getName() == "Emil");
}


TEST_CASE("ranges from unordered map")
{
	FamilyMember member;
	member.setAge(12);
	member.setName("Emil");
	member.setPassportID(165342);
	member.setSex(Sex::Female);
	member.setCrimeScore(5);
	FamilyMember member2;
	member2.setAge(55);
	member2.setName("Justin");
	member2.setPassportID(512324);
	member2.setSex(Sex::Male);
	member2.setCrimeScore(66);
	std::unordered_map<int, FamilyMember> list = { {165342,member},{512324,member2} };
	auto result = list | views::filter(is_male) | views::get_first<FamilyMember>();

	REQUIRE(result->getName() == "Justin");
}




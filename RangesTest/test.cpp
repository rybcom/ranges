#include "pch.h"


class ViewsOnFamily : public testing::Test
{
protected:

	std::function<bool(FamilyMember const &)> is_crime_score_under_50 = [](FamilyMember const & member)
	{
		return  member.getCrimeScore() < 50;
	};

	std::function<bool(FamilyMember const &, FamilyMember const &)> compare_by_crime_score = [](FamilyMember const & mem_a, FamilyMember const & mem_b)
	{
		return  mem_a.getCrimeScore() < mem_b.getCrimeScore();
	};

	std::function<std::string(FamilyMember const &)> transform_familymember_to_string = [](FamilyMember const & member)
	{
		return  member.getName();
	};

	void SetUp() override
	{
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
	}

	Family family;
};

TEST_F(ViewsOnFamily, any_of)
{
	bool result = family.getFamilyMemberListRef().get() | views::any_of<FamilyMember>(
		[](FamilyMember const & member)
	{
		return  member.getAge() > 50;
	});

	EXPECT_TRUE(result);
}

TEST_F(ViewsOnFamily, all_of)
{
	bool result = family.getFamilyMemberListRef().get() | views::all_of<FamilyMember>(
		[](FamilyMember const & member)
	{
		return  member.getSex() == Sex::Male;
	});

	EXPECT_TRUE(result);
}

TEST_F(ViewsOnFamily, none_of)
{
	bool result = family.getFamilyMemberListRef().get() | views::none_of<FamilyMember>(
		[](FamilyMember const & member)
	{
		return  member.getSex() == Sex::Female;
	});

	EXPECT_TRUE(result);
}

TEST_F(ViewsOnFamily, filter)
{
	auto result = family.getFamilyMemberListRef().get()
		| views::filter<FamilyMember>(is_crime_score_under_50)
		| views::transform<FamilyMember, std::string>(transform_familymember_to_string);


	EXPECT_EQ(result.size(), 2);
	EXPECT_TRUE(result[0] == "Emil" || result[1] == "Emil");
	EXPECT_TRUE(result[0] == "Jonatan" || result[1] == "Jonatan");

}

TEST_F(ViewsOnFamily, count)
{
	auto result = family.getFamilyMemberListRef().get()
		| views::filter<FamilyMember>(std::not_fn(is_crime_score_under_50))
		| views::count<FamilyMember>();

	EXPECT_EQ(result, 3);

}

TEST_F(ViewsOnFamily, count_if)
{
	auto result = family.getFamilyMemberListRef().get()
		| views::count_if<FamilyMember>(std::not_fn(is_crime_score_under_50));

	EXPECT_EQ(result, 3);

}

TEST_F(ViewsOnFamily, for_each)
{
	auto change_sex_to_female = [](FamilyMember & member)
	{
		member.setSex(Sex::Female);
	};

	// i prefer use ranges for this rather than views
	family.getFamilyMemberListRef().get() | views::for_each<FamilyMember>(change_sex_to_female);

	bool result = family.getFamilyMemberListRef().get() | views::all_of<FamilyMember>(
		[](FamilyMember const & member)
	{
		return  member.getSex() == Sex::Female;
	});

	EXPECT_TRUE(result);
}

TEST_F(ViewsOnFamily, min_element)
{
	auto result = family.getFamilyMemberListRef().get()
		| views::min_element<FamilyMember>(compare_by_crime_score);

	EXPECT_EQ(result->getName(), "Emil");
}

TEST_F(ViewsOnFamily, max_element)
{
	auto result = family.getFamilyMemberListRef().get()
		| views::max_element<FamilyMember>(compare_by_crime_score);

	EXPECT_EQ(result->getName(), "Igor");
}

TEST_F(ViewsOnFamily, find_if)
{
	auto result = family.getFamilyMemberListRef().get()
		| views::find_if<FamilyMember>([](FamilyMember const & member)
	{
		return member.getCrimeScore() > 50 && member.getAge() > 70;
	});


	EXPECT_EQ(result->getName(), "Igor");
}


TEST_F(ViewsOnFamily, find)
{
	FamilyMember memberToFind;
	memberToFind.setPassportID(1125342);

	auto result = family.getFamilyMemberListRef().get()
		| views::find(memberToFind);


	EXPECT_EQ(result->getName(), "Jozo");
}

TEST_F(ViewsOnFamily, transform)
{
	auto result = family.getFamilyMemberListRef().get()
		| views::transform<FamilyMember, std::string>(transform_familymember_to_string);

	EXPECT_EQ(result.size(), 5);
	EXPECT_EQ(result[0], "Emil");
	EXPECT_EQ(result[1], "Jonatan");
	EXPECT_EQ(result[2], "Jozo");
	EXPECT_EQ(result[3], "Tomas");
	EXPECT_EQ(result[4], "Igor");
}

TEST_F(ViewsOnFamily, zip)
{

	std::vector<int> test_index = { 10,20,30,40,50 };
	auto zip_func = [](FamilyMember const & member, int index) -> std::string
	{
		return member.getName() + " " + std::to_string(index);
	};

	auto result = family.getFamilyMemberListRef().get()
		| views::zip<FamilyMember, int, std::string>(test_index, zip_func);

	EXPECT_EQ(result.size(), 5);
	EXPECT_EQ(result[0], "Emil 10");
	EXPECT_EQ(result[1], "Jonatan 20");
	EXPECT_EQ(result[2], "Jozo 30");
	EXPECT_EQ(result[3], "Tomas 40");
	EXPECT_EQ(result[4], "Igor 50");
}
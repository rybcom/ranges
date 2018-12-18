

#include "pch.h"
#include "stdafx.h"


class FamilyQueryTest : public testing::Test
{
protected:

	void SetUp() override
	{
		FamilyMember member;

		member.setAge(12);
		member.setName("Emil");
		member.setPassportID(125342);

		family.appendMemberToFamily(member);

		member.setAge(55);
		member.setName("Jonatan");
		member.setPassportID(512324);

		family.appendMemberToFamily(member);

		member.setAge(13);
		member.setName("Jozo");
		member.setPassportID(1125342);

		family.appendMemberToFamily(member);

		member.setAge(4);
		member.setName("Tomas");
		member.setPassportID(1175343);

		family.appendMemberToFamily(member);
	}

	Family family;
};

TEST(FamilyPopupating, NoFamilyMembersIsZeroCount) {
	Family family;
	EXPECT_EQ(family.getMemberCount(), 0);
}

TEST(FamilyPopupating, AddOneMemberToFamily) {
	Family family;
	FamilyMember member;
	member.setAge(12);
	member.setName("Emil");
	member.setPassportID(125342);

	family.appendMemberToFamilyAndGetReference(member);

	EXPECT_EQ(family.getMemberCount(), 1);
}

TEST(FamilyPopupating, OneMemberTest) {
	Family family;

	FamilyMember member;
	member.setAge(12);
	member.setName("Igor");
	member.setPassportID(125342);

	family.appendMemberToFamily(member);

	auto result_old = family.getOldestMember();
	auto result_young = family.getYoungestMember();
	auto count = family.getMemberCount();

	EXPECT_EQ(result_old->get().getName(), "Igor");
	EXPECT_EQ(result_young->get().getName(), "Igor");
	EXPECT_EQ(count, 1);
}

TEST_F(FamilyQueryTest, GetOldestMember) {

	auto oldestMember = family.getOldestMember();

	EXPECT_TRUE(oldestMember.has_value());

	if (oldestMember.has_value())
	{
		EXPECT_EQ(oldestMember->get().getName(), "Jonatan");
	}
}

TEST_F(FamilyQueryTest, GetYoungestMember) {

	auto youngestMember = family.getYoungestMember();

	EXPECT_TRUE(youngestMember.has_value());

	if (youngestMember.has_value())
	{
		EXPECT_EQ(youngestMember->get().getName(), "Tomas");
	}
}

TEST_F(FamilyQueryTest, GetOldestMember_NoMember) {

	Family emptyfamily;
	auto result = emptyfamily.getOldestMember();
	EXPECT_FALSE(result.has_value());
}

TEST_F(FamilyQueryTest, FindMember_NoMatch) {

	FamilyMember member;
	member.setPassportID(2112);


	auto result_findByMember = family.findMember(member);
	auto result_findByPassID = family.findMember(PassportID{ member.getPassportID() });

	EXPECT_FALSE(result_findByMember.has_value());
	EXPECT_FALSE(result_findByPassID.has_value());

}

TEST_F(FamilyQueryTest, FindMember_OneMatch) {

	FamilyMember member;
	member.setPassportID(512324);

	auto result_findByMember = family.findMember(member);
	auto result_findByPassID = family.findMember(PassportID{ member.getPassportID() });

	EXPECT_TRUE(result_findByMember.has_value());
	EXPECT_TRUE(result_findByPassID.has_value());

	if (result_findByMember.has_value())
	{
		EXPECT_EQ(result_findByMember->get().getPassportID(), 512324);
		EXPECT_EQ(result_findByMember->get().getName(), "Jonatan");
	}
	if (result_findByPassID.has_value())
	{
		EXPECT_EQ(result_findByPassID->get().getPassportID(), 512324);
		EXPECT_EQ(result_findByPassID->get().getName(), "Jonatan");
	}
}

TEST(FamilyOverall, FamilyAwesomeness){
	Family family;

	FamilyMember tomas;
	tomas.setAge(10);
	tomas.setUefulness(20);
	tomas.setHasOwnCar(false);
	//10 + 20 + 0 = 30

	FamilyMember emil;
	emil.setAge(55);
	emil.setUefulness(5);
	emil.setHasOwnCar(true);
	//45+5+8 = 58

	family.appendMemberToFamily(emil);
	family.appendMemberToFamily(tomas);

	EXPECT_EQ(family.getAwesomeness(), 88);

}

TEST(FamilyOverall, FamilyAwfulness){
	Family family;

	FamilyMember tomas;
	tomas.setAge(10);
	tomas.setUefulness(20);
	tomas.setHasOwnCar(false);
	tomas.setCrimeScore(45);
	//10 + 20 + 0 = 30

	FamilyMember emil;
	emil.setAge(55);
	emil.setUefulness(5);
	emil.setHasOwnCar(true);
	emil.setCrimeScore(5);

	//45+5+8 = 58

	family.appendMemberToFamily(emil);
	family.appendMemberToFamily(tomas);

	EXPECT_EQ(family.getAwfulness(), 50);

}



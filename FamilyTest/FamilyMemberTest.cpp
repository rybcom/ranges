

#include "pch.h"
#include "stdafx.h"

class FamiltyMemberTest : public testing::Test
{
protected:

	void SetUp() override {

	}
	FamilyMember member_a;
	FamilyMember member_b;
	FamilyMember member_c;

};

TEST_F(FamiltyMemberTest, Constructor)
{
	EXPECT_EQ(member_a.getAge(), 0);
	EXPECT_EQ(member_a.getPassportID(), 0);
	EXPECT_EQ(member_a.getUefulness(), 0);
}

TEST_F(FamiltyMemberTest, IsMemberEnoughUseful)
{
	member_a.setUefulness(2);
	member_a.setAge(20);
	member_a.setHasOwnCar(true);

	member_b.setUefulness(12);
	member_b.setAge(12);
	member_b.setHasOwnCar(false);

	member_c.setUefulness(9);
	member_c.setAge(80);
	member_c.setHasOwnCar(false);


	EXPECT_TRUE(member_a.isEnoughUseful());
	EXPECT_FALSE(member_b.isEnoughUseful());
	EXPECT_FALSE(member_c.isEnoughUseful());
}


TEST_F(FamiltyMemberTest, EqualOperator)
{
	member_a.setPassportID(1123);
	member_b.setPassportID(1123);
	member_c.setPassportID(312);

	EXPECT_TRUE(member_a == member_b);
	EXPECT_FALSE(member_a == member_c);
	EXPECT_FALSE(member_b == member_c);
}
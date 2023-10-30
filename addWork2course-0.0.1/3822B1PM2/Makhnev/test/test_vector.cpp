#include "gtest.h"
#include "tvector.h"
TEST(TVector, can_create_vector)
{
	size_t length1 = 100;
	ASSERT_NO_THROW(Vector<int> v(length1););
}
TEST(TVector, can_add_element)
{
	Vector<int> v;
	ASSERT_NO_THROW(v.push_back(1));
}
TEST(TVector, is_added_element_correct)
{
	Vector<int> v;
	v.push_back(1);
	ASSERT_EQ(v[0], 1);
}
TEST(TVector, can_insert_element)
{
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	ASSERT_NO_THROW(v.insert(1, 5));
}
TEST(TVector, is_inserted_element_correct)
{
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.insert(1, 5);
	Vector<int> v2(3);
	v2[0] = 1;
	v2[1] = 5;
	v2[2] = 2;
	ASSERT_EQ(v, v2);
}
TEST(TVector, is_getSize_correct)
{
	Vector<int> v(3);
	ASSERT_EQ(v.getSize(), 3);
}
TEST(TVector, is_erase_correct)
{
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(5);
	v.erase(1);
	Vector<int> v2(2);
	v2[0] = 1;
	v2[1] = 5;
	ASSERT_EQ(v, v2);
}
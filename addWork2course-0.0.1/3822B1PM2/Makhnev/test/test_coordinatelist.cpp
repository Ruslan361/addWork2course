#include <iostream>
#include "gtest.h"
#include "tcoordinatelist.h"
#include "tmatrix.h"


TEST(TCoordinateList, can_init_by_TDynamicMatrix) 
{
	TDynamicMatrix<int> matrix(10);
	matrix[0][0] = 10;
	ASSERT_NO_THROW(TCoordinateList<int> matrix2(matrix));
}
TEST(TCoordinateList, can_set_elment)
{
	TCoordinateList<int> matrix(10);
	ASSERT_NO_THROW(matrix.set(1, 0, 0));
}
TEST(TCoordinateList, is_established_elments_correct)
{
	TCoordinateList<int> matrix(10);
	matrix.set(1, 3, 2);
	matrix.set(2, 0, 0);
	matrix.set(3, 2, 5);
	matrix.set(10, 0, 0);
	ASSERT_EQ(matrix.get(3, 2), 1);
	ASSERT_EQ(matrix.get(0, 0), 10);
	ASSERT_EQ(matrix.get(2, 5), 3);
}
TEST(TCoordinateList, can_multiple_vector_with_matrix)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	//std::cout << vector << std::endl;
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j)%2;
		}
	}
	/*std::cout << std::endl << matrix << std::endl;
	std::cout << matrix * vector << std::endl;*/
	ASSERT_NO_THROW(matrix * vector);
}
//TEST(TCoordinateList, is_multiplication_vector_with_matrix)
//{
//	TDynamicVector<int> vector(3);
//	for (size_t i = 0; i < 3; i++)
//	{
//		vector[i] = i;
//	}
//	//std::cout << vector << std::endl;
//	TDynamicMatrix<int> matrix(3);
//	for (size_t i = 0; i < 3; i++)
//	{
//		for (size_t j = 0; j < 3; j++)
//		{
//			matrix[i][j] = (3 * i + j) % 2;
//		}
//	}
//	/*std::cout << std::endl << matrix << std::endl;
//	std::cout << matrix * vector << std::endl;*/
//	ASSERT_NO_THROW(matrix * vector);
//}
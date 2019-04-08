#define BOOST_TEST_MODULE Vector3d test
#include "boost/test/included/unit_test.hpp"
#include "enhance/vector3d.hpp"
#include <cmath>



BOOST_AUTO_TEST_SUITE(Vector3d)



BOOST_AUTO_TEST_CASE(ConstructorDefaultTest)
{
    {
        auto float_default = enhance::Vector3d<float>();
        BOOST_CHECK_LE(float_default(0), 1e-5);
        BOOST_CHECK_LE(float_default(1), 1e-5);
        BOOST_CHECK_LE(float_default(2), 1e-5);
    }
    {
        auto int_default = enhance::Vector3d<int>();
        BOOST_CHECK_EQUAL(int_default(0), 0);
        BOOST_CHECK_EQUAL(int_default(1), 0);
        BOOST_CHECK_EQUAL(int_default(2), 0);
    }
}


    
BOOST_AUTO_TEST_CASE(ConstructorSingleTest)
{
    {
        auto float_single = enhance::Vector3d<float>(1);
        BOOST_CHECK_LE(std::abs(float_single(0)-1), 1e-5);
        BOOST_CHECK_LE(std::abs(float_single(1)-1), 1e-5);
        BOOST_CHECK_LE(std::abs(float_single(2)-1), 1e-5);
    }
    {
        auto int_single = enhance::Vector3d<int>(2);
        BOOST_CHECK_EQUAL(int_single(0), 2);
        BOOST_CHECK_EQUAL(int_single(1), 2);
        BOOST_CHECK_EQUAL(int_single(2), 2);
    }
}


    
BOOST_AUTO_TEST_CASE(ConstructorTripleTest)
{
    {
        auto float_triple = enhance::Vector3d<float>(1, 0.5, -2.3);
        BOOST_CHECK_LE(std::abs(float_triple(0)-1  ), 1e-5);
        BOOST_CHECK_LE(std::abs(float_triple(1)-0.5), 1e-5);
        BOOST_CHECK_LE(std::abs(float_triple(2)+2.3), 1e-5);
    }
    {
        auto int_triple = enhance::Vector3d<int>(2, 1, -4);
        BOOST_CHECK_EQUAL(int_triple(0),  2);
        BOOST_CHECK_EQUAL(int_triple(1),  1);
        BOOST_CHECK_EQUAL(int_triple(2), -4);
    }
}


    
BOOST_AUTO_TEST_CASE(ConstructorTypecastTest)
{
    {
        auto float_triple = enhance::Vector3d<float>(1, 0.5, -2.3);
        enhance::Vector3d<int> int_vector(float_triple);
        BOOST_CHECK_EQUAL(int_vector(0),  1);
        BOOST_CHECK_EQUAL(int_vector(1),  0);
        BOOST_CHECK_EQUAL(int_vector(2), -2);
    }
}


    
BOOST_AUTO_TEST_CASE(ConstructorCopyTest)
{
    {
        const enhance::Vector3d<int> int_origin(1, 0, -2);
        const enhance::Vector3d<int> int_copy(int_origin);
        BOOST_CHECK_EQUAL(int_origin(0), int_copy(0));
        BOOST_CHECK_EQUAL(int_origin(1), int_copy(1));
        BOOST_CHECK_EQUAL(int_origin(2), int_copy(2));
    }
    {
        const enhance::Vector3d<int> int_origin(1, 0, -2);
        const enhance::Vector3d<int> int_copy = int_origin;
        BOOST_CHECK_EQUAL(int_origin(0), int_copy(0));
        BOOST_CHECK_EQUAL(int_origin(1), int_copy(1));
        BOOST_CHECK_EQUAL(int_origin(2), int_copy(2));
    }
}



BOOST_AUTO_TEST_CASE(UnaryTests)
{
    {
        enhance::Vector3d<int> int_origin(1, 0, -2);
        int_origin.unaryApply([](int& i){ return -i;});
        BOOST_CHECK_EQUAL(int_origin(0), -1);
        BOOST_CHECK_EQUAL(int_origin(1),  0);
        BOOST_CHECK_EQUAL(int_origin(2),  2);
    }
    {
        const enhance::Vector3d<int> int_origin(1, 0, -2);
        const auto int_copy = int_origin.unaryExpr([](const int& i){ return -i;});
        BOOST_CHECK_EQUAL(int_origin(0), -int_copy(0));
        BOOST_CHECK_EQUAL(int_origin(1), -int_copy(1));
        BOOST_CHECK_EQUAL(int_origin(2), -int_copy(2));
    }
}



BOOST_AUTO_TEST_CASE(ArithmeticTests)
{
    {
        enhance::Vector3d<int> a(1, -3, 2);
        enhance::Vector3d<int> b(3, 2, -1);
        BOOST_CHECK_EQUAL((a+b)(0),  4);
        BOOST_CHECK_EQUAL((a+b)(1), -1);
        BOOST_CHECK_EQUAL((a+b)(2),  1);
    }
    {
        enhance::Vector3d<int> a(1, -3, 2);
        enhance::Vector3d<int> b(3, 2, -1);
        BOOST_CHECK_EQUAL((a-b)(0), -2);
        BOOST_CHECK_EQUAL((a-b)(1), -5);
        BOOST_CHECK_EQUAL((a-b)(2),  3);
    }
    {
        enhance::Vector3d<int> a(1, -3, 2);
        enhance::Vector3d<int> b(3, 2, -1);
        a += b;
        BOOST_CHECK_EQUAL(a(0),  4);
        BOOST_CHECK_EQUAL(a(1), -1);
        BOOST_CHECK_EQUAL(a(2),  1);
    }
    {
        enhance::Vector3d<int> a(1, -3, 2);
        enhance::Vector3d<int> b(3, 2, -1);
        a -= b;
        BOOST_CHECK_EQUAL(a(0), -2);
        BOOST_CHECK_EQUAL(a(1), -5);
        BOOST_CHECK_EQUAL(a(2),  3);
    }
}



BOOST_AUTO_TEST_CASE(VectorArithmeticTests)
{
    {
        enhance::Vector3d<int> a(3, 0, -4);
        BOOST_CHECK_LE(a.norm()-5, 1e-5);
    }
    {
        enhance::Vector3d<int> a(1, -3, 2);
        enhance::Vector3d<int> b(3, 2, -1);
        BOOST_CHECK_EQUAL(a.dot(b), -5);
    }
    {
        enhance::Vector3d<int> a(1, -3, 2);
        enhance::Vector3d<int> b(3, 2, -1);
        const auto cross = a.cross(b);
        BOOST_CHECK_EQUAL(cross(0), -1);
        BOOST_CHECK_EQUAL(cross(1),  7);
        BOOST_CHECK_EQUAL(cross(2), 11);
    }
}



BOOST_AUTO_TEST_SUITE_END()
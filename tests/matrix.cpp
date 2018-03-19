#include "catch.hpp"
#include <sstream>
#include "matrix.hpp"
using namespace std;

TEST_CASE("creating matrix")
{
    matrix_t <int> matrix;
    REQUIRE( matrix.Get_Stroki() == 0 );
    REQUIRE( matrix.Get_Stolbi() == 0 );
}

TEST_CASE("reading matrix")
{
    string input{
        "3,3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t<int> matrix;
    istringstream istream{ input };
    
    REQUIRE( matrix.read( istream ) );
    REQUIRE( matrix.Get_Stroki()== 3 );
    REQUIRE( matrix.Get_Stolbi() == 3 );
    
    ostringstream ostream;
    matrix.write( ostream );
    
    REQUIRE( input == ostream.str() );
}

TEST_CASE("= matrix")
{
    string input{
        "3,3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t<int> matrix;
    istringstream istream{ input };
    REQUIRE( matrix.read( istream ) );
    matrix_t<int> copy;
    copy=matrix;
    REQUIRE( copy.Get_Stroki()== 3 );
    REQUIRE( copy.Get_Stolbi() == 3 );
    REQUIRE_NOTHROW( matrix.Get_Stolbi() == copy.Get_Stolbi() && matrix.Get_Stroki() == copy.Get_Stroki() );
    
    ostringstream ostream;
    matrix.write( ostream );
    
    REQUIRE( input == ostream.str() );
}

TEST_CASE("add matrix")
{
    string input1{
        "3,3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t<int> matrix1;
    istringstream istream1{ input1 };
    string input2{
        "3,3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t<int> matrix2;
    istringstream istream2{ input2 };
    string input3{
        "3,3\n"
        "2 2 2\n"
        "4 4 4\n"
        "6 6 6" };
    matrix_t<int> matrix3;
    istringstream istream3{ input3 };
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    
    REQUIRE( matrix1.Get_Stroki()== 3 );
    REQUIRE( matrix1.Get_Stolbi() == 3 );
    
    REQUIRE( matrix2.Get_Stroki()== 3 );
    REQUIRE( matrix2.Get_Stolbi() == 3 );
    
    matrix3=matrix1+matrix2;
    
    REQUIRE( matrix3.Get_Stroki()== 3 );
    REQUIRE( matrix3.Get_Stolbi() == 3 );
    
    
    
    REQUIRE_NOTHROW( matrix1.Get_Stolbi() == matrix2.Get_Stolbi() && matrix1.Get_Stroki() == matrix2.Get_Stroki() );
    
    ostringstream ostream;
    matrix3.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}
TEST_CASE("a-b matrix")
{
    string input1{
        "3,3\n"
        "1.1 1.1 1.1\n"
        "2.2 2.2 2.2\n"
        "3.3 3.3 3.3" };
    matrix_t<float> matrix1;
    istringstream istream1{ input1 };
    string input2{
        "3,3\n"
        "4 4 4\n"
        "5 5 5\n"
        "2 2 2" };
    matrix_t<float> matrix2;
    istringstream istream2{ input2 };
    string input3{
        "3,3\n"
        "-2.9 -2.9 -2.9\n"
        "-2.8 -2.8 -2.8\n"
        "1.3 1.3 1.3" };
    matrix_t<float> matrix3;
    istringstream istream3{ input3 };
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    matrix3=matrix1-matrix2;
    REQUIRE( matrix3.Get_Stroki()== 3 );
    REQUIRE( matrix3.Get_Stolbi() == 3 );
    
    REQUIRE( matrix1.Get_Stroki()== 3 );
    REQUIRE( matrix1.Get_Stolbi() == 3 );
    
    REQUIRE( matrix2.Get_Stroki()== 3 );
    REQUIRE( matrix2.Get_Stolbi() == 3 );
    
    REQUIRE_NOTHROW( matrix1.Get_Stolbi() == matrix2.Get_Stolbi() && matrix1.Get_Stroki() == matrix2.Get_Stroki() );
    
    ostringstream ostream;
    matrix3.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}
TEST_CASE("a*b matrix")
{
    string input1{
        "3,3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t<int> matrix1;
    istringstream istream1{ input1 };
    string input2{
        "3,1\n"
        "4\n"
        "5\n"
        "2" };
    matrix_t <int> matrix2;
    istringstream istream2{ input2 };
    string input3{
        "3,1\n"
        "11 \n"
        "22 \n"
        "33 " };
    matrix_t<int> matrix3;
    istringstream istream3{ input3 };
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    
    REQUIRE( matrix1.Get_Stroki()== 3 );
    REQUIRE( matrix1.Get_Stolbi() == 3 );
    
    REQUIRE( matrix2.Get_Stroki()== 3 );
    REQUIRE( matrix2.Get_Stolbi() == 1);
    
    matrix3=matrix1*matrix2;
    
    REQUIRE( matrix3.Get_Stroki()== 3 );
    REQUIRE( matrix3.Get_Stolbi() == 1 );
    
    REQUIRE_NOTHROW( matrix1.Get_Stolbi() == matrix2.Get_Stroki() );
    
    ostringstream ostream;
    matrix3.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}

TEST_CASE("a*=b matrix")
{
    string input1{
        "3,3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t<int> matrix1;
    istringstream istream1{ input1 };
    string input2{
        "3,2\n"
        "4 6\n"
        "5 3\n"
        "2 7" };
    matrix_t<int> matrix2;
    istringstream istream2{ input2 };
    string input3{
        "3,2\n"
        "11 16 \n"
        "22 32 \n"
        "33 48 " };
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    matrix1*=matrix2;
    REQUIRE( matrix1.Get_Stroki()== 3 );
    REQUIRE( matrix1.Get_Stolbi() == 2 );
    
    ostringstream ostream;
    matrix1.write( ostream );
    REQUIRE_NOTHROW( matrix1.Get_Stolbi() == matrix2.Get_Stroki() );
    REQUIRE( input3 == ostream.str());
}

TEST_CASE("a+=b matrix")
{
    string input1{
        "3,3\n"
        "1.1 1.1 1.1\n"
        "2.1 2.1 2.1\n"
        "3.1 3.1 3.1" };
    matrix_t<float> matrix1;
    istringstream istream1{ input1 };
    string input2{
        "3,3\n"
        "4 6 1\n"
        "5 3 4\n"
        "2 7 3" };
    matrix_t <float>matrix2;
    istringstream istream2{ input2 };
    string input3{
        "3,3\n"
        "5.1 7.1 2.1\n"
        "7.1 5.1 6.1\n"
        "5.1 10.1 6.1" };
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    
    REQUIRE_NOTHROW( matrix1.Get_Stolbi() == matrix2.Get_Stolbi() && matrix1.Get_Stroki() == matrix2.Get_Stroki() );
    
    matrix1+=matrix2;
    REQUIRE( matrix1.Get_Stroki()== 3 );
    REQUIRE( matrix1.Get_Stolbi() == 3 );
    
    ostringstream ostream;
    matrix1.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}

TEST_CASE("a-=b matrix")
{
    string input1{
        "3,3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t<int> matrix1;
    istringstream istream1{ input1 };
    string input2{
        "3,3\n"
        "4 6 1\n"
        "5 3 4\n"
        "2 7 3" };
    matrix_t<int> matrix2;
    istringstream istream2{ input2 };
    string input3{
        "3,3\n"
        "-3 -5 0\n"
        "-3 -1 -2\n"
        "1 -4 0" };
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    
    REQUIRE_NOTHROW( matrix1.Get_Stolbi() == matrix2.Get_Stolbi() && matrix1.Get_Stroki() == matrix2.Get_Stroki() );
    
    matrix1-=matrix2;
    REQUIRE( matrix1.Get_Stroki()== 3 );
    REQUIRE( matrix1.Get_Stolbi() == 3 );
    
    ostringstream ostream;
    matrix1.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}


#include "rna.h"
#include <string>
#include "gtest/gtest.h"

using namespace std;

rna creation(const string &str_of_nucl)
{
    rna rna;
    for (char i: str_of_nucl)
    {
        switch (i)
        {
            case 'A':
                rna.push(A);
                break;
            case 'G':
                rna.push(G);
                break;
            case 'C':
                rna.push(C);
                break;
            case 'T':
                rna.push(T);
            default:
                break;
        }
    }
    return rna;
}

TEST(rna, test_1)/* NOLINT */
{
    rna r1;
    rna r2;
    EXPECT_EQ(true, r1 == r2);
}

TEST(rna, test_2)/* NOLINT */
{
    rna r1(A, 10);
    rna r2(A, 10);
    EXPECT_EQ(true, r1 == r2);
}

TEST(rna, test_3)/* NOLINT */
{
    rna r1(A, 10);
    rna r2(C, 10);
    EXPECT_EQ(false, r1 == r2);
}

TEST(rna, test_4)/* NOLINT */
{
    rna r1(A, 10);
    rna r2(A, 20);
    EXPECT_EQ(false, r1 == r2);
}

TEST(rna, test_5)/* NOLINT */
{
    rna r1(A, 10);
    rna r2(r1);
    EXPECT_EQ(true, r1 == r2);
}

TEST(push, test_1)/* NOLINT */
{
    rna r1;
    r1.push(A);
    rna r2(A, 1);
    EXPECT_EQ(true, r1 == r2);
}

TEST(push, test_2)/* NOLINT */
{
    rna r1;
    r1.push(A);
    rna r2 = creation("A");
    EXPECT_EQ(true, r1 == r2);
}

TEST(push, test_3)/* NOLINT */
{
    rna r1(A, 10);
    r1.push(9, C);
    rna r2 = creation("AAAAAAAAAC");
    EXPECT_EQ(true, r1 == r2);
}

TEST(push, test_4)/* NOLINT */
{
    rna r1(A, 10);
    r1.push(10, C);
    rna r2 = creation("AAAAAAAAAA");
    EXPECT_EQ(true, r1 == r2);
}

TEST(push, test_5)/* NOLINT */
{
    rna r1(A, 10);
    r1.push(16, C);
    rna r2 = creation("AAAAAAAAAA");
    EXPECT_EQ(true, r1 == r2);
}

TEST(pop, test_1)/* NOLINT */
{
    rna r1(A, 1000);
    r1.pop();
    rna r2(A, 999);
    EXPECT_EQ(true, r1 == r2);
}

TEST(pop, test_2)/* NOLINT */
{
    rna r1(A, 1);
    r1.pop();
    rna r2;
    EXPECT_EQ(true, r1 == r2);
}

TEST(get_size, test_1)/* NOLINT */
{
    rna r1(A, 1000);
    EXPECT_EQ(true, r1.get_size() == 1000);
}

TEST(get_size, test_2)/* NOLINT */
{
    rna r1(A, 1000);
    rna r2(A, 1000);
    EXPECT_EQ(true, r1.get_size() == r2.get_size());
}

TEST(get_size, test_3)/* NOLINT */
{
    rna r1(A, 1001);
    rna r2(A, 1000);
    EXPECT_EQ(true, r1.get_size() != r2.get_size());
}

TEST(get_size, test_4)/* NOLINT */
{
    rna r1;
    EXPECT_EQ(true, r1.get_size() == 0);
}

TEST(get_capacity, test_1)/* NOLINT */
{
    rna r1;
    EXPECT_EQ(true, r1.get_capacity() == 4);
}

TEST(get_capacity, test_2)/* NOLINT */
{
    rna r1(A, 4);
    EXPECT_EQ(true, r1.get_capacity() == 4);
}

TEST(get_capacity, test_3)/* NOLINT */
{
    rna r1(A, 5);
    EXPECT_EQ(true, r1.get_capacity() == 8);
}

TEST(get_capacity, test_4)/* NOLINT */
{
    rna r1(A, 5);
    r1.pop();
    EXPECT_EQ(true, r1.get_capacity() == 4);
}

TEST(get_capacity, test_5)/* NOLINT */
{
    rna r1(A, 1000);
    rna r2(A, 1000);
    EXPECT_EQ(true, r1.get_capacity() == r2.get_capacity());
}

TEST(print_rna, test_1)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    r1.print_rna();
}

TEST(square_brackets, test_1)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    r1[3] = A;
    rna r2 = creation("AGCACGA");
    EXPECT_EQ(true, r1 == r2);
}

TEST(square_brackets, test_2)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    r1[3] = r1[0];
    rna r2 = creation("AGCACGA");
    EXPECT_EQ(true, r1 == r2);
}

TEST(square_brackets, test_3)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    rna r2 = creation("AGCACGA");
    r1[3] = r2[3];
    EXPECT_EQ(true, r1 == r2);
}

TEST(square_brackets, test_4)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    cout << (unsigned int)(nucl)r1[3] << endl;
}

TEST(square_brackets, test_5)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    r1[3] = A;
    cout << (unsigned int)(nucl)r1[3] << endl;
}

TEST(assignment, test_1)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    rna r2;
    r2 = r1;
    EXPECT_EQ(true, r1 == r2);
}

TEST(assignment, test_2)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    rna r2;
    r1 = r2;
    EXPECT_EQ(true, r1 == r2);
}

TEST(plus, test_1)/* NOLINT */
{
    rna r1 = creation("AGCT");
    rna r2 = creation("AAAA");
    rna r3 = r1 + r2;
    rna r4 = creation("AGCTAAAA");
    EXPECT_EQ(true, r3 == r4);
}

TEST(plus, test_2)/* NOLINT */
{
    rna r1 = creation("AGCT");
    rna r2 = creation("AAAA");
    r1 = r1 + r2;
    rna r3 = creation("AGCTAAAA");
    EXPECT_EQ(true, r1 == r3);
}

TEST(negation, test_1)/* NOLINT */
{
    rna r1 = creation("AGCT");
    !r1;
    rna r2 = creation("TCGA");
    EXPECT_EQ(true, r1 == r2);
}

TEST(negation, test_2)/* NOLINT */
{
    rna r1 = creation("AGCT");
    rna r2;
    r2 = !r1;
    rna r3 = creation("TCGA");
    EXPECT_EQ(true, r2 == r3);
}

TEST(comparison, test_1)/* NOLINT */
{
    rna r1 = creation("AGCT");
    rna r2;
    r2 = r1;
    bool tmp;
    if (r1 == r2)
        tmp = true;
    EXPECT_EQ(true, tmp);
}

TEST(comparison, test_2)/* NOLINT */
{
    rna r1 = creation("AGCT");
    rna r2 = creation("AACC");
    bool tmp;
    if (r1 != r2)
        tmp = true;
    EXPECT_EQ(true, tmp);
}

TEST(is_complementary, test_1)/* NOLINT */
{
    rna r1 = creation("AGCT");
    rna r2 = creation("TCGA");
    EXPECT_EQ(true, r1.is_complementary(r2));
}

TEST(is_complementary, test_2)/* NOLINT */
{
    rna r1 = creation("AGCT");
    rna r2 = creation("AAAA");
    EXPECT_EQ(false, r1.is_complementary(r2));
}

TEST(is_complementary, test_3)/* NOLINT */
{
    rna r1(A, 1000);
    rna r2(T, 1000);
    EXPECT_EQ(true, r1.is_complementary(r2));
}

TEST(is_complementary, test_4)/* NOLINT */
{
    rna r1(A, 1000);
    rna r2(G, 1000);
    EXPECT_EQ(false, r1.is_complementary(r2));
}

TEST(is_complementary, test_5)/* NOLINT */
{
    rna r1(A, 1000);
    rna r2(T, 100);
    EXPECT_EQ(false, r1.is_complementary(r2));
}

TEST(trim, test_1)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    r1.trim(4);
    rna r2 = creation("AGCT");
    EXPECT_EQ(true, r1 == r2);
}

TEST(trim, test_2)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    r1.trim(0);
    rna r2;
    EXPECT_EQ(true, r1 == r2);
}

TEST(split, test_1)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    rna r2 = r1.split(4);
    rna r3 = creation("AGCT");
    rna r4 = creation("CGA");
    EXPECT_EQ(true, r1 == r3 && r2 == r4);
}

TEST(split, test_2)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    rna r2 = r1.split(0);
    rna r3;
    rna r4 = creation("AGCTCGA");
    EXPECT_EQ(true, r1 == r3 && r2 == r4);
}

TEST(cardinality, test_1)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    EXPECT_EQ(true, r1.cardinality(T) == 1);
}

TEST(cardinality, test_2)/* NOLINT */
{
    rna r1 = creation("AAAAA");
    EXPECT_EQ(true, r1.cardinality(T) == 0);
}

TEST(cardinality, test_3)/* NOLINT */
{
    rna r1 = creation("AGCTCGA");
    cout << r1.cardinality();
}

TEST(large_test, test_1)/* NOLINT */
{
    rna r1(A, 1000000);
    rna r2(T, 1000000);
    EXPECT_EQ(true, r1.is_complementary(r2));
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

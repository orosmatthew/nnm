#include "tests.hpp"

namespace {

void point_set2_tests()
{
    test_case("PointSet<Point2f>");

    constexpr nnm::Point2f p1 { 1.0f, -2.0f };
    constexpr nnm::Point2f p2 { -3.0f, 4.0f };
    constexpr nnm::Point2f p3 { 5.0f, -6.0f };
    constexpr nnm::Point2f p1_near { 1.0f + nnm::epsilon<float>() / 2.0f, -2.0f };

    using PointSet2 = nnm::PointSet<nnm::Point2f, 2>;
    using PointSet3 = nnm::PointSet<nnm::Point2f, 3>;

    constexpr PointSet2 empty2;
    constexpr PointSet3 empty3;
    constexpr PointSet2 single2 { p1 };
    constexpr PointSet2 pair2 { p1, p2 };
    constexpr PointSet2 pair2_swapped { p2, p1 };
    constexpr PointSet2 pair2_near { p1_near, p2 };
    constexpr PointSet2 dedup2 { p1, p1_near };
    constexpr PointSet3 pair3 { p2, p1 };
    constexpr PointSet3 pair3_near { p1_near, p2 };
    constexpr PointSet3 trio3 { p1, p2, p3 };
    constexpr PointSet3 trio3_swapped { p3, p2, p1 };
    constexpr PointSet3 dedup3 { p1, p1_near, p2 };

    test_section("PointSet()");
    {
        TEST_ASSERT(empty2.empty());
        TEST_ASSERT(empty3.empty());
        TEST_ASSERT(empty2.size() == 0);
        TEST_ASSERT(empty3.size() == 0);
        TEST_ASSERT(empty2.begin() == empty2.data());
        TEST_ASSERT(empty2.end() == empty2.data());
        TEST_ASSERT(empty3.begin() == empty3.data());
        TEST_ASSERT(empty3.end() == empty3.data());
        TEST_ASSERT(empty2.data()[0] == nnm::Point2f::zero());
        TEST_ASSERT(empty3.data()[0] == nnm::Point2f::zero());
        TEST_ASSERT(empty3.data()[1] == nnm::Point2f::zero());
        TEST_ASSERT(empty3.data()[2] == nnm::Point2f::zero());
    }

    test_section("PointSet(const std::initializer_list<Point>&)");
    {
        TEST_ASSERT(single2.size() == 1);
        TEST_ASSERT(single2.contains(p1));
        TEST_ASSERT(pair2.size() == 2);
        TEST_ASSERT(pair2.contains(p1));
        TEST_ASSERT(pair2.contains(p2));
        TEST_ASSERT(pair2.contains(p1_near));
        TEST_ASSERT(pair2.approx_equal(pair2_swapped));
        TEST_ASSERT(pair2 == pair2_swapped);
        TEST_ASSERT_FALSE(pair2 == single2);
        TEST_ASSERT(pair2.approx_equal(pair2_near));
        TEST_ASSERT(dedup2.size() == 1);
        TEST_ASSERT(dedup2.contains(p1));
        TEST_ASSERT(dedup3.size() == 2);
        TEST_ASSERT(dedup3.contains(p1));
        TEST_ASSERT(dedup3.contains(p2));
        TEST_ASSERT(trio3.size() == 3);
        TEST_ASSERT(trio3.contains(p1));
        TEST_ASSERT(trio3.contains(p2));
        TEST_ASSERT(trio3.contains(p3));
        TEST_ASSERT(trio3.approx_equal(trio3_swapped));
        TEST_ASSERT(trio3 == trio3_swapped);
        TEST_ASSERT(pair2.approx_equal(pair3));
        TEST_ASSERT(pair2 == pair3);
        TEST_ASSERT(pair2.approx_equal(pair3_near));
        TEST_ASSERT_FALSE(pair2 == pair3_near);
    }

    test_section("capacity");
    {
        TEST_ASSERT(PointSet2::capacity() == 2);
        TEST_ASSERT(PointSet3::capacity() == 3);
    }

    test_section("insert");
    {
        auto set2 = PointSet2();
        set2.insert(p1);
        TEST_ASSERT(set2.size() == 1);
        set2.insert(p1_near);
        TEST_ASSERT(set2.size() == 1);
        set2.insert(p2);
        TEST_ASSERT(set2.size() == 2);
        set2.insert(p1);
        TEST_ASSERT(set2.size() == 2);
        TEST_ASSERT(set2.contains(p1));
        TEST_ASSERT(set2.contains(p1_near));
        TEST_ASSERT(set2.contains(p2));
        TEST_ASSERT_FALSE(set2.contains(p3));

        auto set3 = PointSet3();
        set3.insert(p1);
        set3.insert(p1_near);
        TEST_ASSERT(set3.size() == 1);
        set3.insert(p2);
        set3.insert(p3);
        TEST_ASSERT(set3.size() == 3);
        set3.insert(p1);
        TEST_ASSERT(set3.size() == 3);
        TEST_ASSERT(set3.contains(p1));
        TEST_ASSERT(set3.contains(p2));
        TEST_ASSERT(set3.contains(p3));
    }

    test_section("clear");
    {
        auto set2 = pair2;
        set2.clear();
        TEST_ASSERT(set2.empty());
        TEST_ASSERT(set2.size() == 0);
        TEST_ASSERT(set2.data()[0] == nnm::Point2f::zero());
        TEST_ASSERT(set2.data()[1] == nnm::Point2f::zero());
        TEST_ASSERT(set2.begin() == set2.data());
        TEST_ASSERT(set2.end() == set2.data());

        auto set3 = trio3;
        set3.clear();
        TEST_ASSERT(set3.empty());
        TEST_ASSERT(set3.size() == 0);
        TEST_ASSERT(set3.data()[0] == nnm::Point2f::zero());
        TEST_ASSERT(set3.data()[1] == nnm::Point2f::zero());
        TEST_ASSERT(set3.data()[2] == nnm::Point2f::zero());
    }

    test_section("size");
    {
        TEST_ASSERT(empty2.size() == 0);
        TEST_ASSERT(single2.size() == 1);
        TEST_ASSERT(pair2.size() == 2);
        TEST_ASSERT(trio3.size() == 3);
    }

    test_section("begin");
    {
        TEST_ASSERT(pair2.begin() == pair2.data());
        TEST_ASSERT(pair3.begin() == pair3.data());
        const auto& const_pair2 = pair2;
        const auto& const_pair3 = pair3;
        TEST_ASSERT(const_pair2.begin() == const_pair2.data());
        TEST_ASSERT(const_pair3.begin() == const_pair3.data());
    }

    test_section("end");
    {
        TEST_ASSERT(pair2.end() == pair2.data() + pair2.size());
        TEST_ASSERT(pair3.end() == pair3.data() + pair3.size());
        TEST_ASSERT(trio3.end() == trio3.data() + trio3.size());
        const auto& const_pair2 = pair2;
        TEST_ASSERT(const_pair2.end() == const_pair2.data() + const_pair2.size());
    }

    test_section("data");
    {
        TEST_ASSERT(pair2.data()[0] == p1);
        TEST_ASSERT(pair2.data()[1] == p2);
        const auto& const_pair2 = pair2;
        TEST_ASSERT(const_pair2.data()[0] == p1);
        TEST_ASSERT(const_pair2.data()[1] == p2);
    }

    test_section("approx_equal");
    {
        TEST_ASSERT(empty2.approx_equal(empty3));
        TEST_ASSERT(empty3.approx_equal(empty2));
        TEST_ASSERT(pair2.approx_equal(pair2_swapped));
        TEST_ASSERT(pair2.approx_equal(pair2_near));
        TEST_ASSERT(pair2.approx_equal(pair3));
        TEST_ASSERT(pair2.approx_equal(pair3_near));
        TEST_ASSERT_FALSE(pair2.approx_equal(empty2));
        TEST_ASSERT_FALSE(pair2.approx_equal(trio3));
        TEST_ASSERT_FALSE(pair2.approx_equal(dedup2));
    }

    test_section("contains");
    {
        TEST_ASSERT_FALSE(empty2.contains(p1));
        TEST_ASSERT(pair2.contains(p1));
        TEST_ASSERT(pair2.contains(p1_near));
        TEST_ASSERT(pair2.contains(p2));
        TEST_ASSERT_FALSE(pair2.contains(p3));
        TEST_ASSERT(pair3.contains(p1));
        TEST_ASSERT(pair3.contains(p1_near));
    }

    test_section("empty");
    {
        TEST_ASSERT(empty2.empty());
        TEST_ASSERT(empty3.empty());
        TEST_ASSERT_FALSE(pair2.empty());
        TEST_ASSERT_FALSE(pair3.empty());
    }

    test_section("operator==");
    {
        TEST_ASSERT(empty2 == empty3);
        TEST_ASSERT(pair2 == pair2_swapped);
        TEST_ASSERT(pair2 == pair3);
        TEST_ASSERT_FALSE(pair2 == pair2_near);
        TEST_ASSERT_FALSE(pair2 == trio3);
        TEST_ASSERT_FALSE(pair2 == empty2);
    }

    test_section("operator!=");
    {
        TEST_ASSERT_FALSE(empty2 != empty3);
        TEST_ASSERT_FALSE(pair2 != pair2_swapped);
        TEST_ASSERT_FALSE(pair2 != pair3);
        TEST_ASSERT(pair2 != pair2_near);
        TEST_ASSERT(pair2 != trio3);
        TEST_ASSERT(pair2 != empty2);
    }
}

void point_set3_tests()
{
    test_case("PointSet<Point3f>");

    constexpr nnm::Point3f p1 { 1.0f, -2.0f, 3.0f };
    constexpr nnm::Point3f p2 { -3.0f, 4.0f, -5.0f };
    constexpr nnm::Point3f p3 { 5.0f, -6.0f, 7.0f };
    constexpr nnm::Point3f p1_near { 1.0f + nnm::epsilon<float>() / 2.0f, -2.0f, 3.0f };

    using PointSet2 = nnm::PointSet<nnm::Point3f, 2>;
    using PointSet3 = nnm::PointSet<nnm::Point3f, 3>;

    constexpr PointSet2 empty2;
    constexpr PointSet3 empty3;
    constexpr PointSet2 single2 { p1 };
    constexpr PointSet2 pair2 { p1, p2 };
    constexpr PointSet2 pair2_swapped { p2, p1 };
    constexpr PointSet2 pair2_near { p1_near, p2 };
    constexpr PointSet2 dedup2 { p1, p1_near };
    constexpr PointSet3 pair3 { p2, p1 };
    constexpr PointSet3 pair3_near { p1_near, p2 };
    constexpr PointSet3 trio3 { p1, p2, p3 };
    constexpr PointSet3 trio3_swapped { p3, p2, p1 };
    constexpr PointSet3 dedup3 { p1, p1_near, p2 };

    test_section("PointSet()");
    {
        TEST_ASSERT(empty2.empty());
        TEST_ASSERT(empty3.empty());
        TEST_ASSERT(empty2.size() == 0);
        TEST_ASSERT(empty3.size() == 0);
        TEST_ASSERT(empty2.begin() == empty2.data());
        TEST_ASSERT(empty2.end() == empty2.data());
        TEST_ASSERT(empty3.begin() == empty3.data());
        TEST_ASSERT(empty3.end() == empty3.data());
        TEST_ASSERT(empty2.data()[0] == nnm::Point3f::zero());
        TEST_ASSERT(empty3.data()[0] == nnm::Point3f::zero());
        TEST_ASSERT(empty3.data()[1] == nnm::Point3f::zero());
        TEST_ASSERT(empty3.data()[2] == nnm::Point3f::zero());
    }

    test_section("PointSet(const std::initializer_list<Point>&)");
    {
        TEST_ASSERT(single2.size() == 1);
        TEST_ASSERT(single2.contains(p1));
        TEST_ASSERT(pair2.size() == 2);
        TEST_ASSERT(pair2.contains(p1));
        TEST_ASSERT(pair2.contains(p2));
        TEST_ASSERT(pair2.contains(p1_near));
        TEST_ASSERT(pair2.approx_equal(pair2_swapped));
        TEST_ASSERT(pair2 == pair2_swapped);
        TEST_ASSERT_FALSE(pair2 == single2);
        TEST_ASSERT(pair2.approx_equal(pair2_near));
        TEST_ASSERT(dedup2.size() == 1);
        TEST_ASSERT(dedup2.contains(p1));
        TEST_ASSERT(dedup3.size() == 2);
        TEST_ASSERT(dedup3.contains(p1));
        TEST_ASSERT(dedup3.contains(p2));
        TEST_ASSERT(trio3.size() == 3);
        TEST_ASSERT(trio3.contains(p1));
        TEST_ASSERT(trio3.contains(p2));
        TEST_ASSERT(trio3.contains(p3));
        TEST_ASSERT(trio3.approx_equal(trio3_swapped));
        TEST_ASSERT(trio3 == trio3_swapped);
        TEST_ASSERT(pair2.approx_equal(pair3));
        TEST_ASSERT(pair2 == pair3);
        TEST_ASSERT(pair2.approx_equal(pair3_near));
        TEST_ASSERT_FALSE(pair2 == pair3_near);
    }

    test_section("capacity");
    {
        TEST_ASSERT(PointSet2::capacity() == 2);
        TEST_ASSERT(PointSet3::capacity() == 3);
    }

    test_section("insert");
    {
        auto set2 = PointSet2();
        set2.insert(p1);
        TEST_ASSERT(set2.size() == 1);
        set2.insert(p1_near);
        TEST_ASSERT(set2.size() == 1);
        set2.insert(p2);
        TEST_ASSERT(set2.size() == 2);
        set2.insert(p1);
        TEST_ASSERT(set2.size() == 2);
        TEST_ASSERT(set2.contains(p1));
        TEST_ASSERT(set2.contains(p1_near));
        TEST_ASSERT(set2.contains(p2));
        TEST_ASSERT_FALSE(set2.contains(p3));

        auto set3 = PointSet3();
        set3.insert(p1);
        set3.insert(p1_near);
        TEST_ASSERT(set3.size() == 1);
        set3.insert(p2);
        set3.insert(p3);
        TEST_ASSERT(set3.size() == 3);
        set3.insert(p1);
        TEST_ASSERT(set3.size() == 3);
        TEST_ASSERT(set3.contains(p1));
        TEST_ASSERT(set3.contains(p2));
        TEST_ASSERT(set3.contains(p3));
    }

    test_section("clear");
    {
        auto set2 = pair2;
        set2.clear();
        TEST_ASSERT(set2.empty());
        TEST_ASSERT(set2.size() == 0);
        TEST_ASSERT(set2.data()[0] == nnm::Point3f::zero());
        TEST_ASSERT(set2.data()[1] == nnm::Point3f::zero());
        TEST_ASSERT(set2.begin() == set2.data());
        TEST_ASSERT(set2.end() == set2.data());

        auto set3 = trio3;
        set3.clear();
        TEST_ASSERT(set3.empty());
        TEST_ASSERT(set3.size() == 0);
        TEST_ASSERT(set3.data()[0] == nnm::Point3f::zero());
        TEST_ASSERT(set3.data()[1] == nnm::Point3f::zero());
        TEST_ASSERT(set3.data()[2] == nnm::Point3f::zero());
    }

    test_section("size");
    {
        TEST_ASSERT(empty2.size() == 0);
        TEST_ASSERT(single2.size() == 1);
        TEST_ASSERT(pair2.size() == 2);
        TEST_ASSERT(trio3.size() == 3);
    }

    test_section("begin");
    {
        TEST_ASSERT(pair2.begin() == pair2.data());
        TEST_ASSERT(pair3.begin() == pair3.data());
        const auto& const_pair2 = pair2;
        const auto& const_pair3 = pair3;
        TEST_ASSERT(const_pair2.begin() == const_pair2.data());
        TEST_ASSERT(const_pair3.begin() == const_pair3.data());
    }

    test_section("end");
    {
        TEST_ASSERT(pair2.end() == pair2.data() + pair2.size());
        TEST_ASSERT(pair3.end() == pair3.data() + pair3.size());
        TEST_ASSERT(trio3.end() == trio3.data() + trio3.size());
        const auto& const_pair2 = pair2;
        TEST_ASSERT(const_pair2.end() == const_pair2.data() + const_pair2.size());
    }

    test_section("data");
    {
        TEST_ASSERT(pair2.data()[0] == p1);
        TEST_ASSERT(pair2.data()[1] == p2);
        const auto& const_pair2 = pair2;
        TEST_ASSERT(const_pair2.data()[0] == p1);
        TEST_ASSERT(const_pair2.data()[1] == p2);
    }

    test_section("approx_equal");
    {
        TEST_ASSERT(empty2.approx_equal(empty3));
        TEST_ASSERT(empty3.approx_equal(empty2));
        TEST_ASSERT(pair2.approx_equal(pair2_swapped));
        TEST_ASSERT(pair2.approx_equal(pair2_near));
        TEST_ASSERT(pair2.approx_equal(pair3));
        TEST_ASSERT(pair2.approx_equal(pair3_near));
        TEST_ASSERT_FALSE(pair2.approx_equal(empty2));
        TEST_ASSERT_FALSE(pair2.approx_equal(trio3));
        TEST_ASSERT_FALSE(pair2.approx_equal(dedup2));
    }

    test_section("contains");
    {
        TEST_ASSERT_FALSE(empty2.contains(p1));
        TEST_ASSERT(pair2.contains(p1));
        TEST_ASSERT(pair2.contains(p1_near));
        TEST_ASSERT(pair2.contains(p2));
        TEST_ASSERT_FALSE(pair2.contains(p3));
        TEST_ASSERT(pair3.contains(p1));
        TEST_ASSERT(pair3.contains(p1_near));
    }

    test_section("empty");
    {
        TEST_ASSERT(empty2.empty());
        TEST_ASSERT(empty3.empty());
        TEST_ASSERT_FALSE(pair2.empty());
        TEST_ASSERT_FALSE(pair3.empty());
    }

    test_section("operator==");
    {
        TEST_ASSERT(empty2 == empty3);
        TEST_ASSERT(pair2 == pair2_swapped);
        TEST_ASSERT(pair2 == pair3);
        TEST_ASSERT_FALSE(pair2 == pair2_near);
        TEST_ASSERT_FALSE(pair2 == trio3);
        TEST_ASSERT_FALSE(pair2 == empty2);
    }

    test_section("operator!=");
    {
        TEST_ASSERT_FALSE(empty2 != empty3);
        TEST_ASSERT_FALSE(pair2 != pair2_swapped);
        TEST_ASSERT_FALSE(pair2 != pair3);
        TEST_ASSERT(pair2 != pair2_near);
        TEST_ASSERT(pair2 != trio3);
        TEST_ASSERT(pair2 != empty2);
    }
}

} // namespace

void point_set_tests()
{
    point_set2_tests();
    point_set3_tests();
}

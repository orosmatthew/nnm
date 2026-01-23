#include "tests.hpp"

void vector2i_tests()
{
    test_case("Vector2i");
    test_section("Vector2i()");
    {
        constexpr nnm::Vector2ii v1;
        TEST_ASSERT(v1.x == 0);
        TEST_ASSERT(v1.y == 0);
    }

    test_section("Vector2i(const Vector2&)");
    {
        constexpr nnm::Vector2ii v1(nnm::Vector2(1.1f, -10.7f));
        TEST_ASSERT(v1.x == 1);
        TEST_ASSERT(v1.y == -10);
    }

    test_section("Vector2i(int, int)");
    {
        constexpr nnm::Vector2i v2(1, 2);
        TEST_ASSERT(v2.x == 1);
        TEST_ASSERT(v2.y == 2);
    }

    test_section("all");
    {
        constexpr auto all_threes = nnm::Vector2ii::all(3);
        TEST_ASSERT(all_threes.x == 3);
        TEST_ASSERT(all_threes.y == 3);
    }

    test_section("zero");
    {
        constexpr auto zero = nnm::Vector2ii::zero();
        TEST_ASSERT(zero.x == 0);
        TEST_ASSERT(zero.y == 0);
    }

    test_section("one");
    {
        constexpr auto one = nnm::Vector2ii::one();
        TEST_ASSERT(one.x == 1);
        TEST_ASSERT(one.y == 1);
    }

    test_section("axis_x");
    {
        constexpr auto x = nnm::Vector2ii::axis_x();
        TEST_ASSERT(x.x == 1);
        TEST_ASSERT(x.y == 0);
    }

    test_section("axis_y");
    {
        constexpr auto y = nnm::Vector2ii::axis_y();
        TEST_ASSERT(y.x == 0);
        TEST_ASSERT(y.y == 1);
    }

    test_section("abs");
    {
        constexpr auto result = nnm::Vector2i(1, -2).abs();
        TEST_ASSERT(result == nnm::Vector2i(1, 2));
    }

    test_section("clamp");
    {
        constexpr auto result = nnm::Vector2i(1, -3).clamp({ 1, -2 }, { 2, 2 });
        TEST_ASSERT(result == nnm::Vector2i(1, -2));
    }

    test_section("manhattan_distance");
    {
        constexpr nnm::Vector2i from1(1, 1);
        constexpr nnm::Vector2i to1(2, 2);
        constexpr auto result = from1.manhattan_distance(to1);
        TEST_ASSERT(result == 2);

        auto from = nnm::Vector2i(-1, -1);
        auto to = nnm::Vector2i(1, 1);
        TEST_ASSERT(from.manhattan_distance(to) == 4);

        from = nnm::Vector2i(0, 0);
        to = nnm::Vector2i(3, 0);
        TEST_ASSERT(from.manhattan_distance(to) == 3);

        from = nnm::Vector2i(0, 0);
        to = nnm::Vector2i(0, 4);
        TEST_ASSERT(from.manhattan_distance(to) == 4);

        from = nnm::Vector2i(1, 2);
        to = nnm::Vector2i(1, 2);
        TEST_ASSERT(from.manhattan_distance(to) == 0);
    }

    test_section("length_sqrd");
    {
        constexpr auto result = nnm::Vector2i(3, 4).length_sqrd();
        TEST_ASSERT(result == 25);
        TEST_ASSERT(nnm::Vector2i(-2, 5).length_sqrd() == 29);
        TEST_ASSERT(nnm::Vector2i(0, 0).length_sqrd() == 0);
    }

    test_section("dot");
    {
        constexpr nnm::Vector2i v1(2, 3);
        constexpr nnm::Vector2i v2(4, 5);
        constexpr auto result = v1.dot(v2);
        TEST_ASSERT(result == 23);
    }

    test_section("cross");
    {
        constexpr nnm::Vector2i v1(2, -3);
        constexpr nnm::Vector2i v2(-4, 5);
        constexpr auto result = v1.cross(v2);
        TEST_ASSERT(result == -2);
    }

    test_section("parallel");
    {
        constexpr nnm::Vector2i v1 { 1, -2 };
        TEST_ASSERT(v1.parallel(v1));
        constexpr nnm::Vector2i v2 { -2, 4 };
        constexpr auto result = v1.parallel(v2);
        TEST_ASSERT(result);
        constexpr nnm::Vector2i v3 { 1, -5 };
        TEST_ASSERT_FALSE(v1.parallel(v3));
    }

    test_section("perpendicular");
    {
        constexpr nnm::Vector2i v1 { 1, -2 };
        constexpr nnm::Vector2i v2 { 4, 2 };
        constexpr auto result = v1.perpendicular(v2);
        TEST_ASSERT(result);
        constexpr nnm::Vector2i v3 { -4, -2 };
        TEST_ASSERT(v1.perpendicular(v3));
    }

    test_section("arbitrary_perpendicular");
    {
        constexpr nnm::Vector2i v1 { 1, -2 };
        constexpr auto result = v1.arbitrary_perpendicular();
        TEST_ASSERT(v1.perpendicular(result));
        constexpr nnm::Vector2i v2 { 1, 0 };
        TEST_ASSERT(v2.perpendicular(v2.arbitrary_perpendicular()));
    }

    test_section("max");
    {
        constexpr nnm::Vector2i v1(3, 4);
        constexpr auto result = v1.max();
        TEST_ASSERT(result == 4);
        nnm::Vector2i v2(5, 2);
        TEST_ASSERT(v2.max() == 5);
        nnm::Vector2i v3(0, 0);
        TEST_ASSERT(v3.max() == 0);
        nnm::Vector2i v4 { -2, 1 };
        TEST_ASSERT(v4.max() == 1);
        nnm::Vector2i v5 { 1, -2 };
        TEST_ASSERT(v5.max() == 1);
    }

    test_section("abs_max");
    {
        constexpr nnm::Vector2i v1(3, 4);
        constexpr auto result = v1.abs_max();
        TEST_ASSERT(result == 4);
        nnm::Vector2i v2(5, 2);
        TEST_ASSERT(v2.abs_max() == 5);
        nnm::Vector2i v3(0, 0);
        TEST_ASSERT(v3.abs_max() == 0);
        nnm::Vector2i v4 { -2, 1 };
        TEST_ASSERT(v4.abs_max() == -2);
        nnm::Vector2i v5 { 1, -2 };
        TEST_ASSERT(v5.abs_max() == -2);
    }

    test_section("min");
    {
        constexpr nnm::Vector2i v1(3, 4);
        constexpr auto result = v1.min();
        TEST_ASSERT(result == 3);
        nnm::Vector2i v2(5, 2);
        TEST_ASSERT(v2.min() == 2);
        nnm::Vector2i v3(0, 0);
        TEST_ASSERT(v3.min() == 0);
        nnm::Vector2i v4 { -2, 1 };
        TEST_ASSERT(v4.min() == -2);
        nnm::Vector2i v5 { 1, -2 };
        TEST_ASSERT(v5.min() == -2);
    }

    test_section("abs_min");
    {
        constexpr nnm::Vector2i v1(3, 4);
        constexpr auto result = v1.abs_min();
        TEST_ASSERT(result == 3);
        nnm::Vector2i v2(5, 2);
        TEST_ASSERT(v2.abs_min() == 2);
        nnm::Vector2i v3(0, 0);
        TEST_ASSERT(v3.abs_min() == 0);
        nnm::Vector2i v4 { -2, 1 };
        TEST_ASSERT(v4.abs_min() == 1);
        nnm::Vector2i v5 { 1, -2 };
        TEST_ASSERT(v5.abs_min() == 1);
    }

    test_section("max_index");
    {
        constexpr nnm::Vector2i v1(3, 4);
        constexpr auto result = v1.max_index();
        TEST_ASSERT(result == 1);
        nnm::Vector2i v2(2, 5);
        TEST_ASSERT(v2.max_index() == 1);
        nnm::Vector2i v3(0, 0);
        TEST_ASSERT(v3.max_index() == 0);
        nnm::Vector2i v4 { -2, 1 };
        TEST_ASSERT(v4.max_index() == 1);
        nnm::Vector2i v5 { 1, -2 };
        TEST_ASSERT(v5.max_index() == 0);
    }

    test_section("abs_max_index");
    {
        constexpr nnm::Vector2i v1(3, 4);
        constexpr auto result = v1.abs_max_index();
        TEST_ASSERT(result == 1);
        nnm::Vector2i v2(2, 5);
        TEST_ASSERT(v2.abs_max_index() == 1);
        nnm::Vector2i v3(0, 0);
        TEST_ASSERT(v3.abs_max_index() == 0);
        nnm::Vector2i v4 { -2, 1 };
        TEST_ASSERT(v4.abs_max_index() == 0);
        nnm::Vector2i v5 { 1, -2 };
        TEST_ASSERT(v5.abs_max_index() == 1);
    }

    test_section("min_index");
    {
        constexpr nnm::Vector2i v1(3, 4);
        constexpr auto result = v1.min_index();
        TEST_ASSERT(result == 0);
        nnm::Vector2i v2(2, 5);
        TEST_ASSERT(v2.min_index() == 0);
        nnm::Vector2i v3(0, 0);
        TEST_ASSERT(v3.min_index() == 0);
        nnm::Vector2i v4 { -2, 1 };
        TEST_ASSERT(v4.min_index() == 0);
        nnm::Vector2i v5 { 1, -2 };
        TEST_ASSERT(v5.min_index() == 1);
    }

    test_section("abs_min_index");
    {
        constexpr nnm::Vector2i v1(3, 4);
        constexpr auto result = v1.abs_min_index();
        TEST_ASSERT(result == 0);
        nnm::Vector2i v2(2, 5);
        TEST_ASSERT(v2.abs_min_index() == 0);
        nnm::Vector2i v3(0, 0);
        TEST_ASSERT(v3.abs_min_index() == 0);
        nnm::Vector2i v4 { -2, 1 };
        TEST_ASSERT(v4.abs_min_index() == 1);
        nnm::Vector2i v5 { 1, -2 };
        TEST_ASSERT(v5.abs_min_index() == 0);
    }

    test_section("begin");
    {
        nnm::Vector2i v1(2, -3);
        TEST_ASSERT(v1.begin() == &v1.x);
    }

    test_section("end");
    {
        nnm::Vector2i v1(2, -3);
        TEST_ASSERT(v1.end() == &v1.y + 1);
    }

    test_section("at");
    {
        constexpr nnm::Vector2i v1(2, -3);
        constexpr auto result = v1.at(0);
        TEST_ASSERT(result == 2);
        TEST_ASSERT(v1.at(1) == -3);
    }

    test_section("operator[]");
    {
        constexpr nnm::Vector2i v1(2, -3);
        constexpr auto result = v1[0];
        TEST_ASSERT(result == 2);
        TEST_ASSERT(v1[1] == -3);
    }

    constexpr nnm::Vector2i v1(1, 2);
    constexpr nnm::Vector2i v2(3, 4);
    constexpr nnm::Vector2i v3(1, 2);

    test_section("operator==");
    {
        constexpr auto result = v1 == v3;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(v1 == v2);
    }

    test_section("operator!=");
    {
        constexpr auto result = v1 != v3;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(v1 != v2);
    }

    constexpr nnm::Vector2i v4(1, 2);
    constexpr nnm::Vector2i v5(3, 4);

    test_section("operator+(const Vector2i&)");
    {
        constexpr auto result = v4 + v5;
        TEST_ASSERT(result == nnm::Vector2i(4, 6));
    }

    test_section("operator+=");
    {
        constexpr auto result = [=] {
            auto v4_copy = v4;
            v4_copy += v5;
            return v4_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2i(4, 6));
    }

    test_section("operator-(const Vector2i&)");
    {
        constexpr auto result = v5 - v4;
        TEST_ASSERT(result == nnm::Vector2i(2, 2));
    }

    test_section("operator-=");
    {
        constexpr auto result = [=] {
            auto v5_copy = v5;
            v5_copy -= v4;
            return v5_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2i(2, 2));
    }

    test_section("operator*(const Vector2i&)");
    {
        constexpr auto result = v4 * v5;
        TEST_ASSERT(result == nnm::Vector2i(3, 8));
    }

    test_section("operator*=(const Vector2i&)");
    {
        constexpr auto result = [=] {
            auto v4_copy = v4;
            v4_copy *= v5;
            return v4_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2i(3, 8));
    }

    test_section("operator*(int)");
    {
        constexpr auto result = v4 * 2;
        TEST_ASSERT(result == nnm::Vector2i(2, 4));
    }

    test_section("operator*(int, const Vector2i&)");
    {
        constexpr auto result = 2 * v4;
        TEST_ASSERT(result == nnm::Vector2i(2, 4));
    }

    test_section("operator*=(int)");
    {
        constexpr auto result = [=] {
            auto v4_copy = v4;
            v4_copy *= 2;
            return v4_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2i(2, 4));
    }

    test_section("operator/(const Vector2i&)");
    {
        constexpr auto result = v5 / v4;
        TEST_ASSERT(result == nnm::Vector2i(3, 2));
    }

    test_section("operator/=(const Vector2i&)");
    {
        constexpr auto result = [=] {
            auto v5_copy = v5;
            v5_copy /= v4;
            return v5_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2i(3, 2));
    }

    test_section("operator/(int)");
    {
        constexpr auto result = v5 / 2;
        TEST_ASSERT(result == nnm::Vector2i(1, 2));
    }

    test_section("operator/(int, const Vector2i&)");
    {
        constexpr auto result = 2 / v4;
        TEST_ASSERT(result == nnm::Vector2i(2, 1));
    }

    test_section("operator/=(int)");
    {
        constexpr auto result = [=] {
            auto v5_copy = v5;
            v5_copy /= 2;
            return v5_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2i(1, 2));
    }

    test_section("operator%(const Vector2i&)");
    {
        constexpr auto result = v4 % v5;
        TEST_ASSERT(result == nnm::Vector2i(1, 2));
    }

    test_section("operator%=(const Vector2i&)");
    {
        constexpr auto result = [=] {
            auto v4_copy = v4;
            v4_copy %= v5;
            return v4_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2i(1, 2));
    }

    test_section("operator%(int)");
    {
        constexpr auto result = v4 % 2;
        TEST_ASSERT(result == nnm::Vector2i(1, 0));
    }

    test_section("operator%(int, const Vector2i&)");
    {
        constexpr auto result = 3 % nnm::Vector2i(2, 5);
        TEST_ASSERT(result == nnm::Vector2i(1, 3));
    }

    test_section("operator%=(int)");
    {
        constexpr auto result = [=] {
            auto v4_copy = v4;
            v4_copy %= 2;
            return v4_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2i(1, 0));
    }

    test_section("operator+");
    {
        constexpr auto result = +v4;
        TEST_ASSERT(result == v4);
    }

    test_section("operator-");
    {
        constexpr auto result = -v4;
        TEST_ASSERT(result == nnm::Vector2i(-1, -2));
    }

    test_section("operator<");
    {
        constexpr nnm::Vector2i v7(1, 2);
        constexpr nnm::Vector2i v8(3, 4);
        constexpr auto result = v7 < v8;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(v8 < v7);
    }

    test_section("operator bool");
    {
        constexpr nnm::Vector2i v7(1, 2);
        constexpr auto result = static_cast<bool>(v7);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(static_cast<bool>(nnm::Vector2i(0, 0)));
    }

    test_section("hash");
    {
        constexpr nnm::Vector2i v7(1, 2);
        const auto _ = nnm::Vector2ii::Hash()(v7);
    }
}
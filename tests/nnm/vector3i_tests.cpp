#include "tests.hpp"

void vector3i_tests()
{
    test_case("Vector3i");
    test_section("Vector3i()");
    {
        constexpr nnm::Vector3ii v_default;
        TEST_ASSERT(v_default.x == 0);
        TEST_ASSERT(v_default.y == 0);
        TEST_ASSERT(v_default.z == 0);
    }

    test_section("Vector3i(const Vector3&)");
    {
        constexpr nnm::Vector3ii v(nnm::Vector3(1.1f, 0.2f, -1.6f));
        TEST_ASSERT(v.x == 1);
        TEST_ASSERT(v.y == 0);
        TEST_ASSERT(v.z == -1);
    }

    test_section("Vector3i(const Vector2i&, int)");
    {
        constexpr nnm::Vector3i v(nnm::Vector2i(1, -2), 3);
        TEST_ASSERT(v.x == 1);
        TEST_ASSERT(v.y == -2);
        TEST_ASSERT(v.z == 3);
    }

    test_section("Vector3i(int, int, int)");
    {
        constexpr nnm::Vector3i v_with_params(1, -2, 3);
        TEST_ASSERT(v_with_params.x == 1);
        TEST_ASSERT(v_with_params.y == -2);
        TEST_ASSERT(v_with_params.z == 3);
    }

    test_section("all");
    {
        constexpr auto v_all_threes = nnm::Vector3ii::all(3);
        TEST_ASSERT(v_all_threes.x == 3);
        TEST_ASSERT(v_all_threes.y == 3);
        TEST_ASSERT(v_all_threes.z == 3);
    }

    test_section("zero");
    {
        constexpr auto v_zero = nnm::Vector3ii::zero();
        TEST_ASSERT(v_zero.x == 0);
        TEST_ASSERT(v_zero.y == 0);
        TEST_ASSERT(v_zero.z == 0);
    }

    test_section("one");
    {
        constexpr auto v_one = nnm::Vector3ii::one();
        TEST_ASSERT(v_one.x == 1);
        TEST_ASSERT(v_one.y == 1);
        TEST_ASSERT(v_one.z == 1);
    }

    test_section("axis_x");
    {
        constexpr auto x = nnm::Vector3ii::axis_x();
        TEST_ASSERT(x.x == 1);
        TEST_ASSERT(x.y == 0);
        TEST_ASSERT(x.z == 0);
    }

    test_section("axis_y");
    {
        constexpr auto y = nnm::Vector3ii::axis_y();
        TEST_ASSERT(y.x == 0);
        TEST_ASSERT(y.y == 1);
        TEST_ASSERT(y.z == 0);
    }

    test_section("axis_z");
    {
        constexpr auto z = nnm::Vector3ii::axis_z();
        TEST_ASSERT(z.x == 0);
        TEST_ASSERT(z.y == 0);
        TEST_ASSERT(z.z == 1);
    }

    test_section("abs");
    {
        constexpr nnm::Vector3i v(0, -2, 3);
        constexpr auto result = v.abs();
        TEST_ASSERT(result == nnm::Vector3i(0, 2, 3));
    }

    test_section("clamp");
    {
        constexpr nnm::Vector3i v(0, -2, 3);
        constexpr auto result = v.clamp({ -1, -3, -2 }, { 1, 5, 100 });
        TEST_ASSERT(result == nnm::Vector3i(0, -2, 3));
        TEST_ASSERT(v.clamp({ 1, 3, 5 }, { 2, 5, 100 }) == nnm::Vector3i(1, 3, 5));
        TEST_ASSERT(v.clamp({ -10, -5, -100 }, { -1, -4, 3 }) == nnm::Vector3i(-1, -4, 3));
    }

    test_section("manhattan_distance");
    {
        constexpr nnm::Vector3i from1(1, 1, 1);
        constexpr nnm::Vector3i to1(2, 2, 2);
        constexpr auto result = from1.manhattan_distance(to1);
        TEST_ASSERT(result == 3);

        auto from = nnm::Vector3i(-1, -1, -1);
        auto to = nnm::Vector3i(1, 1, 1);
        TEST_ASSERT(from.manhattan_distance(to) == 6);

        from = nnm::Vector3i(0, 0, 0);
        to = nnm::Vector3i(3, 0, 0);
        TEST_ASSERT(from.manhattan_distance(to) == 3);

        from = nnm::Vector3i(0, 0, 0);
        to = nnm::Vector3i(0, 4, 0);
        TEST_ASSERT(from.manhattan_distance(to) == 4);

        from = nnm::Vector3i(1, 2, 3);
        to = nnm::Vector3i(1, 2, 3);
        TEST_ASSERT(from.manhattan_distance(to) == 0);
    }

    test_section("length_sqrd");
    {
        constexpr nnm::Vector3i v(1, -2, 3);
        constexpr auto result = v.length_sqrd();
        TEST_ASSERT(result == 14);
    }

    test_section("dot");
    {
        constexpr nnm::Vector3i v1(1, -2, 3);
        constexpr nnm::Vector3i v2(-2, 4, -6);
        constexpr auto result = v1.dot(v2);
        TEST_ASSERT(result == -28);
    }

    test_section("cross");
    {
        constexpr nnm::Vector3i v1(1, -2, 3);
        constexpr nnm::Vector3i v2(-2, 4, -6);
        constexpr auto result = v1.cross(v2);
        TEST_ASSERT(result == nnm::Vector3ii::zero());
        constexpr nnm::Vector3i v3(1, 2, 3);
        constexpr nnm::Vector3i v4(-2, 4, 6);
        TEST_ASSERT(v3.cross(v4) == nnm::Vector3i(0, -12, 8));
    }

    test_section("parallel");
    {
        constexpr nnm::Vector3i v1 { 1, 2, -3 };
        constexpr auto result = v1.parallel({ 2, 4, -6 });
        TEST_ASSERT(result);
        TEST_ASSERT(v1.parallel(v1));
        TEST_ASSERT(v1.parallel({ -3, -6, 9 }));
        TEST_ASSERT_FALSE(v1.parallel({ 1, 2, 3 }));
    }

    test_section("approx_perpendicular");
    {
        constexpr nnm::Vector3i v1 { 1, 2, -3 };
        constexpr auto result = v1.perpendicular({ 30, 0, 10 });
        TEST_ASSERT(result);
        TEST_ASSERT(v1.perpendicular({ 0, -6, -4 }));
        TEST_ASSERT_FALSE(v1.perpendicular(v1));
        TEST_ASSERT_FALSE(v1.perpendicular({ 1, 2, 3 }));
    }

    test_section("arbitrary_perpendicular");
    {
        constexpr nnm::Vector3i v1 { 1, 2, -3 };
        constexpr auto result = v1.arbitrary_perpendicular();
        TEST_ASSERT(result.perpendicular(v1));
    }

    test_section("max");
    {
        constexpr nnm::Vector3i v1(3, 4, -2);
        constexpr auto result = v1.max();
        TEST_ASSERT(result == 4);
        nnm::Vector3i v2(-200, 5, 100);
        TEST_ASSERT(v2.max() == 100);
        nnm::Vector3i v3(0, 0, 0);
        TEST_ASSERT(v3.max() == 0);
        nnm::Vector3i v4(5, -200, 100);
        TEST_ASSERT(v4.max() == 100);
        nnm::Vector3i v5(5, 100, -200);
        TEST_ASSERT(v5.max() == 100);
    }

    test_section("abs_max");
    {
        constexpr nnm::Vector3i v1(3, 4, -2);
        constexpr auto result = v1.abs_max();
        TEST_ASSERT(result == 4);
        nnm::Vector3i v2(-200, 5, 100);
        TEST_ASSERT(v2.abs_max() == -200);
        nnm::Vector3i v3(0, 0, 0);
        TEST_ASSERT(v3.abs_max() == 0);
        nnm::Vector3i v4(5, -200, 100);
        TEST_ASSERT(v4.abs_max() == -200);
        nnm::Vector3i v5(5, 100, -200);
        TEST_ASSERT(v5.abs_max() == -200);
    }

    test_section("min");
    {
        constexpr nnm::Vector3i v1(3, 4, -2);
        constexpr auto result = v1.min();
        TEST_ASSERT(result == -2);
        nnm::Vector3i v2(-200, 5, 100);
        TEST_ASSERT(v2.min() == -200);
        nnm::Vector3i v3(0, 0, 0);
        TEST_ASSERT(v3.min() == 0);
        nnm::Vector3i v4(5, -200, 100);
        TEST_ASSERT(v4.min() == -200);
        nnm::Vector3i v5(5, 100, -200);
        TEST_ASSERT(v5.min() == -200);
    }

    test_section("abs_min");
    {
        constexpr nnm::Vector3i v1(3, 4, -2);
        constexpr auto result = v1.abs_min();
        TEST_ASSERT(result == -2);
        nnm::Vector3i v2(-200, 5, 100);
        TEST_ASSERT(v2.abs_min() == 5);
        nnm::Vector3i v3(0, 0, 0);
        TEST_ASSERT(v3.abs_min() == 0);
        nnm::Vector3i v4(5, -200, 100);
        TEST_ASSERT(v4.abs_min() == 5);
        nnm::Vector3i v5(5, 100, -200);
        TEST_ASSERT(v5.abs_min() == 5);
    }

    test_section("max_index");
    {
        constexpr nnm::Vector3i v1(3, 4, -2);
        constexpr auto result = v1.max_index();
        TEST_ASSERT(result == 1);
        nnm::Vector3i v2(-200, 5, 100);
        TEST_ASSERT(v2.max_index() == 2);
        nnm::Vector3i v3(0, 0, 0);
        TEST_ASSERT(v3.max_index() == 0);
        nnm::Vector3i v4(5, -200, 100);
        TEST_ASSERT(v4.max_index() == 2);
        nnm::Vector3i v5(5, 100, -200);
        TEST_ASSERT(v5.max_index() == 1);
    }

    test_section("abs_max_index");
    {
        constexpr nnm::Vector3i v1(3, 4, -2);
        constexpr auto result = v1.abs_max_index();
        TEST_ASSERT(result == 1);
        nnm::Vector3i v2(-200, 5, 100);
        TEST_ASSERT(v2.abs_max_index() == 0);
        nnm::Vector3i v3(0, 0, 0);
        TEST_ASSERT(v3.abs_max_index() == 0);
        nnm::Vector3i v4(5, -200, 100);
        TEST_ASSERT(v4.abs_max_index() == 1);
        nnm::Vector3i v5(5, 100, -200);
        TEST_ASSERT(v5.abs_max_index() == 2);
    }

    test_section("min_index");
    {
        constexpr nnm::Vector3i v1(3, 4, -2);
        constexpr auto result = v1.min_index();
        TEST_ASSERT(result == 2);
        nnm::Vector3i v2(-200, 5, 100);
        TEST_ASSERT(v2.min_index() == 0);
        nnm::Vector3i v3(0, 0, 0);
        TEST_ASSERT(v3.min_index() == 0);
        nnm::Vector3i v4(5, -200, 100);
        TEST_ASSERT(v4.min_index() == 1);
        nnm::Vector3i v5(5, 100, -200);
        TEST_ASSERT(v5.min_index() == 2);
    }

    test_section("abs_min_index");
    {
        constexpr nnm::Vector3i v1(3, 4, -2);
        constexpr auto result = v1.abs_min_index();
        TEST_ASSERT(result == 2);
        nnm::Vector3i v2(-200, 5, 100);
        TEST_ASSERT(v2.abs_min_index() == 1);
        nnm::Vector3i v3(0, 0, 0);
        TEST_ASSERT(v3.abs_min_index() == 0);
        nnm::Vector3i v4(5, -200, 100);
        TEST_ASSERT(v4.abs_min_index() == 0);
        nnm::Vector3i v5(-200, 100, 5);
        TEST_ASSERT(v5.abs_min_index() == 2);
    }

    test_section("xy");
    {
        constexpr nnm::Vector3i v(1, -2, 3);
        constexpr auto result = v.xy();
        TEST_ASSERT(result == nnm::Vector2i(1, -2));
    }

    test_section("begin");
    {
        nnm::Vector3i v(1, -2, 3);
        TEST_ASSERT(v.begin() == &v.x);
    }

    test_section("end");
    {
        nnm::Vector3i v(1, -2, 3);
        TEST_ASSERT(v.end() == &v.z + 1);
    }

    test_section("at");
    {
        constexpr nnm::Vector3i v(1, -2, 3);
        constexpr auto result = v.at(0);
        TEST_ASSERT(result == 1);
        TEST_ASSERT(v.at(1) == -2);
        TEST_ASSERT(v.at(2) == 3);
    }

    test_section("operator[]");
    {
        constexpr nnm::Vector3i v(1, -2, 3);
        constexpr auto result = v[0];
        TEST_ASSERT(result == 1);
        TEST_ASSERT(v[1] == -2);
        TEST_ASSERT(v[2] == 3);
    }

    constexpr nnm::Vector3i v1(1, 2, -3);
    constexpr nnm::Vector3i v2(-3, 4, 100);
    constexpr nnm::Vector3i v3(1, 2, -3);

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

    test_section("operator+(const Vector3i&)");
    {
        constexpr auto result = v1 + v2;
        TEST_ASSERT(result == nnm::Vector3i(-2, 6, 97));
    }

    test_section("operator+=(const Vector3i&)");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy += v2;
            return v1_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3i(-2, 6, 97));
    }

    test_section("operator-(const Vector3i&)");
    {
        constexpr auto result = v2 - v1;
        TEST_ASSERT(result == nnm::Vector3i(-4, 2, 103));
    }

    test_section("operator-=(const Vector3i&)");
    {
        constexpr auto result = [=] {
            auto v2_copy = v2;
            v2_copy -= v1;
            return v2_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3i(-4, 2, 103));
    }

    test_section("operator*(const Vector3i&)");
    {
        constexpr auto result = v1 * v2;
        TEST_ASSERT(result == nnm::Vector3i(-3, 8, -300));
    }

    test_section("operator*=(const Vector3i&)");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy *= v2;
            return v1_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3i(-3, 8, -300));
    }

    test_section("operator*(int)");
    {
        constexpr auto result = v1 * 2;
        TEST_ASSERT(result == nnm::Vector3i(2, 4, -6));
    }

    test_section("operator*(int, const Vector3i&)");
    {
        constexpr auto result = 2 * v1;
        TEST_ASSERT(result == nnm::Vector3i(2, 4, -6));
    }

    test_section("operator*=(int)");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy *= 2;
            return v1_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3i(2, 4, -6));
    }

    test_section("operator/(const Vector3i&)");
    {
        constexpr auto result = v2 / v1;
        TEST_ASSERT(result == nnm::Vector3i(-3, 2, -33));
    }

    test_section("operator/=(const Vector3i&)");
    {
        constexpr auto result = [=] {
            auto v2_copy = v2;
            v2_copy /= v1;
            return v2_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3i(-3, 2, -33));
    }

    test_section("operator/(int)");
    {
        constexpr auto result = v2 / 2;
        TEST_ASSERT(result == nnm::Vector3i(-1, 2, 50));
    }

    test_section("operator/(int, const Vector3i&)");
    {
        constexpr auto result = 2 / v1;
        TEST_ASSERT(result == nnm::Vector3i(2, 1, 0));
    }

    test_section("operator/=(int)");
    {
        constexpr auto result = [=] {
            auto v2_copy = v2;
            v2_copy /= 2;
            return v2_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3i(-1, 2, 50));
    }

    test_section("operator%(const Vector3i&)");
    {
        constexpr auto result = v1 % v2;
        TEST_ASSERT(result == nnm::Vector3i(1, 2, -3));
    }

    test_section("operator%=(const Vector3i&)");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy %= v2;
            return v1_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3i(1, 2, -3));
    }

    test_section("operator%(int)");
    {
        constexpr auto result = v1 % 2;
        TEST_ASSERT(result == nnm::Vector3i(1, 0, -1));
    }

    test_section("operator%(int, const Vector3i&)");
    {
        constexpr auto result = 3 % v2;
        TEST_ASSERT(result == nnm::Vector3i(0, 3, 3));
    }

    test_section("operator%=(int)");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy %= 2;
            return v1_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3i(1, 0, -1));
    }

    test_section("operator+");
    {
        constexpr auto result = +v1;
        TEST_ASSERT(result == v1);
    }

    test_section("operator-");
    {
        constexpr auto result = -v1;
        TEST_ASSERT(result == nnm::Vector3i(-1, -2, 3));
    }

    test_section("operator<");
    {
        constexpr auto result = v2 < v1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(v1 < v2);
    }

    test_section("operator bool");
    {
        constexpr auto result = static_cast<bool>(v1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(static_cast<bool>(nnm::Vector3i(0, 0, 0)));
    }

    test_section("hash");
    {
        constexpr nnm::Vector3i v { 1, -2, 3 };
        const auto _ = nnm::Vector3ii::Hash()(v);
    }
}
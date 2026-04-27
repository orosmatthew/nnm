#include "tests.hpp"

void segment3_tests()
{
    test_case("Segment3");

    test_section("Segment3()");
    {
        constexpr nnm::Segment3f s { };
        TEST_ASSERT(s.start == nnm::Point3f::zero());
        TEST_ASSERT(s.end == nnm::Point3f(1.0f, 0.0f, 0.0f));
    }

    test_section("Segment3(const Vector3&, const Vector3&)");
    {
        constexpr nnm::Segment3f s { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        TEST_ASSERT(s.start == nnm::Point3f(1.0f, -2.0f, 3.0f));
        TEST_ASSERT(s.end == nnm::Point3f(-4.0f, 5.0f, -6.0f));
    }

    test_section("Segment3(const Segment3<Other>&)");
    {
        constexpr nnm::Segment3d s1 { { 1.0, -2.0, 3.0 }, { -4.0, 5.0, -6.0 } };
        constexpr nnm::Segment3f s2 { s1 };
        TEST_ASSERT(s2.start.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(s2.end.approx_equal({ -4.0f, 5.0f, -6.0f }));
    }

    constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };

    test_section("collapse_point");
    {
        constexpr std::optional<nnm::Point3f> r1 = s1.collapse_point();
        TEST_ASSERT_FALSE(r1.has_value());
        constexpr nnm::Segment3f degen_point { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f } };
        constexpr std::optional<nnm::Point3f> r2 = degen_point.collapse_point();
        TEST_ASSERT(r2.has_value() && r2.value().approx_equal({ 1.0f, 1.0f, 1.0f }));
    }

    test_section("collinear(const Vector3&)");
    {
        constexpr auto result = s1.collinear({ 2.9833236933f, -4.7766531707f, 6.569982648f });
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(s1.collinear({ 0.0f, 0.0f, 0.0f }));
        TEST_ASSERT(s1.collinear({ -1.4205585602f, 1.3887819843f, -1.3570054084f }));
        TEST_ASSERT(s1.collinear({ -6.1127619882f, 7.9578667834f, -9.8029715787f }));
    }

    test_section("collinear(const Line3&)");
    {
        constexpr auto result = s1.collinear(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_FALSE(s1.collinear(*nnm::Line3f::from_points({ 2.0f, -1.0f, 4.0f }, { -3.0f, 6.0f, -5.0f })));
        TEST_ASSERT(s1.collinear(*nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f })));
        TEST_ASSERT(s1.collinear(*nnm::Line3f::from_points({ -4.0f, 5.0f, -6.0f }, { 1.0f, -2.0f, 3.0f })));
    }

    test_section("collinear(const Ray3&)");
    {
        TEST_ASSERT_FALSE(s1.collinear(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f })));
        constexpr auto result = s1.collinear(
            nnm::Ray3f({ 2.9833236933f, -4.7766531707f, 6.569982648f }, { -0.40161f, 0.562254f, -0.722897f }));
        TEST_ASSERT(result);
        TEST_ASSERT(
            s1.collinear(nnm::Ray3f({ 2.9833236933f, -4.7766531707f, 6.569982648f }, s1.start.direction(s1.end))));
        TEST_ASSERT(
            s1.collinear(nnm::Ray3f({ -1.4205585602f, 1.3887819843f, -1.3570054084f }, s1.end.direction(s1.start))));
        TEST_ASSERT(
            s1.collinear(nnm::Ray3f({ -1.4205585602f, 1.3887819843f, -1.3570054084f }, s1.start.direction(s1.end))));
        TEST_ASSERT(
            s1.collinear(nnm::Ray3f({ -6.1127619882f, 7.9578667834f, -9.8029715787f }, s1.end.direction(s1.start))));
        TEST_ASSERT(
            s1.collinear(nnm::Ray3f({ -6.1127619882f, 7.9578667834f, -9.8029715787f }, s1.start.direction(s1.end))));
    }

    test_section("collinear(const Segment3&)");
    {
        constexpr auto result = s1.collinear(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(s1.collinear(s1));
        TEST_ASSERT(s1.collinear(
            nnm::Segment3f(
                { 2.9833236933f, -4.7766531707f, 6.569982648f }, { 4.5074673515f, -6.9104542922f, 9.3134412328f })));
        TEST_ASSERT(s1.collinear(
            nnm::Segment3f(
                { -6.1127619882f, 7.9578667834f, -9.8029715787f },
                { -9.0362240787f, 12.0507137102f, -15.0652033417f })));
        TEST_ASSERT_FALSE(s1.collinear(nnm::Segment3f({ 0.0f, -3.0f, 2.0f }, { -5.0f, 4.0f, -7.0f })))
    ;}

    constexpr nnm::Segment3f s4 { { 1.0f, -2.0f, 3.0f }, { 2.0f, -3.0f, 4.0f } };

    test_section("coplanar(const Line3&)");
    {
        constexpr nnm::Line3f l1 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };
        constexpr auto result = s4.coplanar(l1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(s4.coplanar(nnm::Line3f::axis_x()));
        auto l2 = nnm::Line3f::from_points(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        TEST_ASSERT(s4.coplanar(*l2));
    }

    test_section("coplanar(const Ray3&)");
    {
        constexpr auto result
            = s4.coplanar(nnm::Ray3f({ 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f }));
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(s4.coplanar(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x())));
        auto r1 = nnm::Ray3f::from_point_to_point(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        TEST_ASSERT(s4.coplanar(r1));
    }

    test_section("coplanar(const Segment3&)");
    {
        constexpr auto result = s4.coplanar(s4);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(s4.coplanar(nnm::Segment3f(nnm::Point3f::zero(), { 1.0f, 0.0f, 0.0f })));
        auto s5 = nnm::Segment3f(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        TEST_ASSERT(s4.coplanar(s5));
    }

    test_section("coplanar(const Plane&)");
    {
        constexpr auto result = s4.coplanar(nnm::PlaneF::xy());
        TEST_ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        TEST_ASSERT(s4.coplanar(plane));
    }

    test_section("coplanar(const Triangle3&)");
    {
        TEST_ASSERT_FALSE(
            s4.coplanar(nnm::Triangle3f({ 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f })));
        TEST_ASSERT(s4.coplanar(
            nnm::Triangle3f(
                { -4.7984678398f, -1.8092603063f, 4.2111923428f },
                { -0.003134965f, -3.0097031925f, 4.5129127318f },
                { -4.5435928528f, -3.1536294284f, 5.8279349987f })));
    }

    test_section("contains");
    {
        constexpr auto result = s1.contains({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_FALSE(s1.contains({ 2.9833236933f, -4.7766531707f, 6.569982648f }));
        TEST_ASSERT(s1.contains({ -1.4205585602f, 1.3887819843f, -1.3570054084f }));
        TEST_ASSERT_FALSE(s1.contains({ -6.1127619882f, 7.9578667834f, -9.8029715787f }));
    }

    test_section("distance_sqrd(const Vector3&)");
    {
        constexpr auto d1 = s1.distance_sqrd({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(d1, 0.34838709676763f));
        constexpr auto d2 = s1.distance_sqrd({ -5.0f, 7.0f, -7.0f });
        TEST_ASSERT(nnm::approx_equal(d2, 6.0f));
        constexpr auto d3 = s1.distance_sqrd({ 0.0f, -5.0f, 3.0f });
        TEST_ASSERT(nnm::approx_equal(d3, 10.0f));
        constexpr auto d4 = s1.distance_sqrd({ -1.4205585602f, 1.3887819843f, -1.3570054084f });
        TEST_ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance_sqrd(const Line3&)");
    {
        constexpr auto d1 = s1.distance_sqrd(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(d1, 0.06923076776146f));
        constexpr auto d2 = s1.distance_sqrd(nnm::Line3f({ -6.0f, -4.0f, 7.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 20.0f));
        constexpr auto d3 = s1.distance_sqrd(nnm::Line3f({ -6.0f, 7.0f, -7.0f }, { 0.0f, 0.0f, -1.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 8.0f));
    }

    test_section("distance_sqrd(const Ray3&)");
    {
        constexpr auto d1 = s1.distance_sqrd(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d1, 0.34838709676763f));
        constexpr auto d2 = s1.distance_sqrd(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.06923076776146f));
        constexpr auto d3 = s1.distance_sqrd(nnm::Ray3f({ 2.0f, -4.0f, 3.0f }, { 0.57735f, -0.57735f, 0.57735f }));
        TEST_ASSERT(nnm::approx_equal(d3, 5.0f));
        constexpr auto d4 = s1.distance_sqrd(nnm::Ray3f({ 2.0f, -4.0f, 3.0f }, { -0.57735f, 0.57735f, -0.57735f }));
        TEST_ASSERT(nnm::approx_equal(d4, 1.5f));
        constexpr auto d5 = s1.distance_sqrd(nnm::Ray3f({ -5.0f, 7.0f, -7.0f }, { -0.98387f, 0.178885f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d5, 6.0f));
        constexpr auto d6 = s1.distance_sqrd(nnm::Ray3f({ -5.0f, 7.0f, -7.0f }, { 0.492366f, -0.615457f, 0.615457f }));
        TEST_ASSERT(nnm::approx_equal(d6, 0.35217364711461f));
        constexpr auto d7 = s1.distance_sqrd(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { -0.597615f, 0.577107f, -0.556599f }));
        TEST_ASSERT(nnm::approx_zero(d7));
    }

    test_section("distance_sqrd(const Segment3&)");
    {
        constexpr auto d1 = s1.distance_sqrd(s1);
        TEST_ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = s1.distance_sqrd(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.34838709676763f));
        constexpr auto d3 = s1.distance_sqrd(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 0.06923076776146f));
        constexpr auto d4 = s1.distance_sqrd(nnm::Segment3f({ -2.0f, 0.0f, 0.0f }, { -8.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d4, 1.76774193542868f));
        constexpr auto d5 = s1.distance_sqrd(nnm::Segment3f({ 4.0f, -4.0f, 6.0f }, { 5.0f, -4.0f, 6.0f }));
        TEST_ASSERT(nnm::approx_equal(d5, 22.0f));
        constexpr auto d6 = s1.distance_sqrd(nnm::Segment3f({ -5.0f, -4.0f, 6.0f }, { 5.0f, -4.0f, 6.0f }));
        TEST_ASSERT(nnm::approx_equal(d6, 13.0f));
        constexpr auto d7 = s1.distance_sqrd(nnm::Segment3f({ -3.0f, -4.0f, 6.0f }, { -5.0f, -4.0f, 6.0f }));
        TEST_ASSERT(nnm::approx_equal(d7, 29.0f));
        constexpr auto d8 = s1.distance_sqrd(nnm::Segment3f({ -5.0f, 7.0f, -2.0f }, { -5.0f, 7.0f, -1.0f }));
        TEST_ASSERT(nnm::approx_equal(d8, 21.0f));
        constexpr auto d9 = s1.distance_sqrd(nnm::Segment3f({ -5.0f, 7.0f, -10.0f }, { -5.0f, 7.0f, -1.0f }));
        TEST_ASSERT(nnm::approx_equal(d9, 5.0f));
        constexpr auto d10 = s1.distance_sqrd(nnm::Segment3f({ -5.0f, 7.0f, -8.0f }, { -5.0f, 7.0f, -9.0f }));
        TEST_ASSERT(nnm::approx_equal(d10, 9.0f));
        constexpr auto d11
            = s1.distance_sqrd(nnm::Segment3f({ 1.3429285263f, 1.4817304819f, -0.7047254731f }, { -2.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(d11));
    }

    test_section("distance_sqrd(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto d1 = nnm::Segment3f { nnm::Point3f::zero(), { 3.0f, 0.0f, 0.0f } }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d1, 2.0f));
        constexpr auto d2 = nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, { 200.0f, -4.0f, -4.0f } }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d2, 18.0f));
        constexpr auto d3 = nnm::Segment3f { nnm::Point3f::zero(), { -100.0f, -4.0f, -4.0f } }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_zero(d3));
        constexpr auto d4 = nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, nnm::Point3f::zero() }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 3.0f, 0.0f } }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d5, 2.0f));
        constexpr auto d6 = nnm::Segment3f { { 0.0f, 3.0f, 0.0f }, nnm::Point3f::zero() }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d6, 2.0f));
        constexpr auto d7 = nnm::Segment3f { { 0.0f, -4.0f, 0.0f }, { 0.0f, -8.0f, 0.0f } }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d7, 2.0f));
        constexpr auto d8 = nnm::Segment3f { { 0.0f, -8.0f, 0.0f }, { 0.0f, -4.0f, 0.0f } }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d8, 2.0f));
    }

    test_section("distance_sqrd(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr auto d1 = nnm::Segment3f({ -1.0f, 2.0f, 0.0f }, { -1.0f, 3.0f, 0.0f }).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_equal(d1, 2.36885245894616f));
        constexpr auto d2 = nnm::Segment3f({ -1.0f, 3.0f, 0.0f }, { -1.0f, 2.0f, 0.0f }).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_equal(d2, 2.36885245894616f));
        constexpr auto d3 = nnm::Segment3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_zero(d3));
        constexpr auto d4 = nnm::Segment3f({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = nnm::Segment3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_equal(d5, 0.29508196726188f));
        constexpr auto d6 = nnm::Segment3f({ 0.0f, 10.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_equal(d6, 0.29508196726188f));
    }

    test_section("distance_sqrd(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr auto result1 = nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } }.distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        constexpr auto result2 = nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } }.distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_zero(result2));
        constexpr auto result3 = nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, 10.0f, -8.0f } }.distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4 = nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, -10.0f, 12.0f } }.distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(result4, 2.0f))
        ;constexpr auto result5 = nnm::Segment3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 11.0f, 11.0f } }.distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        constexpr auto result6
            = nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } }.distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result6, 1.0f));
        constexpr auto result7
            = nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } }.distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result7));
        constexpr auto result8
            = nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, 8.0f, 0.0f } }.distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result8));
        constexpr auto result9
            = nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, -12.0f, 0.0f } }.distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result9, 4.0f));
        constexpr auto result10
            = nnm::Segment3f { { -3.0f, -2.0f, 3.0f }, { -3.0f, 8.0f, 3.0f } }.distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result10, 9.0f));
        constexpr auto result11
            = nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 10.0f, 0.0f } }.distance_sqrd(r_degen_point);
        TEST_ASSERT(nnm::approx_equal(result11, 7.25f));
        constexpr auto result12
            = nnm::Segment3f { { -2.5f, 1.0f, 20.0f }, { -2.5f, 1.0f, -20.0f } }.distance_sqrd(r_degen_point);
        TEST_ASSERT(nnm::approx_zero(result12));
    }

    test_section("distance_sqrd(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        constexpr float r1 = nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 100.0f, 0.0f, 0.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 0.25f));
        constexpr float r2 = nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 100.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3 = nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -100.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r3, 0.25f));
    }

    test_section("distance_sqrd(const Box&)");
    {
        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        constexpr float r1 = nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 100.0f, 0.0f, 0.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 1.5183982895123f));
        constexpr float r2 = nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -100.0f, 0.0f, 0.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r2, 1.9362916305822f));
        constexpr float r3 = nnm::Segment3f({ 0.0f, 0.0f, 1.5f }, { 0.0f, 100.0f, 0.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r3, 0.07169918465782f));
        constexpr float r4 = nnm::Segment3f({ 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 100.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_zero(r4));
        constexpr float r5 = nnm::Segment3f({ 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -100.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r5, 1.9362916305822f));
    }

    test_section("distance(const Vector3&)");
    {
        const auto d1 = s1.distance({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(d1, 0.5902432522f));
        const auto d2 = s1.distance({ -5.0f, 7.0f, -7.0f });
        TEST_ASSERT(nnm::approx_equal(d2, 2.4494897428f));
        const auto d3 = s1.distance({ 0.0f, -5.0f, 3.0f });
        TEST_ASSERT(nnm::approx_equal(d3, 3.1622776602f));
        const auto d4 = s1.distance({ -1.4205585602f, 1.3887819843f, -1.3570054084f });
        TEST_ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance(const Line3&)");
    {
        const auto d1 = s1.distance(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(d1, 0.263117403f));
        const auto d2 = s1.distance(nnm::Line3f({ -6.0f, -4.0f, 7.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 4.472135955f));
        const auto d3 = s1.distance(nnm::Line3f({ -6.0f, 7.0f, -7.0f }, { 0.0f, 0.0f, -1.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 2.8284271247f));
    }

    test_section("distance(const Ray3&)");
    {
        const auto d1 = s1.distance(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d1, 0.5902432522f));
        const auto d2 = s1.distance(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.263117403f));
        const auto d3 = s1.distance(nnm::Ray3f::from_point_to_point({ 2.0f, -4.0f, 3.0f }, { 3.0f, -5.0f, 4.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 2.2360679775f));
        const auto d4 = s1.distance(nnm::Ray3f::from_point_to_point({ 2.0f, -4.0f, 3.0f }, { 1.0f, -3.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_equal(d4, 1.2247448f));
        const auto d5 = s1.distance(nnm::Ray3f::from_point_to_point({ -5.0f, 7.0f, -7.0f }, { -6.0f, 9.0f, -7.0f }));
        TEST_ASSERT(nnm::approx_equal(d5, 2.4494897428f));
        const auto d6 = s1.distance(nnm::Ray3f::from_point_to_point({ -5.0f, 7.0f, -7.0f }, { -1.0f, 2.0f, -2.0f }));
        TEST_ASSERT(nnm::approx_equal(d6, 0.593442202f));
        const auto d7 = s1.distance(
            nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.3814812713f, 1.3340737798f, -1.2866662883f }));
        TEST_ASSERT(nnm::approx_zero(d7));
    }

    test_section("distance(const Segment3&)");
    {
        const auto d1 = s1.distance(s1);
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = s1.distance(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.5902432522f));
        const auto d3 = s1.distance(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 0.263117403f));
        const auto d4 = s1.distance(nnm::Segment3f({ -2.0f, 0.0f, 0.0f }, { -8.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d4, 1.3295645661f));
        const auto d5 = s1.distance(nnm::Segment3f({ 4.0f, -4.0f, 6.0f }, { 5.0f, -4.0f, 6.0f }));
        TEST_ASSERT(nnm::approx_equal(d5, 4.6904157598f));
        const auto d6 = s1.distance(nnm::Segment3f({ -5.0f, -4.0f, 6.0f }, { 5.0f, -4.0f, 6.0f }));
        TEST_ASSERT(nnm::approx_equal(d6, 3.6055512755f));
        const auto d7 = s1.distance(nnm::Segment3f({ -3.0f, -4.0f, 6.0f }, { -5.0f, -4.0f, 6.0f }));
        TEST_ASSERT(nnm::approx_equal(d7, 5.3851648071f));
        const auto d8 = s1.distance(nnm::Segment3f({ -5.0f, 7.0f, -2.0f }, { -5.0f, 7.0f, -1.0f }));
        TEST_ASSERT(nnm::approx_equal(d8, 4.582575695f));
        const auto d9 = s1.distance(nnm::Segment3f({ -5.0f, 7.0f, -10.0f }, { -5.0f, 7.0f, -1.0f }));
        TEST_ASSERT(nnm::approx_equal(d9, 2.2360679775f));
        const auto d10 = s1.distance(nnm::Segment3f({ -5.0f, 7.0f, -8.0f }, { -5.0f, 7.0f, -9.0f }));
        TEST_ASSERT(nnm::approx_equal(d10, 3.0f));
        const auto d11
            = s1.distance(nnm::Segment3f({ 1.3429285263f, 1.4817304819f, -0.7047254731f }, { -2.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(d11));
    }

    test_section("distance(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto d1 = nnm::Segment3f { nnm::Point3f::zero(), { 3.0f, 0.0f, 0.0f } }.distance(p2);
        TEST_ASSERT(nnm::approx_equal(d1, nnm::sqrt(2.0f)));
        constexpr auto d2 = nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, { 200.0f, -4.0f, -4.0f } }.distance(p2);
        TEST_ASSERT(nnm::approx_equal(d2, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d3 = nnm::Segment3f { nnm::Point3f::zero(), { -100.0f, -4.0f, -4.0f } }.distance(p2);
        TEST_ASSERT(nnm::approx_zero(d3));
        constexpr auto d4 = nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, nnm::Point3f::zero() }.distance(p2);
        TEST_ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 3.0f, 0.0f } }.distance(p2);
        TEST_ASSERT(nnm::approx_equal(d5, nnm::sqrt(2.0f)));
        constexpr auto d6 = nnm::Segment3f { { 0.0f, 3.0f, 0.0f }, nnm::Point3f::zero() }.distance(p2);
        TEST_ASSERT(nnm::approx_equal(d6, nnm::sqrt(2.0f)));
        constexpr auto d7 = nnm::Segment3f { { 0.0f, -4.0f, 0.0f }, { 0.0f, -8.0f, 0.0f } }.distance(p2);
        TEST_ASSERT(nnm::approx_equal(d7, nnm::sqrt(2.0f)));
        constexpr auto d8 = nnm::Segment3f { { 0.0f, -8.0f, 0.0f }, { 0.0f, -4.0f, 0.0f } }.distance(p2);
        TEST_ASSERT(nnm::approx_equal(d8, nnm::sqrt(2.0f)));
    }

    test_section("distance(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        const auto d1 = nnm::Segment3f({ -1.0f, 2.0f, 0.0f }, { -1.0f, 3.0f, 0.0f }).distance(t1);
        TEST_ASSERT(nnm::approx_equal(d1, 1.5391076827f));
        const auto d2 = nnm::Segment3f({ -1.0f, 3.0f, 0.0f }, { -1.0f, 2.0f, 0.0f }).distance(t1);
        TEST_ASSERT(nnm::approx_equal(d2, 1.5391076827f));
        const auto d3 = nnm::Segment3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }).distance(t1);
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = nnm::Segment3f({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }).distance(t1);
        TEST_ASSERT(nnm::approx_zero(d4));
        const auto d5 = nnm::Segment3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }).distance(t1);
        TEST_ASSERT(nnm::approx_equal(d5, 0.5432144763f));
        const auto d6 = nnm::Segment3f({ 0.0f, 10.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }).distance(t1);
        TEST_ASSERT(nnm::approx_equal(d6, 0.5432144763f));
    }

    test_section("distance(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        const auto result1 = nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } }.distance(r1);
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        const auto result2 = nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } }.distance(r1);
        TEST_ASSERT(nnm::approx_zero(result2));
        const auto result3 = nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, 10.0f, -8.0f } }.distance(r1);
        TEST_ASSERT(nnm::approx_zero(result3));
        const auto result4 = nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, -10.0f, 12.0f } }.distance(r1);
        TEST_ASSERT(nnm::approx_equal(result4, 1.4142135624f))
        ;const auto result5 = nnm::Segment3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 11.0f, 11.0f } }.distance(r1);
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        const auto result6 = nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } }.distance(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result6, 1.0f));
        const auto result7 = nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } }.distance(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result7));
        const auto result8 = nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, 8.0f, 0.0f } }.distance(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result8));
        const auto result9 = nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, -12.0f, 0.0f } }.distance(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result9, 2.0f));
        const auto result10 = nnm::Segment3f { { -3.0f, -2.0f, 3.0f }, { -3.0f, 8.0f, 3.0f } }.distance(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result10, 3.0f));
        const auto result11 = nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 10.0f, 0.0f } }.distance(r_degen_point);
        TEST_ASSERT(nnm::approx_equal(result11, 2.6925824036f));
        const auto result12
            = nnm::Segment3f { { -2.5f, 1.0f, 20.0f }, { -2.5f, 1.0f, -20.0f } }.distance(r_degen_point);
        TEST_ASSERT(nnm::approx_zero(result12));
    }

    test_section("distance(const Sphere&)");
    {
        constexpr nnm::SphereF sphere { { 1.0f, -2.0f, 3.0f }, 1.5f };
        constexpr nnm::SphereF s_degen { { 0.0f, 0.0f, 0.0f }, 0.0f };
        const auto r1 = nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { 10.0f, -2.0f, 3.0f }).distance(sphere);
        TEST_ASSERT(nnm::approx_zero(r1));
        const auto r2 = nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { -10.0f, -2.0f, 3.0f }).distance(sphere);
        TEST_ASSERT(nnm::approx_equal(r2, 1.5f));
        const auto r3 = nnm::Segment3f({ 10.0f, -2.0f, 3.0f }, { 20.0f, -2.0f, 3.0f }).distance(sphere);
        TEST_ASSERT(nnm::approx_equal(r3, 7.5f));
        const auto r4 = nnm::Segment3f(nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f }).distance(sphere);
        TEST_ASSERT(nnm::approx_equal(r4, 2.1055512755f));
        const auto r5 = nnm::Segment3f(nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f }).distance(sphere);
        TEST_ASSERT(nnm::approx_equal(r5, 2.2416573868f));
        const auto r6 = nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }).distance(s_degen);
        TEST_ASSERT(nnm::approx_equal(r6, 1.0f));
        const auto r7 = nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }).distance(s_degen);
        TEST_ASSERT(nnm::approx_zero(r7));
    }

    test_section("distance(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        const float r1 = nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 100.0f, 0.0f, 0.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 0.5f));
        const float r2 = nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 100.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_zero(r2));
        const float r3 = nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -100.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r3, 0.5f));
    }

    test_section("distance(const Box&)");
    {
        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        const float r1 = nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 100.0f, 0.0f, 0.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 1.23223305f));
        const float r2 = nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -100.0f, 0.0f, 0.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r2, 1.3915069639f));
        const float r3 = nnm::Segment3f({ 0.0f, 0.0f, 1.5f }, { 0.0f, 100.0f, 0.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r3, 0.2677670343f));
        const float r4 = nnm::Segment3f({ 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 100.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_zero(r4));
        const float r5 = nnm::Segment3f({ 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -100.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r5, 1.3915069639f));
    }

    test_section("direction_unnormalized");
    {
        constexpr auto result = s1.direction_unnormalized();
        TEST_ASSERT(result.approx_equal({ -5.0f, 7.0f, -9.0f }));
    }

    test_section("direction");
    {
        TEST_ASSERT(s1.direction().approx_equal({ -0.4016096645f, 0.5622535302f, -0.7228973960f }));
    }

    test_section("parallel(const Line3&)");
    {
        constexpr auto result = s1.parallel(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(s1.parallel(*nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f })))
        ;TEST_ASSERT(s1.parallel(*nnm::Line3f::from_points({ 3.0f, 0.0f, 5.0f }, { -2.0f, 7.0f, -4.0f })))
    ;}

    test_section("parallel(const Ray3&)");
    {
        constexpr auto result = s1.parallel(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(s1.parallel(nnm::Ray3f::from_point_to_point(s1.start, s1.end)));
        TEST_ASSERT(s1.parallel(nnm::Ray3f(s1.start + nnm::Vector3f(2.0f, -3.0f, 10.0f), -s1.direction())));
    }

    test_section("parallel(const Segment3&)");
    {
        constexpr auto result = s1.parallel(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, -2.0f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(s1.parallel(s1));
        TEST_ASSERT(s1.parallel(
            nnm::Segment3f(s1.start + nnm::Vector3f(2.0f, -2.0f, 5.0f), s1.end + nnm::Vector3f(2.0f, -2.0f, 5.0f))));
    }

    test_section("perpendicular(const Line3&)");
    {
        constexpr auto result = s1.perpendicular(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(s1.perpendicular(
            *nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { -1.1918502675f, 0.1906960428f, 0.8104581819f })));
    }

    test_section("perpendicular(const Ray3&)");
    {
        TEST_ASSERT_FALSE(
            s1.perpendicular(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, -1.0f, -1.0f })));
        constexpr auto r1 = nnm::Ray3f { { 0.0f, 0.0f, 0.0f }, { -0.819782316f, 0.131165162f, 0.557451963f } };
        TEST_ASSERT(s1.perpendicular(r1));
        constexpr auto result = s1.perpendicular(nnm::Ray3f(r1.origin, -r1.direction));
        TEST_ASSERT(result);
    }

    test_section("perpendicular(const Segment3&)");
    {
        constexpr auto result = s1.perpendicular(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(
            s1.perpendicular(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.1918502675f, 0.1906960428f, 0.8104581819f })));
        TEST_ASSERT(
            s1.perpendicular(nnm::Segment3f({ -1.1918502675f, 0.1906960428f, 0.8104581819f }, { 0.0f, 0.0f, 0.0f })));
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto result = s1.intersects(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(s1.intersects(*nnm::Line3f::from_points({ 1, 2, 3 }, { -0.666667f, -3.0476f, 0.0f })));
        TEST_ASSERT_FALSE(s1.intersects(
            *nnm::Line3f::from_points({ -6.3161401722f, -5.0466531233f, 6.9171254442f }, { 5.0f, -2.0f, 3.0f })));
        TEST_ASSERT_FALSE(s1.intersects(
            *nnm::Line3f::from_points({ 6.340530911f, 6.2880512604f, -11.4095884147f }, { -7.0f, 5.0f, -5.0f })));
        TEST_ASSERT(s1.intersects(nnm::Line3f(s1.start, s1.direction())));
    }

    test_section("intersection(const Line3&)");
    {
        constexpr auto i1 = s1.intersection(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = s1.intersection(*nnm::Line3f::from_points({ 1, 2, 3 }, { -0.666667f, -3.0476f, 0.0f }));
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ 0.0967741935f, -0.735483871f, 1.3741935484f }));
        const auto i3 = s1.intersection(
            *nnm::Line3f::from_points({ -6.3161401722f, -5.0466531233f, 6.9171254442f }, { 5.0f, -2.0f, 3.0f }));
        TEST_ASSERT_FALSE(i3.has_value());
        const auto i4 = s1.intersection(
            *nnm::Line3f::from_points({ 6.340530911f, 6.2880512604f, -11.4095884147f }, { -7.0f, 5.0f, -5.0f }));
        TEST_ASSERT_FALSE(i4.has_value());
        const auto i5 = s1.intersection(nnm::Line3f(s1.start, s1.direction()));
        TEST_ASSERT_FALSE(i5.has_value());
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr auto r1 = nnm::Ray3f { { 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        constexpr auto result = s1.intersects(r1);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point({ 1.0f, 2.0f, 3.0f }, { 2.0323377426f, 5.126508592f, 4.8582079368f })));
        TEST_ASSERT(s1.intersects(
            nnm::Ray3f::from_point_to_point({ 2.0323377426f, 5.126508592f, 4.8582079368f }, { 1.0f, 2.0f, 3.0f })));
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point({ 5.0f, -2.0f, 3.0f }, { 8.4624090164f, -1.0678129571f, 1.801473802f })));
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point({ 8.4624090164f, -1.0678129571f, 1.801473802f }, { 5.0f, -2.0f, 3.0f })));
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point(
                { -7.0f, 5.0f, -5.0f }, { -10.7888017215f, 4.6341846614f, -3.1796331959f })));
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point(
                { -10.7888017215f, 4.6341846614f, -3.1796331959f }, { -7.0f, 5.0f, -5.0f })));
        TEST_ASSERT(s1.intersects(
            nnm::Ray3f::from_point_to_point(
                { 3.1803758203f, -5.0525261484f, 6.9246764765f }, { 2.2353232409f, -3.7294525373f, 5.2235818337f })));
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point(
                { 2.2353232409f, -3.7294525373f, 5.2235818337f }, { 3.1803758203f, -5.0525261484f, 6.9246764765f })));
    }

    test_section("intersection(const Ray3&)");
    {

        constexpr auto i1 = s1.intersection(nnm::Ray3f { { 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } });
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = s1.intersection(
            nnm::Ray3f::from_point_to_point({ 1.0f, 2.0f, 3.0f }, { 2.0323377426f, 5.126508592f, 4.8582079368f }));
        TEST_ASSERT_FALSE(i2.has_value());
        const auto i3 = s1.intersection(
            nnm::Ray3f::from_point_to_point({ 2.0323377426f, 5.126508592f, 4.8582079368f }, { 1.0f, 2.0f, 3.0f }));
        TEST_ASSERT(i3.has_value() && i3.value().approx_equal({ 0.0967741935f, -0.735483871f, 1.3741935484f }));
        const auto i4 = s1.intersection(
            nnm::Ray3f::from_point_to_point({ 5.0f, -2.0f, 3.0f }, { 8.4624090164f, -1.0678129571f, 1.801473802f }));
        TEST_ASSERT_FALSE(i4.has_value());
        const auto i5 = s1.intersection(
            nnm::Ray3f::from_point_to_point({ 8.4624090164f, -1.0678129571f, 1.801473802f }, { 5.0f, -2.0f, 3.0f }));
        TEST_ASSERT_FALSE(i5.has_value());
        const auto i6 = s1.intersection(
            nnm::Ray3f::from_point_to_point(
                { -7.0f, 5.0f, -5.0f }, { -10.7888017215f, 4.6341846614f, -3.1796331959f }));
        TEST_ASSERT_FALSE(i6.has_value());
        const auto i7 = s1.intersection(
            nnm::Ray3f::from_point_to_point(
                { -10.7888017215f, 4.6341846614f, -3.1796331959f }, { -7.0f, 5.0f, -5.0f }));
        TEST_ASSERT_FALSE(i7.has_value());
        const auto i8 = s1.intersection(
            nnm::Ray3f::from_point_to_point(
                { 3.1803758203f, -5.0525261484f, 6.9246764765f }, { 2.2353232409f, -3.7294525373f, 5.2235818337f }));
        TEST_ASSERT_FALSE(i8.has_value());
        const auto i9 = s1.intersection(
            nnm::Ray3f::from_point_to_point(
                { 2.2353232409f, -3.7294525373f, 5.2235818337f }, { 3.1803758203f, -5.0525261484f, 6.9246764765f }));
        TEST_ASSERT_FALSE(i9.has_value());
    }

    test_section("intersects(const Segment3&)");
    {
        constexpr auto result = s1.intersects(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -4.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(s1.intersects(s1));
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Segment3f(s1.start + nnm::Vector3f(1.0f, 1.0f, 1.0f), s1.end + nnm::Vector3f(1.0f, 1.0f, 1.0f))));
        TEST_ASSERT(
            s1.intersects(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.3947151596f, 0.2231544255f, 0.9484063085f })));
        TEST_ASSERT_FALSE(
            s1.intersects(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.8903860212f, -0.1424617634f, -0.6054624944f })));
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Segment3f(
                { -1.3947151596f, 0.2231544255f, 0.9484063085f }, { -2.477689579f, 0.3964303326f, 1.6848289137f })));
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Segment3f(
                { 2.9228521743f, -3.1715789131f, 4.9407197828f }, { 4.4763315545f, -2.5022944544f, 4.8928270762f })));
        TEST_ASSERT_FALSE(
            s1.intersects(nnm::Segment3f({ 2.9228521743f, -3.1715789131f, 4.9407197828f }, { 1.0f, -4.0f, 5.0f })));
        TEST_ASSERT_FALSE(
            s1.intersects(nnm::Segment3f({ 1.0f, -4.0f, 5.0f }, { -0.2324762036f, -4.5309868797f, 5.0379963983f })));
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Segment3f(
                { -4.3190323788f, 3.7446637121f, -8.843567106f }, { -4.5930027693f, 5.0543673254f, -8.1018537201f })));
        TEST_ASSERT_FALSE(
            s1.intersects(nnm::Segment3f({ -4.5930027693f, 5.0543673254f, -8.1018537201f }, { -5.0f, 7.0f, -7.0f })));
        TEST_ASSERT_FALSE(
            s1.intersects(nnm::Segment3f({ -5.0f, 7.0f, -7.0f }, { -5.5960814905f, 9.8495418077f, -5.3862430547f })));
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Segment3f({ -1.3071995174f, 3.5612991571f, 3.8583174565f }, { -2.0f, 3.0f, -0.6802903382f })));
        TEST_ASSERT_FALSE(s1.intersects(
            nnm::Segment3f(
                { -2.8239641345f, 2.3324335277f, -6.0781648164f },
                { -3.5475337817f, 1.7462055396f, -10.8183445985f })));
    }

    test_section("intersection(const Segment3&");
    {
        constexpr auto i1 = s1.intersection(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -4.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = s1.intersection(s1);
        TEST_ASSERT_FALSE(i2.has_value());
        constexpr auto i3 = s1.intersection(
            nnm::Segment3f(s1.start + nnm::Vector3f(1.0f, 1.0f, 1.0f), s1.end + nnm::Vector3f(1.0f, 1.0f, 1.0f)));
        TEST_ASSERT_FALSE(i3.has_value());
        constexpr auto i4
            = s1.intersection(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.3947151596f, 0.2231544255f, 0.9484063085f }));
        TEST_ASSERT(i4.has_value() && i4.value().approx_equal({ -0.4838709677f, 0.0774193548f, 0.3290322581f }));
        constexpr auto i5
            = s1.intersection(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.8903860212f, -0.1424617634f, -0.6054624944f }));
        TEST_ASSERT_FALSE(i5.has_value());
        constexpr auto i6 = s1.intersection(
            nnm::Segment3f(
                { -1.3947151596f, 0.2231544255f, 0.9484063085f }, { -2.477689579f, 0.3964303326f, 1.6848289137f }));
        TEST_ASSERT_FALSE(i6.has_value());
        constexpr auto i7 = s1.intersection(
            nnm::Segment3f(
                { 2.9228521743f, -3.1715789131f, 4.9407197828f }, { 4.4763315545f, -2.5022944544f, 4.8928270762f }));
        TEST_ASSERT_FALSE(i7.has_value());
        constexpr auto i8
            = s1.intersection(nnm::Segment3f({ 2.9228521743f, -3.1715789131f, 4.9407197828f }, { 1.0f, -4.0f, 5.0f }));
        TEST_ASSERT_FALSE(i8.has_value());
        constexpr auto i9
            = s1.intersection(nnm::Segment3f({ 1.0f, -4.0f, 5.0f }, { -0.2324762036f, -4.5309868797f, 5.0379963983f }));
        TEST_ASSERT_FALSE(i9.has_value());
        constexpr auto i10 = s1.intersection(
            nnm::Segment3f(
                { -4.3190323788f, 3.7446637121f, -8.843567106f }, { -4.5930027693f, 5.0543673254f, -8.1018537201f }));
        TEST_ASSERT_FALSE(i10.has_value());
        constexpr auto i11 = s1.intersection(
            nnm::Segment3f({ -4.5930027693f, 5.0543673254f, -8.1018537201f }, { -5.0f, 7.0f, -7.0f }));
        TEST_ASSERT_FALSE(i11.has_value());
        constexpr auto i12 = s1.intersection(
            nnm::Segment3f({ -5.0f, 7.0f, -7.0f }, { -5.5960814905f, 9.8495418077f, -5.3862430547f }));
        TEST_ASSERT_FALSE(i12.has_value());
        constexpr auto i13 = s1.intersection(
            nnm::Segment3f({ -1.3071995174f, 3.5612991571f, 3.8583174565f }, { -2.0f, 3.0f, -0.6802903382f }));
        TEST_ASSERT_FALSE(i13.has_value());
        constexpr auto i14 = s1.intersection(
            nnm::Segment3f(
                { -2.8239641345f, 2.3324335277f, -6.0781648164f }, { -3.5475337817f, 1.7462055396f, -10.8183445985f }));
        TEST_ASSERT_FALSE(i14.has_value());
    }

    test_section("project");
    {
        constexpr auto p1 = s1.project({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(p1.approx_equal({ -0.4838709677f, 0.0774193548f, 0.3290322581f }))
        ;constexpr auto p2 = s1.project({ 2.0f, -3.0f, 4.0f });
        TEST_ASSERT(p2.approx_equal(s1.start));
        constexpr auto p3 = s1.project({ -5.0f, 7.0f, -7.0f });
        TEST_ASSERT(p3.approx_equal(s1.end));
    }

    test_section("length_sqrd");
    {
        constexpr auto l = s1.length_sqrd();
        TEST_ASSERT(nnm::approx_equal(l, 155.0f));
    }

    test_section("length");
    {
        TEST_ASSERT(nnm::approx_equal(s1.length(), 12.449899598f));
    }

    test_section("midpoint");
    {
        constexpr auto result = s1.midpoint();
        TEST_ASSERT(result.approx_equal({ -1.5f, 1.5f, -1.5f }));
    }

    test_section("translate");
    {
        constexpr nnm::Vector3f offset { 10.0f, -2.0f, 0.5f };
        constexpr auto s1t = s1.translate(offset);
        TEST_ASSERT(
            s1t.start.approx_equal(s1.start.translate(offset)) && s1t.end.approx_equal(s1.end.translate(offset)));
    }

    test_section("scale_at");
    {
        constexpr nnm::Point3f origin { -5.0f, 0.2f, 3.0f };
        constexpr nnm::Vector3f factor { 10.0f, -2.0f, 0.5f };
        constexpr auto s1s = s1.scale_at(origin, factor);
        TEST_ASSERT(
            s1s.start.approx_equal(s1.start.scale_at(origin, factor))
            && s1s.end.approx_equal(s1.end.scale_at(origin, factor)));
    }

    test_section("scale");
    {
        constexpr nnm::Vector3f factor { 10.0f, -2.0f, 0.5f };
        constexpr auto s1s = s1.scale(factor);
        TEST_ASSERT(s1s.start.approx_equal(s1.start.scale(factor)) && s1s.end.approx_equal(s1.end.scale(factor)));
    }

    test_section("rotate_axis_angle_at");
    {
        constexpr nnm::Point3f origin { -5.0f, 0.2f, 3.0f };
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = nnm::pi<float>() / 3.0f;
        const auto s1r = s1.rotate_axis_angle_at(origin, axis, angle);
        TEST_ASSERT(
            s1r.start.approx_equal(s1.start.rotate_axis_angle_at(origin, axis, angle))
            && s1r.end.approx_equal(s1.end.rotate_axis_angle_at(origin, axis, angle)));
    }

    test_section("rotate_axis_angle");
    {
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = nnm::pi<float>() / 3.0f;
        const auto s1r = s1.rotate_axis_angle(axis, angle);
        TEST_ASSERT(
            s1r.start.approx_equal(s1.start.rotate_axis_angle(axis, angle))
            && s1r.end.approx_equal(s1.end.rotate_axis_angle(axis, angle)));
    }

    test_section("rotate_quaternion_at");
    {
        constexpr nnm::Point3f origin { -5.0f, 0.2f, 3.0f };
        constexpr nnm::QuaternionF quat { 0.0f, 0.5f, 0.05f, 0.866025388f };
        constexpr auto s1r = s1.rotate_quaternion_at(origin, quat);
        TEST_ASSERT(
            s1r.start.approx_equal(s1.start.rotate_quaternion_at(origin, quat))
            && s1r.end.approx_equal(s1.end.rotate_quaternion_at(origin, quat)));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::QuaternionF quat { 0.0f, 0.5f, 0.05f, 0.866025388f };
        constexpr auto s1r = s1.rotate_quaternion(quat);
        TEST_ASSERT(
            s1r.start.approx_equal(s1.start.rotate_quaternion(quat))
            && s1r.end.approx_equal(s1.end.rotate_quaternion(quat)));
    }

    test_section("shear_x_at");
    {
        constexpr nnm::Point3f origin { -5.0f, 0.2f, 3.0f };
        constexpr float factor_y = 0.5f;
        constexpr float factor_z = -2.0f;
        constexpr auto s1s = s1.shear_x_at(origin, factor_y, factor_z);
        TEST_ASSERT(
            s1s.start.approx_equal(s1.start.shear_x_at(origin, factor_y, factor_z))
            && s1s.end.approx_equal(s1.end.shear_x_at(origin, factor_y, factor_z)));
    }

    test_section("shear_x");
    {
        constexpr float factor_y = 0.5f;
        constexpr float factor_z = -2.0f;
        constexpr auto s1s = s1.shear_x(factor_y, factor_z);
        TEST_ASSERT(
            s1s.start.approx_equal(s1.start.shear_x(factor_y, factor_z))
            && s1s.end.approx_equal(s1.end.shear_x(factor_y, factor_z)));
    }

    test_section("shear_y_at");
    {
        constexpr nnm::Point3f origin { -5.0f, 0.2f, 3.0f };
        constexpr float factor_x = 0.5f;
        constexpr float factor_z = -2.0f;
        constexpr auto s1s = s1.shear_y_at(origin, factor_x, factor_z);
        TEST_ASSERT(
            s1s.start.approx_equal(s1.start.shear_y_at(origin, factor_x, factor_z))
            && s1s.end.approx_equal(s1.end.shear_y_at(origin, factor_x, factor_z)));
    }

    test_section("shear_y");
    {
        constexpr float factor_x = 0.5f;
        constexpr float factor_z = -2.0f;
        constexpr auto s1s = s1.shear_y(factor_x, factor_z);
        TEST_ASSERT(
            s1s.start.approx_equal(s1.start.shear_y(factor_x, factor_z))
            && s1s.end.approx_equal(s1.end.shear_y(factor_x, factor_z)));
    }

    test_section("shear_z_at");
    {
        constexpr nnm::Point3f origin { -5.0f, 0.2f, 3.0f };
        constexpr float factor_x = 0.5f;
        constexpr float factor_y = -2.0f;
        constexpr auto s1s = s1.shear_z_at(origin, factor_x, factor_y);
        TEST_ASSERT(
            s1s.start.approx_equal(s1.start.shear_z_at(origin, factor_x, factor_y))
            && s1s.end.approx_equal(s1.end.shear_z_at(origin, factor_x, factor_y)));
    }

    test_section("shear_z");
    {
        constexpr float factor_x = 0.5f;
        constexpr float factor_y = -2.0f;
        constexpr auto s1s = s1.shear_z(factor_x, factor_y);
        TEST_ASSERT(
            s1s.start.approx_equal(s1.start.shear_z(factor_x, factor_y))
            && s1s.end.approx_equal(s1.end.shear_z(factor_x, factor_y)));
    }

    constexpr nnm::Segment3f s2 { { -4.0f, 5.0f, -6.0f }, { 1.0f, -2.0f, 3.0f } };
    constexpr nnm::Segment3f s3 { { 10.0f, -3.2f, 7.0f }, { 0.0f, 1.0f, -9.0f } };

    test_section("coincident");
    {
        constexpr bool r1 = s1.coincident(s2);
        TEST_ASSERT(r1);
        constexpr bool r2 = s1.coincident(s3);
        TEST_ASSERT_FALSE(r2);
        constexpr bool r3 = s2.coincident(s2);
        TEST_ASSERT(r3);
    }

    test_section("approx_equal");
    {
        constexpr bool r1 = s1.approx_equal(s2);
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = s1.approx_equal(s3);
        TEST_ASSERT_FALSE(r2);
        constexpr bool r3 = s2.approx_equal(s2);
        TEST_ASSERT(r3);
    }

    test_section("operator==");
    {
        constexpr bool r1 = s1 == s2;
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = s1 == s3;
        TEST_ASSERT_FALSE(r2);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr bool r3 = s2 == s2;
        TEST_ASSERT(r3);
    }

    test_section("operator!=");
    {
        constexpr bool r1 = s1 != s2;
        TEST_ASSERT(r1);
        constexpr bool r2 = s1 != s3;
        TEST_ASSERT(r2);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr bool r3 = s2 != s2;
        TEST_ASSERT_FALSE(r3);
    }

    test_section("operator<");
    {
        constexpr bool r1 = s1 < s2;
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = s2 < s1;
        TEST_ASSERT(r2);
    }
}


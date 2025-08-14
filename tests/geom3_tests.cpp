#include "geom3_tests.hpp"

#include <nnm/geom3.hpp>

#include "test.hpp"

// ReSharper disable once CppDFATimeOver

inline void intersections3_tests()
{
    test_case("Intersections3");

    test_section("Intersections3()");
    {
        constexpr nnm::Intersections3f i;
        ASSERT(i.empty());
    }

    test_section("Intersections3(const Vector3&)");
    {
        constexpr nnm::Intersections3f i { { 1.0f, -2.0f, 3.0f } };
        ASSERT(i.size() == 1);
        ASSERT(i.contains({ 1.0f, -2.0f, 3.0f }));
    }

    test_section("Intersections3(const Vector3&, const Vector3&)");
    {
        constexpr nnm::Intersections3f i { { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -5.0f } };
        ASSERT(i.size() == 2);
        ASSERT(i.contains({ 1.0f, -2.0f, 3.0f }) && i.contains({ -3.0, 4.0f, -5.0f }));
    }

    constexpr nnm::Intersections3f i1;
    constexpr nnm::Intersections3f i2 { { 1.0f, -2.0f, 3.0f } };
    constexpr nnm::Intersections3f i3 { { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -5.0f } };

    test_section("insert");
    {
        auto i1_copy = i1;
        i1_copy.insert({ 1.5f, -2.5f, 3.5f });
        ASSERT(i1_copy.approx_equal({ { 1.5f, -2.5f, 3.5f } }));
        auto i2_copy = i2;
        i2_copy.insert({ 1.5f, -2.5f, 3.5f });
        ASSERT(i2_copy.approx_equal({ { 1.0f, -2.0f, 3.0f }, { 1.5f, -2.5f, 3.5f } }));
        i2_copy = i2;
        i2_copy.insert({ 1.0f, -2.0f, 3.0f });
        ASSERT(i2_copy.approx_equal(i2));
        auto i3_copy = i3;
        i3_copy.insert({ 1.0f, -2.0f, 3.0f });
        ASSERT(i3_copy.approx_equal(i3));
        i3_copy = i3;
        i3_copy.insert({ -3.0f, 4.0f, -5.0f });
        ASSERT(i3_copy.approx_equal(i3));
    }

    test_section("clear");
    {
        auto i1_copy = i1;
        i1_copy.clear();
        ASSERT(i1.approx_equal(i1));
        auto i2_copy = i2;
        i2_copy.clear();
        ASSERT(i1.approx_equal(i1));
        auto i3_copy = i3;
        i3_copy.clear();
        ASSERT(i3_copy.approx_equal(i1));
    }

    test_section("size");
    {
        constexpr auto result = i1.size(); // NOLINT(*-container-size-empty)
        ASSERT(result == 0);
        ASSERT(i2.size() == 1);
        ASSERT(i3.size() == 2);
    }

    test_section("capacity");
    {
        ASSERT(nnm::Intersections3f::capacity() == 2);
    }

    test_section("begin");
    {
        ASSERT(i1.begin() == i1.data());
        ASSERT(i2.begin() == i2.data());
        ASSERT(i3.begin() == i3.data());
    }

    test_section("end");
    {
        ASSERT(i1.end() == i1.data() + 1);
        ASSERT(i2.end() == i2.data() + 2);
        ASSERT(i3.end() == i3.data() + 3);
    }

    test_section("approx_equal");
    {
        constexpr auto result = i1.approx_equal({});
        ASSERT(result);
        ASSERT_FALSE(i1.approx_equal(i2));
        ASSERT(i2.approx_equal({ { 1.0f, -2.0f, 3.0f } }));
        ASSERT_FALSE(i2.approx_equal(i1));
        ASSERT_FALSE(i2.approx_equal(i3));
        ASSERT(i3.approx_equal({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -5.0f } }));
        ASSERT(i3.approx_equal({ { -3.0f, 4.0f, -5.0f }, { 1.0f, -2.0f, 3.0f } }));
        ASSERT_FALSE(i3.approx_equal(i1));
        ASSERT_FALSE(i3.approx_equal(i2));
    }

    test_section("contains");
    {
        constexpr auto result = i1.contains({ 1.0f, -2.0f, 3.0f });
        ASSERT_FALSE(result);
        ASSERT(i2.contains({ 1.0f, -2.0f, 3.0f }));
        ASSERT_FALSE(i2.contains({ -3.0f, 4.0f, -5.0f }));
        ASSERT(i3.contains({ 1.0f, -2.0f, 3.0f }));
        ASSERT(i3.contains({ -3.0f, 4.0f, -5.0f }));
        ASSERT_FALSE(i3.contains({ 1.5f, -2.5f, 3.5f }));
    }

    test_section("empty");
    {
        constexpr auto result = i1.empty();
        ASSERT(result);
        ASSERT_FALSE(i2.empty());
        ASSERT_FALSE(i3.empty());
    }

    test_section("operator==");
    {
        constexpr auto result = i1 == nnm::Intersections3f(); // NOLINT(*-container-size-empty)
        ASSERT(result);
        ASSERT_FALSE(i1 == i2);
        ASSERT(i2 == nnm::Intersections3f({ 1.0f, -2.0f, 3.0f }));
        ASSERT_FALSE(i2 == i1);
        ASSERT_FALSE(i2 == i3);
        ASSERT(i3 == nnm::Intersections3f({ 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -5.0f }));
        ASSERT(i3 == nnm::Intersections3f({ -3.0f, 4.0f, -5.0f }, { 1.0f, -2.0f, 3.0f }));
        ASSERT_FALSE(i3 == i1);
        ASSERT_FALSE(i3 == i2);
    }

    test_section("operator!=");
    {
        constexpr auto result = i1 != nnm::Intersections3f(); // NOLINT(*-container-size-empty)
        ASSERT_FALSE(result);
        ASSERT(i1 != i2);
        ASSERT_FALSE(i2 != nnm::Intersections3f({ 1.0f, -2.0f, 3.0f }));
        ASSERT(i2 != i1);
        ASSERT(i2 != i3);
        ASSERT_FALSE(i3 != nnm::Intersections3f({ 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -5.0f }));
        ASSERT_FALSE(i3 != nnm::Intersections3f({ -3.0f, 4.0f, -5.0f }, { 1.0f, -2.0f, 3.0f }));
        ASSERT(i3 != i1);
        ASSERT(i3 != i2);
    }
}

inline void line3_tests()
{
    test_case("Line3");

    test_section("Line3()");
    {
        constexpr nnm::Line3f l {};
        ASSERT(l.origin == nnm::Vector3f::zero());
        ASSERT(l.direction == nnm::Vector3f::axis_x());
    }

    test_section("Line3(const Vector3&, const Vector3&)");
    {
        constexpr nnm::Line3f l { { -1.0f, 2.0f, 3.0f }, { 5.0f, 6.0f, -7.0f } };
        ASSERT(l.origin == nnm::Vector3f(-1.0f, 2.0f, 3.0f));
        ASSERT(l.direction == nnm::Vector3f(5.0f, 6.0f, -7.0f));
    }

    test_section("Line3(const Line3<Other>&)");
    {
        constexpr nnm::Line3f l1 { { -1.0, 2.0, 3.0 }, { 5.0, 6.0, -7.0 } };
        constexpr nnm::Line3d l2 { l1 };
        ASSERT(l2.origin.approx_equal({ -1.0f, 2.0f, 3.0f }));
        ASSERT(l2.direction.approx_equal({ 5.0f, 6.0f, -7.0f }));
    }

    test_section("from_points");
    {
        const auto l = nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { 4.0f, -5.0f, 7.0f });
        ASSERT(l.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(l.direction.approx_equal({ 0.5144957554f, -0.5144957554f, 0.6859943406f }));
    }

    test_section("from_segment");
    {
        const auto l = nnm::Line3f::from_segment(nnm::Segment3f { { 1.0f, -2.0f, 3.0f }, { 4.0f, -5.0f, 7.0f } });
        ASSERT(l.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(l.direction.approx_equal({ 0.5144957554f, -0.5144957554f, 0.6859943406f }));
    }

    test_section("from_ray");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -5.0f, 6.0f, -7.0f } };
        constexpr auto l1 = nnm::Line3f::from_ray(r1);
        ASSERT(l1.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(l1.direction.approx_equal({ -5.0f, 6.0f, -7.0f }));
    }

    test_section("axis_x");
    {
        constexpr auto l = nnm::Line3f::axis_x();
        ASSERT(l.origin.approx_equal({ 0.0f, 0.0f, 0.0f }));
        ASSERT(l.direction.approx_equal({ 1.0f, 0.0f, 0.0f }));
    }

    test_section("axis_y");
    {
        constexpr auto l = nnm::Line3f::axis_y();
        ASSERT(l.origin.approx_equal({ 0.0f, 0.0f, 0.0f }));
        ASSERT(l.direction.approx_equal({ 0.0f, 1.0f, 0.0f }));
    }

    test_section("axis_z");
    {
        constexpr auto l = nnm::Line3f::axis_z();
        ASSERT(l.origin.approx_equal({ 0.0f, 0.0f, 0.0f }));
        ASSERT(l.direction.approx_equal({ 0.0f, 0.0f, 1.0f }));
    }

    test_section("axis_x_offset");
    {
        constexpr auto l = nnm::Line3f::axis_x_offset(-1.0f, 2.0f);
        ASSERT(l.origin.approx_equal({ 0.0f, -1.0f, 2.0f }));
        ASSERT(l.direction.approx_equal({ 1.0f, 0.0f, 0.0f }));
    }

    test_section("axis_y_offset");
    {
        constexpr auto l = nnm::Line3f::axis_y_offset(-1.0f, 2.0f);
        ASSERT(l.origin.approx_equal({ -1.0f, 0.0f, 2.0f }));
        ASSERT(l.direction.approx_equal({ 0.0f, 1.0f, 0.0f }));
    }

    test_section("axis_z_offset");
    {
        constexpr auto l = nnm::Line3f::axis_z_offset(-1.0f, 2.0f);
        ASSERT(l.origin.approx_equal({ -1.0f, 2.0f, 0.0f }));
        ASSERT(l.direction.approx_equal({ 0.0f, 0.0f, 1.0f }));
    }

    constexpr nnm::Line3f l1 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };

    test_section("parallel_containing");
    {
        constexpr auto l = l1.parallel_containing({ -5.0f, 6.0f, -7.0f });
        ASSERT(l.origin.approx_equal({ -5.0f, 6.0f, -7.0f }));
        ASSERT(l.direction.approx_equal(l1.direction));
    }

    test_section("arbitrary_perpendicular_containing");
    {
        constexpr auto l = l1.arbitrary_perpendicular_containing({ -5.0f, 6.0f, -7.0f });
        ASSERT(l.origin.approx_equal({ -5.0f, 6.0f, -7.0f }));
        ASSERT(l.direction.perpendicular(l1.direction));
    }

    test_section("perpendicular_plane_parallel");
    {
        nnm::PlaneF p { { 1.0f, 1.0f, 1.0f }, nnm::Vector3f(1.0f, -2.0f, 3.0f).normalize() };
        const auto result = l1.perpendicular_plane_parallel(p);
        ASSERT(result.perpendicular(l1) && p.parallel(result));
    }

    test_section("normalize");
    {
        const auto l = nnm::Line3f { { 1.0f, -2.0f, 3.0f }, { 1.0f, -1.0f, 1.0f } }.normalize();
        ASSERT(l.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(l.direction.approx_equal({ 0.5773502692f, -0.5773502692f, 0.5773502692f }));
    }

    test_section("collinear(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        ASSERT(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -5.0f, 6.0f, -7.0f }).collinear(r1));
        constexpr auto result = nnm::Line3f::axis_x().collinear(r1);
        ASSERT_FALSE(result);
    }

    test_section("collinear(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        const auto result = nnm::Line3f::axis_x().collinear(s1);
        ASSERT_FALSE(result);
        ASSERT_FALSE(nnm::Line3f::from_points({ 2.0f, -1.0f, 4.0f }, { -3.0f, 6.0f, -5.0f }).collinear(s1));
        ASSERT(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }).collinear(s1));
        ASSERT(nnm::Line3f::from_points({ -4.0f, 5.0f, -6.0f }, { 1.0f, -2.0f, 3.0f }).collinear(s1));
    }

    test_section("coplanar(const Line3&)");
    {
        constexpr auto result = l1.coplanar(l1);
        ASSERT(result);
        ASSERT_FALSE(l1.coplanar(nnm::Line3f::axis_x()));
        auto l2 = nnm::Line3f::from_points(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        ASSERT(l1.coplanar(l2));
    }

    test_section("coplanar(const Ray3&)");
    {
        constexpr auto result = l1.coplanar(nnm::Ray3f(l1.origin, l1.direction));
        ASSERT(result);
        ASSERT_FALSE(l1.coplanar(nnm::Ray3f(nnm::Vector3f::zero(), nnm::Vector3f::axis_x())));
        auto r1 = nnm::Ray3f::from_point_to_point(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        ASSERT(l1.coplanar(r1));
    }

    test_section("coplanar(const Segment3&)");
    {
        ASSERT(l1.coplanar(nnm::Segment3f(l1.origin, l1.origin + l1.direction)));
        ASSERT_FALSE(l1.coplanar(nnm::Segment3f(nnm::Vector3f::zero(), nnm::Vector3f::axis_x())));
        auto s1 = nnm::Segment3f(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        ASSERT(l1.coplanar(s1));
    }

    test_section("coplanar(const Plane&)");
    {
        constexpr auto result = l1.coplanar(nnm::PlaneF::xy());
        ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        ASSERT(l1.coplanar(plane));
    }

    test_section("coplanar(const Triangle3&)");
    {
        ASSERT_FALSE(l1.coplanar(nnm::Triangle3f({ 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f })));
        ASSERT(l1.coplanar(
            nnm::Triangle3f(
                { -4.7984678398f, -1.8092603063f, 4.2111923428f },
                { -0.003134965f, -3.0097031925f, 4.5129127318f },
                { -4.5435928528f, -3.1536294284f, 5.8279349987f })));
    }

    test_section("contains");
    {
        constexpr auto result = l1.contains({ 0.0f, 0.0f, 0.0f });
        ASSERT_FALSE(result);
        ASSERT(l1.contains({ -2.0f, 1.0f, 0.0f }));
        ASSERT(l1.contains({ -0.8f, -0.2f, 1.2f }));
        ASSERT_FALSE(nnm::Line3f::axis_x_offset(1.0f, -2.0f).contains({ 0.0f, 0.0f, 0.0f }));
    }

    test_section("distance(const Vector3&)");
    {
        const auto d1 = l1.distance({ 0.0f, 0.0f, 0.0f });
        ASSERT(nnm::approx_equal(d1, 1.41421342f));
        const auto d2 = l1.distance({ -2.0f, 1.0f, 0.0f });
        ASSERT(nnm::approx_zero(d2));
    }

    test_section("distance(const Line3&)");
    {
        const auto d1 = l1.distance(nnm::Line3f::axis_z());
        ASSERT(nnm::approx_equal(d1, 0.7071067812f));
        const auto d2 = nnm::Line3f::axis_x().distance(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        ASSERT(nnm::approx_equal(d2, 1.4142135624f));
        const auto d3 = l1.distance(nnm::Line3f::axis_x());
        ASSERT(nnm::approx_equal(d3, 0.7071067812f));
    }

    test_section("distance(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        const auto d1 = nnm::Line3f::axis_x().distance(r1);
        ASSERT(nnm::approx_equal(d1, 0.31234777f));
        const auto d2 = nnm::Line3f::axis_x_offset(-4.0f, 5.0f).distance(r1);
        ASSERT(nnm::approx_equal(d2, 2.82842708f));
        const auto d3 = nnm::Line3f::axis_z_offset(-2.0f, 2.0f).distance(r1);
        ASSERT(nnm::approx_zero(d3));
        const auto d4 = nnm::Line3f::from_ray(r1).distance(r1);
        ASSERT(nnm::approx_zero(d4));
    }

    test_section("parallel(const Line3&)");
    {
        constexpr auto result = l1.parallel(l1);
        ASSERT(result);
        ASSERT_FALSE(l1.parallel(nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })));
        ASSERT(nnm::Line3f::axis_x().parallel(nnm::Line3f::axis_x_offset(2.0f, -3.0f)));
    }

    test_section("parallel(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        constexpr auto result = nnm::Line3f::axis_x().parallel(r1);
        ASSERT_FALSE(result);
        ASSERT(nnm::Line3f::from_points({ 0.0f, 2.0f, -6.0f }, { 3.0f, -2.0f, -1.0f }).parallel(r1));
    }

    test_section("perpendicular(const Line3&)");
    {
        constexpr auto result = l1.perpendicular(l1);
        ASSERT_FALSE(result);
        ASSERT(nnm::Line3f::axis_x().perpendicular(nnm::Line3f::axis_y_offset(2.0f, -3.0f)));
        ASSERT(nnm::Line3f::axis_z_offset(10.0f, -20.0f).perpendicular(nnm::Line3f::axis_y()));
        ASSERT(
            nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                .perpendicular(nnm::Line3f::from_points({ 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f })));
    }

    test_section("perpendicular(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        constexpr auto result = nnm::Line3f::axis_x().perpendicular(r1);
        ASSERT_FALSE(result);
        ASSERT(nnm::Line3f::from_points({ 2.0f, 0.0f, 3.0f }, { -0.2f, -0.4f, 4.0f }).perpendicular(r1));
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto result = l1.intersects(l1);
        ASSERT(result);
        ASSERT(l1.intersects(nnm::Line3f::from_points({ 0.0f, 0.0f, 1.0f }, { -2.0f, 0.0f, 1.0f })));
        ASSERT_FALSE(l1.intersects(nnm::Line3f::axis_z()));
        ASSERT_FALSE(nnm::Line3f::axis_x_offset(1.0f, -2.0f).intersects(nnm::Line3f::axis_x()));
        ASSERT_FALSE(l1.intersects(nnm::Line3f::axis_x_offset(1.0f, -2.0f)));
        ASSERT(nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }).intersects(nnm::Line3f::axis_x()));
    }

    test_section("intersection(const Line3&)");
    {
        constexpr auto i1 = l1.intersection(l1);
        ASSERT_FALSE(i1.has_value());
        const auto i2 = l1.intersection(nnm::Line3f::from_points({ 0.0f, 0.0f, 1.0f }, { -2.0f, 0.0f, 1.0f }));
        ASSERT(i2.has_value() && i2.value().approx_equal({ -1.0f, 0.0f, 1.0f }));
        constexpr auto i3 = l1.intersection(nnm::Line3f::axis_z());
        ASSERT_FALSE(i3.has_value());
        constexpr auto i4 = nnm::Line3f::axis_x_offset(1.0f, -2.0f).intersection(nnm::Line3f::axis_x());
        ASSERT_FALSE(i4.has_value());
        constexpr auto i5 = l1.intersection(nnm::Line3f::axis_x_offset(1.0f, -2.0f));
        ASSERT_FALSE(i5.has_value());
        const auto i6
            = nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }).intersection(nnm::Line3f::axis_x());
        ASSERT(i6.has_value() && i6.value().approx_equal({ 0.0f, 0.0f, 0.0f }));
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        constexpr auto result = nnm::Line3f::axis_x().intersects(r1);
        ASSERT_FALSE(result);
        ASSERT(nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f }).intersects(r1));
        ASSERT(nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f }).intersects(r1));
        ASSERT_FALSE(nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f }).intersects(r1));
    }

    test_section("intersection(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        constexpr auto i1 = nnm::Line3f::axis_x().intersection(r1);
        ASSERT_FALSE(i1.has_value());
        const auto i2 = nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f }).intersection(r1);
        ASSERT(i2.has_value() && i2.value().approx_equal({ -0.2f, -0.4f, 1.0f }));
        const auto i3 = nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f }).intersection(r1);
        ASSERT_FALSE(i3.has_value());
        const auto i4 = nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f }).intersection(r1);
        ASSERT_FALSE(i4.has_value());
    }

    test_section("project_point");
    {
        constexpr auto p1 = l1.project({ 0.0f, 0.0f, 0.0f });
        ASSERT(p1.approx_equal({ -1.0f, 0.0f, 1.0f }));
        constexpr auto p2 = l1.project({ 0.0f, -1.0f, 2.0f });
        ASSERT(p2.approx_equal({ 0.0f, -1.0f, 2.0f }));
    }

    test_section("coincident");
    {
        ASSERT(l1.coincident(l1));
        ASSERT_FALSE(l1.coincident(nnm::Line3f::axis_x()));
        ASSERT_FALSE(nnm::Line3f::axis_y().coincident(nnm::Line3f::axis_y_offset(1.0f, -2.0f)));
        ASSERT(
            nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                .coincident(nnm::Line3f::from_points({ -1.0f, -1.0f, -1.0f }, { 2.0f, 2.0f, 2.0f })));
    }

    test_section("translate");
    {
        constexpr auto t1 = l1.translate({ 5.0f, 6.0f, -7.0f });
        ASSERT(t1.approx_equal({ { 6.0f, 4.0f, -4.0f }, l1.direction }));
    }

    test_section("scale_at");
    {
        const auto s1 = l1.scale_at({ 5.0f, 6.0f, -7.0f }, { 0.5f, -2.0f, 3.0f });
        ASSERT(s1.approx_equal({ { 3.0f, 22.0f, 23.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
    }

    test_section("scale");
    {
        const auto s1 = l1.scale({ 0.5f, -2.0f, 3.0f });
        ASSERT(s1.approx_equal({ { 0.5f, 4.0f, 9.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
    }

    test_section("rotate_axis_angle_at");
    {
        const auto r1 = l1.rotate_axis_angle_at({ 5.0f, 6.0f, -7.0f }, { 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        ASSERT(r1.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("rotate_axis_angle");
    {
        const auto r1 = l1.rotate_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        ASSERT(r1.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("rotate_quaternion_at");
    {
        const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        const auto r1 = l1.rotate_quaternion_at({ 5.0f, 6.0f, -7.0f }, q1);
        ASSERT(r1.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("rotate_quaternion");
    {
        const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        const auto r1 = l1.rotate_quaternion(q1);
        ASSERT(r1.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("shear_x_at");
    {
        const auto s1 = l1.shear_x_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
        ASSERT(s1.approx_equal({ { 1.0f, -4.0f, 5.0f }, { 0.816497f, -0.408248f, 0.408248f } }));
    }

    test_section("shear_x");
    {
        const auto s1 = l1.shear_x(0.5f, -0.5f);
        ASSERT(s1.approx_equal({ { 1.0f, -1.5f, 2.5f }, { 0.816497f, -0.408248f, 0.408248f } }));
    }

    test_section("shear_y_at");
    {
        const auto s1 = l1.shear_y_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
        ASSERT(s1.approx_equal({ { -3.0f, -2.0f, 7.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
    }

    test_section("shear_y");
    {
        const auto s1 = l1.shear_y(0.5f, -0.5f);
        ASSERT(s1.approx_equal({ { 0.0f, -2.0f, 4.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
    }

    test_section("shear_z_at");
    {
        const auto s1 = l1.shear_z_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
        ASSERT(s1.approx_equal({ { 6.0f, -7.0f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
    }

    test_section("shear_z");
    {
        const auto s1 = l1.shear_z(0.5f, -0.5f);
        ASSERT(s1.approx_equal({ { 2.5f, -3.5f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
    }

    test_section("approx_equal");
    {
        ASSERT(l1.approx_equal(l1));
        ASSERT_FALSE(l1.approx_equal(nnm::Line3f::axis_x()));
        ASSERT_FALSE(nnm::Line3f::axis_x_offset(1.0f, -2.0f).approx_equal(nnm::Line3f::axis_x()));
        ASSERT_FALSE(
            nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                .approx_equal(nnm::Line3f::from_points({ -1.0f, -1.0f, -1.0f }, { 2.0f, 2.0f, 2.0f })));
    }

    test_section("operator==");
    {
        ASSERT(l1 == l1);
        ASSERT_FALSE(l1 == nnm::Line3f::axis_x());
    }

    test_section("operator!=");
    {
        ASSERT(l1 != nnm::Line3f::axis_x());
        ASSERT_FALSE(l1 != l1);
    }

    test_section("operator<");
    {
        ASSERT(nnm::Line3f::axis_x() < l1);
        ASSERT_FALSE(l1 < l1);
        ASSERT_FALSE(l1 < nnm::Line3f::axis_x());
    }
}

inline void ray3_tests()
{
    test_case("Ray3");

    test_section("Ray3()");
    {
        constexpr nnm::Ray3f r1 {};
        ASSERT(r1.origin.approx_zero());
        ASSERT(r1.direction.approx_equal({ 1.0f, 0.0f, 0.0f }));
    }

    test_section("Ray3(const Vector3&, const Vector3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        ASSERT(r1.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(r1.direction.approx_equal({ -4.0f, 5.0f, -6.0f }));
    }

    test_section("Ray3(const Ray3<Other>&");
    {
        constexpr nnm::Ray3d r1 { { 1.0, -2.0, 3.0 }, { 4.0, 5.0, -6.0 } };
        constexpr nnm::Ray3f r2 { r1 };
        ASSERT(r2.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(r2.direction.approx_equal({ 4.0f, 5.0f, -6.0f }));
    }

    test_section("from_point_to_point");
    {
        const auto r1 = nnm::Ray3f::from_point_to_point({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f });
        ASSERT(r1.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(r1.direction.approx_equal({ -0.4016096645f, 0.5622535302f, -0.7228973960f }));
    }

    test_section("normalize");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -5.0f, 7.0f, -9.0f } };
        const auto r2 = r1.normalize();
        ASSERT(r2.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(r2.direction.approx_equal({ -0.4016096645f, 0.5622535302f, -0.7228973960f }));
    }

    constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
    constexpr nnm::Ray3f r2 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };

    test_section("collinear(const Vector3&)");
    {
        constexpr auto result = r1.collinear({ -2.0f, 2.0f, -2.0f });
        ASSERT(result);
        ASSERT_FALSE(r1.collinear({ 0.0f, 0.0f, 0.0f }));
        ASSERT(r1.collinear({ 4.0f, -6.0f, 8.0f }));
    }

    test_section("collinear(const Line3&)");
    {
        ASSERT(r1.collinear(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -5.0f, 6.0f, -7.0f })));
        constexpr auto result = r1.collinear(nnm::Line3f::axis_x());
        ASSERT_FALSE(result);
    }

    test_section("collinear(const Ray3&)");
    {
        constexpr auto result = r1.collinear(r1);
        ASSERT(result);
        ASSERT_FALSE(r1.collinear(nnm::Ray3f::from_point_to_point({ 1.0f, 2.0f, 3.0f }, { 10.0f, 20.0f, -0.5f })))
        ASSERT(r1.collinear(nnm::Ray3f::from_point_to_point({ 4.0f, -6.0f, 8.0f }, { 5.8099f, -8.4132f, 11.0165f })));
        ASSERT(r1.collinear(nnm::Ray3f::from_point_to_point({ 5.8099f, -8.4132f, 11.0165f }, { 4.0f, -6.0f, 8.0f })));
    }

    test_section("coplanar(const Line3&)");
    {
        constexpr auto result = r2.coplanar(nnm::Line3f::from_ray(r2));
        ASSERT(result);
        ASSERT_FALSE(r2.coplanar(nnm::Line3f::axis_x()));
        auto l1 = nnm::Line3f::from_points(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        ASSERT(r2.coplanar(l1));
    }

    test_section("coplanar(const Ray3&)");
    {
        constexpr auto result = r2.coplanar(r2);
        ASSERT(result);
        ASSERT_FALSE(r2.coplanar(nnm::Ray3f(nnm::Vector3f::zero(), nnm::Vector3f::axis_x())));
        auto r3 = nnm::Ray3f::from_point_to_point(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        ASSERT(r2.coplanar(r3));
    }

    test_section("coplanar(const Segment3&)");
    {
        ASSERT(r2.coplanar(nnm::Segment3f(r2.origin, r2.origin + r2.direction)));
        ASSERT_FALSE(r2.coplanar(nnm::Segment3f(nnm::Vector3f::zero(), nnm::Vector3f::axis_x())));
        auto s1 = nnm::Segment3f(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        ASSERT(r2.coplanar(s1));
    }

    test_section("coplanar(const Plane&)");
    {
        constexpr auto result = r2.coplanar(nnm::PlaneF::xy());
        ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        ASSERT(r2.coplanar(plane));
    }

    test_section("coplanar(const Triangle3&)");
    {
        ASSERT_FALSE(r2.coplanar(nnm::Triangle3f({ 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f })));
        ASSERT(r2.coplanar(
            nnm::Triangle3f(
                { -4.7984678398f, -1.8092603063f, 4.2111923428f },
                { -0.003134965f, -3.0097031925f, 4.5129127318f },
                { -4.5435928528f, -3.1536294284f, 5.8279349987f })));
    }

    test_section("contains");
    {
        constexpr auto result = r1.contains({ -0.2f, -0.4f, 1.0f });
        ASSERT(result);
        ASSERT(r1.contains({ -2.0f, 2.0f, -2.0f }));
        ASSERT_FALSE(r1.contains({ 0.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(r1.contains({ 1.54f, -2.72f, 3.9f }));
    }

    test_section("distance(const Vector3&)");
    {
        const auto d1 = r1.distance({ 0.0f, 0.0f, 0.0f });
        ASSERT(nnm::approx_equal(d1, 0.692820311f));
        const auto d2 = r1.distance({ -2.0f, 2.0f, -2.0f });
        ASSERT(nnm::approx_zero(d2));
        const auto d3 = r1.distance({ 4.0f, -6.0f, 8.0f });
        ASSERT(nnm::approx_equal(d3, 7.0711f));
        const auto d4 = r1.distance({ 4.0f, -5.0f, 9.0f });
        ASSERT(nnm::approx_equal(d4, 7.3485f));
    }

    test_section("distance(const Line3&)");
    {
        const auto d1 = r1.distance(nnm::Line3f::axis_x());
        ASSERT(nnm::approx_equal(d1, 0.31234777f));
        const auto d2 = r1.distance(nnm::Line3f::axis_x_offset(-4.0f, 5.0f));
        ASSERT(nnm::approx_equal(d2, 2.82842708f));
        const auto d3 = r1.distance(nnm::Line3f::axis_z_offset(-2.0f, 2.0f));
        ASSERT(nnm::approx_zero(d3));
        const auto d4 = r1.distance(nnm::Line3f::from_ray(r1));
        ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance(const Ray3&)");
    {
        const auto d1 = r1.distance(r1);
        ASSERT(nnm::approx_zero(d1));
        const auto d2 = r1.distance(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d2, 0.692820311f));
        const auto d3 = nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }).distance(r1);
        ASSERT(nnm::approx_equal(d3, 0.692820311f));
        const auto d4 = r1.distance(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d4, 0.31234777f));
        const auto d5 = nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }).distance(r1);
        ASSERT(nnm::approx_equal(d5, 0.31234777f));
        const auto d6 = r1.distance(nnm::Ray3f::from_point_to_point({ 3.0f, -4.0f, 5.0f }, { 4.0f, -4.0f, 5.0f }));
        ASSERT(nnm::approx_equal(d6, 3.4641f));
        const auto d7 = nnm::Ray3f::from_point_to_point({ 3.0f, -4.0f, 5.0f }, { 4.0f, -4.0f, 5.0f }).distance(r1);
        ASSERT(nnm::approx_equal(d7, 3.4641f));
        const auto d8 = r1.distance(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { 8.0f, -8.0f, 10.0f }));
        ASSERT(nnm::approx_equal(d8, 2.4495f));
        const auto d9 = nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { 8.0f, -8.0f, 10.0f }).distance(r1);
        ASSERT(nnm::approx_equal(d9, 2.4495f));
    }

    test_section("project");
    {
        constexpr auto p1 = r1.project({ 2.0f, 0.0f, 0.0f });
        ASSERT(p1.approx_equal({ -0.2f, -0.4f, 1.0f }));
        constexpr auto p2 = r1.project({ 6.0f, -4.0f, 6.0f });
        ASSERT(p2.approx_equal({ 1.0f, -2.0f, 3.0f }));
        constexpr auto p3 = r1.project({ -2.0f, 2.0f, -2.0f });
        ASSERT(p3.approx_equal({ -2.0f, 2.0f, -2.0f }));
    }

    test_section("parallel(const Line3&)");
    {
        constexpr auto result = r1.parallel(nnm::Line3f::axis_x());
        ASSERT_FALSE(result);
        ASSERT(r1.parallel(nnm::Line3f::from_points({ 0.0f, 2.0f, -6.0f }, { 3.0f, -2.0f, -1.0f })));
    }

    test_section("parallel(const Ray3&)");
    {
        constexpr auto result = r1.parallel(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 0.57735f, 0.57735f, 0.57735f }));
        ASSERT_FALSE(result);
        ASSERT(r1.parallel(nnm::Ray3f::from_point_to_point({ 0.0f, 2.0f, -6.0f }, { 3.0f, -2.0f, -1.0f })));
    }

    test_section("perpendicular(const Line3&)");
    {
        constexpr auto result = r1.perpendicular(nnm::Line3f::axis_x());
        ASSERT_FALSE(result);
        ASSERT(r1.perpendicular(nnm::Line3f::from_points({ 2.0f, 0.0f, 3.0f }, { -0.2f, -0.4f, 4.0f })));
    }

    test_section("perpendicular(const Ray3&)");
    {
        constexpr auto result = r1.perpendicular(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 0.57735f, 0.57735f, 0.57735f }));
        ASSERT_FALSE(result);
        ASSERT(r1.perpendicular(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 3.0f }, { -0.2f, -0.4f, 4.0f })));
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto result = r1.intersects(nnm::Line3f::axis_x());
        ASSERT_FALSE(result);
        ASSERT(r1.intersects(nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f })));
        ASSERT(r1.intersects(nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f })));
        ASSERT_FALSE(r1.intersects(nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f })));
    }

    test_section("intersection(const Line3&)");
    {
        constexpr auto i1 = r1.intersection(nnm::Line3f::axis_x());
        ASSERT_FALSE(i1.has_value());
        const auto i2 = r1.intersection(nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f }));
        ASSERT(i2.has_value() && i2.value().approx_equal({ -0.2f, -0.4f, 1.0f }));
        const auto i3 = r1.intersection(nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f }));
        ASSERT_FALSE(i3.has_value());
        const auto i4 = r1.intersection(nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f }));
        ASSERT_FALSE(i4.has_value());
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr auto result = r1.intersects(r1);
        ASSERT(result);
        ASSERT_FALSE(r1.intersects(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f })));
        ASSERT(r1.intersects(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { -0.2f, -0.4f, 1.0f })));
        ASSERT_FALSE(r1.intersects(nnm::Ray3f::from_point_to_point({ -2.0f, -4.0f, 5.0f }, { 1.54f, -2.72f, 3.9f })));
    }

    test_section("intersection(const Ray3&)");
    {
        constexpr auto i1 = r1.intersection(r1);
        ASSERT_FALSE(i1.has_value());
        const auto i2 = r1.intersection(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(i2.has_value());
        const auto i3 = r1.intersection(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { -0.2f, -0.4f, 1.0f }));
        ASSERT(i3.has_value() && i3.value().approx_equal({ -0.2f, -0.4f, 1.0f }));
        const auto i4
            = r1.intersection(nnm::Ray3f::from_point_to_point({ -2.0f, -4.0f, 5.0f }, { 1.54f, -2.72f, 3.9f }));
        ASSERT_FALSE(i4.has_value());
    }

    test_section("translate");
    {
        constexpr auto t1 = r2.translate({ 5.0f, 6.0f, -7.0f });
        ASSERT(t1.approx_equal({ { 6.0f, 4.0f, -4.0f }, r2.direction }));
    }

    test_section("scale_at");
    {
        const auto s1 = r2.scale_at({ 5.0f, 6.0f, -7.0f }, { 0.5f, -2.0f, 3.0f });
        ASSERT(s1.approx_equal({ { 3.0f, 22.0f, 23.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
    }

    test_section("scale");
    {
        const auto s1 = r2.scale({ 0.5f, -2.0f, 3.0f });
        ASSERT(s1.approx_equal({ { 0.5f, 4.0f, 9.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
    }

    test_section("rotate_axis_angle_at");
    {
        const auto r1r = r2.rotate_axis_angle_at({ 5.0f, 6.0f, -7.0f }, { 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        ASSERT(r1r.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("rotate_axis_angle");
    {
        const auto r1r = r2.rotate_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        ASSERT(r1r.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("rotate_quaternion_at");
    {
        const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        const auto r = r2.rotate_quaternion_at({ 5.0f, 6.0f, -7.0f }, q1);
        ASSERT(r.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("rotate_quaternion");
    {
        const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        const auto r = r2.rotate_quaternion(q1);
        ASSERT(r.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("shear_x_at");
    {
        const auto s1 = r2.shear_x_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
        ASSERT(s1.approx_equal({ { 1.0f, -4.0f, 5.0f }, { 0.816497f, -0.408248f, 0.408248f } }));
    }

    test_section("shear_x");
    {
        const auto s1 = r2.shear_x(0.5f, -0.5f);
        ASSERT(s1.approx_equal({ { 1.0f, -1.5f, 2.5f }, { 0.816497f, -0.408248f, 0.408248f } }));
    }

    test_section("shear_y_at");
    {
        const auto s1 = r2.shear_y_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
        ASSERT(s1.approx_equal({ { -3.0f, -2.0f, 7.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
    }

    test_section("shear_y");
    {
        const auto s1 = r2.shear_y(0.5, -0.5f);
        ASSERT(s1.approx_equal({ { 0.0f, -2.0f, 4.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
    }

    test_section("shear_z_at");
    {
        const auto s1 = r2.shear_z_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
        ASSERT(s1.approx_equal({ { 6.0f, -7.0f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
    }

    test_section("shear_z");
    {
        const auto s1 = r2.shear_z(0.5f, -0.5f);
        ASSERT(s1.approx_equal({ { 2.5f, -3.5f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
    }

    test_section("approx_equal");
    {
        constexpr auto result = r1.approx_equal(r1);
        ASSERT(result);
        ASSERT(r2.approx_equal(r2));
        ASSERT_FALSE(r1.approx_equal(r2));
        ASSERT_FALSE(r2.approx_equal(r1));
    }

    test_section("operator=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = r1 == r1;
        ASSERT(result);
        ASSERT(r2 == r2);
        ASSERT_FALSE(r1 == r2);
        ASSERT_FALSE(r2 == r1);
    }

    test_section("operator!=");
    {
        constexpr auto result = r1 != r2;
        ASSERT(result);
        ASSERT(r2 != r1);
        ASSERT_FALSE(r1 != r1);
        ASSERT_FALSE(r2 != r2);
    }

    test_section("operator<");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = r1 < r1;
        ASSERT_FALSE(result);
        ASSERT(r1 < r2);
        ASSERT_FALSE(r2 < r1);
    }
}

inline void segment3_tests()
{
    test_case("Segment3");

    test_section("Segment3()");
    {
        constexpr nnm::Segment3f s {};
        ASSERT(s.start == nnm::Vector3f::zero());
        ASSERT(s.end == nnm::Vector3f::axis_x());
    }

    test_section("Segment3(const Vector3&, const Vector3&)");
    {
        constexpr nnm::Segment3f s { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        ASSERT(s.start == nnm::Vector3f(1.0f, -2.0f, 3.0f));
        ASSERT(s.end == nnm::Vector3f(-4.0f, 5.0f, -6.0f));
    }

    test_section("Segment3(const Segment3<Other>&)");
    {
        constexpr nnm::Segment3d s1 { { 1.0, -2.0, 3.0 }, { -4.0, 5.0, -6.0 } };
        constexpr nnm::Segment3f s2 { s1 };
        ASSERT(s2.start.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(s2.end.approx_equal({ -4.0f, 5.0f, -6.0f }));
    }

    constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };

    test_section("collinear(const Vector3&)");
    {
        const auto result = s1.collinear({ 2.9833236933f, -4.7766531707f, 6.569982648f });
        ASSERT(result);
        ASSERT_FALSE(s1.collinear({ 0.0f, 0.0f, 0.0f }));
        ASSERT(s1.collinear({ -1.4205585602f, 1.3887819843f, -1.3570054084f }));
        ASSERT(s1.collinear({ -6.1127619882f, 7.9578667834f, -9.8029715787f }));
    }

    test_section("collinear(const Line3&)");
    {
        const auto result = s1.collinear(nnm::Line3f::axis_x());
        ASSERT_FALSE(result);
        ASSERT_FALSE(s1.collinear(nnm::Line3f::from_points({ 2.0f, -1.0f, 4.0f }, { -3.0f, 6.0f, -5.0f })));
        ASSERT(s1.collinear(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f })));
        ASSERT(s1.collinear(nnm::Line3f::from_points({ -4.0f, 5.0f, -6.0f }, { 1.0f, -2.0f, 3.0f })));
    }

    test_section("collinear(const Ray3&)");
    {
        ASSERT_FALSE(s1.collinear(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f })));
        const auto result = s1.collinear(
            nnm::Ray3f({ 2.9833236933f, -4.7766531707f, 6.569982648f }, { -0.40161f, 0.562254f, -0.722897f }));
        ASSERT(result);
        ASSERT(s1.collinear(nnm::Ray3f({ 2.9833236933f, -4.7766531707f, 6.569982648f }, s1.start.direction(s1.end))));
        ASSERT(s1.collinear(nnm::Ray3f({ -1.4205585602f, 1.3887819843f, -1.3570054084f }, s1.end.direction(s1.start))));
        ASSERT(s1.collinear(nnm::Ray3f({ -1.4205585602f, 1.3887819843f, -1.3570054084f }, s1.start.direction(s1.end))));
        ASSERT(s1.collinear(nnm::Ray3f({ -6.1127619882f, 7.9578667834f, -9.8029715787f }, s1.end.direction(s1.start))));
        ASSERT(s1.collinear(nnm::Ray3f({ -6.1127619882f, 7.9578667834f, -9.8029715787f }, s1.start.direction(s1.end))));
    }

    test_section("collinear(const Segment3&)");
    {
        const auto result = s1.collinear(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(result);
        ASSERT(s1.collinear(s1));
        ASSERT(s1.collinear(
            nnm::Segment3f(
                { 2.9833236933f, -4.7766531707f, 6.569982648f }, { 4.5074673515f, -6.9104542922f, 9.3134412328f })));
        ASSERT(s1.collinear(
            nnm::Segment3f(
                { -6.1127619882f, 7.9578667834f, -9.8029715787f },
                { -9.0362240787f, 12.0507137102f, -15.0652033417f })));
        ASSERT_FALSE(s1.collinear(nnm::Segment3f({ 0.0f, -3.0f, 2.0f }, { -5.0f, 4.0f, -7.0f })))
    }

    constexpr nnm::Segment3f s4 { { 1.0f, -2.0f, 3.0f }, { 2.0f, -3.0f, 4.0f } };

    test_section("coplanar(const Line3&)");
    {
        constexpr nnm::Line3f l1 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };
        const auto result = s4.coplanar(l1);
        ASSERT(result);
        ASSERT_FALSE(s4.coplanar(nnm::Line3f::axis_x()));
        auto l2 = nnm::Line3f::from_points(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        ASSERT(s4.coplanar(l2));
    }

    test_section("coplanar(const Ray3&)");
    {
        const auto result
            = s4.coplanar(nnm::Ray3f({ 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f }));
        ASSERT(result);
        ASSERT_FALSE(s4.coplanar(nnm::Ray3f(nnm::Vector3f::zero(), nnm::Vector3f::axis_x())));
        auto r1 = nnm::Ray3f::from_point_to_point(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        ASSERT(s4.coplanar(r1));
    }

    test_section("coplanar(const Segment3&)");
    {
        const auto result = s4.coplanar(s4);
        ASSERT(result);
        ASSERT_FALSE(s4.coplanar(nnm::Segment3f(nnm::Vector3f::zero(), nnm::Vector3f::axis_x())));
        auto s5 = nnm::Segment3f(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        ASSERT(s4.coplanar(s5));
    }

    test_section("coplanar(const Plane&)");
    {
        constexpr auto result = s4.coplanar(nnm::PlaneF::xy());
        ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        ASSERT(s4.coplanar(plane));
    }

    test_section("coplanar(const Triangle3&)");
    {
        ASSERT_FALSE(s4.coplanar(nnm::Triangle3f({ 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f })));
        ASSERT(s4.coplanar(
            nnm::Triangle3f(
                { -4.7984678398f, -1.8092603063f, 4.2111923428f },
                { -0.003134965f, -3.0097031925f, 4.5129127318f },
                { -4.5435928528f, -3.1536294284f, 5.8279349987f })));
    }

    test_section("contains");
    {
        constexpr auto result = s1.contains({ 0.0f, 0.0f, 0.0f });
        ASSERT_FALSE(result);
        ASSERT_FALSE(s1.contains({ 2.9833236933f, -4.7766531707f, 6.569982648f }));
        ASSERT(s1.contains({ -1.4205585602f, 1.3887819843f, -1.3570054084f }));
        ASSERT_FALSE(s1.contains({ -6.1127619882f, 7.9578667834f, -9.8029715787f }));
    }

    test_section("distance(const Vector3&)");
    {
        const auto d1 = s1.distance({ 0.0f, 0.0f, 0.0f });
        ASSERT(nnm::approx_equal(d1, 0.5902432522f));
        const auto d2 = s1.distance({ -5.0f, 7.0f, -7.0f });
        ASSERT(nnm::approx_equal(d2, 2.4494897428f));
        const auto d3 = s1.distance({ 0.0f, -5.0f, 3.0f });
        ASSERT(nnm::approx_equal(d3, 3.1622776602f));
        const auto d4 = s1.distance({ -1.4205585602f, 1.3887819843f, -1.3570054084f });
        ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance(const Line3&)");
    {
        const auto d1 = s1.distance(nnm::Line3f::axis_x());
        ASSERT(nnm::approx_equal(d1, 0.263117403f));
        const auto d2 = s1.distance(nnm::Line3f({ -6.0f, -4.0f, 7.0f }, { 1.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d2, 4.472135955f));
        const auto d3 = s1.distance(nnm::Line3f({ -6.0f, 7.0f, -7.0f }, { 0.0f, 0.0f, -1.0f }));
        ASSERT(nnm::approx_equal(d3, 2.8284271247f));
    }

    test_section("distance(const Ray3&)");
    {
        const auto d1 = s1.distance(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d1, 0.5902432522f));
        const auto d2 = s1.distance(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d2, 0.263117403f));
        const auto d3 = s1.distance(nnm::Ray3f::from_point_to_point({ 2.0f, -4.0f, 3.0f }, { 3.0f, -5.0f, 4.0f }));
        ASSERT(nnm::approx_equal(d3, 2.2360679775f));
        const auto d4 = s1.distance(nnm::Ray3f::from_point_to_point({ 2.0f, -4.0f, 3.0f }, { 1.0f, -3.0f, 2.0f }));
        ASSERT(nnm::approx_equal(d4, 1.2247448f));
        const auto d5 = s1.distance(nnm::Ray3f::from_point_to_point({ -5.0f, 7.0f, -7.0f }, { -6.0f, 9.0f, -7.0f }));
        ASSERT(nnm::approx_equal(d5, 2.4494897428f));
        const auto d6 = s1.distance(nnm::Ray3f::from_point_to_point({ -5.0f, 7.0f, -7.0f }, { -1.0f, 2.0f, -2.0f }));
        ASSERT(nnm::approx_equal(d6, 0.593442202f));
        const auto d7 = s1.distance(
            nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.3814812713f, 1.3340737798f, -1.2866662883f }));
        ASSERT(nnm::approx_zero(d7));
    }

    test_section("distance(const Segment3&)");
    {
        const auto d1 = s1.distance(s1);
        ASSERT(nnm::approx_zero(d1));
        const auto d2 = s1.distance(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d2, 0.5902432522f));
        const auto d3 = s1.distance(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d3, 0.263117403f));
        const auto d4 = s1.distance(nnm::Segment3f({ -2.0f, 0.0f, 0.0f }, { -8.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d4, 1.3295645661f));
        const auto d5 = s1.distance(nnm::Segment3f({ 4.0f, -4.0f, 6.0f }, { 5.0f, -4.0f, 6.0f }));
        ASSERT(nnm::approx_equal(d5, 4.6904157598f));
        const auto d6 = s1.distance(nnm::Segment3f({ -5.0f, -4.0f, 6.0f }, { 5.0f, -4.0f, 6.0f }));
        ASSERT(nnm::approx_equal(d6, 3.6055512755f));
        const auto d7 = s1.distance(nnm::Segment3f({ -3.0f, -4.0f, 6.0f }, { -5.0f, -4.0f, 6.0f }));
        ASSERT(nnm::approx_equal(d7, 5.3851648071f));
        const auto d8 = s1.distance(nnm::Segment3f({ -5.0f, 7.0f, -2.0f }, { -5.0f, 7.0f, -1.0f }));
        ASSERT(nnm::approx_equal(d8, 4.582575695f));
        const auto d9 = s1.distance(nnm::Segment3f({ -5.0f, 7.0f, -10.0f }, { -5.0f, 7.0f, -1.0f }));
        ASSERT(nnm::approx_equal(d9, 2.2360679775f));
        const auto d10 = s1.distance(nnm::Segment3f({ -5.0f, 7.0f, -8.0f }, { -5.0f, 7.0f, -9.0f }));
        ASSERT(nnm::approx_equal(d10, 3.0f));
        const auto d11
            = s1.distance(nnm::Segment3f({ 1.3429285263f, 1.4817304819f, -0.7047254731f }, { -2.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_zero(d11));
    }

    test_section("direction_unnormalized");
    {
        constexpr auto result = s1.direction_unnormalized();
        ASSERT(result.approx_equal({ -5.0f, 7.0f, -9.0f }));
    }

    test_section("direction");
    {
        ASSERT(s1.direction().approx_equal({ -0.4016096645f, 0.5622535302f, -0.7228973960f }));
    }

    test_section("parallel(const Line3&)");
    {
        constexpr auto result = s1.parallel(nnm::Line3f::axis_x());
        ASSERT_FALSE(result);
        ASSERT(s1.parallel(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f })))
        ASSERT(s1.parallel(nnm::Line3f::from_points({ 3.0f, 0.0f, 5.0f }, { -2.0f, 7.0f, -4.0f })))
    }

    test_section("parallel(const Ray3&)");
    {
        constexpr auto result = s1.parallel(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        ASSERT_FALSE(result);
        ASSERT(s1.parallel(nnm::Ray3f::from_point_to_point(s1.start, s1.end)));
        ASSERT(s1.parallel(nnm::Ray3f(s1.start + nnm::Vector3f(2.0f, -3.0f, 10.0f), -s1.direction())));
    }

    test_section("parallel(const Segment3&)");
    {
        constexpr auto result = s1.parallel(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, -2.0f }));
        ASSERT_FALSE(result);
        ASSERT(s1.parallel(s1));
        ASSERT(s1.parallel(
            nnm::Segment3f(s1.start + nnm::Vector3f(2.0f, -2.0f, 5.0f), s1.end + nnm::Vector3f(2.0f, -2.0f, 5.0f))));
    }

    test_section("perpendicular(const Line3&)");
    {
        constexpr auto result = s1.perpendicular(nnm::Line3f::axis_x());
        ASSERT_FALSE(result);
        ASSERT(s1.perpendicular(
            nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { -1.1918502675f, 0.1906960428f, 0.8104581819f })));
    }

    test_section("perpendicular(const Ray3&)");
    {
        ASSERT_FALSE(s1.perpendicular(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, -1.0f, -1.0f })));
        constexpr auto r1 = nnm::Ray3f { { 0.0f, 0.0f, 0.0f }, { -0.819782316f, 0.131165162f, 0.557451963f } };
        ASSERT(s1.perpendicular(r1));
        constexpr auto result = s1.perpendicular(nnm::Ray3f(r1.origin, -r1.direction));
        ASSERT(result);
    }

    test_section("perpendicular(const Segment3&)");
    {
        constexpr auto result = s1.perpendicular(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }));
        ASSERT_FALSE(result);
        ASSERT(
            s1.perpendicular(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.1918502675f, 0.1906960428f, 0.8104581819f })));
        ASSERT(
            s1.perpendicular(nnm::Segment3f({ -1.1918502675f, 0.1906960428f, 0.8104581819f }, { 0.0f, 0.0f, 0.0f })));
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto result = s1.intersects(nnm::Line3f::axis_x());
        ASSERT_FALSE(result);
        ASSERT(s1.intersects(nnm::Line3f::from_points({ 1, 2, 3 }, { -0.666667f, -3.0476f, 0.0f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Line3f::from_points({ -6.3161401722f, -5.0466531233f, 6.9171254442f }, { 5.0f, -2.0f, 3.0f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Line3f::from_points({ 6.340530911f, 6.2880512604f, -11.4095884147f }, { -7.0f, 5.0f, -5.0f })));
        ASSERT(s1.intersects(nnm::Line3f(s1.start, s1.direction())));
    }

    test_section("intersection(const Line3&)");
    {
        constexpr auto i1 = s1.intersection(nnm::Line3f::axis_x());
        ASSERT_FALSE(i1.has_value());
        const auto i2 = s1.intersection(nnm::Line3f::from_points({ 1, 2, 3 }, { -0.666667f, -3.0476f, 0.0f }));
        ASSERT(i2.has_value() && i2.value().approx_equal({ 0.0967741935f, -0.735483871f, 1.3741935484f }));
        const auto i3 = s1.intersection(
            nnm::Line3f::from_points({ -6.3161401722f, -5.0466531233f, 6.9171254442f }, { 5.0f, -2.0f, 3.0f }));
        ASSERT_FALSE(i3.has_value());
        const auto i4 = s1.intersection(
            nnm::Line3f::from_points({ 6.340530911f, 6.2880512604f, -11.4095884147f }, { -7.0f, 5.0f, -5.0f }));
        ASSERT_FALSE(i4.has_value());
        const auto i5 = s1.intersection(nnm::Line3f(s1.start, s1.direction()));
        ASSERT_FALSE(i5.has_value());
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr auto r1 = nnm::Ray3f { { 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        constexpr auto result = s1.intersects(r1);
        ASSERT_FALSE(result);
        ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point({ 1.0f, 2.0f, 3.0f }, { 2.0323377426f, 5.126508592f, 4.8582079368f })));
        ASSERT(s1.intersects(
            nnm::Ray3f::from_point_to_point({ 2.0323377426f, 5.126508592f, 4.8582079368f }, { 1.0f, 2.0f, 3.0f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point({ 5.0f, -2.0f, 3.0f }, { 8.4624090164f, -1.0678129571f, 1.801473802f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point({ 8.4624090164f, -1.0678129571f, 1.801473802f }, { 5.0f, -2.0f, 3.0f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point(
                { -7.0f, 5.0f, -5.0f }, { -10.7888017215f, 4.6341846614f, -3.1796331959f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point(
                { -10.7888017215f, 4.6341846614f, -3.1796331959f }, { -7.0f, 5.0f, -5.0f })));
        ASSERT(s1.intersects(
            nnm::Ray3f::from_point_to_point(
                { 3.1803758203f, -5.0525261484f, 6.9246764765f }, { 2.2353232409f, -3.7294525373f, 5.2235818337f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Ray3f::from_point_to_point(
                { 2.2353232409f, -3.7294525373f, 5.2235818337f }, { 3.1803758203f, -5.0525261484f, 6.9246764765f })));
    }

    test_section("intersection(const Ray3&)");
    {

        constexpr auto i1 = s1.intersection(nnm::Ray3f { { 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } });
        ASSERT_FALSE(i1.has_value());
        const auto i2 = s1.intersection(
            nnm::Ray3f::from_point_to_point({ 1.0f, 2.0f, 3.0f }, { 2.0323377426f, 5.126508592f, 4.8582079368f }));
        ASSERT_FALSE(i2.has_value());
        const auto i3 = s1.intersection(
            nnm::Ray3f::from_point_to_point({ 2.0323377426f, 5.126508592f, 4.8582079368f }, { 1.0f, 2.0f, 3.0f }));
        ASSERT(i3.has_value() && i3.value().approx_equal({ 0.0967741935f, -0.735483871f, 1.3741935484f }));
        const auto i4 = s1.intersection(
            nnm::Ray3f::from_point_to_point({ 5.0f, -2.0f, 3.0f }, { 8.4624090164f, -1.0678129571f, 1.801473802f }));
        ASSERT_FALSE(i4.has_value());
        const auto i5 = s1.intersection(
            nnm::Ray3f::from_point_to_point({ 8.4624090164f, -1.0678129571f, 1.801473802f }, { 5.0f, -2.0f, 3.0f }));
        ASSERT_FALSE(i5.has_value());
        const auto i6 = s1.intersection(
            nnm::Ray3f::from_point_to_point(
                { -7.0f, 5.0f, -5.0f }, { -10.7888017215f, 4.6341846614f, -3.1796331959f }));
        ASSERT_FALSE(i6.has_value());
        const auto i7 = s1.intersection(
            nnm::Ray3f::from_point_to_point(
                { -10.7888017215f, 4.6341846614f, -3.1796331959f }, { -7.0f, 5.0f, -5.0f }));
        ASSERT_FALSE(i7.has_value());
        const auto i8 = s1.intersection(
            nnm::Ray3f::from_point_to_point(
                { 3.1803758203f, -5.0525261484f, 6.9246764765f }, { 2.2353232409f, -3.7294525373f, 5.2235818337f }));
        ASSERT_FALSE(i8.has_value());
        const auto i9 = s1.intersection(
            nnm::Ray3f::from_point_to_point(
                { 2.2353232409f, -3.7294525373f, 5.2235818337f }, { 3.1803758203f, -5.0525261484f, 6.9246764765f }));
        ASSERT_FALSE(i9.has_value());
    }

    test_section("intersects(const Segment3&)");
    {
        constexpr auto result = s1.intersects(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -4.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(result);
        ASSERT(s1.intersects(s1));
        ASSERT_FALSE(s1.intersects(
            nnm::Segment3f(s1.start + nnm::Vector3f(1.0f, 1.0f, 1.0f), s1.end + nnm::Vector3f(1.0f, 1.0f, 1.0f))));
        ASSERT(s1.intersects(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.3947151596f, 0.2231544255f, 0.9484063085f })));
        ASSERT_FALSE(
            s1.intersects(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.8903860212f, -0.1424617634f, -0.6054624944f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Segment3f(
                { -1.3947151596f, 0.2231544255f, 0.9484063085f }, { -2.477689579f, 0.3964303326f, 1.6848289137f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Segment3f(
                { 2.9228521743f, -3.1715789131f, 4.9407197828f }, { 4.4763315545f, -2.5022944544f, 4.8928270762f })));
        ASSERT_FALSE(
            s1.intersects(nnm::Segment3f({ 2.9228521743f, -3.1715789131f, 4.9407197828f }, { 1.0f, -4.0f, 5.0f })));
        ASSERT_FALSE(
            s1.intersects(nnm::Segment3f({ 1.0f, -4.0f, 5.0f }, { -0.2324762036f, -4.5309868797f, 5.0379963983f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Segment3f(
                { -4.3190323788f, 3.7446637121f, -8.843567106f }, { -4.5930027693f, 5.0543673254f, -8.1018537201f })));
        ASSERT_FALSE(
            s1.intersects(nnm::Segment3f({ -4.5930027693f, 5.0543673254f, -8.1018537201f }, { -5.0f, 7.0f, -7.0f })));
        ASSERT_FALSE(
            s1.intersects(nnm::Segment3f({ -5.0f, 7.0f, -7.0f }, { -5.5960814905f, 9.8495418077f, -5.3862430547f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Segment3f({ -1.3071995174f, 3.5612991571f, 3.8583174565f }, { -2.0f, 3.0f, -0.6802903382f })));
        ASSERT_FALSE(s1.intersects(
            nnm::Segment3f(
                { -2.8239641345f, 2.3324335277f, -6.0781648164f },
                { -3.5475337817f, 1.7462055396f, -10.8183445985f })));
    }

    test_section("intersection(const Segment3&");
    {
        constexpr auto i1 = s1.intersection(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -4.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = s1.intersection(s1);
        ASSERT_FALSE(i2.has_value());
        constexpr auto i3 = s1.intersection(
            nnm::Segment3f(s1.start + nnm::Vector3f(1.0f, 1.0f, 1.0f), s1.end + nnm::Vector3f(1.0f, 1.0f, 1.0f)));
        ASSERT_FALSE(i3.has_value());
        constexpr auto i4
            = s1.intersection(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.3947151596f, 0.2231544255f, 0.9484063085f }));
        ASSERT(i4.has_value() && i4.value().approx_equal({ -0.4838709677f, 0.0774193548f, 0.3290322581f }));
        constexpr auto i5
            = s1.intersection(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.8903860212f, -0.1424617634f, -0.6054624944f }));
        ASSERT_FALSE(i5.has_value());
        constexpr auto i6 = s1.intersection(
            nnm::Segment3f(
                { -1.3947151596f, 0.2231544255f, 0.9484063085f }, { -2.477689579f, 0.3964303326f, 1.6848289137f }));
        ASSERT_FALSE(i6.has_value());
        constexpr auto i7 = s1.intersection(
            nnm::Segment3f(
                { 2.9228521743f, -3.1715789131f, 4.9407197828f }, { 4.4763315545f, -2.5022944544f, 4.8928270762f }));
        ASSERT_FALSE(i7.has_value());
        constexpr auto i8
            = s1.intersection(nnm::Segment3f({ 2.9228521743f, -3.1715789131f, 4.9407197828f }, { 1.0f, -4.0f, 5.0f }));
        ASSERT_FALSE(i8.has_value());
        constexpr auto i9
            = s1.intersection(nnm::Segment3f({ 1.0f, -4.0f, 5.0f }, { -0.2324762036f, -4.5309868797f, 5.0379963983f }));
        ASSERT_FALSE(i9.has_value());
        constexpr auto i10 = s1.intersection(
            nnm::Segment3f(
                { -4.3190323788f, 3.7446637121f, -8.843567106f }, { -4.5930027693f, 5.0543673254f, -8.1018537201f }));
        ASSERT_FALSE(i10.has_value());
        constexpr auto i11 = s1.intersection(
            nnm::Segment3f({ -4.5930027693f, 5.0543673254f, -8.1018537201f }, { -5.0f, 7.0f, -7.0f }));
        ASSERT_FALSE(i11.has_value());
        constexpr auto i12 = s1.intersection(
            nnm::Segment3f({ -5.0f, 7.0f, -7.0f }, { -5.5960814905f, 9.8495418077f, -5.3862430547f }));
        ASSERT_FALSE(i12.has_value());
        constexpr auto i13 = s1.intersection(
            nnm::Segment3f({ -1.3071995174f, 3.5612991571f, 3.8583174565f }, { -2.0f, 3.0f, -0.6802903382f }));
        ASSERT_FALSE(i13.has_value());
        constexpr auto i14 = s1.intersection(
            nnm::Segment3f(
                { -2.8239641345f, 2.3324335277f, -6.0781648164f }, { -3.5475337817f, 1.7462055396f, -10.8183445985f }));
        ASSERT_FALSE(i14.has_value());
    }

    test_section("project");
    {
        constexpr auto p1 = s1.project({ 0.0f, 0.0f, 0.0f });
        ASSERT(p1.approx_equal({ -0.4838709677f, 0.0774193548f, 0.3290322581f }))
        constexpr auto p2 = s1.project({ 2.0f, -3.0f, 4.0f });
        ASSERT(p2.approx_equal(s1.start));
        constexpr auto p3 = s1.project({ -5.0f, 7.0f, -7.0f });
        ASSERT(p3.approx_equal(s1.end));
    }

    test_section("length_sqrd");
    {
        constexpr auto l = s1.length_sqrd();
        ASSERT(nnm::approx_equal(l, 155.0f));
    }

    test_section("length");
    {
        ASSERT(nnm::approx_equal(s1.length(), 12.449899598f));
    }

    test_section("midpoint");
    {
        constexpr auto result = s1.midpoint();
        ASSERT(result.approx_equal({ -1.5f, 1.5f, -1.5f }));
    }

    test_section("translate");
    {
        constexpr nnm::Vector3f offset { 10.0f, -2.0f, 0.5f };
        constexpr auto s1t = s1.translate(offset);
        ASSERT(s1t.start.approx_equal(s1.start.translate(offset)) && s1t.end.approx_equal(s1.end.translate(offset)));
    }

    test_section("scale_at");
    {
        constexpr nnm::Vector3f origin { -5.0f, 0.2f, 3.0f };
        constexpr nnm::Vector3f factor { 10.0f, -2.0f, 0.5f };
        constexpr auto s1s = s1.scale_at(origin, factor);
        ASSERT(
            s1s.start.approx_equal(s1.start.scale_at(origin, factor))
            && s1s.end.approx_equal(s1.end.scale_at(origin, factor)));
    }

    test_section("scale");
    {
        constexpr nnm::Vector3f factor { 10.0f, -2.0f, 0.5f };
        constexpr auto s1s = s1.scale(factor);
        ASSERT(s1s.start.approx_equal(s1.start.scale(factor)) && s1s.end.approx_equal(s1.end.scale(factor)));
    }

    test_section("rotate_axis_angle_at");
    {
        constexpr nnm::Vector3f origin { -5.0f, 0.2f, 3.0f };
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = nnm::pi<float>() / 3.0f;
        const auto s1r = s1.rotate_axis_angle_at(origin, axis, angle);
        ASSERT(
            s1r.start.approx_equal(s1.start.rotate_axis_angle_at(origin, axis, angle))
            && s1r.end.approx_equal(s1.end.rotate_axis_angle_at(origin, axis, angle)));
    }

    test_section("rotate_axis_angle");
    {
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = nnm::pi<float>() / 3.0f;
        const auto s1r = s1.rotate_axis_angle(axis, angle);
        ASSERT(
            s1r.start.approx_equal(s1.start.rotate_axis_angle(axis, angle))
            && s1r.end.approx_equal(s1.end.rotate_axis_angle(axis, angle)));
    }

    test_section("rotate_quaternion_at");
    {
        constexpr nnm::Vector3f origin { -5.0f, 0.2f, 3.0f };
        constexpr nnm::QuaternionF quat { 0.0f, 0.5f, 0.05f, 0.866025388f };
        constexpr auto s1r = s1.rotate_quaternion_at(origin, quat);
        ASSERT(
            s1r.start.approx_equal(s1.start.rotate_quaternion_at(origin, quat))
            && s1r.end.approx_equal(s1.end.rotate_quaternion_at(origin, quat)));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::QuaternionF quat { 0.0f, 0.5f, 0.05f, 0.866025388f };
        constexpr auto s1r = s1.rotate_quaternion(quat);
        ASSERT(
            s1r.start.approx_equal(s1.start.rotate_quaternion(quat))
            && s1r.end.approx_equal(s1.end.rotate_quaternion(quat)));
    }

    test_section("shear_x_at");
    {
        constexpr nnm::Vector3f origin { -5.0f, 0.2f, 3.0f };
        constexpr float factor_y = 0.5f;
        constexpr float factor_z = -2.0f;
        constexpr auto s1s = s1.shear_x_at(origin, factor_y, factor_z);
        ASSERT(
            s1s.start.approx_equal(s1.start.shear_x_at(origin, factor_y, factor_z))
            && s1s.end.approx_equal(s1.end.shear_x_at(origin, factor_y, factor_z)));
    }

    test_section("shear_x");
    {
        constexpr float factor_y = 0.5f;
        constexpr float factor_z = -2.0f;
        constexpr auto s1s = s1.shear_x(factor_y, factor_z);
        ASSERT(
            s1s.start.approx_equal(s1.start.shear_x(factor_y, factor_z))
            && s1s.end.approx_equal(s1.end.shear_x(factor_y, factor_z)));
    }

    test_section("shear_y_at");
    {
        constexpr nnm::Vector3f origin { -5.0f, 0.2f, 3.0f };
        constexpr float factor_x = 0.5f;
        constexpr float factor_z = -2.0f;
        constexpr auto s1s = s1.shear_y_at(origin, factor_x, factor_z);
        ASSERT(
            s1s.start.approx_equal(s1.start.shear_y_at(origin, factor_x, factor_z))
            && s1s.end.approx_equal(s1.end.shear_y_at(origin, factor_x, factor_z)));
    }

    test_section("shear_y");
    {
        constexpr float factor_x = 0.5f;
        constexpr float factor_z = -2.0f;
        constexpr auto s1s = s1.shear_y(factor_x, factor_z);
        ASSERT(
            s1s.start.approx_equal(s1.start.shear_y(factor_x, factor_z))
            && s1s.end.approx_equal(s1.end.shear_y(factor_x, factor_z)));
    }

    test_section("shear_z_at");
    {
        constexpr nnm::Vector3f origin { -5.0f, 0.2f, 3.0f };
        constexpr float factor_x = 0.5f;
        constexpr float factor_y = -2.0f;
        constexpr auto s1s = s1.shear_z_at(origin, factor_x, factor_y);
        ASSERT(
            s1s.start.approx_equal(s1.start.shear_z_at(origin, factor_x, factor_y))
            && s1s.end.approx_equal(s1.end.shear_z_at(origin, factor_x, factor_y)));
    }

    test_section("shear_z");
    {
        constexpr float factor_x = 0.5f;
        constexpr float factor_y = -2.0f;
        constexpr auto s1s = s1.shear_z(factor_x, factor_y);
        ASSERT(
            s1s.start.approx_equal(s1.start.shear_z(factor_x, factor_y))
            && s1s.end.approx_equal(s1.end.shear_z(factor_x, factor_y)));
    }

    constexpr nnm::Segment3f s2 { { -4.0f, 5.0f, -6.0f }, { 1.0f, -2.0f, 3.0f } };
    constexpr nnm::Segment3f s3 { { 10.0f, -3.2f, 7.0f }, { 0.0f, 1.0f, -9.0f } };

    test_section("coincident");
    {
        constexpr bool r1 = s1.coincident(s2);
        ASSERT(r1);
        constexpr bool r2 = s1.coincident(s3);
        ASSERT_FALSE(r2);
        constexpr bool r3 = s2.coincident(s2);
        ASSERT(r3);
    }

    test_section("approx_equal");
    {
        constexpr bool r1 = s1.approx_equal(s2);
        ASSERT_FALSE(r1);
        constexpr bool r2 = s1.approx_equal(s3);
        ASSERT_FALSE(r2);
        constexpr bool r3 = s2.approx_equal(s2);
        ASSERT(r3);
    }

    test_section("operator==");
    {
        constexpr bool r1 = s1 == s2;
        ASSERT_FALSE(r1);
        constexpr bool r2 = s1 == s3;
        ASSERT_FALSE(r2);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr bool r3 = s2 == s2;
        ASSERT(r3);
    }

    test_section("operator!=");
    {
        constexpr bool r1 = s1 != s2;
        ASSERT(r1);
        constexpr bool r2 = s1 != s3;
        ASSERT(r2);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr bool r3 = s2 != s2;
        ASSERT_FALSE(r3);
    }

    test_section("operator<");
    {
        constexpr bool r1 = s1 < s2;
        ASSERT_FALSE(r1);
        constexpr bool r2 = s2 < s1;
        ASSERT(r2);
    }
}

inline void plane_tests()
{
    test_case("Plane");

    test_section("Plane()");
    {
        constexpr nnm::PlaneF p;
        ASSERT(p.origin.approx_equal(nnm::Vector3f::zero()));
        ASSERT(p.normal.approx_equal(nnm::Vector3f::axis_x()));
    }

    test_section("Plane(const Vector3&, const Vector3&)");
    {
        constexpr nnm::PlaneF p { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        ASSERT(p.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(p.normal.approx_equal({ -4.0f, 5.0f, -6.0f }));
    }

    test_section("Plane(const Plane<Other>&)");
    {
        constexpr nnm::PlaneD p1 { { 1.0, -2.0, 3.0 }, { -4.0, 5.0, -6.0 } };
        constexpr nnm::PlaneF p2 { p1 };
        ASSERT(p2.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
    }

    test_section("from_points_unchecked");
    {
        const auto p
            = nnm::PlaneF::from_points_unchecked({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { -2.0f, -3.0f, 4.0f });
        constexpr nnm::Vector3f n { -0.0484501608f, 0.775202572f, 0.629852057f };
        ASSERT(p.normal.approx_equal(n) || p.normal.approx_equal(-n));
        ASSERT(p.contains({ 1.0f, -2.0f, 3.0f }));
        ASSERT(p.contains({ -4.0f, 5.0f, -6.0f }));
        ASSERT(p.contains({ -2.0f, -3.0f, 4.0f }));
    }

    test_section("from_points");
    {
        const auto p1 = nnm::PlaneF::from_points({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { -2.0f, -3.0f, 4.0f });
        constexpr nnm::Vector3f n { -0.0484501608f, 0.775202572f, 0.629852057f };
        ASSERT(p1.has_value() && (p1->normal.approx_equal(n) || p1->normal.approx_equal(-n)))
        ASSERT(p1.has_value() && p1->contains({ 1.0f, -2.0f, 3.0f }));
        ASSERT(p1.has_value() && p1->contains({ -4.0f, 5.0f, -6.0f }));
        ASSERT(p1.has_value() && p1->contains({ -2.0f, -3.0f, 4.0f }));
        const auto p2 = nnm::PlaneF::from_points(nnm::Vector3f::zero(), nnm::Vector3f::zero(), nnm::Vector3f::zero());
        ASSERT_FALSE(p2.has_value());
        const auto p3 = nnm::PlaneF::from_points({ -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        ASSERT_FALSE(p3.has_value());
    }

    test_section("from_triangle_unchecked");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { -2.0f, -3.0f, 4.0f } };
        const auto p = nnm::PlaneF::from_triangle_unchecked(t1);
        constexpr nnm::Vector3f n { -0.0484501608f, 0.775202572f, 0.629852057f };
        ASSERT(p.normal.approx_equal(n) || p.normal.approx_equal(-n));
        ASSERT(p.contains({ 1.0f, -2.0f, 3.0f }));
        ASSERT(p.contains({ -4.0f, 5.0f, -6.0f }));
        ASSERT(p.contains({ -2.0f, -3.0f, 4.0f }));
    }

    test_section("from_triangle");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { -2.0f, -3.0f, 4.0f } };
        const auto p1 = nnm::PlaneF::from_triangle(t1);
        constexpr nnm::Vector3f n { -0.0484501608f, 0.775202572f, 0.629852057f };
        ASSERT(p1.has_value() && (p1->normal.approx_equal(n) || p1->normal.approx_equal(-n)))
        ASSERT(p1.has_value() && p1->contains({ 1.0f, -2.0f, 3.0f }));
        ASSERT(p1.has_value() && p1->contains({ -4.0f, 5.0f, -6.0f }));
        ASSERT(p1.has_value() && p1->contains({ -2.0f, -3.0f, 4.0f }));
        constexpr nnm::Triangle3f t2 { nnm::Vector3f::zero(), nnm::Vector3f::zero(), nnm::Vector3f::zero() };
        const auto p2 = nnm::PlaneF::from_triangle(t2);
        ASSERT_FALSE(p2.has_value());
        constexpr nnm::Triangle3f t3 { { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } };
        const auto p3 = nnm::PlaneF::from_triangle(t3);
        ASSERT_FALSE(p3.has_value());
    }

    test_section("xy");
    {
        constexpr auto p = nnm::PlaneF::xy();
        ASSERT(p.origin.approx_zero());
        ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        ASSERT(p.normal.parallel(nnm::Vector3f::axis_z()));
    }

    test_section("xy_offset");
    {
        constexpr auto p = nnm::PlaneF::xy_offset(3.0f);
        ASSERT(p.origin.approx_equal({ 0.0f, 0.0f, 3.0f }));
        ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        ASSERT(p.normal.parallel(nnm::Vector3f::axis_z()));
    }

    test_section("xz");
    {
        constexpr auto p = nnm::PlaneF::xz();
        ASSERT(p.origin.approx_zero());
        ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        ASSERT(p.normal.parallel(nnm::Vector3f::axis_y()));
    }

    test_section("xz_offset");
    {
        constexpr auto p = nnm::PlaneF::xz_offset(3.0f);
        ASSERT(p.origin.approx_equal({ 0.0f, 3.0f, 0.0f }));
        ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        ASSERT(p.normal.parallel(nnm::Vector3f::axis_y()));
    }

    test_section("yz");
    {
        constexpr auto p = nnm::PlaneF::yz();
        ASSERT(p.origin.approx_zero());
        ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        ASSERT(p.normal.parallel(nnm::Vector3f::axis_x()));
    }

    test_section("yz_offset");
    {
        constexpr auto p = nnm::PlaneF::yz_offset(3.0f);
        ASSERT(p.origin.approx_equal({ 3.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        ASSERT(p.normal.parallel(nnm::Vector3f::axis_x()));
    }

    test_section("normalize");
    {
        constexpr nnm::PlaneF p { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        const auto norm = p.normalize();
        ASSERT(norm.origin.approx_equal(p.origin));
        ASSERT(norm.normal.approx_equal({ -0.455844f, 0.569805f, -0.683766f }));
    }

    test_section("coplanar(const Line3&)");
    {
        constexpr nnm::Line3f l1 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };
        constexpr auto result = nnm::PlaneF::xy().coplanar(l1);
        ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        ASSERT(plane.coplanar(l1));
    }

    test_section("coplanar(const Ray3&)");
    {
        constexpr nnm::Ray3f r2 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };
        constexpr auto result = nnm::PlaneF::xy().coplanar(r2);
        ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        ASSERT(plane.coplanar(r2));
    }

    test_section("coplanar(const Segment3&)");
    {
        constexpr nnm::Segment3f s4 { { 1.0f, -2.0f, 3.0f }, { 2.0f, -3.0f, 4.0f } };
        constexpr auto result = nnm::PlaneF::xy().coplanar(s4);
        ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        ASSERT(plane.coplanar(s4));
    }

    constexpr nnm::PlaneF p1 { { 1.0f, -2.0f, 3.0f }, { -0.455844f, 0.569805f, -0.683766f } };

    test_section("coplanar(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { p1.origin, -p1.normal };
        constexpr auto result = p1.coplanar(p2);
        ASSERT(result);
        constexpr nnm::PlaneF p3 { nnm::Vector3f::zero(), nnm::Vector3f::axis_z() };
        constexpr nnm::PlaneF p4 { { 1.0f, 2.0f, 0.0f }, -nnm::Vector3f::axis_z() };
        ASSERT(p3.coplanar(p4));
        ASSERT(p4.coplanar(p3));
        ASSERT_FALSE(p1.coplanar(p4));
    }

    test_section("coplanar(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr nnm::Triangle3f t2 { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        const bool r1 = nnm::PlaneF::from_triangle_unchecked(t1).coplanar(t1);
        ASSERT(r1);
        const bool r2 = nnm::PlaneF::xy().coplanar(t1);
        ASSERT_FALSE(r2);
        const bool r3 = nnm::PlaneF::xy().coplanar(t2);
        ASSERT(r3);
        const bool r4 = nnm::PlaneF::xz().coplanar(t2);
        ASSERT(r4);
        const bool r5 = nnm::PlaneF::yz().coplanar(t2);
        ASSERT_FALSE(r5);
        const bool r6 = nnm::PlaneF::xz_offset(100.0f).coplanar(t2);
        ASSERT_FALSE(r6);
    }

    constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };

    test_section("contains");
    {
        constexpr auto result = p2.contains({ -1.89f, -3.46f, 1.46f });
        ASSERT(result);
        ASSERT(p2.contains({ 1.0f, -2.0f, 0.0f }));
        ASSERT_FALSE(p2.contains({ 1.0f, -2.0f, 1.0f }));
        ASSERT_FALSE(p2.contains({ 5.0f, -20.0f, -100.0f }));
    }

    test_section("distance(const Vector3&)");
    {
        constexpr auto result = p2.distance({ -1.89f, -3.46f, 1.46f });
        ASSERT(nnm::approx_zero(result));
        ASSERT(nnm::approx_equal(p2.distance({ -1.89f, -2.752893f, 2.167107f }), 1.0f));
        ASSERT(nnm::approx_equal(p2.distance({ 100.0f, -6.995535f, -2.075535f }), 5.0f));
    }

    test_section("distance(const Line3&)");
    {
        constexpr auto d1 = p2.distance(nnm::Line3f::axis_x());
        ASSERT(nnm::approx_equal(d1, nnm::sqrt(2.0f)));
        constexpr auto d2 = p2.distance(nnm::Line3f::axis_z());
        ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = p2.distance(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        ASSERT(nnm::approx_equal(d3, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d4 = p2.distance(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = p2.distance(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        ASSERT(nnm::approx_zero(d5));
    }

    test_section("distance(const Ray3&)");
    {
        constexpr auto d1 = p2.distance(nnm::Ray3f { nnm::Vector3f::zero(), nnm::Vector3f::axis_y() });
        ASSERT(nnm::approx_equal(d1, nnm::sqrt(2.0f)));
        constexpr auto d2 = p2.distance(nnm::Ray3f { nnm::Ray3f { nnm::Vector3f::zero(), -nnm::Vector3f::axis_y() } });
        ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = p2.distance(nnm::Ray3f { nnm::Vector3f::zero(), nnm::Vector3f::axis_x() });
        ASSERT(nnm::approx_equal(d3, nnm::sqrt(2.0f)));
        constexpr auto d4 = p2.distance(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        ASSERT(nnm::approx_equal(d4, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d5 = p2.distance(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        ASSERT(nnm::approx_equal(d5, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d6 = p2.distance(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_z() });
        ASSERT(nnm::approx_zero(d6));
    }

    test_section("distance(const Segment3&)");
    {
        constexpr auto d1 = p2.distance(nnm::Segment3f { nnm::Vector3f::zero(), { 3.0f, 0.0f, 0.0f } });
        ASSERT(nnm::approx_equal(d1, nnm::sqrt(2.0f)));
        constexpr auto d2 = p2.distance(nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, { 200.0f, -4.0f, -4.0f } });
        ASSERT(nnm::approx_equal(d2, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d3 = p2.distance(nnm::Segment3f { nnm::Vector3f::zero(), { -100.0f, -4.0f, -4.0f } });
        ASSERT(nnm::approx_zero(d3));
        constexpr auto d4 = p2.distance(nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::zero() });
        ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = p2.distance(nnm::Segment3f { nnm::Vector3f::zero(), { 0.0f, 3.0f, 0.0f } });
        ASSERT(nnm::approx_equal(d5, nnm::sqrt(2.0f)));
        constexpr auto d6 = p2.distance(nnm::Segment3f { { 0.0f, 3.0f, 0.0f }, nnm::Vector3f::zero() });
        ASSERT(nnm::approx_equal(d6, nnm::sqrt(2.0f)));
        constexpr auto d7 = p2.distance(nnm::Segment3f { { 0.0f, -4.0f, 0.0f }, { 0.0f, -8.0f, 0.0f } });
        ASSERT(nnm::approx_equal(d7, nnm::sqrt(2.0f)));
        constexpr auto d8 = p2.distance(nnm::Segment3f { { 0.0f, -8.0f, 0.0f }, { 0.0f, -4.0f, 0.0f } });
        ASSERT(nnm::approx_equal(d8, nnm::sqrt(2.0f)));
    }

    test_section("distance(const Plane&)");
    {
        constexpr auto d1 = p2.distance(p2);
        ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = p2.distance(nnm::PlaneF { p2.origin.translate({ 100.0f, 0.0f, 0.0f }), -p2.normal });
        ASSERT(nnm::approx_zero(d2));
        constexpr auto d3
            = p2.distance(nnm::PlaneF { p2.origin.translate({ -100.0f, 0.707107f, 0.707107f }), p2.normal });
        ASSERT(nnm::approx_equal(d3, 1.0f));
        constexpr auto d4
            = p2.distance(nnm::PlaneF { p2.origin.translate({ -100.0f, -0.707107f, -0.707107f }), p2.normal });
        ASSERT(nnm::approx_equal(d4, 1.0f));
        constexpr auto d5 = p1.distance(p2);
        ASSERT(nnm::approx_zero(d5));
        constexpr auto d6 = p2.distance(p1);
        ASSERT(nnm::approx_zero(d6));
    }

    test_section("parallel(const Line3&)");
    {
        constexpr auto r1 = p2.parallel(nnm::Line3f::axis_x());
        ASSERT(r1);
        constexpr auto r2 = p2.parallel(nnm::Line3f::axis_z());
        ASSERT_FALSE(r2);
        constexpr auto r3 = p2.parallel(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        ASSERT(r3);
        constexpr auto r4 = p2.parallel(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        ASSERT_FALSE(r4);
        constexpr auto r5 = p2.parallel(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        ASSERT_FALSE(r5);
    }

    test_section("parallel(const Ray3&)");
    {
        constexpr auto r1 = p2.parallel(nnm::Ray3f { nnm::Vector3f::zero(), nnm::Vector3f::axis_y() });
        ASSERT_FALSE(r1);
        constexpr auto r2 = p2.parallel(nnm::Ray3f { nnm::Ray3f { nnm::Vector3f::zero(), -nnm::Vector3f::axis_y() } });
        ASSERT_FALSE(r2);
        constexpr auto r3 = p2.parallel(nnm::Ray3f { nnm::Vector3f::zero(), nnm::Vector3f::axis_x() });
        ASSERT(r3);
        constexpr auto r4 = p2.parallel(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        ASSERT_FALSE(r4);
        constexpr auto r5 = p2.parallel(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_x() });
        ASSERT(r5);
        constexpr auto r6 = p2.parallel(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_z() });
        ASSERT_FALSE(r6);
    }

    test_section("parallel(const Segment&)");
    {
        constexpr auto r1 = p2.parallel(nnm::Segment3f { nnm::Vector3f::zero(), { 3.0f, 0.0f, 0.0f } });
        ASSERT(r1);
        constexpr auto r2 = p2.parallel(nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, { 200.0f, -4.0f, -4.0f } });
        ASSERT(r2);
        constexpr auto r3 = p2.parallel(nnm::Segment3f { nnm::Vector3f::zero(), { -100.0f, -4.0f, -4.0f } });
        ASSERT_FALSE(r3);
        constexpr auto r4 = p2.parallel(nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::zero() });
        ASSERT_FALSE(r4);
        constexpr auto r5 = p2.parallel(nnm::Segment3f { nnm::Vector3f::zero(), { 0.0f, 3.0f, 0.0f } });
        ASSERT_FALSE(r5);
        constexpr auto r6 = p2.parallel(nnm::Segment3f { { 0.0f, 3.0f, 0.0f }, nnm::Vector3f::zero() });
        ASSERT_FALSE(r6);
        constexpr auto r7 = p2.parallel(nnm::Segment3f { { 0.0f, -4.0f, 0.0f }, { 0.0f, -8.0f, 0.0f } });
        ASSERT_FALSE(r7);
        constexpr auto r8 = p2.parallel(nnm::Segment3f { { 0.0f, -8.0f, 0.0f }, { 0.0f, -4.0f, 0.0f } });
        ASSERT_FALSE(r8);
    }

    test_section("parallel(const Plane&)");
    {
        constexpr auto r1 = p2.parallel(p2);
        ASSERT(r1);
        constexpr auto r2 = p2.parallel(nnm::PlaneF { p2.origin.translate({ 100.0f, 0.0f, 0.0f }), -p2.normal });
        ASSERT(r2);
        constexpr auto r3
            = p2.parallel(nnm::PlaneF { p2.origin.translate({ -100.0f, 0.707107f, 0.707107f }), p2.normal });
        ASSERT(r3);
        constexpr auto r4
            = p2.parallel(nnm::PlaneF { p2.origin.translate({ -100.0f, -0.707107f, -0.707107f }), p2.normal });
        ASSERT(r4);
        constexpr auto r5 = p1.parallel(p2);
        ASSERT_FALSE(r5);
        constexpr auto r6 = p2.parallel(p1);
        ASSERT_FALSE(r6);
    }

    test_section("perpendicular(const Line3&)");
    {
        constexpr auto r1 = p2.perpendicular(nnm::Line3f::axis_x());
        ASSERT_FALSE(r1);
        constexpr auto r2 = p2.perpendicular(nnm::Line3f { nnm::Vector3f::zero(), p2.normal });
        ASSERT(r2);
        constexpr auto r3 = p2.perpendicular(nnm::Line3f { nnm::Vector3f::zero(), -p2.normal });
        ASSERT(r3);
        constexpr auto r4 = p2.perpendicular(nnm::Line3f::axis_z());
        ASSERT_FALSE(r4);
    }

    test_section("perpendicular(const Ray3&)");
    {
        constexpr auto r1 = p2.perpendicular(nnm::Ray3f { nnm::Vector3f::zero(), nnm::Vector3f::axis_x() });
        ASSERT_FALSE(r1);
        constexpr auto r2 = p2.perpendicular(nnm::Ray3f { nnm::Vector3f::zero(), -nnm::Vector3f::axis_y() });
        ASSERT_FALSE(r2);
        constexpr auto r3 = p2.perpendicular(nnm::Ray3f { nnm::Vector3f::zero(), p2.normal });
        ASSERT(r3);
        constexpr auto r4 = p2.perpendicular(nnm::Ray3f { nnm::Vector3f::zero(), -p2.normal });
        ASSERT(r4);
    }

    test_section("perpendicular(const Segment3&)");
    {
        constexpr auto r1 = p2.perpendicular(nnm::Segment3f { nnm::Vector3f::zero(), { 0.0f, 1.0f, 0.0f } });
        ASSERT_FALSE(r1);
        constexpr auto r2 = p2.perpendicular(nnm::Segment3f { nnm::Vector3f::zero(), { 0.0f, -100.0f, 0.0f } });
        ASSERT_FALSE(r2);
        constexpr auto r3 = p2.perpendicular(nnm::Segment3f { { -100.0f, 10.0f, 10.0f }, { 100.0f, 10.0f, 10.0f } });
        ASSERT_FALSE(r3);
        constexpr auto r4 = p2.perpendicular(nnm::Segment3f { nnm::Vector3f::zero(), { 0.0f, 100.0f, 100.0f } });
        ASSERT(r4);
        constexpr auto r5 = p2.perpendicular(nnm::Segment3f { { 0.0f, 100.0f, 100.0f }, nnm::Vector3f::zero() });
        ASSERT(r5);
        constexpr auto r6 = p2.perpendicular(nnm::Segment3f { { 0.0f, 100.0f, 100.0f }, { 0.0f, -100.0, -100.0f } });
        ASSERT(r6);
    }

    test_section("perpendicular(const Plane&)");
    {
        constexpr auto r1 = p2.perpendicular(p2);
        ASSERT_FALSE(r1);
        constexpr auto r2
            = p2.perpendicular(nnm::PlaneF { { 100.0f, -20.0f, 0.5f }, p2.normal.arbitrary_perpendicular() });
        ASSERT(r2);
        constexpr auto r3 = p1.perpendicular(p2);
        ASSERT_FALSE(r3);
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto r1 = p2.intersects(nnm::Line3f::axis_x());
        ASSERT_FALSE(r1);
        constexpr auto r2 = p2.intersects(nnm::Line3f::axis_z());
        ASSERT(r2);
        constexpr auto r3 = p2.intersects(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        ASSERT_FALSE(r3);
        constexpr auto r4 = p2.intersects(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        ASSERT(r4);
        constexpr auto r5 = p2.intersects(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        ASSERT(r5);
        constexpr auto r6 = p2.intersects(nnm::Line3f::axis_x_offset(-2.0f, 0.0f));
        ASSERT(r6);
    }

    test_section("intersection(const Line3&)");
    {
        constexpr auto i1 = p2.intersection(nnm::Line3f::axis_x());
        ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = p2.intersection(nnm::Line3f::axis_z());
        ASSERT(i2.has_value() && i2->approx_equal({ 0.0f, 0.0f, -2.0f }));
        constexpr auto i3 = p2.intersection(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        ASSERT_FALSE(i3.has_value());
        constexpr auto i4 = p2.intersection(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        ASSERT(i4.has_value() && i4->approx_equal({ -100.0f, 2.0f, -4.0f }));
        constexpr auto i5 = p2.intersection(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        ASSERT(i5.has_value() && i5->approx_equal({ -100.0f, 2.0f, -4.0f }));
        constexpr auto i6 = p2.intersection(nnm::Line3f::axis_x_offset(-2.0f, 0.0f));
        ASSERT_FALSE(i6.has_value());
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr auto r1 = p2.intersects(nnm::Ray3f { nnm::Vector3f::zero(), nnm::Vector3f::axis_x() });
        ASSERT_FALSE(r1);
        constexpr auto r2 = p2.intersects(nnm::Ray3f { nnm::Vector3f::zero(), nnm::Vector3f::axis_z() });
        ASSERT_FALSE(r2);
        constexpr auto r3 = p2.intersects(nnm::Ray3f { nnm::Vector3f::zero(), -nnm::Vector3f::axis_z() });
        ASSERT(r3);
        constexpr auto r4 = p2.intersects(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        ASSERT_FALSE(r4);
        constexpr auto r5 = p2.intersects(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        ASSERT(r5);
        constexpr auto r6 = p2.intersects(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        ASSERT_FALSE(r6);
        constexpr auto r7 = p2.intersects(nnm::Ray3f { { 0.0f, -2.0f, 0.0f }, nnm::Vector3f::axis_x() });
        ASSERT(r7);
    }

    test_section("intersection(const Ray3&)");
    {
        constexpr auto i1 = p2.intersection(nnm::Ray3f { nnm::Vector3f::zero(), nnm::Vector3f::axis_x() });
        ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = p2.intersection(nnm::Ray3f { nnm::Vector3f::zero(), nnm::Vector3f::axis_z() });
        ASSERT_FALSE(i2.has_value());
        constexpr auto i3 = p2.intersection(nnm::Ray3f { nnm::Vector3f::zero(), -nnm::Vector3f::axis_z() });
        ASSERT(i3.has_value() && i3->approx_equal({ 0.0f, 0.0f, -2.0f }));
        constexpr auto i4 = p2.intersection(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        ASSERT_FALSE(i4.has_value());
        constexpr auto i5 = p2.intersection(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        ASSERT(i5.has_value() && i5->approx_equal({ -100.0f, 2.0f, -4.0f }));
        constexpr auto i6 = p2.intersection(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        ASSERT_FALSE(i6.has_value());
        constexpr auto i7 = p2.intersection(nnm::Ray3f { { 0.0f, -2.0f, 0.0f }, nnm::Vector3f::axis_x() });
        ASSERT_FALSE(i7.has_value());
    }

    test_section("intersects(const Segment3&)");
    {
        constexpr auto r1 = p2.intersects(nnm::Segment3f { nnm::Vector3f::zero(), { 0.0f, 1.0f, 0.0f } });
        ASSERT_FALSE(r1);
        constexpr auto r2 = p2.intersects(nnm::Segment3f { nnm::Vector3f::zero(), { 0.0f, -100.0f, 0.0f } });
        ASSERT(r2);
        constexpr auto r3 = p2.intersects(nnm::Segment3f { { -100.0f, 10.0f, 10.0f }, { 100.0f, 10.0f, 10.0f } });
        ASSERT_FALSE(r3);
        constexpr auto r4 = p2.intersects(nnm::Segment3f { { -100.0f, -100.0f, -100.0f }, { 100.0f, 100.0f, 100.0f } });
        ASSERT(r4);
        constexpr auto r5 = p2.intersects(nnm::Segment3f { { 100.0f, 100.0f, 100.0f }, { -100.0f, -100.0f, -100.0f } });
        ASSERT(r5);
        constexpr auto r6 = p2.intersects(nnm::Segment3f { { -10.0f, -10.0f, 0.0f }, { -10.0f, -10.0, -10.0f } });
        ASSERT_FALSE(r6);
        constexpr auto r7 = p2.intersects(nnm::Segment3f { { 0.0f, -2.0f, 0.0f }, { 100.0f, -2.0f, 0.0f } });
        ASSERT(r7);
    }

    test_section("intersection(const Segment3&)");
    {
        constexpr auto i1 = p2.intersection(nnm::Segment3f { nnm::Vector3f::zero(), { 0.0f, 1.0f, 0.0f } });
        ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = p2.intersection(nnm::Segment3f { nnm::Vector3f::zero(), { 0.0f, -100.0f, 0.0f } });
        ASSERT(i2.has_value() && i2->approx_equal({ 0.0f, -2.0f, 0.0f }));
        constexpr auto i3 = p2.intersection(nnm::Segment3f { { -100.0f, 10.0f, 10.0f }, { 100.0f, 10.0f, 10.0f } });
        ASSERT_FALSE(i3.has_value());
        constexpr auto i4
            = p2.intersection(nnm::Segment3f { { -100.0f, -100.0f, -100.0f }, { 100.0f, 100.0f, 100.0f } });
        ASSERT(i4.has_value() && i4->approx_equal({ -1.0f, -1.0f, -1.0f }));
        constexpr auto i5
            = p2.intersection(nnm::Segment3f { { 100.0f, 100.0f, 100.0f }, { -100.0f, -100.0f, -100.0f } });
        ASSERT(i5.has_value() && i5->approx_equal({ -1.0f, -1.0f, -1.0f }));
        constexpr auto i6 = p2.intersection(nnm::Segment3f { { -10.0f, -10.0f, 0.0f }, { -10.0f, -10.0, -10.0f } });
        ASSERT_FALSE(i6.has_value());
        constexpr auto i7 = p2.intersection(nnm::Segment3f { { 0.0f, -2.0f, 0.0f }, { 100.0f, -2.0f, 0.0f } });
        ASSERT_FALSE(i7.has_value());
    }

    test_section("intersects(const Plane&)");
    {
        constexpr auto r1 = p2.intersects(p2);
        ASSERT(r1);
        constexpr auto r2 = p2.intersects(nnm::PlaneF { p2.origin.translate({ 100.0f, 0.0f, 0.0f }), -p2.normal });
        ASSERT(r2);
        constexpr auto r3
            = p2.intersects(nnm::PlaneF { p2.origin.translate({ -100.0f, 0.707107f, 0.707107f }), p2.normal });
        ASSERT_FALSE(r3);
        constexpr auto r4
            = p2.intersects(nnm::PlaneF { p2.origin.translate({ -100.0f, -0.707107f, -0.707107f }), p2.normal });
        ASSERT_FALSE(r4);
        constexpr auto r5 = p1.intersects(p2);
        ASSERT(r5);
        constexpr auto r6 = p2.intersects(p1);
        ASSERT(r6);
    }

    test_section("intersection(const Plane&)");
    {
        const auto i1 = p2.intersection(p2);
        ASSERT_FALSE(i1.has_value());
        const auto i2 = p2.intersection(nnm::PlaneF { p2.origin.translate({ 100.0f, 0.0f, 0.0f }), -p2.normal });
        ASSERT_FALSE(i2.has_value());
        const auto i3
            = p2.intersection(nnm::PlaneF { p2.origin.translate({ -100.0f, 0.707107f, 0.707107f }), p2.normal });
        ASSERT_FALSE(i3.has_value());
        const auto i4
            = p2.intersection(nnm::PlaneF { p2.origin.translate({ -100.0f, -0.707107f, -0.707107f }), p2.normal });
        ASSERT_FALSE(i4.has_value());
        const auto i5 = p1.intersection(p2);
        ASSERT(
            i5.has_value() && p1.contains(i5->origin) && p2.contains(i5->origin) && p1.parallel(*i5)
            && p2.parallel(*i5));
        const auto i6 = p2.intersection(p1);
        ASSERT(
            i6.has_value() && p2.contains(i6->origin) && p2.contains(i6->origin) && p2.parallel(*i6)
            && p2.parallel(*i6));
        constexpr nnm::PlaneF p3 { nnm::Vector3f::zero(), nnm::Vector3f::axis_z() };
        const auto i7 = p2.intersection(p3);
        ASSERT(
            i7.has_value() && p2.contains(i7->origin) && p3.contains(i7->origin) && p2.parallel(*i7)
            && p3.parallel(*i7));
    }

    test_section("project");
    {
        constexpr nnm::Vector3f pt1 = p2.project({ 1.0f, -2.0f, 3.0f });
        ASSERT(pt1.approx_equal({ 1.0f, -3.5f, 1.5f }));
        constexpr nnm::Vector3f pt2 = p2.project({ 0.0f, -2.0f, 0.0f });
        ASSERT(pt2.approx_equal({ 0.0f, -2.0f, 0.0f }));
        constexpr nnm::Vector3f pt3 = p2.project({ 3.0f, -4.0f, -2.0f });
        ASSERT(pt3.approx_equal({ 3.0f, -2.0f, 0.0f }));
    }

    test_section("translate");
    {
        constexpr nnm::PlaneF p2t = p2.translate({ 1.0f, -2.0f, 3.0f });
        ASSERT(p2t.approx_equal({ { 2.0f, -4.0f, 3.0f }, p2.normal }));
    }

    test_section("scale_at");
    {
        const nnm::PlaneF p2s = p2.scale_at({ -3.0f, 2.0f, -1.0f }, { 0.5f, 1.0f, -2.0f });
        ASSERT(p2s.approx_equal({ { -1.0f, -2.0f, -3.0f }, { 0.0f, 0.447214f, -0.89442f } }));
    }

    test_section("scale");
    {
        const nnm::PlaneF p2s = p2.scale({ 0.5f, 1.0f, -2.0f });
        ASSERT(p2s.approx_equal({ { 0.5f, -2.0f, 0.0f }, { 0.0f, 0.447214f, -0.89442f } }));
    }

    test_section("rotate_axis_angle_at");
    {
        constexpr nnm::Vector3f origin { -3.0f, 2.0f, -1.0f };
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr auto angle = nnm::pi<float>() / 5.0f;
        const nnm::PlaneF p2r = p2.rotate_axis_angle_at(origin, axis, angle);
        const nnm::PlaneF p2r_expected { p2.origin.rotate_axis_angle_at(origin, axis, angle),
                                         p2.normal.rotate_axis_angle(axis, angle).normalize() };
        ASSERT(p2r.approx_equal(p2r_expected));
    }

    test_section("rotate_axis_angle");
    {
        constexpr auto axis = nnm::Vector3f::axis_z();
        constexpr auto angle = -nnm::pi<float>() / 5.0f;
        const nnm::PlaneF p2r = p2.rotate_axis_angle(axis, angle);
        const nnm::PlaneF p2r_expected { p2.origin.rotate_axis_angle(axis, angle),
                                         p2.normal.rotate_axis_angle(axis, angle).normalize() };
        ASSERT(p2r.approx_equal(p2r_expected));
    }

    test_section("rotate_quaternion_at");
    {
        constexpr nnm::Vector3f origin { -3.0f, 2.0f, -1.0f };
        const auto quat = nnm::QuaternionF::from_axis_angle(-nnm::Vector3f::axis_y(), 3.0f * nnm::pi<float>() / 2.0f);
        const nnm::PlaneF p2r = p2.rotate_quaternion_at(origin, quat);
        const nnm::PlaneF p2r_expected { p2.origin.rotate_quaternion_at(origin, quat),
                                         p2.normal.rotate_quaternion(quat).normalize() };
        ASSERT(p2r.approx_equal(p2r_expected));
    }

    test_section("rotate_quaternion");
    {
        const auto quat = nnm::QuaternionF::from_axis_angle(-nnm::Vector3f::axis_y(), 3.0f * nnm::pi<float>() / 2.0f);
        const nnm::PlaneF p2r = p2.rotate_quaternion(quat);
        const nnm::PlaneF p2r_expected { p2.origin.rotate_quaternion(quat),
                                         p2.normal.rotate_quaternion(quat).normalize() };
        ASSERT(p2r.approx_equal(p2r_expected));
    }

    test_section("shear_x_at");
    {
        constexpr nnm::Vector3f origin { -3.0f, 2.0f, -1.0f };
        constexpr float factor_y = 2.0f;
        constexpr float factor_z = -0.5f;
        const nnm::PlaneF p2s = p2.shear_x_at(origin, factor_y, factor_z);
        const nnm::PlaneF p2s_expected { p2.origin.shear_x_at(origin, factor_y, factor_z),
                                         p2.normal.shear_x(factor_y, factor_z).normalize() };
        ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("shear_x");
    {
        constexpr float factor_y = 2.0f;
        constexpr float factor_z = -0.5f;
        const nnm::PlaneF p2s = p2.shear_x(factor_y, factor_z);
        const nnm::PlaneF p2s_expected { p2.origin.shear_x(factor_y, factor_z),
                                         p2.normal.shear_x(factor_y, factor_z).normalize() };
        ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("shear_y_at");
    {
        constexpr nnm::Vector3f origin { -3.0f, 2.0f, -1.0f };
        constexpr float factor_x = 2.0f;
        constexpr float factor_z = -0.5f;
        const nnm::PlaneF p2s = p2.shear_y_at(origin, factor_x, factor_z);
        const nnm::PlaneF p2s_expected { p2.origin.shear_y_at(origin, factor_x, factor_z),
                                         p2.normal.shear_y(factor_x, factor_z).normalize() };
        ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("shear_y");
    {
        constexpr float factor_x = 2.0f;
        constexpr float factor_z = -0.5f;
        const nnm::PlaneF p2s = p2.shear_y(factor_x, factor_z);
        const nnm::PlaneF p2s_expected { p2.origin.shear_y(factor_x, factor_z),
                                         p2.normal.shear_y(factor_x, factor_z).normalize() };
        ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("shear_z_at");
    {
        constexpr nnm::Vector3f origin { -3.0f, 2.0f, -1.0f };
        constexpr float factor_x = 2.0f;
        constexpr float factor_y = -0.5f;
        const nnm::PlaneF p2s = p2.shear_z_at(origin, factor_x, factor_y);
        const nnm::PlaneF p2s_expected { p2.origin.shear_z_at(origin, factor_x, factor_y),
                                         p2.normal.shear_z(factor_x, factor_y).normalize() };
        ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("shear_z");
    {
        constexpr float factor_x = 2.0f;
        constexpr float factor_y = -0.5f;
        const nnm::PlaneF p2s = p2.shear_z(factor_x, factor_y);
        const nnm::PlaneF p2s_expected { p2.origin.shear_z(factor_x, factor_y),
                                         p2.normal.shear_z(factor_x, factor_y).normalize() };
        ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("approx_equal");
    {
        constexpr auto result = p2.approx_equal(p2);
        ASSERT(result);
        ASSERT_FALSE(p2.approx_equal(p1));
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = p2 == p2;
        ASSERT(result);
        ASSERT_FALSE(p1 == p2);
    }

    test_section("operator!=");
    {
        constexpr auto result = p1 != p2;
        ASSERT(result);
        ASSERT_FALSE(p2 != p2);
    }

    test_section("operator<");
    {
        constexpr auto result = p2 < p1;
        ASSERT(result);
        ASSERT_FALSE(p1 < p2);
    }
}

inline void triangle3_tests()
{
    test_case("triangle3");

    test_section("Triangle3()");
    {
        constexpr nnm::Triangle3f t1;
        ASSERT(t1.vertices[0].approx_equal(nnm::Vector3f::zero()));
        ASSERT(t1.vertices[1].approx_equal(nnm::Vector3f::zero()));
        ASSERT(t1.vertices[2].approx_equal(nnm::Vector3f::zero()));
    }

    test_section("Triangle3(const Vector3&, const Vector3&, const Vector3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        ASSERT(t1.vertices[1].approx_equal({ -2.0f, 3.0f, -4.0f }));
        ASSERT(t1.vertices[0].approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(t1.vertices[2].approx_equal({ 4.0f, 0.0f, 2.0f }));
    }

    test_section("Triangle3(const Triangle3<Other>&)");
    {
        constexpr nnm::Triangle3d t1 { { 1.0, -2.0, 3.0 }, { -2.0, 3.0, -4.0 }, { 4.0, 0.0, 2.0 } };
        constexpr nnm::Triangle3f t2 { t1 };
        ASSERT(t2.vertices[1].approx_equal({ -2.0f, 3.0f, -4.0f }));
        ASSERT(t2.vertices[0].approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(t2.vertices[2].approx_equal({ 4.0f, 0.0f, 2.0f }));
    }

    constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };

    test_section("edge");
    {
        constexpr nnm::Segment3f e0 = t1.edge(0);
        constexpr nnm::Segment3f e1 = t1.edge(1);
        constexpr nnm::Segment3f e2 = t1.edge(2);
        ASSERT(e0.approx_equal({ { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f } }));
        ASSERT(e1.approx_equal({ { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } }));
        ASSERT(e2.approx_equal({ { 4.0f, 0.0f, 2.0f }, { 1.0f, -2.0f, 3.0f } }));
    }

    test_section("centroid");
    {
        constexpr nnm::Vector3f c = t1.centroid();
        constexpr nnm::Vector3f average = (t1.vertices[0] + t1.vertices[1] + t1.vertices[2]) / 3.0f;
        ASSERT(c.approx_equal(average));
    }

    constexpr nnm::Triangle3f t2 { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };

    test_section("circumcenter");
    {
        const std::optional<nnm::Vector3f> c1 = t1.circumcenter();
        ASSERT(c1.has_value() && c1->approx_equal({ 0.245901704f, 0.844262301f, -0.573770523f }));
        const std::optional<nnm::Vector3f> c2 = t2.circumcenter();
        ASSERT_FALSE(c2.has_value());
    }

    test_section("perimeter");
    {
        const float p1 = t1.perimeter();
        ASSERT(nnm::approx_equal(p1, 21.85209097f));
        const float p2 = t2.perimeter();
        ASSERT(nnm::approx_equal(p2, 4.0f));
    }

    test_section("incenter");
    {
        const auto result = t1.incenter();
        ASSERT(result.has_value() && result->approx_equal({ 1.7370612086f, -0.3100402543f, 1.3845008086f }));
        ASSERT_FALSE(t2.incenter().has_value());
    }

    test_section("orthocenter");
    {
        const std::optional<nnm::Vector3f> c1 = t1.orthocenter();
        ASSERT(c1.has_value() && c1->approx_equal({ 2.50819683f, -0.688524485f, 2.14754105f }));
        const std::optional<nnm::Vector3f> c2 = t2.orthocenter();
        ASSERT_FALSE(c2.has_value());
    }

    constexpr nnm::Triangle3f t3 { { 4.0f, 0.0f, 2.0f }, { -2.0f, 3.0f, -4.0f }, { 1.0f, -2.0f, 3.0f } };

    test_section("area");
    {
        const float a1 = t1.area();
        ASSERT(nnm::approx_equal(a1, 16.5680415258f));
        const float a2 = t2.area();
        ASSERT(nnm::approx_zero(a2));
        const float a3 = t3.area();
        ASSERT(nnm::approx_equal(a3, 16.5680415258f));
    }

    test_section("median");
    {
        constexpr nnm::Segment3f m0 = t1.median(0);
        ASSERT(m0.approx_equal({ { 1.0f, -2.0f, 3.0f }, { 1.0f, 1.5f, -1.0f } }));
        constexpr nnm::Segment3f m1 = t1.median(1);
        ASSERT(m1.approx_equal({ { -2.0f, 3.0f, -4.0f }, { 2.5f, -1.0f, 2.5f } }));
        constexpr nnm::Segment3f m2 = t1.median(2);
        ASSERT(m2.approx_equal({ { 4.0f, 0.0f, 2.0f }, { -0.5f, 0.5f, -0.5f } }));
    }

    test_section("perpendicular_bisector");
    {
        const std::optional<nnm::Line3f> pb0 = t1.perpendicular_bisector(0);
        ASSERT(
            pb0.has_value()
            && pb0->approx_equal({ { -0.5f, 0.5f, -0.5f }, { -0.904320657f, -0.417378753f, 0.0894383192f } }));
        const std::optional<nnm::Line3f> pb1 = t1.perpendicular_bisector(1);
        ASSERT(
            pb1.has_value()
            && pb1->approx_equal({ { 1.0f, 1.5f, -1.0f }, { 0.694107413f, 0.603571713f, -0.392321587f } }));
        const std::optional<nnm::Line3f> pb2 = t1.perpendicular_bisector(2);
        ASSERT(
            pb2.has_value()
            & pb2->approx_equal({ { 2.5f, -1.0f, 2.5f }, { 0.532327354f, -0.435540527f, 0.725900888f } }));
        const std::optional<nnm::Line3f> pb3 = t2.perpendicular_bisector(0);
        ASSERT_FALSE(pb3.has_value());
        const std::optional<nnm::Line3f> pb4 = t2.perpendicular_bisector(1);
        ASSERT_FALSE(pb4.has_value());
        const std::optional<nnm::Line3f> pb5 = t2.perpendicular_bisector(2);
        ASSERT_FALSE(pb5.has_value());
    }

    test_section("angle");
    {
        const float a0 = t1.angle(0);
        ASSERT(nnm::approx_equal(a0, 1.3339009374f));
        const float a1 = t1.angle(1);
        ASSERT(nnm::approx_equal(a1, 0.4160259987f));
        const float a2 = t1.angle(2);
        ASSERT(nnm::approx_equal(a2, 1.3916657175f));
        const float a3 = t3.angle(0);
        ASSERT(nnm::approx_equal(a3, 1.3916657175f));
        const float a4 = t3.angle(1);
        ASSERT(nnm::approx_equal(a4, 0.4160259987f));
        const float a5 = t3.angle(2);
        ASSERT(nnm::approx_equal(a5, 1.3339009374f));
    }

    test_section("angle_bisector");
    {
        const nnm::Line3f l1 = t1.angle_bisector(0);
        ASSERT(l1.approx_equal({ { 1.0f, -2.0f, 3.0f }, { 0.300677031f, 0.689402819f, -0.659027338f } }));
        const nnm::Line3f l2 = t1.angle_bisector(1);
        ASSERT(l2.approx_equal({ { -2.0f, 3.0f, -4.0f }, { 0.508951068f, -0.450794995f, 0.733316183f } }));
        const nnm::Line3f l3 = t1.angle_bisector(2);
        ASSERT(l3.approx_equal({ { 4.0f, 0.0f, 2.0f }, { -0.956620216f, -0.131064415f, -0.260192215f } }));
        const nnm::Line3f l4 = t3.angle_bisector(0);
        ASSERT(l4.approx_equal({ { 4.0f, 0.0f, 2.0f }, { -0.956620216f, -0.131064415f, -0.260192215f } }));
        const nnm::Line3f l5 = t3.angle_bisector(1);
        ASSERT(l5.approx_equal({ { -2.0f, 3.0f, -4.0f }, { 0.508951068f, -0.450794995f, 0.733316183f } }));
        const nnm::Line3f l6 = t3.angle_bisector(2);
        ASSERT(l6.approx_equal({ { 1.0f, -2.0f, 3.0f }, { 0.300677031f, 0.689402819f, -0.659027338f } }));
    }

    test_section("altitude");
    {
        const std::optional<nnm::Segment3f> a1 = t1.altitude(0);
        ASSERT(a1.has_value() && a1->approx_equal({ { 1.0f, -2.0f, 3.0f }, { 3.55555534f, 0.22222209f, 1.5555557f } }));
        const std::optional<nnm::Segment3f> a2 = t1.altitude(1);
        ASSERT(
            a2.has_value()
            && a2->approx_equal({ { -2.0f, 3.0f, -4.0f }, { 2.71428585f, -0.857142687f, 2.42857122f } }));
        const std::optional<nnm::Segment3f> a3 = t1.altitude(2);
        ASSERT(
            a3.has_value() && a3->approx_equal({ { 4.0f, 0.0f, 2.0f }, { 0.710843325f, -1.51807225f, 2.32530117f } }));
        const std::optional<nnm::Segment3f> a4 = t2.altitude(0);
        ASSERT_FALSE(a4.has_value());
        const std::optional<nnm::Segment3f> a5 = t2.altitude(1);
        ASSERT_FALSE(a5.has_value());
        const std::optional<nnm::Segment3f> a6 = t2.altitude(2);
        ASSERT_FALSE(a6.has_value());
    }

    test_section("lerp_point");
    {
        constexpr nnm::Vector3f p1 = t1.lerp_point({ 0.3f, 0.1f, 0.6f });
        constexpr nnm::Vector3f expected1 = t1.vertices[0] * 0.3f + t1.vertices[1] * 0.1f + t1.vertices[2] * 0.6f;
        ASSERT(p1.approx_equal(expected1));
        constexpr nnm::Vector3f p2 = t3.lerp_point({ 0.25f, 0.56f, 0.19f });
        constexpr nnm::Vector3f expected2 = t3.vertices[0] * 0.25f + t3.vertices[1] * 0.56f + t3.vertices[2] * 0.19f;
        ASSERT(p2.approx_equal(expected2));
    }

    test_section("barycentric_unchecked");
    {
        const nnm::Vector3f w1 = t1.barycentric_unchecked({ 2.5f, -0.3f, 1.7f });
        ASSERT(w1.approx_equal({ 0.3f, 0.1f, 0.6f }));
        const nnm::Vector3f w2 = t3.barycentric_unchecked({ 0.07f, 1.3f, -1.17f });
        ASSERT(w2.approx_equal({ 0.25f, 0.56f, 0.19f }));
    }

    test_section("barycentric");
    {
        const std::optional<nnm::Vector3f> w1 = t1.barycentric({ 2.5f, -0.3f, 1.7f });
        ASSERT(w1.has_value() && w1->approx_equal({ 0.3f, 0.1f, 0.6f }));
        const std::optional<nnm::Vector3f> w2 = t3.barycentric({ 0.07f, 1.3f, -1.17f });
        ASSERT(w2.has_value() && w2->approx_equal({ 0.25f, 0.56f, 0.19f }));
        const std::optional<nnm::Vector3f> w3 = t2.barycentric(nnm::Vector3f::zero());
        ASSERT_FALSE(w3.has_value());
    }

    test_section("contains");
    {
        const bool r1 = t1.contains({ 3.0f, 0.0f, 0.0f });
        ASSERT_FALSE(r1);
        const bool r2 = t1.contains({ 2.5f, -0.3f, 1.7f });
        ASSERT(r2);
        const bool r3 = t2.contains({ 0.5f, 0.0f, 0.0f });
        ASSERT(r3);
        const bool r4 = t2.contains({ 0.0f, 1.0f, 0.0f });
        ASSERT_FALSE(r4);
        const bool r5 = t1.contains({ 3.0f, 0.0f, 0.0f });
        ASSERT_FALSE(r5);
        const bool r6 = t1.contains({ 2.5f, -0.3f, 1.7f });
        ASSERT(r6);
        const bool r7 = t1.contains(t1.vertices[2]);
        ASSERT(r7);
        const bool r8 = t3.contains(t3.edge(1).midpoint());
        ASSERT(r8);
        const bool r9 = t2.contains({ 0.0f, -100.0f, 0.0f });
        ASSERT_FALSE(r9);
    }

    test_section("contains_projected");
    {
        const bool r1 = t1.contains_projected({ 3.0f, 0.0f, 0.0f });
        ASSERT_FALSE(r1);
        const bool r2 = t1.contains_projected({ 2.5f, -0.3f, 1.7f });
        ASSERT(r2);
        const bool r3 = t2.contains_projected({ 0.5f, 0.0f, 0.0f });
        ASSERT(r3);
        const bool r4 = t2.contains_projected({ 0.0f, 1.0f, 0.0f });
        ASSERT(r4);
        const bool r5 = t1.contains_projected({ 3.0f, 0.0f, 0.0f });
        ASSERT_FALSE(r5);
        const bool r6 = t1.contains_projected({ 2.5f, -0.3f, 1.7f });
        ASSERT(r6);
        const bool r7 = t1.contains_projected(t1.vertices[2]);
        ASSERT(r7);
        const bool r8 = t3.contains_projected(t3.edge(1).midpoint());
        ASSERT(r8);
        const bool r9 = t2.contains_projected({ 0.0f, -100.0f, 0.0f });
        ASSERT(r9);
    }

    test_section("collinear");
    {
        const bool r1 = t1.collinear();
        ASSERT_FALSE(r1);
        const bool r2 = t2.collinear();
        ASSERT(r2);
        const bool r3 = t3.collinear();
        ASSERT_FALSE(r3);
    }

    test_section("coplanar(const Vector3&)");
    {
        const bool r1 = t1.coplanar(nnm::Vector3f::zero());
        ASSERT_FALSE(r1);
        const bool r2 = t1.coplanar({ 2.5f, -0.3f, 1.7f });
        ASSERT(r2);
        const bool r3 = t1.coplanar({ 5.0009826255f, 0.9973796652f, 1.2891300792f });
        ASSERT(r3);
        const bool r4 = t2.coplanar({ 1.0f, -2.0f, 3.0f });
        ASSERT(r4);
        const bool r5 = t2.coplanar({ 100.0f, 0.0f, 0.0f });
        ASSERT(r5);
    }

    test_section("coplanar(const Line3&)");
    {
        const bool r1 = t1.coplanar(nnm::Line3f::axis_x());
        ASSERT_FALSE(r1);
        const bool r2 = t1.coplanar(nnm::Line3f::from_segment(t1.edge(0)));
        ASSERT(r2);
        const bool r3 = t1.coplanar(
            nnm::Line3f::from_points(
                { 5.6279295263f, 0.2174812388f, 2.4491340955f }, { 3.7355435221f, 2.8096960263f, -1.3244196634f }));
        ASSERT(r3);
        const bool r4 = t2.coplanar(nnm::Line3f::axis_x_offset(100.0f, -100.0f));
        ASSERT(r4);
        const bool r5 = t2.coplanar(nnm::Line3f::axis_y());
        ASSERT(r5);
        const bool r6 = t2.coplanar(nnm::Line3f::axis_y_offset(-100.0f, 100.0f));
        ASSERT_FALSE(r6);
    }

    test_section("coplanar(const Ray3&)");
    {
        const bool r1 = t1.coplanar(nnm::Ray3f { nnm::Vector3f::zero(), nnm::Vector3f::axis_x() });
        ASSERT_FALSE(r1);
        const bool r2 = t1.coplanar(nnm::Ray3f::from_point_to_point(t1.edge(0).start, t1.edge(0).end));
        ASSERT(r2);
        const bool r3 = t1.coplanar(
            nnm::Ray3f::from_point_to_point(
                { 5.6279295263f, 0.2174812388f, 2.4491340955f }, { 3.7355435221f, 2.8096960263f, -1.3244196634f }));
        ASSERT(r3);
        const bool r4 = t2.coplanar(nnm::Ray3f { { 0.0f, 100.0f, -100.0f }, nnm::Vector3f::axis_x() });
        ASSERT(r4);
        const bool r5 = t2.coplanar(nnm::Ray3f { nnm::Vector3f::zero(), nnm::Vector3f::axis_y() });
        ASSERT(r5);
        const bool r6 = t2.coplanar(nnm::Ray3f { { -100.0f, 0.0f, 100.0f }, nnm::Vector3f::axis_y() });
        ASSERT_FALSE(r6);
    }

    test_section("coplanar(const Segment3&)");
    {
        const bool r1 = t1.coplanar(nnm::Segment3f { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } });
        ASSERT_FALSE(r1);
        const bool r2 = t1.coplanar(nnm::Segment3f { t1.edge(0).start, t1.edge(0).end });
        ASSERT(r2);
        const bool r3 = t1.coplanar(
            nnm::Segment3f { { 5.6279295263f, 0.2174812388f, 2.4491340955f },
                             { 3.7355435221f, 2.8096960263f, -1.3244196634f } });
        ASSERT(r3);
        const bool r4 = t2.coplanar(nnm::Segment3f { { 0.0f, 100.0f, -100.0f }, { 1.0f, 100.0f, -100.0f } });
        ASSERT(r4);
        const bool r5 = t2.coplanar(nnm::Segment3f { { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } });
        ASSERT(r5);
        const bool r6 = t2.coplanar(nnm::Segment3f { { -100.0f, 0.0f, 100.0f }, { -100.0f, 1.0f, 100.0f } });
        ASSERT_FALSE(r6);
    }

    test_section("coplanar(const Plane&)");
    {
        const bool r1 = t1.coplanar(nnm::PlaneF::from_triangle_unchecked(t1));
        ASSERT(r1);
        const bool r2 = t1.coplanar(nnm::PlaneF::xy());
        ASSERT_FALSE(r2);
        const bool r3 = t2.coplanar(nnm::PlaneF::xy());
        ASSERT(r3);
        const bool r4 = t2.coplanar(nnm::PlaneF::xz());
        ASSERT(r4);
        const bool r5 = t2.coplanar(nnm::PlaneF::yz());
        ASSERT_FALSE(r5);
        const bool r6 = t2.coplanar(nnm::PlaneF::xz_offset(100.0f));
        ASSERT_FALSE(r6);
    }

    test_section("project");
    {
        const auto p1 = t1.project({ -1.5f, 3.5f, 3.0f });
        ASSERT(p1.approx_equal({ -0.2336065574f, 0.1229508197f, 0.0450819672f }))
        const auto p2 = t1.project({ -1.0f, 1.0f, 3.0f });
        ASSERT(p2.approx_equal({ 0.2409638554f, -0.734939759f, 1.2289156627f }));
        const auto p3 = t1.project({ 0.8632112627f, -3.9685633672f, -1.3474929463f });
        ASSERT(p3.approx_equal({ 0.2409638554f, -0.734939759f, 1.2289156627f }));
        const auto p4 = t2.project({ 0.5f, 100.0f, 0.0f });
        ASSERT(p4.approx_equal({ 0.5f, 0.0f, 0.0f }));
        const auto p5 = t2.project({ 100.0f, -100.0f, 0.0f });
        ASSERT(p5.approx_equal({ 1.0f, 0.0f, 0.0f }));
    }

    test_section("distance(const Vector3&)");
    {
        const auto d1 = t1.distance({ 0.0f, 3.0f, 3.0f });
        ASSERT(nnm::approx_equal(d1, 3.8930370798f));
        const auto d2 = t1.distance({ -3.0f, 4.0f, 3.0f });
        ASSERT(nnm::approx_equal(d2, 5.5449966593f));
        const auto d3 = t1.distance(t1.vertices[1]);
        ASSERT(nnm::approx_zero(d3));
        const auto d4 = t2.distance({ 0.5f, 0.0, 100.0f });
        ASSERT(nnm::approx_equal(d4, 100.0f));
        const auto d5 = t2.distance({ 100.0f, 0.0f, 0.0f });
        ASSERT(nnm::approx_equal(d5, 99.0f));
    }

    test_section("distance(const Line3&)");
    {
        const auto d1 = t1.distance(nnm::Line3f::axis_y());
        ASSERT(nnm::approx_zero(d1));
        const auto d2 = t1.distance(nnm::Line3f::axis_y_offset(-1.0f, 0.0f));
        ASSERT(nnm::approx_equal(d2, 0.656532168f));
        const auto d3 = t2.distance(nnm::Line3f::axis_x_offset(10.0f, 0.0f));
        ASSERT(nnm::approx_equal(d3, 10.0f));
        const auto d4 = t2.distance(nnm::Line3f::axis_z_offset(5.0f, 0.0f));
        ASSERT(nnm::approx_equal(d4, 4.0f));
    }

    test_section("distance(const Ray3&)");
    {
        const auto d1 = t1.distance(nnm::Ray3f({ -1.0f, 2.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d1, 1.5391076827f));
        const auto d2 = t1.distance(nnm::Ray3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }));
        ASSERT(nnm::approx_zero(d2));
        const auto d3 = t1.distance(nnm::Ray3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d3, 0.5432144763f));
    }

    test_section("distance(const Segment3&)");
    {
        const auto d1 = t1.distance(nnm::Segment3f({ -1.0f, 2.0f, 0.0f }, { -1.0f, 3.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d1, 1.5391076827f));
        const auto d2 = t1.distance(nnm::Segment3f({ -1.0f, 3.0f, 0.0f }, { -1.0f, 2.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d2, 1.5391076827f));
        const auto d3 = t1.distance(nnm::Segment3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }));
        ASSERT(nnm::approx_zero(d3));
        const auto d4 = t1.distance(nnm::Segment3f({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        ASSERT(nnm::approx_zero(d4));
        const auto d5 = t1.distance(nnm::Segment3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d5, 0.5432144763f));
        const auto d6 = t1.distance(nnm::Segment3f({ 0.0f, 10.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d6, 0.5432144763f));
    }

    test_section("distance(const Plane&)");
    {
        constexpr auto d1 = t1.distance(nnm::PlaneF::xy());
        ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = t1.distance(nnm::PlaneF::xy_offset(5.0f));
        ASSERT(nnm::approx_equal(d2, 2.0f));
        constexpr auto d3 = t1.distance(nnm::PlaneF::yz_offset(5.0f));
        ASSERT(nnm::approx_equal(d3, 1.0f));
    }

    test_section("distance(const Triangle3&)");
    {
        const auto d1 = t1.distance(nnm::Triangle3f({ 0.0f, -2.0f, 0.0f }, { 0.0, 3.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_zero(d1));
        const auto d2
            = t1.distance(nnm::Triangle3f({ 0.0f, -2.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { -2.0f, 2.0f, 0.0f }));
        ASSERT(nnm::approx_equal(d2, 0.701334476f));
        const auto d3 = t1.distance(t1.translate(nnm::PlaneF::from_triangle_unchecked(t1).normal * 3.0f));
        ASSERT(nnm::approx_equal(d3, 3.0f));
    }

    test_section("intersects(const Line3&)");
    {
        const auto r1 = t1.intersects(nnm::Line3f::from_segment(t1.edge(0)));
        ASSERT(r1);
        const auto r2 = t1.intersects(nnm::Line3f::axis_x());
        ASSERT_FALSE(r2);
        const auto r3 = t1.intersects(nnm::Line3f::axis_y());
        ASSERT(r3);
        const auto r4 = t2.intersects(nnm::Line3f::axis_y());
        ASSERT(r4);
        const auto r5 = t2.intersects(nnm::Line3f::axis_z_offset(-1.0f, 1.0f));
        ASSERT_FALSE(r5);
    }

    test_section("intersection(const Line3&)");
    {
        const auto i1 = t1.intersection(nnm::Line3f::from_segment(t1.edge(0)));
        ASSERT_FALSE(i1.has_value());
        const auto i2 = t1.intersection(nnm::Line3f::axis_x());
        ASSERT_FALSE(i2.has_value());
        const auto i3 = t1.intersection(nnm::Line3f::axis_y());
        ASSERT(i3.has_value() && i3->approx_equal({ 0.0f, 0.25f, 0.0f }));
        const auto r4 = t2.intersection(nnm::Line3f::axis_y());
        ASSERT(r4.has_value() && r4->approx_equal({ 0.0f, 0.0f, 0.0f }));
        const auto r5 = t2.intersection(nnm::Line3f::axis_z_offset(-1.0f, 1.0f));
        ASSERT_FALSE(r5.has_value());
    }

    test_section("intersects(const Ray3&)");
    {
        const auto r1 = t1.intersects(nnm::Ray3f::from_point_to_point(t1.edge(0).start, t1.edge(1).end));
        ASSERT(r1);
        const auto r2 = t1.intersects(nnm::Ray3f({ -2.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r2);
        const auto r3 = t1.intersects(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, nnm::Vector3f::axis_y()));
        ASSERT_FALSE(r3);
        const auto r4 = t1.intersects(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, -nnm::Vector3f::axis_y()));
        ASSERT(r4);
        const auto r5 = t2.intersects(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, nnm::Vector3f::axis_y()));
        ASSERT_FALSE(r5)
        const auto r6 = t2.intersects(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, -nnm::Vector3f::axis_y()));
        ASSERT(r6)
        const auto r7 = t2.intersects(nnm::Ray3f({ -1.0f, 1.0f, 1.0f }, -nnm::Vector3f::axis_z()));
        ASSERT_FALSE(r7);
    }

    test_section("intersection(const Ray3&)");
    {
        const auto i1 = t1.intersection(nnm::Ray3f::from_point_to_point(t1.edge(0).start, t1.edge(1).end));
        ASSERT_FALSE(i1.has_value());
        const auto i2 = t1.intersection(nnm::Ray3f({ -2.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        ASSERT_FALSE(i2.has_value());
        const auto i3 = t1.intersection(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, nnm::Vector3f::axis_y()));
        ASSERT_FALSE(i3.has_value());
        const auto i4 = t1.intersection(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, -nnm::Vector3f::axis_y()));
        ASSERT(i4.has_value() && i4->approx_equal({ 0.0f, 0.25f, 0.0f }));
        const auto i5 = t2.intersection(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, nnm::Vector3f::axis_y()));
        ASSERT_FALSE(i5.has_value());
        const auto i6 = t2.intersection(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, -nnm::Vector3f::axis_y()));
        ASSERT(i6.has_value() && i6->approx_zero());
        const auto i7 = t2.intersection(nnm::Ray3f({ -1.0f, 1.0f, 1.0f }, -nnm::Vector3f::axis_z()));
        ASSERT_FALSE(i7.has_value());
    }

    test_section("intersects(const Segment3&)");
    {
        const auto r1 = t1.intersects(t1.edge(0));
        ASSERT(r1);
        const auto r2 = t1.intersects(nnm::Segment3f({ -2.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(r2);
        const auto r3 = t1.intersects(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }));
        ASSERT_FALSE(r3);
        const auto r4 = t1.intersects(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        ASSERT(r4);
        const auto r5 = t1.intersects(nnm::Segment3f({ 0.0f, -2.0f, 0.0f }, { 0.0f, -10.0f, 0.0f }));
        ASSERT_FALSE(r5);
        const auto r6 = t2.intersects(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }));
        ASSERT_FALSE(r6);
        const auto r7 = t2.intersects(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        ASSERT(r7);
        const auto r8 = t2.intersects(nnm::Segment3f({ -1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, -10.0f }));
        ASSERT_FALSE(r8);
    }

    test_section("intersection(const Segment3&)");
    {
        const auto i1 = t1.intersection(t1.edge(0));
        ASSERT_FALSE(i1.has_value());
        const auto i2 = t1.intersection(nnm::Segment3f({ -2.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(i2.has_value());
        const auto i3 = t1.intersection(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }));
        ASSERT_FALSE(i3.has_value());
        const auto i4 = t1.intersection(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        ASSERT(i4.has_value() && i4->approx_equal({ 0.0f, 0.25f, 0.0f }));
        const auto i5 = t1.intersection(nnm::Segment3f({ 0.0f, -2.0f, 0.0f }, { 0.0f, -10.0f, 0.0f }));
        ASSERT_FALSE(i5.has_value());
        const auto i6 = t2.intersection(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }));
        ASSERT_FALSE(i6.has_value());
        const auto i7 = t2.intersection(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        ASSERT(i7.has_value() && i7->approx_zero());
        const auto i8 = t2.intersection(nnm::Segment3f({ -1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, -10.0f }));
        ASSERT_FALSE(i8.has_value());
    }

    test_section("intersects(const Plane&)");
    {
        constexpr auto p1 = nnm::PlaneF({ 1.0f, -2.0f, 3.0f }, { 0.27160725f, -0.724286019f, -0.633750259f });
        constexpr auto r1 = t1.intersects(p1);
        ASSERT(r1);
        constexpr auto r2 = t1.intersects(p1.translate(p1.normal * 3.0f));
        ASSERT_FALSE(r2);
        constexpr auto r3 = t1.intersects(nnm::PlaneF::xy());
        ASSERT(r3);
        constexpr auto r4 = t1.intersects(nnm::PlaneF::yz_offset(4.0f));
        ASSERT(r4);
        constexpr auto r5 = t2.intersects(nnm::PlaneF::yz());
        ASSERT(r5);
        constexpr auto r6 = t2.intersects(nnm::PlaneF::xy_offset(1.0f));
        ASSERT_FALSE(r6);
    }

    test_section("intersection(const Plane&)");
    {
        constexpr auto p1 = nnm::PlaneF({ 1.0f, -2.0f, 3.0f }, { 0.27160725f, -0.724286019f, -0.633750259f });
        constexpr auto i1 = t1.intersection(p1);
        ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = t1.intersection(p1.translate(p1.normal * 3.0f));
        ASSERT_FALSE(i2);
        constexpr auto i3 = t1.intersection(nnm::PlaneF::xy());
        ASSERT(i3.has_value() && i3->coincident({ { 2.0f, 1.0f, 0.0f }, { -0.2857142857f, 0.1428571429f, 0.0f } }));
        constexpr auto i4 = t1.intersection(nnm::PlaneF::yz_offset(4.0f));
        ASSERT(i4.has_value() && i4->coincident({ { 4.0f, 0.0f, 2.0f }, { 4.0f, 0.0f, 2.0f } }));
        constexpr auto i5 = t2.intersection(nnm::PlaneF::yz());
        ASSERT(i5.has_value() && i5->coincident({ nnm::Vector3f::zero(), nnm::Vector3f::zero() }))
        constexpr auto i6 = t2.intersection(nnm::PlaneF::xy_offset(1.0f));
        ASSERT_FALSE(i6.has_value());
    }

    test_section("intersects(const Triangle3&)");
    {
        const auto r1 = t1.intersects(t1);
        ASSERT(r1);
        const auto r2
            = t1.intersects(nnm::Triangle3f({ 0.0f, -2.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { -2.0f, 2.0f, 0.0f }));
        ASSERT_FALSE(r2);
        const auto r3
            = t1.intersects(nnm::Triangle3f({ 2.0f, 2.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        ASSERT(r3);
        const auto r4
            = t1.intersects(nnm::Triangle3f({ -3.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }, { 3.0f, 2.0f, 0.0f }));
        ASSERT(r4);
        const auto r5
            = t1.intersects(nnm::Triangle3f({ 1.0f, 3.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }));
        ASSERT(r5);
    }

    test_section("intersection(const Triangle3&)");
    {
        const auto i1 = t1.intersection(t1);
        ASSERT_FALSE(i1.has_value());
        const auto i2
            = t1.intersection(nnm::Triangle3f({ 0.0f, -2.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { -2.0f, 2.0f, 0.0f }));
        ASSERT_FALSE(i2.has_value());
        const auto i3
            = t1.intersection(nnm::Triangle3f({ 2.0f, 2.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        ASSERT(
            i3.has_value()
            && i3->coincident({ { -0.2857142857f, 0.1428571429f, 0.0f }, { 1.3846153846f, 0.7692307692f, 0.0f } }));
        const auto i4
            = t1.intersection(nnm::Triangle3f({ -3.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }, { 3.0f, 2.0f, 0.0f }));
        ASSERT(i4.has_value() && i4->coincident({ { 2.0f, 1.0f, 0.0f }, { -0.2857142857f, 0.1428571429f, 0.0f } }));
        const auto i5
            = t1.intersection(nnm::Triangle3f({ 1.0f, 3.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }));
        ASSERT(
            i5.has_value()
            && i5->coincident({ { 1.7037037037f, 0.8888888889f, 0.0f }, { 0.4864864865f, 0.4324324324f, 0.0f } }));
    }

    test_section("coincident");
    {
        constexpr auto r1 = t1.coincident(t1);
        ASSERT(r1);
        constexpr auto r2 = t1.coincident(t2);
        ASSERT_FALSE(r2);
        constexpr auto r3 = t2.coincident(t1);
        ASSERT_FALSE(r3);
        constexpr auto r4 = t2.coincident(t2);
        ASSERT(r4);
        constexpr auto r5 = t1.coincident({ { -2.0f, 3.0f, -4.0f }, { 1.0f, -2.0f, 3.0f }, { 4.0f, 0.0f, 2.0f } });
        ASSERT(r5);
        constexpr auto r6 = t1.coincident({ { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f }, { 1.0f, -2.0f, 3.0f } });
        ASSERT(r6);
        constexpr auto r7 = t1.coincident({ { -2.0f, 3.0f, -4.0f }, { 4.0f, 1.0f, 2.0f }, { 1.0f, -2.0f, 3.0f } });
        ASSERT_FALSE(r7);
        constexpr auto r8 = t1.coincident({ { -2.0f, 3.0f, -4.1f }, { 1.0f, -2.0f, 3.0f }, { 4.0f, 0.0f, 2.0f } });
        ASSERT_FALSE(r8);
    }

    test_section("transform_at(const Vector3&, const Basis3&)");
    {
        constexpr nnm::Vector3f origin { 2.0f, -10.0f, 0.5f };
        constexpr nnm::Basis3f basis { { { 1.0f, -2.0f, 3.0f }, { 4.0f, 1.5f, 0.0f }, { -2.0f, 0.2f, 10.0f } } };
        constexpr auto r1 = t1.transform_at(origin, basis);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].transform_at(origin, basis),
              t1.vertices[1].transform_at(origin, basis),
              t1.vertices[2].transform_at(origin, basis) }));
    }

    test_section("transform(const Basis3&)");
    {
        constexpr nnm::Basis3f basis { { { 1.0f, -2.0f, 3.0f }, { 4.0f, 1.5f, 0.0f }, { -2.0f, 0.2f, 10.0f } } };
        constexpr auto r1 = t1.transform(basis);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].transform(basis), t1.vertices[1].transform(basis), t1.vertices[2].transform(basis) }));
    }

    test_section("transform_at(const Vector3&, const Transform3&");
    {
        constexpr nnm::Vector3f origin { 2.0f, -10.0f, 0.5f };
        constexpr nnm::Transform3f transform { { { 1.0f, -2.0f, 3.0f, -0.2f },
                                                 { 4.0f, 1.5f, 0.0f, 5.0f },
                                                 { -2.0f, 0.2f, 10.0f, 1.0f },
                                                 { 0.0f, 0.0f, 0.0f, 1.0f } } };
        constexpr auto r1 = t1.transform_at(origin, transform);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].transform_at(origin, transform),
              t1.vertices[1].transform_at(origin, transform),
              t1.vertices[2].transform_at(origin, transform) }));
    }

    test_section("transform(const Transform3&)");
    {
        constexpr nnm::Transform3f transform { { { 1.0f, -2.0f, 3.0f, -0.2f },
                                                 { 4.0f, 1.5f, 0.0f, 5.0f },
                                                 { -2.0f, 0.2f, 10.0f, 1.0f },
                                                 { 0.0f, 0.0f, 0.0f, 1.0f } } };
        constexpr auto r1 = t1.transform(transform);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].transform(transform),
              t1.vertices[1].transform(transform),
              t1.vertices[2].transform(transform) }));
    }

    test_section("translate");
    {
        constexpr auto r1 = t1.translate({ 1.0f, -2.0f, 3.0f });
        ASSERT(r1.approx_equal(
            { t1.vertices[0].translate({ 1.0f, -2.0f, 3.0f }),
              t1.vertices[1].translate({ 1.0f, -2.0f, 3.0f }),
              t1.vertices[2].translate({ 1.0f, -2.0f, 3.0f }) }));
    }

    test_section("scale_at");
    {
        constexpr nnm::Vector3f origin { 2.0f, -10.0f, 0.5f };
        constexpr auto r1 = t1.scale_at(origin, { 1.0f, -2.0f, 3.0f });
        ASSERT(r1.approx_equal(
            { t1.vertices[0].scale_at(origin, { 1.0f, -2.0f, 3.0f }),
              t1.vertices[1].scale_at(origin, { 1.0f, -2.0f, 3.0f }),
              t1.vertices[2].scale_at(origin, { 1.0f, -2.0f, 3.0f }) }));
    }

    test_section("scale");
    {
        constexpr auto r1 = t1.scale({ 2.0f, -10.0f, 0.5f });
        ASSERT(r1.approx_equal(
            { t1.vertices[0].scale({ 2.0f, -10.0f, 0.5f }),
              t1.vertices[1].scale({ 2.0f, -10.0f, 0.5f }),
              t1.vertices[2].scale({ 2.0f, -10.0f, 0.5f }) }));
    }

    test_section("rotate_axis_angle_at");
    {
        constexpr nnm::Vector3f origin { 2.0f, -10.0f, 0.5f };
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = 2.0f * nnm::pi<float>() / 3.0f;
        const auto r1 = t1.rotate_axis_angle_at(origin, axis, angle);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].rotate_axis_angle_at(origin, axis, angle),
              t1.vertices[1].rotate_axis_angle_at(origin, axis, angle),
              t1.vertices[2].rotate_axis_angle_at(origin, axis, angle) }));
    }

    test_section("rotate_axis_angle");
    {
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = 2.0f * nnm::pi<float>() / 3.0f;
        const auto r1 = t1.rotate_axis_angle(axis, angle);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].rotate_axis_angle(axis, angle),
              t1.vertices[1].rotate_axis_angle(axis, angle),
              t1.vertices[2].rotate_axis_angle(axis, angle) }));
    }

    test_section("rotate_quaternion_at");
    {
        constexpr nnm::Vector3f origin { 2.0f, -10.0f, 0.5f };
        constexpr nnm::QuaternionF quat { 0.0f, 0.866025447f, 0.0f, 0.5f };
        constexpr auto r1 = t1.rotate_quaternion_at(origin, quat);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].rotate_quaternion_at(origin, quat),
              t1.vertices[1].rotate_quaternion_at(origin, quat),
              t1.vertices[2].rotate_quaternion_at(origin, quat) }));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::QuaternionF quat { 0.0f, 0.866025447f, 0.0f, 0.5f };
        constexpr auto r1 = t1.rotate_quaternion(quat);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].rotate_quaternion(quat),
              t1.vertices[1].rotate_quaternion(quat),
              t1.vertices[2].rotate_quaternion(quat) }));
    }

    test_section("shear_x_at");
    {
        constexpr nnm::Vector3f origin { 2.0f, -10.0f, 0.5f };
        constexpr auto r1 = t1.shear_x_at(origin, -1.3f, 0.2f);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_x_at(origin, -1.3f, 0.2f),
              t1.vertices[1].shear_x_at(origin, -1.3f, 0.2f),
              t1.vertices[2].shear_x_at(origin, -1.3f, 0.2f) }));
    }

    test_section("shear_x");
    {
        constexpr auto r1 = t1.shear_x(-1.3f, 0.2f);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_x(-1.3f, 0.2f),
              t1.vertices[1].shear_x(-1.3f, 0.2f),
              t1.vertices[2].shear_x(-1.3f, 0.2f) }));
    }

    test_section("shear_y_at");
    {
        constexpr nnm::Vector3f origin { 2.0f, -10.0f, 0.5f };
        constexpr auto r1 = t1.shear_y_at(origin, -1.3f, 0.2f);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_y_at(origin, -1.3f, 0.2f),
              t1.vertices[1].shear_y_at(origin, -1.3f, 0.2f),
              t1.vertices[2].shear_y_at(origin, -1.3f, 0.2f) }));
    }

    test_section("shear_y");
    {
        constexpr auto r1 = t1.shear_y(-1.3f, 0.2f);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_y(-1.3f, 0.2f),
              t1.vertices[1].shear_y(-1.3f, 0.2f),
              t1.vertices[2].shear_y(-1.3f, 0.2f) }));
    }

    test_section("shear_z_at");
    {
        constexpr nnm::Vector3f origin { 2.0f, -10.0f, 0.5f };
        constexpr auto r1 = t1.shear_z_at(origin, -1.3f, 0.2f);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_z_at(origin, -1.3f, 0.2f),
              t1.vertices[1].shear_z_at(origin, -1.3f, 0.2f),
              t1.vertices[2].shear_z_at(origin, -1.3f, 0.2f) }));
    }

    test_section("shear_z");
    {
        constexpr auto r1 = t1.shear_z(-1.3f, 0.2f);
        ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_z(-1.3f, 0.2f),
              t1.vertices[1].shear_z(-1.3f, 0.2f),
              t1.vertices[2].shear_z(-1.3f, 0.2f) }));
    }

    test_section("approx_equal");
    {
        constexpr auto r1 = t1.approx_equal(t1);
        ASSERT(r1);
        constexpr auto r2 = t1.approx_equal(t2);
        ASSERT_FALSE(r2);
        constexpr auto r3 = t2.approx_equal(t1);
        ASSERT_FALSE(r3);
        constexpr auto r4 = t2.approx_equal(t2);
        ASSERT(r4);
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r1 = t1 == t1;
        ASSERT(r1);
        constexpr auto r2 = t1 == t2;
        ASSERT_FALSE(r2);
        constexpr auto r3 = t2 == t1;
        ASSERT_FALSE(r3);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r4 = t2 == t2;
        ASSERT(r4);
    }

    test_section("operator!=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r1 = t1 != t1;
        ASSERT_FALSE(r1);
        constexpr auto r2 = t1 != t2;
        ASSERT(r2);
        constexpr auto r3 = t2 != t1;
        ASSERT(r3);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r4 = t2 != t2;
        ASSERT_FALSE(r4);
    }

    test_section("operator<");
    {
        constexpr auto r1 = t1 < t2;
        ASSERT_FALSE(r1);
        constexpr auto r2 = t2 < t1;
        ASSERT(r2);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r3 = t1 < t1;
        ASSERT_FALSE(r3);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r4 = t2 < t2;
        ASSERT_FALSE(r4);
    }
}

void sphere_tests()
{
    test_case("sphere");

    test_section("Sphere()");
    {
        constexpr nnm::SphereF s1 {};
        ASSERT(s1.center.approx_zero());
        ASSERT(nnm::approx_equal(s1.radius, 1.0f));
    }

    test_section("Sphere(const Vector3&, Real)");
    {
        constexpr nnm::SphereF s1 { { 1.0f, -2.0f, 3.0f }, 1.5f };
        ASSERT(s1.center.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(nnm::approx_equal(s1.radius, 1.5f));
    }

    test_section("Sphere(const Sphere<Other>&)");
    {
        constexpr nnm::SphereD s1 { { 1.0, -2.0, 3.0 }, 1.5 };
        constexpr nnm::SphereF s2 { s1 };
        ASSERT(s2.center.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(nnm::approx_equal(s2.radius, 1.5f));
    }

    test_section("from_center_surface_point");
    {
        const auto s1 = nnm::SphereF::from_center_surface_point(
            { 1.0f, -2.0f, 3.0f }, { 1.4199396004f, -2.6830724743f, 4.2676997779f });
        ASSERT(s1.center.approx_equal({ 1.0f, -2.0f, 3.0f }));
        ASSERT(nnm::approx_equal(s1.radius, 1.5f));
    }

    constexpr nnm::SphereF s1 { { 1.0f, -2.0f, 3.0f }, 1.5f };
    constexpr nnm::SphereF s_degen { { 0.0f, 0.0f, 0.0f }, 0.0f };

    test_section("surface_area");
    {
        constexpr auto r1 = s1.surface_area();
        ASSERT(nnm::approx_equal(r1, 28.2743338823f));
        constexpr auto r2 = s_degen.surface_area();
        ASSERT(nnm::approx_zero(r2));
    }

    test_section("volume");
    {
        constexpr auto r1 = s1.volume();
        ASSERT(nnm::approx_equal(r1, 14.1371669412f));
        constexpr auto r2 = s_degen.volume();
        ASSERT(nnm::approx_zero(r2));
    }

    test_section("diameter");
    {
        constexpr auto r1 = s1.diameter();
        ASSERT(nnm::approx_equal(r1, 3.0f));
        constexpr auto r2 = s_degen.diameter();
        ASSERT(nnm::approx_zero(r2));
    }

    test_section("contains");
    {
        constexpr auto r1 = s1.contains({ 1.4199396004f, -2.6830724743f, 4.2676997779f });
        ASSERT(r1);
        constexpr auto r2 = s1.contains(s1.center);
        ASSERT(r2);
        constexpr auto r3 = s1.contains({ 0.75f, -2.1f, 3.25f });
        ASSERT(r3);
        constexpr auto r4 = s1.contains(nnm::Vector3f::zero());
        ASSERT_FALSE(r4);
        constexpr auto r5 = s_degen.contains({ 1.0f, 1.0f, 1.0f });
        ASSERT_FALSE(r5);
        constexpr auto r6 = s_degen.contains(nnm::Vector3f::zero());
        ASSERT(r6);
    }

    test_section("signed_distance");
    {
        const auto r1 = s1.signed_distance(s1.center);
        ASSERT(nnm::approx_equal(r1, -s1.radius));
        const auto r2 = s1.signed_distance({ 1.4199396004f, -2.6830724743f, 4.2676997779f });
        ASSERT(nnm::approx_zero(r2));
        const auto r3 = s1.signed_distance(nnm::Vector3f::zero());
        ASSERT(nnm::approx_equal(r3, 2.2416573868f));
        const auto r4 = s_degen.signed_distance({ 1.0f, 1.0f, 1.0f });
        ASSERT(nnm::approx_equal(r4, 1.7320508076f));
        const auto r5 = s_degen.signed_distance(nnm::Vector3f::zero());
        ASSERT(nnm::approx_zero(r5));
    }

    test_section("distance(const Vector3&)");
    {
        const auto r1 = s1.distance(s1.center);
        ASSERT(nnm::approx_zero(r1));
        const auto r2 = s1.distance({ 1.4199396004f, -2.6830724743f, 4.2676997779f });
        ASSERT(nnm::approx_zero(r2));
        const auto r3 = s1.distance(nnm::Vector3f::zero());
        ASSERT(nnm::approx_equal(r3, 2.2416573868f));
        const auto r4 = s_degen.distance({ 1.0f, 1.0f, 1.0f });
        ASSERT(nnm::approx_equal(r4, 1.7320508076f));
        const auto r5 = s_degen.distance(nnm::Vector3f::zero());
        ASSERT(nnm::approx_zero(r5));
    }

    test_section("distance(const Line3&)");
    {
        const auto r1 = s1.distance(nnm::Line3f::axis_x_offset(-2.0f, 3.0f));
        ASSERT(nnm::approx_zero(r1));
        const auto r2 = s1.distance(nnm::Line3f::axis_x());
        ASSERT(nnm::approx_equal(r2, 2.1055512755f));
        const auto r3 = s1.distance(nnm::Line3f::axis_y_offset(2.5f, 3.0f));
        ASSERT(nnm::approx_zero(r3));
        const auto r4 = s_degen.distance(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        ASSERT(nnm::approx_equal(r4, 1.4142135624f));
        const auto r5 = s_degen.distance(nnm::Line3f::axis_z());
        ASSERT(nnm::approx_zero(r5));
    }

    test_section("distance(const Ray3&)");
    {
        const auto r1 = s1.distance(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x()));
        ASSERT(nnm::approx_zero(r1));
        const auto r2 = s1.distance(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, -nnm::Vector3f::axis_x()));
        ASSERT(nnm::approx_equal(r2, 1.5f));
        const auto r3 = s1.distance(nnm::Ray3f(nnm::Vector3f::zero(), nnm::Vector3f::axis_x()));
        ASSERT(nnm::approx_equal(r3, 2.1055512755f));
        const auto r4 = s1.distance(nnm::Ray3f(nnm::Vector3f::zero(), -nnm::Vector3f::axis_x()));
        ASSERT(nnm::approx_equal(r4, 2.2416573868f));
        const auto r5 = s_degen.distance(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        ASSERT(nnm::approx_equal(r5, 1.0f));
        const auto r6 = s_degen.distance(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, -nnm::Vector3f::axis_x()));
        ASSERT(nnm::approx_zero(r6));
    }

    test_section("distance(const Segment3&)");
    {
        const auto r1 = s1.distance(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { 10.0f, -2.0f, 3.0f }));
        ASSERT(nnm::approx_zero(r1));
        const auto r2 = s1.distance(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { -10.0f, -2.0f, 3.0f }));
        ASSERT(nnm::approx_equal(r2, 1.5f));
        const auto r3 = s1.distance(nnm::Segment3f({ 10.0f, -2.0f, 3.0f }, { 20.0f, -2.0f, 3.0f }));
        ASSERT(nnm::approx_equal(r3, 7.5f));
        const auto r4 = s1.distance(nnm::Segment3f(nnm::Vector3f::zero(), { 10.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(r4, 2.1055512755f));
        const auto r5 = s1.distance(nnm::Segment3f(nnm::Vector3f::zero(), { -10.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(r5, 2.2416573868f));
        const auto r6 = s_degen.distance(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(r6, 1.0f));
        const auto r7 = s_degen.distance(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_zero(r7));
    }

    test_section("distance(const Plane&)");
    {
        constexpr auto r1 = s1.distance(nnm::PlaneF::xy());
        ASSERT(nnm::approx_equal(r1, 1.5f));
        constexpr auto r2 = s1.distance(nnm::PlaneF::yz_offset(-0.5f));
        ASSERT(nnm::approx_zero(r2));
        constexpr auto r3 = s1.distance(nnm::PlaneF::xz_offset(-1.5f));
        ASSERT(nnm::approx_zero(r3));
        constexpr auto r4 = s_degen.distance(nnm::PlaneF::xy_offset(2.7f));
        ASSERT(nnm::approx_equal(r4, 2.7f));
        constexpr auto r5 = s_degen.distance(nnm::PlaneF::xz());
        ASSERT(nnm::approx_zero(r5));
    }

    test_section("distance(const Triangle3&)");
    {
        const auto r1 = s1.distance(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        ASSERT(nnm::approx_equal(r1, 1.5822070015f));
        const auto r2 = s1.distance(nnm::Triangle3f({ 0.0f, -5.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 4.0f }));
        ASSERT(nnm::approx_zero(r2));
        const auto r3
            = s1.distance(nnm::Triangle3f({ 0.0f, -5.0f, 0.0f }, { 0.0f, -2.0f, 4.0f }, { 0.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_zero(r3));
        const auto r4
            = s1.distance(nnm::Triangle3f({ -0.5f, -5.0f, 0.0f }, { -0.5f, -2.0f, 4.0f }, { -0.5f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_zero(r4));
        const auto r5 = s1.distance(nnm::Triangle3f({ 0.0, 0.0, 6.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, -5.0f, 3.0f }));
        ASSERT(nnm::approx_zero(r5));
        const auto r6 = s1.distance(
            nnm::Triangle3f(
                { 1.4913057739f, -1.194313814f, 3.7420624503f },
                { 1.2924884416f, -2.7911804169f, 3.0f },
                { 1.0f, -1.5f, 3.0f }));
        ASSERT(nnm::approx_zero(r6));
        const auto r7
            = s1.distance(nnm::Triangle3f({ -2.0f, -5.0f, 0.0f }, { -2.0f, -2.0f, 4.0f }, { -2.0f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_equal(r7, 1.5f));
    }

    test_section("distance(const Sphere&)");
    {
        const auto r1 = s1.distance(s1);
        ASSERT(nnm::approx_zero(r1));
        const auto r2 = s1.distance(nnm::SphereF(nnm::Vector3f::zero(), 1.0f));
        ASSERT(nnm::approx_equal(r2, 1.2416573868f));
        const auto r3 = s1.distance(s1.translate({ 1.5f, 0.0f, 0.0f }));
        ASSERT(nnm::approx_zero(r3));
    }

    test_section("point_at");
    {
        constexpr auto r1 = s1.point_at(nnm::Vector3f::axis_x());
        ASSERT(r1.approx_equal({ 2.5f, -2.0f, 3.0f }))
    }

    test_section("normal_at");
    {
        constexpr auto r1 = s1.normal_at(nnm::Vector3f::axis_x());
        ASSERT(r1.approx_equal(nnm::Vector3f::axis_x()));
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto r1 = s1.intersects(nnm::Line3f::axis_x_offset(-2.0f, 3.0f));
        ASSERT(r1);
        constexpr auto r2 = s1.intersects(nnm::Line3f::axis_x());
        ASSERT_FALSE(r2);
        constexpr auto r3 = s1.intersects(nnm::Line3f::axis_y_offset(2.5f, 3.0f));
        ASSERT(r3);
        constexpr auto r4 = s_degen.intersects(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        ASSERT_FALSE(r4);
        constexpr auto r5 = s_degen.intersects(nnm::Line3f::axis_z());
        ASSERT(r5);
    }

    test_section("surface_intersections(const Line3&)");
    {
        const auto r1 = s1.surface_intersections(nnm::Line3f::axis_x_offset(-2.0f, 3.0f));
        ASSERT(r1.approx_equal({ { -0.5f, -2.0f, 3.0f }, { 2.5f, -2.0f, 3.0f } }));
        const auto r2 = s1.surface_intersections(nnm::Line3f::axis_x());
        ASSERT(r2.empty());
        const auto r3 = s1.surface_intersections(nnm::Line3f::axis_y_offset(2.5f, 3.0f));
        ASSERT(r3.approx_equal({ { 2.5f, -2.0f, 3.0f } }));
        const auto r4 = s_degen.surface_intersections(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        ASSERT(r4.empty());
        const auto r5 = s_degen.surface_intersections(nnm::Line3f::axis_z());
        ASSERT(r5.approx_equal({ nnm::Vector3f::zero() }));
    }

    test_section("intersects(const Ray3&)");
    {
        const auto r1 = s1.intersects(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x()));
        ASSERT(r1);
        const auto r2 = s1.intersects(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, -nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r2);
        const auto r3 = s1.intersects(nnm::Ray3f(nnm::Vector3f::zero(), nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r3);
        const auto r4 = s1.intersects(nnm::Ray3f(nnm::Vector3f::zero(), -nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r4);
        const auto r5 = s_degen.intersects(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r5);
        const auto r6 = s_degen.intersects(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, -nnm::Vector3f::axis_x()));
        ASSERT(r6);
        const auto r7 = s1.intersects(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, nnm::Vector3f::axis_x()));
        ASSERT(r7);
        const auto r8 = s1.intersects(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, -nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r8);
    }

    test_section("surface_intersections(const Ray3&)");
    {
        const auto r1 = s1.surface_intersections(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x()));
        ASSERT(r1.approx_equal({ { -0.5f, -2.0f, 3.0f }, { 2.5f, -2.0f, 3.0f } }));
        const auto r2 = s1.surface_intersections(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, -nnm::Vector3f::axis_x()));
        ASSERT(r2.empty());
        const auto r3 = s1.surface_intersections(nnm::Ray3f(nnm::Vector3f::zero(), nnm::Vector3f::axis_x()));
        ASSERT(r3.empty());
        const auto r4 = s1.surface_intersections(nnm::Ray3f(nnm::Vector3f::zero(), -nnm::Vector3f::axis_x()));
        ASSERT(r4.empty());
        const auto r5 = s_degen.surface_intersections(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        ASSERT(r5.empty());
        const auto r6 = s_degen.surface_intersections(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, -nnm::Vector3f::axis_x()));
        ASSERT(r6.approx_equal({ nnm::Vector3f::zero() }));
        const auto r7 = s1.surface_intersections(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, nnm::Vector3f::axis_x()));
        ASSERT(r7.approx_equal({ { 1.0f, -2.0f, 1.5f } }));
        const auto r8 = s1.surface_intersections(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, -nnm::Vector3f::axis_x()));
        ASSERT(r8.empty());
    }

    test_section("intersects(const Segment3&)");
    {
        const auto r1 = s1.intersects(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { 10.0f, -2.0f, 3.0f }));
        ASSERT(r1);
        const auto r2 = s1.intersects(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { -10.0f, -2.0f, 3.0f }));
        ASSERT_FALSE(r2);
        const auto r3 = s1.intersects(nnm::Segment3f({ 10.0f, -2.0f, 3.0f }, { 20.0f, -2.0f, 3.0f }));
        ASSERT_FALSE(r3);
        const auto r4 = s1.intersects(nnm::Segment3f(nnm::Vector3f::zero(), { 10.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(r4);
        const auto r5 = s1.intersects(nnm::Segment3f(nnm::Vector3f::zero(), { -10.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(r5);
        const auto r6 = s_degen.intersects(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(r6);
        const auto r7 = s_degen.intersects(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        ASSERT(r7);
        const auto r8 = s1.intersects(nnm::Segment3f({ -2.0f, -2.0f, 1.5f }, { 5.0f, -2.0f, 1.5f }));
        ASSERT(r8);
    }

    test_section("surface_intersections(const Segment3&)");
    {
        const auto r1 = s1.surface_intersections(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { 10.0f, -2.0f, 3.0f }));
        ASSERT(r1.approx_equal({ { -0.5f, -2.0f, 3.0f }, { 2.5f, -2.0f, 3.0f } }));
        const auto r2 = s1.surface_intersections(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { -10.0f, -2.0f, 3.0f }));
        ASSERT(r2.empty());
        const auto r3 = s1.surface_intersections(nnm::Segment3f({ 10.0f, -2.0f, 3.0f }, { 20.0f, -2.0f, 3.0f }));
        ASSERT(r3.empty());
        const auto r4 = s1.surface_intersections(nnm::Segment3f(nnm::Vector3f::zero(), { 10.0f, 0.0f, 0.0f }));
        ASSERT(r4.empty());
        const auto r5 = s1.surface_intersections(nnm::Segment3f(nnm::Vector3f::zero(), { -10.0f, 0.0f, 0.0f }));
        ASSERT(r5.empty());
        const auto r6 = s_degen.surface_intersections(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }));
        ASSERT(r6.empty());
        const auto r7 = s_degen.surface_intersections(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        ASSERT(r7.approx_equal({ nnm::Vector3f::zero() }));
        const auto r8 = s1.surface_intersections(nnm::Segment3f({ -2.0f, -2.0f, 1.5f }, { 5.0f, -2.0f, 1.5f }));
        ASSERT(r8.approx_equal({ { 1.0f, -2.0f, 1.5f } }));
    }

    test_section("intersects(const Sphere&)");
    {
        constexpr auto r1 = s1.intersects(s1);
        ASSERT(r1);
        constexpr auto r2 = s1.intersects(nnm::SphereF(nnm::Vector3f::zero(), 1.0f));
        ASSERT_FALSE(r2);
        constexpr auto r3 = s1.intersects(s1.translate({ 1.5f, 0.0f, 0.0f }));
        ASSERT(r3);
        constexpr auto r4 = s1.intersects(s1.translate({ 3.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(r4);
    }

    test_section("intersect_depth(const Sphere&)");
    {
        const auto r1 = s1.intersect_depth(s1);
        ASSERT(r1.has_value() && nnm::approx_equal(r1->length(), s1.radius * 2.0f));
        const auto r2 = s1.intersect_depth(nnm::SphereF(nnm::Vector3f::zero(), 1.0f));
        ASSERT_FALSE(r2.has_value());
        const auto r3 = s1.intersect_depth(s1.translate({ 1.5f, 0.0f, 0.0f }));
        ASSERT(r3.has_value() && r3->approx_equal({ 1.5f, 0.0f, 0.0f }));
        const auto r4 = s1.intersect_depth(s1.translate({ 3.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(r4.has_value());
    }

    test_section("tangent(const Line3&)");
    {
        constexpr auto r1 = s1.tangent(nnm::Line3f::axis_x_offset(-2.0f, 3.0f));
        ASSERT_FALSE(r1);
        constexpr auto r2 = s1.tangent(nnm::Line3f::axis_x());
        ASSERT_FALSE(r2);
        constexpr auto r3 = s1.tangent(nnm::Line3f::axis_y_offset(2.5f, 3.0f));
        ASSERT(r3);
        constexpr auto r4 = s_degen.tangent(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        ASSERT_FALSE(r4);
        constexpr auto r5 = s_degen.tangent(nnm::Line3f::axis_z());
        ASSERT(r5);
    }

    test_section("tangent(const Ray3&)");
    {
        constexpr auto r1 = s1.tangent(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r1);
        constexpr auto r2 = s1.tangent(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, -nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r2);
        constexpr auto r3 = s1.tangent(nnm::Ray3f(nnm::Vector3f::zero(), nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r3);
        constexpr auto r4 = s1.tangent(nnm::Ray3f(nnm::Vector3f::zero(), -nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r4);
        constexpr auto r5 = s_degen.tangent(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r5);
        constexpr auto r6 = s_degen.tangent(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, -nnm::Vector3f::axis_x()));
        ASSERT(r6);
        constexpr auto r7 = s1.tangent(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, nnm::Vector3f::axis_x()));
        ASSERT(r7);
        constexpr auto r8 = s1.tangent(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, -nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r8);
        constexpr auto r9 = s1.tangent(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, -nnm::Vector3f::axis_x()));
        ASSERT_FALSE(r9);
    }

    test_section("tangent(const Segment3&)");
    {
        const auto r1 = s1.tangent(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { 10.0f, -2.0f, 3.0f }));
        ASSERT_FALSE(r1);
        const auto r2 = s1.tangent(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { -10.0f, -2.0f, 3.0f }));
        ASSERT_FALSE(r2);
        const auto r3 = s1.tangent(nnm::Segment3f({ 10.0f, -2.0f, 3.0f }, { 20.0f, -2.0f, 3.0f }));
        ASSERT_FALSE(r3);
        const auto r4 = s1.tangent(nnm::Segment3f(nnm::Vector3f::zero(), { 10.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(r4);
        const auto r5 = s1.tangent(nnm::Segment3f(nnm::Vector3f::zero(), { -10.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(r5);
        const auto r6 = s_degen.tangent(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }));
        ASSERT_FALSE(r6);
        const auto r7 = s_degen.tangent(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        ASSERT(r7);
        const auto r8 = s1.tangent(nnm::Segment3f({ -2.0f, -2.0f, 1.5f }, { 5.0f, -2.0f, 1.5f }));
        ASSERT(r8);
        const auto r9 = s1.tangent(nnm::Segment3f({ -20.0f, -2.0f, 1.5f }, { -50.0f, -2.0f, 1.5f }));
        ASSERT_FALSE(r9);
    }

    test_section("translate");
    {
        constexpr auto r1 = s1.translate({ -3.0f, 4.5f, -5.0f });
        ASSERT(r1.approx_equal({ s1.center.translate({ -3.0f, 4.5f, -5.0f }), s1.radius }));
    }

    test_section("rotate_axis_angle_at");
    {
        constexpr nnm::Vector3f origin { -3.0f, 4.5f, -5.0f };
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = -2.0f * nnm::pi<float>() / 3.0f;
        const auto r1 = s1.rotate_axis_angle_at(origin, axis, angle);
        ASSERT(r1.approx_equal({ s1.center.rotate_axis_angle_at(origin, axis, angle), s1.radius }));
    }

    test_section("rotate_axis_angle");
    {
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = -2.0f * nnm::pi<float>() / 3.0f;
        const auto r1 = s1.rotate_axis_angle(axis, angle);
        ASSERT(r1.approx_equal({ s1.center.rotate_axis_angle(axis, angle), s1.radius }));
    }

    test_section("rotate_quaternion_at");
    {
        constexpr nnm::Vector3f origin { -3.0f, 4.5f, -5.0f };
        constexpr nnm::QuaternionF quat { 0.0f, -0.866025447f, 0.0f, 0.5f };
        constexpr auto r1 = s1.rotate_quaternion_at(origin, quat);
        ASSERT(r1.approx_equal({ s1.center.rotate_quaternion_at(origin, quat), s1.radius }));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::QuaternionF quat { 0.0f, -0.866025447f, 0.0f, 0.5f };
        constexpr auto r1 = s1.rotate_quaternion(quat);
        ASSERT(r1.approx_equal({ s1.center.rotate_quaternion(quat), s1.radius }));
    }

    test_section("scale_at");
    {
        constexpr nnm::Vector3f origin { -3.0f, 4.5f, -5.0f };
        constexpr float factor = 1.25f;
        constexpr auto r1 = s1.scale_at(origin, factor);
        ASSERT(r1.approx_equal({ s1.center.scale_at(origin, nnm::Vector3f::all(factor)), s1.radius * factor }));
    }

    test_section("scale");
    {
        constexpr float factor = 1.25f;
        constexpr auto r1 = s1.scale(factor);
        ASSERT(r1.approx_equal({ s1.center.scale(nnm::Vector3f::all(factor)), s1.radius * factor }));
    }

    test_section("approx_equal");
    {
        constexpr auto r1 = s1.approx_equal(s1);
        ASSERT(r1);
        constexpr auto r2 = s1.approx_equal(s_degen);
        ASSERT_FALSE(r2);
        constexpr auto r3 = s1.approx_equal({ { 1.0f, -2.0f, 3.0f }, 1.5f });
        ASSERT(r3);
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r1 = s1 == s1;
        ASSERT(r1);
        constexpr auto r2 = s1 == s_degen;
        ASSERT_FALSE(r2);
        constexpr auto r3 = s1 == nnm::SphereF({ 1.0f, -2.0f, 3.0f }, 1.5f);
        ASSERT(r3);
    }

    test_section("operator!=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r1 = s1 != s1;
        ASSERT_FALSE(r1);
        constexpr auto r2 = s1 != s_degen;
        ASSERT(r2);
        constexpr auto r3 = s1 != nnm::SphereF({ 1.0f, -2.0f, 3.0f }, 1.5f);
        ASSERT_FALSE(r3);
    }

    test_section("operator<");
    {
        constexpr auto r1 = s1 < s_degen;
        ASSERT_FALSE(r1);
        constexpr auto r2 = s_degen < s1;
        ASSERT(r2);
    }
}

void geom3_tests()
{
    intersections3_tests();
    line3_tests();
    ray3_tests();
    segment3_tests();
    plane_tests();
    triangle3_tests();
    sphere_tests();
}
#include "tests.hpp"

void box_tests()
{
    test_case("Box");

    test_section("Box()");
    {
        constexpr nnm::BoxF b;
        TEST_ASSERT(b.approx_equal(
            { nnm::Point3f::zero(), nnm::Vector3f::zero(), nnm::Vector3f::zero(), nnm::Vector3f::zero() }));
    }

    test_section("Box(const Vector3&, const Vector3&, const Vector3&, const Vector3&)");
    {
        constexpr nnm::BoxF b { { 1.0f, -2.0f, 3.0f },
                                { 0.707106769f, 0.0f, 0.707106769f },
                                { 0.0f, 2.0f, 0.0f },
                                { 1.06066012f, 0.0f, 1.06066012f } };
        TEST_ASSERT(b.approx_equal(
            { { 1.0f, -2.0f, 3.0f },
              { 0.707106769f, 0.0f, 0.707106769f },
              { 0.0f, 2.0f, 0.0f },
              { 1.06066012f, 0.0f, 1.06066012f } }));
    }

    test_section("Box(const Box<Other>&)");
    {
        constexpr nnm::BoxD bd {
            { 1.0, -2.0, 3.0 }, { 0.707106769, 0.0, 0.707106769 }, { 0.0, 2.0, 0.0 }, { 1.06066012, 0.0, 1.06066012 }
        };
        constexpr nnm::BoxF bf { bd };
        TEST_ASSERT(bf.approx_equal(
            { { 1.0f, -2.0f, 3.0f },
              { 0.707106769f, 0.0f, 0.707106769f },
              { 0.0f, 2.0f, 0.0f },
              { 1.06066012f, 0.0f, 1.06066012f } }));
    }

    test_section("from_center_size");
    {
        constexpr auto b = nnm::BoxF::from_center_size({ 1.0f, -2.0f, 3.0f }, { 2.0f, 4.0f, 3.0f });
        TEST_ASSERT(b.approx_equal(
            { { 1.0f, -2.0f, 3.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, { 0.0f, 0.0f, 1.5f } }));
    }

    // auto b1 = nnm::BoxF::from_center_size({ 1.0f, -2.0f, 3.0f }, { 2.0f, 4.0f, 3.0f });
    // b1 = b1.rotate_axis_angle(nnm::Vector3f::axis_y(), nnm::pi<float>() / 4.0f, b1.center);
    constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                             { 0.707106769f, 0.0f, -0.707106769f },
                             { 0.0f, 2.0f, 0.0f },
                             { 1.06066012f, 0.0f, 1.06066012f } };
    constexpr nnm::BoxF b_degen_rect {
        { 1.0f, -2.0f, 3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, { 1.06066012f, 0.0f, 1.06066012f }
    };
    constexpr nnm::BoxF b_degen_segment {
        { 1.0f, -2.0f, 3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }
    };
    constexpr nnm::BoxF b_degen_point {
        { 1.0f, -2.0f, 3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }
    };

    test_section("collapse_rectangle");
    {
        constexpr std::optional<nnm::Rectangle3f> r1 = b1.collapse_rectangle();
        TEST_ASSERT_FALSE(r1.has_value());
        constexpr std::optional<nnm::Rectangle3f> r2 = b_degen_rect.collapse_rectangle();
        TEST_ASSERT(
            r2.has_value()
            && r2->coincident({ { 1.0f, -2.0f, 3.0f }, { 0.0f, 2.0f, 0.0f }, { 1.06066012f, 0.0f, 1.06066012f } }));
        constexpr std::optional<nnm::Rectangle3f> r3 = b_degen_segment.collapse_rectangle();
        TEST_ASSERT(
            r3.has_value() && r3->coincident({ { 1.0f, -2.0f, 3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 2.0f, 0.0f } }));
        constexpr std::optional<nnm::Rectangle3f> r4 = b_degen_point.collapse_rectangle();
        TEST_ASSERT(
            r4.has_value() && r4->coincident({ { 1.0f, -2.0f, 3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }));
    }

    test_section("collapse_segment");
    {
        constexpr std::optional<nnm::Segment3f> r1 = b1.collapse_segment();
        TEST_ASSERT_FALSE(r1.has_value());
        constexpr std::optional<nnm::Segment3f> r2 = b_degen_rect.collapse_segment();
        TEST_ASSERT_FALSE(r2.has_value());
        constexpr std::optional<nnm::Segment3f> r3 = b_degen_segment.collapse_segment();
        TEST_ASSERT(r3.has_value() && r3->coincident({ { 1.0f, 0.0f, 3.0f }, { 1.0f, -4.0f, 3.0f } }));
        constexpr std::optional<nnm::Segment3f> r4 = b_degen_point.collapse_segment();
        TEST_ASSERT(r4.has_value() && r4->coincident({ { 1.0f, -2.0f, 3.0f }, { 1.0f, -2.0f, 3.0f } }));
    }

    test_section("collapse_point");
    {
        constexpr std::optional<nnm::Point3f> r1 = b1.collapse_point();
        TEST_ASSERT_FALSE(r1.has_value());
        constexpr std::optional<nnm::Point3f> r2 = b_degen_rect.collapse_point();
        TEST_ASSERT_FALSE(r2.has_value());
        constexpr std::optional<nnm::Point3f> r3 = b_degen_segment.collapse_point();
        TEST_ASSERT_FALSE(r3.has_value());
        constexpr std::optional<nnm::Point3f> r4 = b_degen_point.collapse_point();
        TEST_ASSERT(r4.has_value() && r4->approx_equal({ 1.0f, -2.0f, 3.0f }));
    }

    test_section("vertex");
    {
        std::vector<nnm::Point3f> vertices;
        constexpr nnm::Point3f v0 = b1.vertex(0);
        vertices.push_back(v0);
        constexpr nnm::Point3f v1 = b1.vertex(1);
        vertices.push_back(v1);
        constexpr nnm::Point3f v2 = b1.vertex(2);
        vertices.push_back(v2);
        constexpr nnm::Point3f v3 = b1.vertex(3);
        vertices.push_back(v3);
        constexpr nnm::Point3f v4 = b1.vertex(4);
        vertices.push_back(v4);
        constexpr nnm::Point3f v5 = b1.vertex(5);
        vertices.push_back(v5);
        constexpr nnm::Point3f v6 = b1.vertex(6);
        vertices.push_back(v6);
        constexpr nnm::Point3f v7 = b1.vertex(7);
        vertices.push_back(v7);

        auto vertices_contains_approx = [&vertices](const nnm::Point3f& vertex) {
            return std::find_if(
                       vertices.begin(),
                       vertices.end(),
                       [&vertex](const nnm::Point3f& v) { return v.approx_equal(vertex); })
                != vertices.end();
        };

        TEST_ASSERT(vertices_contains_approx({ -0.767766892f, -4.0f, 2.6464467f }));
        TEST_ASSERT(vertices_contains_approx({ 1.3535533f, -4.0f, 4.76776695f }));
        TEST_ASSERT(vertices_contains_approx({ -0.767766892f, 0.0f, 2.6464467f }));
        TEST_ASSERT(vertices_contains_approx({ 1.3535533f, 0.0f, 4.76776695f }));
        TEST_ASSERT(vertices_contains_approx({ 0.646446704f, -4.0f, 1.23223305f }));
        TEST_ASSERT(vertices_contains_approx({ 2.767766896f, -4.0f, 3.3535533f }));
        TEST_ASSERT(vertices_contains_approx({ 2.767766896f, 0.0f, 3.3535533f }));
        TEST_ASSERT(vertices_contains_approx({ 0.646446704f, 0.0f, 1.23223305f }));
    }

    test_section("edge");
    {
        std::vector<nnm::Segment3f> edges;
        constexpr nnm::Segment3f e0 = b1.edge(0);
        edges.push_back(e0);
        constexpr nnm::Segment3f e1 = b1.edge(1);
        edges.push_back(e1);
        constexpr nnm::Segment3f e2 = b1.edge(2);
        edges.push_back(e2);
        constexpr nnm::Segment3f e3 = b1.edge(3);
        edges.push_back(e3);
        constexpr nnm::Segment3f e4 = b1.edge(4);
        edges.push_back(e4);
        constexpr nnm::Segment3f e5 = b1.edge(5);
        edges.push_back(e5);
        constexpr nnm::Segment3f e6 = b1.edge(6);
        edges.push_back(e6);
        constexpr nnm::Segment3f e7 = b1.edge(7);
        edges.push_back(e7);
        constexpr nnm::Segment3f e8 = b1.edge(8);
        edges.push_back(e8);
        constexpr nnm::Segment3f e9 = b1.edge(9);
        edges.push_back(e9);
        constexpr nnm::Segment3f e10 = b1.edge(10);
        edges.push_back(e10);
        constexpr nnm::Segment3f e11 = b1.edge(11);
        edges.push_back(e11);

        auto edges_contains_coincident = [&edges](const nnm::Segment3f& edge) {
            return std::find_if(
                       edges.begin(), edges.end(), [&edge](const nnm::Segment3f& e) { return e.coincident(edge); })
                != edges.end();
        };

        TEST_ASSERT(edges_contains_coincident({ b1.vertex(0), b1.vertex(1) }));
        TEST_ASSERT(edges_contains_coincident({ b1.vertex(0), b1.vertex(2) }));
        TEST_ASSERT(edges_contains_coincident({ b1.vertex(2), b1.vertex(3) }));
        TEST_ASSERT(edges_contains_coincident({ b1.vertex(1), b1.vertex(3) }));
        TEST_ASSERT(edges_contains_coincident({ b1.vertex(0), b1.vertex(4) }));
        TEST_ASSERT(edges_contains_coincident({ b1.vertex(1), b1.vertex(5) }));
        TEST_ASSERT(edges_contains_coincident({ b1.vertex(2), b1.vertex(6) }));
        TEST_ASSERT(edges_contains_coincident({ b1.vertex(3), b1.vertex(7) }));
        TEST_ASSERT(edges_contains_coincident({ b1.vertex(4), b1.vertex(5) }));
        TEST_ASSERT(edges_contains_coincident({ b1.vertex(4), b1.vertex(6) }));
        TEST_ASSERT(edges_contains_coincident({ b1.vertex(6), b1.vertex(7) }));
        TEST_ASSERT(edges_contains_coincident({ b1.vertex(5), b1.vertex(7) }));
    }

    test_section("face");
    {
        std::vector<nnm::Rectangle3f> faces;
        constexpr nnm::Rectangle3f f0 = b1.face(0);
        faces.push_back(f0);
        constexpr nnm::Rectangle3f f1 = b1.face(1);
        faces.push_back(f1);
        constexpr nnm::Rectangle3f f2 = b1.face(2);
        faces.push_back(f2);
        constexpr nnm::Rectangle3f f3 = b1.face(3);
        faces.push_back(f3);
        constexpr nnm::Rectangle3f f4 = b1.face(4);
        faces.push_back(f4);
        constexpr nnm::Rectangle3f f5 = b1.face(5);
        faces.push_back(f5);

        auto faces_contains_coincident = [&faces](const nnm::Rectangle3f& face) {
            return std::find_if(
                       faces.begin(), faces.end(), [&face](const nnm::Rectangle3f& f) { return f.coincident(face); })
                != faces.end();
        };

        TEST_ASSERT(faces_contains_coincident(
            { { 0.292893204f, -2.0f, 3.707106825f },
              nnm::Vector3f::axis_y() * 2.0f,
              { 1.0606601718f, 0.0f, 1.0606601718f } }));
        TEST_ASSERT(faces_contains_coincident(
            { { 1.7071068f, -2.0f, 2.292893175f },
              nnm::Vector3f::axis_y() * 2.0f,
              { 1.0606601718f, 0.0f, 1.0606601718f } }));
        TEST_ASSERT(faces_contains_coincident(
            { { 1.0f, -4.0f, 3.0f },
              { -0.7071067812f, 0.0f, 0.7071067812f },
              { 1.0606601718f, 0.0f, 1.0606601718f } }));
        TEST_ASSERT(faces_contains_coincident(
            { { 1.0f, 0.0f, 3.0f }, { -0.7071067812f, 0.0f, 0.7071067812f }, { 1.0606601718f, 0.0f, 1.0606601718f } }));
        TEST_ASSERT(faces_contains_coincident(
            { { 2.060660098f, -2.0f, 4.060660125f },
              -nnm::Vector3f::axis_y() * 2.0f,
              { -0.7071067812f, 0.0f, 0.7071067812f } }));
        TEST_ASSERT(faces_contains_coincident(
            { { -0.060660094f, -2.0f, 1.939339875f },
              -nnm::Vector3f::axis_y() * 2.0f,
              { -0.7071067812f, 0.0f, 0.7071067812f } }));
    }

    test_section("valid");
    {
        constexpr bool r1 = b1.valid();
        TEST_ASSERT(r1);
        constexpr bool r2
            = nnm::BoxF(
                  { 1.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x(), nnm::Vector3f::axis_x(), nnm::Vector3f::axis_z())
                  .valid();
        TEST_ASSERT_FALSE(r2);
        constexpr bool r3 = nnm::BoxF().valid();
        TEST_ASSERT_FALSE(r3);
    }

    test_section("size");
    {
        const nnm::Vector3f r1 = b1.size();
        TEST_ASSERT(r1.approx_equal({ 2.0f, 4.0f, 3.0f }));
    }

    test_section("volume");
    {
        constexpr float r1 = b1.volume();
        TEST_ASSERT(nnm::approx_equal(r1, 24.0f));
    }

    test_section("surface_area");
    {
        const float r1 = b1.surface_area();
        TEST_ASSERT(nnm::approx_equal(r1, 52.0f));
    }

    test_section("contains");
    {
        constexpr bool r1 = b1.contains(nnm::Point3f::zero());
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1.contains({ 0.0f, -2.0f, 3.0f });
        TEST_ASSERT(r2);
        constexpr bool r3 = b1.contains(b1.vertex(0));
        TEST_ASSERT(r3);
        constexpr bool r4 = b1.contains({ 0.0f, -2.0f, 5.0f });
        TEST_ASSERT_FALSE(r4);
    }

    test_section("distance_sqrd(const Vector3&)");
    {
        constexpr float r1 = b1.distance_sqrd(nnm::Point3f::zero());
        TEST_ASSERT(nnm::approx_equal(r1, 1.9362916306f));
        constexpr float r2 = b1.distance_sqrd({ 0.0f, -2.0f, 3.0f });
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3 = b1.distance_sqrd(b1.vertex(0));
        TEST_ASSERT(nnm::approx_zero(r3));
        constexpr float r4 = b1.distance_sqrd({ 0.0f, -2.0f, 5.0f });
        TEST_ASSERT(nnm::approx_equal(r4, 1.2573591981f));
    }

    test_section("distance_sqrd(const Triangle3&)");
    {
        constexpr float r1
            = b1.distance_sqrd(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(r1, 1.5183982895123f));
        constexpr float r2
            = b1.distance_sqrd(nnm::Triangle3f({ 1.0f, 10.0f, 0.0f }, { 1.0f, -2.0f, 10.0f }, { 1.0f, -10.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3
            = b1.distance_sqrd(nnm::Triangle3f({ -0.5f, -1.0f, 1.5f }, { -1.0f, 0.0f, 1.0f }, { 1.0f, -5.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(r3, 0.38603907872361f));
    }

    test_section("distance(const Vector3&)");
    {
        const float r1 = b1.distance(nnm::Point3f::zero());
        TEST_ASSERT(nnm::approx_equal(r1, 1.3915069639f));
        const float r2 = b1.distance({ 0.0f, -2.0f, 3.0f });
        TEST_ASSERT(nnm::approx_zero(r2));
        const float r3 = b1.distance(b1.vertex(0));
        TEST_ASSERT(nnm::approx_zero(r3));
        const float r4 = b1.distance({ 0.0f, -2.0f, 5.0f });
        TEST_ASSERT(nnm::approx_equal(r4, 1.1213202924f));
    }

    test_section("distance(const Line3&)");
    {
        const float r1 = b1.distance(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(r1, 1.23223305f));
        const float r2 = b1.distance(nnm::Line3f::axis_y_offset(0.0f, 1.5f));
        TEST_ASSERT(nnm::approx_equal(r2, 0.2677670343f));
        const float r3 = b1.distance(nnm::Line3f::axis_z_offset(0.0f, -1.0f));
        TEST_ASSERT(nnm::approx_zero(r3));
    }

    test_section("distance(const Ray3&)");
    {
        const float r1 = b1.distance(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT(nnm::approx_equal(r1, 1.23223305f));
        const float r2 = b1.distance(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_x()));
        TEST_ASSERT(nnm::approx_equal(r2, 1.3915069639f));
        const float r3 = b1.distance(nnm::Ray3f({ 0.0f, 0.0f, 1.5f }, nnm::Vector3f::axis_y()));
        TEST_ASSERT(nnm::approx_equal(r3, 0.2677670343f));
        const float r4 = b1.distance(nnm::Ray3f({ 0.0f, -1.0f, 0.0f }, nnm::Vector3f::axis_z()));
        TEST_ASSERT(nnm::approx_zero(r4));
        const float r5 = b1.distance(nnm::Ray3f({ 0.0f, -1.0f, 0.0f }, -nnm::Vector3f::axis_z()));
        TEST_ASSERT(nnm::approx_equal(r5, 1.3915069639f));
    }

    test_section("distance(const Segment3&)");
    {
        const float r1 = b1.distance(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 100.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(r1, 1.23223305f));
        const float r2 = b1.distance(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -100.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(r2, 1.3915069639f));
        const float r3 = b1.distance(nnm::Segment3f({ 0.0f, 0.0f, 1.5f }, { 0.0f, 100.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(r3, 0.2677670343f));
        const float r4 = b1.distance(nnm::Segment3f({ 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 100.0f }));
        TEST_ASSERT(nnm::approx_zero(r4));
        const float r5 = b1.distance(nnm::Segment3f({ 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -100.0f }));
        TEST_ASSERT(nnm::approx_equal(r5, 1.3915069639f));
    }

    test_section("distance(const Plane&)");
    {
        constexpr float r1 = b1.distance(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_equal(r1, 1.23223305f));
        constexpr float r2 = b1.distance(nnm::PlaneF::yz());
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3 = b1.distance(nnm::PlaneF::yz_offset(-2.0f));
        TEST_ASSERT(nnm::approx_equal(r3, 1.232233108f));
    }

    test_section("intersects(const Line3&)");
    {
        constexpr bool r1 = b1.intersects(nnm::Line3f::axis_y());
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1.intersects(nnm::Line3f::axis_z());
        TEST_ASSERT(r2);
        constexpr bool r4 = b1.intersects(nnm::Line3f({ 0.0f, -2.0f, 5.0f }, { 0.7071067812f, 0.0f, -0.7071067812f }));
        TEST_ASSERT(r4);
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr bool r1 = b1.intersects(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_y()));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1.intersects(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_z()));
        TEST_ASSERT(r2);
        constexpr bool r3 = b1.intersects(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_z()));
        TEST_ASSERT_FALSE(r3);
        constexpr bool r4 = b1.intersects(nnm::Ray3f({ 0.0f, -2.0f, 5.0f }, { 0.7071067812f, 0.0f, -0.7071067812f }));
        TEST_ASSERT(r4);
        constexpr bool r5 = b1.intersects(nnm::Ray3f({ 0.0f, -2.0f, 5.0f }, { -0.7071067812f, 0.0f, 0.7071067812f }));
        TEST_ASSERT_FALSE(r5);
        constexpr bool r6 = b1.intersects(nnm::Ray3f({ 0.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(r6);
    }

    test_section("intersects(const Segment3&)");
    {
        constexpr bool r1 = b1.intersects(nnm::Segment3f(nnm::Point3f::zero(), { 0.0f, -3.0f, 0.0f }));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1.intersects(nnm::Segment3f(nnm::Point3f::zero(), { 0.0f, 0.0f, 3.0f }));
        TEST_ASSERT(r2);
        constexpr bool r3 = b1.intersects(nnm::Segment3f(nnm::Point3f::zero(), { 0.0f, 0.0f, -3.0f }));
        TEST_ASSERT_FALSE(r3);
        constexpr bool r4 = b1.intersects(nnm::Segment3f({ 0.0f, -2.0f, 5.0f }, { 10.0f, -2.0f, -5.0f }));
        TEST_ASSERT(r4);
        constexpr bool r5 = b1.intersects(nnm::Segment3f({ 0.0f, -2.0f, 5.0f }, { -10.0f, -2.0f, 15.0f }));
        TEST_ASSERT_FALSE(r5);
        constexpr bool r6 = b1.intersects(nnm::Segment3f({ 0.0f, -2.0f, 3.0f }, { 10.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r6);
        constexpr bool r7 = b1.intersects(nnm::Segment3f({ 0.0f, -2.0f, 3.0f }, { 0.0f, -3.0f, 3.0f }));
        TEST_ASSERT(r7);
    }

    test_section("intersects(const Plane&)");
    {
        constexpr bool r1 = b1.intersects(nnm::PlaneF::xy());
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1.intersects(nnm::PlaneF::xz());
        TEST_ASSERT(r2);
        constexpr bool r3 = b1.intersects(nnm::PlaneF::xz_offset(-2.0f));
        TEST_ASSERT(r3);
    }

    test_section("intersects(const Triangle3&)");
    {
        const bool r1
            = b1.intersects(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }, { 0.0f, -10.0f, 0.0f }));
        TEST_ASSERT_FALSE(r1);
        const bool r2
            = b1.intersects(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 3.0f }));
        TEST_ASSERT(r2);
        const bool r3
            = b1.intersects(nnm::Triangle3f({ 0.0f, -2.0f, 0.0f }, { 2.0f, -2.0f, 0.0f }, { 0.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r3);
        const bool r4 = b1.intersects(
            nnm::Triangle3f({ -100.0f, -2.0f, 0.0f }, { 100.0f, -2.0f, 0.0f }, { 0.0f, -2.0f, 100.0f }));
        TEST_ASSERT(r4);
        const bool r5
            = b1.intersects(nnm::Triangle3f({ 0.0f, -2.0f, 3.0f }, { 0.0f, -3.0f, 3.0f }, { 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r5);
    }

    test_section("intersects(const Rectangle3&)");
    {
        constexpr bool r1 = b1.intersects(nnm::Rectangle3f::from_xy_offset_size({ 0.0f, -2.0f, 0.0f }, 1.0f, 1.0f));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1.intersects(nnm::Rectangle3f::from_xz_offset_size({ 0.0f, -2.0f, 2.0f }, 1.0f, 1.0f));
        TEST_ASSERT(r2);
        constexpr bool r3 = b1.intersects(nnm::Rectangle3f::from_xz_offset_size({ 0.0f, -2.0f, 1.0f }, 100.0f, 100.0f));
        TEST_ASSERT(r3);
        constexpr bool r4 = b1.intersects(nnm::Rectangle3f::from_xz_offset_size({ 0.0f, -2.0f, 3.0f }, 0.01f, 0.01f));
        TEST_ASSERT(r4);
    }

    test_section("intersects(const Sphere&)");
    {
        constexpr bool r1 = b1.intersects(nnm::SphereF(nnm::Point3f::zero(), 1.0f));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1.intersects(nnm::SphereF({ 0.0f, -2.0f, 1.0f }, 3.0f));
        TEST_ASSERT(r2);
        constexpr bool r3 = b1.intersects(nnm::SphereF(nnm::Point3f::zero(), 100.0f));
        TEST_ASSERT(r3);
        constexpr bool r4 = b1.intersects(nnm::SphereF({ 0.0f, -2.0f, 3.0f }, 0.01f));
        TEST_ASSERT(r4);
    }

    test_section("intersects(const AlignedBox&)");
    {
        const bool r1
            = b1.intersects(nnm::AlignedBoxF::from_bounding_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, -1.0f, 1.0f }));
        TEST_ASSERT_FALSE(r1);
        const bool r2
            = b1.intersects(nnm::AlignedBoxF::from_bounding_points({ 0.0f, 2.0f, 0.0f }, { 0.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r2);
        const bool r3 = b1.intersects(
            nnm::AlignedBoxF::from_bounding_points({ 0.0f, 2.0f, 0.0f }, { 1000.0f, -1000.0f, 1000.0f }));
        TEST_ASSERT(r3);
        const bool r4
            = b1.intersects(nnm::AlignedBoxF::from_bounding_points({ 0.0f, -2.0f, 3.0f }, { 1.0f, -1.0f, 2.5f }));
        TEST_ASSERT(r4);
    }

    test_section("intersects(const Box&)");
    {
        const bool r1 = b1.intersects(nnm::BoxF::from_center_size(nnm::Point3f::zero(), nnm::Vector3f::all(1.0f)));
        TEST_ASSERT_FALSE(r1);
        const bool r2 = b1.intersects(nnm::BoxF::from_center_size(nnm::Point3f::zero(), nnm::Vector3f::all(5.0f)));
        TEST_ASSERT(r2);
        const bool r3 = b1.intersects(nnm::BoxF::from_center_size(nnm::Point3f::zero(), nnm::Vector3f::all(1000.0f)));
        TEST_ASSERT(r3);
        const bool r4 = b1.intersects(nnm::BoxF::from_center_size({ 0.0f, -2.0f, 3.0f }, nnm::Vector3f::all(0.01f)));
        TEST_ASSERT(r4);
    }

    test_section("surface_intersections(const Line3&)");
    {
        constexpr nnm::PointSet<nnm::Point3f, 2> r1 = b1.surface_intersections(nnm::Line3f::axis_y());
        TEST_ASSERT(r1.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r2 = b1.surface_intersections(nnm::Line3f::axis_z());
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 3.414213613f }, { 0.0f, 0.0f, 1.8786797787f } }));
        constexpr nnm::PointSet<nnm::Point3f, 2> r4
            = b1.surface_intersections(nnm::Line3f({ 0.0f, -2.0f, 5.0f }, { 0.7071067812f, 0.0f, -0.7071067812f }));
        TEST_ASSERT(
            r4.approx_equal({ { 0.7928931935f, -2.0f, 4.2071068282f }, { 2.2071068358f, -2.0f, 2.7928932245f } }));
    }

    test_section("surface_intersections(const Ray3&)");
    {
        constexpr nnm::PointSet<nnm::Point3f, 2> r1
            = b1.surface_intersections(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_y()));
        TEST_ASSERT(r1.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r2
            = b1.surface_intersections(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_z()));
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 3.414213613f }, { 0.0f, 0.0f, 1.8786797787f } }));
        constexpr nnm::PointSet<nnm::Point3f, 2> r3
            = b1.surface_intersections(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_z()));
        TEST_ASSERT(r3.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r4
            = b1.surface_intersections(nnm::Ray3f({ 0.0f, -2.0f, 5.0f }, { 0.7071067812f, 0.0f, -0.7071067812f }));
        TEST_ASSERT(
            r4.approx_equal({ { 0.7928931935f, -2.0f, 4.2071068282f }, { 2.2071068358f, -2.0f, 2.7928932245f } }));
        constexpr nnm::PointSet<nnm::Point3f, 2> r5
            = b1.surface_intersections(nnm::Ray3f({ 0.0f, -2.0f, 5.0f }, { -0.7071067812f, 0.0f, 0.7071067812f }));
        TEST_ASSERT(r5.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r6
            = b1.surface_intersections(nnm::Ray3f({ 0.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(r6.approx_equal({ { 2.4142136057f, -2.0f, 3.0f } }));
    }

    test_section("surface_intersections(const Segment3&)");
    {
        constexpr nnm::PointSet<nnm::Point3f, 2> r1
            = b1.surface_intersections(nnm::Segment3f(nnm::Point3f::zero(), { 0.0f, -3.0f, 0.0f }));
        TEST_ASSERT(r1.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r2
            = b1.surface_intersections(nnm::Segment3f(nnm::Point3f::zero(), { 0.0f, 0.0f, 3.0f }));
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 1.8786797787f } }));
        constexpr nnm::PointSet<nnm::Point3f, 2> r3
            = b1.surface_intersections(nnm::Segment3f(nnm::Point3f::zero(), { 0.0f, 0.0f, -3.0f }));
        TEST_ASSERT(r3.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r4
            = b1.surface_intersections(nnm::Segment3f({ 0.0f, -2.0f, 5.0f }, { 10.0f, -2.0f, -5.0f }));
        TEST_ASSERT(
            r4.approx_equal({ { 0.7928931935f, -2.0f, 4.2071068282f }, { 2.2071068358f, -2.0f, 2.7928932245f } }));
        constexpr nnm::PointSet<nnm::Point3f, 2> r5
            = b1.surface_intersections(nnm::Segment3f({ 0.0f, -2.0f, 5.0f }, { -10.0f, -2.0f, 15.0f }));
        TEST_ASSERT(r5.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r6
            = b1.surface_intersections(nnm::Segment3f({ 0.0f, -2.0f, 3.0f }, { 10.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r6.approx_equal({ { 2.4142136057f, -2.0f, 3.0f } }));
        constexpr nnm::PointSet<nnm::Point3f, 2> r7
            = b1.surface_intersections(nnm::Segment3f({ 0.0f, -2.0f, 3.0f }, { 0.0f, -3.0f, 3.0f }));
        TEST_ASSERT(r7.empty());
    }

    test_section("translate");
    {
        constexpr nnm::Vector3f offset { -3.0f, 2.0f, 1.0f };
        constexpr nnm::BoxF r1 = b1.translate(offset);
        TEST_ASSERT(r1.approx_equal(r1));
    }

    test_section("rotate_axis_angle");
    {
        constexpr nnm::Point3f origin { -3.0f, 2.0f, 1.0f };
        constexpr auto axis = nnm::Vector3f::axis_z();
        constexpr float angle = -2.0f * nnm::pi<float>() / 3.0f;
        const nnm::BoxF r1 = b1.rotate_axis_angle(axis, angle, origin);
        TEST_ASSERT(r1.approx_equal(
            { b1.center.rotate_axis_angle_at(origin, axis, angle),
              b1.half_span_u.rotate_axis_angle(axis, angle),
              b1.half_span_v.rotate_axis_angle(axis, angle),
              b1.half_span_w.rotate_axis_angle(axis, angle) }));
        const nnm::BoxF r2 = b1.rotate_axis_angle(axis, angle);
        TEST_ASSERT(r2.approx_equal(
            { b1.center.rotate_axis_angle(axis, angle),
              b1.half_span_u.rotate_axis_angle(axis, angle),
              b1.half_span_v.rotate_axis_angle(axis, angle),
              b1.half_span_w.rotate_axis_angle(axis, angle) }));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::Point3f origin { -3.0f, 2.0f, 1.0f };
        constexpr nnm::QuaternionF quat { 0.0f, 0.0f, 0.8660254f, 0.5f };
        constexpr nnm::BoxF r1 = b1.rotate_quaternion(quat, origin);
        TEST_ASSERT(r1.approx_equal(
            { b1.center.rotate_quaternion_at(origin, quat),
              b1.half_span_u.rotate_quaternion(quat),
              b1.half_span_v.rotate_quaternion(quat),
              b1.half_span_w.rotate_quaternion(quat) }));
        constexpr nnm::BoxF r2 = b1.rotate_quaternion(quat);
        TEST_ASSERT(r2.approx_equal(
            { b1.center.rotate_quaternion(quat),
              b1.half_span_u.rotate_quaternion(quat),
              b1.half_span_v.rotate_quaternion(quat),
              b1.half_span_w.rotate_quaternion(quat) }));
    }

    test_section("scale");
    {
        constexpr nnm::Point3f origin { -3.0f, 2.0f, 1.0f };
        constexpr nnm::Vector3f factor { 0.5f, -1.5f, 2.0f };
        constexpr nnm::BoxF r1 = b1.scale(factor, origin);
        TEST_ASSERT(r1.approx_equal(
            { b1.center.scale_at(origin, factor),
              b1.half_span_u.scale(factor),
              b1.half_span_v.scale(factor),
              b1.half_span_w.scale(factor) }));
        constexpr nnm::BoxF r2 = b1.scale(factor);
        TEST_ASSERT(r2.approx_equal(
            { b1.center.scale(factor),
              b1.half_span_u.scale(factor),
              b1.half_span_v.scale(factor),
              b1.half_span_w.scale(factor) }));
    }

    test_section("coincident");
    {
        const bool r1 = b1.coincident(b1);
        TEST_ASSERT(r1);
        constexpr auto b2 = nnm::BoxF(
            { 1.0f, -2.0f, 3.0f },
            { 0.0f, 2.0f, 0.0f },
            { 0.707106769f, 0.0f, -0.707106769f },
            { 1.06066012f, 0.0f, 1.06066012f });
        const bool r2 = b1.coincident(b2);
        TEST_ASSERT(r2);
        constexpr auto b3 = nnm::BoxF(
            { 1.0f, -2.0f, 3.0f },
            { 0.0f, -2.0f, 0.0f },
            { 0.707106769f, 0.0f, -0.707106769f },
            { 1.06066012f, 0.0f, 1.06066012f });
        const bool r3 = b1.coincident(b3);
        TEST_ASSERT(r3);
        constexpr auto b4 = nnm::BoxF::from_center_size({ 1.0f, -2.0f, 3.0f }, { 1.0f, 2.0f, 3.0f });
        const bool r4 = b1.coincident(b4);
        TEST_ASSERT_FALSE(r4);
        constexpr auto b5 = nnm::BoxF(
            { 1.0f, 2.0f, 3.0f },
            { 0.0f, -2.0f, 0.0f },
            { 0.707106769f, 0.0f, -0.707106769f },
            { 1.06066012f, 0.0f, 1.06066012f });
        const bool r5 = b1.coincident(b5);
        TEST_ASSERT_FALSE(r5);
    }

    test_section("approx_equal");
    {
        constexpr bool r1 = b1.approx_equal(
            { { 1.0f, -2.0f, 3.0f },
              { 0.707106769f, 0.0f, -0.707106769f },
              { 0.0f, 2.0f, 0.0f },
              { 1.06066012f, 0.0f, 1.06066012f } });
        TEST_ASSERT(r1);
        constexpr bool r2 = b1.approx_equal(
            { { 1.0f, -3.0f, 2.0f },
              { 0.707106769f, 0.0f, -0.707106769f },
              { 0.0f, 2.0f, 0.0f },
              { 1.06066012f, 0.0f, 1.06066012f } });
        TEST_ASSERT_FALSE(r2);
    }

    test_section("operator==");
    {
        constexpr bool r1 = b1
            == nnm::BoxF({ { 1.0f, -2.0f, 3.0f },
                           { 0.707106769f, 0.0f, -0.707106769f },
                           { 0.0f, 2.0f, 0.0f },
                           { 1.06066012f, 0.0f, 1.06066012f } });
        TEST_ASSERT(r1);
        constexpr bool r2 = b1
            == nnm::BoxF({ { 1.0f, -3.0f, 2.0f },
                           { 0.707106769f, 0.0f, -0.707106769f },
                           { 0.0f, 2.0f, 0.0f },
                           { 1.06066012f, 0.0f, 1.06066012f } });
        TEST_ASSERT_FALSE(r2);
    }

    test_section("operator!=");
    {
        constexpr bool r1 = b1
            != nnm::BoxF({ { 1.0f, -2.0f, 3.0f },
                           { 0.707106769f, 0.0f, -0.707106769f },
                           { 0.0f, 2.0f, 0.0f },
                           { 1.06066012f, 0.0f, 1.06066012f } });
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1
            != nnm::BoxF({ { 1.0f, -3.0f, 2.0f },
                           { 0.707106769f, 0.0f, -0.707106769f },
                           { 0.0f, 2.0f, 0.0f },
                           { 1.06066012f, 0.0f, 1.06066012f } });
        TEST_ASSERT(r2);
    }

    test_section("operator<");
    {
        constexpr bool r1 = b1
            < nnm::BoxF({ { 1.0f, -2.0f, 3.0f },
                          { 0.707106769f, 0.0f, -0.707106769f },
                          { 0.0f, 2.0f, 0.0f },
                          { 1.06066012f, 0.0f, 1.06066012f } });
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1
            < nnm::BoxF({ { 1.0f, -3.0f, 2.0f },
                          { 0.707106769f, 0.0f, -0.707106769f },
                          { 0.0f, 2.0f, 0.0f },
                          { 1.06066012f, 0.0f, 1.06066012f } });
        TEST_ASSERT_FALSE(r2);
        constexpr bool r3 = b1
            < nnm::BoxF({ { 1.0f, -2.0f, 3.0f },
                          { 10.0f, 0.0f, -10.0f },
                          { 0.0f, 2.0f, 0.0f },
                          { 1.06066012f, 0.0f, 1.06066012f } });
        TEST_ASSERT(r3);
    }
}


#include "tests.hpp"

void aligned_box_tests()
{
    test_case("AlignedBox");

    test_section("AlignedBox()");
    {
        constexpr nnm::AlignedBoxF b1 { };
        TEST_ASSERT(b1.min.approx_zero());
        TEST_ASSERT(b1.max.approx_zero());
    }

    test_section("AlignedBox(const Vector3&, const Vector3&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        TEST_ASSERT(b1.min.approx_equal({ -1.0f, -3.0f, 0.5f }));
        TEST_ASSERT(b1.max.approx_equal({ 2.0f, 2.0f, 4.0f }));
    }

    test_section("from_bounding_points");
    {
        constexpr auto b1 = nnm::AlignedBoxF::from_bounding_points({ 1.0f, -2.0f, 3.0f }, { 1.0f, -2.0f, 3.0f });
        TEST_ASSERT(b1.min.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(b1.max.approx_equal({ 1.0f, -2.0f, 3.0f }));
        constexpr auto b2 = nnm::AlignedBoxF::from_bounding_points({ -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f });
        TEST_ASSERT(b2.min.approx_equal({ -1.0f, -3.0f, 0.5f }));
        TEST_ASSERT(b2.max.approx_equal({ 2.0f, 2.0f, 4.0f }));
        constexpr auto b3 = nnm::AlignedBoxF::from_bounding_points({ -1.0f, 2.0f, 0.5f }, { 2.0f, -3.0f, 4.0f });
        TEST_ASSERT(b3.min.approx_equal({ -1.0f, -3.0f, 0.5f }));
        TEST_ASSERT(b3.max.approx_equal({ 2.0f, 2.0f, 4.0f }));
        constexpr auto b4 = nnm::AlignedBoxF::from_bounding_points({ 2.0f, 2.0f, 4.0f }, { -1.0f, -3.0f, 0.5f });
        TEST_ASSERT(b4.min.approx_equal({ -1.0f, -3.0f, 0.5f }));
        TEST_ASSERT(b4.max.approx_equal({ 2.0f, 2.0f, 4.0f }));
    }

    test_section("from_bounding_segment");
    {
        constexpr auto b1 = nnm::AlignedBoxF::from_bounding_segment({ { 1.0f, -2.0f, 3.0f }, { 1.0f, -2.0f, 3.0f } });
        TEST_ASSERT(b1.min.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(b1.max.approx_equal({ 1.0f, -2.0f, 3.0f }));
        constexpr auto b2 = nnm::AlignedBoxF::from_bounding_segment({ { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } });
        TEST_ASSERT(b2.min.approx_equal({ -1.0f, -3.0f, 0.5f }));
        TEST_ASSERT(b2.max.approx_equal({ 2.0f, 2.0f, 4.0f }));
        constexpr auto b3 = nnm::AlignedBoxF::from_bounding_segment({ { -1.0f, 2.0f, 0.5f }, { 2.0f, -3.0f, 4.0f } });
        TEST_ASSERT(b3.min.approx_equal({ -1.0f, -3.0f, 0.5f }));
        TEST_ASSERT(b3.max.approx_equal({ 2.0f, 2.0f, 4.0f }));
        constexpr auto b4 = nnm::AlignedBoxF::from_bounding_segment({ { 2.0f, 2.0f, 4.0f }, { -1.0f, -3.0f, 0.5f } });
        TEST_ASSERT(b4.min.approx_equal({ -1.0f, -3.0f, 0.5f }));
        TEST_ASSERT(b4.max.approx_equal({ 2.0f, 2.0f, 4.0f }));
    }

    test_section("from_bounding_triangle");
    {
        constexpr auto b1 = nnm::AlignedBoxF::from_bounding_triangle({ });
        TEST_ASSERT(b1.min.approx_zero());
        TEST_ASSERT(b1.max.approx_zero());
        constexpr auto b2 = nnm::AlignedBoxF::from_bounding_triangle(
            { { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } });
        TEST_ASSERT(b2.min.approx_equal({ -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(b2.max.approx_equal({ 1.0f, 0.0f, 0.0f }));
        constexpr auto b3 = nnm::AlignedBoxF::from_bounding_triangle(
            { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } });
        TEST_ASSERT(b3.min.approx_equal({ 0.0f, 0.0f, 0.0f }));
        TEST_ASSERT(b3.max.approx_equal({ 0.0f, 1.0f, 1.0f }));
        constexpr auto b4 = nnm::AlignedBoxF::from_bounding_triangle(
            { { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { -1.0f, -1.0f, 1.0f } });
        TEST_ASSERT(b4.min.approx_equal({ -1.0f, -1.0f, 0.0f }));
        TEST_ASSERT(b4.max.approx_equal({ 1.0f, 1.0f, 1.0f }));
    }

    test_section("from_bounding_rectangle");
    {
        constexpr auto b1 = nnm::AlignedBoxF::from_bounding_rectangle({ });
        TEST_ASSERT(b1.min.approx_zero());
        TEST_ASSERT(b1.max.approx_zero());
        constexpr auto b2 = nnm::AlignedBoxF::from_bounding_rectangle(
            { { -2.5f, 0.0f, 0.0f }, { 1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } });
        TEST_ASSERT(b2.min.approx_equal({ -4.0f, 0.0f, 0.0f }));
        TEST_ASSERT(b2.max.approx_equal({ -1.0f, 0.0f, 0.0f }));
        constexpr auto b3 = nnm::AlignedBoxF::from_bounding_rectangle(
            { { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.5f, 0.0f } });
        TEST_ASSERT(b3.min.approx_equal({ 0.0f, 0.5f, 1.0f }));
        TEST_ASSERT(b3.max.approx_equal({ 2.0f, 1.5f, 1.0f }));
        constexpr auto b4 = nnm::AlignedBoxF::from_bounding_rectangle(
            { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } });
        TEST_ASSERT(b4.min.approx_equal({ -4.0f, 0.0f, 0.0f }));
        TEST_ASSERT(b4.max.approx_equal({ -1.0f, 2.0f, 2.0f }));
    }

    test_section("from_bounding_sphere");
    {
        constexpr auto b1 = nnm::AlignedBoxF::from_bounding_sphere({ });
        TEST_ASSERT(b1.min.approx_equal({ -1.0f, -1.0f, -1.0f }));
        TEST_ASSERT(b1.max.approx_equal({ 1.0f, 1.0f, 1.0f }));
        constexpr auto b2 = nnm::AlignedBoxF::from_bounding_sphere({ { 1.0f, -2.0f, 3.0f }, 0.0f });
        TEST_ASSERT(b2.min.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(b2.max.approx_equal({ 1.0f, -2.0f, 3.0f }));
        constexpr auto b3 = nnm::AlignedBoxF::from_bounding_sphere({ { 1.0f, -2.0f, 3.0f }, 1.5f });
        TEST_ASSERT(b3.min.approx_equal({ -0.5f, -3.5f, 1.5f }));
        TEST_ASSERT(b3.max.approx_equal({ 2.5f, -0.5f, 4.5f }));
    }

    constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
    constexpr nnm::AlignedBoxF b_degen_rect { { -1.0f, -2.0f, 3.0f }, { 1.0f, 0.0f, 3.0f } };
    constexpr nnm::AlignedBoxF b_degen_segment { { 3.0f, -1.0f, 3.0f }, { 3.0f, 2.0f, 3.0f } };
    constexpr nnm::AlignedBoxF b_degen_point { { 1.0f, -2.0f, 3.0f }, { 1.0f, -2.0f, 3.0f } };

    test_section("collapse_rectangle");
    {
        constexpr std::optional<nnm::Rectangle3f> r1 = b1.collapse_rectangle();
        TEST_ASSERT_FALSE(r1.has_value());
        constexpr std::optional<nnm::Rectangle3f> r2 = b_degen_rect.collapse_rectangle();
        TEST_ASSERT(
            r2.has_value() && r2->coincident({ { 0.0f, -1.0f, 3.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } }));
        constexpr std::optional<nnm::Rectangle3f> r3 = b_degen_segment.collapse_rectangle();
        TEST_ASSERT(
            r3.has_value() && r3->coincident({ { 3.0f, 0.5f, 3.0f }, { 0.0f, 1.5f, 0.0f }, { 0.0f, 0.0f, 0.0f } }));
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
        TEST_ASSERT(r3.has_value() && r3->coincident({ { 3.0f, -1.0f, 3.0f }, { 3.0f, 2.0f, 3.0f } }));
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

        TEST_ASSERT(vertices_contains_approx({ -1.0f, -3.0f, 4.0f }));
        TEST_ASSERT(vertices_contains_approx({ 2.0f, -3.0f, 4.0f }));
        TEST_ASSERT(vertices_contains_approx({ -1.0f, -3.0f, 0.5f }));
        TEST_ASSERT(vertices_contains_approx({ 2.0f, -3.0f, 0.5f }));
        TEST_ASSERT(vertices_contains_approx({ -1.0f, 2.0f, 4.0f }));
        TEST_ASSERT(vertices_contains_approx({ 2.0f, 2.0f, 4.0f }));
        TEST_ASSERT(vertices_contains_approx({ -1.0f, 2.0f, 0.5f }));
        TEST_ASSERT(vertices_contains_approx({ 2.0f, 2.0f, 0.5f }));
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

        TEST_ASSERT(edges_contains_coincident({ { -1.0f, -3.0f, 4.0f }, { -1.0f, -3.0f, 0.5f } }));
        TEST_ASSERT(edges_contains_coincident({ { -1.0f, -3.0f, 4.0f }, { 2.0f, -3.0f, 4.0f } }));
        TEST_ASSERT(edges_contains_coincident({ { 2.0f, -3.0f, 4.0f }, { 2.0f, -3.0f, 0.5f } }));
        TEST_ASSERT(edges_contains_coincident({ { 2.0f, -3.0f, 0.5f }, { -1.0f, -3.0f, 0.5f } }));
        TEST_ASSERT(edges_contains_coincident({ { -1.0f, 2.0f, 4.0f }, { -1.0f, -3.0f, 4.0f } }));
        TEST_ASSERT(edges_contains_coincident({ { 2.0f, 2.0f, 4.0f }, { 2.0f, -3.0f, 4.0f } }));
        TEST_ASSERT(edges_contains_coincident({ { -1.0f, 2.0f, 0.5f }, { -1.0f, -3.0f, 0.5f } }));
        TEST_ASSERT(edges_contains_coincident({ { 2.0f, 2.0f, 0.5f }, { 2.0f, -3.0f, 0.5f } }));
        TEST_ASSERT(edges_contains_coincident({ { 2.0f, 2.0f, 4.0f }, { 2.0f, 2.0f, 0.5f } }));
        TEST_ASSERT(edges_contains_coincident({ { 2.0f, 2.0f, 4.0f }, { -1.0f, 2.0f, 4.0f } }));
        TEST_ASSERT(edges_contains_coincident({ { -1.0f, 2.0f, 4.0f }, { -1.0f, 2.0f, 0.5f } }));
        TEST_ASSERT(edges_contains_coincident({ { 2.0f, 2.0f, 0.5f }, { -1.0f, 2.0f, 0.5f } }));
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

        TEST_ASSERT(faces_contains_coincident({ { 0.5f, 2.0f, 2.25f }, { 1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.75f } }));
        TEST_ASSERT(
            faces_contains_coincident({ { -1.0f, -0.5f, 2.25f }, { 0.0f, 2.5f, 0.0f }, { 0.0f, 0.0f, 1.75f } }));
        TEST_ASSERT(faces_contains_coincident({ { 0.5f, -3.0f, 2.25f }, { 1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.75f } }));
        TEST_ASSERT(faces_contains_coincident({ { 2.0f, -0.5f, 2.25f }, { 0.0f, 2.5f, 0.0f }, { 0.0f, 0.0f, 1.75f } }));
        TEST_ASSERT(faces_contains_coincident({ { 0.5f, -0.5f, 4.0f }, { 1.5f, 0.0f, 0.0f }, { 0.0f, 2.5f, 0.0f } }));
        TEST_ASSERT(faces_contains_coincident({ { 0.5f, -0.5f, 0.5f }, { 1.5f, 0.0f, 0.0f }, { 0.0f, 2.5f, 0.0f } }));
    }

    test_section("size");
    {
        constexpr auto s = b1.size();
        TEST_ASSERT(s.approx_equal({ 3.0f, 5.0f, 3.5f }));
    }

    test_section("volume");
    {
        constexpr auto v = b1.volume();
        TEST_ASSERT(nnm::approx_equal(v, 52.5f));
    }

    test_section("surface_area");
    {
        constexpr auto s = b1.surface_area();
        TEST_ASSERT(nnm::approx_equal(s, 86.0f));
    }

    test_section("extend_bounding");
    {
        constexpr auto r1 = b1.extend_bounding(nnm::Point3f::zero());
        TEST_ASSERT(r1.approx_equal({ { -1.0f, -3.0f, 0.0f }, { 2.0f, 2.0f, 4.0f } }));
        constexpr auto r2 = b1.extend_bounding({ 1.0f, 1.0f, 1.0f });
        TEST_ASSERT(r2.approx_equal(b1));
        constexpr auto r3 = b1.extend_bounding({ 100.0f, 200.0f, 300.0f });
        TEST_ASSERT(r3.approx_equal({ b1.min, { 100.0f, 200.0f, 300.0f } }));
        constexpr auto r4 = b1.extend_bounding({ -100.0f, -200.0f, -300.0f });
        TEST_ASSERT(r4.approx_equal({ { -100.0f, -200.0f, -300.0f }, b1.max }));
    }

    test_section("contains");
    {
        constexpr auto r1 = b1.contains(nnm::Point3f::zero());
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = b1.contains(b1.min);
        TEST_ASSERT(r2);
        constexpr auto r3 = b1.contains({ 1.0f, 1.0f, 1.0f });
        TEST_ASSERT(r3);
        constexpr auto r4 = b1.contains({ 100.0f, 200.0f, 300.0f });
        TEST_ASSERT_FALSE(r4);
    }

    test_section("center");
    {
        constexpr auto r1 = b1.center();
        TEST_ASSERT(r1.approx_equal({ 0.5f, -0.5f, 2.25f }));
    }

    test_section("approx_equal");
    {
        constexpr auto r1 = b1.approx_equal(b1);
        TEST_ASSERT(r1);
        constexpr auto r2 = b1.approx_equal({ { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } });
        TEST_ASSERT(r2);
        constexpr auto r3 = b1.approx_equal({ { -1.0f, -3.0f, 0.5f }, { 2.0f, 1.0f, 4.0f } });
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4 = b1.approx_equal({ { 1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } });
        TEST_ASSERT_FALSE(r4);
    }

    test_section("distance_sqrd(const Vector3&)");
    {
        constexpr float r1 = b1.distance_sqrd(nnm::Point3f::zero());
        TEST_ASSERT(nnm::approx_equal(r1, 0.25f));
        constexpr float r2 = b1.distance_sqrd({ 1.0f, 1.0f, 0.5f });
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3 = b1.distance_sqrd({ 1.0f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_zero(r3));
        constexpr float r4 = b1.distance_sqrd({ 10.0f, 10.0f, 10.0f });
        TEST_ASSERT(nnm::approx_equal(r4, 164.0f));
    }

    test_section("distance_sqrd(const Triangle3&)");
    {
        constexpr float r1
            = b1.distance_sqrd(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 3.0f, -2.0f }));
        TEST_ASSERT(nnm::approx_equal(r1, 0.25f));
        constexpr float r2
            = b1.distance_sqrd(nnm::Triangle3f({ -3.0f, 0.0f, 1.0f }, { -3.0f, -2.0f, 1.0f }, { -3.0f, 0.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_equal(r2, 4.0f));
        constexpr float r3
            = b1.distance_sqrd(nnm::Triangle3f({ 10.0f, 0.0f, 1.0f }, { 0.0f, -10.0f, 1.0f }, { -10.0f, 0.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_zero(r3));
    }

    test_section("distance(const Plane&)");
    {
        constexpr float r1 = b1.distance_sqrd(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_equal(r1, 0.25f));
        constexpr float r2 = b1.distance_sqrd(nnm::PlaneF::xz());
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3 = b1.distance_sqrd(nnm::PlaneF({ -3.0f, 100.0f, -100.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(nnm::approx_equal(r3, 4.0f));
    }

    test_section("distance(const Vector3&)");
    {
        const float r1 = b1.distance(nnm::Point3f::zero());
        TEST_ASSERT(nnm::approx_equal(r1, 0.5f));
        const float r2 = b1.distance({ 1.0f, 1.0f, 0.5f });
        TEST_ASSERT(nnm::approx_zero(r2));
        const float r3 = b1.distance({ 1.0f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_zero(r3));
        const float r4 = b1.distance({ 10.0f, 10.0f, 10.0f });
        TEST_ASSERT(nnm::approx_equal(r4, 12.8062484749f));
    }

    test_section("distance(const Line3&)");
    {
        const float r1 = b1.distance(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(r1, 0.5f));
        const float r2 = b1.distance(nnm::Line3f::axis_z());
        TEST_ASSERT(nnm::approx_zero(r2));
    }

    test_section("distance(const Ray3&)");
    {
        const float r1 = b1.distance(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT(nnm::approx_equal(r1, 0.5f));
        const float r2 = b1.distance(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_z()));
        TEST_ASSERT(nnm::approx_zero(r2));
        const float r3 = b1.distance(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_z()));
        TEST_ASSERT(nnm::approx_equal(r3, 0.5f));
    }

    test_section("distance(const Segment3&)");
    {
        const float r1 = b1.distance(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 100.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(r1, 0.5f));
        const float r2 = b1.distance(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 100.0f }));
        TEST_ASSERT(nnm::approx_zero(r2));
        const float r3 = b1.distance(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -100.0f }));
        TEST_ASSERT(nnm::approx_equal(r3, 0.5f));
    }

    test_section("distance(const Plane&)");
    {
        constexpr float r1 = b1.distance(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_equal(r1, 0.5f));
        constexpr float r2 = b1.distance(nnm::PlaneF::xz());
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3 = b1.distance(nnm::PlaneF({ -3.0f, 100.0f, -100.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(nnm::approx_equal(r3, 2.0f));
    }

    test_section("distance(const Triangle3&)");
    {
        const float r1
            = b1.distance(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 3.0f, -2.0f }));
        TEST_ASSERT(nnm::approx_equal(r1, 0.5f));
        const float r2
            = b1.distance(nnm::Triangle3f({ -3.0f, 0.0f, 1.0f }, { -3.0f, -2.0f, 1.0f }, { -3.0f, 0.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_equal(r2, 2.0f));
        const float r3
            = b1.distance(nnm::Triangle3f({ 10.0f, 0.0f, 1.0f }, { 0.0f, -10.0f, 1.0f }, { -10.0f, 0.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_zero(r3));
    }

    // TODO: here
    test_section("distance(const Rectangle3&)");
    {
    }

    // TODO: here
    test_section("distance(const Sphere&)");

    // TODO: here
    test_section("distance(const AlignedBox&)");

    // TODO: here
    test_section("distance(const Box&)");

    test_section("intersects(const Line3&)");
    {
        constexpr auto r1 = b1.intersects(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = b1.intersects(nnm::Line3f::axis_z());
        TEST_ASSERT(r2);
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr auto r1 = b1.intersects(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = b1.intersects(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_z() });
        TEST_ASSERT(r2);
        constexpr auto r3 = b1.intersects(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_z() });
        TEST_ASSERT_FALSE(r3);
    }

    test_section("intersects(const Segment3&)");
    {
        constexpr bool r1 = b1.intersects(nnm::Segment3f { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } });
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1.intersects(nnm::Segment3f { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } });
        TEST_ASSERT(r2);
        constexpr bool r3 = b1.intersects(nnm::Segment3f { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 100.0f } });
        TEST_ASSERT(r3);
        constexpr bool r4 = b1.intersects(nnm::Segment3f { { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.5f } });
        TEST_ASSERT(r4);
    }

    test_section("intersects(const Plane&)");
    {
        constexpr bool r1 = b1.intersects(nnm::PlaneF::xy());
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1.intersects(nnm::PlaneF::xz());
        TEST_ASSERT(r2);
    }

    test_section("intersects(const Triangle3&)");
    {
        const bool r1
            = b1.intersects(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT_FALSE(r1);
        const bool r2
            = b1.intersects(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r2);
        const bool r3
            = b1.intersects(nnm::Triangle3f({ 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f }));
        TEST_ASSERT(r3);
        const bool r4
            = b1.intersects(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 1000.0f }, { -1.0f, 0.0f, 1000.0f }));
        TEST_ASSERT(r4);
    }

    test_section("intersects(const Rectangle3&)");
    {
        constexpr bool r1
            = b1.intersects(nnm::Rectangle3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2
            = b1.intersects(nnm::Rectangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT(r2);
        constexpr bool r3
            = b1.intersects(nnm::Rectangle3f({ 0.0f, 0.0f, 50.0f }, { 100.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -100.0f }));
        TEST_ASSERT(r3);
        constexpr bool r4
            = b1.intersects(nnm::Rectangle3f({ 0.0f, 0.0f, 2.0f }, { -0.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT(r4);
    }

    test_section("intersects(const Sphere&)");
    {
        constexpr bool r1 = b1.intersects(nnm::SphereF({ 0.0f, 0.0f, 0.0f }, 0.1f));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1.intersects(nnm::SphereF({ 0.0f, 0.0f, 0.0f }, 2.0f));
        TEST_ASSERT(r2);
        constexpr bool r3 = b1.intersects(nnm::SphereF({ 0.0f, 0.0f, 2.0f }, 0.5f));
        TEST_ASSERT(r3);
        constexpr bool r4 = b1.intersects(nnm::SphereF({ 0.0f, 0.0f, 10.0f }, 100.0f));
        TEST_ASSERT(r4);
    }

    test_section("intersects(const AlignedBox&)");
    {
        constexpr bool r1 = b1.intersects(nnm::AlignedBoxF({ -1.0f, -1.0f, -2.0f }, { 1.0f, 1.0f, 0.0f }));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1.intersects(nnm::AlignedBoxF({ -1.0f, -1.0f, -10.0f }, { 1.0f, 1.0f, 2.0f }));
        TEST_ASSERT(r2);
        constexpr bool r3 = b1.intersects(nnm::AlignedBoxF({ -0.5f, -1.0f, 1.0f }, { 1.0f, 2.0f, 3.0f }));
        TEST_ASSERT(r3);
        constexpr bool r4 = b1.intersects(nnm::AlignedBoxF({ -100.0f, -100.0f, -100.0f }, { 100.0f, 100.0f, 100.0f }));
        TEST_ASSERT(r4);
    }

    test_section("surface_intersections(const Line3&)");
    {
        constexpr nnm::PointSet<nnm::Point3f, 2> r1 = b1.surface_intersections(nnm::Line3f::axis_x());
        TEST_ASSERT(r1.empty())
        ;constexpr nnm::PointSet<nnm::Point3f, 2> r2 = b1.surface_intersections(nnm::Line3f::axis_z());
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 0.5f }, { 0.0f, 0.0f, 4.0f } }));
    }

    test_section("surface_intersections(const Ray3&)");
    {
        constexpr nnm::PointSet<nnm::Point3f, 2> r1
            = b1.surface_intersections(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT(r1.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r2
            = b1.surface_intersections(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_z() });
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 4.0f }, { 0.0f, 0.0f, 0.5f } }));
        constexpr nnm::PointSet<nnm::Point3f, 2> r3
            = b1.surface_intersections(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_z() });
        TEST_ASSERT(r3.empty());
    }

    test_section("surface_intersections(const Segment3&)");
    {
        constexpr nnm::PointSet<nnm::Point3f, 2> r1
            = b1.surface_intersections(nnm::Segment3f { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } });
        TEST_ASSERT(r1.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r2
            = b1.surface_intersections(nnm::Segment3f { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } });
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 0.5f } }));
        constexpr nnm::PointSet<nnm::Point3f, 2> r3
            = b1.surface_intersections(nnm::Segment3f { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 100.0f } });
        TEST_ASSERT(r3.approx_equal({ { 0.0f, 0.0f, 0.5f }, { 0.0f, 0.0f, 4.0f } }));
        constexpr nnm::PointSet<nnm::Point3f, 2> r4
            = b1.surface_intersections(nnm::Segment3f { { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.5f } });
        TEST_ASSERT(r4.empty());
    }

    test_section("intersection(const AlignedBox&)");
    {
        constexpr std::optional<nnm::AlignedBoxF> r1
            = b1.intersection(nnm::AlignedBoxF({ -1.0f, -1.0f, -2.0f }, { 1.0f, 1.0f, 0.0f }));
        TEST_ASSERT_FALSE(r1.has_value());
        constexpr std::optional<nnm::AlignedBoxF> r2
            = b1.intersection(nnm::AlignedBoxF({ -1.0f, -1.0f, -10.0f }, { 1.0f, 1.0f, 2.0f }));
        TEST_ASSERT(r2.has_value() && r2->approx_equal({ { -1.0f, -1.0f, 0.5f }, { 1.0f, 1.0f, 2.0f } }));
        constexpr std::optional<nnm::AlignedBoxF> r3
            = b1.intersection(nnm::AlignedBoxF({ -0.5f, -1.0f, 1.0f }, { 1.0f, 2.0f, 3.0f }));
        TEST_ASSERT(r3.has_value() && r3->approx_equal({ { -0.5f, -1.0f, 1.0f }, { 1.0f, 2.0f, 3.0f } }));
        constexpr std::optional<nnm::AlignedBoxF> r4
            = b1.intersection(nnm::AlignedBoxF({ -100.0f, -100.0f, -100.0f }, { 100.0f, 100.0f, 100.0f }));
        TEST_ASSERT(r4.has_value() && r4->approx_equal({ { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } }));
    }

    test_section("valid");
    {
        constexpr bool r1 = b1.valid();
        TEST_ASSERT(r1);
        constexpr bool r2 = nnm::AlignedBoxF({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }).valid();
        TEST_ASSERT(r2);
        constexpr bool r3 = nnm::AlignedBoxF({ 1.0f, 1.0f, 1.0f }, { 1.0f, -1.0f, 2.0f }).valid();
        TEST_ASSERT_FALSE(r3);
        constexpr bool r4 = nnm::AlignedBoxF({ 2.0f, 2.0f, 4.0f }, { -1.0f, -3.0f, 0.5f }).valid();
        TEST_ASSERT_FALSE(r4);
    }

    test_section("translate");
    {
        constexpr nnm::Vector3f offset { -1.0f, 2.0f, -3.0f };
        constexpr nnm::AlignedBoxF r1 = b1.translate(offset);
        TEST_ASSERT(r1.approx_equal({ b1.min.translate(offset), b1.max.translate(offset) }));
    }

    test_section("rotate_axis_angle_at");
    {
        constexpr nnm::Point3f origin { -1.0f, 2.0f, -3.0f };
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = 2.0f * nnm::pi<float>() / 3.0f;
        const nnm::AlignedBoxF r1 = b1.rotate_axis_angle_at(origin, axis, angle);
        TEST_ASSERT(r1.approx_equal(
            { b1.min.rotate_axis_angle_at(origin, axis, angle), b1.max.rotate_axis_angle_at(origin, axis, angle) }));
    }

    test_section("rotate_axis_angle");
    {
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = 2.0f * nnm::pi<float>() / 3.0f;
        const nnm::AlignedBoxF r1 = b1.rotate_axis_angle(axis, angle);
        TEST_ASSERT(r1.approx_equal({ b1.min.rotate_axis_angle(axis, angle), b1.max.rotate_axis_angle(axis, angle) }));
    }

    test_section("rotate_quaternion_at");
    {
        constexpr nnm::Point3f origin { -1.0f, 2.0f, -3.0f };
        constexpr nnm::QuaternionF quat { 0.0f, 0.866025447f, 0.0f, 0.5f };
        constexpr nnm::AlignedBoxF r1 = b1.rotate_quaternion_at(origin, quat);
        TEST_ASSERT(
            r1.approx_equal({ b1.min.rotate_quaternion_at(origin, quat), b1.max.rotate_quaternion_at(origin, quat) }));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::QuaternionF quat { 0.0f, 0.866025447f, 0.0f, 0.5f };
        constexpr nnm::AlignedBoxF r1 = b1.rotate_quaternion(quat);
        TEST_ASSERT(r1.approx_equal({ b1.min.rotate_quaternion(quat), b1.max.rotate_quaternion(quat) }));
    }

    test_section("scale_at");
    {
        constexpr nnm::Point3f origin { -1.0f, 2.0f, -3.0f };
        constexpr nnm::Vector3f factor { 0.5f, -1.5f, 2.0f };
        constexpr nnm::AlignedBoxF r1 = b1.scale_at(origin, factor);
        TEST_ASSERT(r1.approx_equal({ b1.min.scale_at(origin, factor), b1.max.scale_at(origin, factor) }));
    }

    test_section("scale");
    {
        constexpr nnm::Vector3f factor { 0.5f, -1.5f, 2.0f };
        constexpr nnm::AlignedBoxF r1 = b1.scale(factor);
        TEST_ASSERT(r1.approx_equal({ b1.min.scale(factor), b1.max.scale(factor) }));
    }

    constexpr nnm::AlignedBoxF b2 { { -3.0f, -0.5f, 1.0f }, { 10.0f, 0.0f, 5.0f } };

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr bool r1 = b1 == b1;
        TEST_ASSERT(r1);
        constexpr bool r2 = b1 == b2;
        TEST_ASSERT_FALSE(r2);
    }

    test_section("operator!=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr bool r1 = b1 != b1;
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b1 != b2;
        TEST_ASSERT(r2);
    }

    test_section("operator<");
    {
        constexpr bool r1 = b1 < b2;
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = b2 < b1;
        TEST_ASSERT(r2);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr bool r3 = b1 < b1;
        TEST_ASSERT_FALSE(r3);
    }
}


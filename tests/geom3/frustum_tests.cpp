#include "tests.hpp"

void frustum_tests()
{
    test_case("Frustum");

    test_section("Frustum()");
    {
        constexpr nnm::FrustumF f { };
        TEST_ASSERT(f.near_plane.approx_equal(nnm::PlaneF()));
        TEST_ASSERT(f.far_plane.approx_equal(nnm::PlaneF()));
        TEST_ASSERT(f.left_plane.approx_equal(nnm::PlaneF()));
        TEST_ASSERT(f.right_plane.approx_equal(nnm::PlaneF()));
        TEST_ASSERT(f.bottom_plane.approx_equal(nnm::PlaneF()));
        TEST_ASSERT(f.top_plane.approx_equal(nnm::PlaneF()));
    }

    test_section("Frustum(const Plane&, const Plane&, const Plane&, const Plane&, const Plane&, const Plane&)");
    {
        constexpr nnm::FrustumF f {
            nnm::PlaneF({ 1.0f, -1.0f, 3.0f }, nnm::Vector3f::axis_y()),
            nnm::PlaneF({ 1.0f, 8.0f, 3.0f }, -nnm::Vector3f::axis_y()),
            nnm::PlaneF({ 2.0f, -1.0f, 3.0f }, { -0.7071067812f, 0.7071067812f, 0.0f }),
            nnm::PlaneF({ 0.0f, -1.0f, 3.0f }, { 0.7071067812f, 0.7071067812f, 0.0f }),
            nnm::PlaneF({ 1.0f, -1.0f, 2.5f }, { 0.0f, 0.4472135955f, 0.8944271910f }),
            nnm::PlaneF({ 1.0f, -1.0f, 3.5f }, { 0.0f, 0.4472135955f, -0.8944271910f })
        };
        TEST_ASSERT(f.near_plane.approx_equal(nnm::PlaneF({ 1.0f, -1.0f, 3.0f }, nnm::Vector3f::axis_y())));
        TEST_ASSERT(f.far_plane.approx_equal(nnm::PlaneF({ 1.0f, 8.0f, 3.0f }, -nnm::Vector3f::axis_y())));
        TEST_ASSERT(
            f.left_plane.approx_equal(nnm::PlaneF({ 2.0f, -1.0f, 3.0f }, { -0.7071067812f, 0.7071067812f, 0.0f })));
        TEST_ASSERT(
            f.right_plane.approx_equal(nnm::PlaneF({ 0.0f, -1.0f, 3.0f }, { 0.7071067812f, 0.7071067812f, 0.0f })));
        TEST_ASSERT(
            f.bottom_plane.approx_equal(nnm::PlaneF({ 1.0f, -1.0f, 2.5f }, { 0.0f, 0.4472135955f, 0.8944271910f })));
        TEST_ASSERT(
            f.top_plane.approx_equal(nnm::PlaneF({ 1.0f, -1.0f, 3.5f }, { 0.0f, 0.4472135955f, -0.8944271910f })));
    }

    test_section("from_camera_left_hand");
    {
        const auto f = nnm::FrustumF::from_camera_left_hand(
            { 1.0f, -2.0f, 3.0f },
            nnm::Vector3f::axis_y(),
            nnm::Vector3f::axis_z(),
            0.927295218f, // ~53 deg vertical which is ~90 deg horizontal for 2:1
            2.0f,
            1.0f,
            10.0f);
        TEST_ASSERT(f.near_plane.approx_equal(nnm::PlaneF({ 1.0f, -1.0f, 3.0f }, nnm::Vector3f::axis_y())));
        TEST_ASSERT(f.far_plane.approx_equal(nnm::PlaneF({ 1.0f, 8.0f, 3.0f }, -nnm::Vector3f::axis_y())));
        TEST_ASSERT(
            f.left_plane.approx_equal(nnm::PlaneF({ 2.0f, -1.0f, 3.0f }, { -0.7071067812f, 0.7071067812f, 0.0f })));
        TEST_ASSERT(
            f.right_plane.approx_equal(nnm::PlaneF({ 0.0f, -1.0f, 3.0f }, { 0.7071067812f, 0.7071067812f, 0.0f })));
        TEST_ASSERT(
            f.bottom_plane.approx_equal(nnm::PlaneF({ 1.0f, -1.0f, 2.5f }, { 0.0f, 0.4472135955f, 0.8944271910f })));
        TEST_ASSERT(
            f.top_plane.approx_equal(nnm::PlaneF({ 1.0f, -1.0f, 3.5f }, { 0.0f, 0.4472135955f, -0.8944271910f })));
    }

    test_section("from_camera_right_hand");
    {
        const auto f = nnm::FrustumF::from_camera_right_hand(
            { 1.0f, -2.0f, 3.0f },
            nnm::Vector3f::axis_y(),
            nnm::Vector3f::axis_z(),
            0.927295218f, // ~53 deg vertical which is ~90 deg horizontal for 2:1
            2.0f,
            1.0f,
            10.0f);
        TEST_ASSERT(f.near_plane.approx_equal(nnm::PlaneF({ 1.0f, -1.0f, 3.0f }, nnm::Vector3f::axis_y())));
        TEST_ASSERT(f.far_plane.approx_equal(nnm::PlaneF({ 1.0f, 8.0f, 3.0f }, -nnm::Vector3f::axis_y())));
        TEST_ASSERT(
            f.left_plane.approx_equal(nnm::PlaneF({ 0.0f, -1.0f, 3.0f }, { 0.7071067812f, 0.7071067812f, 0.0f })));
        TEST_ASSERT(
            f.right_plane.approx_equal(nnm::PlaneF({ 2.0f, -1.0f, 3.0f }, { -0.7071067812f, 0.7071067812f, 0.0f })));
        TEST_ASSERT(
            f.bottom_plane.approx_equal(nnm::PlaneF({ 1.0f, -1.0f, 2.5f }, { 0.0f, 0.4472135955f, 0.8944271910f })));
        TEST_ASSERT(
            f.top_plane.approx_equal(nnm::PlaneF({ 1.0f, -1.0f, 3.5f }, { 0.0f, 0.4472135955f, -0.8944271910f })));
    }

    constexpr nnm::FrustumF f1 {
        nnm::PlaneF({ 1.0f, -1.0f, 3.0f }, nnm::Vector3f::axis_y()),
        nnm::PlaneF({ 1.0f, 2.0f, 3.0f }, -nnm::Vector3f::axis_y()),
        nnm::PlaneF({ 0.0f, -1.0f, 3.0f }, { 0.7071067812f, 0.7071067812f, 0.0f }),
        nnm::PlaneF({ 2.0f, -1.0f, 3.0f }, { -0.7071067812f, 0.7071067812f, 0.0f }),
        nnm::PlaneF({ 1.0f, -1.0f, 2.5f }, { 0.0f, 0.4472135955f, 0.8944271910f }),
        nnm::PlaneF({ 1.0f, -1.0f, 3.5f }, { 0.0f, 0.4472135955f, -0.8944271910f })
    };

    test_section("vertex");
    {
        std::vector<nnm::Point3f> vertices;
        constexpr nnm::Point3f v0 = f1.vertex(0);
        vertices.push_back(v0);
        constexpr nnm::Point3f v1 = f1.vertex(1);
        vertices.push_back(v1);
        constexpr nnm::Point3f v2 = f1.vertex(2);
        vertices.push_back(v2);
        constexpr nnm::Point3f v3 = f1.vertex(3);
        vertices.push_back(v3);
        constexpr nnm::Point3f v4 = f1.vertex(4);
        vertices.push_back(v4);
        constexpr nnm::Point3f v5 = f1.vertex(5);
        vertices.push_back(v5);
        constexpr nnm::Point3f v6 = f1.vertex(6);
        vertices.push_back(v6);
        constexpr nnm::Point3f v7 = f1.vertex(7);
        vertices.push_back(v7);

        auto vertices_contains_approx = [&vertices](const nnm::Point3f& vertex) {
            return std::find_if(
                       vertices.begin(),
                       vertices.end(),
                       [&vertex](const nnm::Point3f& v) { return v.approx_equal(vertex); })
                != vertices.end();
        };

        TEST_ASSERT(vertices_contains_approx({ 0.0f, -1.0f, 2.5f }));
        TEST_ASSERT(vertices_contains_approx({ 0.0f, -1.0f, 3.5f }));
        TEST_ASSERT(vertices_contains_approx({ 2.0f, -1.0f, 2.5f }));
        TEST_ASSERT(vertices_contains_approx({ 2.0f, -1.0f, 3.5f }));
        TEST_ASSERT(vertices_contains_approx({ -3.0f, 2.0f, 1.0f }));
        TEST_ASSERT(vertices_contains_approx({ -3.0f, 2.0f, 5.0f }));
        TEST_ASSERT(vertices_contains_approx({ 5.0f, 2.0f, 1.0f }));
        TEST_ASSERT(vertices_contains_approx({ 5.0f, 2.0f, 5.0f }));
    }

    test_section("edge");
    {
        std::vector<nnm::Segment3f> edges;
        constexpr nnm::Segment3f e0 = f1.edge(0);
        edges.push_back(e0);
        constexpr nnm::Segment3f e1 = f1.edge(1);
        edges.push_back(e1);
        constexpr nnm::Segment3f e2 = f1.edge(2);
        edges.push_back(e2);
        constexpr nnm::Segment3f e3 = f1.edge(3);
        edges.push_back(e3);
        constexpr nnm::Segment3f e4 = f1.edge(4);
        edges.push_back(e4);
        constexpr nnm::Segment3f e5 = f1.edge(5);
        edges.push_back(e5);
        constexpr nnm::Segment3f e6 = f1.edge(6);
        edges.push_back(e6);
        constexpr nnm::Segment3f e7 = f1.edge(7);
        edges.push_back(e7);
        constexpr nnm::Segment3f e8 = f1.edge(8);
        edges.push_back(e8);
        constexpr nnm::Segment3f e9 = f1.edge(9);
        edges.push_back(e9);
        constexpr nnm::Segment3f e10 = f1.edge(10);
        edges.push_back(e10);
        constexpr nnm::Segment3f e11 = f1.edge(11);
        edges.push_back(e11);

        auto edges_contains_coincident = [&edges](const nnm::Segment3f& edge) {
            return std::find_if(
                       edges.begin(), edges.end(), [&edge](const nnm::Segment3f& e) { return e.coincident(edge); })
                != edges.end();
        };

        TEST_ASSERT(edges_contains_coincident({ f1.vertex(0), f1.vertex(1) }));
        TEST_ASSERT(edges_contains_coincident({ f1.vertex(2), f1.vertex(3) }));
        TEST_ASSERT(edges_contains_coincident({ f1.vertex(0), f1.vertex(2) }));
        TEST_ASSERT(edges_contains_coincident({ f1.vertex(1), f1.vertex(3) }));
        TEST_ASSERT(edges_contains_coincident({ f1.vertex(4), f1.vertex(5) }));
        TEST_ASSERT(edges_contains_coincident({ f1.vertex(6), f1.vertex(7) }));
        TEST_ASSERT(edges_contains_coincident({ f1.vertex(4), f1.vertex(6) }));
        TEST_ASSERT(edges_contains_coincident({ f1.vertex(5), f1.vertex(7) }));
        TEST_ASSERT(edges_contains_coincident({ f1.vertex(0), f1.vertex(4) }));
        TEST_ASSERT(edges_contains_coincident({ f1.vertex(1), f1.vertex(5) }));
        TEST_ASSERT(edges_contains_coincident({ f1.vertex(2), f1.vertex(6) }));
        TEST_ASSERT(edges_contains_coincident({ f1.vertex(3), f1.vertex(7) }));
    }

    test_section("contains");
    {
        constexpr bool r1 = f1.contains(nnm::Point3f::zero());
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = f1.contains({ 0.0f, 0.0f, 3.0f });
        TEST_ASSERT(r2);
        constexpr bool r3 = f1.contains(f1.vertex(6));
        TEST_ASSERT(r3);
        constexpr bool r4 = f1.contains({ 1.0f, -2.0f, 3.0f });
        TEST_ASSERT_FALSE(r4);
        constexpr bool r5 = f1.contains({ 4.0f, 1.5f, 2.0f });
        TEST_ASSERT(r5);
        constexpr bool r6 = f1.contains({ 1.0f, 3.0f, 3.0f });
        TEST_ASSERT_FALSE(r6);
    }

    test_section("intersects(const Line3&)");
    {
        constexpr bool r1 = f1.intersects(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = f1.intersects(nnm::Line3f::axis_z());
        TEST_ASSERT(r2);
        constexpr bool r3 = f1.intersects(nnm::Line3f::axis_y_offset(1.0f, 3.0f));
        TEST_ASSERT(r3);
        constexpr bool r4 = f1.intersects(nnm::Line3f::axis_z_offset(0.0f, 2.0f));
        TEST_ASSERT(r4);
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr bool r1 = f1.intersects(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = f1.intersects(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_z()));
        TEST_ASSERT(r2);
        constexpr bool r3 = f1.intersects(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_z()));
        TEST_ASSERT_FALSE(r3);
        constexpr bool r4 = f1.intersects(nnm::Ray3f({ 1.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_y()));
        TEST_ASSERT(r4);
        constexpr bool r5 = f1.intersects(nnm::Ray3f({ 1.0f, -2.0f, 3.0f }, -nnm::Vector3f::axis_y()));
        TEST_ASSERT_FALSE(r5);
        constexpr bool r6 = f1.intersects(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, nnm::Vector3f::axis_z()));
        TEST_ASSERT(r6);
    }

    test_section("intersects(const Segment3&)");
    {
        constexpr bool r1 = f1.intersects(nnm::Segment3(nnm::Point3f::zero(), { 100.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = f1.intersects(nnm::Segment3(nnm::Point3f::zero(), { 0.0f, 0.0f, 100.0f }));
        TEST_ASSERT(r2);
        constexpr bool r3 = f1.intersects(nnm::Segment3f(nnm::Point3f::zero(), { 0.0f, 0.0f, -100.0f }));
        TEST_ASSERT_FALSE(r3);
        constexpr bool r4 = f1.intersects(nnm::Segment3f({ 1.0f, -2.0f, 3.0f }, { 0.0f, 100.0f, 0.0f }));
        TEST_ASSERT(r4);
        constexpr bool r5 = f1.intersects(nnm::Segment3f({ 1.0f, -2.0f, 3.0f }, { 0.0f, -100.0f, 0.0f }));
        TEST_ASSERT_FALSE(r5);
        constexpr bool r6 = f1.intersects(nnm::Segment3f({ 0.0f, -0.5f, 3.0f }, { 2.0f, 1.5f, 2.0f }));
        TEST_ASSERT(r6);
        constexpr bool r7 = f1.intersects(nnm::Segment3f({ 0.0f, 2.0f, 2.0f }, { 0.0f, 2.0f, 3.0f }));
        TEST_ASSERT(r7);
    }

    test_section("intersects(const Plane&)");
    {
        const bool r1 = f1.intersects(nnm::PlaneF::xy());
        TEST_ASSERT_FALSE(r1);
        const bool r2 = f1.intersects(nnm::PlaneF::xz());
        TEST_ASSERT(r2);
        const bool r3 = f1.intersects(f1.far_plane);
        TEST_ASSERT(r3);
    }

    test_section("intersects(const Triangle3&)");
    {
        constexpr bool r1
            = f1.intersects(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 100.0f, 0.0f, 0.0f }, { 0.0f, 100.0f, 0.0f }));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2
            = f1.intersects(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 100.0f }, { 0.0f, 100.0f, 0.0f }));
        TEST_ASSERT(r2);
        constexpr bool r3
            = f1.intersects(nnm::Triangle3f({ 0.0f, 0.0f, 3.0f }, { 1.0f, 1.75f, 3.0f }, { 2.0f, 1.5f, 2.0f }));
        TEST_ASSERT(r3);
        constexpr bool r4
            = f1.intersects(nnm::Triangle3f({ 0.0f, 2.0f, 2.0f }, { 0.0f, 2.0f, 3.0f }, { 2.0f, 2.0f, 2.0f }));
        TEST_ASSERT(r4);
    }

    test_section("intersects(const Rectangle&)");
    {
        constexpr bool r1 = f1.intersects(nnm::Rectangle3f::from_xy_offset_size(nnm::Point3f::zero(), 100.0f, 100.0f));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = f1.intersects(nnm::Rectangle3f::from_xz_offset_size({ 0.0f, 0.0f, 1.0f }, 4.0f, 4.0f));
        TEST_ASSERT(r2);
        constexpr bool r3
            = f1.intersects(nnm::Rectangle3f::from_xz_offset_size(nnm::Point3f::zero(), 1000.0f, 1000.0f));
        TEST_ASSERT(r3);
        constexpr bool r4 = f1.intersects(nnm::Rectangle3f::from_yz_offset_size({ 0.0f, 1.0f, 3.0f }, 0.5f, 0.1f));
        TEST_ASSERT(r4);
        constexpr bool r5 = f1.intersects(nnm::Rectangle3f::from_xz_offset_size({ 0.0f, 2.0f, 3.0f }, 0.1f, 0.1f));
        TEST_ASSERT(r5);
    }

    test_section("intersects(const Sphere&)");
    {
        constexpr bool r1 = f1.intersects(nnm::SphereF({ 0.0f, 0.0f, 0.0f }, 1.0f));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = f1.intersects(nnm::SphereF({ -1.0f, 0.0f, 0.0f }, 1.0f));
        TEST_ASSERT_FALSE(r2);
        constexpr bool r3 = f1.intersects(nnm::SphereF({ 0.0f, 0.0f, 0.0f }, 1000.0f));
        TEST_ASSERT(r3);
        constexpr bool r4 = f1.intersects(nnm::SphereF({ 0.0f, 0.0f, 0.0f }, 3.0f));
        TEST_ASSERT(r4);
        constexpr bool r5 = f1.intersects(nnm::SphereF({ 0.0f, 1.0f, 3.0f }, 0.1f));
        TEST_ASSERT(r5);
    }

    test_section("intersects(const AlignedBox&)");
    {
        constexpr bool r1
            = f1.intersects(nnm::AlignedBoxF::from_bounding_points({ 0.0f, 0.0f, 0.0f }, { 10.0f, 0.5f, 1.0f }));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2
            = f1.intersects(nnm::AlignedBoxF::from_bounding_points({ -3.0f, -3.0f, -3.0f }, { 3.0f, 3.0f, 3.0f }));
        TEST_ASSERT(r2);
        constexpr bool r3 = f1.intersects(
            nnm::AlignedBoxF::from_bounding_points({ -5.0f, -5.0f, -5.0f }, { 1000.0f, 1000.0f, 1000.0f }));
        TEST_ASSERT(r3);
        constexpr bool r4
            = f1.intersects(nnm::AlignedBoxF::from_bounding_points({ 0.0f, 0.0f, 2.0f }, { 2.0f, 1.5f, 3.0f }));
        TEST_ASSERT(r4);
        constexpr bool r5
            = f1.intersects(nnm::AlignedBoxF::from_bounding_points({ -4.0f, 2.0f, -10.0f }, { 7.0f, 4.0f, 10.0f }));
        TEST_ASSERT(r5);
    }

    test_section("intersects(const Box&)");
    {
        constexpr bool r1 = f1.intersects(nnm::BoxF::from_center_size(nnm::Point3f::zero(), { 10.0f, 1.0f, 2.0f }));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = f1.intersects(nnm::BoxF::from_center_size({ 0.0f, 0.0f, 0.0f }, { 4.0f, 1.0f, 6.0f }));
        TEST_ASSERT(r2);
        constexpr bool r3
            = f1.intersects(nnm::BoxF::from_center_size({ 0.0f, 0.0f, 0.0f }, { 1000.0f, 1000.0f, 1000.0f }));
        TEST_ASSERT(r3);
        constexpr bool r4 = f1.intersects(nnm::BoxF::from_center_size({ 1.0f, 1.0f, 3.0f }, { 0.1f, 0.1f, 0.1f }));
        TEST_ASSERT(r4);
        constexpr bool r5 = f1.intersects(nnm::BoxF::from_center_size({ 1.0f, 2.5f, 3.0f }, { 100.0f, 1.0f, 100.0f }));
        TEST_ASSERT(r5);
        constexpr bool r6 = f1.intersects(nnm::BoxF::from_center_size({ 1.0f, 2.5f, 3.0f }, { 100.0f, 0.5f, 100.0f }));
        TEST_ASSERT_FALSE(r6);
    }

    // const auto f2 = nnm::FrustumF::from_camera_right_hand_pos_forward_up_fov_aspect_near_far(
    //     { 5.0f, 2.5f, -1.0f },
    //     (-nnm::Vector3f::axis_y())
    //         .rotate_axis_angle(nnm::Vector3f::axis_x(), -nnm::pi<float>() / 4.0f)
    //         .rotate_axis_angle(nnm::Vector3f::axis_z(), -nnm::pi<float>() / 4.0f),
    //     nnm::Vector3f::axis_z(),
    //     nnm::pi<float>() / 4.0f,
    //     0.5f,
    //     0.5f,
    //     3.5f);
    // std::array<nnm::Vector3f, 8> vertices { f2.vertex(0), f2.vertex(1), f2.vertex(2), f2.vertex(3),
    //                                         f2.vertex(4), f2.vertex(5), f2.vertex(6), f2.vertex(7) };
    constexpr nnm::FrustumF f2 {
        { { 4.75f, 2.25f, -0.646446586f }, { 0.5f, -0.5f, 0.707106769f } },
        { { 3.25f, 0.75f, 1.47487378f }, { 0.5f, 0.5f, -0.707106769f } },
        { { 4.82322311f, 2.17677665f, -0.646446586f }, { -0.793814182f, 0.591011405f, 0.143403217f } },
        { { 4.67677689f, 2.32322335f, -0.646446586f }, { 0.591011405f, -0.793814241f, 0.143403277f } },
        { { 4.6464467f, 2.1464467f, -0.792893171f }, { 0.270598173f, 0.270598173f, 0.923879444f } },
        { { 4.8535533f, 2.3535533f, -0.5f }, { -0.65328145f, -0.65328145f, -0.382683665f } }
    };

    test_section("intersects(const Frustum&)");
    {
        constexpr bool r1 = f1.intersects(f2);
        TEST_ASSERT(r1);
        constexpr bool r2 = f2.intersects(f1);
        TEST_ASSERT(r2);
        constexpr bool r3 = f1.intersects(f1);
        TEST_ASSERT(r3);
        constexpr nnm::FrustumF f3 = f2.translate({ 0.0f, 0.0f, -4.0f });
        constexpr bool r4 = f1.intersects(f3);
        TEST_ASSERT_FALSE(r4);
        constexpr bool r5 = f3.intersects(f1);
        TEST_ASSERT_FALSE(r5);
    }

    test_section("surface_intersections(const Line3&)");
    {
        constexpr nnm::PointSet<nnm::Point3f, 2> r1 = f1.surface_intersections(nnm::Line3f::axis_x());
        TEST_ASSERT(r1.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r2 = f1.surface_intersections(nnm::Line3f::axis_z());
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.0f, 4.0f } }));
    }

    test_section("surface_intersections(const Ray3&)");
    {
        constexpr nnm::PointSet<nnm::Point3f, 2> r1
            = f1.surface_intersections(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT(r1.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r2
            = f1.surface_intersections(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_z()));
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.0f, 4.0f } }));
        constexpr nnm::PointSet<nnm::Point3f, 2> r3
            = f1.surface_intersections(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_z()));
        TEST_ASSERT(r3.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r4
            = f1.surface_intersections(nnm::Ray3f({ 0.0f, 0.0f, 3.0f }, nnm::Vector3f::axis_y()));
        TEST_ASSERT(r4.approx_equal({ { 0.0f, 2.0f, 3.0f } }));
    }

    test_section("surface_intersections(const Segment3&)");
    {
        const nnm::PointSet<nnm::Point3f, 2> r1
            = f1.surface_intersections(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 100.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r1.empty());
        const nnm::PointSet<nnm::Point3f, 2> r2
            = f1.surface_intersections(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 100.0f }));
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.0f, 4.0f } }));
        const nnm::PointSet<nnm::Point3f, 2> r3
            = f1.surface_intersections(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -100.0f }));
        TEST_ASSERT(r3.empty());
        const nnm::PointSet<nnm::Point3f, 2> r4
            = f1.surface_intersections(nnm::Segment3f({ 0.0f, 0.0f, 3.0f }, { 0.0f, 100.0f, 3.0f }));
        TEST_ASSERT(r4.approx_equal({ { 0.0f, 2.0f, 3.0f } }));
        const nnm::PointSet<nnm::Point3f, 2> r5
            = f1.surface_intersections(nnm::Segment3f({ 0.0f, 0.0f, 3.0f }, { 0.0f, 1.0f, 3.0f }));
        TEST_ASSERT(r5.empty());
    }

    test_section("translate");
    {
        constexpr nnm::Vector3f offset { -2.0f, 3.0f, 0.5f };
        constexpr nnm::FrustumF r1 = f1.translate({ -2.0f, 3.0f, 0.5f });
        constexpr nnm::FrustumF e1 { f1.near_plane.translate(offset),   f1.far_plane.translate(offset),
                                     f1.left_plane.translate(offset),   f1.right_plane.translate(offset),
                                     f1.bottom_plane.translate(offset), f1.top_plane.translate(offset) };
        TEST_ASSERT(r1.approx_equal(e1));
    }

    test_section("rotate_axis_angle");
    {
        constexpr nnm::Point3f origin { -2.0f, 3.0f, 0.5f };
        constexpr auto axis = nnm::Vector3f::axis_x();
        constexpr float angle = nnm::pi<float>() / 5.0f;
        const nnm::FrustumF r1 = f1.rotate_axis_angle(axis, angle, origin);
        const nnm::FrustumF e1 { f1.near_plane.rotate_axis_angle_at(origin, axis, angle),
                                 f1.far_plane.rotate_axis_angle_at(origin, axis, angle),
                                 f1.left_plane.rotate_axis_angle_at(origin, axis, angle),
                                 f1.right_plane.rotate_axis_angle_at(origin, axis, angle),
                                 f1.bottom_plane.rotate_axis_angle_at(origin, axis, angle),
                                 f1.top_plane.rotate_axis_angle_at(origin, axis, angle) };
        TEST_ASSERT(r1.approx_equal(e1));
        const nnm::FrustumF r2 = f1.rotate_axis_angle(axis, angle);
        const nnm::FrustumF e2 {
            f1.near_plane.rotate_axis_angle(axis, angle),   f1.far_plane.rotate_axis_angle(axis, angle),
            f1.left_plane.rotate_axis_angle(axis, angle),   f1.right_plane.rotate_axis_angle(axis, angle),
            f1.bottom_plane.rotate_axis_angle(axis, angle), f1.top_plane.rotate_axis_angle(axis, angle)
        };
        TEST_ASSERT(r2.approx_equal(e2));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::Point3f origin { -2.0f, 3.0f, 0.5f };
        constexpr nnm::QuaternionF quat { 0.309017003f, 0.0f, 0.0f, 0.95105654f };
        constexpr nnm::FrustumF r1 = f1.rotate_quaternion(quat, origin);
        constexpr nnm::FrustumF e1 {
            f1.near_plane.rotate_quaternion_at(origin, quat),   f1.far_plane.rotate_quaternion_at(origin, quat),
            f1.left_plane.rotate_quaternion_at(origin, quat),   f1.right_plane.rotate_quaternion_at(origin, quat),
            f1.bottom_plane.rotate_quaternion_at(origin, quat), f1.top_plane.rotate_quaternion_at(origin, quat)
        };
        TEST_ASSERT(r1.approx_equal(e1));
    }

    test_section("scale");
    {
        constexpr nnm::Point3f origin { -2.0f, 3.0f, 0.5f };
        constexpr nnm::Vector3f factor { 1.5f, -0.25f, 3.0f };
        const nnm::FrustumF r1 = f1.scale(factor, origin);
        const nnm::FrustumF e1 { f1.near_plane.scale_at(origin, factor),   f1.far_plane.scale_at(origin, factor),
                                 f1.left_plane.scale_at(origin, factor),   f1.right_plane.scale_at(origin, factor),
                                 f1.bottom_plane.scale_at(origin, factor), f1.top_plane.scale_at(origin, factor) };
        TEST_ASSERT(r1.approx_equal(e1));
        const nnm::FrustumF r2 = f1.scale(factor);
        const nnm::FrustumF e2 { f1.near_plane.scale(factor),   f1.far_plane.scale(factor),
                                 f1.left_plane.scale(factor),   f1.right_plane.scale(factor),
                                 f1.bottom_plane.scale(factor), f1.top_plane.scale(factor) };
        TEST_ASSERT(r2.approx_equal(e2));
    }

    test_section("approx_equal");
    {
        constexpr bool r1 = f1.approx_equal(
            { nnm::PlaneF({ 1.0f, -1.0f, 3.0f }, nnm::Vector3f::axis_y()),
              nnm::PlaneF({ 1.0f, 2.0f, 3.0f }, -nnm::Vector3f::axis_y()),
              nnm::PlaneF({ 0.0f, -1.0f, 3.0f }, { 0.7071067812f, 0.7071067812f, 0.0f }),
              nnm::PlaneF({ 2.0f, -1.0f, 3.0f }, { -0.7071067812f, 0.7071067812f, 0.0f }),
              nnm::PlaneF({ 1.0f, -1.0f, 2.5f }, { 0.0f, 0.4472135955f, 0.8944271910f }),
              nnm::PlaneF({ 1.0f, -1.0f, 3.5f }, { 0.0f, 0.4472135955f, -0.8944271910f }) });
        TEST_ASSERT(r1);
        constexpr bool r2 = f1.approx_equal(f2);
        TEST_ASSERT_FALSE(r2);
    }

    test_section("operator==");
    {
        constexpr bool r1 = f1
            == nnm::FrustumF(nnm::PlaneF({ 1.0f, -1.0f, 3.0f }, nnm::Vector3f::axis_y()),
                             nnm::PlaneF({ 1.0f, 2.0f, 3.0f }, -nnm::Vector3f::axis_y()),
                             nnm::PlaneF({ 0.0f, -1.0f, 3.0f }, { 0.7071067812f, 0.7071067812f, 0.0f }),
                             nnm::PlaneF({ 2.0f, -1.0f, 3.0f }, { -0.7071067812f, 0.7071067812f, 0.0f }),
                             nnm::PlaneF({ 1.0f, -1.0f, 2.5f }, { 0.0f, 0.4472135955f, 0.8944271910f }),
                             nnm::PlaneF({ 1.0f, -1.0f, 3.5f }, { 0.0f, 0.4472135955f, -0.8944271910f }));
        TEST_ASSERT(r1);
        constexpr bool r2 = f1 == f2;
        TEST_ASSERT_FALSE(r2);
    }

    test_section("operator!=");
    {
        constexpr bool r1 = f1
            != nnm::FrustumF(nnm::PlaneF({ 1.0f, -1.0f, 3.0f }, nnm::Vector3f::axis_y()),
                             nnm::PlaneF({ 1.0f, 2.0f, 3.0f }, -nnm::Vector3f::axis_y()),
                             nnm::PlaneF({ 0.0f, -1.0f, 3.0f }, { 0.7071067812f, 0.7071067812f, 0.0f }),
                             nnm::PlaneF({ 2.0f, -1.0f, 3.0f }, { -0.7071067812f, 0.7071067812f, 0.0f }),
                             nnm::PlaneF({ 1.0f, -1.0f, 2.5f }, { 0.0f, 0.4472135955f, 0.8944271910f }),
                             nnm::PlaneF({ 1.0f, -1.0f, 3.5f }, { 0.0f, 0.4472135955f, -0.8944271910f }));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = f1 != f2;
        TEST_ASSERT(r2);
    }

    test_section("operator<");
    {
        constexpr bool r1 = f1
            < nnm::FrustumF(nnm::PlaneF({ 1.0f, -1.0f, 3.0f }, nnm::Vector3f::axis_y()),
                            nnm::PlaneF({ 1.0f, 2.0f, 3.0f }, -nnm::Vector3f::axis_y()),
                            nnm::PlaneF({ 0.0f, -1.0f, 3.0f }, { 0.7071067812f, 0.7071067812f, 0.0f }),
                            nnm::PlaneF({ 2.0f, -1.0f, 3.0f }, { -0.7071067812f, 0.7071067812f, 0.0f }),
                            nnm::PlaneF({ 1.0f, -1.0f, 2.5f }, { 0.0f, 0.4472135955f, 0.8944271910f }),
                            nnm::PlaneF({ 1.0f, -1.0f, 3.5f }, { 0.0f, 0.4472135955f, -0.8944271910f }));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = f1 < f2;
        TEST_ASSERT(r2);
        constexpr bool r3 = f2 < f1;
        TEST_ASSERT_FALSE(r3);
    }
}


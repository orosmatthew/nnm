
#ifndef NNM_POINT_SET_HPP
#define NNM_POINT_SET_HPP

#include <nnm/core.hpp>

#include <cstdint>
#include <initializer_list>

namespace nnm {

/**
 * Fixed-capacity, stack-allocated unordered set of points.
 * Points are considered duplicates when they are approximately equal.
 * @tparam Point Point type.
 * @tparam Capacity Fixed capacity.
 */
template <typename Point, uint8_t Capacity>
class PointSet {
    static_assert(Capacity > 0, "PointSet capacity must be greater than zero.");

public:
    /**
     * Default initialize to zero points.
     */
    constexpr PointSet()
        : m_points { }
        , m_size { 0 }
    {
    }

    /**
     * Initialize with points.
     * @param points Points.
     */
    // ReSharper disable once CppNonExplicitConvertingConstructor
    constexpr PointSet(std::initializer_list<Point> points) // NOLINT(*-explicit-constructor)
        : PointSet()
    {
        for (const Point& point : points) {
            insert(point);
        }
    }

    /**
     * Fixed capacity.
     * @return Result.
     */
    [[nodiscard]] static constexpr uint8_t capacity()
    {
        return Capacity;
    }

    /**
     * Insert point with approximate duplicate checking.
     * @param point Point.
     */
    constexpr void insert(const Point& point)
    {
        if (contains(point)) {
            return;
        }
        NNM_BOUNDS_CHECK_ASSERT("PointSet", m_size < capacity());
        m_points[m_size++] = point;
    }

    /**
     * Clear points.
     */
    constexpr void clear()
    {
        for (uint8_t i = 0; i < Capacity; ++i) {
            m_points[i] = Point::zero();
        }
        m_size = 0;
    }

    /**
     * Number of points.
     * @return Result.
     */
    [[nodiscard]] constexpr uint8_t size() const
    {
        return m_size;
    }

    /**
     * Start iterator.
     * @return Iterator.
     */
    constexpr Point* begin()
    {
        return m_points;
    }

    /**
     * End iterator.
     * @return Iterator.
     */
    constexpr Point* end()
    {
        return m_points + m_size;
    }

    /**
     * Start const iterator.
     * @return Iterator.
     */
    constexpr const Point* begin() const
    {
        return m_points;
    }

    /**
     * End const iterator.
     * @return Iterator.
     */
    constexpr const Point* end() const
    {
        return m_points + m_size;
    }

    /**
     * Data pointer.
     * @return Result.
     */
    constexpr const Point* data() const
    {
        return m_points;
    }

    /**
     * Data pointer.
     * @return Result.
     */
    constexpr Point* data()
    {
        return m_points;
    }

    /**
     * Unordered approximate equality.
     * @param other Other point set.
     * @return Result.
     */
    template <uint8_t OtherCapacity>
    [[nodiscard]] constexpr bool approx_equal(const PointSet<Point, OtherCapacity>& other) const
    {
        if (m_size != other.size()) {
            return false;
        }

        bool matched[OtherCapacity] { };
        for (uint8_t i = 0; i < m_size; ++i) {
            bool found = false;
            for (uint8_t j = 0; j < m_size; ++j) {
                if (!matched[j] && m_points[i].approx_equal(other.data()[j])) {
                    matched[j] = true;
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }

    /**
     * Unordered approximate equality.
     * @param other Other point set.
     * @return Result.
     */
    [[nodiscard]] constexpr bool approx_equal(const PointSet& other) const
    {
        return approx_equal<Capacity>(other);
    }

    /**
     * Determine if approximately contains point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] constexpr bool contains(const Point& point) const
    {
        for (uint8_t i = 0; i < m_size; ++i) {
            if (m_points[i].approx_equal(point)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determine if there are no points.
     */
    [[nodiscard]] constexpr bool empty() const
    {
        return m_size == 0;
    }

    /**
     * Exact unordered equality.
     * @param other Other point set.
     * @return Result.
     */
    template <uint8_t OtherCapacity>
    [[nodiscard]] constexpr bool operator==(const PointSet<Point, OtherCapacity>& other) const
    {
        if (m_size != other.size()) {
            return false;
        }

        bool matched[OtherCapacity] { };
        for (uint8_t i = 0; i < m_size; ++i) {
            bool found = false;
            for (uint8_t j = 0; j < m_size; ++j) {
                if (!matched[j] && m_points[i] == other.data()[j]) {
                    matched[j] = true;
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }

    /**
     * Exact unordered equality.
     * @param other Other point set.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator==(const PointSet& other) const
    {
        return operator== <Capacity>(other);
    }

    /**
     * Exact unordered inequality.
     * @param other Other point set.
     * @return Result.
     */
    template <uint8_t OtherCapacity>
    [[nodiscard]] constexpr bool operator!=(const PointSet<Point, OtherCapacity>& other) const
    {
        return !(*this == other);
    }

    /**
     * Exact unordered inequality.
     * @param other Other point set.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator!=(const PointSet& other) const
    {
        return !(*this == other);
    }

private:
    Point m_points[Capacity];
    uint8_t m_size;
};

}

#endif

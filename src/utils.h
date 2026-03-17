#include <array>

namespace Utils
{
    template <typename T, std::size_t N1, std::size_t N2>
    constexpr auto concat(const std::array<T, N1> &a,
                          const std::array<T, N2> &b)
    {
        std::array<T, N1 + N2> result{};

        for (std::size_t i = 0; i < N1; ++i)
            result[i] = a[i];

        for (std::size_t i = 0; i < N2; ++i)
            result[N1 + i] = b[i];

        return result;
    }
}
#pragma once

#include "type_checks.h"
#include "typedefs.h"
#include <stddef.h>
#include <string>
#include <vector>

namespace fratio {

template <typename T>
class GenericFilter {
    static_assert(std::is_floating_point<T>::value && !std::is_const<T>::value, "Only accept non-complex floating point types.");

public:
    static std::string filterStatus(FilterStatus status);

public:
    // Careful: Only an assert check for the filter status
    T stepFilter(const T& data); 
    Eigen::VectorX<T> filter(const Eigen::VectorX<T>& data);
    bool getFilterResults(Eigen::Ref<Eigen::VectorX<T>> results, const Eigen::VectorX<T>& data);
    void resetFilter();

    bool setCoeffs(const std::vector<T>& aCoeff, const std::vector<T>& bCoeff);
    bool setCoeffs(const Eigen::VectorX<T>& aCoeff, const Eigen::VectorX<T>& bCoeff);
    void getCoeffs(std::vector<T>& aCoeff, std::vector<T>& bCoeff) const;
    void getCoeffs(Eigen::Ref<Eigen::VectorX<T>> aCoeff, Eigen::Ref<Eigen::VectorX<T>> bCoeff) const;
    FilterStatus status() const noexcept { return m_status; }

protected:
    GenericFilter() = default;
    GenericFilter(const Eigen::VectorX<T>& aCoeff, const Eigen::VectorX<T>& bCoeff);
    virtual ~GenericFilter() = default;

    void normalizeCoeffs();
    template <typename T2>
    bool checkCoeffs(const T2& aCoeff, const T2& bCoeff);

protected:
    FilterStatus m_status;
    Eigen::VectorX<T> m_aCoeff;
    Eigen::VectorX<T> m_bCoeff;

private:
    Eigen::VectorX<T> m_filteredData;
    Eigen::VectorX<T> m_rawData;
};

} // namespace fratio

#include "GenericFilter.tpp"

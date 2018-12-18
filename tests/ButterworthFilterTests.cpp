#define BOOST_TEST_MODULE ButterworthFilterTests

// Note: In term of precision, LP > HP > BP ~= BR

#include "fratio"
#include "test_functions.h"
#include "warning_macro.h"
#include <boost/test/unit_test.hpp>

DISABLE_CONVERSION_WARNING_BEGIN

template <typename T>
struct System {
    fratio::vectX_t<T> data = (fratio::vectX_t<T>(8) << 1, 2, 3, 4, 5, 6, 7, 8).finished();
    int order = 5;
    T fc = 10;
    T fs = 100;
    T bw = 10;
    T fCenter = 10;
    // LP
    fratio::vectX_t<T> lpACoeffRes = (fratio::vectX_t<T>(6) << 1, -2.975422109745684, 3.806018119320413, -2.545252868330468, 0.881130075437837, -0.125430622155356).finished();
    fratio::vectX_t<T> lpBCoeffRes = (fratio::vectX_t<T>(6) << 0.001282581078961, 0.006412905394803, 0.012825810789607, 0.012825810789607, 0.006412905394803, 0.001282581078961).finished();
    fratio::vectX_t<T> lpResults = (fratio::vectX_t<T>(8) << 0.001282581078961, 0.012794287652606, 0.062686244350084, 0.203933712825708, 0.502244959135609, 1.010304217144175, 1.744652693589064, 2.678087381460197).finished();
    // HP
    fratio::vectX_t<T> hpACoeffRes = (fratio::vectX_t<T>(6) << 1, -2.975422109745683, 3.806018119320411, -2.545252868330467, 0.8811300754378368, -0.1254306221553557).finished();
    fratio::vectX_t<T> hpBCoeffRes = (fratio::vectX_t<T>(6) << 0.3541641810934298, -1.770820905467149, 3.541641810934299, -3.541641810934299, 1.770820905467149, -0.3541641810934298).finished();
    fratio::vectX_t<T> hpResults = (fratio::vectX_t<T>(8) << 0.3541641810934298, -0.008704608374924483, -0.3113626313910076, -0.3460321436983160, -0.1787600153274098, 0.04471440201428267, 0.2059279258827846, 0.2533941579793959).finished();
    // BP
    fratio::vectX_t<T> bpACoeffRes = (fratio::vectX_t<T>(11) << 1, -6.784299264603903, 21.577693329895588, -42.338550072279737, 56.729081385507655, -54.208087151300411, 37.399203252161037, -18.397491390111661, 6.180883710485754, -1.283022311577260, 0.125430622155356).finished();
    fratio::vectX_t<T> bpBCoeffRes = (fratio::vectX_t<T>(11) << 0.001282581078963, 0, -0.006412905394817, 0, 0.012825810789633, 0, -0.012825810789633, 0, 0.006412905394817, 0, -0.001282581078963).finished();
    fratio::vectX_t<T> bpResults = (fratio::vectX_t<T>(8) << 0.001282581078963, 0.011266576028733, 0.046195520115810, 0.116904647483408, 0.200574194600111, 0.232153315136604, 0.141350142008155, -0.086403129422609).finished();
};

DISABLE_CONVERSION_WARNING_END

BOOST_FIXTURE_TEST_CASE(BUTTERWORTH_LP_FILTER_FLOAT, System<float>)
{
    auto bf = fratio::Butterworthf(order, fc, fs);
    BOOST_REQUIRE_EQUAL(bf.aOrder(), bf.bOrder());
    test_coeffs(lpACoeffRes, lpBCoeffRes, bf, std::numeric_limits<float>::epsilon() * 10);
    test_results(lpResults, data, bf, std::numeric_limits<float>::epsilon() * 100);
}

BOOST_FIXTURE_TEST_CASE(BUTTERWORTH_LP_FILTER_DOUBLE, System<double>)
{
    auto bf = fratio::Butterworthd(order, fc, fs);
    BOOST_REQUIRE_EQUAL(bf.aOrder(), bf.bOrder());
    test_coeffs(lpACoeffRes, lpBCoeffRes, bf, std::numeric_limits<double>::epsilon() * 10);
    test_results(lpResults, data, bf, std::numeric_limits<double>::epsilon() * 100);
}

BOOST_FIXTURE_TEST_CASE(BUTTERWORTH_HP_FILTER_FLOAT, System<float>)
{
    auto bf = fratio::Butterworthf(order, fc, fs, fratio::Butterworthf::Type::HighPass);
    BOOST_REQUIRE_EQUAL(bf.aOrder(), bf.bOrder());
    test_coeffs(hpACoeffRes, hpBCoeffRes, bf, std::numeric_limits<float>::epsilon() * 10);
    test_results(hpResults, data, bf, std::numeric_limits<float>::epsilon() * 1000);
}

BOOST_FIXTURE_TEST_CASE(BUTTERWORTH_HP_FILTER_DOUBLE, System<double>)
{
    auto bf = fratio::Butterworthd(order, fc, fs, fratio::Butterworthd::Type::HighPass);
    BOOST_REQUIRE_EQUAL(bf.aOrder(), bf.bOrder());
    test_coeffs(hpACoeffRes, hpBCoeffRes, bf, std::numeric_limits<double>::epsilon() * 10);
    test_results(hpResults, data, bf, std::numeric_limits<double>::epsilon() * 100);
}

BOOST_FIXTURE_TEST_CASE(BUTTERWORTH_BP_FILTER_FLOAT, System<float>)
{
    auto bf = fratio::Butterworthf(order, bw, fs, fCenter);
    BOOST_REQUIRE_EQUAL(bf.aOrder(), bf.bOrder());
    test_coeffs(bpACoeffRes, bpBCoeffRes, bf, std::numeric_limits<float>::epsilon() * 1000);
    test_results(bpResults, data, bf, std::numeric_limits<float>::epsilon() * 10000);
}

BOOST_FIXTURE_TEST_CASE(BUTTERWORTH_BP_FILTER_DOUBLE, System<double>)
{
    auto bf = fratio::Butterworthd(order, bw, fs, fCenter);
    BOOST_REQUIRE_EQUAL(bf.aOrder(), bf.bOrder());
    test_coeffs(bpACoeffRes, bpBCoeffRes, bf, std::numeric_limits<double>::epsilon() * 1000);
    test_results(bpResults, data, bf, std::numeric_limits<double>::epsilon() * 10000);
}
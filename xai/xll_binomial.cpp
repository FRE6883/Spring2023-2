// xll_binomial.cpp - Binomial model option pricing
#include "../cpp/fms_binomial.h"
#include "xai.h"

using namespace fms;
using namespace xll;

AddIn xai_binomial_european(
	Function(XLL_DOUBLE, "xll_binomial_european", "XLL.BINOMIAL.EUROPEAN")
	.Arguments({
		Arg(XLL_DOUBLE, "f", "is the forward."),
		Arg(XLL_DOUBLE, "s", "is the vol."),
		Arg(XLL_DOUBLE, "k", "is the strike of a call (k > 0) or put (k < 0)."),
		Arg(XLL_LONG, "n", "is the number of steps."),
		})
		.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return value of binomial European option.")
);
double WINAPI xll_binomial_european(double f, double s, double k, long n)
{
#pragma XLLEXPORT
	double v0 = std::numeric_limits<double>::quiet_NaN();

	std::vector<double> v(n + 1);

	if (k > 0) {
		v0 = binomial::european::value(f, s, [=](double x) { return std::max(x - k, 0.); }, std::span(v));
	}
	else if (k < 0) {
		v0 = binomial::european::value(f, s, [=](double x) { return std::max(-k - x, 0.); }, std::span(v));
	}
	else {
		v0 = binomial::european::value(f, s, [](double x) { return x; }, std::span(v));
	}

	return v0;
}

// !!! Implement XLL.BINOMIAL.EUROPEANP based on XLL.BINOMIAL.EUROPEAN

AddIn xai_binomial_europeanp(
	Function(XLL_DOUBLE, "xll_binomial_europeanp", "XLL.BINOMIAL.EUROPEANP")
	.Arguments({
		Arg(XLL_DOUBLE, "f", "is the forward."),
		Arg(XLL_DOUBLE, "s", "is the vol."),
		Arg(XLL_DOUBLE, "k", "is the strike of a call (k > 0) or put (k < 0)."),
		Arg(XLL_LONG, "n", "is the number of steps."),
		Arg(XLL_DOUBLE, "p", "is the probability of an up step.")
		})
		.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return value of binomial European option.")
);
double WINAPI xll_binomial_europeanp(double f, double s, double k, long n, double p)
{
#pragma XLLEXPORT
	double v0 = std::numeric_limits<double>::quiet_NaN();

	std::vector<double> v(n + 1);

	if (k > 0) {
		v0 = binomial::european::valuep(f, s, p, [=](double x) { return std::max(x - k, 0.); }, std::span(v));
	}
	else if (k < 0) {
		v0 = binomial::european::valuep(f, s, p, [=](double x) { return std::max(-k - x, 0.); }, std::span(v));
	}
	else {
		v0 = binomial::european::valuep(f, s, p, [](double x) { return x; }, std::span(v));
	}

	return v0;
}

AddIn xai_binomial_american(
	Function(XLL_DOUBLE, "xll_binomial_american", "XLL.BINOMIAL.AMERICAN")
	.Arguments({
		Arg(XLL_DOUBLE, "f", "is the forward."),
		Arg(XLL_DOUBLE, "s", "is the vol."),
		Arg(XLL_DOUBLE, "k", "is the strike of a call (k > 0) or put (k < 0)."),
		Arg(XLL_LONG, "n", "is the number of steps."),
		})
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return value of binomial American option.")
);
double WINAPI xll_binomial_american(double f, double s, double k, long n)
{
#pragma XLLEXPORT
	double v0 = std::numeric_limits<double>::quiet_NaN();

	std::vector<double> v(n + 1);

	if (k > 0) {
		v0 = binomial::american::value(f, s, [=](double x) { return std::max(x - k, 0.); }, std::span(v));
	}
	else if (k < 0) {
		v0 = binomial::american::value(f, s, [=](double x) { return std::max(-k - x, 0.); }, std::span(v));
	}
	else {
		v0 = binomial::american::value(f, s, [](double x) { return x; }, std::span(v));
	}

	return v0;
}

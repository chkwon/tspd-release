//
// Created by Gonzalo Lera Romero.
// Grupo de Optimizacion Combinatoria (GOC).
// Departamento de Computacion - Universidad de Buenos Aires.
//

#ifndef GOC_MATH_INTERVAL_H
#define GOC_MATH_INTERVAL_H

#include <iostream>

#include "goc/lib/json.hpp"
#include "goc/print/printable.h"
#include "goc/math/number_utils.h"

namespace goc
{
// This class represents a closed interval [left, right].
class Interval : public Printable
{
public:
	// Limits of the interval.
	double left, right;
	
	// Represents the empty interval [INFTY, -INFTY].
	Interval();
	
	// Represents the interval [left, right].
	Interval(double left, double right);
	
	// Returns: if left > right.
	inline bool Empty() const { return epsilon_bigger(left, right); }
	
	// Returns: if value \in [left, right] using epsilon-comparison.
	inline bool Includes(double value) const { return epsilon_smaller_equal(left, value) && epsilon_bigger_equal(right, value); }
	
	// Returns: if r=[a,b]\subseteq [left, right] using epsilon-comparison.
	bool IsIncludedIn(const Interval& r) const;
	
	// Returns: if r=[a,b] \cap [left, right] using epsilon-comparison.
	bool Intersects(const Interval& r) const;
	
	// Returns: this \cap r.
	inline Interval Intersection(const Interval& r) const { return Interval(std::max(left, r.left), std::min(right, r.right)); }
	
	// Returns: if the domain is [a, a] for some a.
	inline bool IsPoint() const { return epsilon_equal(left, right); }
	
	// Prints the interval.
	// Format: [left, right].
	virtual void Print(std::ostream& os) const;
	
	// Returns: if two intervals are the same.
	// We say two intervals are the same if their limits are the same or if they are empty intervals (left > right).
	bool operator==(const Interval& i) const;
	
	// Returns: if two intervals are different.
	bool operator!=(const Interval& i) const;
};

// JSON format: [left, right].
void from_json(const nlohmann::json& j, Interval& i);

void to_json(nlohmann::json& j, const Interval& i);
} // namespace goc

// Adding to namespace std to not conflict with overload.
namespace std
{
// Returns: i.left
inline double min(const goc::Interval& i) { return i.left; }

// Returns: i.right
inline double max(const goc::Interval& i) { return i.right; }
} // namespace std

#endif //GOC_MATH_INTERVAL_H

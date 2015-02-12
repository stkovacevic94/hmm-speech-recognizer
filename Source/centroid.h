#ifndef CENTROID
#define CENTROID

#include "point.h"

class centroid : public point
{
public:
	centroid(const std::vector<double>& coords);

	std::vector<point> get_points() { return m_points; }

	void add_point(point& p);
	void remove_point(point& p);
	void update();
	void reset();
	void remove_all() { m_points.clear(); }

private:
	std::vector<point> m_points;
};

#endif

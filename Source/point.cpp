#include "point.h"

double point::distance(const point& pt) const
{
	double distance = 0.0f;
	for (int i = 0; i < get_dimension(); i++) {
		double d = get_coordinate(i) - pt.get_coordinate(i);
		distance += d * d;
	}
	return distance;
}

size_t point::find_nearest(const std::vector<point*>& points) const
{
	if (!points.size()) 
		return -1;

	int ind = 0;
	double dist = distance(*points[0]);
	for (int i = 0; i < points.size(); i++) {
		double tmpDistance = distance(*points[i]);
		if (tmpDistance < dist) {
			dist = tmpDistance;
			ind = i;
		}
	}
	return ind;
}

bool point::operator==(const point& rhs)
{
	for (size_t i = 0; i < m_coords.size(); i++)
		if (m_coords[i] != rhs.m_coords[i])
			return false;
	return true;
}
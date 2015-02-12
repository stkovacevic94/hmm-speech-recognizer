#ifndef POINT
#define POINT

#include <vector>

class point
{
public:
	point(std::vector<double> coords) : m_coords(coords){};

	std::vector<double> get_all() { return m_coords; }
	double get_coordinate(size_t ind) const { return m_coords[ind]; }
	size_t get_dimension() const { return m_coords.size(); }
	
	double distance(const point& pt) const;

	size_t find_nearest(const std::vector<point*>& points) const;

	bool operator==(const point& rhs);
protected:
	std::vector<double> m_coords;
};

#endif


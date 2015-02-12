#include "centroid.h"
#include <algorithm>

using namespace std;

centroid::centroid(const vector<double>& coords)
	: point(coords), m_points(std::vector<point>())
{
}

void centroid::add_point(point& p)
{
	m_points.push_back(p);
}

void centroid::remove_point(point& p)
{
	auto it = find(m_points.begin(), m_points.end(), p);
	m_points.erase(it);
}

void centroid::update()
{
	reset();
	for (point p : m_points)
		for (int i = 0; i < m_coords.size(); i++) 
			m_coords[i] += p.get_coordinate(i);
		
	for (int i = 0; i < m_coords.size(); i++) 
		m_coords[i] /= m_points.size();
}

void centroid::reset()
{
	for (int i = 0; i < m_coords.size(); i++)
		m_coords[i] = 0.0f;
}
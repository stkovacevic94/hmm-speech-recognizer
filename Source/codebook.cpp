#include "codebook.h"

#include "centroid.h"

codebook::codebook(const std::vector<point>& points, size_t codebook_size)
	: m_points(points), m_codebook_size(codebook_size)
{
}

void codebook::init()
{
	m_clusters = std::vector<centroid>();
	for (point pt : m_points) 
	{
		m_clusters.push_back(centroid(pt.get_all()));
		if (m_clusters.size() == m_codebook_size) 
			break;
	}

	for (int it = 0; it < 20; it++) 
	{
		reasign_points(m_clusters, m_points);
		update_clusters(m_clusters);
	}
}

std::vector<int> codebook::quantitize(const std::vector<point>& points)
{
	std::vector<int> quantized(points.size());
	for (int i = 0; i < points.size(); i++) {
		std::vector<point*> clust(m_clusters.size());
		for (size_t j = 0; j < clust.size(); j++)
			clust[j] = &m_clusters[j];
		quantized[i] = points[i].find_nearest(clust);
	}
	return quantized;
}

void codebook::reasign_points(std::vector<centroid>& clusters, const std::vector<point>& points)
{
	for (centroid cluster : clusters)
		cluster.remove_all();

	std::vector<point*> clust(clusters.size());
	for (size_t i = 0; i < clust.size(); i++)
		clust[i] = &clusters[i];

	int processed_points = 0;
	for (point pt : points) 
	{
		int idx = pt.find_nearest(clust);
		clusters[idx].add_point(pt);
	}
}

void codebook::update_clusters(std::vector<centroid>& clusters)
{
	for (centroid cluster : clusters) 
		cluster.update();
}

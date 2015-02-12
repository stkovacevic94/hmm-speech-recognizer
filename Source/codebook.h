#ifndef CODEBOOK
#define CODEBOOK

#include <list>
#include <vector>

class point;
class centroid;

class codebook
{
public:
	static const unsigned short DEFAULT_CODEBOK_SIZE = 1024;

	codebook(const std::vector<point>& points, size_t codebook_size);
	
	void init();

	std::vector<int> quantitize(const std::vector<point>& points);
	
	std::vector<centroid>	get_clusters();// { return m_clusters; }
	std::vector<point>		get_points();// { return m_points; }
	size_t					get_size();// { return m_codebook_size; }
private:
	void reasign_points(std::vector<centroid>& clusters, const std::vector<point>& points);
	void update_clusters(std::vector<centroid>& clusters);

	std::vector<point> m_points;
	std::vector<centroid> m_clusters;
	size_t m_codebook_size;
};

#endif


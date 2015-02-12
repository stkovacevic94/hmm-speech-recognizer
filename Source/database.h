#ifndef DATABASE
#define DATABASE

#include "codebook.h"

class database
{
public:
	database();
	~database();

	codebook* get_codebook() { return m_codebook; }
private:
	codebook* m_codebook;
};

#endif
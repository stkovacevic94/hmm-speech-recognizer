#ifndef IOBSERVER
#define IOBSERVER

class iobserver
{
public:
	virtual void update(const std::string& word) = 0;
};

#endif
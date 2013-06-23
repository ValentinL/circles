#ifndef _NON_COPYABLE_H
#define _NON_COPYABLE_H

class NonCopyable
{
protected:
	NonCopyable(){};
	~NonCopyable(){};
private:
	NonCopyable(const NonCopyable& root);
	NonCopyable& operator=(const NonCopyable&);
};

#endif
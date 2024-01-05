#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "quote.h"
#include "bulk_quote.h"
#include "limit_quote.h"

//void print_debug(const Quote& q);
//
//double print_total(std::ostream& os, const Quote& item, size_t n);

class base
{

public:
	std::string name() { return basename; }
	virtual void print(std::ostream& os) { os << basename; }

private:

	std::string basename = "base\n";
};


class derived :public base
{

public:
	void print(std::ostream& os) override { base::print(os); os << " derived\n" << i; }


private:

	int i;
};






int main()
{

	/*Quote q("aaa", 10.60);
	Bulk_quote bq("bbb", 111, 10, 0.3);
	Limit_quote lq("ccc", 222, 10, 0.3);


	Quote& r = q;
	r.debug();
	std::cout << "\n";

	r = bq;
	r.debug();
	std::cout << "\n";

	r = lq;
	r.debug();
	std::cout << "\n";

	std::cout<< "====================\n";



	print_debug(q);
	std::cout << "\n";
	print_debug(lq);
	std::cout << "\n";
	print_debug(bq);
	std::cout << "\n";*/

	base bobj;
	base* bp1 = &bobj;
	base& br1 = bobj;

	derived dobj;
	base* bp2 = &dobj;
	base& br2 = dobj;


	br2.print(std::cout);


	return 0;
}

double print_total(std::ostream& os, const Quote& item, size_t n)
{

	double ret = item.net_price(n);

	os << "ISBN:" << item.isbn() << "# sold: " << n << " total due: " << ret << std::endl;

	return ret;
}


void print_debug(const Quote& q)
{
	q.debug();
}

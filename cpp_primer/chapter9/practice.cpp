#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <cstddef>
#include <fstream>
#include <forward_list>
#include <stack>

using std::list; using std::vector; using std::cout; using std::endl;
using std::cin; using std::deque; using std::string; using std::end;
using std::forward_list; using std::advance; using std::ifstream;
using std::stack;

void double_and_insert(std::vector<int>& v, int some_val)
{
	auto mid = [&] {return v.begin() + v.size() / 2; };
	for (auto curr = v.begin(); curr != mid(); ++curr)
		if (*curr == some_val)
			++(curr = v.insert(curr, 2 * some_val));
}

auto remove_odds(forward_list<int>& flist)
{
	auto is_odd = [](int i) {return i & 0x1; };
	flist.remove_if(is_odd);
}

auto remove_evens_and_double_odds(list<int>& data)
{

	for (auto cur = data.begin(); cur != data.end();)
		if (*cur & 0x1)
			cur = data.insert(cur, *cur), advance(cur, 2);
		else
			cur = data.erase(cur);
}

auto remove_evens_and_double_odds(forward_list<int>& data)
{
	for (auto cur = data.begin(), prv = data.before_begin(); cur != data.end();)
		if (*cur & 0x1)
			cur = data.insert_after(prv, *cur),
			advance(cur, 2),
			advance(prv, 2);
		else
			cur = data.erase_after(prv);
}

auto replace_with(string& s, string const& oldVal, string const& newVal)
{

	for (auto cur = s.begin(); cur <= s.end() - oldVal.size();)
		if (oldVal == string{ cur,cur + oldVal.size() })
			cur = s.erase(cur, cur + oldVal.size()),
			cur = s.insert(cur, newVal.begin(), newVal.end()),
			cur += newVal.size();
		else
			++cur;
}

auto add_pre_and_suffix(string name, string const& pre, string const& su)
{

	/*name.insert(name.begin(), pre.cbegin(), pre.cend());
	return name.append(su);*/

	name.insert(0, pre);
	name.insert(name.size(), su);
	return name;
}

auto sum_for_int(std::vector<std::string> const& v)
{

	int sum = 0;
	for (auto const& s : v)
		sum += std::stoi(s);

	return sum;
}

auto sum_for_float(std::vector<std::string> const& v)
{
	float sum = 0.0;
	for (auto const& s : v)
		sum += std::stof(s);

	return sum;
}

class My_date {

private:
	unsigned year, month, day;

public:
	My_date(const string& s) {

		unsigned tag;
		unsigned format;
		format = tag = 0;

		if (s.find_first_of("/") != string::npos)
		{

			format = 0x01;
		}

		if ((s.find_first_of(',') >= 4) && s.find_first_of(',') != string::npos) {

			format = 0x10;
		}
		else {

			if(s.find_first_of(' ')>=3
				&& s.find_first_of(' ') != string::npos){
					format=0x10;
					tag=1;
				}
				
		}

		switch (format)
		{

		case 0x01:
			day = stoi(s.substr(0, s.find_first_of("/")));
			month = stoi(s.substr(s.find_first_of("/") + 1, s.find_last_of("/") - s.find_first_of("/")));
			year = stoi(s.substr(s.find_last_of("/") + 1, 4));

			break;

		case 0x10:
			if (s.find("Jan") < s.size())  month = 1;
			if (s.find("Feb") < s.size())  month = 2;
			if (s.find("Mar") < s.size())  month = 3;
			if (s.find("Apr") < s.size())  month = 4;
			if (s.find("May") < s.size())  month = 5;
			if (s.find("Jun") < s.size())  month = 6;
			if (s.find("Jul") < s.size())  month = 7;
			if (s.find("Aug") < s.size())  month = 8;
			if (s.find("Sep") < s.size())  month = 9;
			if (s.find("Oct") < s.size())  month = 10;
			if (s.find("Nov") < s.size())  month = 11;
			if (s.find("Dec") < s.size())  month = 12;

			char chr = ',';
			if (tag == 1) {
				chr = ' ';
			}
			day = stoi(s.substr(s.find_first_of("123456789"), s.find_first_of(chr) - s.find_first_of("123456789")));

			year = stoi(s.substr(s.find_last_of(' ') + 1, 4));
			break;
		
		}
	}

	void print() {

		cout << "day:" << day << " " << "month: " << month << " " << "year: " << year;
	}


};




int main()
{

	string expression{ "This is (peyz)." };
	bool bSeen = false;
	stack<char> stk;
	for (const auto& s : expression)
	{
		if (s == '(') {
			bSeen = true; continue;
		}
		else if (s == ')') bSeen = false;

		if (bSeen) stk.push(s);
	}

	string repstr;
	while (!stk.empty())
	{
		repstr += stk.top();
		stk.pop();
	}

	expression.replace(expression.find("(") + 1, repstr.size(), repstr);

	cout << expression << endl;

	/*My_date d("Jan 1 1900");

	d.print();*/
	


	/*std::vector<std::string> v = { "1","2","3","4.5" };
	std::cout << sum_for_int(v) << std::endl;
	std::cout << sum_for_float(v) << std::endl;*/



	/*ifstream ifs("letters");
	if (!ifs) return -1;

	string longest;
	auto update_with = [&longest](string const& curr)
	{

		if (string::npos == curr.find_first_not_of("aceimnorsuvwxz"))
			longest = longest.size() < curr.size() ? curr : longest;
	};

	for (string curr; ifs >> curr; update_with(curr));
	cout << longest << endl;*/

	/*string numbers{ "123456789" };
	string alphabet{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	string str{ "ab2c3d7R4E6" };

	cout << "numeric characters: ";
	for (int pos = 0; (pos = str.find_first_not_of(alphabet, pos)) != string::npos; ++pos)
		cout << str[pos] << " ";
	cout << "\nalphabetic characters: ";
	for (int pos = 0; (pos = str.find_first_not_of(numbers, pos)) != string::npos; ++pos)
		cout << str[pos] << " ";
	cout << endl;*/

	/*cout << "numeric characters: ";
	for (int pos = 0; (pos = str.find_first_of(numbers, pos)) != string::npos; ++pos)
		cout << str[pos] << " ";

	cout << "\nalphabetic characters: ";
	for (int pos = 0; (pos = str.find_first_of(alphabet, pos)) != string::npos; ++pos)
		cout << str[pos] << " ";

	cout << endl;*/

	//string name("Wang");
	/*string name("alan");
	cout << add_pre_and_suffix(name, "Mr.", ", Jr.") << endl;*/


	/*string s{ "To drive straight thru is a foolish, tho courageuous act." };
	replace_with(s, "tho", "though");
	replace_with(s, "thru", "through");
	cout << s << endl;*/

	/*vector<char> v{ 'p','e','z','y' };
	string str(v.cbegin(), v.cend());
	cout << str << endl;*/





	/*std::vector<std::string> v;
	for (std::string buffer; std::cin >> buffer; v.push_back(buffer))
		std::cout << v.capacity() << std::endl;*/

	/*vector<int> data{ 0,1,2,3,4,5,6,7,8,9 };
	for (auto cur = data.begin(); cur != data.end(); ++cur)
		if (*cur & 0x1)
			cur = data.insert(cur, *cur), ++cur;

	for (auto i : data)
		cout << i << " ";*/

	/*forward_list<int> data{ 0,1,2,3,4,5,6,7,8,9 };
	remove_evens_and_double_odds(data);
	for (auto i : data)
		cout << i << " ";*/



	/*list<int> data{ 0,1,2,3,4,5,6,7,8,9 };
	remove_evens_and_double_odds(data);
	for (auto i : data) cout << i << " ";*/


	/*forward_list<int> data = { 0,1,2,3,4,5,6,7,8,9 };
	remove_odds(data);
	for (auto i : data)
		cout << i << " ";*/

	/*int ia[] = { 0,1,1,2,3,5,8,13,21,55,89 };

	vector<int> vec(ia, end(ia));
	list<int> lst(vec.begin(), vec.end());

	for (auto it = lst.begin(); it != lst.end();)
		if (*it & 0x1) it = lst.erase(it);
		else ++it;

	cout << "list : ";
	for (auto i : lst) cout << i << " ";
	cout << "\nvector : ";
	for (auto i : vec) cout << i << " ";
	cout << std::endl;*/



	/*std::vector<int> v;
	std::cout << v.at(0);
	std::cout << v[0];
	std::cout << v.front();
	std::cout << *v.begin();*/



	/*vector<int> v{ 1,9,1,9,9,9,1,1 };
	double_and_insert(v, 1);

	for (auto i : v)
		cout << i << endl;*/

	/*list<int> ilst(5, 4);
	vector<int> ivc(5, 5);

	vector<double> dvc(ilst.begin(), ilst.end());
	for (auto i : ilst) cout << i << " ";
	cout << endl;
	for (auto d : dvc) cout << d << " ";
	cout << endl;

	vector<double> dvc2(ivc.begin(), ivc.end());
	for (auto i : ivc) cout << i << " ";
	cout << endl;
	for (auto d : dvc2) cout << d << " ";*/

	/*std::list<const char*> l{ "Mooophy","pezy","Queeuqueg" };
	std::vector<std::string> v;
	v.assign(l.cbegin(), l.cend());

	for (auto ptr : v)
		std::cout << ptr << std::endl;*/

	/*std::vector<int> vec1{ 1,2,3,4,5 };
	std::vector<int> vec2{ 1,2,3,4,5 };
	std::vector<int> vec3{ 1,2,3,4 };

	std::cout << (vec1 == vec2 ? "true" : "false") << std::endl;
	std::cout << (vec1 == vec3 ? "true" : "false") << std::endl;*/

	/*std::list<int> li{ 1,2,3,4,5 };
	std::vector<int> vec2{ 1,2,3,4,5 };
	std::vector<int> vec3{ 1,2,3,4 };

	std::cout << (std::vector<int>(li.begin(), li.end()) == vec2 ? "true" : "false") << std::endl;
	std::cout << (std::vector<int>(li.begin(), li.end()) == vec3 ? "true" : "false") << std::endl;*/

	/*deque<string> input;
	for (string str; cin >> str; input.push_back(str));
	for (auto iter = input.cbegin(); iter != input.cend(); ++iter)
		cout << *iter << endl;*/

	/*list<string> input;
	for (string str; cin >> str; input.push_back(str));
	for (auto iter = input.cbegin(); iter != input.cend(); ++iter)
		cout << *iter << endl;*/

	/*list<int> l{ 1,2,3,4,5,6,7,8,9,10 };
	deque<int> odd, even;
	for (auto i : l)
		(i & 0x1 ? odd : even).push_back(i);

	for (auto i : odd) cout << i << " ";
	cout << endl;
	for (auto i : even) cout << i << " ";
	cout << endl;*/





	return 0;
}
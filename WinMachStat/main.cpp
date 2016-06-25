#include <iostream>
#include <string>

class print {
	void Hello() {
		std::cout << "Hello" << std::endl;
	}
	std::string getHello() {
		return "Hello";
	}
};

int main()
{
	print p;
	std::cout << p.getHello(); << std::endl; 
	p.Hello();
}
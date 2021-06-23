#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <algorithm>
#include <array>

constexpr size_t maxErase = 15;

using vector_type = std::vector<size_t>;
using map_type = std::map<size_t,size_t>;

size_t Rnd(size_t from, size_t to) {
	static std::random_device rd;
	static std::mt19937 eng(rd());
	if (from > to) std::swap(from, to);
	std::uniform_int_distribution<size_t> rnd(from, to);
	return rnd(eng);
	}

void Filling(vector_type& vector, map_type& map) {
	constexpr size_t minSize = 20;
	constexpr size_t maxSize = 50;
	size_t size = Rnd(minSize, maxSize);
	vector.resize(Rnd(minSize, maxSize));
	map.clear();
	std::generate(vector.begin(), vector.end(), [] {return Rnd(1, 9); });
	for (size_t i = 0; i < size; ++i) {
		map[i] = Rnd(1, 9);
	}
}

void RandomErase(vector_type& vector) {
	size_t num = std::min(maxErase, vector.size());
	size_t max = vector.size();
	num = Rnd(0, num);
	while (num > 0) {
		vector.erase(vector.begin() + Rnd(0, --max));
		--num;
	}
}

void RandomErase(map_type& map) {
	size_t num = std::min(maxErase, map.size());
	size_t max = map.size() - 1;
	num = Rnd(0, num);
	while (num > 0) {
		auto it = map.find(Rnd(0, max));
		if (it != map.end()) {
			map.erase(it);
			--num;
		}
	}
}

void RandomErase(vector_type& vector, map_type& map) {
	RandomErase(vector);
	RandomErase(map);
}

void Intersection(vector_type& vector, map_type& map) {
	std::array<bool, 9> tmp{ false };
	auto iv = vector.begin();
	auto im = map.begin();
	size_t i=0;
	while (iv != vector.end() && im != map.end()) {
		if (i!=im->first)
			++iv;
		else {
			if (*iv == im->second) tmp[*iv - 1] = true;
			++iv;
			++im;
		} 
		++i;
	}

	vector.erase(iv, vector.end());
	map.erase(im, map.end());
}

void Print(vector_type& left, map_type& right) {
	auto li = left.begin();
	auto ri = right.begin();
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Size: " << left.size() << " | " << right.size() << std::endl;
	while (li != left.end() || ri != right.end()) {
		if (li != left.end())	std::cout << *li++;
		else std::cout << " ";
		std::cout << " | ";
		if (ri != right.end()){
			std::cout << "(" << ri->first << ",";
			std::cout << ri++->second << ")";
		}
		std::cout << std::endl;
	}
}

int main()
{
	vector_type vector;
	map_type map;
	Filling(vector, map);
	Print(vector, map);
	RandomErase(vector, map);
	Print(vector, map);
	Intersection(vector, map);
	Print(vector, map);
}

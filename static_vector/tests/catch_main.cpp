
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <static_vector.h>

TEST_CASE("default construction")
{
	auto v = std::vector<int>();
	auto sv = static_vector<int, 3>();

	REQUIRE(sv.size() == 0);
	REQUIRE(sv.capacity() == 3);
}

TEST_CASE("push_back and pop_back")
{
	auto v = std::vector<int>();
	auto sv = static_vector<int, 5>();

	sv.push_back(0);
	REQUIRE(sv[0] == 0);

	sv.push_back(1);
	REQUIRE(sv[1] == 1);

	sv.push_back(2);
	REQUIRE(sv[2] == 2);

	REQUIRE(sv.size() == 3);

	int i = 0;

	sv.pop_back();
	REQUIRE(sv.size() == 2);
	REQUIRE(std::ranges::equal(sv, std::vector{ 0, 1 }));

	sv.pop_back();
	sv.pop_back();

	REQUIRE(sv.size() == 0);
}

TEST_CASE("individual insert and erase")
{
	namespace rng = std::ranges;
	
	auto sv = static_vector<int, 5>();

	sv.push_back(2);
	sv.push_back(4);

	auto it = sv.begin();
	
	// insert at begin
	sv.insert(it, 1);
	REQUIRE(rng::equal(sv, std::vector{ 1, 2, 4 }));

	it += 2;

	// insert in the middle
	sv.insert(it, 3);
	REQUIRE(rng::equal(sv, std::vector{ 1, 2, 3, 4 }));

	it += 2;

	// insert at end
	sv.insert(it, 5);
	REQUIRE(rng::equal(sv, std::vector{ 1, 2, 3, 4, 5 }));

	REQUIRE(sv.size() == 5);

	it = sv.begin();

	// erase at begin
	it = sv.erase(it);
	REQUIRE(rng::equal(sv, std::vector{ 2, 3, 4, 5 }));
	REQUIRE(*it == 2);
	REQUIRE(sv.size() == 4);

	++it;

	// erase in the middle
	it = sv.erase(it);
	REQUIRE(rng::equal(sv, std::vector{ 2, 4, 5 }));
	REQUIRE(*it == 4);
	REQUIRE(sv.size() == 3);

	it = sv.end() - 1;

	// erase at end
	it = sv.erase(it);
	REQUIRE(rng::equal(sv, std::vector{ 2, 4 }));
	REQUIRE(it == sv.end());
	REQUIRE(sv.size() == 2);
}

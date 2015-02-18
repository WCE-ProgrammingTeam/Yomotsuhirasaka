#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch.hpp"

#include <string>
#include <vector>
#include <array>

#include "../../../src/yomotsuhirasaka/yomotsuhirasaka.hpp"

namespace ys=yomotsuhirasaka;
typedef std::vector<uint8_t> charz;

// * the password, initial-vector and plain-text is fixed in each test. *
std::string password="test";
std::string given_plain="The quick brown fox jumps over the lazy dog.";
charz init_vector= 
	{
		// "Enigmatic string" in hex; this is 256bit.
		// 45 6E 69 67 6D 61 74 69 63 20 73 74 72 69 6E 67
		0x45, 0x6E, 0x69, 0x67, 0x6D, 0x61, 0x74, 0x69, 0x63, 0x20,
		0x73, 0x74, 0x72, 0x69, 0x6E, 0x67
	};

//乱数生成のテストも書く？

TEST_CASE("mugi::estream/dstream can encrypt/decrypt bytes with mugi")
{
	charz given_cipher=
		{
			//will add
		};

	SECTION("encrypt with mugi")
	{
		ys::mugi::estream<> estr;
		estr<<ys::key(password);
		estr<<ys::iv(init_vector);
		estr<<given_plain<<ys::endd;
		charz cipher;
		estr>>cipher;
		
		CHECK(cipher==given_cipher);
	}
	
	SECTION("decrypt with mugi")
	{
		ys::mugi::dstream<> dstr;
		dstr<<ys::key(password);
		dstr<<ys::iv(init_vector);
		dstr<<given_cipher<<ys::endd;
		std::string plain;
		dstr>>plain;
		
		CHECK(plain==given_plain);
	}
} //TEST_CASE("mugi::estream/dstream can encrypt/decrypt bytes with mugi")

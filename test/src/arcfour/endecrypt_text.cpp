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

TEST_CASE("arcfour::estream/dstream can encrypt/decrypt bytes with Arcfour")
{
	charz given_cipher=
		{
			// used : http://rc4.online-domain-tools.com/
			0xFA, 0xE7, 0x42, 0x31, 0x91, 0x5F, 0x14, 0x46,
			0xBD, 0x6E, 0x3F, 0x11, 0x7E, 0xD3, 0x89, 0xEF,
			0xDB, 0xF1, 0xC8, 0x26, 0xE4, 0x5D, 0x64, 0xF6,
			0xF2, 0x5D, 0x50, 0xEB, 0x05, 0x7E, 0x26, 0x5D,
			0x77, 0x6E, 0xC9, 0x7B, 0x4A, 0x85, 0x49, 0x44,
			0xC4, 0x71, 0x4F, 0xDA
		};

	SECTION("encrypt with Arcfour")
	{
		ys::arcfour::estream<> estr;
		estr<<ys::key(password);
		estr<<given_plain<<ys::endd;
		charz cipher;
		estr>>cipher;

		CHECK(cipher==given_cipher);
	}
	
	SECTION("decrypt with Arcfour")
	{
		ys::arcfour::dstream<> dstr;
		dstr<<ys::key(password);
		dstr<<given_cipher<<ys::endd;
		std::string plain;
		dstr>>plain;

		CHECK(plain==given_plain);
	}
} // TEST_CASE("arcfour::estream/dstream can encrypt/decrypt bytes with Arcfour")

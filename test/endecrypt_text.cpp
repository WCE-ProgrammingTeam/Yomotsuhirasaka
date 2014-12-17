#include <string>
#include <vector>
#include <array>

#include "../src/yomotsuhirasaka/yomotsuhirasaka.hpp"
#include "fct.h"

namespace ys=yomotsuhirasaka;
typedef std::vector<char> charz;

FCT_BGN()
{
	// * in these tests, the password and plain-text is fixed in each test. *
	std::string password="test";
	std::string given_plain="The quick brown fox jumps over the lazy dog.";
	// std::vector<char> given_cipher; // this is declared in each test, not fixed.

	FCT_SUITE_BGN(Arcfour)
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

		charz cipher; std::string plain; // the results

		FCT_TEST_BGN(arcfour_encrypt)
		{
			ys::arcfour::estream estr;
			estr<<ys::key(password);
			estr<<given_plain<<ys::endd;
			estr>>cipher;
			fct_chk(cipher==given_cipher);
		}
		FCT_TEST_END();
		
		FCT_TEST_END(arcfour_decrypt)
		{
			ys::arcfour::dstream dstr;
			dstr.key(password);
			dstr<<cipher;
			dstr>>plain;
			fct_chk(plain==given_plain);
		}
		FCT_TEST_END();
	}
	FCT_SUITE_END();

	FCT_SUITE_BGN(MUGI)
	{
		charz given_cipher=
		{
			//given cipher
		};

		charz cipher; std::string plain; // the results

		FCT_TEST_BGN(mugi_encrypt)
		{
			ys::mugi::estream estr;
			estr<<ys::key(password);
			estr<<ys::iv();
			estr<<given_plain<<ys::endd;
			estr>>cipher;
			fct_chk(cipher==given_cipher);
		}
		FCT_TEST_END();
		
		FCT_TEST_END(mugi_decrypt)
		{
			ys::mugi::dstream dstr;
			dstr.key(password);
			estr<<ys::iv();
			dstr<<cipher;
			dstr>>plain;
			fct_chk(plain==given_plain);
		}
		FCT_TEST_END();		
	}
	FCT_SUITE_END();

	FCT_SUITE_BGN(AES)
	{
		charz given_cipher =
		{
			0x7c,0x59,0x71,0xec,0x5a,0x06,0x2b,0xb3,
			0x5f,0x82,0xdd,0xea,0x88,0x27,0xfd,0x82,
			0x1d,0x9c,0xf8,0x36,0x02,0x4f,0x02,0xde,
			0x00,0x4d,0xfd,0xba,0x94,0x20,0xff,0x42,
			0x14,0x20,0x79,0xde,0x5c,0x0f,0xbd,0x53,
			0xe7,0x4a,0x1b,0xcc,0x78,0x94,0x9f,0x23
		};

		charz cipher; std::string plain; // the results

		FCT_TEST_BGN(aes_cbc_encrypt)
		{
			ys::aes::estream estr;
			estr << ys::key(password);
			estr << given_plain << ys::endd;
			estr >> cipher;
			fct_chk(cipher == given_cipher);
		}
		FCT_TEST_END();

		FCT_TEST_END(aes_cbc_decrypt)
		{
			ys::aes::dstream dstr;
			dstr.key(password);
			dstr << cipher;
			dstr >> plain;
			fct_chk(plain == given_plain);
		}
		FCT_TEST_END();
	}
	FCT_SUITE_END();

	FCT_SUITE_BGN(Twofish)
	{}
	FCT_SUITE_END();

}
FCT_END();

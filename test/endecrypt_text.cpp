#include <string>
#include <vector>
#include <array>

#include "../src/yomotsuhirasaka/yomotsuhirasaka.hpp"
#include "fct.h"

namespace ys=yomotsuhirasaka;
typedef std::vector<char> charz;

FCT_BGN()
{
	// * in these tests, the password, initial-vector and plain-text is fixed in each test. *
	std::string password="test";
	std::string given_plain="The quick brown fox jumps over the lazy dog.";
	charz init_vector=
		{
			// "Enigmatic string" in hex; this is 256bit.
			// 45 6E 69 67 6D 61 74 69 63 20 73 74 72 69 6E 67
			0x45, 0x6E, 0x69, 0x67, 0x6D, 0x61, 0x74, 0x69, 0x63, 0x20,
			0x73, 0x74, 0x72, 0x69, 0x6E, 0x67
		};

	// charz given_cipher; // this is declared in each test, not fixed.

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
			dstr<<ys::key(password);
			dstr<<cipher<<ys::endd;
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
			estr<<ys::iv(init_vector);
			estr<<given_plain<<ys::endd;
			estr>>cipher;
			fct_chk(cipher==given_cipher);
		}
		FCT_TEST_END();
		
		FCT_TEST_END(mugi_decrypt)
		{
			ys::mugi::dstream dstr;
			dstr<<ys::(password);
			dstr<<ys::iv(init_vector);
			dstr<<cipher<<ys::endd;
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
			// used : http://aes.online-domain-tools.com/
			0x0C, 0xC0, 0x5D, 0xA0, 0x14, 0xAF, 0xC9, 0x19, 
			0xCC, 0xAA, 0x8C, 0x2E, 0x5F, 0x71, 0xD3, 0x92, 
			0x4A, 0x1C, 0x11, 0xC8, 0xC1, 0x78, 0x3C, 0x7B, 
			0x85, 0x10, 0x17, 0x67, 0xE8, 0x40, 0x4A, 0x58, 
			0x8B, 0x9C, 0xD5, 0x36, 0x76, 0xAC, 0x90, 0x71, 
			0x90, 0xF7, 0xC6, 0x1F, 0x3D, 0x76, 0x5F, 0x4D
		};

		charz cipher; std::string plain; // the results

		FCT_TEST_BGN(aes256_cbc_encrypt)
		{
			ys::aes::estream estr;
			estr << ys::key(password);
			estr << ys::iv(init_vector);
			estr << given_plain << ys::endd;
			estr >> cipher;
			fct_chk(cipher == given_cipher);
		}
		FCT_TEST_END();

		FCT_TEST_END(aes256_cbc_decrypt)
		{
			ys::aes::dstream dstr;
			dstr << ys::key(password);
			dstr << ys::iv(init_vector);
			dstr << cipher << ys::endd;
			dstr >> plain;
			fct_chk(plain == given_plain);
		}
		FCT_TEST_END();
	}
	FCT_SUITE_END();

	FCT_SUITE_BGN(Twofish)
	{
		charz given_cipher=
		{
			// used : http://twofish.online-domain-tools.com/
			 0xFA, 0x1C, 0x66, 0x60, 0x0C, 0x1A, 0x4B, 0x5D,
			 0xEB, 0x9B, 0x77, 0xB9, 0xF1, 0x2D, 0x5A, 0x2E,
			 0x48, 0xAE, 0xC2, 0xE0, 0xB3, 0x00, 0xAE, 0xC8,
			 0x8E, 0x72, 0xB9, 0xF0, 0x04, 0xB4, 0xD3, 0x69,
			 0x77, 0xFE, 0xFE, 0x6B, 0x07, 0x08, 0xEE, 0xB4,
			 0x9A, 0x7F, 0x34, 0xB9, 0xDE, 0x25, 0x39, 0x05
		};

		charz cipher; std::string plain; // the results
	
		FCT_TEST_BGN(twofish_cbc_encrypt)
		{
			ys::arcfour::estream estr;
			estr << ys::key(password);
			estr << ys::iv(init_vector);
			estr << given_plain << ys::endd;
			estr >> cipher;
			fct_chk(cipher == given_cipher);
		}
		FCT_TEST_END();
	}
	FCT_SUITE_END();

}
FCT_END();

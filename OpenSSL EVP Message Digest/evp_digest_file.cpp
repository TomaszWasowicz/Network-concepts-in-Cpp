/*
OpenSSL Message Digest : A Message Digest or Hash Function takes any arbitrary message 
(with any content or length) as an input and provides a fixed size 
hash value as a result

 1) Message Digest implements a secure one-way function.
	Original Data -> Secure Hash Value
 2) From Hash Value there is no indication about the
	original data that produced it.
 3) The only way to identify the original data is to “brute-force”
	through every  possible combination of inputs.
 4) Every message digest algorithm has a fixed-length output
	Example:
	SHA256  : Secure Hash Algorithm 256 bits hash value 32 Bytes
	MD5     : The MD5 message-digest algorithm 128-bits hash value 16 bytes.
	SHA512  : Secure Hash Algorithm 512 bits hash value 64 Bytes (Longest Known)
 5) Two distinct inputs the probability that both yield the same output is
	highly unlikely.

Usage Example : 
1) create unique identifiers for arbitrary data or binary documents. 
2) ideal for public key signature algorithms 
3) To validate the integrity of a signed document 
4) Digital signatures or Digital certificates

Supported digest 
SHA, SHA1, SHA224, SHA256, SHA384 and SHA512, 
MD2, MD4, MDC2 and MD5

*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <openssl/evp.h>

int main(int argc, char* argv[])
{
	EVP_MD_CTX* mdctx;
	const EVP_MD* md;
	int inByte = 0;
	BIO *bio_in = NULL;
	BIO *bio_out = NULL;

	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned char plaintext[EVP_MAX_MD_SIZE];
	unsigned int md_len;

	memset (md_value, '\0', EVP_MAX_MD_SIZE);
	memset  (plaintext, '\0', EVP_MAX_MD_SIZE);

	if (argc != 4) {
		printf("Usage: evp_digest_file <algorithm> <In Data File> <Out Hash File>\n");
		printf("Example : evp_digest_file SHA256 text_data.txt has_data.dat\n");
		printf("Supported Digest Algorithm :\n");
		printf(" SHA, SHA1, SHA224, SHA256, SHA384 and SHA256 \n");
		printf(" MD2, MD4, MDC2 and MD5 \n");
		exit(1);
	}

	bio_in = BIO_new_file(argv[2], "r");
	bio_out = BIO_new_file(argv[3], "wb");

	md = EVP_get_digestbyname(argv[1]);
	if (md == NULL) {
		printf("unknown message digest %s\n", argv[1]);
		exit(1);
	}

	// 1)create a message digest context
	mdctx = EVP_MD_CTX_new();

	// 2)Initialize the context
	EVP_DigestInit_ex(mdctx, md, NULL);

	while ((inByte = BIO_read(bio_in, plaintext, EVP_MAX_MD_SIZE)) > 0) {
		// 3)Digest (Hashes) data into context
		EVP_DigestUpdate(mdctx, plaintext, inByte);
	}

	//4)Finalize retrieves result from ctx
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);

	//5) Cleans up digest context ctx
	EVP_MD_CTX_free(mdctx);

	BIO_write(bio_out, md_value, md_len);
	BIO_free(bio_in);
	BIO_free(bio_out);


	exit(0);
}
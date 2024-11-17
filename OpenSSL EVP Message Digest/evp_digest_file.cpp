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
	unsigned char plaintext[EVP_MAAX_MD_SIZE];
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
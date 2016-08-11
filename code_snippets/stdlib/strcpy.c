#include <stdio.h>

char *strcpy(char *dest, const char *src)
{
	int i;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];

	dest[i] = '\0';	
	return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';
	
	return dest;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	int i;

	for (i = 0; i < n; i++) {
		if (s1[i] != s2[i])
			return s1[i] - s2[i];
		else if (s1[i] == '\0')
			return 0;
	}

	return 0;
}

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
#define ALIGN 4

void *memcpy(void *dest, const void *src, size_t n)
{
	int index = 0;
	uint8_t *t_dest = (uint8_t *) dest;
	uint8_t *t_src = (uint8_t *) src;

	/* It is not possible to align both source and destination pointers,
	 * following aligns destination only and then copies data
	 * word-by-word, a little more efficient than byte copy
	 */

	while ((index < n) && ((size_t) t_dest & ~(ALIGN-1))) {
		*t_dest++ = *t_src++;
		index++;
	}	

	uint32_t *w_dest = (uint32_t *) t_dest;
	uint32_t *w_src = (uint32_t *) t_src;

	while (index < (n - sizeof(uint32_t))) {
		*w_dest++ = *w_src++;
		index += sizeof(uint32_t);
	}

	t_dest = (uint8_t *) w_dest;
	t_src = (uint8_t *) w_src;

	while (index < n) {
		*t_dest++ = *t_src++;
		index++;
	}

	return dest;
}

int main()
{
	char src[] = "Hello World";
	char src1[] = "Foo Bar";
	char dest[64];

	strcpy(dest, src);
	printf("Dest string is :%s:\r\n", dest);

	strncpy(dest, src1, sizeof(dest));
	printf("Dest string is :%s:\r\n", dest);

	int a[] = {0x1, 0x55, 0x33, 0x22, 0x33, 0x44, 0x44,
			 0x55, 0x56, 0x57, 0x58, 0x59, 0x60};

	int b[64];
	memset(b, 0, sizeof(b));
	memcpy(b, a, 13 * sizeof(int));

	for (int i = 0; i < (sizeof(b) / sizeof b[0]); i++)
		printf("Val is 0x%x\n", b[i]);		


	printf("Compare strings %d\n", strncmp(src1, dest, sizeof(src1)));
	return 0;
}

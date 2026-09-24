#include <stdio.h>
#include <string.h>

char name[15]; // Address: 0x0804c034
char logged_in = 0; // Address: 0x0804c043
 
static
void
authenticate_admin (void)
{
	char pass[16];
	printf("Please enter your username:\n");
	gets(name);
 
	if (!strncmp(name, "admin", 4)) {
		if (logged_in == '1') {
			printf("Welcome back!\n");
		} else {
			printf("Please enter your password\n");
			fgets(pass, sizeof(pass), stdin);
		}
	} else {
		printf("Admins only!\n");
	}
}

int main() {
    authenticate_admin();
}
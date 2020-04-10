#include <unistd.h>
int main(int c, char** argv)
{
    execv("find.exe" , argv);
	return 0;
}
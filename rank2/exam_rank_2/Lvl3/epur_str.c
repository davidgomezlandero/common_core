#include <unistd.h>

int main (int argc, char **argv)
{
    int i = 0;
    int flag = 0;

    while (argv[1][i] == 32 || argv[1][i] == 9)
        i++;
    if (argc == 2)
    {
        while(argv[1][i] != '\0')
        {
            if(argv[1][i] == 32 || argv[1][i] == 9)
            {
                if (flag == 0)
                    write (1, " ", 1);
                flag++;
            }
            if(argv[1][i] != 32 && argv[1][i] != 9)
            {
                flag = 0;
                write(1, &argv[1][i], 1);
            }
            i++;
        }
    }
    write (1, "\n", 1);
}


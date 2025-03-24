#include <curses.h>

int main(int argc, char const *argv[])
{
    initscr();
    char t;
    size_t i = 0;
    char str[20];
    while ((t = getch()) != '\n')
    {
        str[i++] = t;
    printf("%c\n", str);

    }
    
    endwin();

    return 0;
}

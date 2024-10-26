#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
void show_board(char *t1, char *t2, char p1, char p2, char p3, char p4, int co, int moves, int pairs, int score, bool matchbool);
int main()
{
    char t1[36], t2[36], p1, p2, p3, p4;
    char ch[] = "ABCDE!@#$&{}=<>|:,", inp[100];
    int moves = 0, score = 0, pairs = 18, co;
    bool matchbool = false;
    srand(time(NULL));
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            t1[y * 2 + x] = ch[y];
            t2[y * 2 + x] = 0;
        }
    }
    for (int i = 0; i < 100; i++)
    {
        int n1 = rand() % 36;
        int n2 = rand() % 36;
        int n = t1[n2];
        t1[n2] = t1[n1];
        t1[n1] = n;
    }
    while (pairs > 0)
    {
        co = 0;
        show_board(t1, t2, p1, p2, p3, p4, co, moves, pairs, score, matchbool);
        printf("\nMove (format albl)? ");
        scanf("%s", inp);
        if (strlen(inp) == 4)
        {
            p1 = inp[0] - 'a';
            p2 = inp[1] - '1';
            p3 = inp[2] - 'a';
            p4 = inp[3] - '1';
            if (!((p1 == p3) && (p2 == p4)))
            {
                if (((p1 >= 0) && (p1 <= 5)) && ((p2 >= 0) && (p2 <= 5)) && ((p3 >= 0) && ((p3 <= 5)) && (p4 >= 0) && (p4 <= 5)))
                {
                    if ((t2[p1 * 6 + p2] == 0) && (t2[p3 * 6 + p4] == 0))
                    {
                        t2[p1 * 6 + p2] = 1;
                        t2[p3 * 6 + p4] = 1;
                        moves++;
                        co = 1;
                        show_board(t1, t2, p1, p2, p3, p4, co, moves, pairs, score, matchbool);
                        sleep(1);
                        pairs--;
                        if (t1[p1 * 6 + p2] != t1[p3 * 6 + p4])
                        {
                            t2[p1 * 6 + p2] = 0;
                            t2[p3 * 6 + p4] = 0;
                            pairs++;
                            
                        }else{
                            score++;
                            matchbool = true;
                        }
                    }
                }
            }
            
            
        }
    }
    printf("Game over!\n");
    return (0);
}
void show_board(char *t1, char *t2, char p1, char p2, char p3, char p4, int co, int moves, int pairs, int score, bool matchbool)
{
    printf("\e[2J\e[H\e[39m\nMemory game by Harshita\n\n");
    printf("Max score: %d Moves: %d Pairs left: %d", score, moves, pairs);
    if(matchbool == true){
        printf(" Matched - Score 1 Added \n\n");
    }else{
        printf(" Not Matched - Score 0\n\n");
    }
    printf("  1 2 3 4 5 6\n\n");

    for (int y = 0; y < 6; y++)
    {
        printf("\e[39m%c ", 'A' + y); // Row labels A, B, C, ...

        for (int x = 0; x < 6; x++)
        {
            printf("\e[94m"); // Set text color to blue

            if (co == 1)
            {
                // Highlight the selected pairs in green
                if (((p1 == y) && (p2 == x)) || ((p3 == y) && (p4 == x)))
                {
                    printf("\e[92m"); // Set text color to green
                }
            }

            if (t2[y * 6 + x] == 1)
            {
                // Print revealed character
                printf("%c", t1[y * 6 + x]);
            }
            else
            {
                // Print '+' for hidden cells
                printf("\e[39m+ ");
            }
        }
        printf("\n\n");
    }
    printf("\e[39m");
}
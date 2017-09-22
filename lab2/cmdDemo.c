#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void math();

void dogBark();

int main()
{
    char cmd[128];
    while(1)
    {
        scanf("%s", cmd);
        if(strcmp(cmd, "help") == 0)
        {
            printf("This is help cmd!\n");
        }
        else if(strcmp(cmd, "quit") == 0)
        {
            exit(0);
        }
        else if(strcmp(cmd, "math") == 0)
        {
            math();
        }
        else if(strcmp(cmd, "bark") == 0)
        {
            dogBark();
        }
        else if(strcmp(cmd, "story") == 0)
	{
            printf("Formerly have a mountain ...\n");
        }
        else if(strcmp(cmd, "meat") == 0)
        {
            printf("uh...! It's delicious!\n");
        }
        else if(strcmp(cmd, "happy") == 0)
        {
            printf("hahaheheheiheihohoxiaxia\n");
        }
        else
        {
            printf("Cmd is wrong!\n");
        }
    }
}

void math()
{
    printf("1 + 2 = %d\n", 1+2);
}
void dogBark()
{
    printf("Woo Woo ... !\n");
}


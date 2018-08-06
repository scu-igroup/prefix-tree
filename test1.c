#include <stdio.h>        // for printf()
#include <sys/time.h>    // for gettimeofday()
#include <unistd.h>        // for sleep()
#include "suffix.h"
int main()
{
    struct timeval start, end;
    PNode root = NULL;
    float average_usec = 0;
    float average_sec= 0;
    float average = 0;
    float x = 0;
    int i;
    int num=0;
    char buff[1024] = { "\0" };
    FILE *fp = NULL;

//calculate the time of build the tree
    
    for(i=0;i<10;i++)
{
    gettimeofday( &start, NULL ); 
    root = Build_tree("/home/handsome/Public/c2/domain_list.txt",1);   
    gettimeofday( &end, NULL );
    x = end.tv_usec-start.tv_usec+( end.tv_sec- start.tv_sec)*1000000;   
    average = average +x;
} 
    printf("the average of ten times of building the tree:%lfus\n",average/10);   

while(1)
{
       average = 0;
       num = 0;
       fp = fopen("/home/handsome/Public/c2/URL_WhiteFilter.conf", "r");
	while (fgets(buff, 1024, fp))

      {
        for (i = 0; i < strlen(buff); i++)
	{
		if (buff[i] == '\r' || buff[i] == '\n')
		{
			buff[i] = '\0';
		}		
	}
        gettimeofday( &start, NULL );
        if (!Search_Tree(buff, root, root, 1, 1))
	{
		//printf("no this word\n");
                //printf("%s\n",buff);
                //printf("num:%d\n",num);

	} 
         gettimeofday( &end, NULL ); 
         x = end.tv_usec-start.tv_usec+( end.tv_sec- start.tv_sec)*1000000;
         //printf("the x is :%lf\n",x);
         average = average +x;
         num++;
      } 
    printf("the average of the time of search tree(about 60000 datas):%lfus\n",average/num);
   fclose(fp);
 }
    return 0;
}

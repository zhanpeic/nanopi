#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libfahw.h"

void test(char* line1, char* line2)
{
    int devFD;
    if ((devFD = LCD1602Init()) == -1) {
        printf("Fail to init LCD1602\n");
        return;
    }

	    if (LCD1602Clear(devFD) == -1) {
		    printf("Fail to Clear\n");
		    return;
	    }
    
    if (LCD1602DispLines(devFD, line1, line2) == -1) {
        printf("Fail to Display String\n");
        return ;
    }
    
    LCD1602DeInit(devFD);
}

int main(int argc, char ** argv) {
    int i;
    for (i=0; i<1000; i++) {
         //test("FriendlyARM", "NanoPi & Matrix");
	 test("IIC B&G Char LCD","--by FriendlyARM");
         sleep(3000);
    }
    return 0;
}










#include <stdio.h>
#include <string.h>

int main(){
	char source[101];
	char target[101];
	
	printf("Source file? : ");
	scanf("%100s",source);

	while(getchar() != '\n');
	
	FILE* sourceFile = fopen(source,"rb");
	if(!sourceFile){
		printf("There is no such file.\n");
		return 0;
	}

	printf("Target file? : ");
	scanf("%100s",target);
	
	FILE* targetFile;
	if(fopen(target, "r")){
		printf("That file is aleady exist.\n");
		return 0;
	}
	targetFile = fopen(target, "wb");
	
	unsigned char buffer[1024];
	int count;
	
       	while(count = fread(buffer,sizeof(char),1024,sourceFile)){
		fwrite(buffer,sizeof(char),count,targetFile);
	}

	fclose(targetFile);
	fclose(sourceFile);

	return 0;
}


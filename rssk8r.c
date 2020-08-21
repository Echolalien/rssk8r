/* rssk8r.c
 *
 * Copyright 2020 @echolalien
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
______  _____   ___   _      _     __   __              
| ___ \|  ___| / _ \ | |    | |    \ \ / /              
| |_/ /| |__  / /_\ \| |    | |     \ V /               
|    / |  __| |  _  || |    | |      \ /                
| |\ \ | |___ | | | || |____| |____  | |                
\_| \_|\____/ \_| |_/\_____/\_____/  \_/                
                                                        
                                                        
 _____  _____  _____  _   __                            
/  ___||_   _|/  __ \| | / /                            
\ `--.   | |  | /  \/| |/ /                             
 `--. \  | |  | |    |    \                             
/\__/ / _| |_ | \__/\| |\  \                            
\____/  \___/  \____/\_| \_/                            
                                                        
                                                        
 _____ __   __ _   _ ______  _____  _   __ _____ ______ 
/  ___|\ \ / /| \ | ||  _  \|_   _|| | / /|  _  || ___ \
\ `--.  \ V / |  \| || | | |  | |  | |/ /  \ V / | |_/ /
 `--. \  \ /  | . ` || | | |  | |  |    \  / _ \ |    / 
/\__/ /  | |  | |\  || |/ /  _| |_ | |\  \| |_| || |\ \ 
\____/   \_/  \_| \_/|___/   \___/ \_| \_/\_____/\_| \_|
                                                        
Updates and documentation at github.com/echolalien/rssk8r
                              
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char version[] = "1.0";

unsigned int itemCount = 0; //keep a record of how many pushes in this session
char filepath[200];         //path to the rss file you're pushing to
FILE *fp1, *fp2;            //file pointers
int linectr = 0;            //line counter for rewrite
char str[256];              //buffer for line copying 

//input fields for user
char url[256];
char guid[256];
int guidMode = 0;
char title[256];
char descr[512];

//time collection
time_t rawtime;
char timebuffer[200];
struct tm* timeinfo;

int main(int argc, char *argv[]){

  
  printf("RSSK8R(REALLY SICK SYNDIK8R)- barebones rss feed pusher. Version %s. Please see github.com/echolalien/rssk8r for documentation. Released under GPLv3. Press CTRL+C to exit.\n", version);
	//identify file path, check arguments. if file path not given, prompt for it.
	if(argc>2){
		printf("Too many arguments, only argument should be rss file location.\n");
		exit(EXIT_FAILURE);
	} else if(argc>1){
		strcpy(filepath, argv[1]);
	} else{
		printf("Enter rss file location (must be .xml): ");
		fgets(filepath, 200, stdin);
		strtok(filepath, "\n");
	}

  //check file exists and is of correct type             
	if((fp1 = fopen(filepath, "r"))){
		fclose(fp1);
	} else {
		printf("File doesn't exist.\n"); //todo: create file dialog
		exit(EXIT_FAILURE);
	}
	char * end = strrchr(filepath, '.');
	if(strcmp(end, ".xml") != 0){
		printf("File is not an .xml file.\n");
		exit(EXIT_FAILURE);
	}
	printf("Pushing to %s\n", filepath);

  //find the start of the item declarations
	fp1 = fopen(filepath, "r");
	char searcher[4] = "item";
	int lno = 0; //current line number
  int found = 0;
	while(fgets(str, 256, fp1) != NULL) {
		if((strstr(str, searcher)) != NULL) {
			//printf("First item found on line: %d\n", lno+1);
      ++found;
			break;
		}
		lno++;
	}
  if(found == 0){
    printf("Couldn't find any items. Is this an rss file? If so, please"
    " create at least one dummy item by typing <item></item>.\n");
    exit(EXIT_FAILURE);
  }
  fclose(fp1);
  
	while(1){

   	printf( "Enter URL (max 256 characters): ");
   	fgets(url, 256, stdin);
		strtok(url, "\n");
    
    if(guidMode){
     	printf( "Enter unique post ID (max 256 characters): ");
     	fgets(guid, 256, stdin);
		  strtok(guid, "\n");
    } else{
      strcpy(guid, url);
    }
      
		printf("Enter title (max 256 characters): ");
		fgets(title, 256, stdin);
    strtok(title, "\n"); 

		printf("Enter description (max 512 characters): ");
		fgets(descr, 512, stdin);
		strtok(descr, "\n");

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(timebuffer, 200, "%a, %d %b %Y %X %Z", timeinfo);
		++itemCount;

    char itembuffer[2048] = "butts";
    snprintf(itembuffer, 2048, "<item>\n\t<title>%s</title>\n\t<link>%s"
      "</link>\n\t<guid>%s</guid>\n\t<pubDate>"
			"%s</pubDate>\n\t<description>%s</description>\n"
			"</item>\n\n", title, url, guid, timebuffer, descr);
    printf("\nPushing:\n%s", itembuffer);
    
    //edit file to create new item at top of items list
    char temp[] = "temp.txt"; //temporary doc for overwrite
    linectr = 0;
    fp1 = fopen(filepath, "r");
    if (!fp1) {
            printf("Lost access to rss file!\n");
            return 0;
    }  fp2 = fopen(temp, "w");
    if (!fp2) {
        printf("Unable to create temporary file!n");
        fclose(fp1);
        return 0;
    }
    while (!feof(fp1)) 
    {
        strcpy(str, "\0");
        fgets(str, 512, fp1);
        if (!feof(fp1)) 
        {
            linectr++;
            fprintf(fp2, "%s", str);
            if (linectr == lno) {
                //printf ("Inserting new lines after line %d\n", lno);
                fprintf(fp2, "%s", itembuffer);
            }
         }
    }
    fclose(fp1);
    fclose(fp2);
    remove(filepath);
    rename(temp, filepath);
    printf("Push successful!\n");
    
		printf("You have pushed %u posts this session.\n", itemCount);

	}

	return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>

int showFile(char *path, char *filename);
int showDirectory(char *dirname);
int showSubFile(char* path);
int showAll(char* path);
int showAllInode(char* path);
int ls_l(char *path);
int ls_d(char *path);
int ls_R(char *path);
int ls_a(char *path);
int ls_i(char *path);

int main(int argc, char **argv) {
    struct stat statbuf;
    char *path;
    char tempPath[128];
    if (path == NULL || path[0] == '-') {
        path = tempPath;
        getcwd(path, 128);
    }

	if (argc == 1) {
	    if (S_ISDIR(statbuf.st_mode)) {
			showDirectory(path);
	    } else {
			printf("%s\n", path);
	    }
	    return 0;
	} else if (argc == 3) {
   		path = argv[2];
	}

    char opt;
    char *optString = "ldRai";
    while((opt = getopt(argc, argv, optString)) != -1) {
        switch (opt) {
            case 'l':
		        ls_l(path);
		        break;
            case 'd':
		        ls_d(path);
		        break;
            case 'R':
		        ls_R(path);
		        break;
            case 'a':
		        ls_a(path);
		        break;
            case 'i':
		        ls_i(path);
                break;
            default:
                printf("Unknown option: %c\n", (char)opt);
                break;
        }
    }

    return 0;
}

int ls_l(char *path) {
	struct stat st;
	
	if (stat(path, &st) < 0) {
		printf("Error: No such directory or file\n");
		return -1;
    } else if ((st.st_mode & S_IFMT) == S_IFDIR) {
		showDirectory(path);
    } else {
		showFile(path, path);
    }
    return 1;
}

int showFile(char *path, char *filename) {
	struct stat st;							
	stat(path, &st);
	
	struct passwd *pw;
	struct group *gr;						
	struct tm *tm;							
	
	switch(st.st_mode & S_IFMT) {
		case S_IFREG:  
			printf("-");    
			break;
		case S_IFDIR:  
			printf("d");   	
			break;
		case S_IFLNK: 
			printf("l");    
			break;
		case S_IFBLK:  
			printf("b");    
			break;
		case S_IFCHR:  
			printf("c");    
			break;
		case S_IFIFO:  
			printf("p");    
			break;
		case S_IFSOCK: 
			printf("s");    
			break;
    }
	
	int i;
	for (i = 8; i >= 0; i--) {
        if (st.st_mode & (1 << i)) {
            switch(i % 3) {
				case 2: 
					printf("r"); 
					break;
				case 1: 
					printf("w"); 
					break;
				case 0: 
					printf("x"); 
					break;
            }
        } else {
            printf("-");
        }
    }
	
	pw = getpwuid(st.st_uid);
    gr = getgrgid(st.st_gid);
	printf("%2d %s %s %4lld", st.st_nlink, pw->pw_name, gr->gr_name, st.st_size);
	
	tm = localtime(&st.st_ctime);
    printf(" %04d-%02d-%02d %02d:%02d",tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);

    printf(" %s\n", filename);
    return 1;
}

int showDirectory(char *dirname) {
	DIR *dir = opendir(dirname);
	struct dirent *dirent;
	
	char buf[1024];
	struct stat st;
	while ((dirent = readdir(dir)) != NULL) {
		strcpy(buf, dirname);
        strcat(buf, "/");
        strcat(buf, dirent->d_name);
		
		if (stat(buf, &st) < 0) {
			printf("Error: No such directory or file\n");
            return -1;
        }

        if (dirent->d_name[0] != '.') {
            showFile(buf, dirent->d_name);
        }
	}
    return 1;
}

int ls_d(char *path) {
	struct stat st;
	
	if (stat(path, &st) < 0) {
		printf("Error: No such directory or file\n");
		return -1;
    } else {
		printf("%s\n", path);
    }
    return 1;
}

int ls_R(char *path) {
	struct stat st;
	
    if (stat(path, &st) < 0) {
		printf("Error: No such directory or file\n");
		return -1;
    } else if ((st.st_mode & S_IFMT) == S_IFDIR) {
		showSubFile(path);
    } else {
		printf("%s\n", path);
    }
    return 1;
}

int showSubFile(char* path) {
	printf("%s:\n", path);
	
	DIR *dir = opendir(path);
	struct dirent *dirent;
	
	char subPath[1024][1024];
	int num = 0;
	
	char buf[1024];
	struct stat st;
	while ((dirent = readdir(dir)) != NULL) {
		strcpy(buf, path);
        strcat(buf, "/");
        strcat(buf, dirent->d_name);
		stat(buf, &st);

        if (dirent->d_name[0] != '.') {
			printf("%s\t", dirent->d_name);
			if ((st.st_mode & S_IFMT) == S_IFDIR) {
				strcpy(subPath[num], buf);
				num++;
			}
		}
	}
	printf("\n");

	num--;
	for (; num >= 0; num--) {
		showSubFile(subPath[num]);
	}
    return 1;
}

int ls_a(char *path) {
	struct stat st;
	
	if (stat(path, &st) < 0) {
		printf("Error: No such directory or file\n");
		return -1;
    } else if ((st.st_mode & S_IFMT) == S_IFDIR) {
		showAll(path);
    } else {
		printf("%s\n", path);
    }
    return 1;
}

int showAll(char* path) {
	DIR *dir = opendir(path);
	struct dirent *dirent;
	
	while ((dirent = readdir(dir)) != NULL) {
		printf("%s\t", dirent->d_name);
	}
	printf("\n");
    return 1;
}

int ls_i(char *path){
	struct stat st;
	
	if (stat(path, &st) < 0) {
		printf("Error: No such directory or file\n");
		return -1;
    } else if ((st.st_mode & S_IFMT) == S_IFDIR) {
		showAllInode(path);
    } else {
		printf("%9llu %s\n", st.st_ino, path);
    }
    return 1;
}

int showAllInode(char* path) {
	DIR *dir = opendir(path);
	struct dirent *dirent;
	
	char buf[1024];
	struct stat st;
	while ((dirent = readdir(dir)) != NULL) {
		strcpy(buf, path);
        strcat(buf, "/");
        strcat(buf, dirent->d_name);
		stat(buf, &st);

        if (dirent->d_name[0] != '.') {
            printf("%9llu %s\t", st.st_ino, dirent->d_name);
        }
	}	
	printf("\n");
    return 1;
}

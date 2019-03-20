#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

int verbose_flag = 0; //by default, program should be in verbose

int main (int argc, char **argv){
  if(argc < 3){ //assuming that "ls" will always be called with flags
    printf("Too little arguments!\n");
    exit(0);
  }
  
  if(argc > 5){//assuming that arguments cannot exceed 5
    printf("Too many arguments!\n");
    exit(0);
  }
  
  struct stat fileinfo;
  struct dirent **dirinfo; 
  
  int i = 0;
  int n;
  
  if(argc == 4){
    //assumes that follows
    //./myls ls -flags [thing]
    
    if(lstat(argv[3], &fileinfo) < 0){
      printf("myls: cannot access %s: No such file or directory\n", argv[3]);
      exit(0);
    }
    
    if(S_ISDIR(fileinfo.st_mode)){
      n = scandir(argv[3], &dirinfo, NULL, NULL);
      
      if(n < 0)
        exit(0);
      
      for(; i < n; i++){
        if(!strcmp(argv[2], "-ai1")){
          printf("%d %s\n", (int) fileinfo.st_ino, dirinfo[i]->d_name);
        } else if(!strcmp(argv[2], "-ail1")){
        printf("%d ", (int) fileinfo.st_ino);
        //inode#
        printf( (S_ISDIR(fileinfo.st_mode)) ? "d" : "-");
        printf( (fileinfo.st_mode & S_IRUSR) ? "r" : "-");
        printf( (fileinfo.st_mode & S_IWUSR) ? "w" : "-");
        printf( (fileinfo.st_mode & S_IXUSR) ? "x" : "-");
        printf( (fileinfo.st_mode & S_IRGRP) ? "r" : "-");
        printf( (fileinfo.st_mode & S_IWGRP) ? "w" : "-");
        printf( (fileinfo.st_mode & S_IXGRP) ? "x" : "-");
        printf( (fileinfo.st_mode & S_IROTH) ? "r" : "-");
        printf( (fileinfo.st_mode & S_IWOTH) ? "w" : "-");
        printf( (fileinfo.st_mode & S_IXOTH) ? "x" : "-");
        //permissions
        printf(" %d ", (int) fileinfo.st_nlink);
        //# of hardlinks
        //printf("%s ", fileinfo.st_uid);
        //ownerid
        //printf("%s ", fileinfo.st_gid);
        //groupid
        printf("%d ", (int) fileinfo.st_size);
        //total size bytes
        //last mod
        printf("%s\n", dirinfo[i]->d_name);
        free(dirinfo[i]);
        }
      }
      //free(dirinfo);
    } else {
      if(!strcmp(argv[2], "-ai1")){
        printf("%d %s\n", (int) fileinfo.st_ino, argv[3]);
      } else if(!strcmp(argv[2], "-ail1")){
        printf("%d ", (int) fileinfo.st_ino);
        //inode#
        printf( (S_ISDIR(fileinfo.st_mode)) ? "d" : "-");
        printf( (fileinfo.st_mode & S_IRUSR) ? "r" : "-");
        printf( (fileinfo.st_mode & S_IWUSR) ? "w" : "-");
        printf( (fileinfo.st_mode & S_IXUSR) ? "x" : "-");
        printf( (fileinfo.st_mode & S_IRGRP) ? "r" : "-");
        printf( (fileinfo.st_mode & S_IWGRP) ? "w" : "-");
        printf( (fileinfo.st_mode & S_IXGRP) ? "x" : "-");
        printf( (fileinfo.st_mode & S_IROTH) ? "r" : "-");
        printf( (fileinfo.st_mode & S_IWOTH) ? "w" : "-");
        printf( (fileinfo.st_mode & S_IXOTH) ? "x" : "-");
        //permissions
        printf(" %d ", (int) fileinfo.st_nlink);
        //# of hardlinks
        //printf("%s ", fileinfo.st_uid);
        //ownerid
        //printf("%s ", fileinfo.st_gid);
        //groupid
        printf("%d ", (int) fileinfo.st_size);
        //total size bytes
        //last mod
        printf("%s\n", argv[3]);
        //free(dirinfo[i]);
      }
    }
  } else {
    //just print out everything in directory
    n = scandir(".", &dirinfo, NULL, alphasort);
    
    if(n < 0)
      exit(0);
    //printf("%d %d\n", i, n);
    for(; i < n; i++){
      //printf("%s\n", dirinfo[i]->d_name);
      if(!strcmp(argv[2], "-ai1")){
        if(lstat(dirinfo[i]->d_name, &fileinfo) == 0){
          printf("%d %s\n", (int) fileinfo.st_ino, dirinfo[i]->d_name);
        }
      } else if(!strcmp(argv[2], "-ail1")){
        if(lstat(dirinfo[i]->d_name, &fileinfo) == 0){
          printf("%d ", (int) fileinfo.st_ino);
          //inode#
          printf( (S_ISDIR(fileinfo.st_mode)) ? "d" : "-");
          printf( (fileinfo.st_mode & S_IRUSR) ? "r" : "-");
          printf( (fileinfo.st_mode & S_IWUSR) ? "w" : "-");
          printf( (fileinfo.st_mode & S_IXUSR) ? "x" : "-");
          printf( (fileinfo.st_mode & S_IRGRP) ? "r" : "-");
          printf( (fileinfo.st_mode & S_IWGRP) ? "w" : "-");
          printf( (fileinfo.st_mode & S_IXGRP) ? "x" : "-");
          printf( (fileinfo.st_mode & S_IROTH) ? "r" : "-");
          printf( (fileinfo.st_mode & S_IWOTH) ? "w" : "-");
          printf( (fileinfo.st_mode & S_IXOTH) ? "x" : "-");
          //permissions
          printf(" %d ", (int) fileinfo.st_nlink);
          //# of hardlinks
          //printf("%s ", fileinfo.st_uid);
          //ownerid
          //printf("%s ", fileinfo.st_gid);
          //groupid
          printf("%d ", (int) fileinfo.st_size);
          //total size bytes
          //last mod
          printf("%s\n", dirinfo[i]->d_name);
          free(dirinfo[i]);
        }
        //free(dirinfo);
      }
    }
  }
}
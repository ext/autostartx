//autostartx-bin.c
//by moowei
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <grp.h>

int main(int argc, char *argv[])
{
	struct passwd *userinfo;

	if(argc < 2){
		printf("No specified username. Exit.\n");
		exit(1);
	}   
   
	userinfo = getpwnam(argv[1]);
	if (userinfo == NULL){
		printf("User does not exist. Exit.\n");
		exit(1);
	}
   
	if ( initgroups(userinfo->pw_name, userinfo->pw_gid) == -1){
		printf("Cannot initgroups. Exit.\n");
		exit(1);
	}

	if ( setgid(userinfo->pw_gid) == -1){
		printf("Cannot setgid. Exit.\n");
		exit(1);
	}

	setenv("USER", userinfo->pw_name, 1);
	setenv("USERNAME", userinfo->pw_name, 1);
	setenv("LOGNAME", userinfo->pw_name, 1);
	setenv("HOME", userinfo->pw_dir, 1);
	setenv("SHELL", userinfo->pw_shell, 1);

	if ( setuid(userinfo->pw_uid) == -1){
		printf("Cannot setuid. Exit.\n");
		exit(1);
	}

	chdir(userinfo->pw_dir);
	execlp("startx", "startx", NULL);
   
	return 0;
}

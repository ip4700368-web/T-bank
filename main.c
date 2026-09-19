// gcc main.c -o chall -no-pie -O0 -lseccomp
#define _GNU_SOURCE
#include <seccomp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char flag[] = "nto{***REDACTED***}";

void init() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

static void install_seccomp(void) { // ;)
    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);

    if (!ctx ||
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0) < 0 ||
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0) < 0 ||
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0) < 0 ||
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0) < 0 ||
        seccomp_load(ctx) < 0) {
        perror("seccomp");
        exit(1);
    }
}

void menu() {
    puts("====================");
    puts("=== ARRAY BINARY ===");
    puts("====================");
    puts("Features:");
    puts("1) edit array");
    puts("2) print array");
    puts("3) exit");
}

void win() {
    puts(flag);
}

int main() {
    size_t array[32];
    memset(array, 0, sizeof(array));

    init();
    menu();
    install_seccomp();

    int choice, ln;
    while(1){
	printf("Your choice > ");
	scanf("%d", &choice);
        switch(choice) {
	    case 1:
		    printf("Input idx of last element > ");
    		scanf("%d", &ln);
    		for(int i = 0; i < ln; i++) {
                printf("> ");
		        scanf("%lld", &array[i]);
    		}
    		puts("Done.");
		    break;
	    case 2:
		    puts("Array:");
		    for(int i = 0; i < 32; i++) {
		        printf("[%lld] --> %lld\n", i+1, array[i]);
		    }
		    break;
	    case 3:
	        return 0;
    	}
    }
}

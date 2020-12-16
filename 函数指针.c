#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char *name;
    int (*func)(void);
    int flags;
    int argcmin;
    char *argc_errmsg;
} cmds_t;

static int subcmd(const cmds_t tab[], int argc, char *argv, void *p)
{
    cmds_t *cmdp;
    int i;

    for(cmdp = tab; cmdp->name != NULL; cmdp++){
        if(strncmp(argv,cmdp->name, strlen(argv)) == 0){
            printf("success");
            printf("funcation = %s \n", cmdp->name);
            // printf("\n name = %s\n", cmdp->func);
            printf("\n flags = %d\n",cmdp->flags);
            printf("\n funcation = %p\n",cmdp->func);
            break;
        }
    }
    printf("over");
    return (*cmdp->func)();//(argc,argv,p);
}
// int argc,char *argv, void *p
static int do_create()
{

    int id;
    printf("\rdo_create:");
    return 0;
}

static cmds_t cfgcmds[] = {
    {"create",do_create, 0x01, 0 ,NULL},
    { NULL,  NULL, 0x01,0 ,NULL}

};

int main()
{

    printf("pointer = %p\n",do_create);
    subcmd(cfgcmds, 1, "create", NULL);
    return 0;
}

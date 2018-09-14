#include <stdio.h>
#include "dnsmasq.h"
#include "uthash.h"

void add_user_by_table(unsigned int user_id, char* name, hash_struct **hash_id, hash_struct **hash_name)
{
    struct hash_struct *s=NULL;
    HASH_FIND(hh2, (*hash_name), name, strlen(name), s);
    if (!s) {
        s = (struct hash_struct*)malloc(sizeof(struct hash_struct));
        s->id = user_id;
        strcpy(s->name, name);
        my_syslog(LOG_INFO, "[add_usr_by_table]name:%s", s->name);
        /* add the structure to both hash tables */
        HASH_ADD(hh1, (*hash_id), id, sizeof(int), s);
        HASH_ADD(hh2, (*hash_name), name, strlen(s->name), s);
    }
}

void print_users_by_table(hash_struct *hash_id, hash_struct *hash_name)
{
    struct hash_struct *s=NULL;

    my_syslog(LOG_INFO, "[print_users_by_table]");
    for(s=hash_name; s != NULL; s=(struct hash_struct*)(s->hh2.next)) {
        my_syslog(LOG_INFO, "[print_users_by_table]user id %d: name %s", s->id, s->name);
    }
}

void clr_user(hash_struct **hash_id, hash_struct **hash_name)
{
    struct hash_struct *current_user, *tmp;

    HASH_ITER(hh1, (*hash_id), current_user, tmp) {
        HASH_DELETE(hh1, (*hash_id), current_user);    /* delete; users advances to next */
        HASH_DELETE(hh2, (*hash_name), current_user);  /* delete; users advances to next */
        free(current_user);  /* optional- if you want to free  */
    }
}

int hit_hash_by_table(char* hash_value, struct hash_struct *hashtable)
{
    struct hash_struct *s=NULL;
    HASH_FIND(hh2, hashtable, hash_value, strlen(hash_value), s);
    if (s) {
        my_syslog(LOG_INFO, "[hit_hash]hash hit:%s", hash_value);
        return 1;
    }
    return 0;
}

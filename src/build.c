#include "../include/vshcfp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024

/* Globals */
char *entry_field;

void analize(HcfOpts opts, char *exec_seq);

char *
extend_get(HcfOpts opts, char *default_field, char *extend_key)
{
    char *c;

    c = strchr(extend_key, '.');

    if (!c)
    {
        return hcf_get(opts, default_field, extend_key);
    }

    *c = '\0';
    return hcf_get(opts, extend_key, c + 1);
}

void
execute(HcfOpts opts, char *seq)
{
    char  buf[MAXLEN] = { 0 };
    char *key_intro;
    char *key_sep;
    char *value;

    // printf("[SEQ] %s\n", seq);

    if (!seq)
    {
        printf("Invalid sequence!\n");
        return;
    }

    key_sep = seq;
    while (key_sep && (key_intro = strchr(seq, '$')))
    {
        *key_intro = '\0';
        strcat(buf, seq);

        key_sep = strchr(key_intro + 1, ' ');
        if (key_sep)
            *key_sep = '\0';


        // printf("Entry field: %s\n", entry_field);
        if ((value = extend_get(opts, entry_field, key_intro + 1)))
            strcat(buf, value);

        /* Getting from default field */
        else if ((value = extend_get(opts, "default", key_intro + 1)))
            strcat(buf, value);

        else
            printf("Can not found %s key!\n", key_intro + 1);

        strcat(buf, " ");
        seq = key_sep + 1;
    }
    if (key_sep && *seq)
        strcat (buf, seq);
    /* Si acaba por un comando constante y no definido en
     * otro campo seguramente no lo pille */

    printf("> exec: %s\n", buf);
    system(buf);
}

void
analize(HcfOpts opts, char *exec_seq)
{
    char *entry_point;
    char *cur_seq;
    char *temp;
    char *c;

    entry_point = exec_seq;

    while (entry_point && *entry_point)
    {
        c = strchr(entry_point, ' ');
        if (c)
            *c = '\0';

        // printf("Current entry: (%s).%s\n", entry_field, entry_point);
        cur_seq = extend_get(opts, entry_field, entry_point);
        // printf("CURSEQ: %s\n", cur_seq);
        if (cur_seq)
            execute(opts, cur_seq);

        /* If it is a field name, execute its exec */
        else if (hcf_get_field(opts, entry_field))
        {
            temp        = entry_field;
            entry_field = entry_point;
            analize(opts, extend_get(opts, entry_point, "exec"));
            entry_field = temp;
        }

        else
            printf("Invalid entry!");


        /* Removing spaces */

        if (c)
            do
            {
                ++c;
            } while (*c == ' ');

        entry_point = c;
    }
}


int
main(int argc, char *argv[])
{
    HcfOpts opts;
    char   *exec_seq;

    if (argc == 2)
        entry_field = argv[1];
    else
        entry_field = "default";

    opts = hcf_load("build.hcf");

    /* Opts were not created */
    if (opts.node_arr == NULL)
        exit(1);

    exec_seq = hcf_get(opts, entry_field, "exec");

    if (exec_seq == NULL)
    {
        printf("Can not find entry point %s.exec!\n", entry_field);
        hcf_destroy(&opts);
    }

    // printf("Exec sequence: %s\n", exec_seq);

    analize(opts, exec_seq);

    hcf_destroy(&opts);
    return 0;
}

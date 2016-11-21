/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: mrp
 *
 * Created on November 21, 2016, 3:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#define DEBUG

#define NB_RULES_DEFAULT 32
#define RULE_LEN_DEFAULT 8
#define WILDCARD_RATIO_DEFAULT 10
#define OUTPUT_FILE  "/home/mrp/msc_project/dummy_rules/RULES_NB%d_LEN%d_WR%.2f"

int nb_rules = 0;
int rule_len = 0;
float wildcard_ratio = 0;

void parse_args(int argc, char* argv[]) {
        int i;
        for (i = 1; i < argc; i += 2) {
#ifdef DEBUG
                printf("argv[%d] : %s\t\n", i, argv[i]);
#endif
                if (strcmp(argv[i], "--NB-RULES") == 0) {
                        nb_rules = atoi(argv[i + 1]);
                } else if (strcmp(argv[i], "--RULE-LEN") == 0) {
                        rule_len = atoi(argv[i + 1]);
                } else if (strcmp(argv[i], "--WILDCARD-RATIO") == 0) {
                        wildcard_ratio = atof(argv[i + 1]);
                } else {
                        printf("Usage: %s [--NB-RULES 1] [--RULE-LEN 2] [--WILDCARD-RATIO 3]\n", argv[0]);
                        exit(0);
                }
        }
        if (nb_rules == 0)
                nb_rules = NB_RULES_DEFAULT;
        if (rule_len == 0)
                rule_len = RULE_LEN_DEFAULT;
        if (wildcard_ratio == 0)
                wildcard_ratio = WILDCARD_RATIO_DEFAULT;
}

/*
 * 
 */
int main(int argc, char** argv) {

        parse_args(argc, argv);

        float wildcard_th = wildcard_ratio;
        float zero_th = (100 - wildcard_th) / 2 + wildcard_th;
        int i, j;
        FILE *fp;
        char *rule;
        float random;
        int pri;

        char *file_name;
        file_name = (char *) malloc(sizeof (OUTPUT_FILE) + 3);
        sprintf(file_name, OUTPUT_FILE, nb_rules, rule_len, wildcard_ratio);

        fp = fopen(file_name, "w");
        rule = (char *) malloc(rule_len + 1);
        srand(time(NULL));

        fprintf(fp, "NB_RULES=%d RULE_LEN=%d\n", nb_rules, rule_len);

        for (i = 0; i < nb_rules; i++) {
                for (j = 0; j < rule_len; j++) {
                        random = (float)((rand() % 10000) / 100.0);
                        if (random < wildcard_th)
                                rule[j] = '*';
                        else if (random >= wildcard_th && random < zero_th)
                                rule[j] = '0';
                        else
                                rule[j] = '1';
                }
                rule[rule_len] = '\0';
                pri = (rand() % 10) + 1;
                fprintf(fp, "ID:%-7d PRI:%-2d --> %s\n", i, pri, rule);
        }

        fclose(fp);
        sleep(1);

        return (EXIT_SUCCESS);
}


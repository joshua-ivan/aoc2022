#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aoc2022-13.h"

int parse_packet(packet* pt, char* raw) {
    int i = 0;

    if (isdigit(raw[i])) {
        char *atom_str = malloc(sizeof(char) * 4);
        do {
            atom_str[i] = raw[i];
        } while (isdigit(raw[++i])) ;

        pt->atom = atoi(atom_str);
        pt->list = NULL;

        free(atom_str);
    } else if (raw[i] == '[') {
        i++;

        packet *li = malloc(sizeof(packet) * 128);
        for (int j = 0; j < 128; j++) {
            li[j].atom = -1;
            li[j].list = NULL;
        }

        int j = 0;
        while (raw[i] != ']') {
            i += parse_packet(&li[j++], (raw + i));
            if (raw[i] == ',') {
                i++;
                continue;
            }
        }

        pt->atom = -1;
        pt->list = li;

        i++;
    } else {
        // do nothing
    }

    return i;
}

char* to_string(packet p) {
    if (p.atom > -1) {
        char* s = malloc(sizeof(char) * 4);
        sprintf(s, "%d", p.atom);
        return s;
    } else {
        char* s = malloc(sizeof(char) * 512);

        int num_subpackets = 0;
        char **subpackets = malloc(sizeof(char *) * 512);
        while (is_defined(p.list[num_subpackets])) {
            subpackets[num_subpackets] = to_string(p.list[num_subpackets]);
            num_subpackets++;
        }

        int i = 0;
        int j = 0;
        s[j++] = '[';
        while (i < num_subpackets) {
            strcpy((s + j), subpackets[i]);
            j += strlen(subpackets[i]);
            if (++i < num_subpackets) {
                s[j++] = ',';
            }
        }
        s[j] = ']';

        return s;
    }
}

packet wrap_atom(int a) {
    packet temp;

    temp.atom = -1;
    temp.list = malloc(sizeof(packet) * 128);
    for (int i = 0; i < 128; i++) {
        temp.list[i].atom = -1;
        temp.list[i].list = NULL;
    }
    temp.list[0].atom = a;

    return temp;
}

packet wrap_list(packet p) {
    packet wrap;

    wrap.atom = -1;
    wrap.list = malloc(sizeof(packet) * 128);
    wrap.list[0] = p;
    for (int i = 1; i < 128; i++) {
        wrap.list[i].atom = -1;
        wrap.list[i].list = NULL;
    }

    return wrap;
}

int is_defined(packet p) {
    return (p.atom > -1) || (p.list != NULL);
}

int compare_packets(packet p, packet q) {
    if (p.atom > -1 && q.atom > -1) {
        return q.atom - p.atom;
    } else if (p.atom > -1) {
        packet temp = wrap_atom(p.atom);
        return compare_packets(temp, q);
    } else if (q.atom > -1) {
        packet temp = wrap_atom(q.atom);
        return compare_packets(p, temp);
    } else {
        int i = 0;
        while (is_defined(p.list[i]) && is_defined(q.list[i])) {
            int comp = compare_packets(p.list[i], q.list[i]);
            if (comp != 0) {
                return comp;
            }
            i++;
        }
        if (!(is_defined(p.list[i]) || is_defined(q.list[i]))) {
            return 0;
        } else if (!is_defined(p.list[i])) {
            return 1;
        } else {
            return -1;
        }
    }
}

void insert_packet(packet *ps, packet p, int num_packets) {
    int i = 0;
    while (i < num_packets) {
        if (compare_packets(p, ps[i]) > 0) {
            int j = num_packets - 1;
            while (j >= i) {
                ps[j + 1] = ps[j];
                j--;
            }
            break;
        }
        i++;
    }
    ps[i] = p;
}

packet* sort_packets(char* raw) {
    packet* ps = malloc(sizeof(packet) * 512);
    for (int i = 0; i < 512; i++) {
        ps[i].atom = -1;
        ps[i].list = NULL;
    }

    FILE *fp = fopen(raw, "r");
    if (fp == NULL) {
        return ps;
    }

    ps[0] = wrap_list(wrap_atom(2));
    ps[1] = wrap_list(wrap_atom(6));
    int num_packets = 2;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    while ((read = getline(&line, &length, fp)) != -1) {
        if (!strcmp(line, "\n")) {
            continue;
        }

        packet p;
        parse_packet(&p, line);
        insert_packet(ps, p, num_packets++);
    }

    return ps;
}

int search_packet(packet* ps, packet p) {
    char *p_str = to_string(p);
    int i = 0;
    while (is_defined(ps[i])) {
        if (!strcmp(to_string(ps[i]), p_str)) {
            return i;
        }
        i++;
    }
    return -1;
}

int get_decoder_key(packet* ps) {
    packet div[2];
    parse_packet(&div[0], "[[2]]");
    parse_packet(&div[1], "[[6]]");

    return (search_packet(ps, div[0]) + 1) * (search_packet(ps, div[1]) + 1);
}

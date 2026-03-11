#pragma once

#define ARRAY_LEN(a) (sizeof (a) / sizeof (a)[0])

void print_array(int A[], int n);

int get_array_from_user(int A[], int max);
int *get_array_from_user_unknown(int *outlen);

#pragma once
#define ALPHABET_SIZE 26
#define TOP_N 3

void read_distribution(const char* filename, double distribution[ALPHABET_SIZE]);

void compute_histogram(const char* text, double histogram[ALPHABET_SIZE]);

double chi_squared_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE]);

double euclidean_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE]);

double cosine_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE]);

void break_caesar_cipher(const char* text, int top_shifts[TOP_N], double top_distances[TOP_N],
    double (*distance_function)(const double[], const double[]));

#define _CRT_SECURE_NO_WARNINGS
#include "CaesarCipherCracker.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void read_distribution(const char* filename, double distribution[ALPHABET_SIZE])
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: could not open file %s\n", filename);
		return;
	}
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		fscanf(file, "%lf", &distribution[i]);
	}
	fclose(file);
}

void compute_histogram(const char* text, double histogram[ALPHABET_SIZE])
{
	int total_letters = 0;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		histogram[i] = 0;
	}

	for (int i = 0; text[i] != '\0'; i++)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
		{
			histogram[text[i] - 'a']++;
			total_letters++;
		}
		else if (text[i] >= 'A' && text[i] <= 'Z')
		{
			histogram[text[i] - 'A']++;
			total_letters++;
		}
	}
	if (total_letters > 0)
	{
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			histogram[i] /= total_letters;
		}
	}
}

double chi_squared_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE])
{
	double distance = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (hist2[i] > 0)
		{
			double diff = hist1[i] - hist2[i];
			distance += (diff * diff) / hist2[i];
		}
	}
	return distance;
}


double euclidean_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE])
{
	double distance = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		double diff = hist1[i] - hist2[i];
		distance += (diff * diff);
	}
	return sqrt(distance);
}

double cosine_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE])
{
	double dot_product = 0;
	double norm1 = 0;
	double norm2 = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		dot_product += hist1[i] * hist2[i];
		norm1 += hist1[i] * hist1[i];
		norm2 += hist2[i] * hist2[i];
	}
	return 1 - dot_product / (sqrt(norm1) * sqrt(norm2));
}

void break_caesar_cipher(const char* text, int top_shifts[TOP_N], double top_distances[TOP_N], double(*distance_function)(const double[], const double[]))
{
	double distribution[ALPHABET_SIZE];
	read_distribution("distribution.txt", distribution);

	double min_distances[TOP_N];
	int best_shifts[TOP_N];

	for (int i = 0; i < TOP_N; i++) {
		min_distances[i] = 1e9;
		best_shifts[i] = -1;
	}

	int text_len = strlen(text);
	char* shifted_text = (char*)malloc((text_len + 1) * sizeof(char));

	if (shifted_text == NULL) {
		fprintf(stderr, "Error: Memory allocation failed.\n");
		return;
	}

	for (int shift = 0; shift < ALPHABET_SIZE; shift++)
	{
		for (int i = 0; i < text_len; i++)
		{
			if (text[i] >= 'a' && text[i] <= 'z')
				shifted_text[i] = 'a' + (text[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
			else if (text[i] >= 'A' && text[i] <= 'Z')
				shifted_text[i] = 'A' + (text[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
			else
				shifted_text[i] = text[i];
		}
		shifted_text[text_len] = '\0';

		double histogram[ALPHABET_SIZE];
		compute_histogram(shifted_text, histogram);

		double distance = distance_function(histogram, distribution);

		for (int j = 0; j < TOP_N; j++)
		{
			if (distance < min_distances[j])
			{
				for (int k = TOP_N - 1; k > j; k--)
				{
					min_distances[k] = min_distances[k - 1];
					best_shifts[k] = best_shifts[k - 1];
				}
				min_distances[j] = distance;
				best_shifts[j] = shift;
				break;
			}
		}
	}

	free(shifted_text);  

	for (int i = 0; i < TOP_N; i++)
	{
		top_shifts[i] = best_shifts[i];
		top_distances[i] = min_distances[i];
	}
}



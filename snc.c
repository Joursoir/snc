#include <stdio.h>

#include "snc.h"

int getRomanValue(char symbol)
{
	switch(symbol) {
		case 'I': return SNC_ROMAN_I; // have triple notation
		case 'V': return SNC_ROMAN_V;
		case 'X': return SNC_ROMAN_X; // have triple notation
		case 'L': return SNC_ROMAN_L;
		case 'C': return SNC_ROMAN_C; // have triple notation
		case 'D': return SNC_ROMAN_D;
		case 'M': return SNC_ROMAN_M; // have triple notation
	}
	return 0;
}

int romanToArabic(char *str)
{
	int answer = 0;
	int last_value = 0;
	int amount_char = 0;
	while(*str)
	{
		int cur_value = getRomanValue(*str);
		if(cur_value == 0)
			return -1;
		else if(last_value == cur_value || last_value == 0) {
			answer += cur_value;
			amount_char++;
		}
		else if(last_value > cur_value) {
			answer += cur_value;
			amount_char = 1;
		}
		else if(last_value < cur_value) {
			answer += cur_value - 2 * last_value;
			if(amount_char > 1) return -1;
			amount_char = 1;
		}
		last_value = cur_value;

		if(amount_char > 3)
			return -1;
		else if(cur_value == SNC_ROMAN_V ||
				cur_value == SNC_ROMAN_L || cur_value == SNC_ROMAN_D) {
			if(amount_char > 1) return -1;
		}

		str++;
	}

	return answer;
}

int main(int argc, char *argv[])
{
	if(argc < 2)
		return printf("Simple numbers converter\n"
					"\n"
					"Synopsis: snc [number]\n");

	int answer = romanToArabic(argv[1]);
	if(answer == -1) printf("ERROR! %s is not roman number\n", argv[1]);
	else printf("answer: %d\n", answer);

	return 0;
}
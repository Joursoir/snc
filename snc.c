/***
	This file is part of Simple numbers converter.

	Copyright (C) 2021 Aleksandr D. Goncharov (Joursoir) <chat@joursoir.net>

	Simple numbers converter is free software; you can redistribute it
	and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	Simple numbers converter is distributed in the hope that it will be
	useful, but WITHOUT ANY WARRANTY; without even the implied warranty
	of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, see <http://www.gnu.org/licenses/>.
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
			if(last_value * 10 < cur_value)
				return -1;
			else if(last_value == SNC_ROMAN_V ||
					last_value == SNC_ROMAN_L || last_value == SNC_ROMAN_D)
				return -1;
			
			answer += cur_value - 2 * last_value;
			if(amount_char > 1)
				return -1;
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

char *arabicToRoman(char *str)
{
	int number = atoi(str);
	if(!number || number > SNC_ROMAN_MAX_NUMBER)
		return NULL;

	const char *units[] = {"","I","II","III","IV",
							"V","VI","VII","VIII","IV"};
	const char *tens[] = {"","X","XX","XXX","XL",
							"L","LX","LXX","LXXX","XC"};
	const char *hundreds[] = {"","C","CC","CCC","CD",
							"D","DC","DCC","DCCC","CM"};
	const char *thousands[] = {"","M","MM","MMM"};
	char *answer = malloc(sizeof(char) * (SNC_ROMAN_MAXLEN + 1));

	strcpy(answer, thousands[number / 1000]);
	strcat(answer, hundreds[number / 100 % 10]);
	strcat(answer, tens[number / 10 % 10]);
	strcat(answer, units[number % 10]);

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
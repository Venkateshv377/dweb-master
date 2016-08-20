#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dwebsvr.h"

void gpio_response(struct hitArgs *args, char *path, char *request_body)
{
	char response[200] = {};
	int value, j, tmp;
	char buff[50];
	static char *status[] = {"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};

	printf("request: %s\n", request_body);
	tmp = (int)(*request_body);

	if (tmp != 99)					/* If button is clicked then only execute atoi(i.e passing the id of the button) */
		value = atoi(request_body);
	else
		value = '$';

	for (j = 0; j < 20; j++)
	{
		if (j == value)
		{
			if (status[value] == "0")
			{
				status[value] = "1";
				if (value == 2)
				{
					sprintf(buff, "echo %s > /sys/kernel/gpio48/foo", status[value]);
					system(buff);
				}
			}
			else
			{
				status[value] = "0";
				if (value == 2)
				{
					sprintf(buff, "echo %s > /sys/kernel/gpio48/foo", status[value]);
					system(buff);
				}
			}
		}
		strcat(response, status[j]);
		strcat(response, ":");
	}
	printf("response: %s\n", response);
	return ok_200(args, "\nContent-Type: text/plain", response, path);
}

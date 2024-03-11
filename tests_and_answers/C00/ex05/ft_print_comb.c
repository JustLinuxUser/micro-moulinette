/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andokhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:55:45 by andokhni          #+#    #+#             */
/*   Updated: 2023/08/15 16:05:29 by andokhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void print_arr_3(int num[3]) {
    char temp;

    temp = '0' + num[0];
    write(1, &temp, 1);
    temp = '0' + num[1];
    write(1, &temp, 1);
    temp = '0' + num[2];
    write(1, &temp, 1);
}

void ft_print_comb(void) {
    int num[3];

    num[0] = 0;
    while (num[0] <= 7) {
        num[1] = num[0] + 1;
        while (num[1] <= 8) {
            num[2] = num[1] + 1;
            while (num[2] <= 9) {
                print_arr_3(num);
                if (num[0] != 7 || num[1] != 8 || num[2] != 9)
                    write(1, ", ", 2);
                num[2]++;
            }
            num[1]++;
        }
        num[0]++;
    }
}

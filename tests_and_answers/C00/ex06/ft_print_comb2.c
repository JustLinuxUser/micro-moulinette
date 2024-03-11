/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andokhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:55:45 by andokhni          #+#    #+#             */
/*   Updated: 2023/08/15 16:17:43 by andokhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putnbr(int n) {
    char c;

    if (n < 9) {
        write(1, "0", 1);
        c = '0' + n % 10;
        write(1, &c, 1);
    } else {
        c = '0' + n / 10;
        write(1, &c, 1);
        c = '0' + n % 10;
        write(1, &c, 1);
    }
}

void print_arr_2(int num[2]) {
    ft_putnbr(num[0]);
    write(1, " ", 1);
    ft_putnbr(num[1]);
}

void ft_print_comb2(void) {
    int num[2];

    num[0] = 0;
    while (num[0] <= 98) {
        num[1] = num[0] + 1;
        while (num[1] <= 99) {
            print_arr_2(num);
            if (num[0] != 98 || num[1] != 99)
                write(1, ", ", 2);
            num[1]++;
        }
        num[0]++;
    }
}

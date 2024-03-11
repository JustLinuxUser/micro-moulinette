/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andokhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:02:08 by andokhni          #+#    #+#             */
/*   Updated: 2023/08/15 17:02:10 by andokhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putnbr(int n) {
    long nl;
    char c;

    nl = n;
    if (nl < 0) {
        nl *= -1;
        write(1, "-", 1);
    }
    if (nl > 9)
        ft_putnbr(nl / 10);
    c = '0' + nl % 10;
    write(1, &c, 1);
}

void print_n(int n, int* arr) {
    int i;

    i = 0;
    while (i < n) {
        ft_putnbr(arr[i]);
        i++;
    }
}

void increment(int n, int* num) {
    int lowest;
    int i;

    lowest = 999;
    i = n - 1;
    while (i > 0) {
        if (num[i] > 10 - n + i) {
            lowest = i;
            num[i - 1]++;
            num[i] = num[i - 1] + 1;
        }
        i--;
    }
    i = lowest + 1;
    while (i < n) {
        num[i] = num[i - 1] + 1;
        i++;
    }
}

void ft_print_combn(int n) {
    int num[10];
    int iter;
    int i;

    if (n >= 10 || n <= 0) {
        return;
    }

    i = 0;
    while (i < n) {
        num[i] = i;
        i++;
    }
    iter = 0;
    while (1) {
        increment(n, num);
        if (num[0] > 10 - n)
            return;
        if (iter != 0)
            write(1, ", ", 2);
        print_n(n, num);
        num[n - 1]++;
        iter++;
    }
}

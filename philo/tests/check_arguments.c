#include "philo.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(init, check_arguments)
{
	cr_redirect_stdout();
	// fail
	cr_assert_eq(check_arguments(0, NULL), FALSE);
	cr_assert_eq(check_arguments(1, NULL), FALSE);
	cr_assert_eq(check_arguments(2, NULL), FALSE);
	cr_assert_eq(check_arguments(3, NULL), FALSE);
	cr_assert_eq(check_arguments(4, NULL), FALSE);
	cr_assert_eq(check_arguments(5, NULL), FALSE);
	cr_assert_eq(check_arguments(6, NULL), FALSE);
	cr_assert_eq(check_arguments(7, NULL), FALSE);
	cr_assert_eq(check_arguments(8, NULL), FALSE);
	cr_assert_eq(check_arguments(9, NULL), FALSE);
	char *argv_with_zero1[] = {"./philo", "0", "1", "1", "1", 0};
	cr_assert_eq(check_arguments(5, argv_with_zero1), FALSE);
	char *argv_with_zero2[] = {"./philo", "1", "0", "1", "1", 0};
	cr_assert_eq(check_arguments(5, argv_with_zero2), FALSE);
	char *argv_with_zero3[] = {"./philo", "1", "1", "0", "1", 0};
	cr_assert_eq(check_arguments(5, argv_with_zero3), FALSE);
	char *argv_with_zero4[] = {"./philo", "1", "1", "1", "0", 0};
	cr_assert_eq(check_arguments(5, argv_with_zero4), FALSE);
	// success
	char *argv_4_args[] = {"./philo", "1", "1", "1", "1", 0};
	cr_assert_eq(check_arguments(5, argv_4_args), TRUE);
	char *argv_5_args[] = {"./philo", "1", "1", "1", "1", "1", 0};
	cr_assert_eq(check_arguments(6, argv_5_args), TRUE);
}

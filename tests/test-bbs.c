/*
 *  Copyright (C) 2014 ChangZhuo Chen
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include <check.h>

#include <bbs.h>

START_TEST(test_new_delete)
{
    struct BBSContext *ctx = bbs_new();
    ck_assert_ptr_ne(ctx, 0);

    bbs_delete(&ctx);
    ck_assert_ptr_eq(ctx, 0);
}
END_TEST

int main (int argc, char *argv[]) {
    Suite *suite = suite_create("test");

    TCase *tcase = tcase_create("testcase");
    tcase_add_test(tcase, test_new_delete);

    suite_add_tcase(suite, tcase);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);

    int number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return !!number_failed;
}

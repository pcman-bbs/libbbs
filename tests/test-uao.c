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

START_TEST(test_big5_to_utf8_no_output_ascii)
{
    struct BBSContext *ctx = bbs_new(0, 0);
    ck_assert_int_eq(bbs_big5_to_utf8(ctx, "test", 0, 0), 4);
    bbs_delete(&ctx);
}
END_TEST

START_TEST(test_big5_to_utf8_ascii)
{
    struct BBSContext *ctx = bbs_new(0, 0);
    char utf8[5];
    ck_assert_int_eq(bbs_big5_to_utf8(ctx, "test", utf8, sizeof(utf8)), 4);
    ck_assert_str_eq(utf8, "test");
    bbs_delete(&ctx);
}
END_TEST

START_TEST(test_utf8_to_big5_no_output_ascii)
{
    struct BBSContext *ctx = bbs_new(0, 0);
    ck_assert_int_eq(bbs_utf8_to_big5(ctx, "test", 0, 0), 4);
    bbs_delete(&ctx);
}
END_TEST

START_TEST(test_utf8_to_big5_ascii)
{
    struct BBSContext *ctx = bbs_new(0, 0);
    char big5[5];
    ck_assert_int_eq(bbs_utf8_to_big5(ctx, "test", big5, sizeof(big5)), 4);
    ck_assert_str_eq(big5, "test");
    bbs_delete(&ctx);
}
END_TEST

int main (int argc, char *argv[]) {
    Suite *suite = suite_create("test-uao");

    TCase *tcase_bbs_big5_to_utf8 = tcase_create("bbs_big5_to_utf8");
    tcase_add_test(tcase_bbs_big5_to_utf8, test_big5_to_utf8_no_output_ascii);
    tcase_add_test(tcase_bbs_big5_to_utf8, test_big5_to_utf8_ascii);

    TCase *tcase_bbs_utf8_to_big5 = tcase_create("bbs_utf8_to_big5");
    tcase_add_test(tcase_bbs_utf8_to_big5, test_utf8_to_big5_no_output_ascii);
    tcase_add_test(tcase_bbs_utf8_to_big5, test_utf8_to_big5_ascii);

    suite_add_tcase(suite, tcase_bbs_big5_to_utf8);
    suite_add_tcase(suite, tcase_bbs_utf8_to_big5);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);

    int number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return !!number_failed;
}

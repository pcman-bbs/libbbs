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

const char BIG5_STRING[] = "convert test string: \x81\x40\xa0\xa6\xa0\xa7\x98\x41!";
const char UTF8_STRING[] = "convert test string: \xe4\xb8\x97\xee\xb9\x9f\xc3\x80\xe2\x9d\xb6!";

const char BIG5_DUPLICATED[] = "\xc9\x4a\xa4\x61 \xdd\xfc\xdc\xd1";
const char UTF8_DUPLICATED[] = "\xef\xa8\x8c\xe5\x85\x80 \xef\xa8\x8d\xe5\x97\x80";

START_TEST(test_big5_to_utf8)
{
    char buf[100];
    ck_assert_int_eq(bbs_big5_to_utf8(BIG5_STRING, buf, sizeof(buf)), strlen(UTF8_STRING));
    ck_assert_str_eq(buf, UTF8_STRING);
}
END_TEST

START_TEST(test_big5_to_utf8_duplicated)
{
    char buf[100];
    ck_assert_int_eq(bbs_big5_to_utf8(BIG5_DUPLICATED, buf, sizeof(buf)), strlen(UTF8_DUPLICATED));
    ck_assert_str_eq(buf, UTF8_DUPLICATED);
}
END_TEST

START_TEST(test_big5_to_utf8_output_not_enough)
{
    char buf[5];
    ck_assert_int_eq(bbs_big5_to_utf8(BIG5_STRING, buf, sizeof(buf)), strlen(UTF8_STRING));
}
END_TEST

START_TEST(test_big5_to_utf8_no_output)
{
    ck_assert_int_eq(bbs_big5_to_utf8(BIG5_STRING, 0, 0), strlen(UTF8_STRING));
}
END_TEST

START_TEST(test_big5_to_utf8_broken_big5)
{
    char utf8[5];
    ck_assert_int_eq(bbs_big5_to_utf8("\x81", utf8, sizeof(utf8)), 1);
    ck_assert_str_eq(utf8, "?");
}
END_TEST

START_TEST(test_utf8_to_big5_no_output_ascii)
{
    ck_assert_int_eq(bbs_utf8_to_big5("test", 0, 0), 4);
}
END_TEST

START_TEST(test_utf8_to_big5_ascii)
{
    char big5[5];
    ck_assert_int_eq(bbs_utf8_to_big5("test", big5, sizeof(big5)), 4);
    ck_assert_str_eq(big5, "test");
}
END_TEST

int main (int argc, char *argv[]) {
    Suite *suite = suite_create("test-uao");

    TCase *tcase_bbs_big5_to_utf8 = tcase_create("bbs_big5_to_utf8");
    tcase_add_test(tcase_bbs_big5_to_utf8, test_big5_to_utf8);
    tcase_add_test(tcase_bbs_big5_to_utf8, test_big5_to_utf8_duplicated);
    tcase_add_test(tcase_bbs_big5_to_utf8, test_big5_to_utf8_output_not_enough);
    tcase_add_test(tcase_bbs_big5_to_utf8, test_big5_to_utf8_no_output);
    tcase_add_test(tcase_bbs_big5_to_utf8, test_big5_to_utf8_broken_big5);

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

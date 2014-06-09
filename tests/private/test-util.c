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

#include <util.h>

const char UTF8_1_BYTE_FIRST[] = "\x00";
const char UTF8_1_BYTE_LAST[]  = "\x7f";
const char UTF8_2_BYTE_FIRST[] = "\xc2\x80";
const char UTF8_2_BYTE_LAST[]  = "\xdf\xbf";
const char UTF8_3_BYTE_FIRST[] = "\xe0\xa0\x80";
const char UTF8_3_BYTE_LAST[]  = "\xef\xbf\xbf";
const char UTF8_4_BYTE_FIRST[] = "\xf0\x90\x80\x80";
const char UTF8_4_BYTE_LAST[]  = "\xf4\x8f\xbf\xbf";

START_TEST(test_get_utf8_length_by_first_byte)
{
    ck_assert_int_eq(get_utf8_length_by_first_byte(UTF8_1_BYTE_FIRST[0]), 1);
    ck_assert_int_eq(get_utf8_length_by_first_byte(UTF8_1_BYTE_LAST[0]), 1);

    ck_assert_int_eq(get_utf8_length_by_first_byte(UTF8_2_BYTE_FIRST[0]), 2);
    ck_assert_int_eq(get_utf8_length_by_first_byte(UTF8_2_BYTE_LAST[0]), 2);

    ck_assert_int_eq(get_utf8_length_by_first_byte(UTF8_3_BYTE_FIRST[0]), 3);
    ck_assert_int_eq(get_utf8_length_by_first_byte(UTF8_3_BYTE_LAST[0]), 3);

    ck_assert_int_eq(get_utf8_length_by_first_byte(UTF8_4_BYTE_FIRST[0]), 4);
    ck_assert_int_eq(get_utf8_length_by_first_byte(UTF8_4_BYTE_LAST[0]), 4);
}
END_TEST

int main (int argc, char *argv[]) {
    Suite *suite = suite_create("test-util");

    TCase *tcase = tcase_create("get_utf8_length_by_first_byte");
    tcase_add_test(tcase, test_get_utf8_length_by_first_byte);

    suite_add_tcase(suite, tcase);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);

    int number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return !!number_failed;
}

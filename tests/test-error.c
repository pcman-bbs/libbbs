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

START_TEST(test_null_ctx)
{
    ck_assert_int_eq(bbs_big5_to_utf8(0, 0, 0), BBS_ERROR);
    ck_assert_int_eq(bbs_utf8_to_big5(0, 0, 0), BBS_ERROR);
}
END_TEST

int main (int argc, char *argv[]) {
    Suite *suite = suite_create("test-error");

    TCase *tcase = tcase_create("null");
    tcase_add_test(tcase, test_null_ctx);

    suite_add_tcase(suite, tcase);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);

    int number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return !!number_failed;
}

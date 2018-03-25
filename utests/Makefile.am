ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/utests/Makefile.test.common

SUBDIRS = fixtures

TESTS = ut_button.xtest

noinst_PROGRAMS = $(TESTS)

check_PROGRAMS = $(TESTS)

ut_button_xtest_SOURCES = ut_button.h
ut_button_xtest_SOURCES += main.cpp
ut_button_xtest_CFLAGS = $(TESTCFLAGS)
ut_button_xtest_CXXFLAGS = $(TESTCXXFLAGS)
ut_button_xtest_LDFLAGS = $(TESTLDFLAGS)
ut_button_xtest_LDADD  = $(top_builddir)/src/libbutton.la
ut_button_xtest_LDADD += $(top_builddir)/utests/fixtures/libfixtures.la

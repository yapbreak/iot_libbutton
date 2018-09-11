ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

bin_PROGRAMS = buttontest

buttontest_CFLAGS = -DTESTFIRMWARE $(AM_CFLAGS)
buttontest_CXXFLAGS = -DTESTFIRMWARE $(AM_CXXFLAGS)
buttontest_SOURCES  = ../src/test.cpp
buttontest_SOURCES += simulate.cpp
buttontest_LDADD = $(top_builddir)/src/libbutton.la $(ARDSIM_LIBS)

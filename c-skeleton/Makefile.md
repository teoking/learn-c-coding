# This makefile is designed to build a static library.

## 注释版，实际使用时可删除注释 ##

# These are the usual CFLAGS that you set in all of your projects, 
# but with a few others that may be needed to build libraries. 
# You may need to adjust these for different platforms. Notice the OPTFLAGS variable 
# at the end which lets people augment the build options as needed.
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
# Options used when linking a library, and allows someone else to 
# augment the linking options using the OPTLIBS variable.
LIBS=-ldl $(OPTLIBS)
# Setting an optional variable called PREFIX that will only have this value 
# if the person running the Makefile didn't already give a PREFIX setting. 
# That's what the ?= does.
PREFIX?=/usr/local

# This fancy line of awesome dynamically creates the SOURCES variable by 
# doing a wildcard search for all *.c files in the src/ directory. 
# You have to give both src/**/*.c and src/*.c so that GNU make will include the files in src and also the ones below it.
SOURCES=$(wildcard src/**/*.c src/*.c)
# Once you have the list of source files, you can then use the patsubst 
# to take the SOURCES list of *.c files and make a new list of all the 
# object files. You do this by telling patsubst to change all %.c extensions to %.o 
# and then those are assigned to OBJECTS.
# patsubst是一个make函数
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

# Using the wildcard again to find all the test source files for the unit tests. 
# These are separate from the library's source files.
TEST_SRC=$(wildcard tests/*_tests.c)
# Then using the same patsubst trick to dynamically get all the TEST targets. 
# In this case I'm stripping away the .c extension so that a full program will be made with the same name. 
# Previously I had replaced the .c with {.o} so an object file is created.
TESTS=$(patsubst %.c,%,$(TEST_SRC))

# Finally, we say the ultimate target is build/libYOUR_LIBRARY.a, 
# which you will change to be whatever library you are actually trying to build.
TARGET=build/libYOUR_LIBRARY.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# Remember that the first target is what make will run by default when no target is given. 
# In this case it's called all: and it gives $(TARGET) tests as the targets to build. 
# Look up at the TARGET variable and you see that's the library, so all: will first build the library. 
# The tests target is then further down in the Makefile and builds the unit tests.
# The Target Build
all: $(TARGET) $(SO_TARGET) tests

# Another target for making "developer builds" that introduces a technique for changing options 
# for just one target. If I do a "dev build" I want the CFLAGS to include options like -Wextra 
# that are useful for finding bugs. If you place them on the target line as options like this, 
# then give another line that says the original target (in this case all) then it will change 
# the options you set. I use this for setting different flags on different platforms that need it.
dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

# Line 74
# Builds the TARGET library, whatever that is, and also uses the same trick from line 15 of 
# giving a target with just options changes to alter them for this run. In this case I'm adding
# -fPIC just for the library build using the += syntax to add it on.

# Line 75
# Now the real target where I say first make the build directory, then compile all the OBJECTS.

# Line 76
# Runs the ar command which actually makes the TARGET. The syntax $@ $(OBJECTS) is a way of saying, 
# "put the target for this Makefile source here and all the OBJECTS after that". 
# In this case the $@ maps back to the $(TARGET) on line 19, which maps to build/libYOUR_LIBRARY.a. 
# It seems like a lot to keep track of this indirection, and it can be, but once you get it working 
# this means you just change TARGET at the top and build a whole new library.

# Line 77
# Finally, to make the library you run ranlib on the TARGET and it's built.
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
       ar rcs $@ $(OBJECTS)
       ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
       $(CC) -shared -o $@ $(OBJECTS)


# This just makes the build/ or bin/ directories if they don't exist. 
# This is then referenced from line 19 when it gives the build target to make sure the build/ directory is made.
build:
       @mkdir -p build
       @mkdir -p bin

# If you have a target that's not "real", but there is a directory or file with that name, 
# then you need to tag the target with .PHONY: so make will ignore the file and always run.
# The Unit Tests
.PHONY: tests

# I use the same trick for modifying the CFLAGS variable to add the TARGET to the build 
# so that each of the test programs will be linked with the TARGET library. In this case it will 
# add build/libYOUR_LIBRARY.a to the linking.
tests: CFLAGS += $(TARGET)
# Then I have the actual tests: target which depends on all the programs listed in the TESTS variable 
# we created in the header. This one line actually says, "Make, use what you know about building 
# programs and the current CFLAGS settings to build each program in TESTS."
tests: $(TESTS)
	   #Finally, when all of the TESTS are built, there's a simple shell script I'll create later 
	   # that knows how to run them all and report their output. This line actually runs it so you
	   # can see the test results.
       sh ./tests/runtests.sh

# In order to be able to dynamically rerun the tests with Valgrind there's a valgrind: 
# target that sets the right variable and runs itself again. This puts the valgrind logs into 
# /tmp/valgrind-*.log so you can go look and see what might be going on. The tests/runtests.sh 
# then knows to run the test programs under Valgrind when it sees this VALGRIND variable.
valgrind:
       VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The clean: target starts things off whenever we need to clean up the project.
# The Cleaner
clean:
	   # This cleans out most of the junk that various compilers and tools leave behind.
	   # It also gets rid of the build/ directory and uses a trick at the end to cleanly erase 
	   # the weird *.dSYM directories Apple's XCode leaves behind for debugging purposes.
       rm -rf build $(OBJECTS) $(TESTS)
       rm -f tests/tests.log
       find . -name "*.gc*" -exec rm {} \;
       rm -rf `find . -name "*.dSYM" -print`

# This makes install: depend on the all: target so that when you run make install it will 
# be sure to build everything.
# The Install
install: all
	   # I then use the program install to create the target lib directory if it doesn't exist. 
	   # In this case I'm trying to make the install as flexible as possible by using two variables 
	   # that are conventions for installers. DESTDIR is handed to make by installers that do 
	   # their builds in secure or odd locations to build packages. PREFIX is used when people want 
	   # the project to be installed in someplace other than /usr/local.
       install -d $(DESTDIR)/$(PREFIX)/lib/
       # After that I'm just using install to actually install the library where it needs to go.
       install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# Sets a variable which is a big regex looking for bad functions like strcpy.
# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
# The check: target so you can run a check whenever you need.
check:
	   # Just a way to print a message, but doing @echo tells make to not print the command, 
	   # just its output.
       @echo Files with potentially dangerous functions.
       # Run the egrep command on the source files looking for any bad patterns. 
       # The || true at the end is a way to prevent make from thinking that egrep not finding things is a failure.
       @egrep $(BADFUNCS) $(SOURCES) || true






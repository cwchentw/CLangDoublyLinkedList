.PHONY: all test testStatic dynamic static clean
all: test

test: dynamic
	for x in $(TEST_OBJS); do \
		$(CC) $(CFLAGS) -c "$${x%.*}.c" \
			-I..$(SEP)$(INCLUDE_DIR) $(INCLUDE) \
			-L..$(SEP)$(DIST_DIR) -llist $(LIBS); \
		$(CC) $(CFLAGS) -o "$${x%.*}" $$x \
			-I..$(SEP)$(INCLUDE_DIR) $(INCLUDE) \
			-L..$(SEP)$(DIST_DIR) -llist $(LIBS); \
		LD_LIBRARY_PATH=..$(SEP)$(DIST_DIR) .$(SEP)"$${x%.*}"; \
		if [ $$? -ne 0 ]; then echo "Failed program state"; exit 1; fi \
	done

testStatic: static
	for x in $(TEST_OBJS); do \
		$(CC) $(CFLAGS) -c "$${x%.*}.c" \
			-I..$(SEP)$(INCLUDE_DIR) $(INCLUDE) \
			-L..$(SEP)$(DIST_DIR) -llist $(LIBS); \
		$(CC) $(CFLAGS) -o "$${x%.*}" $$x \
			-I..$(SEP)$(INCLUDE_DIR) $(INCLUDE) \
			-L..$(SEP)$(DIST_DIR) -llist $(LIBS); \
		.$(SEP)"$${x%.*}"; \
		if [ $$? -ne 0 ]; then echo "Failed program state"; exit 1; fi \
	done

dynamic: ..$(SEP)$(DIST_DIR)$(SEP)$(DYNAMIC_LIB)
	$(MAKE) -C ..$(SEP)$(SOURCE_DIR) dynamic

static: ..$(SEP)$(DIST_DIR)$(SEP)$(STATIC_LIB)
	$(MAKE) -C ..$(SEP)$(SOURCE_DIR) static

clean:
	$(RM) $(TEST_OBJS) $(TEST_OBJS:.o=)

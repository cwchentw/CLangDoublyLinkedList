.PHONY: all dynamic static clean

all: dynamic

dynamic:
	for x in `ls *.c`; do $(CC) $(CFLAGS) -fPIC -c $$x \
		-I ..$(SEP)$(INCLUDE_DIR) $(INCLUDE) $(LIBS); done
	$(CC) $(CFLAGS) -shared -o ..$(SEP)$(DIST_DIR)$(SEP)$(DYNAMIC_LIB) $(OBJS) \
		-I ..$(SEP)$(INCLUDE_DIR) $(INCLUDE) $(LIBS)

static: $(OBJS)
ifeq ($(detected_OS),Darwin)
	libtool -static -o ..$(SEP)$(DIST_DIR)$(SEP)$(STATIC_LIB) $(OBJS)
else
	$(AR) rcs -o ..$(SEP)$(DIST_DIR)$(SEP)$(STATIC_LIB) $(OBJS)
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I ..$(SEP)$(INCLUDE_DIR) $(INCLUDE) $(LIBS)

clean:
	$(RM) $(OBJS)

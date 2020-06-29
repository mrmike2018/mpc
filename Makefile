SUBDIRS = player1 player2 player3 player4 player5

subdirs:
		for dir in $(SUBDIRS); do \
			$(MAKE) -C $$dir; \
		done

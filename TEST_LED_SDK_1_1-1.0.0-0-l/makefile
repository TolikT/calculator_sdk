# ---------------------------------------------------------------------------
# Èìÿ ïðîåêòà

NAME	= test_led

# Íàñòðîéêè êîìïèëÿòîðà è ëèíêåðà

CC      = sdcc
CFLAGS  = -I./INCLUDE -c --stack-auto
LFLAGS  = --code-loc 0x2100 --xram-loc 0x6000 --stack-auto --stack-loc 0x80 

# Íàñòðîéêè ñèñòåìû àâòîèíêðåìåíòà âåðñèè ñáîðêè

PROJECT  = $(shell cat PROJECT)
VERSION  = $(shell cat VERSION)
BUILD    = $(shell cat BUILD)
TYPE     = $(shell cat TYPE)

PROJNAME = ${PROJECT}-${VERSION}-${BUILD}-${TYPE}
TARBALL  = ${PROJNAME}.tar

# Íàñòðîéêè M3P

M3P		 = /home/tolik/Документы/TEST_LED_SDK_1_1-1.0.0-0-l/gm3p/m3p
COMPORT	 = /dev/ttyUSB0
COMLOG	 = $(COMPORT)_log.txt
BAUD	 = 9600	

# Êàòàëîãè ñ èñõîäíûìè òåêñòàìè

SRC_DIR = SRC
# ---------------------------------------------------------------------------

all: test_led

clean:
	-rm -f  $(NAME).hex \
			$(NAME).bin \
			$(NAME).map \
			$(NAME).mem \
			$(NAME).lnk \
			pm3p_*.txt \
			com?_log.txt \
			$(TARBALL).gz \
			$(SRC_DIR)/*.asm \
			$(SRC_DIR)/*.rel \
			$(SRC_DIR)/*.rst \
			$(SRC_DIR)/*.sym \
			$(SRC_DIR)/*.lst 

load:
	$(M3P) lfile load.m3p


dist:
	tar cvf $(TARBALL) *
	gzip $(TARBALL)

term:
	$(M3P) echo $(COMLOG) $(BAUD)  openchannel $(COMPORT) +echo 6 term -echo bye


LIST_SRC = \
$(SRC_DIR)/max.c \
$(SRC_DIR)/console.c \
$(SRC_DIR)/str.c \
$(SRC_DIR)/expr2str.c \
$(SRC_DIR)/lab5.c \

LIST_OBJ = $(LIST_SRC:.c=.rel)

test_led : $(LIST_OBJ) makefile
	$(CC) $(LIST_OBJ) -o test_led.hex $(LFLAGS)
	$(M3P) hb166 test_led.hex test_led.bin bye


$(LIST_OBJ) : %.rel : %.c makefile
	$(CC) -c $(CFLAGS) $< -o $@  

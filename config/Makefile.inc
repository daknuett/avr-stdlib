m168_CFLAG = -std=gnu99 -I $(INCDIR) -mmcu=atmega168 -O -o  
m8_CFLAG = -std=gnu99 -I $(INCDIR) -mmcu=atmega8 -O -o  
 
 
m168_LIBDIR= $(std_LIBDIR)/m168
 
m8_LIBDIR= $(std_LIBDIR)/m8
 
m168_LIBS= $(m168_LIBDIR)/digital.o $(m168_LIBDIR)/analog.o $(m168_LIBDIR)/pins.o
 
m8_LIBS= $(m8_LIBDIR)/digital.o $(m8_LIBDIR)/analog.o $(m8_LIBDIR)/pins.o
 
m168_USART= $(m168_LIBDIR)/usart.o 
m8_USART= $(m8_LIBDIR)/usart.o
 
m8_USART_IO= $(m8_LIBDIR)/usart_io.o 
m168_USART_IO= $(m168_LIBDIR)/usart_io.o
extra_LIBDIR = $(std_LIBDIR)/extra
 m644_CFLAG = -std=gnu99 -I $(INCDIR) -mmcu=atmega644 -O -o  
 
m644_LIBDIR= $(std_LIBDIR)/m644
 
m644_LIBS= $(m644_LIBDIR)/digital.o $(m644_LIBDIR)/analog.o $(m644_LIBDIR)/pins.o
 m644_USART= $(m644_LIBDIR)/usart.o 

m644_USART_IO= $(m644_LIBDIR)/usart_io.o
extra_ONEWIRE = $(extra_LIBDIR)/one_wire.o
extra_LCD = $(extra_LIBDIR)/lcd.o
extra_LCD_IO = $(extra_LIBDIR)/lcd_io.o
extra_WAIT = $(extra_LIBDIR)/wait.o 
extra_BL3_MOTOR = $(extra_LIBDIR)/brushless3.o
LIBDIR = $(m168_LIBDIR)
CFLAG = $(m168_CFLAG)
LIBS = $(m168_LIBS)
USART = $(m168_USART)
USART_IO = $(m168_USART_IO)
ONEWIRE = $(extra_ONEWIRE)
LCD = $(extra_LCD)
LCD_IO = $(extra_LCD_IO)
DEVICE = m168
LIBS += $(USART) $(USART_IO)

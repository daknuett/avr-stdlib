m168_CFLAG = -I $(INCDIR) -mmcu=atmega168 -O -o  
m8_CFLAG = -I $(INCDIR) -mmcu=atmega8 -O -o  
 
 
m168_LIBDIR= $(std_LIBDIR)/m168
 
m8_LIBDIR= $(std_LIBDIR)/m8
 
m168_LIBS= $(m168_LIBDIR)/digital.o $(m168_LIBDIR)/analog.o $(m168_LIBDIR)/pins.o
 
m8_LIBS= $(m8_LIBDIR)/digital.o $(m8_LIBDIR)/analog.o $(m8_LIBDIR)/pins.o
 
m168_USART= $(m168_LIBDIR)/usart.o 
m8_USART= $(m8_LIBDIR)/usart.o
 
m8_USART_IO= $(m8_LIBDIR)/usart_io.o 
m168_USART_IO= $(m168_LIBDIR)/usart_io.o
extra_LIBDIR = $(std_LIBDIR)/extra
 extra_ONEWIRE = $(extra_LIBDIR)/one_wire.o
m168_LCD = $(m168_LIBDIR)/lcd.o
m8_LCD = $(m8_LIBDIR)/lcd.o
m168_LCD_IO = $(m168_LIBDIR)/lcd_io.o
m8_LCD_IO = $(m8_LIBDIR)/lcd_io.o
extra_WAIT = $(extra_LIBDIR)/wait.o 
extra_BL3_MOTOR = $(extra_LIBDIR)/brushless3.o
LIBDIR = $(m168_LIBDIR)
CFLAG = $(m168_CFLAG)
LIBS = $(m168_LIBS)
USART = $(m168_USART)
USART_IO = $(m168_USART_IO)
ONEWIRE = $(extra_ONEWIRE)
LCD = $(m168_LCD)
LCD_IO = $(m168_LCD_IO)
DEVICE = m168
LIBS += $(extra_BL3_MOTOR)

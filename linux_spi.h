#ifndef LINUX_SPI_H
#define LINUX_SPI_H


#include <stdint.h>





class Linux_SPI
{    

    public:


        enum SPI_Error{

            ERROR_DEV_NOT_OPEN,
            ERROR_CANT_OPEN_DEV,
            ERROR_CANT_SET_MODE,
            ERROR_CANT_GET_MODE,
            ERROR_CANT_SET_BITS,
            ERROR_CANT_GET_BITS,
            ERROR_CANT_SET_SPEED,
            ERROR_CANT_GET_SPEED,
            ERROR_BAD_PARAM,
            ERROR_CANT_READ,
            ERROR_CANT_WRITE,
            ERROR_CANT_SEND_TR
        };


         Linux_SPI();
        ~Linux_SPI();


         int  dev_open(const char *spi_dev);
         void dev_close(void);

         int  set_mode(uint8_t mode);
         int  get_mode(uint8_t *mode);

         int  set_bits_per_word(uint8_t bits_per_word);
         int  get_bits_per_word(uint8_t *bits_per_word);


         SPI_Error get_errno(void){ return _errno; }

         static const char* strerror(SPI_Error error);


    private:


         SPI_Error  _errno;
         int        _dev_fd;
};





#endif // LINUX_SPI_H

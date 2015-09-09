#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



#include "linux_spi.h"






Linux_SPI::Linux_SPI()
{
}



Linux_SPI::~Linux_SPI()
{
}



const char *Linux_SPI::strerror(Linux_SPI::SPI_Error error)
{

    switch (error)
    {

        case ERROR_DEV_NOT_OPEN:
            return "device is not open";

        case ERROR_CANT_OPEN_DEV:
            return "cant open device";

        case ERROR_CANT_SET_MODE:
            return "cant set mode";

        case ERROR_CANT_GET_MODE:
            return "cant get mode";

        case ERROR_CANT_SET_BITS:
            return "cant set bits";

        case ERROR_CANT_GET_BITS:
            return "cant get bits";

        case ERROR_CANT_SET_SPEED:
            return "cant set speed";

        case ERROR_CANT_GET_SPEED:
            return "cant get speed";

        case ERROR_BAD_PARAM:
            return "bad param";

        case ERROR_CANT_READ:
            return "cant read";

        case ERROR_CANT_WRITE:
            return "cant write";

        case ERROR_CANT_SEND_TR:
            return "cant send";

        default:
            return "unknown error";
    }
}

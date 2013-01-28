/**
 * \file   uartStdio.c
 *
 * \brief  This file contains functions which interface interactively
 *         with the user through the serial console to perform some 
 *         utility operations.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include "stdarg.h"
#include "utils/uartStdio.h"


/* A mapping from an integer between 0 and 15 to its ASCII character
 * equivalent. */
static const char * const g_pcHex = "0123456789abcdef";


/****************************************************************************
**                    EXTERNAL FUNCTION DECLARATIONS
****************************************************************************/
extern void UARTConsolePutc(unsigned char data);
extern unsigned char UARTConsoleGetc(void);
extern void UARTConsoleInit(void);

/*****************************************************************************
**                    FUNCTION DEFINITIONS
*****************************************************************************/

/**
 * \brief   This function initializes the specified UART instance for use for
 *          console operations.
 *
 * \param   None.
 *
 * \return  None.
 *
 */

void UARTStdioInit(void)
{
    UARTConsoleInit();
}

/**
 * \brief  This function writes data from a specified buffer onto the
 *         transmitter FIFO of UART.
 *
 * \param  pTxBuffer        Pointer to a buffer in the transmitter.  
 * \param  numBytesToWrite  Number of bytes to be transmitted to the 
 *                          transmitter FIFO. The user has the freedom to not 
 *                          specify any valid value for this if he wants to
 *                          print until the occurence of a NULL character.
 *                          In this case, he has to pass a negative value as
 *                          this parameter. 
 *  
 * \return  Number of bytes written to the transmitter FIFO.
 *
 * \note   1> Whenever a null character(\0) is encountered in the 
 *            data to be transmitted, the transmission is stopped. \n
 *         2> Whenever the transmitter data has a new line character(\n), 
 *            it is interpreted as a new line(\n) + carraige return(\r)
 *            characters. This is because the serial console interprets a 
 *            new line character as it is and does not introduce a carraige 
 *            return. \n
 *            
 *         Some example function calls of this function are: \n
 *
 *         UARTPuts(txArray, -2): This shall print the contents of txArray[]
 *         until the occurence of a NULL character. \n
 *
 *         UARTPuts("Hello World", 8): This shall print the first 8 characters
 *         of the string shown. \n
 *
 *         UARTPuts("Hello World", 20): This shall print the string shown until
 *         the occurence of the NULL character. Here, the NULL character is
 *         encountered earlier than the length of 20 bytes.\n
 * 
 */
unsigned int UARTPuts(char *pTxBuffer, int numBytesToWrite)
{
     unsigned int count = 0;
     unsigned int flag = 0;

     if(numBytesToWrite < 0)
     {
          flag = 1;
     }
     
     while('\0' != *pTxBuffer)
     {
          /* Checks if data is a newline character. */
          if('\n' == *pTxBuffer)
          {
               /* Ensuring applicability to serial console.*/
               UARTPutc('\r');
               UARTPutc('\n');
          }
          else
          {
               UARTPutc((unsigned char)*pTxBuffer);
          }
          pTxBuffer++;
          count++;

          if((0 == flag) && (count == numBytesToWrite))
          {
               break;
          }

     }
   /* Returns the number of bytes written onto the transmitter FIFO. */
   return count;
}

/**
 * \brief  This function reads data from the receiver FIFO to a buffer 
 *         in the receiver. 
 *
 * \param  pRxBuffer        Pointer to a buffer in the receiver.
 * \param  numBytesToRead   The number of bytes the receiver buffer can hold.
 *                          However, if the user wishes not to specify this
 *                          parameter, he has freedom to do so. In that case,
 *                          the user has to pass a negative value for this 
 *                          parameter.
 *
 * \return  Number of bytes read from the receiver FIFO.
 *
 * \note   The two exit points for this function are:
 *         1> To enter an ESC character or a carraige return character('Enter'
 *            key on the Keyboard).\n
 *         2> Specify a limit to the number of bytes to be read. \n
 * 
 *         Some example function calls of this function are:
 *
 *         UARTGets(rxBuffer, -2): This reads characters from
 *         the receiver FIFO of UART until the occurence of a carriage return
 *         ('Enter' key on the keyboard pressed) or an ESC character.
 *           
 *         UARTGets(rxBuffer, 12): This reads characters until
 *         12 characters have been read or until an occurence of a carriage 
 *         return or an ESC character, whichever occurs first.
 */

unsigned int UARTGets(char *pRxBuffer, int numBytesToRead)
{     
     unsigned int count = 0;
     unsigned int flag = 0;

     if(numBytesToRead < 0)
     {
          flag = 1;
     }
     do
     {
          *pRxBuffer = UARTGetc();
          
          /*
          ** 0xD - ASCII value of Carriage Return.
          ** 0x1B - ASCII value of ESC character.
          */ 
          if(0xD == *pRxBuffer || 0x1B == *pRxBuffer)
          {
               *pRxBuffer = '\0';
               break;
          }

          /* Echoing the typed character back to the serial console. */
          UARTPutc((unsigned char)*pRxBuffer);
          pRxBuffer++;     
          count++;

          if(0 == flag && (count == numBytesToRead))
          {
               break;
          }

     }while(1);
     
     return count;
}


/**
 *  \brief   This function prints the specified numbers(positive or negative) 
 *           on the serial console.
 *
 *  \param   value     The number to be printed on the serial console.
 *      
 *  \return  None.
 *
 *  \note    The numbers that this function can print should lie in the 
 *           following range:
 *           [-2^(31)] to [2^(31) - 1] i.e.
 *           0x80000000 to 0x7FFFFFFF
 *
 */

void UARTPutNum(int value)
{
     unsigned char num[10] = {0};
     unsigned int quotient = 0;
     unsigned int dividend = 0;
     int count = 0;

     if(value < 0)
     {
          UARTPutc('-');      
          /* 
          ** Making the negative number as positive. 
          ** This is done to simplify further processing and printing.
          */
          value = -value; 
     }

     dividend = value; 
     do
     {
          quotient = dividend/10;
          num[count] = (unsigned char)(dividend % 10);
          if(0 == quotient)
          {
               break;
          }            
          count++;
          dividend = quotient;

     }while(count < 10);      

     if(10 == count)
     {
          count--;
     }
      
     /* Printing the digits. */
     do
     {
          /* We add 0x30 to a digit to obtain its respective ASCII value.*/
          UARTPutc(num[count--] + 0x30);
     }while(count >= 0);
}

/**
 * \brief  This function is used to print hexadecimal numbers on the serial
 *         console.
 *
 * \param  hexValue   The Hexadecimal number to be printed.
 *
 * \return None
 */

void UARTPutHexNum(unsigned int hexValue)
{
    unsigned char num[8] = {0};
    unsigned int quotient = 0;
    unsigned int dividend = 0;
    int count = 0;

    dividend = hexValue;

    do
    {
        quotient = dividend/16;
        num[count] = (unsigned char)(dividend % 16);
        if(0 == quotient)
        {
            break;
        }
        count++;
        dividend = quotient;

    }while(count < 8);

    if(8 == count)
    {
        count--;
    }

    UARTPutc('0');
    UARTPutc('x');

    while(count >= 0)
    {
        /* Checking for alphanumeric numbers. */
        if((16 - num[count]) <= 6)
        {
            /* Printing alphanumeric numbers. */
            UARTPutc(num[count--] + 0x37);
        }
        else
        {
            /* Printing numbers in the range 0 to 9. */
            UARTPutc(num[count--] + 0x30);
        }
    }
}

/**
 * \brief   This function reads the numbers typed on the serial console.
 *
 * \return  The value entered on the serial console.
 *
 * \note    The numbers that this function can recieve should lie in the
 *          following range:
 *          [-2^(31)] to [2^(31) - 1] i.e.
 *          0x80000000 to  0x7FFFFFFF  
 *
 */

int UARTGetNum(void)  
{
     unsigned char rxByte;
     int sign = 1;
     int value = 0;

     rxByte = UARTGetc();

     /* Accounting for negative numbers.*/
     if('-' == rxByte)
     {
          UARTPutc('-');
          sign = -1;
     }
     else
     {
          UARTPutc(rxByte);
          value = value*10 + (rxByte - 0x30);
     } 
     
     do
     {
          rxByte = UARTGetc();

          /* Echoing the typed characters to the serial console.*/
          UARTPutc(rxByte);
          /*
          ** Checking if the entered character is a carriage return.
          ** Pressing the 'Enter' key on the keyboard executes a 
          ** carriage return on the serial console.
          */
          if('\r' == rxByte)
          {
               break;
          }
          /* 
          ** Subtracting 0x30 to convert the representation of the digit 
          ** from ASCII to hexadecimal.
          */
          value = value*10 + (rxByte - 0x30);

      }while(1);                 

      /* Accounting for the sign of the number.*/
      value = value * sign;

      return value;
}

/**
 * \brief   This function receives hexadecimal numbers entered on the serial
 *          console of the host machine.
 *
 * \param   None
 *
 * \return  The hexadecimal number entered on the serial console of the host
 *          machine.
 *
 * \note    1> The points below explain the ways of entering hexadecimal
 *             numbers:\n
 *             - 0xABCDEF12 - Hexadecimal number preceded by a '0x'.\n
 *             - 0XABCDEF12 - Hexadecimal number preceded by a '0X'.\n
 *             - 0xabcdef12 - Lower-case alphanumeric numbers are allowed.\n
 *             - 0xaBcDeF12 - Intermixing of lower-case and upper-case
 *                            alphanumeric numbers is allowed.\n
 *             - abcdef12   - A preceding '0x' or '0X' is not requried.
 *                            The entered number shall be treated as a
 *                            hexadecimal number.\n
 *             - 12345678   - Interpreted as 0x12345678 and not decimal
 *                            12345678.\n
 *             - xABCDEF12  - A preceding '0' is not required.\n
 *          2> This function does not take into consideration any character
 *             other than a hexadecimal character after reception.\n
 *             Example: Characters in the range G,H,I,...Z or g,h,...,z
 *             are not taken into consideration.\n
 *          3> The maximum value that can be returned by this function
 *             is 0xFFFFFFFF. The reception exits after eight characters have
 *             been received.\n
 *          4> To input a  number lesser that eight characters (Ex: 0x1AB),
 *             press the 'Enter' key after entering the number.\n
 */

unsigned int UARTGetHexNum(void)
{
    unsigned char rxByte;
    unsigned int value = 0;
    unsigned int loopIndex;
    unsigned int byteCount = 0;

    for(loopIndex = 0; loopIndex < 2; loopIndex++)
    {
        /* Receiving bytes from the host machine through serial console. */
        rxByte = UARTGetc();

        /*
        ** Checking if the entered character is a carriage return.
        ** Pressing the 'Enter' key on the keyboard executes a
        ** carriage return on the serial console.
        */
        if('\r' == rxByte)
        {
            break;
        }

        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set A,B,C...F
        */
        if(('A' <= rxByte) && (rxByte <= 'F'))
        {
            /* Echoing the typed characters to the serial console.*/
            UARTPutc(rxByte);
            value = value*16 + (rxByte - 0x37);
            byteCount++;
        }

        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set a,b,c...f
        */
        else if(('a' <= rxByte) && (rxByte <= 'f'))
        {
            UARTPutc(rxByte);
            value = value*16 + (rxByte - 0x57);
            byteCount++;
        }

        /*
        ** Checking if the character entered is one among the decimal
        ** number set 0,1,2,3,....9
        */
        else if(('0' <= rxByte) && (rxByte <= '9'))
        {
            UARTPutc(rxByte);
            value = value*16 + (rxByte - 0x30);
            byteCount++;
        }

        /*
        ** Checking if the character is either a 'x'(lower-case) or an 'X'
        ** (upper-case).
        */
        else if(('x' == rxByte) || ('X' == rxByte))
        {
            UARTPutc(rxByte);
            value = 0;
            break;
        }
    }

    if(0 == value)
    {
        byteCount = 0;
    }

    do
    {
        rxByte = UARTGetc();

        if('\r' == rxByte)
        {
            break;
        }

        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set A,B,C...F
        */
        if(('A' <= rxByte) && (rxByte <= 'F'))
        {
            UARTPutc(rxByte);
            value = value*16 + (rxByte - 0x37);
            byteCount++;
        }

        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set a,b,c...f
        */
        else if(('a' <= rxByte) && (rxByte <= 'f'))
        {
            UARTPutc(rxByte);
            value = value*16 + (rxByte - 0x57);
            byteCount++;
        }

        /*
        ** Checking if the character entered is one among the decimal
        ** number set 0,1,2,3,....9
        */
        else if(('0' <= rxByte) && (rxByte <= '9'))
        {
            UARTPutc(rxByte);
            value = value*16 + (rxByte - 0x30);
            byteCount++;
        }

        /*
        ** Not receiving any other character other than the one belonging
        ** to the above three categories.
        */
        else
        {
            /* Intentionally left empty. */
        }

    }while(byteCount < 8);

    return value;
}

/** 
 * \brief   This function writes a byte on the serial console.
 *
 * \param   byteTx   The byte to be transmitted.
 *
 * \return  None.
 */

void UARTPutc(unsigned char byteTx)
{
     UARTConsolePutc(byteTx);
}

/**
 * \brief   This function reads a byte entered on the serial console.
 *
 * \return  Returns the entered byte typecasted as an unsigned character.
 */

unsigned char UARTGetc(void)
{
     return (UARTConsoleGetc());
}


/**
 * Writes a string of characters to the UART output.
 *
 * \param pcBuf points to a buffer containing the string to transmit.
 * \param len   is the length of the string to transmit.
 *
 * This function will transmit the string to the UART output.  The number of
 * characters transmitted is determined by the \e len parameter.  This
 * function does no interpretation or translation of any characters.  Since
 * the output is sent to a UART, any LF (/n) characters encountered will be
 * replaced with a CRLF pair.
 *
 * Besides using the \e len parameter to stop transmitting the string, if a
 * null character (0) is encountered, then no more characters will be
 * transmitted and the function will return.
 *
 * In non-buffered mode, this function is blocking and will not return until
 * all the characters have been written to the output FIFO.  In buffered mode,
 * the characters are written to the UART transmit buffer and the call returns
 * immediately.  If insufficient space remains in the transmit buffer,
 * additional characters are discarded.
 *
 * \return Returns the count of characters written.
 */
unsigned int UARTwrite(const char *pcBuf, unsigned int len)
{
    unsigned int uIdx;    

    /* Send the characters */
    for(uIdx = 0; uIdx < len; uIdx++)
    {
        /* If the character to the UART is \n, then add a \r before it so that
         * \n is translated to \n\r in the output. */
        if(pcBuf[uIdx] == '\n')
        {
            UARTPutc('\r');
        }

        /* Send the character to the UART output. */
       UARTPutc(pcBuf[uIdx]);
    }

    /* Return the number of characters written. */
    return(uIdx);
}

/**
 * A simple UART based printf function supporting \%c, \%d, \%p, \%s, \%u,
 * \%x, and \%X.
 *
 * \param pcString is the format string.
 * \param ... are the optional arguments, which depend on the contents of the
 * format string.
 *
 * This function is very similar to the C library <tt>fprintf()</tt> function.
 * All of its output will be sent to the UART.  Only the following formatting
 * characters are supported:
 *
 * - \%c to print a character
 * - \%d to print a decimal value
 * - \%s to print a string
 * - \%u to print an unsigned decimal value
 * - \%x to print a hexadecimal value using lower case letters
 * - \%X to print a hexadecimal value using lower case letters (not upper case
 * letters as would typically be used)
 * - \%p to print a pointer as a hexadecimal value
 * - \%\% to print out a \% character
 *
 * For \%s, \%d, \%u, \%p, \%x, and \%X, an optional number may reside
 * between the \% and the format character, which specifies the minimum number
 * of characters to use for that value; if preceded by a 0 then the extra
 * characters will be filled with zeros instead of spaces.  For example,
 * ``\%8d'' will use eight characters to print the decimal value with spaces
 * added to reach eight; ``\%08d'' will use eight characters as well but will
 * add zeroes instead of spaces.
 *
 * The type of the arguments after \e pcString must match the requirements of
 * the format string.  For example, if an integer was passed where a string
 * was expected, an error of some kind will most likely occur.
 *
 * \return None.
 */
void UARTprintf(const char *pcString, ...)
{
    unsigned int idx, pos, count, base, neg;
    char *pcStr, pcBuf[16], cFill;
    va_list vaArgP;
    int value;

    /* Start the varargs processing. */
    va_start(vaArgP, pcString);

    /* Loop while there are more characters in the string. */
    while(*pcString)
    {
        /* Find the first non-% character, or the end of the string. */
        for(idx = 0; (pcString[idx] != '%') && (pcString[idx] != '\0'); idx++)
        {
        }

        /* Write this portion of the string. */
        UARTwrite(pcString, idx);

        /* Skip the portion of the string that was written. */
        pcString += idx;

        /* See if the next character is a %. */
        if(*pcString == '%')
        {
            /* Skip the %. */
            pcString++;

            /* Set the digit count to zero, and the fill character to space
             * (i.e. to the defaults). */
            count = 0;
            cFill = ' ';

            /* It may be necessary to get back here to process more characters.
             * Goto's aren't pretty, but effective.  I feel extremely dirty for
             * using not one but two of the beasts. */
again:

            /* Determine how to handle the next character. */
            switch(*pcString++)
            {
                /* Handle the digit characters. */
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    /* If this is a zero, and it is the first digit, then the
                     * fill character is a zero instead of a space. */
                    if((pcString[-1] == '0') && (count == 0))
                    {
                        cFill = '0';
                    }

                    /* Update the digit count. */
                    count *= 10;
                    count += pcString[-1] - '0';

                    /* Get the next character. */
                    goto again;
                }

                /* Handle the %c command. */
                case 'c':
                {
                    /* Get the value from the varargs. */
                    value = va_arg(vaArgP, unsigned int);

                    /* Print out the character. */
                    UARTwrite((char *)&value, 1);

                    /* This command has been handled. */
                    break;
                }

                /* Handle the %d command. */
                case 'd':
                {
                    /* Get the value from the varargs. */
                    value = va_arg(vaArgP, unsigned int);

                    /* Reset the buffer position. */
                    pos = 0;

                    /* If the value is negative, make it positive and indicate
                     * that a minus sign is needed. */
                    if((int)value < 0)
                    {
                        /* Make the value positive. */
                        value = -(int)value;

                        /* Indicate that the value is negative. */
                        neg = 1;
                    }
                    else
                    {
                        /* Indicate that the value is positive so that a minus
                         * sign isn't inserted. */
                        neg = 0;
                    }

                    /* Set the base to 10. */
                    base = 10;

                    /* Convert the value to ASCII. */
                    goto convert;
                }

                /* Handle the %s command. */
                case 's':
                {
                    /* Get the string pointer from the varargs. */
                    pcStr = va_arg(vaArgP, char *);

                    /* Determine the length of the string. */
                    for(idx = 0; pcStr[idx] != '\0'; idx++)
                    {
                    }

                    /* Write the string. */
                    UARTwrite(pcStr, idx);

                    /* Write any required padding spaces */
                    if(count > idx)
                    {
                        count -= idx;
                        while(count--)
                        {
                            UARTwrite((const char *)" ", 1);
                        }
                    }
                    /* This command has been handled. */
                    break;
                }

                /* Handle the %u command. */
                case 'u':
                {
                    /* Get the value from the varargs. */
                    value = va_arg(vaArgP, unsigned int);

                    /* Reset the buffer position. */
                    pos = 0;

                    /* Set the base to 10. */
                    base = 10;

                    /* Indicate that the value is positive so that a minus sign
                     * isn't inserted. */
                    neg = 0;

                    /* Convert the value to ASCII. */
                    goto convert;
                }

                /* Handle the %x and %X commands.  Note that they are treated
                 * identically; i.e. %X will use lower case letters for a-f
                 * instead of the upper case letters is should use.  We also
                 * alias %p to %x. */
                case 'x':
                case 'X':
                case 'p':
                {
                    /* Get the value from the varargs. */
                    value = va_arg(vaArgP, unsigned int);

                    /* Reset the buffer position. */
                    pos = 0;

                    /* Set the base to 16. */
                    base = 16;

                    /* Indicate that the value is positive so that a minus sign
                     * isn't inserted. */
                    neg = 0;

                    /* Determine the number of digits in the string version of
                     * the value. */
convert:
                    for(idx = 1;
                        (((idx * base) <= value) &&
                         (((idx * base) / base) == idx));
                        idx *= base, count--)
                    {
                    }

                    /* If the value is negative, reduce the count of padding
                     * characters needed. */
                    if(neg)
                    {
                        count--;
                    }

                    /* If the value is negative and the value is padded with
                     * zeros, then place the minus sign before the padding. */
                    if(neg && (cFill == '0'))
                    {
                        /* Place the minus sign in the output buffer. */
                        pcBuf[pos++] = '-';

                        /* The minus sign has been placed, so turn off the
                         * negative flag. */
                        neg = 0;
                    }

                    /* Provide additional padding at the beginning of the
                     * string conversion if needed. */
                    if((count > 1) && (count < 16))
                    {
                        for(count--; count; count--)
                        {
                            pcBuf[pos++] = cFill;
                        }
                    }

                    /* If the value is negative, then place the minus sign
                     * before the number. */
                    if(neg)
                    {
                        /* Place the minus sign in the output buffer. */
                        pcBuf[pos++] = '-';
                    }

                    /* Convert the value into a string. */
                    for(; idx; idx /= base)
                    {
                        pcBuf[pos++] = g_pcHex[(value / idx) % base];
                    }

                    /* Write the string. */
                    UARTwrite(pcBuf, pos);

                    /* This command has been handled. */
                    break;
                }

                /* Handle the %% command. */
                case '%':
                {
                    /* Simply write a single %. */
                    UARTwrite(pcString - 1, 1);

                    /* This command has been handled. */
                    break;
                }

                /* Handle all other commands. */
                default:
                {
                    /* Indicate an error. */
                    UARTwrite((const char *)"ERROR", 5);

                    /* This command has been handled. */
                    break;
                }
            }
        }
    }

    /* End the varargs processing. */
    va_end(vaArgP);
}

/******************************* End of file *********************************/

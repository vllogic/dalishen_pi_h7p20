/*
 * @file     hme_retarget.h
 * @brief    HME HeaderFile
 * @version  0.1
 * @date     01. March 2021
 */

#ifndef __HME_RETARGET_H
#define __HME_RETARGET_H

#include <stdio.h>
#include <stdlib.h>

#include "hme_conf.h"
#include "hme_uart.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UNUSED_PARAM
#   define UNUSED_PARAM(__VAL)      (__VAL) = (__VAL)
#endif

//! \note for IAR
#ifdef __IS_COMPILER_IAR__
#   undef __IS_COMPILER_IAR__
#endif
#if defined(__IAR_SYSTEMS_ICC__)
#   define __IS_COMPILER_IAR__                 1
#endif

//! \note for arm compiler 5
#ifdef __IS_COMPILER_ARM_COMPILER_5__
#   undef __IS_COMPILER_ARM_COMPILER_5__
#endif
#if ((__ARMCC_VERSION >= 5000000) && (__ARMCC_VERSION < 6000000))
#   define __IS_COMPILER_ARM_COMPILER_5__      1
#endif

//! \note for arm compiler 6
#ifdef __IS_COMPILER_ARM_COMPILER_6__
#   undef __IS_COMPILER_ARM_COMPILER_6__
#endif
#if ((__ARMCC_VERSION >= 6000000) && (__ARMCC_VERSION < 7000000))
#   define __IS_COMPILER_ARM_COMPILER_6__      1
#endif

#ifdef __IS_COMPILER_LLVM__
#   undef  __IS_COMPILER_LLVM__
#endif
#if defined(__clang__) && !__IS_COMPILER_ARM_COMPILER_6__
#   define __IS_COMPILER_LLVM__                1
#else
//! \note for gcc
#ifdef __IS_COMPILER_GCC__
#   undef __IS_COMPILER_GCC__
#endif
#if defined(__GNUC__) && !(     __IS_COMPILER_ARM_COMPILER_6__                  \
                            ||  __IS_COMPILER_LLVM__                            \
                            ||  __IS_COMPILER_ARM_COMPILER_5__)
#   define __IS_COMPILER_GCC__                 1
#endif
#endif

#ifndef HME_PRINT_UART
#   define HME_PRINT_UART   UART0
#endif

__WEAK int hme_stdout_putchar(char ch)
{
    while (1 != HME_UART_SendData(HME_PRINT_UART, 1, (uint8_t*)&ch));
    return 1;
}

__WEAK int hme_stderr_putchar(char ch)
{
    return hme_stdout_putchar(ch);
}

__WEAK int hme_stdin_getchar(void)
{
    uint8_t ch;
    while (1 != HME_UART_ReceiveData(HME_PRINT_UART, 1, &ch));
	return ch;
}

__WEAK void HME_Retarget_Init(void)
{
    HME_UART_InitTypeDef init;

    HME_UART_DeInit(HME_PRINT_UART);

    HME_UART_StructInit(&init);
    HME_UART_Init(HME_PRINT_UART, &init);
}

size_t __hme_stdio_write(int handle, const unsigned char *buf, size_t buf_size)
{
    size_t nChars = 0;
    /* Check for the command to flush all handles */
    if (handle == -1) {
        return 0;
    }
    /* Check for stdout and stderr
    (only necessary if FILE descriptors are enabled.) */
    if (handle != 1 && handle != 2) {
        return 0;
    }
    for (/* Empty */; buf_size > 0; --buf_size) {
        hme_stdout_putchar(*buf++);
        ++nChars;
    }
    return nChars;
}

size_t __hme_stdio_read(int handle, unsigned char *buf, size_t buf_size)
{
    size_t nChars = 0;
    /* Check for stdin
    (only necessary if FILE descriptors are enabled) */
    if (handle != 0) {
        return 0;
    }
    for (/*Empty*/; buf_size > 0; --buf_size) {
        uint8_t c = hme_stdin_getchar();
        if (c == 0) {
            break;
        }
        *buf++ = c;
        ++nChars;
    }
    return nChars;
}

#if __IS_COMPILER_ARM_COMPILER_5__ || __IS_COMPILER_ARM_COMPILER_6__
#   include <rt_sys.h>

#define RTE_Compiler_IO_STDOUT
#define RTE_Compiler_IO_STDOUT_User
#define RTE_Compiler_IO_STDIN
#define RTE_Compiler_IO_STDIN_User
#define RTE_Compiler_IO_STDERR
#define RTE_Compiler_IO_STDERR_User

#ifndef STDIN_ECHO
#define STDIN_ECHO 0 /* STDIN: echo to STDOUT */
#endif
#ifndef STDOUT_CR_LF
#define STDOUT_CR_LF 0 /* STDOUT: add CR for LF */
#endif
#ifndef STDERR_CR_LF
#define STDERR_CR_LF 0 /* STDERR: add CR for LF */
#endif

#ifdef RTE_Compiler_IO_STDIN
static int getchar_undo = 0;
static int getchar_ch = -1;
#endif

/**
   Writes the character specified by c (converted to an unsigned char) to
   the output stream pointed to by stream, at the position indicated by the
   associated file position indicator (if defined), and advances the
   indicator appropriately. If the file position indicator is not defined,
   the character is appended to the output stream.

  \param[in] c       Character
  \param[in] stream  Stream handle

  \return    The character written. If a write error occurs, the error
             indicator is set and fputc returns EOF.

int fputc(int c, FILE *stream)
{
    if (stream == &__stdout) {
        return (hme_stdout_putchar(c));
    }

    if (stream == &__stderr) {
        return (hme_stderr_putchar(c));
    }

    return (-1);
}*/

int fputc(int c, FILE *stream)
{
		uint8_t ch = c;
    if (stream == &__stdout) {
		if (c == '\n'){
				ch = '\r';
				hme_stdout_putchar(ch);
		}
        return (hme_stdout_putchar(c));
    }

    if (stream == &__stderr) {
        return (hme_stderr_putchar(c));
    }

    return (-1);
}


/**
   Obtains the next character (if present) as an unsigned char converted to
   an int, from the input stream pointed to by stream, and advances the
   associated file position indicator (if defined).

  \param[in] stream  Stream handle

  \return    The next character from the input stream pointed to by stream.
             If the stream is at end-of-file, the end-of-file indicator is
             set and fgetc returns EOF. If a read error occurs, the error
             indicator is set and fgetc returns EOF.
*/
int fgetc(FILE *stream)
{
    int ch;

    if (stream == &__stdin) {
        if (getchar_undo) {
            ch = getchar_ch;
            getchar_ch = -1;
            getchar_undo = 0;
            return (ch);
        }
        ch = hme_stdin_getchar();

        getchar_ch = ch;
        return (ch);
    }

    return (-1);
}

/**
   The function __backspace() is used by the scanf family of functions, and must
   be re-implemented if you retarget the stdio arrangements at the fgetc()
  level.

  \param[in] stream  Stream handle

  \return    The value returned by __backspace() is either 0 (success) or EOF
             (failure). It returns EOF only if used incorrectly, for example,
             if no characters have been read from the stream. When used
             correctly, __backspace() must always return 0, because the scanf
             family of functions do not check the error return.
*/
__WEAK int __backspace(FILE *stream)
{
    if (stream == &__stdin) {
        if (getchar_ch != -1) {
            getchar_undo = 1;
            return (0);
        }
        return (-1);
    }

    return (-1);
}

/**
  Called from assert() and prints a message on stderr and calls abort().

  \param[in] expr  assert expression that was not TRUE
  \param[in] file  source file of the assertion
  \param[in] line  source line of the assertion
*/
void __aeabi_assert(const char *expr, const char *file, int line)
{
    char str[12], *p;

    fputs("*** assertion failed: ", stderr);
    fputs(expr, stderr);
    fputs(", file ", stderr);
    fputs(file, stderr);
    fputs(", line ", stderr);

    p = str + sizeof(str);
    *--p = '\0';
    *--p = '\n';
    while (line > 0) {
        *--p = '0' + (line % 10);
        line /= 10;
    }
    fputs(p, stderr);

    abort();
}

__WEAK void abort(void)
{
    for (;;);
}

/* IO device file handles. */
#define FH_STDIN  0x8001
#define FH_STDOUT 0x8002
#define FH_STDERR 0x8003

/**
  Defined in rt_sys.h, this function opens a file.

  The _sys_open() function is required by fopen() and freopen(). These
  functions in turn are required if any file input/output function is to
  be used.
  The openmode parameter is a bitmap whose bits mostly correspond directly to
  the ISO mode specification. Target-dependent extensions are possible, but
  freopen() must also be extended.

  \param[in] name     File name
  \param[in] openmode Mode specification bitmap

  \return    The return value is 1 if an error occurs.
*/

//__attribute__((weak))
FILEHANDLE $Sub$$_sys_open(const char *name, int openmode)
{
    UNUSED_PARAM(name);
    UNUSED_PARAM(openmode);

    return (0);
}

/**
  Defined in rt_sys.h, this function closes a file previously opened
  with _sys_open().

  This function must be defined if any input/output function is to be used.

  \param[in] fh File handle

  \return    The return value is 0 if successful. A nonzero value indicates
             an error.
*/
__WEAK int _sys_close(FILEHANDLE fh)
{
    UNUSED_PARAM(fh);
    return 0;
}

/**
  Defined in rt_sys.h, this function writes the contents of a buffer to a file
  previously opened with _sys_open().

  \note The mode parameter is here for historical reasons. It contains
        nothing useful and must be ignored.

  \param[in] fh   File handle
  \param[in] buf  Data buffer
  \param[in] len  Data length
  \param[in] mode Ignore this parameter

  \return    The return value is either:
             - a positive number representing the number of characters not
               written (so any nonzero return value denotes a failure of
               some sort)
             - a negative number indicating an error.
*/

__WEAK int _sys_write(FILEHANDLE fh, const uint8_t *buf, uint32_t len, int mode)
{
    int ch;
    (void)buf;
    (void)len;

    (void)mode;

    switch (fh) {
        case FH_STDIN:
            return (-1);
        case FH_STDOUT:

            for (; len; len--) {
                ch = *buf++;
                hme_stdout_putchar(ch);
            }

            return (0);
        case FH_STDERR:

            for (; len; len--) {
                ch = *buf++;
                hme_stderr_putchar(ch);
            }
            return (0);
    }

    return -1;
}

/**
  Defined in rt_sys.h, this function reads the contents of a file into a buffer.

  Reading up to and including the last byte of data does not turn on the EOF
  indicator. The EOF indicator is only reached when an attempt is made to read
  beyond the last byte of data. The target-independent code is capable of
  handling:
    - the EOF indicator being returned in the same read as the remaining bytes
      of data that precede the EOF
    - the EOF indicator being returned on its own after the remaining bytes of
      data have been returned in a previous read.

  \note The mode parameter is here for historical reasons. It contains
        nothing useful and must be ignored.

  \param[in] fh   File handle
  \param[in] buf  Data buffer
  \param[in] len  Data length
  \param[in] mode Ignore this parameter

  \return     The return value is one of the following:
              - The number of bytes not read (that is, len - result number of
                bytes were read).
              - An error indication.
              - An EOF indicator. The EOF indication involves the setting of
                0x80000000 in the normal result.
*/

__WEAK int _sys_read(FILEHANDLE fh, uint8_t *buf, uint32_t len, int mode)
{
    int ch;

    (void)buf;
    (void)len;

    (void)mode;

    switch (fh) {
        case FH_STDIN:

            ch = hme_stdin_getchar();
            if (ch < 0) {
                return ((int)(len | 0x80000000U));
            }
            *buf++ = (uint8_t)ch;

            len--;
            return ((int)(len));

        case FH_STDOUT:
            return (-1);
        case FH_STDERR:
            return (-1);
    }

    return -1;
}

#elif __IS_COMPILER_IAR__
size_t __write(int handle, const unsigned char *buf, size_t buf_size)
{
    return __hme_stdio_write(handle, buf, buf_size);
}

size_t __read(int handle, unsigned char *buf, size_t buf_size)
{
    return __hme_stdio_read(handle, buf, buf_size);
}
#elif
int _write(int handle, char *buf, int buf_size)
{
    return __hme_stdio_write(handle, (const unsigned char *)buf, buf_size);
}

int _read(int handle, char *buf, int buf_size)
{
    return __hme_stdio_read(handle, (unsigned char *)buf, buf_size);
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* __HME_RETARGET_H */

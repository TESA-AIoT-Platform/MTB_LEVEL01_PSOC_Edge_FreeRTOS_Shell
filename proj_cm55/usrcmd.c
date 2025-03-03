/**
 * @file usrcmd.c
 * @author CuBeatSystems
 * @author Shinichiro Nakamura
 * @copyright
 * ===============================================================
 * Natural Tiny Shell (NT-Shell) Version 0.3.1
 * ===============================================================
 * Copyright (c) 2010-2016 Shinichiro Nakamura
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


#include "ntopt.h"
#include "ntlibc.h"
#include "ntshell.h"
#include <stdio.h>

#include "ntshell.h"
#include "ntlibc.h"
#include "psoc6_ntshell_port.h"
#include "cy_retarget_io.h"

#include "FreeRTOS.h"
#include "task.h"
#include "poten_task.h"

static ntshell_t ntshell;

typedef int (*USRCMDFUNC)(int argc, char **argv);

static int usrcmd_ntopt_callback(int argc, char **argv, void *extobj);
static int usrcmd_help(int argc, char **argv);
static int usrcmd_info(int argc, char **argv);
static int usrcmd_clear(int argc, char **argv);
//static int usrcmd_pargs(int argc, char **argv);
static int usrcmd_blink(int argc, char **argv);
static int usrcmd_poten(int argc, char **argv);
#ifdef configUSE_TRACE_FACILITY
#if configUSE_STATS_FORMATTING_FUNCTIONS ==1
static int usrcmd_list(int argc, char **argv);
#endif
#endif

typedef struct {
    char *cmd;
    char *desc;
    USRCMDFUNC func;
} cmd_table_t;

static const cmd_table_t cmdlist[] = {
    { "help", " Show all commands on Infineon's PSoC Edge (E84) Board", usrcmd_help },
    { "info", " Describe the developer team and released version", usrcmd_info },
    { "clear", " Clear the screen", usrcmd_clear },
    //{ "pargs","print the list of arguments", usrcmd_pargs},
	{ "blink"," Enable start/stop USER LED blinking", usrcmd_blink},
	{ "poten"," Read the POTEN's values", usrcmd_poten},
#ifdef configUSE_TRACE_FACILITY 
#if configUSE_STATS_FORMATTING_FUNCTIONS ==1
    { "tasks"," print the list of RTOS Tasks", usrcmd_list},
#endif
#endif
};


void usrcmd_task()
{

  setvbuf(stdin, NULL, _IONBF, 0);
  /* \x1b[2J\x1b[;H - ANSI ESC sequence to clear screen. */
  printf("\x1b[2J\x1b[;H");

  ntshell_init(
	       &ntshell,
	       ntshell_read,
	       ntshell_write,
	       ntshell_callback,
	       (void *)&ntshell);
  ntshell_set_prompt(&ntshell, "TESA_Shell:~$ ");
  vtsend_erase_display(&ntshell.vtsend);
  printf("Started Command Line Interface via TESA::BDH Shell\n");
  ntshell_execute(&ntshell);
}

int usrcmd_execute(const char *text)
{
    return ntopt_parse(text, usrcmd_ntopt_callback, 0);
}

static int usrcmd_ntopt_callback(int argc, char **argv, void *extobj)
{
    if (argc == 0) {
        return 0;
    }
    const cmd_table_t *p = &cmdlist[0];
    for (unsigned int i = 0; i < sizeof(cmdlist) / sizeof(cmdlist[0]); i++) {
        if (ntlibc_strcmp((const char *)argv[0], p->cmd) == 0) {
            return p->func(argc, argv);
        }
        p++;
    }
    printf("%s","Unknown command found.\n");
    return 0;
}

static int usrcmd_help(int argc, char **argv)
{
    const cmd_table_t *p = &cmdlist[0];
    for (unsigned int i = 0; i < sizeof(cmdlist) / sizeof(cmdlist[0]); i++) {
        printf("%s",p->cmd);
        printf("%s","\t:");
        printf("%s",p->desc);
        printf("%s","\n");
        p++;
    }
    return 0;
}


static int usrcmd_info(int argc, char **argv)
{
    if (argc != 2) {
        printf("%s","info sys\n");
        printf("%s","info ver\n");
        return 0;
    }
    if (ntlibc_strcmp(argv[1], "sys") == 0) {
        printf("%s","Infineon's PSoC Edge (E84) CLI Console, CopyRight by TESA & BDH\n");
        return 0;
    }
    if (ntlibc_strcmp(argv[1], "ver") == 0) {
        printf("%s","Version 0.1 - March 2025\n");
        return 0;
    }
    printf("%s","Unknown sub command found\n");
    return -1;
}


static int usrcmd_clear(int argc, char **argv)
{
    vtsend_erase_display_home(&ntshell.vtsend);
    return 0;
}

//static int usrcmd_pargs(int argc, char **argv)
//{
//    printf("ARGC = %d\n",argc);
//
//    for(int i =0;i<argc;i++)
//    {
//        printf("argv[%d] = %s\n",i,argv[i]);
//    }
//    return 0;
//
//}

static int usrcmd_blink(int argc, char **argv)
{
    if (argc != 2) {
        printf("%s","blink start\n");
        printf("%s","blink stop\n");
        return 0;
    }
    if (ntlibc_strcmp(argv[1], "start") == 0) {
        printf("%s","Starting blinking...\n");
        LED_blink_control(1);
        return 0;
    }
    if (ntlibc_strcmp(argv[1], "stop") == 0) {
        printf("%s","Stopping blinking...\n");
        LED_blink_control(0);
        return 0;
    }
    printf("%s","Unknown sub command found\n");
    return -1;
}

static int usrcmd_poten(int argc, char **argv)
{
	vtsend_erase_display_home(&ntshell.vtsend);
	vtsend_set_cursor(&ntshell.vtsend, 0);
	live_print_poten_status();
	vtsend_set_cursor(&ntshell.vtsend, 1);
    return 0;
}

void live_print_poten_status()
{
	/* Variable for storing character read from terminal */
//	uint8_t uart_read_value;
//	size_t num_read;

	for (;;)
	    {
			print_poten_status();
			vtsend_cursor_up(&ntshell.vtsend, 3);
//	        /* Check if 'Enter' key was pressed */
//		    /* Attempt to read one byte from the UART */
//		    cy_rslt_t result = cyhal_uart_read(&cy_retarget_io_uart_obj, &uart_read_value, 1, &num_read);
//
//		    /* Check if the read was successful and one byte was read */
//		    if ((result == CY_RSLT_SUCCESS) && (num_read == 1))
//		    {
//		        if (uart_read_value == '\r')
//		            break;
//
//		        /* Process the received character as needed */
//		    }
	    }
	printf("\n\n\n");
}


#ifdef configUSE_TRACE_FACILITY
#if configUSE_STATS_FORMATTING_FUNCTIONS ==1
static int usrcmd_list(int argc,char **argv)
{
    // 40 bytes/task + some margin
    char buff[40*10 + 100];

    vTaskList( buff );
    printf("Name          State Priority   Stack  Num\n");
    printf("------------------------------------------\n");
    printf("%s",buff);

    printf("‘B’ – Blocked\n‘R’ – Ready\n‘D’ – Deleted (waiting clean up)\n‘S’ – Suspended, or Blocked without a timeout\n");
    printf("Stack = bytes free at highwater\n");
    return 0;
}
#endif
#endif

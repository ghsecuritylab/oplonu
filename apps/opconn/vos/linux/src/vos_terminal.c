/*************************************************************************
*
*  COPYRIGHT (C) 2003-2008 Opulan Technologies Corp. ALL RIGHTS RESERVED.  
*
*                       Proprietary and Confidential
*
* 	This software is made available only to customers and prospective
* 	customers of Opulan Technologies Corporation under license and may be
*	used only with Opulan semi-conductor products. 
*
* FILENAME:  vos_terminal.c
*
* DESCRIPTION: 
*	
*
* Date Created: May 20, 2008
*
* Authors(optional): Gan Zhiheng
*
* Reviewed by (optional):
*
* Edit History:
* $Id: //depot/sw/abu/opconn/release/v3.2.1/apps/opconn/vos/linux/src/vos_terminal.c#1 $
* $Log:$
*
*
**************************************************************************/
     
#include <termios.h>
#include <string.h>
#include <vos_terminal.h>
#include <vos_sync.h>

static struct termios initial_settings, new_settings;

static VOS_MUTEX_t g_pstTerminalLock;

int vosTerminalInit(void)
{
    if (VOS_MUTEX_OK != vosMutexCreate(&g_pstTerminalLock))
    { 
        printf("vosTerminalInit: create mutex failed.\r\n");
        return -1;
    } 
    return 0;
}


int vosTermSettingsGet(int fd, void *pSettings)
{
    return tcgetattr(fd, (struct termios *)pSettings);
}

int vosTermSettingsSet(int fd, const void *pSettings)
{
    return tcsetattr(fd, TCSANOW, (struct termios *)pSettings);
}

int vosTermBackup(int fd)
{
    int rv;

    vosMutexTake(&g_pstTerminalLock);

    rv = tcgetattr(fd, &initial_settings);

    vosMutexGive(&g_pstTerminalLock);

    return rv;
}

int vosTermConfig(int fd)
{
    int rv;

    vosMutexTake(&g_pstTerminalLock);

    memcpy(&new_settings, &initial_settings, sizeof(new_settings));
    new_settings.c_lflag &= ~ICANON;        /* unbuffered input */
    /* Turn off echoing and CTRL-C, so we can trap it */
    new_settings.c_lflag &= ~(ECHO | ECHONL | ISIG);
    /* Hmm, in linux c_cc[] is not parsed if ICANON is off */
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    /* Turn off CTRL-C, so we can trap it */
#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE '\0'
#endif
    new_settings.c_cc[VINTR] = _POSIX_VDISABLE;

    rv = tcsetattr(fd, TCSANOW, &new_settings);

    vosMutexGive(&g_pstTerminalLock);

    return rv;
}

int vosTermRestore(int fd)
{
    int rv;

    vosMutexTake(&g_pstTerminalLock);

    rv = tcsetattr(fd, TCSANOW, &initial_settings);

    vosMutexGive(&g_pstTerminalLock);

    return rv;
}



/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : cantype.h
 * Author        : xundanqing
 * Date          : 2018-09-13
 * Description   : .C file function description
 * Version       : 1.0
 * Function List :
 * 
 * Record        :
 * 1.Date        : 2018-09-13
 *   Author      : xundanqing
 *   Modification: Created file

*************************************************************************************************************/

#ifndef  _CAN_TYPE_H
#define  _CAN_TYPE_H
#include <map>
#include <string>
#include <net/if.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <linux/can/raw.h>
#include "list.h"
#define   CANLEN              (4096)
#define   CAN_SUCCESS           ( 0)
#define   CAN_ERROR             (-1)
#define   CAN_DECOLER_CONTIN    ( 0)
#define   CAN_DECOLER_SUCCESS   ( 1)

using  namespace  std;

/*can  Packet  send */
typedef   struct    st_CanPacket
{
   unsigned char   srcaddr;
   unsigned char   dstaddr;
   unsigned char   packetid;
   unsigned char*  buffer;
   int         ibufferlen;
   
}stCanPacket;


/*can  SendBuffer  Quene*/
typedef   struct    st_CantimeNode
{   
    int    ilen;
    int    iSendnum;
    unsigned char*  buffer;
    unsigned int    hashkey;    
    SysListHead     list;
    
}stCantimeNode;


typedef   int       CAN_API; 
typedef   struct    can_filter  CanFilter;
typedef   struct    can_frame   stCanframe; 
typedef   int      (*CmdAction) (unsigned  char *buffer,int ilen);

#endif

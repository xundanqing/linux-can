/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : can.h
 * Author        : xundanqing
 * Date          : 2018-09-10
 * Description   : .h file function description
 * Version       : 1.0
 * Function List :
 * 
 * Record        :
 * 1.Date        : 2018-09-10
 *   Author      : xundanqing
 *   Modification: Created file

*************************************************************************************************************/
#ifndef  _CAN_H
#define  _CAN_H

#include "list.h"
#include "cantype.h"
#include "canclient.h"
#include "circlebuffer.h"

class     CanDevice
{

  public:
  
     CanDevice(string  PortName);
    ~CanDevice();

     CAN_API       CanInit();
     CAN_API       CanSetFilter   ( );
     CAN_API       CanrecvStart   ( );
     CAN_API       CanDeveviceProc( );
     static void * CanRecvThread  (void *arg);
     static void * CanSendThread  (void *arg);
     CAN_API       CanProcCanframe(stCanframe     CanFrame);
     CAN_API       CanAddClient   (CanClient*     Canclient);
     CAN_API       CanSendBuffer  (stCanPacket    CanPacket);
     CanClient*    CanClientAdapt (stCanframe     CanFrame );

     
  private:
  
      int          iCanfd;
      int          iCantag;
      string       CanPort;
      SysListHead  list;
      map<int   ,CanClient* > CanClientMng;  

};


#endif

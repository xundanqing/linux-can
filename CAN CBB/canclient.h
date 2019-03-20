/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : canclient.h
 * Author        : xundanqing
 * Date          : 2018-09-12
 * Description   : .C file function description
 * Version       : 1.0
 * Function List :
 * 
 * Record        :
 * 1.Date        : 2018-09-12
 *   Author      : xundanqing
 *   Modification: Created file

*************************************************************************************************************/
#ifndef  CAN_CLIENT_H
#define  CAN_CLIENT_H

#include"cantype.h"
#include"candecoler.h"

class      CanClient 
{
  public :
     CanClient(string  name);
     ~CanClient();
     CanDecoler  Clientdecoler;
     string      GetClientname();
     CanFilter   GetCanfilter ();
     int         SetCanfilter (CanFilter    stCanfilter);
     int         SendCanPacket(stCanPacket  CanPacket  );
     int         ReadCanPacket(stCanframe   CanFrame   );
     int         RegCanAction (CmdAction    CallBackFun);
     
  private:
     string      Clientname;
     CanFilter   Canfilter;
     CmdAction   CanAction;
     
};

#endif

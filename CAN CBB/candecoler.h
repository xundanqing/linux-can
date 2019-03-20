/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : candecoler.h
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
#ifndef  CAN_DECOLER_H
#define  CAN_DECOLER_H

#include "cantype.h"
#include "circlebuffer.h"

class    CanDecoler
{
   public :
   
     CanDecoler();
     ~CanDecoler();
     int  GetDecolerSta();
     int  GetCanSta  (stCanframe   canframe);
     int  PushCanData(stCanframe   canframe);
     int  PoPCanData (unsigned char* data,int  len);
     int  CrcCanData (unsigned char* data,int  len);
     
   private:
 
     int   CanDecolerSta;
     CircleQue  CanQuene;
     
};

#endif 

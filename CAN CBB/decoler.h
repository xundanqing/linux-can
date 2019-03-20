/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : decoler.h
 * Author        : xundanqing
 * Date          : 2018-09-11
 * Description   : .C file function description
 * Version       : 1.0
 * Function List :
 * 
 * Record        :
 * 1.Date        : 2018-09-11
 *   Author      : xundanqing
 *   Modification: Created file

*************************************************************************************************************/
#ifndef  _DECOLER_H_
#define  _DECOLER_H_

#include "circlebuffer.h"

/*检索数据包状态*/
#define  DECOLER_BEGIN   (1)
#define  DECOLER_HEAD    (2)
#define  DECOLER_LEN     (3)
#define  DECOLER_DATA    (4)
#define  DECOLER_END     (5)

#define  DECOLER_ERROR   (-1)
#define  DECOLER_SUCCESS ( 1)

/*命令信息*/
typedef  int (*CmdAction)(unsigned  char * buffer,int ilen);

/*检索数据*/
class  Decoler
{
  
  public :
    Decoler();
   ~Decoler();
    Decoler(unsigned char  *buf,int ilen);
    int SetPrifix  (unsigned char *buf,int  ilen);
    int PushDecoler(unsigned char *buf,int  ilen);
    int PoPDecoler (unsigned char *buf,int  ilen);
    int CrcDecoler (unsigned char *buf,int  ilen);
    int RegCallBack(CmdAction CallBack);

  private :
    int Gethead ();
    int Getlenth();
    int Getdata ();
    
  private :
    
    int   DecolerLen;
    int   DecolerSta;
    char* DecolerPrifix;
    int   DecolerPrifixlen;
    CmdAction  CallBackFun;
    CircleQue  Circlebuffer;
    
};

#endif

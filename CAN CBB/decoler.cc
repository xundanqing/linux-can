/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : decoler.cc
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
#include<stdio.h>
#include<string.h>
#include"decoler.h"
#include"circlebuffer.h"
/*****************************************************************************
 * Function      : Decoler.Decoler
 * Description   : 解包器构造函数
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
Decoler::Decoler()
{
   DecolerLen    = 0;
   DecolerPrifix = NULL;
   CallBackFun   = NULL;
   DecolerSta    = DECOLER_BEGIN;
}
/*****************************************************************************
 * Function      : Decoler.Decoler
 * Description   : 构造函数重载
 * Input         : unsigned char  *buf  
                int ilen             
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
Decoler::Decoler(unsigned char  *buf,int ilen)
{

   DecolerPrifix     = NULL;
   
   if(buf && ilen)
   {  
       DecolerPrifixlen = ilen ;
       DecolerPrifix =    new char[ilen];
       memcpy(DecolerPrifix ,buf,ilen);
   }
}
/*****************************************************************************
 * Function      : Decoler.~Decoler
 * Description   : 解包器析构函数
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
Decoler :: ~Decoler()
{
   if(DecolerPrifix)
   {
      delete  DecolerPrifix;
      DecolerPrifix  = NULL;
   }
}
/*****************************************************************************
 * Function      : Decoler.SetPrifix
 * Description   : 设置包头检索数据头
 * Input         : unsigned char *buf  
                int  ilen           
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  Decoler :: SetPrifix  (unsigned char *buf,int  ilen)
{
   if(buf && ilen)
   {
       DecolerPrifixlen =  ilen ;
       DecolerPrifix    =  new char[ilen];
       memcpy(DecolerPrifix ,buf,ilen);
       return  DECOLER_ERROR;
   }
   return    DECOLER_SUCCESS;
}
/*****************************************************************************
 * Function      : Decoler.PushDecoler
 * Description   : 放置缓冲区数据
 * Input         : unsigned char *buf  
                int  ilen           
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int Decoler :: PushDecoler(unsigned char *buf,int  ilen)
{
    if(Circlebuffer.QuenePush(buf,ilen)== CIRCLE_TRUE)
    {
       return  DECOLER_SUCCESS;
    }
    return     DECOLER_ERROR;
}
/*****************************************************************************
 * Function      : Decoler.Gethead
 * Description   : 获得数据头
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int Decoler :: Gethead ()
{

   int  iCirQueLen =  Circlebuffer.GetCircleQueLen();
   int  iCheckNum  =  iCirQueLen -  DecolerPrifixlen;
   
   if(iCheckNum)
   {
       for(int  inum = 0;inum <  iCheckNum; inum++)
       {
          unsigned char   cbuffer[4] = {0};
          Circlebuffer.QueCheck(cbuffer ,DecolerPrifixlen);
          if(memcmp(cbuffer,DecolerPrifix,DecolerPrifixlen)== 0)
          {
              for(inum  = 0 ;inum < DecolerPrifixlen; inum++  )
              {
                  Circlebuffer.CircleShiftCheck();
              }
              
              DecolerSta =  DECOLER_LEN;
              return    DECOLER_SUCCESS;
          }
          Circlebuffer.CircleShiftCheck();
          Circlebuffer.CircleCheckFront();
       }
   }
   return   DECOLER_ERROR; 
}
/*****************************************************************************
 * Function      : Decoler.Getlenth
 * Description   : 获得数据长度信息
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int Decoler ::  Getlenth()
{
    int  iCircleLen =  Circlebuffer.GetCircleQueLen();
    if (iCircleLen - DecolerPrifixlen >  sizeof(short))
    {
        unsigned  char  sCmdLen[2];
        Circlebuffer.QueCheck(sCmdLen, 2);
        DecolerLen = sCmdLen[0]*256+sCmdLen[1];
        DecolerSta = DECOLER_DATA;
        return       DECOLER_SUCCESS;
    }
    return           DECOLER_ERROR;
}
/*****************************************************************************
 * Function      : Decoler.Getdata
 * Description   : 获得数据内容
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int Decoler ::  Getdata ()
{
	int  iCircleLen = Circlebuffer.GetCircleQueLen();
    if(iCircleLen >=  DecolerLen)
    {
       DecolerSta = DECOLER_END;
       return       DECOLER_SUCCESS;
    }
    return          DECOLER_ERROR;
}
/*****************************************************************************
 * Function      : Decoler.PoPDecoler
 * Description   : 读取缓冲区中的数据
 * Input         : unsigned char *buf  
                int  ilen           
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int Decoler ::PoPDecoler  (unsigned char *buf, int  ilen)
{

    if(DecolerSta == DECOLER_END)
       DecolerSta =  DECOLER_BEGIN;
       
    if(DecolerSta == DECOLER_BEGIN)
       Gethead();
       
    if(DecolerSta== DECOLER_LEN)
       Getlenth();
       
    if(DecolerSta == DECOLER_DATA)
       Getdata();
       
    if(DecolerSta == DECOLER_END)
    {
       Circlebuffer.QuenePoP(buf,ilen);
       Circlebuffer.CircleFrontCheck();
       return   DECOLER_SUCCESS;
    }  

    return   DECOLER_ERROR;
}
/*****************************************************************************
 * Function      : Decoler.CrcDecoler
 * Description   : 数据校验
 * Input         : unsigned char *buf  
                int  ilen           
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int Decoler ::CrcDecoler (unsigned char *buf,  int  ilen)
{
   return   DECOLER_SUCCESS;
}
/*****************************************************************************
 * Function      : Decoler.RegCallBack
 * Description   : 注册处理回调函数
 * Input         : CmdAction CallBack  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int Decoler ::RegCallBack(CmdAction CallBack)
{
    if(CallBack)
    {
        CallBackFun =  CallBack;
        return  DECOLER_SUCCESS;
    }
    return DECOLER_ERROR;
}

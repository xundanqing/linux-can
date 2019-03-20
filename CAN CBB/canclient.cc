/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : canclient.cc
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
#include"can.h"
#include"canclient.h"
#include"candecoler.h"
#include"circlebuffer.h"
#include<string.h>
/*****************************************************************************
 * Function      : CanClient.CanClient
 * Description   : Can对接设备构造
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CanClient::CanClient(string  name)
{
   CanAction  =  NULL;
   Clientname =  name;
}
/*****************************************************************************
 * Function      : CanClient.~CanClient
 * Description   : Can decoler 析构函数
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CanClient::~CanClient()
{}
/*****************************************************************************
 * Function      : CanClient.SetCanfilter
 * Description   : 设置Canfiler
 * Input         : CanFilter    stCanfilter  
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int   CanClient::SetCanfilter (CanFilter    stCanfilter)
{
      Canfilter = stCanfilter;
}
/*****************************************************************************
 * Function      : CanClient.GetCanfilter
 * Description   : 获得Can 过滤规则
 * Input          : None
 * Output        : None
 * Return        : CanFilter
 * Others        : 
 * Record
 * 1.Date        : 20180913
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CanFilter CanClient :: GetCanfilter()
{
    return   Canfilter;
}
/*****************************************************************************
 * Function      : CanClient.Clientname
 * Description   : 获得Can 名称
 * Input          : None
 * Output        : None
 * Return        : char*
 * Others        : 
 * Record
 * 1.Date        : 20180913
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
string   CanClient:: GetClientname()
{
    return  Clientname;
}
/*****************************************************************************
 * Function      : CanClient.GetCanPacketid
 * Description   : 获得CAN数据id
 * Input         : stCanPacket  CanPacket  
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int   CanClient::SendCanPacket(stCanPacket  CanPacket)
{
   
}
/*****************************************************************************
 * Function      : CanClient.ReadCanPacket
 * Description   : Can 读取数据处理
 * Input         : stCanframe   CanFrame  
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int   CanClient::ReadCanPacket(stCanframe   CanFrame )
{
    int  ilen = 0;
    unsigned  char Candata[CANLEN];
    memset( Candata, 0x00, CANLEN);
    
    if(Clientdecoler.PushCanData(CanFrame) ==  CAN_ERROR)
        return  CAN_ERROR;

    if(Clientdecoler.GetDecolerSta()==CAN_DECOLER_CONTIN)
        return  CAN_ERROR;  
    
    if((ilen = Clientdecoler.PoPCanData(Candata, CANLEN)))
    {
        if(CanAction)
            CanAction(Candata,ilen);
    }
    
    return   CAN_ERROR;
}
/*****************************************************************************
 * Function      : CanClient.RegCanAction
 * Description   : 注册回调函数
 * Input         : CmdAction    CallBackFun  
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int    CanClient:: RegCanAction (CmdAction    CallBackFun)
{
    if(CallBackFun)
    {
        CanAction =  CallBackFun;
        return       CAN_SUCCESS;
    }
    
    return  CAN_ERROR;
}

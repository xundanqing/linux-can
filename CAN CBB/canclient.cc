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
 * Description   : Can�Խ��豸����
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
 * Description   : Can decoler ��������
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
 * Description   : ����Canfiler
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
 * Description   : ���Can ���˹���
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
 * Description   : ���Can ����
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
 * Description   : ���CAN����id
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
 * Description   : Can ��ȡ���ݴ���
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
 * Description   : ע��ص�����
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

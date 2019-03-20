/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : candecoler.cc
 * Author        : xundanqing
 * Date          : 2018-09-10
 * Description   : .C file function description
 * Version       : 1.0
 * Function List :
 * 
 * Record        :
 * 1.Date        : 2018-09-10
 *   Author      : xundanqing
 *   Modification: Created file

*************************************************************************************************************/
#include"can.h"
#include"candecoler.h"
#include"circlebuffer.h"
/*****************************************************************************
 * Function      : CanDecoler.CanDececoler
 * Description   : CAN 解包器
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CanDecoler :: CanDecoler()
{
   CanDecolerSta =  CAN_DECOLER_CONTIN;
}
/*****************************************************************************
 * Function      : CanDecoler.CanDececoler
 * Description   : CAN 解包器
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CanDecoler ::  ~CanDecoler()
{
}
/*****************************************************************************
 * Function      : CanDecoler.GetDecolerSta
 * Description   : 获得当前的Decoler 状态
 * Input          : None
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180913
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CanDecoler :: GetDecolerSta()
{
    return   CanDecolerSta;
}
/*****************************************************************************
 * Function      : CanDecoler.GetCanSta
 * Description   : 通过CAN帧获得当前的数据包状态
 * Input         : stCanframe  canframe  
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CanDecoler ::  GetCanSta  (stCanframe  canframe)
{
    if((canframe.can_id & 0X00000010)>>4)
        return  CAN_DECOLER_CONTIN;
        
    else 
        return CAN_DECOLER_SUCCESS;
}
/*****************************************************************************
 * Function      : CanDecoler.PushCanData
 * Description   : Can Push放置缓冲区数据
 * Input         : stCanframe  canframe  
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CanDecoler :: PushCanData(stCanframe  canframe)
{

   if(CanQuene.CircleQueLeft()  <  canframe.can_dlc)
      return  CAN_ERROR;
   
   if(CanQuene.QuenePush(canframe.data,canframe.can_dlc)==CIRCLE_FALSE)
      return  CAN_ERROR;

   CanDecolerSta =  GetCanSta(canframe);
   
   return     CAN_SUCCESS;
}
/*****************************************************************************
 * Function      : CanDecoler.PoPCanData
 * Description   : 读取数据缓冲区
 * Input         : unsigned char* data  
                int  len             
 * Output        : None
 * Return        : int 数据读取的长度值，0 无整包数据，0 <有数据
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int CanDecoler:: PoPCanData (unsigned char* data,int  len)
{

    int  iCandatalen  =  CanQuene.GetCircleQueLen();
    
    if(CanDecolerSta !=  CAN_DECOLER_SUCCESS)
      return   0;

    if(CanQuene.QuenePoP(data,iCandatalen)== CIRCLE_FALSE)
       return  0;
    
    CanDecolerSta =  CAN_DECOLER_CONTIN;
     
    return    iCandatalen;
}
/*****************************************************************************
 * Function      : CanDecoler.CrcCanData
 * Description   : 校验当前的CAN数据
 * Input         : unsigned char* data  
                int  len             
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int CanDecoler:: CrcCanData (unsigned char* data,int  len)
{
    return   CAN_SUCCESS;
}



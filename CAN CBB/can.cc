/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : can.cc
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
#include "list.h"
#include "can.h"
#include "cantype.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
/*****************************************************************************
 * Function      : CanDevice.CanDev
 * Description   : Can构造函数
 * Input         : char *CanName   
                char *PortName  
 * Output        : None
 * Return        : CAN_API
 * Others        : 
 * Record
 * 1.Date        : 20180910
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CanDevice:: CanDevice (string  PortName)
{   
    iCanfd  =  0;
    iCantag =  0;
    CanPort =  PortName;
}
/*****************************************************************************
 * Function      : CanDevice.~CanDev
 * Description   : 
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180910
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CanDevice ::  ~CanDevice()
{ 
}
/*****************************************************************************
 * Function      : CanDevice.CanInit
 * Description   : Can 初始化
 * Input          : None
 * Output        : None
 * Return        : CAN_API
 * Others        : 
 * Record
 * 1.Date        : 20180910
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CAN_API  CanDevice :: CanInit()
{
    struct ifreq ifr;
	struct sockaddr_can can_addr;
	
	iCanfd =  socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if(iCanfd < 0)
		 return  CAN_ERROR;

	can_addr.can_family = PF_CAN;
	strncpy(ifr.ifr_name,(const char* )CanPort.c_str(), sizeof(ifr.ifr_name));
	if(ioctl(iCanfd, SIOCGIFINDEX, &ifr)) 
		 return  CAN_ERROR;

	can_addr.can_ifindex = ifr.ifr_ifindex;
	if(bind(iCanfd, (struct sockaddr *)&can_addr, sizeof(can_addr)) < 0)
		 return  CAN_ERROR; 
    
    return       CAN_SUCCESS;
}
/*****************************************************************************
 * Function      : CanDevice.CanSetRule
 * Description   : 设置Can 过滤规则
 * Input          : None
 * Output        : None
 * Return        : CAN_API
 * Others        : 
 * Record
 * 1.Date        : 20180913
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CAN_API   CanDevice :: CanSetFilter()
{
    if(CanClientMng.size())
    {
        int  index = 0;
        int         iFileternum     =       CanClientMng.size();
        CanFilter*  CanFilterTable  =  new  CanFilter[iFileternum];

        map<int  ,CanClient* >::iterator   iter;
        for(iter = CanClientMng.begin();iter!=  CanClientMng.end();iter++)
        {
           CanFilterTable[index].can_id   = iter->second->GetCanfilter().can_id;
           CanFilterTable[index].can_mask = iter->second->GetCanfilter().can_mask;
           index++;
        } 
       
	    if(setsockopt(iCanfd, SOL_CAN_RAW, CAN_RAW_FILTER,CanFilterTable,\
                                        iFileternum* sizeof(CanFilter)) != 0)
        {
           delete  []CanFilterTable;
           return    CAN_ERROR;
        }
        
        delete  []CanFilterTable;
        return       CAN_SUCCESS;
    }
    return     CAN_ERROR;
}
/*****************************************************************************
 * Function      : CanDevice.CanAddClient
 * Description   : 添加Can 客户端
 * Input         : CanClient  Canclient  
 * Output        : None
 * Return        : CAN_API
 * Others        : 
 * Record
 * 1.Date        : 20180912
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CAN_API  CanDevice ::  CanAddClient (CanClient * Canclient)
{
    if(Canclient)
    {
       CanFilter Canidfilter = Canclient->GetCanfilter();
       map<int  , CanClient *>::iterator iter ;
       iter  =    CanClientMng.find(Canidfilter.can_id);
       if(iter == CanClientMng.end())
       {
           CanClientMng[Canidfilter.can_id] = Canclient;
           return CAN_SUCCESS;
       }
    }
    return         CAN_ERROR;
}
/*****************************************************************************
 * Function      : CanDevice.CanSendBuffer
 * Description   : 发送CAN数据
 * Input         : char      *pcBuffer  
                int  Bufferlen       
 * Output        : None
 * Return        : CAN_API
 * Others        : 
 * Record
 * 1.Date        : 20180910
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CAN_API CanDevice :: CanSendBuffer(stCanPacket  CanPacket)
{
    if(CanPacket.buffer && CanPacket.ibufferlen)
    {
        return  CAN_SUCCESS;
    } 
    return        CAN_ERROR;
}
/*****************************************************************************
 * Function      : CanClientAdapt
 * Description   : 适配注册的Can 客户端，返回当前的CanClient
 * Input         : stCanframe     CanFrame  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180913
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CanClient* CanDevice ::   CanClientAdapt (stCanframe     CanFrame )
{ 
    int  Canid =  (CanFrame.can_id & 0X7FFFFFFF)&(0XFFFF0000>>3);
    map<int ,CanClient *>::iterator iter  = CanClientMng.find(Canid);
    if(iter != CanClientMng.end())
    {
        return  iter->second;
    }
    return  NULL;
}
/*****************************************************************************
 * Function      : CanDevice.CanProcCanframe
 * Description   : 处理CAN帧
 * Input         : stCanframe     CanFrame  
 * Output        : None
 * Return        : CAN_API
 * Others        : 
 * Record
 * 1.Date        : 20180913
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CAN_API CanDevice :: CanProcCanframe(stCanframe     CanFrame)
{ 
    CanClient*  pclient =   CanClientAdapt(CanFrame);
    if(pclient)
    {
        pclient->ReadCanPacket(CanFrame);
        return  CAN_SUCCESS;
    }
    return   CAN_ERROR;
}
/*****************************************************************************
 * Function      : CanDevice.CanDeveviceProc
 * Description   : 读取Can设备处理流程
 * Input          : None
 * Output        : None
 * Return        : CAN_API
 * Others        : 
 * Record
 * 1.Date        : 20180913
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CAN_API CanDevice :: CanDeveviceProc()
{ 

   while(1)
   {
      timeval     stime;  
      stime.tv_sec  = 5;  
      stime.tv_usec = 0;   
      fd_set     readfd;   
      FD_ZERO(&readfd );   
      FD_SET (iCanfd, &readfd);  
     
      if (select(iCanfd+1, &readfd, 0, 0, &stime) > 0)  
      {    
           stCanframe  Canframe ;
           memset(&Canframe,0x00,sizeof(stCanframe));
           if (read(iCanfd,&Canframe,sizeof(stCanframe)) > 0)   
           {    
               CanProcCanframe(Canframe);
           }      
           else    
           {          
                    
           }
      } 
   }
}
/*****************************************************************************
 * Function      : CanDevice.CanRecvThread
 * Description   : Can 读取线程处理
 * Input         : void *arg  
 * Output        : None
 * Return        : void
 * Others        : 
 * Record
 * 1.Date        : 20180914
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
void *  CanDevice ::CanRecvThread  (void *arg)
{
	CanDevice*  Candev =   (CanDevice*) arg;
	Candev->CanDeveviceProc();
}
/*****************************************************************************
 * Function      : CanDevice.CanrecvStart
 * Description   : 开启Can 设备读取
 * Input          : None
 * Output        : None
 * Return        : CAN_API
 * Others        : 
 * Record
 * 1.Date        : 20180914
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CAN_API  CanDevice :: CanrecvStart()
{
   int        iRet;
   pthread_t  Canthreadt;

   iRet =  pthread_create(&Canthreadt,NULL,CanRecvThread,this);
   if(iRet < 0)
   {
      return  CAN_ERROR;
   }
   
   return     CAN_SUCCESS;
}
/*****************************************************************************
 * Function      : CanDevice.CanSendThread
 * Description   : Can发送线程
 * Input         : void *arg  
 * Output        : None
 * Return        : void
 * Others        : 
 * Record
 * 1.Date        : 20180914
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
void * CanDevice :: CanSendThread(void *arg)
{
   	

}


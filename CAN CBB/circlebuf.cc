#include <string.h>
#include <stdio.h>
#include "circlebuffer.h"
/*****************************************************************************
 * Function      : CircleQue.GetCircleQueLen
 * Description   : 构造函数初始化环形缓冲区的状态
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180910
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CircleQue :: CircleQue()
{
    front   =  0;
    tail    =  0;
    check   =  0;
    total   =  CIRCLE_BUFFER_SIZE;
    memset(buffer,0X00,CIRCLE_BUFFER_SIZE);
}
/*****************************************************************************
 * Function      : CircleQue.~CircleQue
 * Description   : 析构函数
 * Input          : None
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180910
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
CircleQue :: ~CircleQue()
{

}
/*****************************************************************************
 * Function      : CircleQue.GetCircleQueLen
 * Description   : 获得当前的环形缓冲区的长度
 * Input          : None
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180910
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CircleQue :: GetCircleQueLen()
{
    return (tail+total-front)%total;
}
/*****************************************************************************
 * Function      : CircleQue.CircleQueLeft
 * Description   : 获得缓冲区剩余大小
 * Input          : None
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CircleQue ::  CircleQueLeft ()
{
   return  (total - GetCircleQueLen());
}
/*****************************************************************************
 * Function      : CircleQue.CircleQueIsFull
 * Description   : 环形缓冲区是否满
 * Input          : None
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180910
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CircleQue :: CircleQueIsFull()
{
   return  ((tail + 1) % total)  == front ? CIRCLE_TRUE : CIRCLE_FALSE;
}
/*****************************************************************************
 * Function      : CircleQue.CircleQueIsEmpty
 * Description   : 环形缓冲区是否空
 * Input          : None
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180910
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CircleQue ::CircleQueIsEmpty()
{
   return  (tail == front) ? CIRCLE_TRUE : CIRCLE_FALSE;
}
/*****************************************************************************
 * Function      : CircleQue.CircleCheckFront
 * Description   : 设置同步检测位置
 * Input         : None
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CircleQue :: CircleCheckFront ()
{
    front = check;
}
/*****************************************************************************
 * Function      : CircleQue.CircleFrontCheck
 * Description   : 同步检测位置
 * Input          : None
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CircleQue :: CircleFrontCheck()
{
    check = front;
}
/*****************************************************************************
 * Function      : CircleQue.CircleShiftCheck
 * Description   : 平移检测数据包位置
 * Input          : None
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CircleQue ::  CircleShiftCheck()
{
    check =  (check+1)%total;
}
/*****************************************************************************
 * Function      : CircleQue.CircleQuePush
 * Description   : 放入缓冲区数据
 * Input          : None
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180910
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CircleQue :: CircleQuePush   (unsigned  char *data)
{
   if (CircleQueIsFull())
        return   CIRCLE_FALSE;
        
    else
    {
        buffer[tail] = *data;
        tail         = (tail+1)%total;
    }
    return   CIRCLE_TRUE;
}
/*****************************************************************************
 * Function      : CircleQue.CircleQuePop
 * Description   : 读取环形缓冲区数据
 * Input          : None
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180910
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CircleQue ::CircleQuePop     (unsigned  char  *data)
{
    if (CircleQueIsEmpty ())
       return  CIRCLE_FALSE;
        
    else
    {
        *data    =  buffer[front];
         front= (front + 1)%total;
    }
    return     CIRCLE_TRUE;
}
/*****************************************************************************
 * Function      : CircleQue.CircleQueCheck
 * Description   : 
 * Input         : char *data  
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int CircleQue :: CircleQueCheck  (unsigned  char *data)
{
    if (CircleQueIsEmpty ())
       return  CIRCLE_FALSE;
        
    else
    {
        *data    =  buffer[check];
         check= (check + 1)%total;
    }
}
/*****************************************************************************
 * Function      : CircleQue.QuenePoP
 * Description   : 读取缓冲区中的指定的数据
 * Input         : char * data  
                int len      
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CircleQue :: QuenePoP(unsigned  char * data, int len)
{
    if(len > GetCircleQueLen())
    {
       return CIRCLE_FALSE;
    }
    
    for(int  inum = 0;inum  < len;inum++)
    {
        CircleQuePop(data++);
    }
    
    return  CIRCLE_TRUE;
}
/*****************************************************************************
 * Function      : CircleQue.QuenePush
 * Description   : 放置缓冲区指定长的数据
 * Input         : char * data  
                int len      
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int  CircleQue :: QuenePush(unsigned  char * data, int len)
{
    if(len > CircleQueLeft())
    {
       return CIRCLE_FALSE;
    }
    
    for(int  inum = 0;inum  < len;inum++)
    {
        CircleQuePush(data++);
    }
    
    return  CIRCLE_TRUE;
}
/*****************************************************************************
 * Function      : CircleQue.QueCheck
 * Description   : 检测固定长度的数据
 * Input         : char *data  
                int len     
 * Output        : None
 * Return        : int
 * Others        : 
 * Record
 * 1.Date        : 20180911
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
int   CircleQue :: QueCheck (unsigned  char *data,int len)
{
   for(int  inum  = 0;inum < len; inum++)
   {
       CircleQueCheck(data);
   }
   return  CIRCLE_TRUE;
}




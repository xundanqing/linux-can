/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : list.cc
 * Author        : xundanqing
 * Date          : 2018-09-14
 * Description   : .C file function description
 * Version       : 1.0
 * Function List :
 * 
 * Record        :
 * 1.Date        : 2018-09-14
 *   Author      : xundanqing
 *   Modification: Created file

*************************************************************************************************************/
#include"list.h"
/*****************************************************************************
 * Function      : list_add
 * Description   : 插入队列
 * Input         : SysListHead *pstNew   
                SysListHead *pstPrev  
                SysListHead *pstNext  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180702
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
void list_add(SysListHead *pstNew, SysListHead *pstPrev, SysListHead *pstNext)
{
	pstNext->pstPrev = pstNew;
	pstNew->pstNext = pstNext;
	pstNew->pstPrev = pstPrev;
	pstPrev->pstNext = pstNew;
}
/*****************************************************************************
 * Function      : list_del
 * Description   : 删除队列
 * Input         : SysListHead *pstPrev  
                SysListHead *pstNext  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180702
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
void list_del(SysListHead *pstPrev, SysListHead *pstNext)
{
	pstNext->pstPrev = pstPrev;
	pstPrev->pstNext = pstNext;
}
/*****************************************************************************
 * Function      : SYS_ListAdd_Head
 * Description   : 添加到队列头
 * Input         : SysListHead *pstPrev  
                SysListHead *pstNext  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180702
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
void  SYS_ListAdd_Head(SysListHead *pstPrev, SysListHead *pstHead)
{
	list_add(pstPrev,pstHead,pstHead->pstNext);
}
/*****************************************************************************
 * Function      : SYS_ListAdd_Tail
 * Description   : 添加到队列尾
 * Input         : SysListHead *pstPrev  
                SysListHead *pstNext  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180702
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
void  SYS_ListAdd_Tail(SysListHead *pstNew, SysListHead *pstHead)
{
   	list_add(pstNew, pstHead->pstPrev, pstHead);
}
/*****************************************************************************
 * Function      : SYS_ListDel
 * Description   : 删除链表结构
 * Input         : SysListHead *pstEntry  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180703
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
void   SYS_ListDel(SysListHead *pstEntry)
{ 
	list_del(pstEntry->pstPrev, pstEntry->pstNext);
}
/*****************************************************************************
 * Function      : SYS_List_Replace
 * Description   : 添加到队列尾
 * Input         : SysListHead *pstOld   
                SysListHead  *pstNew  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180702
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
void  SYS_List_Replace(SysListHead *pstOld, SysListHead  *pstNew)
{
	pstNew->pstNext = pstOld->pstNext;
	pstNew->pstNext->pstPrev = pstNew;
	pstNew->pstPrev = pstOld->pstPrev;
	pstNew->pstPrev->pstNext = pstNew;
}
/*****************************************************************************
 * Function      : SYS_ListEmpty
 * Description   : 对列空判断
 * Input         : const SysListHead *pstHead  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180707
 *   Author      : xundanqing
 *   Modification: Created function

*****************************************************************************/
BOOL SYS_ListEmpty(const SysListHead *pstHead)
{
	BOOL bRet = SYS_FALSE;

    if (pstHead->pstNext == pstHead)
    {
    	bRet = SYS_TRUE;
    }

    return bRet;
}



/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : list.h
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
#ifndef  _TM_SYS_LIST_H
#define  _TM_SYS_LIST_H

#ifndef  SYS_TRUE
#define  SYS_TRUE   (1)
#endif

#ifndef  SYS_FALSE
#define  SYS_FALSE  (0)
#endif   

#ifndef  BOOL
#define  BOOL       int 
#endif

/*队列结构体*/
typedef struct SysListHead_st
{
	struct  SysListHead_st *pstNext ,  *pstPrev;
	
}SysListHead;
/**
 * 初始化List头结点
 * @name:   SysListHead类型变量名
 */
#define SYS_LIST_HEAD_INIT(name)    name.pstNext = &name; name.pstPrev = &name
/**
 * 定义List，并初始化头结点
 * @name:   SysListHead类型变量名
 *
 */
#define SYS_LIST_HEAD(name) 	  SysListHead name = { &(name), &(name) }
/**
 * 取出list中的元素中在结构体的偏移
 * @name:   SysListHead类型变量名
 */
#define sys_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
/**
 * 获取SysListHead嵌入的结构体结点地址
 * @ptr:    指向SysListHead类型成员指针
 * @type:  	SysListHead类型成员嵌入的结构体类型
 * @member: SysListHead类型成员名
 */
#define SYS_LIST_ENTRY(ptr, type, member)    ({          \
			 const typeof(((type *)0)->member)*mptr = (ptr);    \
		    (type *)((int8 *)mptr - sys_offsetof(type, member)); })
/**
 * 遍历List
 * @pos:   遍历用的游标
 * @head:  List头结点
 */
#define SYS_LIST_FOR_EACH(pos, head) \
			for (pos = (head)->pstNext; pos != (head); pos = pos->pstNext)
/**
 * 遍历List中的所有节点及元素
 * @pos:   遍历用的游标
 * @head:  List头结点
 */
#define SYS_LIST_FOR_EACH_ENTRY(pos, head, member)	\
			for (pos = SYS_LIST_ENTRY ((head)->pstNext,typeof(*pos), member);	\
	     	&pos->member != (head); 	\
	     	pos = SYS_LIST_ENTRY (pos->member.pstNext, typeof(*pos), member))

#endif


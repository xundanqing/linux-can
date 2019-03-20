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

/*���нṹ��*/
typedef struct SysListHead_st
{
	struct  SysListHead_st *pstNext ,  *pstPrev;
	
}SysListHead;
/**
 * ��ʼ��Listͷ���
 * @name:   SysListHead���ͱ�����
 */
#define SYS_LIST_HEAD_INIT(name)    name.pstNext = &name; name.pstPrev = &name
/**
 * ����List������ʼ��ͷ���
 * @name:   SysListHead���ͱ�����
 *
 */
#define SYS_LIST_HEAD(name) 	  SysListHead name = { &(name), &(name) }
/**
 * ȡ��list�е�Ԫ�����ڽṹ���ƫ��
 * @name:   SysListHead���ͱ�����
 */
#define sys_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
/**
 * ��ȡSysListHeadǶ��Ľṹ�����ַ
 * @ptr:    ָ��SysListHead���ͳ�Աָ��
 * @type:  	SysListHead���ͳ�ԱǶ��Ľṹ������
 * @member: SysListHead���ͳ�Ա��
 */
#define SYS_LIST_ENTRY(ptr, type, member)    ({          \
			 const typeof(((type *)0)->member)*mptr = (ptr);    \
		    (type *)((int8 *)mptr - sys_offsetof(type, member)); })
/**
 * ����List
 * @pos:   �����õ��α�
 * @head:  Listͷ���
 */
#define SYS_LIST_FOR_EACH(pos, head) \
			for (pos = (head)->pstNext; pos != (head); pos = pos->pstNext)
/**
 * ����List�е����нڵ㼰Ԫ��
 * @pos:   �����õ��α�
 * @head:  Listͷ���
 */
#define SYS_LIST_FOR_EACH_ENTRY(pos, head, member)	\
			for (pos = SYS_LIST_ENTRY ((head)->pstNext,typeof(*pos), member);	\
	     	&pos->member != (head); 	\
	     	pos = SYS_LIST_ENTRY (pos->member.pstNext, typeof(*pos), member))

#endif


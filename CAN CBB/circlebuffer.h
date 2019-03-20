/********************************************************************************

 **** Copyright (C), 2018, xx xx xx xx info&tech Co., Ltd.                ****

 ********************************************************************************
 * File Name     : tm_circle_buffer.h
 * Author        : xundanqing
 * Date          : 2018-06-06
 * Description   : .C file function description
 * Version       : 1.0
 * Function List :
 * 
 * Record        :
 * 1.Date        : 2018-06-06
 *   Author      : xundanqing
 *   Modification: Created file

************************************************************************************************************/
#ifndef   _CIRCLE_H_
#define   _CIRCLE_H_

#define   CIRCLE_FALSE       (0 )
#define   CIRCLE_TRUE        (1 )
#define   CIRCLE_BUFFER_SIZE (4096)

class CircleQue
{
  public :
    CircleQue ();
    ~CircleQue();
    int   GetCircleQueLen ();
    int   CircleQueLeft   ();
    int   CircleQueIsFull ();
    int   CircleQueIsEmpty();
    int   CircleShiftCheck();
    int   CircleFrontCheck();
    int   CircleCheckFront();
    int   CircleQuePush   (unsigned  char *data);
    int   CircleQuePop    (unsigned  char *data);
    int   CircleQueCheck  (unsigned  char *data);

  public  :
    int   QuenePush(unsigned  char *data,int len);
    int   QuenePoP (unsigned  char *data,int len);
    int   QueCheck (unsigned  char *data,int len);
    
  private :
    int   front;    
    int   tail;     
    int   check; 
    int   total;
    char  buffer[CIRCLE_BUFFER_SIZE];  
};

#endif


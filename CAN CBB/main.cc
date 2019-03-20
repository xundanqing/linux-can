#include<stdio.h>
#include<string>
#include"cantype.h"
#include"can.h"
#include"candecoler.h"
#include"canclient.h"

/*测试Can 投币机数据处理*/
int  CanCoinProc(unsigned  char *buf,int  len)
{
   printf("Car  Proc ...\n");
   printf("Car  len %d\n",len);
   for(int  i=0 ; i < len; i++)
   {
       printf("%02X",buf[i]);
   }
   printf("\n");
}

/*测试Can  车载机 数据处理*/
int  CancarProc(unsigned  char *buf,int  len)
{
   printf("Car  Proc ...\n");
   printf("Car  len %d\n",len);

   for(int  i=0 ; i < len; i++)
   {
       printf("%02X",buf[i]);
   }
   printf("\n");
}


class   stu
{
 public  :
    stu()
    {

    }
    
    ~stu()
    {

    }
    
    int  set(int  idnum) 
    {
      id = idnum;
    }

    int dis()const  
    {
       printf("age :%d\n",id);
    }

    int dis()
    {
       id  =  0;
       printf("ccccc\n");
    }
 
 private :
    int  age;
    int  id;

};



int  main()
{

   CanDevice  Candev("can0");
   
   /*1.添加投币机Can 客户端*/
   CanClient*   coincanClient  = new CanClient("Coinbox");
   CanFilter    coincanfilter  = {(0xAAA10000>>3),(0XFFFF0000>>3)};
   coincanClient->SetCanfilter(coincanfilter);
   coincanClient->RegCanAction(CanCoinProc  );
   Candev.CanAddClient(coincanClient);

   /*2.添加车载机Can 客户端*/
   CanClient*   CarcanClient  = new CanClient("car");
   CanFilter    Carcanfilter  = {(0XC9A10000>>3 ),(0XFFFF0000>>3 )};
   CarcanClient->SetCanfilter(Carcanfilter);
   CarcanClient->RegCanAction(CancarProc  );
   Candev.CanAddClient(CarcanClient);

   /*3.打开CAN,设置CAN 规则*/
   Candev.CanInit();
   Candev.CanSetFilter();
   Candev.CanrecvStart();


 
   const  stu  stu1;
   stu1.dis();

   /** 
    1.const 修饰数据成员，初始化位置可以在参数列表中进行初始化，
      新版本也可以在声明的位置进行初始化


    2.const 修饰的成员函数，const的位置分为.h 和.cpp  中。都要进行
      初始化const 修饰，const 函数能与非const 函数进行重载


    3.const 修饰的对象，只能访问const 修饰的函数
      const 修饰的函数，只能访问const 函数
   **/
   
   return  0;
   
   while(1)
   {
       sleep(1);
       
   }
   
}

#include<stdio.h>
#include<string>
#include"cantype.h"
#include"can.h"
#include"candecoler.h"
#include"canclient.h"

/*����Can Ͷ�һ����ݴ���*/
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

/*����Can  ���ػ� ���ݴ���*/
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
   
   /*1.���Ͷ�һ�Can �ͻ���*/
   CanClient*   coincanClient  = new CanClient("Coinbox");
   CanFilter    coincanfilter  = {(0xAAA10000>>3),(0XFFFF0000>>3)};
   coincanClient->SetCanfilter(coincanfilter);
   coincanClient->RegCanAction(CanCoinProc  );
   Candev.CanAddClient(coincanClient);

   /*2.��ӳ��ػ�Can �ͻ���*/
   CanClient*   CarcanClient  = new CanClient("car");
   CanFilter    Carcanfilter  = {(0XC9A10000>>3 ),(0XFFFF0000>>3 )};
   CarcanClient->SetCanfilter(Carcanfilter);
   CarcanClient->RegCanAction(CancarProc  );
   Candev.CanAddClient(CarcanClient);

   /*3.��CAN,����CAN ����*/
   Candev.CanInit();
   Candev.CanSetFilter();
   Candev.CanrecvStart();


 
   const  stu  stu1;
   stu1.dis();

   /** 
    1.const �������ݳ�Ա����ʼ��λ�ÿ����ڲ����б��н��г�ʼ����
      �°汾Ҳ������������λ�ý��г�ʼ��


    2.const ���εĳ�Ա������const��λ�÷�Ϊ.h ��.cpp  �С���Ҫ����
      ��ʼ��const ���Σ�const ���������const ������������


    3.const ���εĶ���ֻ�ܷ���const ���εĺ���
      const ���εĺ�����ֻ�ܷ���const ����
   **/
   
   return  0;
   
   while(1)
   {
       sleep(1);
       
   }
   
}

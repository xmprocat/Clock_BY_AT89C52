#include "reg52.h"	 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include "stdlib.h"
void delay(unsigned int n);//��������
void display(long int number);
void control();
unsigned char segs[13] = {0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0x02,0x00,0xde,}; //λѡ0,1,2,3,4,5,6,7,8,9,kong,-,e
unsigned char tongd[7] = {0xff,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,};//��ѡ
long int m,i,z,k=0,amount=0;
long int temp=0;
long int g,u=0;



void main()//������
{
    m=999;//���99������������ֻҪ����0~9֮���������
    g=0;//���Ǹ�����������ֵ�������������������������ʾ0
    while(1)
    {
        control();//�����̵��������
        if(m!=999)//������������������룬��ôm�ͱ�Ȼ��0~9֮���һ����,ִ�к�����
        {
            g = 10*g + m;
            m = 999;//һ��Ҫ�������mֵ����Ϊ�����ϵļ�ֵ�Ѿ�������g�����������mֵ���ͻ�������if���ÿ�ζ��ᱻִ�У�����������û�а��¼���
        }
        if(k==31||k==32||k==33||k==34)//������ı�־λ
        {
            u = k;//��kֵ������һ��������Ȼ���k���㣬��������㣬���if���Ҳ��ÿ�ζ���ִ�еģ�����������û�а��¼���
            temp = g;//������������ǰѸղŵ������������

            g=0;//���gҲҪ����ģ�����ǲ�����Ҫ�μ�����ĵ�2�����ģ�
            k=0;//������˵����������
        }
        if(amount==30)//������ǵ�������
        {
            switch(u)
            {
            case 31:
                g=temp + g;
                break;//���
            case 32:
                g=temp-g;
                break;//���
            case 33:
                g=temp*g;
                break;//���
            case 34:
                g=temp/g;
                break;//����
            /*case 35:
                g=pow(temp,g);
                break;//��n�η�
            case 36:
                g=log10(temp)/log10(g);
                break;//��n�η�
                case 37:g=temp*g;break;
                case 38:g=temp/g;break;*/
            }
            u=0;
            amount=0;//���������������
        }
        display(g);//��ʾ�����
        if(z==40)
            break;//�����ˣ���������Ѽ�������λ
    }
}

				
	
void control() {//����ɨ���ȡ����,�Ҽ��̽���P3��
    unsigned char tablelie[]= {0x7f,0xbf,0xdf,0xef};//4*4������̣���P3�ڣ���4λ�������͵�ƽ�����ݵ�4λ�ĵ�ƽ�仯ȷ�����µ����ĸ�����
    for(i=0; i<4; i++) //���ѭ���Ǹ�P3���ϵļ��̵ĸ�4λ�������͵�ƽ��
    {

        P0= tablelie[i];
        if ((P0 & tablelie[i])!= tablelie[i]) //�����Ǽ���Ƿ��м��̱����£�
        {


            delay(10);

            if((P0 & tablelie[i]) != tablelie[i]) //���ﾭ��10����ʱ�󣬿�������Ƿ��ڱ����µ�״̬���������ν�����������
            {
                switch (P0)//��ȡ���µ��ַ�
                {
                case 0xb7://���ǰ���ʱ�ĵ�ƽ���,�ɸ���Proteusģ��ó�
                    m=1;
                    break;
                case 0xbb:
                    m=2;
                    break;
                case 0xbd:
                    m=3;
                    break;
                case 0x7e:
                    k=31;
                    break;//���ǡ��ӡ��ı�־λ��
                case 0xd7:
                    m=4;
                    break;
                case 0xdb:
                    m=5;
                    break;
                case 0xdd:
                    m=6;
                    break;
                case 0xbe:
                    k=32;
                    break;//���ǡ������ı�־λ��
                case 0xe7:
                    m=7;
                    break;
                case 0xeb:
                    m=8;
                    break;
                case 0xed:
                    m=9;
                    break;
                case 0xde:
                    k=33;
                    break;//���ǡ��ˡ��ı�־λ;
                case 0x77:
                    z=40;
                    break;//���ǡ����������㡱�ı�־λ��
                case 0x7b:
                    m=0;
                    break;
                case 0x7d:
                    amount=30;
                    break;//���ǡ����ڡ��ı�־λ��
                case 0xee:
                    k=34;
                    break;//���ǡ������ı�־λ��
                }
            }
            while((P0 & tablelie[i]) != tablelie[i]);//��˵�е����ּ�⣬����Ҫ��
        }
    }

}


 

  


void display(long int number) { //��ʾ������������ʾ���������������
	int fu = 0;
	int cdu,se;
	long int temp;
	if(number > 999999 || number < -99999 ) { //�������ֵĺ������ж�
	   for(se = 6;se > 0;se--) { //������
			P2 = tongd[se];
			P1 = segs[10]; 				
			delay(1);	
			//P1 = segs[11];
			//P2 = tongd[0];
			delay(1);
	  	}
	
	} else if(number <= 999999 && number >= -99999) { //��ȡ���ֵĳ��ȣ���ʱ�벻�����õ��㷨
		
		temp = labs(number);
		
		if(number <= 9 && number >= 0) {cdu=1;}//����д�Ƿ�ֹ�����м���0
		else if (number <= 99 && number >= 10) {cdu=2;}	
		else if (number <= 999 && number >= 100) {cdu=3;}
		else if (number <= 9999 && number >= 1000) {cdu=4;}
		else if (number <= 99999 && number >= 10000) {cdu=5;}
		else if (number <= 999999 && number >= 100000) {cdu=6;}

		else if (number < 0 && number > -10) {cdu=1;P2 = 0xfe;P1 = 0x02;}
		else if (number <= -10 && number >= -99) {cdu=2;P2 = 0xfe;P1 = 0x02;}	
		else if (number <= -100 && number >= -999) {cdu=3;P2 = 0xfe;P1 = 0x02;}
		else if (number <= -1000 && number >= -9999) {cdu=4;P2 = 0xfe;P1 = 0x02;}
		else if (number <= -10000 && number >= -99999) {cdu=5;P2 = 0xfe;P1 = 0x02;}
		
		for(se = 6;se > 6 - cdu;se--) {//ˢ����ʾ�����seΪ��ǰˢ��
				if(number < 0) {
				P2 = 0xfe;P1 = 0x02;
					
						
					delay(1);//��ʱ
			
					//P1 = segs[11];//���λѡ
					//P2 = tongd[0];//��ն�ѡ��ֹ��Ӱ
				
				 }
				 delay(1);//��ʱ
		
				P1 = segs[11];//���
				P2 = tongd[0];//��շ�ֹ��Ӱ
				delay(1);
				P2 = tongd[se];//λѡ
				P1 = segs[temp%10];//��ѡ
				temp/=10;//ÿ�ζ�ѡȡ�����һλ��Ȼ���10�������һλ
					
				
			
			
	  	}
		}
    
}
void delay(unsigned int n) { //һ���򵥵���ʱ����
  unsigned int i,j;
  for(j=0;i<n;i++) {
  	for(j=0;j<123;j++){}
  }
}
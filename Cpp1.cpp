#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<Windows.h>
#include<time.h>                                                                                                                                                                                                                                                                                                                                                                                                                                                                

//*****��������*****
char s[10];           //ʢ����ʾ�÷ֵ��ַ���
char s2[10];
int a[4][4] = { 0 };  //ʢ��4*4���ֵĶ�ά����
int loss=0;           //�ж���Ϸ�Ƿ������Ϊ1ʱ��Ϸ������
int emtpy;            //�ո������
int score;            //��ǰ�÷�
int scoremax;         //��ʷ��߷�
char name[20]; //����һ��ָ����������ܷ��صĵ�ַ
char namemax[100];


//*******����*******

void init()       //����ʼ��������
{
    int x, y;
    srand(time(0));
    x = rand() % 4;
    y = rand() % 4;
    a[x][y] = 2;
    emtpy = 15;
}

void music()      //���������ֺ�����
{
	srand((unsigned int)time(NULL));										     	// ��ʼ���ڴ�С
	mciSendString("open 2048\\�������������.mp3 alias mymusic", NULL, 0, NULL);	// ������
	mciSendString("play mymusic", NULL, 0, NULL);                                   //��������
}

char *getString(char b[] )  //�����д�
{       
	gets(b); //��������gets(a);       
    return b;      
}

void Login()      //����¼������
{ 
	char s[]	= "��ʼ��Ϸ";
	char ss[]	= "�˳���Ϸ";
    
	MOUSEMSG m;                    //�洢������
	setfont(50,25,"");             //�����ַ���ʽ��С
	outtextxy(530, 550, s);        //��ʾ�ַ�"��ʼ��Ϸ"
	outtextxy(530, 615, ss);       //��ʾ�ַ�"�˳���Ϸ"

    while(1)
	{
		m = GetMouseMsg();                             //��������Ϣ	
		if(m.uMsg==WM_LBUTTONDOWN )                    // �ж��Ƿ������
	    	if(m.x >= 530 && m.x <= 735 && m.y >= 550 && m.y <= 610)//�ж�����Ƿ�������Ϊ"��ʼ��Ϸ"����
			{
                    
					//char temp[20];
                  	inputbox_getline("�����������","���������Ĵ���",name,20);


				   /*PIMAGE imgmain=newimage(250,250);
                	getimage(imgmain,"2048/main.png",0,0);
                	putimage(0,0,250,250,imgmain,0,0);
		                //*/	
					break;
					
			}
	        else if(m.x >= 530 && m.x <= 735 && m.y >=615 && m.y <= 655)//�ж���갴�������Ƿ���"�˳���Ϸ����"
			{
		      	if(m.uMsg==WM_LBUTTONDOWN)
				{
			    	exit(1);
				}
			}
		
	}
}

void draw()      //����ͼ������
{
    int i, j;                  //����ˢ�³�ÿ���Ӧ��ͼƬ
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            PIMAGE img;             //�洢ͼƬ
            img = newimage();             
            switch (a[i][j])  
            {
            case 0:
            {
                getimage(img, "2048\\0.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            case 2:
            {
                getimage(img, "2048\\2.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            case 4:
            {
                getimage(img, "2048\\4.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            case 8:
            {
                getimage(img, "2048\\8.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            case 16:
            {
                getimage(img, "2048\\16.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            case 32:
            {
                getimage(img, "2048\\32.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            case 64:
            {
                getimage(img, "2048\\64.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            case 128:
            {
                getimage(img, "2048\\128.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            case 256:
            {
                getimage(img, "2048\\256.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            case 512:
            {
                getimage(img, "2048\\512.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            case 1024:
            {
                getimage(img, "2048\\1024.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            case 2048:
            {
                getimage(img, "2048\\2048.png");
                putimage(j * 184+4, i * 184+34, img);
                break;
            }
            }
        }
    }
}

void duqu ()  //����ȡ������߷ֺ�����
{
	FILE *fp1, *fp2;   
    int a[1];
    fp1=fopen("a.dat","rb");        //�Զ��ķ�ʽ���ĵ�
	fread(a,sizeof(int),1,fp1);     //�����ַ�����ֵ���ַ���a
	scoremax=a[0];                 //�ַ���ת��������

	fp2=fopen("name.txt","rb+");
    fread(namemax,sizeof(int),2,fp2);
	fclose(fp2);
}

//**************��Ϸ�����к���********************
int _up()             //�����ϼ�������
{
    int x, y, i;
    int sum=0;              //����ÿ�ε÷�
    for (y = 0; y < 4; ++y) // �������ºϲ���ͬ�ķ���
	{      
        for (x = 0; x < 4; ++x) 
		{
            if (a[x][y] == 0);
            else
			{
                for (i = x + 1; i < 4; ++i) 
				{
                    if (a[i][y] == 0);
                    else if (a[x][y] == a[i][y]) //��ȵĺϲ�
					{
                        a[x][y] += a[i][y];
						sum += a[x][y];
                        a[i][y] = 0;
                        ++emtpy;
                        x = i;
                        break;
                    }
                    else
					{
                      break;
                    }
                }
            }
        }
    }
    for (y = 0; y < 4; ++y)    // �����ƶ�����
	{
		for (x = 0; x < 4; ++x)
        {
            if (a[x][y] == 0);
            else 
			{
                for (i = x; (i > 0) && (a[i - 1][y] == 0); --i) 
				{
                    a[i - 1][y] = a[i][y];
                    a[i][y] = 0;
                }
            }
        }
	}
	return sum;
}

int _down()       //�����¼�������
{
    int x, y, i;
    int sum=0;    //����ÿ�ε÷�
    for (y = 0; y < 4; ++y)  // ���ºϲ���ͬ�ķ��� 
        for (x = 3; x >= 0; --x)
		{
            if (a[x][y] == 0);
            else
			{
                for (i = x - 1; i >= 0; --i)
				{
                    if (a[i][y] == 0)
                        ;
                    else if (a[x][y] == a[i][y]) 
					{
                        a[x][y] += a[i][y];
						sum += a[x][y];
                        a[i][y] = 0;
                        ++emtpy;
                        x = i;
                        break;
                    }
                    else
                        break;
                }
            }
        }
    for (y = 0; y < 4; ++y)  // �����ƶ����� 
	{
		for (x = 3; x >= 0; --x) 
		{
            if (a[x][y] == 0);
            else {
                for (i = x; (i < 3) && (a[i + 1][y] == 0); ++i) {
                    a[i + 1][y] = a[i][y];
                    a[i][y] = 0;
                }
            }
        }
	}
	return sum;
}
int _left()      //�������������
{
    int x, y, i;
    int sum=0;                //����ÿ�ε÷�
    for (x = 0; x < 4; ++x)   // ����ϲ���ͬ�ķ��� 
        for (y = 0; y < 4; ++y)
		{
            if (a[x][y] == 0);
            else 
			{
                for (i = y + 1; i < 4; ++i)
				{
                    if (a[x][i] == 0);
                    else if (a[x][y] == a[x][i]) 
					{
                        a[x][y] += a[x][i];
						sum += a[x][y];
                        a[x][i] = 0;
                        emtpy++;
                        y = i;
                        break;
                    }
                    else
                        break;
                }
            }
        }
    for (x = 0; x < 4; ++x)  // �����ƶ����� 
	{
		for (y = 0; y < 4; ++y)
		{
            if (a[x][y] == 0);
            else 
			{
                for (i = y; (i > 0) && (a[x][i - 1] == 0); --i) 
				{
                    a[x][i - 1] = a[x][i];
                    a[x][i] = 0;
                }
            }
        }
	}
	return sum;
}
int _right()     //�����Ҽ�������
 {
    int x, y, i;
    int sum=0;               //����ÿ�ε÷�
    for (x = 0; x < 4; ++x)  // ���Һϲ���ͬ�ķ��� 
        for (y = 3; y >= 0; --y) 
		{
            if (a[x][y] == 0);
            else
			{
                for (i = y - 1; i >= 0; --i)
				{
                    if (a[x][i] == 0) ;
                    else if (a[x][y] == a[x][i]) 
					{
                        a[x][y] += a[x][i];
						sum += a[x][y];
                        a[x][i] = 0;
                        ++emtpy;
                        y = i;
                        break;
                    }
                    else
                        break;
                }
            }
        }
    for (x = 0; x < 4; ++x)     // �����ƶ����� 
	{
		for (y = 3; y >= 0; --y) 
		{
            if (a[x][y] == 0);
            else 
			{
                for (i = y; (i < 3) && (a[x][i + 1] == 0); ++i)
				{
                    a[x][i + 1] = a[x][i];
                    a[x][i] = 0;
                }
            }
        }
	}
	return sum;
}

int _Esc()    //����;�˳�������
{
    initgraph(740,760);      //��ʼ������
    PIMAGE imu;              //����ͼ��
    imu = newimage();
    getimage(imu, "2048/����.jpg");
    putimage(0, 20, imu);

    char e[20] = "�˳���Ϸ";
    char j[20] = "���ĵ÷�:";
	char l[20] = "�û���:";

    setfont(50,25,"");
	
	outtextxy( 230,145, l);
	outtextxy( 400,145, name);
    outtextxy( 230,205, j);  //��ʾ�ַ�"���ĵ÷�"
    sprintf(s,"%d",score);//��ʾ�÷�
    outtextxy(450,205,s); 
	outtextxy(230,265,"��ʷ��߷�:");    
    sprintf(s2,"%d",scoremax);        //��������߷�ת��Ϊ�ַ�������ʾ
    outtextxy(505,265,s2);
//	outtextxy(230,520, e);  //��ʾ�ַ�"�˳���Ϸ"
outtextrect( 230, 520, 555, 580, e);  //��ʾ�ַ�"�˳���Ϸ"
	

    MOUSEMSG m;                           //�ж����������Ƿ��˳���Ϸ��
	while(m.uMsg)
	{
		m=GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:
			 if(m.x>230&&m.x<555&&m.y>520&&m.y<580)
			 {
			 closegraph();
			 }
		}
	}
	return 0;
}

void add_number()   //������������鲢�ж��Ƿ�ʧ�ܺ�����
{
    srand(time(0)); 
    if (emtpy > 0)  //�п�λ�������2��4
    {
        int x, y, temp;
        do
        {
            x = rand() % 4;
            y = rand() % 4;
        } while (a[x][y] != 0);
        temp = rand();
        int i = temp % 2;
        if (i == 1)
        {
            a[x][y] = 2;
            emtpy--;
        }
        else
        {
            a[x][y] = 4;
            emtpy--;
        }
    }
	else             //û��λ�ж��Ƿ���Ϸ����
	{   
		loss=1;
		for (int i = 0; i < 3; i++)
		{  
          for (int j = 0; j < 3; j++)
		  {  
            if (a[i][j] == a[i][j + 1] ||a[i][j] == a[i + 1][j])
			{
			 loss=0;
			}
		  }
		}
	}
}

int play()     //����Ϸ���к�����
{
    int k=0;    //���������Ҳ����÷ֽ������
	char c = getch();
    switch (c)
    {
    case 'w':
    case'W':
    {
        k=_up();
        add_number();
        draw();
        break;
    }

    case 's':
    case'S':
    {
        k=_down();
        add_number();
        draw();
        break;
    }

    case 'a':
    case'A':
    {
        k=_left();
        add_number();
        draw();
        break;
    }

	case 'd':
    case'D':
    {
        k=_right();
        add_number();
        draw();
        break;
    }

	case VK_ESCAPE:    // ��;�˳���Ϸ
    {
        k=_Esc();
        add_number();
        draw();
        break;
    }
    }
return k;
}

//********��Ϸ��������*************
void zuigaofen()    //���ж��Ƿ������߷֡�
{   
	FILE *fp1, *fp2;   
    int a[1];
	if (scoremax<score)            //�ж�
	{
		a[0]=score;                //������ֵ����߷��ַ���a
        fp1=fopen("a.dat","wb");    //д�ķ�ʽ���ļ�
        fwrite(a,sizeof(int),1,fp1);//д��
		fclose(fp1); 

		fp2=fopen("name.txt","rb+");    //д�ķ�ʽ���ļ�
        fwrite(name,sizeof(int),2,fp2);//д��

	}
          
}

int  main()         //����������
{
    init();                           //�����ʼ���������ر�ͼ�ν���
	char s2[10];                      //��߷��ַ���
    initgraph(740, 770);              //��ʼ��

    PIMAGE img;                       //�˵�ͼƬ��ʾ��������������
    img = newimage();
    getimage(img, "2048/�˵�.jpg");
    putimage(0, 0, img);
    music();                          //����

    Login();                          //��¼

    

    initgraph(740, 770);              //��ʼ����Ϸ����
    PIMAGE imp;
    imp = newimage();
    getimage(img, "2048/����.jpg");
    putimage(0, 30, imp);             //��ʼ����Ϸ����ͼ
    draw();                           //ˢ��ͼƬ

	

	duqu ();                 //��ȡ��߷�
    for (; is_run(); delay_fps(30))
    {
        score+=play();                    //�����ۼ�
        sprintf(s,"%d",score);            //ʵʱ��ʾ����
		setfont(29,19,""); 
		outtextxy(20,0,"�÷֣�");         //��ʾ�ַ���"�÷�"
	    outtextxy(120,0,s);               //��ʾ�ַ���"����"
        outtextxy(500,0,namemax);
		
		outtextxy(350,0,"��߷�:");    
        sprintf(s2,"%d",scoremax);        //��������߷�ת��Ϊ�ַ�������ʾ
        outtextxy(650,0,s2);              //��ʾ�ַ���߷�
		if (loss==1)                                 //ʧ���ж�
		{
	      	getimage(img, "2048\\Game over.jpg");
            putimage(175, 175, img);
            outtextxy(182,490,"�û�����");
		    outtextxy(330,490, name);
			outtextxy(182,520,"���ε÷֣�");
			outtextxy(350,520,s);
			outtextxy(182,550,"��ʷ��߷֣�");
			outtextxy(400,550,s2);
            
			zuigaofen();
			
		}
    }
    
	return 0;
}

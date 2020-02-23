#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<Windows.h>
#include<time.h>                                                                                                                                                                                                                                                                                                                                                                                                                                                                

//*****变量声明*****
char s[10];           //盛放显示得分的字符串
char s2[10];
int a[4][4] = { 0 };  //盛放4*4数字的二维数组
int loss=0;           //判断游戏是否结束？为1时游戏结束。
int emtpy;            //空格的数量
int score;            //当前得分
int scoremax;         //历史最高分
char name[20]; //这里一个指针变量来接受返回的地址
char namemax[100];


//*******函数*******

void init()       //【初始化函数】
{
    int x, y;
    srand(time(0));
    x = rand() % 4;
    y = rand() % 4;
    a[x][y] = 2;
    emtpy = 15;
}

void music()      //【背景音乐函数】
{
	srand((unsigned int)time(NULL));										     	// 初始窗口大小
	mciSendString("open 2048\\我想大声告诉你.mp3 alias mymusic", NULL, 0, NULL);	// 打开音乐
	mciSendString("play mymusic", NULL, 0, NULL);                                   //音乐走起
}

char *getString(char b[] )  //这里有错
{       
	gets(b); //这里我用gets(a);       
    return b;      
}

void Login()      //【登录函数】
{ 
	char s[]	= "开始游戏";
	char ss[]	= "退出游戏";
    
	MOUSEMSG m;                    //存储鼠标变量
	setfont(50,25,"");             //设置字符样式大小
	outtextxy(530, 550, s);        //显示字符"开始游戏"
	outtextxy(530, 615, ss);       //显示字符"退出游戏"

    while(1)
	{
		m = GetMouseMsg();                             //获得鼠标信息	
		if(m.uMsg==WM_LBUTTONDOWN )                    // 判断是否按下鼠标
	    	if(m.x >= 530 && m.x <= 735 && m.y >= 550 && m.y <= 610)//判断鼠标是否按下区域为"开始游戏"区域
			{
                    
					//char temp[20];
                  	inputbox_getline("玩家姓名输入","请输入您的大名",name,20);


				   /*PIMAGE imgmain=newimage(250,250);
                	getimage(imgmain,"2048/main.png",0,0);
                	putimage(0,0,250,250,imgmain,0,0);
		                //*/	
					break;
					
			}
	        else if(m.x >= 530 && m.x <= 735 && m.y >=615 && m.y <= 655)//判断鼠标按下区域是否是"退出游戏区域"
			{
		      	if(m.uMsg==WM_LBUTTONDOWN)
				{
			    	exit(1);
				}
			}
		
	}
}

void draw()      //【画图函数】
{
    int i, j;                  //依次刷新出每块对应的图片
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            PIMAGE img;             //存储图片
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

void duqu ()  //【读取往期最高分函数】
{
	FILE *fp1, *fp2;   
    int a[1];
    fp1=fopen("a.dat","rb");        //以读的方式打开文档
	fread(a,sizeof(int),1,fp1);     //读入字符串赋值给字符串a
	scoremax=a[0];                 //字符串转换成整数

	fp2=fopen("name.txt","rb+");
    fread(namemax,sizeof(int),2,fp2);
	fclose(fp2);
}

//**************游戏进行中函数********************
int _up()             //【按上键函数】
{
    int x, y, i;
    int sum=0;              //定义每次得分
    for (y = 0; y < 4; ++y) // 从上向下合并相同的方块
	{      
        for (x = 0; x < 4; ++x) 
		{
            if (a[x][y] == 0);
            else
			{
                for (i = x + 1; i < 4; ++i) 
				{
                    if (a[i][y] == 0);
                    else if (a[x][y] == a[i][y]) //相等的合并
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
    for (y = 0; y < 4; ++y)    // 向上移动箱子
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

int _down()       //【按下键函数】
{
    int x, y, i;
    int sum=0;    //定义每次得分
    for (y = 0; y < 4; ++y)  // 向下合并相同的方格 
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
    for (y = 0; y < 4; ++y)  // 向下移动方格 
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
int _left()      //【按左键函数】
{
    int x, y, i;
    int sum=0;                //定义每次得分
    for (x = 0; x < 4; ++x)   // 向左合并相同的方格 
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
    for (x = 0; x < 4; ++x)  // 向左移动方格 
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
int _right()     //【按右键函数】
 {
    int x, y, i;
    int sum=0;               //定义每次得分
    for (x = 0; x < 4; ++x)  // 向右合并相同的方格 
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
    for (x = 0; x < 4; ++x)     // 向右移动方格 
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

int _Esc()    //【中途退出函数】
{
    initgraph(740,760);      //初始化界面
    PIMAGE imu;              //储存图像
    imu = newimage();
    getimage(imu, "2048/结束.jpg");
    putimage(0, 20, imu);

    char e[20] = "退出游戏";
    char j[20] = "您的得分:";
	char l[20] = "用户名:";

    setfont(50,25,"");
	
	outtextxy( 230,145, l);
	outtextxy( 400,145, name);
    outtextxy( 230,205, j);  //显示字符"您的得分"
    sprintf(s,"%d",score);//显示得分
    outtextxy(450,205,s); 
	outtextxy(230,265,"历史最高分:");    
    sprintf(s2,"%d",scoremax);        //将整数最高分转化为字符串并显示
    outtextxy(505,265,s2);
//	outtextxy(230,520, e);  //显示字符"退出游戏"
outtextrect( 230, 520, 555, 580, e);  //显示字符"退出游戏"
	

    MOUSEMSG m;                           //判断鼠标操作（是否退出游戏）
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

void add_number()   //【增加随机方块并判断是否失败函数】
{
    srand(time(0)); 
    if (emtpy > 0)  //有空位随机生成2或4
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
	else             //没空位判断是否游戏结束
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

int play()     //【游戏进行函数】
{
    int k=0;    //对上下左右操作得分进行输出
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

	case VK_ESCAPE:    // 中途退出游戏
    {
        k=_Esc();
        add_number();
        draw();
        break;
    }
    }
return k;
}

//********游戏结束函数*************
void zuigaofen()    //【判断是否大于最高分】
{   
	FILE *fp1, *fp2;   
    int a[1];
	if (scoremax<score)            //判断
	{
		a[0]=score;                //分数赋值给最高分字符串a
        fp1=fopen("a.dat","wb");    //写的方式打开文件
        fwrite(a,sizeof(int),1,fp1);//写入
		fclose(fp1); 

		fp2=fopen("name.txt","rb+");    //写的方式打开文件
        fwrite(name,sizeof(int),2,fp2);//写入

	}
          
}

int  main()         //【主函数】
{
    init();                           //构造初始化函数、关闭图形界面
	char s2[10];                      //最高分字符串
    initgraph(740, 770);              //初始化

    PIMAGE img;                       //菜单图片显示、背景音乐走起
    img = newimage();
    getimage(img, "2048/菜单.jpg");
    putimage(0, 0, img);
    music();                          //音乐

    Login();                          //登录

    

    initgraph(740, 770);              //初始化游戏界面
    PIMAGE imp;
    imp = newimage();
    getimage(img, "2048/背景.jpg");
    putimage(0, 30, imp);             //初始化游戏背景图
    draw();                           //刷新图片

	

	duqu ();                 //读取最高分
    for (; is_run(); delay_fps(30))
    {
        score+=play();                    //分数累加
        sprintf(s,"%d",score);            //实时显示分数
		setfont(29,19,""); 
		outtextxy(20,0,"得分：");         //显示字符串"得分"
	    outtextxy(120,0,s);               //显示字符串"分数"
        outtextxy(500,0,namemax);
		
		outtextxy(350,0,"最高分:");    
        sprintf(s2,"%d",scoremax);        //将整数最高分转化为字符串并显示
        outtextxy(650,0,s2);              //显示字符最高分
		if (loss==1)                                 //失败判断
		{
	      	getimage(img, "2048\\Game over.jpg");
            putimage(175, 175, img);
            outtextxy(182,490,"用户名：");
		    outtextxy(330,490, name);
			outtextxy(182,520,"本次得分：");
			outtextxy(350,520,s);
			outtextxy(182,550,"历史最高分：");
			outtextxy(400,550,s2);
            
			zuigaofen();
			
		}
    }
    
	return 0;
}

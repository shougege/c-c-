#include<stdio.h>
/*
//按下onOKKey 
void onOKKey()
{
	// 判断在什么焦点菜单上按下Ok键，调用相应处理函数
	switch(currentFocus)
	{
		case MENUI:
			menu1OnOk();
			break;
		case MENU2:
			menu2OnOk();
			break;	
	} 
		
}
// 按下Cancel键 
void onCancelKey()
{
	// 判断在什么焦点菜单上按下Cancel键，调用相应处理函数 
	switch(currentFocus)
	{
		case MENU1:
			menu1ONCance1();
		case MENU2:
			menu2OnCancel();
			break;
				
	}	
} */
// 以上是正常的想法， 其实我们可以用 面向对象的思想来处理这样的问题
 
 // 将菜单的属性和操作"封装" 在一起
 typedef struct tagSysMenu
{
	char *text; // 菜单的文本
	BYTE xPos; // 菜单在LCD上的x坐标
	BYTE yPos; // 菜单在LCD上的坐标
	void (*onOkFun)();// 在该菜单上按下ok键的处理函数指针
	void (*onCancelFun)(); // 在该菜单上按下cancel键的处理函数指针	
}SysMenu,*LPSysMenu; 

// 当定义菜单时，只需要这样
static SysMenu menu[MENU_NUM] =
{
	{
		"menu1",0,48,menu10nOk,menu10nCancel 
	},
	{
		"menu2",7,48,menu20nOk,menu20nCancel
	},
	{
		"menu3",7,48,menu30nOk,menu30mCancel
	},
	{
		"menu4",7,48,menu40nOk,menu40nCancel
	}
	
} ;
// OK 键和Cancel键的处理变成
void onOkkey()
{
	menu[currentFocusMenu].onOkFun();
 } 
 // 按下Cancel键
 void onCancelKey()
 {
 	menu[currentFocusMenu].onCancelFun();
  } 
  /*
  这样程序大大的简化了，也开始具有很好的可扩展性！
  我们仅用了面向对象中的封装思想，就让程序结构清晰，其结构是几乎
  可以在无需修改程序的情况下的系统中添加更多的菜单，
  而系统的按键处理函数保持不变 
  */
  
  typedef enum TYPE {
  	ID_OK,
  	ID_OKCANCEL
  }MSG_TYPE;

extern BYTE MessageBox(LPBYIE lpStr,BYTE TYPE)
{
	BYTE keyValue = -1;
	ClearScreen(); //清除屏幕 
	DisplayString(xPos,yPos,lpStr,TRUE); //显示字符串
	// 根据对话框类型决定是否显示确定 取消
	switch(TYPE)
	{
		case ID_OK:
			DisplayString(13,yPos+High+1,"确定"，0)；
			break;
		case ID_OKCANCEL:
		 	DisplayString(8,yPos+High+1,"确定"，0);
			DisplayString(17,yPos+High+1,"取消"，0)；
			break;
		default:
		break; 
	 } 
	 DrawRect(0,0,239,yPos+High+16+4);// 绘制外框
	 // MessageBox是模拟对话框，阻塞运行，等待按键
	 while(keyValue != KEY_OK || keyValue != KEY_CANCEL)
	 {
	 	keyValue = getSysKey();
	  } 
	  // 返回按键类型
	  if(keyValue == KEY_OK)
	  {
	  	 return ID_OK;
	   } 
	   else {
	   	return ID_CANCEL;
	   }
}
int main()
{
	

	return 0;
}

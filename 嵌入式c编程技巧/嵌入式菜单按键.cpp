#include<stdio.h>
/*
//����onOKKey 
void onOKKey()
{
	// �ж���ʲô����˵��ϰ���Ok����������Ӧ������
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
// ����Cancel�� 
void onCancelKey()
{
	// �ж���ʲô����˵��ϰ���Cancel����������Ӧ������ 
	switch(currentFocus)
	{
		case MENU1:
			menu1ONCance1();
		case MENU2:
			menu2OnCancel();
			break;
				
	}	
} */
// �������������뷨�� ��ʵ���ǿ����� ��������˼������������������
 
 // ���˵������ԺͲ���"��װ" ��һ��
 typedef struct tagSysMenu
{
	char *text; // �˵����ı�
	BYTE xPos; // �˵���LCD�ϵ�x����
	BYTE yPos; // �˵���LCD�ϵ�����
	void (*onOkFun)();// �ڸò˵��ϰ���ok���Ĵ�����ָ��
	void (*onCancelFun)(); // �ڸò˵��ϰ���cancel���Ĵ�����ָ��	
}SysMenu,*LPSysMenu; 

// ������˵�ʱ��ֻ��Ҫ����
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
// OK ����Cancel���Ĵ�����
void onOkkey()
{
	menu[currentFocusMenu].onOkFun();
 } 
 // ����Cancel��
 void onCancelKey()
 {
 	menu[currentFocusMenu].onCancelFun();
  } 
  /*
  ����������ļ��ˣ�Ҳ��ʼ���кܺõĿ���չ�ԣ�
  ���ǽ�������������еķ�װ˼�룬���ó���ṹ��������ṹ�Ǽ���
  �����������޸ĳ��������µ�ϵͳ����Ӹ���Ĳ˵���
  ��ϵͳ�İ������������ֲ��� 
  */
  
  typedef enum TYPE {
  	ID_OK,
  	ID_OKCANCEL
  }MSG_TYPE;

extern BYTE MessageBox(LPBYIE lpStr,BYTE TYPE)
{
	BYTE keyValue = -1;
	ClearScreen(); //�����Ļ 
	DisplayString(xPos,yPos,lpStr,TRUE); //��ʾ�ַ���
	// ���ݶԻ������;����Ƿ���ʾȷ�� ȡ��
	switch(TYPE)
	{
		case ID_OK:
			DisplayString(13,yPos+High+1,"ȷ��"��0)��
			break;
		case ID_OKCANCEL:
		 	DisplayString(8,yPos+High+1,"ȷ��"��0);
			DisplayString(17,yPos+High+1,"ȡ��"��0)��
			break;
		default:
		break; 
	 } 
	 DrawRect(0,0,239,yPos+High+16+4);// �������
	 // MessageBox��ģ��Ի����������У��ȴ�����
	 while(keyValue != KEY_OK || keyValue != KEY_CANCEL)
	 {
	 	keyValue = getSysKey();
	  } 
	  // ���ذ�������
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

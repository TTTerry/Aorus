#pragma once
struct Led_Struce
{
    int Fun_Type;
	/*
	Shared memory 狀態,要寫入時請先檢查狀態
	Fun_Type_Ready:讀取Shared memory時,代表目前沒有人占用Shared Memory 可以寫入新指令
	Fun_Type_Write:代表指令寫入
	Fun_Type_Reset:代表Shared占用中
	Fun_Type_Wait:代表Shared占用中
	*/
    unsigned int Current_Easy_Color;
	/*
	要設定顏色值,請使用ARGB的格式,A的值皆為0xFF,EX:0xFFFF0000=紅色
	*/
    int Current_Pattern;
	/*
	要設定的模式
	PatternType_Static:恆亮
	PatternType_Pulse:呼吸
	PatternType_Music:音樂
	PatternType_Flash:閃爍
	PatternType_Random:隨機
	PatternType_Wave:波浪(10區的板子才有)
	PatternType_off:關閉
	PatternType_Color:自動換色
	PatternType_Inte:監控(須搭配其他軟體"EztuneService"才能正常)
	*/
    int Current_Profile;
	/*
	進階模式的設定檔,目前不提供這個功能
	*/
    int Current_Mode;
	/*
	設定成全區模式或是進階模式,目前只提供全區模式
	Mode_Easy:1
	Mode_Adv:0
	*/
    int Other_Mode;
	/*
	監控模式的種類
    Other_mode_CPUTEMP:CPU 溫度
    Other_mode_CPUUSAGE:CPU 使用率
    Other_mode_CPUFAN:CPU 風扇
    Other_mode_MEMORYOC:記憶體是否超頻
    Other_mode_LANSPEED:網路速度
    Other_mode_STATSTATUS:AHCI 或是 RAID
    Other_mode_DAYTIME:白天時間,必須搭配S_Date,E_Date
	EX:
			if((Ptr_Struct->Current_Pattern==PatternType_Inte) && (Ptr_Struct->Other_Mode==Other_mode_DAYTIME))
			{
				wsprintf(Ptr_Struct->S_Date,"08:00");//白天開始時間請用24小時
				wsprintf(Ptr_Struct->E_Date,"19:00");//白天結束時間請用24小時
			}
    Other_mode_SYSTEMTEMP:系統溫度;
	*/
    int Brightness;
	/*
	亮度,數值由0~3
	0最暗,3最亮
	*/
    int Speed;
	/*
	速度,數值由0~2
	0最慢,2最快
	*/
	int Support_Flag;
	/*
	主板支援的模式
	bit0://Color Cycle & Intelligent & Off & Static
	bit1://Music
	bit2://Pulse
	bit3://DFlash
	bit4://Flash
	bit5://Random
	bit6://Wave
	*/
	int Write_mcu_fun;
	/*
	寫入MCU的模式
	Write_mcu_All:寫入所有設定
	Write_mcu_Bri:只寫入亮度
	Write_mcu_Speed:只寫入速度
	Write_mcu_Color:只寫入顏色
	*/
   char S_Date[5];
   char E_Date[5];
};

typedef enum {PatternType_Static=0,PatternType_Pulse=1,PatternType_Music=2,PatternType_Flash = 4,PatternType_Random = 5,PatternType_Wave = 6,PatternType_off = 8,PatternType_Color = 9,PatternType_Inte = 10};
typedef enum{Mode_Easy = 0,Mode_Adv = 1};
typedef enum{Fun_Type_Ready = 0,Fun_Type_Write = 1,Fun_Type_Reset = 2,Fun_Type_Wait = 3};
typedef enum{Write_mcu_All = 0,Write_mcu_Bri = 1,Write_mcu_Speed = 2,Write_mcu_Color = 3};
typedef enum{Other_mode_CPUUSAGE = 1,Other_mode_CPUTEMP = 2,Other_mode_SYSTEMTEMP = 3,Other_mode_CPUFAN = 4,Other_mode_LANSPEED = 5,Other_mode_MEMORYOC = 6,Other_mode_STATSTATUS = 7,Other_mode_DAYTIME = 8};

Led_Struce* Get_LED_Struct(void);
bool Set_LED_Struct(Led_Struce* Str_Ptr);

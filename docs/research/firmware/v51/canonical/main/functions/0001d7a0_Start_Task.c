/* Address: 0001d7a0; name: Start_Task; body bytes: 116 */

/* Confirmed by caller passing name Start_Task and by creation of all four named tasks. */

void Start_Task(void)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  enter_critical();
  FUN_00066ba4(0x53339,"lvgl_task",0x400,0,0,&DAT_1ffe022c);
  FUN_00066ba4(0x1f209,"User_task",0x200,0,3,&DAT_1ffe0230);
  FUN_00066ba4(0x1e021,"Time_task",0x200,0,2,&DAT_1ffe0234);
  uVar2 = 4;
  puVar3 = &DAT_1ffe0238;
  FUN_00066ba4(0x1b495,"Power_task",0x200,0);
  uVar1 = FUN_0006590c(DAT_1ffe0228);
  exit_critical((int)uVar1,(int)((ulonglong)uVar1 >> 0x20),uVar2,puVar3);
  return;
}


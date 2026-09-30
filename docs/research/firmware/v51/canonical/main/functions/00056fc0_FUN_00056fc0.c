/* Address: 00056fc0; name: FUN_00056fc0; body bytes: 142 */

void FUN_00056fc0(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  uVar2 = FUN_00015a5c(0x55);
  uVar4 = FUN_00010a20((&DAT_1ffe0784)[DAT_1ffe0865]);
  uVar4 = FUN_00010920((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),0,0x408f4000);
  uVar3 = FUN_0004b9de(DAT_1ffe05b0,4);
  uVar3 = FUN_0004b9de(uVar3,1);
  FUN_000499de(uVar3,"%.1fV/0.1%s",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20),uVar2);
  uVar2 = FUN_0004037c(0xffa600);
  uVar3 = FUN_0004b9de(DAT_1ffe06ec,DAT_1ffe0865);
  FUN_0004e8b2(uVar3,uVar2,0);
  uVar1 = DAT_1fffab62;
  enter_critical();
  DAT_1fffaa1a = uVar1;
  exit_critical();
  return;
}


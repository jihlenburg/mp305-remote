/* Address: 000581ac; name: FUN_000581ac; body bytes: 162 */

void FUN_000581ac(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  if ((&DAT_1ffe07a4)[DAT_1ffe0866] == 0) {
    uVar2 = FUN_00015a5c(0x46);
    uVar3 = FUN_0004b9de(DAT_1ffe05b0,5);
    uVar3 = FUN_0004b9de(uVar3,1);
    FUN_000499de(uVar3,&DAT_00058264,uVar2);
  }
  else {
    uVar4 = FUN_00010a20();
    uVar4 = FUN_00010920((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),0,0x408f4000);
    uVar2 = FUN_0004b9de(DAT_1ffe05b0,5);
    uVar2 = FUN_0004b9de(uVar2,1);
    FUN_000499de(uVar2,"%.1fV@5A",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
  }
  uVar2 = FUN_0004037c(0xffa600);
  uVar3 = FUN_0004b9de(DAT_1ffe06fc,DAT_1ffe0866);
  FUN_0004e8b2(uVar3,uVar2,0);
  uVar1 = DAT_1fffab70;
  enter_critical();
  DAT_1fffaa0e = uVar1;
  exit_critical();
  return;
}


/* Address: 00056d0c; name: FUN_00056d0c; body bytes: 106 */

void FUN_00056d0c(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar2 = FUN_00015a5c(0x56);
  uVar3 = FUN_0004b9de(DAT_1ffe05b0,6);
  uVar3 = FUN_0004b9de(uVar3,1);
  FUN_000499de(uVar3,"%d %s",(&DAT_1ffe0798)[DAT_1ffe0867],uVar2);
  uVar2 = FUN_0004037c(0xffa600);
  uVar3 = FUN_0004b9de(DAT_1ffe06f4,DAT_1ffe0867);
  FUN_0004e8b2(uVar3,uVar2,0);
  uVar1 = DAT_1fffab64;
  enter_critical();
  DAT_1fffaa1c = uVar1;
  exit_critical();
  return;
}


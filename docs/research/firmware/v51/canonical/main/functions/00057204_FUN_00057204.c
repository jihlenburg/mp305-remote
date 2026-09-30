/* Address: 00057204; name: FUN_00057204; body bytes: 104 */

void FUN_00057204(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  char *pcVar3;
  
  if (DAT_1fffaafa == '\0') {
    uVar1 = FUN_00015a5c(0x46);
    uVar2 = FUN_0004b9de(DAT_1ffe05b0,2);
    uVar2 = FUN_0004b9de(uVar2,1);
    pcVar3 = "%s";
  }
  else {
    uVar1 = FUN_00015a5c(0x55);
    uVar2 = FUN_0004b9de(DAT_1ffe05b0,2);
    uVar2 = FUN_0004b9de(uVar2,1);
    pcVar3 = "30 %s";
  }
  FUN_000499de(uVar2,pcVar3,uVar1);
  uVar1 = FUN_0004037c(0xffa600);
  uVar2 = FUN_0004b9de(DAT_1ffe06dc,DAT_1fffaafa);
  FUN_0004e8b2(uVar2,uVar1,0);
  return;
}


/* Address: 0001cd70; name: FUN_0001cd70; body bytes: 50 */

void FUN_0001cd70(undefined4 param_1,char param_2,undefined4 param_3,byte param_4,byte param_5)

{
  int iVar1;
  
  iVar1 = FUN_00015ee8();
  *(byte *)(iVar1 + 6) =
       *(byte *)(iVar1 + 6) & 0x50 | param_2 << 7 | (param_4 & 3) << 2 | param_5 & 3;
  FUN_0001d038(param_1,param_3);
  return;
}


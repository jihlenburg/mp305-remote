/* Address: 0001d038; name: FUN_0001d038; body bytes: 48 */

void FUN_0001d038(undefined4 param_1,uint param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined2 uVar4;
  
  iVar3 = FUN_00015ee8();
  bVar1 = *(byte *)(iVar3 + 6);
  bVar2 = (byte)((param_2 & 1) << 4);
  *(byte *)(iVar3 + 6) = bVar1 & 0xef | bVar2;
  if (param_2 == 1) {
    uVar4 = 0x28;
  }
  else {
    uVar4 = 100;
  }
  *(undefined2 *)(iVar3 + 10) = uVar4;
  *(byte *)(iVar3 + 6) = bVar1 & 0xaf | bVar2;
  FUN_00012cb0(param_1,9);
  return;
}


/* Address: ram:0004e17a; name: FUN_ram_0004e17a; body bytes: 40 */

undefined4 FUN_ram_0004e17a(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004df14();
  uVar2 = 1;
  if (iVar1 != 0) {
    uVar2 = 1;
    if (*(ushort *)(iVar1 + 0x14) != param_2) {
      *(short *)(iVar1 + 0x14) = (short)param_2;
      uVar2 = 0;
    }
  }
  return uVar2;
}


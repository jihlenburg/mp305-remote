/* Address: ram:0004d270; name: FUN_ram_0004d270; body bytes: 162 */

void FUN_ram_0004d270(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined2 uStack_18;
  undefined2 uStack_16;
  undefined2 uStack_14;
  
  gp = 0x20004000;
  iVar2 = *(int *)(param_1 + 0xc);
  if (iVar2 == 0) {
    tmos_memset(&uStack_18,0,6,param_2);
  }
  else {
    uStack_16 = *(undefined2 *)(iVar2 + 2);
    if (param_2 == 0x62) {
      uVar1 = (uint)*(ushort *)(iVar2 + 6);
      if ((uint)DAT_ram_20001a5e < (uint)*(ushort *)(iVar2 + 6)) {
        uVar1 = (uint)DAT_ram_20001a5e;
      }
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)(iVar2 + 0x10) - (uint)*(ushort *)(iVar2 + 0x12) & 0xff;
      if (*(ushort *)(iVar2 + 0x12) == 0) {
        uVar3 = uVar3 + 2 & 0xff;
      }
      if (uVar1 == 0) {
        uStack_14 = 0xffff;
      }
      else {
        uStack_14 = (undefined2)((int)(uVar3 + uVar1 + -1) / (int)uVar1);
      }
    }
    else {
      uStack_14 = *(undefined2 *)(DAT_ram_20001cc4 + (uint)*(byte *)(iVar2 + 0x1c) * 0x10 + 6);
    }
  }
  uStack_18 = *(undefined2 *)(param_1 + 2);
  FUN_ram_0004d1f6(*(undefined1 *)(param_1 + 8),*(undefined2 *)(param_1 + 6),0,param_2,0,&uStack_18)
  ;
  return;
}


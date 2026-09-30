/* Address: ram:0006620a; name: FUN_ram_0006620a; body bytes: 154 */

undefined4 FUN_ram_0006620a(undefined4 param_1,uint param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  ushort uVar3;
  uint uVar4;
  ushort uVar5;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  uVar3 = DAT_ram_20001d8a;
  if ((*(uint *)(iVar1 + 0x108) & 0x20) == 0) {
    uVar2 = 0x11;
  }
  else {
    uVar2 = 0x12;
    if ((((param_2 - 0x1b & 0xffff) < 0xe1) && ((param_3 - 0x148 & 0xffff) < 0x4149)) &&
       (uVar2 = 0, *(ushort *)(iVar1 + 0x1c8) != param_2)) {
      uVar4 = (uint)DAT_ram_20001d8a;
      *(char *)(iVar1 + 0x7b) = (char)param_2;
      *(ushort *)(iVar1 + 0x7c) = (ushort)param_3;
      uVar5 = DAT_ram_20001d8c;
      if ((param_2 & 0xff) < uVar4) {
        uVar3 = (ushort)(param_2 & 0xff);
      }
      uVar4 = (uint)DAT_ram_20001d8c;
      *(ushort *)(iVar1 + 0x1b8) = uVar3;
      if (param_3 < uVar4) {
        uVar5 = (ushort)param_3;
      }
      *(ushort *)(iVar1 + 0x1ba) = uVar5;
      *(uint *)(iVar1 + 0xa4) = *(uint *)(iVar1 + 0xa4) | 0x800;
      uVar2 = 0;
    }
  }
  return uVar2;
}


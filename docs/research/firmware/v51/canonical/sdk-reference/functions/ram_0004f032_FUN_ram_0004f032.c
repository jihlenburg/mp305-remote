/* Address: ram:0004f032; name: FUN_ram_0004f032; body bytes: 230 */

undefined4 FUN_ram_0004f032(undefined4 param_1,uint param_2)

{
  ushort *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_0004df14(param_2);
  if (iVar2 == 0) {
    uVar3 = 2;
  }
  else {
    puVar1 = *(ushort **)(iVar2 + 0x34);
    if (puVar1 == (ushort *)0x0) {
      uVar3 = 0x12;
    }
    else {
      if (((*(byte *)((int)puVar1 + 5) & 0xfb) != 2) && (*(byte *)((int)puVar1 + 5) != 4)) {
        gp = 0x20004000;
        return 0x12;
      }
      uVar3 = 2;
      if (*puVar1 == param_2) {
        tmos_memcpy(puVar1 + 4,param_1,0x10);
        tmos_memcpy(puVar1 + 0xc,param_1,0x10);
        if ((byte)(*(char *)((int)puVar1 + 3) - 0x11U) < 2) {
          FUN_ram_000440ba(puVar1 + 0x1e,0x10);
          FUN_ram_0004e8ec(puVar1,puVar1 + 4,puVar1 + 0x1e,puVar1 + 0x16);
          if (((char)puVar1[1] != '\0') || (*(char *)((int)puVar1 + 3) == '\x12')) {
            uVar3 = FUN_ram_00050272(puVar1);
            return uVar3;
          }
          *(undefined1 *)((int)puVar1 + 3) = 0x12;
          uVar3 = 0;
        }
        else {
          uVar3 = 0;
          if ((*(char *)((int)puVar1 + 3) == 'Q') && (uVar3 = 0, (char)puVar1[1] != '\0')) {
            uVar3 = FUN_ram_000502da(puVar1);
            return uVar3;
          }
        }
      }
    }
  }
  return uVar3;
}


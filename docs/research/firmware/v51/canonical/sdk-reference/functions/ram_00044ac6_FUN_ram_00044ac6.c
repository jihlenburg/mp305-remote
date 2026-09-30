/* Address: ram:00044ac6; name: FUN_ram_00044ac6; body bytes: 228 */

int FUN_ram_00044ac6(undefined2 *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  
  gp = 0x20004000;
  iVar1 = 2;
  if (param_1 != (undefined2 *)0x0) {
    iVar1 = 0x14;
    iVar2 = FUN_ram_0004df14(*param_1);
    if (((iVar2 != 0) && (iVar1 = 0x12, 1 < (byte)(DAT_ram_20001d50 - 1U))) &&
       ((*(char *)(iVar2 + 0xc) != '\b' || (param_2 == 0)))) {
      iVar1 = 0x11;
      if (*(int *)(iVar2 + 0x38) == 0) {
        puVar3 = (undefined1 *)FUN_ram_20000040(0x2c,0x4714);
        *(undefined1 **)(iVar2 + 0x38) = puVar3;
        iVar1 = 0x13;
        if (puVar3 != (undefined1 *)0x0) {
          tmos_memset(puVar3,0,0x2c);
          *(undefined2 *)(puVar3 + 2) = *param_1;
          tmos_memcpy(puVar3 + 4,param_1 + 2,0x1c);
          *puVar3 = 2;
          iVar1 = FUN_ram_0004f238(*(char *)(iVar2 + 0xc) == '\b',DAT_ram_20001d4c,*param_1,
                                   puVar3 + 4);
          if (param_2 != 0) {
            FUN_ram_0004e81e(iVar2,param_2);
          }
          if (iVar1 != 0) {
            FUN_ram_0004434e(iVar2);
          }
        }
      }
    }
  }
  return iVar1;
}


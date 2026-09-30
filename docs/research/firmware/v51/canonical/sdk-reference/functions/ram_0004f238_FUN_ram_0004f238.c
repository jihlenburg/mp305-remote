/* Address: ram:0004f238; name: FUN_ram_0004f238; body bytes: 194 */

int FUN_ram_0004f238(int param_1,undefined1 param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  
  gp = 0x20004000;
  iVar3 = FUN_ram_0004df14(param_3);
  if (iVar3 != 0) {
    if (*(int *)(iVar3 + 0x34) != 0) {
      gp = 0x20004000;
      return 0x11;
    }
    bVar1 = GAP_GetParamValue(0x13);
    bVar2 = GAP_GetParamValue(0x14);
    if (((param_4 != 0) && (bVar1 <= *(byte *)(param_4 + 0x18))) &&
       (*(byte *)(param_4 + 0x18) <= bVar2)) {
      puVar4 = (undefined2 *)FUN_ram_20000040(0x84,0x53);
      *(undefined2 **)(iVar3 + 0x34) = puVar4;
      if (puVar4 == (undefined2 *)0x0) {
        gp = 0x20004000;
        return 0x13;
      }
      tmos_memset(puVar4,0,0x84);
      *(undefined1 *)((int)puVar4 + 3) = 0;
      *(char *)(puVar4 + 1) = (char)param_1;
      *(undefined1 *)(puVar4 + 2) = param_2;
      *puVar4 = (short)param_3;
      *(int *)(puVar4 + 0x36) = param_4;
      *(undefined4 *)(puVar4 + 0x14) = 0;
      *(undefined1 *)((int)puVar4 + 5) = 0;
      if (param_1 == 0) {
        gp = 0x20004000;
        return 0;
      }
      iVar5 = FUN_ram_00050212(puVar4);
      if (iVar5 == 0) {
        gp = 0x20004000;
        return 0;
      }
      FUN_ram_0004e524(iVar3);
      gp = 0x20004000;
      return iVar5;
    }
  }
  return 2;
}


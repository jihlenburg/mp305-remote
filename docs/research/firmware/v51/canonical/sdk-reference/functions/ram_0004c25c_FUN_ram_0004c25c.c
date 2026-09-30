/* Address: ram:0004c25c; name: FUN_ram_0004c25c; body bytes: 232 */

undefined4 FUN_ram_0004c25c(undefined4 param_1,undefined1 param_2,int param_3,undefined4 *param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  
  gp = 0x20004000;
  if (param_4 == (undefined4 *)0x0) {
    return 1;
  }
  iVar2 = linkDB_State(param_1,1);
  uVar4 = 0x14;
  if (iVar2 != 0) {
    uVar1 = 0;
    uVar3 = (uint)DAT_ram_20001a61;
    if (param_3 == 0) {
      uVar1 = (uint)DAT_ram_20001a61;
      uVar3 = (uint)DAT_ram_20001a60;
    }
    puVar5 = (undefined1 *)(uVar1 * 0x10 + DAT_ram_20001a58);
    for (; uVar1 < uVar3; uVar1 = uVar1 + 1 & 0xff) {
      if (*(short *)(puVar5 + 2) == 0) {
        if (param_3 == 0) {
          *(undefined4 *)(puVar5 + 0xc) = 0;
        }
        else {
          iVar2 = FUN_ram_20000040(0x20,0x4c02);
          *(int *)(puVar5 + 0xc) = iVar2;
          if (iVar2 == 0) break;
          tmos_memset(iVar2,0,0x20);
          *(short *)(puVar5 + 2) = (short)uVar1 + 0x40;
        }
        *puVar5 = 0;
        *(short *)(puVar5 + 6) = (short)param_1;
        iVar2 = DAT_ram_20001cc4;
        if (param_3 == 0) {
          puVar5[8] = param_2;
        }
        else {
          puVar5[8] = *(undefined1 *)(param_3 + 9);
          *(char *)(*(int *)(puVar5 + 0xc) + 0x1c) = (char)((uint)(param_3 - iVar2 >> 4) >> 4);
        }
        *param_4 = puVar5;
        gp = 0x20004000;
        return 0;
      }
      puVar5 = puVar5 + 0x10;
    }
    uVar4 = 0x15;
  }
  return uVar4;
}


/* Address: ram:0004a896; name: FUN_ram_0004a896; body bytes: 270 */

int FUN_ram_0004a896(int param_1,undefined2 *param_2)

{
  undefined2 uVar1;
  int iVar2;
  code *pcVar3;
  undefined2 *puVar4;
  short *psVar5;
  undefined2 uStack_1e;
  undefined1 auStack_1c [8];
  int iStack_14;
  
  gp = 0x20004000;
  iVar2 = GATT_FindHandle(*(undefined2 *)(param_1 + 8),&uStack_1e);
  if (iVar2 == 0) {
    iVar2 = 1;
  }
  else {
    if ((*(byte *)(iVar2 + 8) & 0x20) != 0) {
      pcVar3 = (code *)FUN_ram_0004a174(uStack_1e);
      if (pcVar3 == (code *)0x0) {
        *param_2 = *(undefined2 *)(param_1 + 8);
        gp = 0x20004000;
        return 0xe;
      }
      iVar2 = (*pcVar3)(*(undefined2 *)(param_1 + 2),iVar2,0x12);
      if (iVar2 != 0) goto LAB_ram_0004a8ee;
    }
    uVar1 = *(undefined2 *)(param_1 + 2);
    puVar4 = (undefined2 *)FUN_ram_0004a124(uVar1);
    if (puVar4 == (undefined2 *)0x0) {
      puVar4 = (undefined2 *)FUN_ram_0004a124(0xffff);
      if (puVar4 == (undefined2 *)0x0) {
        *param_2 = *(undefined2 *)(param_1 + 8);
        gp = 0x20004000;
        return 9;
      }
      *puVar4 = uVar1;
    }
    psVar5 = puVar4 + 2;
    iVar2 = 0;
    do {
      if (*psVar5 == 0) {
        tmos_memcpy(puVar4 + iVar2 * 6 + 2,param_1 + 8,0xc);
        tmos_memcpy(auStack_1c,param_1 + 8,0xc);
        iStack_14 = GATT_bm_alloc(*(undefined2 *)(param_1 + 2),0x17,*(undefined2 *)(param_1 + 0xc),0
                                  ,0x10);
        if (iStack_14 == 0) {
          *param_2 = *(undefined2 *)(param_1 + 8);
          gp = 0x20004000;
          return 0x11;
        }
        tmos_memcpy(iStack_14,*(undefined4 *)(param_1 + 0x10),*(undefined2 *)(param_1 + 0xc));
        iVar2 = FUN_ram_00043de4(*(undefined2 *)(param_1 + 2),auStack_1c);
        if (iVar2 == 0) {
          gp = 0x20004000;
          return 0;
        }
        gp = 0x20004000;
        return 0x16;
      }
      iVar2 = iVar2 + 1;
      psVar5 = psVar5 + 6;
    } while (iVar2 != 0xf);
    iVar2 = 9;
  }
LAB_ram_0004a8ee:
  *param_2 = *(undefined2 *)(param_1 + 8);
  return iVar2;
}


/* Address: ram:000458c4; name: FUN_ram_000458c4; body bytes: 362 */

undefined4 FUN_ram_000458c4(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  ushort auStack_18 [2];
  ushort uStack_14;
  ushort auStack_12 [5];
  
  gp = 0x20004000;
  if (param_1 == 3) {
    uVar6 = *(undefined2 *)(param_2 + 10);
    uVar5 = *(undefined2 *)(param_2 + 8);
    uVar4 = *(undefined2 *)(param_2 + 6);
    cVar1 = *(char *)(param_2 + 3);
    uVar3 = *(undefined2 *)(param_2 + 4);
  }
  else {
    if (param_1 == 0x200d) {
      if (*(char *)(param_2 + 2) == '\0') {
        gp = 0x20004000;
        return 1;
      }
      if (DAT_ram_200019e0 == (undefined1 *)0x0) {
        gp = 0x20004000;
        return 1;
      }
      FUN_ram_0004491e(*(char *)(param_2 + 2),*DAT_ram_200019e0,DAT_ram_200019e0[3],
                       DAT_ram_200019e0 + 4,0,0,0,0,0,0);
      FUN_ram_00044f96(1);
      gp = 0x20004000;
      return 1;
    }
    if (param_1 == 0x200e) {
      gp = 0x20004000;
      return 1;
    }
    if (param_1 != 0x2013) {
      if (param_1 == 0x2019) {
        gp = 0x20004000;
        return 1;
      }
      if (param_1 == 0xc) {
        FUN_ram_000448c6(DAT_ram_20001c07);
        gp = 0x20004000;
        return 1;
      }
      if (param_1 != 0xffff) {
        gp = 0x20004000;
        return 0;
      }
      if (*(char *)(param_2 + 5) != '\x12') {
        gp = 0x20004000;
        return 1;
      }
      iVar2 = FUN_ram_00052648(*(undefined2 *)(param_2 + 8),*(undefined2 *)(param_2 + 10),
                               *(undefined2 *)(param_2 + 0xc),*(undefined2 *)(param_2 + 0xe));
      if (iVar2 == 0) {
        auStack_18[0] = 1;
      }
      else {
        iVar2 = GAP_GetParamValue(0x17);
        auStack_18[0] = (ushort)(iVar2 != 0);
      }
      FUN_ram_0004de1e(*(undefined2 *)(param_2 + 2),*(undefined1 *)(param_2 + 4),auStack_18);
      if (auStack_18[0] != 0) {
        gp = 0x20004000;
        return 1;
      }
      GAPRole_GetParameter(0x311,&uStack_14);
      GAPRole_GetParameter(0x312,auStack_12);
      if (*(ushort *)(param_2 + 8) < uStack_14) {
        *(ushort *)(param_2 + 8) = uStack_14;
      }
      if (auStack_12[0] < *(ushort *)(param_2 + 10)) {
        *(ushort *)(param_2 + 10) = auStack_12[0];
      }
      if (*(ushort *)(param_2 + 10) < *(ushort *)(param_2 + 8)) {
        *(ushort *)(param_2 + 10) = *(ushort *)(param_2 + 8);
      }
      FUN_ram_0005a7de(*(undefined2 *)(param_2 + 2));
      thunk_FUN_ram_000652dc
                (*(undefined2 *)(param_2 + 2),*(undefined2 *)(param_2 + 8),
                 *(undefined2 *)(param_2 + 10),*(undefined2 *)(param_2 + 0xc),
                 *(undefined2 *)(param_2 + 0xe),0,0);
      gp = 0x20004000;
      return 1;
    }
    cVar1 = *(char *)(param_2 + 2);
    if (cVar1 == '\0') {
      gp = 0x20004000;
      return 1;
    }
    uVar6 = 0;
    uVar5 = 0;
    uVar4 = 0;
    uVar3 = 0;
  }
  FUN_ram_00044812(cVar1,uVar3,uVar4,uVar5,uVar6);
  return 1;
}


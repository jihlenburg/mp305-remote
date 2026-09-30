/* Address: ram:00008402; name: FUN_ram_00008402; body bytes: 668 */

/* WARNING: Removing unreachable block (ram,0x0000865a) */

int FUN_ram_00008402(int param_1,undefined4 *param_2,byte *param_3,int *param_4)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  byte *pbVar4;
  int unaff_s4;
  int iVar5;
  int *piStack_94;
  uint uStack_90;
  int iStack_8c;
  undefined4 uStack_88;
  int iStack_84;
  int iStack_7c;
  byte bStack_78;
  undefined1 uStack_77;
  undefined1 uStack_76;
  undefined1 uStack_4d;
  undefined4 uStack_38;
  
  gp = &DAT_ram_20002000;
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) == 0)) {
    FUN_ram_00007f90();
  }
  if (param_2 == &DAT_ram_00009234) {
    param_2 = *(undefined4 **)(param_1 + 4);
  }
  else if (param_2 == (undefined4 *)&DAT_ram_00009254) {
    param_2 = *(undefined4 **)(param_1 + 8);
  }
  else if (param_2 == (undefined4 *)&DAT_ram_00009214) {
    param_2 = *(undefined4 **)(param_1 + 0xc);
  }
  if ((((*(ushort *)(param_2 + 3) & 8) == 0) || (param_2[4] == 0)) &&
     (iVar5 = FUN_ram_00007b82(param_1,param_2), iVar5 != 0)) {
    return -1;
  }
  uStack_77 = 0x20;
  iStack_7c = 0;
  uStack_76 = 0x30;
  piStack_94 = param_4;
  pbVar4 = param_3;
  do {
    for (; (*param_3 != 0 && (*param_3 != 0x25)); param_3 = param_3 + 1) {
    }
    iVar5 = (int)param_3 - (int)pbVar4;
    if (iVar5 != 0) {
      iVar1 = FUN_ram_000083c0(param_1,param_2,pbVar4,iVar5);
      if (iVar1 == -1) {
LAB_ram_0000867a:
        if ((*(ushort *)(param_2 + 3) & 0x40) != 0) {
          return -1;
        }
        return iStack_7c;
      }
      iStack_7c = iStack_7c + iVar5;
    }
    if (*param_3 == 0) goto LAB_ram_0000867a;
    uStack_90 = 0;
    iStack_84 = 0;
    iStack_8c = -1;
    uStack_88 = 0;
    uStack_4d = 0;
    uStack_38 = 0;
    pbVar4 = param_3 + 1;
    while( true ) {
      iVar5 = FUN_ram_00008cbc("#-0+ ",*pbVar4,5);
      param_3 = pbVar4 + 1;
      if (iVar5 == 0) break;
      uStack_90 = uStack_90 | 1 << (iVar5 - 0x9274U & 0x1f);
      pbVar4 = param_3;
    }
    if ((uStack_90 & 0x10) != 0) {
      uStack_4d = 0x20;
    }
    if ((uStack_90 & 8) != 0) {
      uStack_4d = 0x2b;
    }
    if (*pbVar4 == 0x2a) {
      piVar3 = piStack_94 + 1;
      iStack_84 = *piStack_94;
      piStack_94 = piVar3;
      if (iStack_84 < 0) {
        iStack_84 = -iStack_84;
        uStack_90 = uStack_90 | 2;
      }
    }
    else {
      bVar2 = false;
      param_3 = pbVar4;
      iVar5 = iStack_84;
      while( true ) {
        if (9 < *param_3 - 0x30) break;
        bVar2 = true;
        iVar5 = iVar5 * 10 + (*param_3 - 0x30);
        param_3 = param_3 + 1;
      }
      if (bVar2) {
        iStack_84 = iVar5;
      }
    }
    if (*param_3 == 0x2e) {
      if (param_3[1] == 0x2a) {
        param_3 = param_3 + 2;
        piVar3 = piStack_94 + 1;
        iVar5 = *piStack_94;
        piStack_94 = piVar3;
        if (iVar5 < 0) {
          iVar5 = -1;
        }
      }
      else {
        iStack_8c = 0;
        bVar2 = false;
        iVar5 = 0;
        while( true ) {
          param_3 = param_3 + 1;
          if (9 < *param_3 - 0x30) break;
          bVar2 = true;
          iVar5 = iVar5 * 10 + (*param_3 - 0x30);
        }
        if (!bVar2) goto LAB_ram_000085e0;
      }
      iStack_8c = iVar5;
    }
LAB_ram_000085e0:
    iVar5 = FUN_ram_00008cbc(&DAT_ram_0000927c,*param_3,3);
    if (iVar5 != 0) {
      param_3 = param_3 + 1;
      uStack_90 = uStack_90 | 0x40 << (iVar5 - 0x927cU & 0x1f);
    }
    bStack_78 = *param_3;
    param_3 = param_3 + 1;
    iVar5 = FUN_ram_00008cbc("efgEFG",bStack_78,6);
    if (iVar5 == 0) {
      unaff_s4 = FUN_ram_000087aa(param_1,&uStack_90,param_2,FUN_ram_000083c0,&piStack_94);
      if (unaff_s4 == -1) goto LAB_ram_0000867a;
    }
    else if ((uStack_90 & 0x100) == 0) {
      piStack_94 = (int *)(((int)piStack_94 + 7U & 0xfffffff8) + 8);
    }
    else {
      piStack_94 = piStack_94 + 1;
    }
    iStack_7c = iStack_7c + unaff_s4;
    pbVar4 = param_3;
  } while( true );
}


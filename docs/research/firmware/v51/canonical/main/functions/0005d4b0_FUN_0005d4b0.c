/* Address: 0005d4b0; name: FUN_0005d4b0; body bytes: 330 */

void FUN_0005d4b0(int param_1,undefined4 param_2,int param_3,uint param_4,undefined4 param_5,
                 int *param_6,int param_7)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int local_78;
  int local_74;
  int local_68;
  int local_64;
  undefined1 auStack_54 [24];
  undefined1 auStack_3c [16];
  int local_2c;
  int local_28;
  
  uVar2 = FUN_00046718(param_2);
  FUN_0001049c(auStack_54,0x14);
  if (*(int *)(param_1 + 0x38) == 0) {
    FUN_00050540(auStack_54,0x14,&LAB_0005d5fc,param_5);
    *(undefined1 **)(param_3 + 0x1c) = auStack_54;
    *(byte *)(param_3 + 0x4c) = *(byte *)(param_3 + 0x4c) | 0x40;
  }
  else if ((*(int *)(param_1 + 0x58) < (int)(param_4 & 0xffff)) ||
          (iVar3 = *(int *)(*(int *)(param_1 + 0x38) + (param_4 & 0xffff) * 4 + -4), iVar3 == 0)) {
    *(undefined4 *)(param_3 + 0x1c) = 0;
  }
  else {
    *(int *)(param_3 + 0x1c) = iVar3;
    *(byte *)(param_3 + 0x4c) = *(byte *)(param_3 + 0x4c) & 0xbf;
  }
  cVar1 = *(char *)(param_1 + 0x3c);
  if ((((cVar1 != '\x02') && (cVar1 != '\x04')) && (cVar1 != '\x01')) && (cVar1 != '\0')) {
    if ((cVar1 != '\x10') && (cVar1 != '\b')) {
      return;
    }
    FUN_0004bab4(param_1,&local_78);
    uVar4 = FUN_0003db28(&local_78);
    uVar5 = FUN_0003db0a(&local_78);
    if (uVar4 >> 1 < uVar5 >> 1) {
      uVar4 = FUN_0003db28();
    }
    else {
      uVar4 = FUN_0003db0a(&local_78);
    }
    uVar4 = uVar4 >> 1;
    local_68 = local_78 + uVar4;
    local_64 = local_74 + uVar4;
    iVar3 = FUN_0004c6f0(param_1,0x20000);
    local_2c = 0;
    if (*(char *)(param_1 + 0x3c) == '\b') {
      local_2c = (uVar4 - iVar3) - (*(int *)(param_3 + 0x3c) + 0xf);
    }
    else if (*(char *)(param_1 + 0x3c) == '\x10') {
      local_2c = *(int *)(param_3 + 0x3c) + uVar4 + iVar3 + 0xf;
    }
    local_2c = local_68 + local_2c;
    local_28 = local_64;
    FUN_0004f292(&local_2c,
                 (uint)(param_7 * 10 * *(int *)(param_1 + 0x50)) /
                 ((*(ushort *)(param_1 + 0x48) & 0x7fff) - 1) + *(int *)(param_1 + 0x54) * 10,0x100,
                 0x100,&local_68,0);
    param_6 = &local_2c;
  }
  FUN_0005da08(param_1,param_3,param_6,auStack_3c);
  FUN_00041d52(uVar2,param_3,auStack_3c);
  return;
}


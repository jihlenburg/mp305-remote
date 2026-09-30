/* Address: 00027ee0; name: FUN_00027ee0; body bytes: 180 */

undefined4 FUN_00027ee0(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 uVar7;
  int local_24;
  
  puVar5 = *(undefined4 **)(param_2 + 0x48);
  uVar7 = *puVar5;
  uVar4 = (*(uint *)(param_2 + 0x20) & 0xffff) >> 8;
  iVar6 = 0x100;
  if (uVar4 == 7) {
    iVar2 = 2;
  }
  else if (uVar4 == 8) {
    iVar2 = 4;
  }
  else if (uVar4 == 9) {
    iVar2 = 0x10;
  }
  else {
    iVar2 = iVar6;
    if (uVar4 != 10) {
      iVar2 = 0;
    }
  }
  iVar2 = iVar2 * 4;
  if ((int)(*(uint *)(param_2 + 0x20) << 0xc) < 0) {
    iVar2 = puVar5[8];
  }
  else {
    if (*(char *)(param_2 + 0x10) == '\x01') {
      local_24 = param_4;
      iVar3 = FUN_0004a318(iVar2);
      if (iVar3 == 0) {
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      iVar1 = FUN_00036b7c(uVar7,0xc,iVar3,iVar2,&local_24);
      if ((iVar1 != 0) || (local_24 != iVar2)) {
        FUN_00046bec(iVar3);
        return 0;
      }
      puVar5[1] = iVar3;
      goto LAB_00027f6a;
    }
    if (*(char *)(param_2 + 0x10) != '\0') {
      return 0;
    }
    iVar2 = *(int *)(param_2 + 0xc);
  }
  iVar3 = *(int *)(iVar2 + 0x10);
LAB_00027f6a:
  *(int *)(param_2 + 0x30) = iVar3;
  if (uVar4 == 7) {
    iVar6 = 2;
  }
  else if (uVar4 == 8) {
    iVar6 = 4;
  }
  else if (uVar4 == 9) {
    iVar6 = 0x10;
  }
  else if (uVar4 != 10) {
    iVar6 = 0;
  }
  *(int *)(param_2 + 0x34) = iVar6;
  return 1;
}


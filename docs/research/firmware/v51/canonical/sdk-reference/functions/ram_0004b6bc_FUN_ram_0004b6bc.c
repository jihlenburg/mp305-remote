/* Address: ram:0004b6bc; name: FUN_ram_0004b6bc; body bytes: 174 */

int FUN_ram_0004b6bc(undefined4 param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined2 auStack_22 [5];
  
  gp = 0x20004000;
  uVar4 = 0;
  while( true ) {
    if (*(ushort *)(param_2 + 1) <= uVar4) {
      return 0;
    }
    iVar1 = uVar4 * 2;
    iVar2 = iVar1 + 1;
    iVar3 = GATT_FindHandle(CONCAT11(*(undefined1 *)(*param_2 + iVar2),
                                     *(undefined1 *)(*param_2 + iVar1)),auStack_22);
    if (iVar3 == 0) break;
    iVar3 = FUN_ram_0004b654(param_1,*(undefined1 *)(iVar3 + 8),auStack_22[0]);
    if (iVar3 != 0) {
      *(undefined1 *)*param_2 = ((undefined1 *)*param_2)[iVar1];
      *(undefined1 *)(*param_2 + 1) = *(undefined1 *)(iVar2 + *param_2);
      gp = 0x20004000;
      return iVar3;
    }
    uVar4 = uVar4 + 1 & 0xffff;
  }
  *(undefined1 *)*param_2 = ((undefined1 *)*param_2)[iVar1];
  *(undefined1 *)(*param_2 + 1) = *(undefined1 *)(iVar2 + *param_2);
  gp = 0x20004000;
  return 1;
}


/* Address: 000411ca; name: FUN_000411ca; body bytes: 162 */

void FUN_000411ca(ushort *param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 local_38;
  int local_34;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  
  if (param_1 == (ushort *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = param_1[4];
  if (param_2 == 0) {
    uVar5 = FUN_000414c8(param_1,0);
    FUN_0004a5e2(uVar5,(uint)uVar1 * (*(uint *)(param_1 + 2) >> 0x10));
  }
  else {
    local_28 = 0;
    local_24 = 0;
    local_20 = param_1[2] - 1;
    local_1c = (*(uint *)(param_1 + 2) >> 0x10) - 1;
    iVar2 = FUN_0003db4c(&local_38,param_2,&local_28);
    if (((iVar2 != 0) && (iVar2 = FUN_0003db28(&local_38), 0 < iVar2)) &&
       (iVar2 = FUN_0003db0a(&local_38), 0 < iVar2)) {
      iVar2 = FUN_000414c8(param_1,local_38,local_34);
      iVar3 = FUN_00040314(*param_1 >> 8);
      iVar4 = FUN_0003db28(&local_38);
      for (; local_34 <= local_2c; local_34 = local_34 + 1) {
        FUN_0004a5e2(iVar2,iVar4 * iVar3 + 7 >> 3);
        iVar2 = iVar2 + (uint)uVar1;
      }
    }
  }
  return;
}


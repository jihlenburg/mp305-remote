/* Address: 0003cd58; name: FUN_0003cd58; body bytes: 330 */

void FUN_0003cd58(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint in_fpscr;
  undefined1 auStack_108 [36];
  float local_e4;
  float local_e0;
  undefined4 local_dc;
  undefined4 uStack_d8;
  undefined2 local_d4;
  int local_b8;
  undefined1 auStack_b4 [112];
  undefined4 local_44;
  undefined4 uStack_40;
  undefined1 auStack_30 [20];
  
  iVar1 = FUN_00046698();
  uVar2 = FUN_00046718(param_1);
  FUN_000371f0(iVar1,&local_44,&local_b8);
  if (0 < local_b8) {
    FUN_00040ce4(auStack_108);
    FUN_0004cdfc(iVar1,0,auStack_108);
    local_dc = local_44;
    uStack_d8 = uStack_40;
    local_e4 = (float)VectorSignedToFloat(*(undefined4 *)(iVar1 + 0x2c),(byte)(in_fpscr >> 0x16) & 3
                                         );
    local_e4 = *(float *)(iVar1 + 0x38) + local_e4;
    local_e0 = (float)VectorSignedToFloat(*(undefined4 *)(iVar1 + 0x2c),(byte)(in_fpscr >> 0x16) & 3
                                         );
    local_e0 = *(float *)(iVar1 + 0x3c) + local_e0;
    local_d4 = (undefined2)local_b8;
    FUN_00040c74(uVar2,auStack_108);
  }
  iVar3 = FUN_0004c846(iVar1,0x20000);
  iVar4 = FUN_0004c88e(iVar1,0x20000);
  iVar5 = FUN_0004c8e2(iVar1,0x20000);
  iVar6 = FUN_0004c7e6(iVar1,0x20000);
  iVar7 = iVar4;
  if (iVar4 < iVar3) {
    iVar7 = iVar3;
  }
  iVar8 = iVar6;
  if (iVar6 < iVar5) {
    iVar8 = iVar5;
  }
  if (iVar8 < iVar7) {
    if (iVar4 < iVar3) {
      iVar4 = iVar3;
    }
  }
  else {
    iVar4 = iVar6;
    if (iVar6 < iVar5) {
      iVar4 = iVar5;
    }
  }
  iVar4 = local_b8 - iVar4;
  if (0 < iVar4) {
    FUN_00040ce4(auStack_108);
    FUN_0004cdfc(iVar1,0x20000,auStack_108);
    local_dc = local_44;
    uStack_d8 = uStack_40;
    local_e4 = (float)VectorSignedToFloat(*(undefined4 *)(iVar1 + 0x2c),(byte)(in_fpscr >> 0x16) & 3
                                         );
    local_e4 = *(float *)(iVar1 + 0x30) + local_e4;
    local_e0 = (float)VectorSignedToFloat(*(undefined4 *)(iVar1 + 0x2c),(byte)(in_fpscr >> 0x16) & 3
                                         );
    local_e0 = *(float *)(iVar1 + 0x34) + local_e0;
    local_d4 = (undefined2)iVar4;
    FUN_00040c74(uVar2,auStack_108);
  }
  FUN_000374e4(iVar1,&local_44,local_b8,auStack_30);
  FUN_00042ec4(auStack_b4);
  FUN_0004d0bc(iVar1,0x30000,auStack_b4);
  FUN_00042a98(uVar2,auStack_b4,auStack_30);
  return;
}


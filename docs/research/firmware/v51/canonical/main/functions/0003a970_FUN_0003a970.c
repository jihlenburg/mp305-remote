/* Address: 0003a970; name: FUN_0003a970; body bytes: 190 */

void FUN_0003a970(float param_1,float param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint in_fpscr;
  float fVar3;
  float fVar4;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined1 auStack_30 [16];
  uint local_20 [2];
  
  iVar1 = FUN_0004d4c8();
  if ((iVar1 != 0) && (param_1 != param_2)) {
    if (0x43b40000 < (int)param_1) {
      param_1 = param_1 - 360.0;
    }
    if (0x43b40000 < (int)param_2) {
      param_2 = param_2 - 360.0;
    }
    fVar4 = (float)VectorSignedToFloat(*(undefined4 *)(param_3 + 0x2c),
                                       (byte)((in_fpscr & 0xfffffff) >> 0x16) & 3);
    fVar3 = (float)VectorSignedToFloat(*(undefined4 *)(param_3 + 0x2c),
                                       (byte)((in_fpscr & 0xfffffff) >> 0x16) & 3);
    fVar4 = fVar4 + param_1;
    fVar3 = fVar3 + param_2;
    if (0x43b40000 < (int)fVar4) {
      fVar4 = fVar4 - 360.0;
    }
    if (0x43b40000 < (int)fVar3) {
      fVar3 = fVar3 - 360.0;
    }
    FUN_000371f0(param_3,&local_38,local_20);
    uVar2 = FUN_0004c5ac(param_3,param_4);
    iVar1 = FUN_0004c924(param_3,param_4,0x51);
    FUN_00040d14(fVar4,fVar3,local_38,uStack_34,local_20[0] & 0xffff,uVar2,iVar1 != 0,auStack_30);
    FUN_0004d40e(param_3,auStack_30);
  }
  return;
}


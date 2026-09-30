/* Address: 000670f4; name: FUN_000670f4; body bytes: 106 */

void FUN_000670f4(undefined4 param_1)

{
  short sVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  byte *pbVar5;
  
  uVar2 = FUN_00046698();
  uVar3 = FUN_0004675a(param_1);
  sVar1 = FUN_000461e4(uVar2);
  piVar4 = (int *)FUN_0003f334(uVar3);
  pbVar5 = (byte *)FUN_000461d4(uVar2);
  FUN_0003f338(uVar3,((ushort)pbVar5[1] * 100 + (ushort)pbVar5[2] * 10 +
                      (ushort)pbVar5[3] + (*pbVar5 - 0x30) * 1000 + -0x14d0) - sVar1,
               (*piVar4 << 8) >> 0x18);
  return;
}

